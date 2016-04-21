 /***********************************************************
 *                         _ooOoo_                          *
 *                        o8888888o                         *
 *                        88" . "88                         *
 *                        (| -_- |)                         *
 *                         O\ = /O                          *
 *                     ____/`---'\____                      *
 *                   .   ' \\| |// `.                       *
 *                    / \\||| : |||// \                     *
 *                  / _||||| -:- |||||- \                   *
 *                    | | \\\ - /// | |                     *
 *                  | \_| ''\---/'' | |                     *
 *                   \ .-\__ `-` ___/-. /                   *
 *                ___`. .' /--.--\ `. . __                  *
 *             ."" '< `.____<|>_/___.' >'"".                *
 *            | | : `- \`.;` _ /`;.`/ - ` : | |             *
 *              \ \ `-. \_ __\ /__ _/ .-` / /               *
 *      ======`-.____`-.___\_____/___.-`____.-'======       *
 *                         `=---='                          *
 *                                                          *
 *      .............................................       *
 *             Buddha bless me, No bug forever              *
 *                                                          *
 ************************************************************
 * Author       : ZhuHaiWen                                 *
 * Email        : zhuhw@ihep.ac.cn/zhwren0211@whu.edu.cn    *
 * Last modified: 2015-07-14 09:46
 * Filename     : MocotoDetectorConstruction.cc
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/

#include "MocotoDetectorConstruction.hh"
#include "MocotoVolumeRCT.hh"
#include "MocotoVolumeTarget.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4SubtractionSolid.hh"
#include "MocotoDetectorConstructionMessenger.hh"

MocotoDetectorConstruction::MocotoDetectorConstruction()
  :G4VUserDetectorConstruction()
{
  detnumber = 1;
  colnumber = 1;
  target_d  = 10.*cm;
  targetRotate = 0.*deg;
  m_copper  = 0.*mm;
  m_aluminum = 0.*mm;
  m_wolfram = 0.*mm;
  tubdetector = 0;
  position = G4ThreeVector(0,0,0);
  DefineMaterials();
  messenger = new MocotoDetectorConstructionMessenger(this);
}

MocotoDetectorConstruction::~MocotoDetectorConstruction()
{}

void MocotoDetectorConstruction::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();
  matWater = man->FindOrBuildMaterial("G4_WATER",false);
//  std::vector<G4String> Names = const_cast<std::vector<G4String>&>(man->GetNistMaterialNames());
//  std::vector<G4String>::iterator it;
//  for(it =Names.begin(); it!=Names.end(); it++)
//    G4cout << (*it) << " " << man->FindOrBuildMaterial(*it,false)->GetDensity()/matWater->GetDensity() << G4endl;
  G4bool isotopes = false;
  Galactic = new G4Material("Galactic", 1., 1.01*g/mole, universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);
  matAir = man->FindOrBuildMaterial("G4_AIR",isotopes);
  matIron = man->FindOrBuildMaterial("G4_Fe",isotopes);
  matWolfram = man->FindOrBuildMaterial("G4_W",isotopes);
  matCsI = man->FindOrBuildMaterial("G4_CESIUM_IODIDE",isotopes);
  matAl = man->FindOrBuildMaterial("G4_Al",isotopes);
  matCu = man->FindOrBuildMaterial("G4_Cu",isotopes);
  matTi = man->FindOrBuildMaterial("G4_Ti",isotopes);
  matPb = man->FindOrBuildMaterial("G4_Pb",isotopes);
  matPOLYETHYLENE = man->FindOrBuildMaterial("G4_POLYETHYLENE",isotopes);
  matBoneCompact = man->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU",isotopes);
  matBoneCortical = man->FindOrBuildMaterial("G4_BONE_CORTICAL_ICRP",isotopes);
  matBrain = man->FindOrBuildMaterial("G4_BRAIN_ICRP",isotopes);
}

G4VPhysicalVolume* MocotoDetectorConstruction::Construct()
{

  ////World Parameters
  G4double world_x = 2.0*m;
  G4double world_y = 2.0*m;
  G4double world_z = 2.0*m;

  solidWorld = new G4Box("sWorld", 0.5*world_x, 0.5*world_y, 0.5*world_z);
  logicWorld = new G4LogicalVolume(solidWorld, matAir, "lWorld");
  physiWorld = new G4PVPlacement(0,
                                 G4ThreeVector(0,0,0),
                  		 logicWorld,
                                 "pWorld",
                        	 0,
                        	 false,
                        	 999);
  //logicWorld->SetVisAttributes( G4VisAttributes::Invisible );

  G4RotationMatrix *rot = new G4RotationMatrix();
//  MocotoVolumeRCT* varian = new MocotoVolumeRCT();
//  varian->GetVolume(logicWorld,G4Transform3D(*rot,G4ThreeVector(19*cm+15.5/2*mm,0,0)));

  MocotoVolumeTarget* target = new MocotoVolumeTarget();
  rot = new G4RotationMatrix();
  rot->rotateZ(targetRotate);
  if( target_d != 0 )
    target->GetDiffSizeOfTarget( target_d, logicWorld);
  
  MakeDetectorVolume(detnumber);
  MakeCollimatorLogical(colnumber);

  return physiWorld;
}

//Detector
G4VPhysicalVolume* MocotoDetectorConstruction::MakeDetectorVolume(G4int N)
{
  G4double DetectorSizeX = 1.7*mm;
//  G4double DetectorSizeY = 25.784*mm;
  G4double DetectorSizeY = 25.614*mm;
  G4double DetectorSizeZ = 33.255*mm;
  G4double DetectorRadius = 440*mm + DetectorSizeX/2;
  G4double RotateDegree,tmpx,tmpy;
  G4RotationMatrix* rot;

//--------------------------------------------------------------------------------------------------
//   each detector is constructed by 24 rows  
  solidDetector = new G4Box("sDetector", DetectorSizeX*0.5, DetectorSizeY*0.5, DetectorSizeZ*0.5);
  logicDetector = new G4LogicalVolume(solidDetector, matAir, "lDetector");
  //============================================================
  //-----------------------21 detectors-------------------------
  G4int copyNo = 0;
  if( N==1 )
  {
    physiDetector = new G4PVPlacement(0,
	                              G4ThreeVector(DetectorRadius-24*cm, 0, 0),
				      logicDetector,
				      "pDetector",
				      logicWorld,
				      false,
				      copyNo);
    copyNo++;
  }

  else
  {
    for(G4int i=0; i<N; i++)
    {
      RotateDegree = (35-i*3.5)*deg;
      tmpx = DetectorRadius*cos(RotateDegree)-24*cm;
      tmpy = DetectorRadius*sin(RotateDegree);
      rot = new G4RotationMatrix();
      rot->rotateZ((-1)*RotateDegree);
      physiDetector = new G4PVPlacement(rot,
                                        G4ThreeVector(tmpx,tmpy,0),
        			              logicDetector,
        			              "pDetector",
        			              logicWorld,
        			              false,
        			              copyNo);
      copyNo++;
    }
  }
  MakeDetectorLinePhysical(logicDetector);

  //============================================================
  //----------------------Visualization-------------------------
  //G4VisAttributes* DetectorVisAtt = new G4VisAttributes( G4Colour(0., 0., 1.) );
  //DetectorVisAtt->SetForceSolid( true );
  //logicDetector->SetVisAttributes( DetectorVisAtt );
  logicDetector->SetVisAttributes( G4VisAttributes::Invisible );

  return physiDetector;
}
//......oooOO0OOooo......oooOO0OOooo......oooOO0OOooo......oooOO0OOooo......
G4VPhysicalVolume* MocotoDetectorConstruction::MakeDetectorLinePhysical(G4LogicalVolume* logicPlacement)
{
  G4double mdbby[24] = {12.36475*mm, 11.34000*mm, 10.26000*mm,  9.18000*mm,  8.10000*mm,  7.02000*mm,
                         5.94000*mm,  4.86000*mm,  3.78000*mm,  2.70000*mm,  1.62000*mm,  0.54000*mm,
			-0.54000*mm, -1.62000*mm, -2.70000*mm, -3.78000*mm, -4.86000*mm, -5.94000*mm,
			-7.02000*mm, -8.10000*mm, -9.18000*mm,-10.26000*mm,-11.34000*mm,-12.36475*mm };
  //G4Box* solidStrip = new G4Box("sStrip", 1.4*0.5*mm, 0.8845*0.5*mm, 33.085*0.5*mm);
  G4Box* solidStrip = new G4Box("sStrip", 1.4*0.5*mm, 0.8845*0.5*mm, 1.915*0.5*mm);
  G4LogicalVolume* logicStrip = new G4LogicalVolume(solidStrip, matCsI,"lStrip");
  G4VPhysicalVolume *physiStrip = new G4PVPlacement(0,
                                 G4ThreeVector(-0.15*mm,mdbby[0],0*mm),
        			 logicStrip,
        			 "pStrip",
        			 logicPlacement,
        			 false,
        			 0);
  
  physiStrip = new G4PVPlacement(0,
                                G4ThreeVector(-0.15*mm,mdbby[23],0*mm),
        			logicStrip,
        			"pStrip",
        			logicPlacement,
        			false,
        			23);
  G4VisAttributes* StripVisAtt = new G4VisAttributes( G4Colour(1., 1., 1.) );
  StripVisAtt->SetForceSolid(true);
  logicStrip->SetVisAttributes( StripVisAtt );
  //MakeDetectorRowPhysical(logicStrip,0.8845);

  //solidStrip = new G4Box("sStrip", 1.4*0.5*mm, 0.995*0.5*mm, 33.085*mm*0.5);
  solidStrip = new G4Box("sStrip", 1.4*0.5*mm, 0.995*0.5*mm, 1.915*mm*0.5);
  logicStrip = new G4LogicalVolume(solidStrip, matCsI, "lStrip");
  for(G4int i=1;i<23;i++)
  {
    physiStrip = new G4PVPlacement(0,
                                  G4ThreeVector(-0.15*mm,mdbby[i],0*mm),
        			  logicStrip,
        			  "pStrip",
        			  logicPlacement,
        			  false,
        			  i);
  }
  
  logicStrip->SetVisAttributes(StripVisAtt);
  //MakeDetectorRowPhysical(logicStrip,0.995);

  return physiStrip;
}
//......oooOO0OOooo......oooOO0OOooo......oooOO0OOooo......oooOO0OOooo......
G4VPhysicalVolume* MocotoDetectorConstruction::MakeDetectorRowPhysical(G4LogicalVolume* logicPlacement,G4double ysize)
{
  G4double mdbbz[24] = {15.0*mm, 13.0*mm, 11.0*mm,  9.0*mm,  7.5*mm,  6.5*mm,
                         5.5*mm,  4.5*mm,  3.5*mm,  2.5*mm,  1.5*mm,  0.5*mm,
			-0.5*mm, -1.5*mm, -2.5*mm, -3.5*mm, -4.5*mm, -5.5*mm,
			-6.5*mm, -7.5*mm, -9.0*mm,-11.0*mm,-13.0*mm,-15.0*mm };
  G4Box* solidCrystal = new G4Box("sCrystal", 1.4*0.5*mm, ysize*0.5*mm, 1.915*0.5*mm);
  G4LogicalVolume* logicCrystal = new G4LogicalVolume(solidCrystal, matCsI, "lCrystal");
  G4VPhysicalVolume* physiCrystal;
  for(G4int i=0;i<4;i++)
  {
    physiCrystal = new G4PVPlacement(0,
	                             G4ThreeVector(0,0,mdbbz[i]),
				     logicCrystal,
				     "pCrystal",
				     logicPlacement,
				     false,
				     i+1);
    physiCrystal = new G4PVPlacement(0,
	                             G4ThreeVector(0,0,mdbbz[23-i]),
				     logicCrystal,
				     "pCrystal",
				     logicPlacement,
				     false,
				     24-i);
  }
  
  G4VisAttributes *rowVisAtt = new G4VisAttributes( G4Colour(0.8, 0.8, 0.) );
  rowVisAtt->SetForceSolid( true );
  logicCrystal->SetVisAttributes( rowVisAtt );

  solidCrystal = new G4Box("sCrystal", 1.4*0.5*mm, ysize*0.5*mm, 0.5*0.5*mm);
  logicCrystal = new G4LogicalVolume(solidCrystal, matCsI, "lCrystal");
  physiCrystal = new G4PVPlacement(0,
                                   G4ThreeVector(0,0,16.2925*mm),
				   logicCrystal,
				   "pCrystal",
				   logicPlacement,
				   false,
				   0);
  physiCrystal = new G4PVPlacement(0,
                                   G4ThreeVector(0,0,-16.2925*mm),
				   logicCrystal,
				   "pCrystal",
				   logicPlacement,
				   false,
				   25);
  logicCrystal->SetVisAttributes( rowVisAtt );
  
  solidCrystal = new G4Box("sCrystal", 1.4*0.5*mm, ysize*0.5*mm, 0.915*0.5*mm);
  logicCrystal = new G4LogicalVolume(solidCrystal, matCsI, "lCrystal");
  for(G4int i=4;i<20;i++)
  {
    physiCrystal = new G4PVPlacement(0,
	                             G4ThreeVector(0,0,mdbbz[i]),
				     logicCrystal,
				     "pCrystal",
				     logicPlacement,
				     false,
				     i+1);
  }
  logicCrystal->SetVisAttributes( rowVisAtt );

  return physiCrystal;
}
//===========================================================================================
G4VPhysicalVolume* MocotoDetectorConstruction::MakeCollimatorLogical(G4int N)
{
  //===============
  //Collimator Size
  G4double coll_size_x = 12.*mm;
  G4double coll_size_y = 0.16*mm;
  G4double coll_size_z = 33.255*mm;
  G4double coll_tub_r_max = 440*mm;
  G4double coll_tub_r_min = (439.8-coll_size_x)*mm;
  G4double coll_cent_r = (coll_tub_r_max + coll_tub_r_min )/2;
  G4double rotate,tmpx,tmpy;
  G4RotationMatrix* rot;

  solidCollimatorTub = new G4Tubs("sCollimatorTub", coll_tub_r_min, coll_tub_r_max, coll_size_z*0.5, -1.7*deg, 3.4*deg);
  logicCollimatorTub = new G4LogicalVolume(solidCollimatorTub, matAir, "lCollimatorTub");
  solidCollimator = new G4Box("sCollimator", coll_size_x*0.5, coll_size_y*0.5, coll_size_z*0.5);
  logicCollimator = new G4LogicalVolume(solidCollimator, matWolfram, "lCollimator");
  for(G4int i=0;i<13;i++)
  {
    rotate = i*0.1403*deg;
    tmpx = coll_cent_r*cos(rotate);
    tmpy = coll_cent_r*sin(rotate);
    rot = new G4RotationMatrix();
    rot->rotateZ((-1)*rotate);
    physiCollimator = new G4PVPlacement(rot,
	              G4ThreeVector(tmpx,tmpy,0),
		      logicCollimator,
		      "pCollimator",
		      logicCollimatorTub,
		      false,
		      0);
    if( i!=0 )
    {
      rot = new G4RotationMatrix();
      rot->rotateZ(rotate);
      physiCollimator = new G4PVPlacement(rot,
	                G4ThreeVector(tmpx,-1*tmpy,0),
			logicCollimator,
			"pCollimator",
			logicCollimatorTub,
			false,
			0);
    }
  }

  if( N==1 )
  {
    physiDetector = new G4PVPlacement(0,
	                              G4ThreeVector(-24*cm, 0, 0),
				      logicCollimatorTub,
				      "pCollimatorTub",
				      logicWorld,
				      false,
				      0);
  }

  else
  {
    for(G4int i=0; i<N; i++)
    {
      rotate = (35-i*3.5)*deg;
      rot = new G4RotationMatrix();
      rot->rotateZ((-1)*rotate);
      physiDetector = new G4PVPlacement(rot,
                                        G4ThreeVector(-24*cm,0,0),
        			              logicCollimatorTub,
        			              "pCollimatorTub",
        			              logicWorld,
        			              false,
        			              0);
    }
  }

  G4VisAttributes* CollimatorVisAtt = new G4VisAttributes( G4Colour(1., 1., 0.) );
  CollimatorVisAtt->SetForceSolid( true );
  logicCollimator->SetVisAttributes( CollimatorVisAtt );

  G4VisAttributes* CollimatorTubVisAtt = new G4VisAttributes( G4Colour(1., 0., 0.) );
  logicCollimatorTub->SetVisAttributes( CollimatorTubVisAtt );
  return physiCollimatorTub;
}
