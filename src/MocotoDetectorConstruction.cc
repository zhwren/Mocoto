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
#include "MocotoVolumeMCT.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
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
#include "MocotoDetectorConstructionMessenger.hh"
#include "MocotoDetectorSD.hh"

MocotoDetectorConstruction::MocotoDetectorConstruction()
  :G4VUserDetectorConstruction()
{
  detnumber = 1;
  colnumber = 1;
  target_d  = 10.*cm;
  targetRotate = 0.*deg;
  position = G4ThreeVector(0,0,0);
  messenger = new MocotoDetectorConstructionMessenger(this);
}

MocotoDetectorConstruction::~MocotoDetectorConstruction()
{}

G4VPhysicalVolume* MocotoDetectorConstruction::Construct()
{
  G4double world_x = 2.0*m;
  G4double world_y = 2.0*m;
  G4double world_z = 2.0*m;

  G4bool isotopes = false;
  G4NistManager* man = G4NistManager::Instance();
  G4Material* matAir = man->FindOrBuildMaterial("G4_AIR",isotopes);
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
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  MocotoDetectorSD* aDetectorSD = MocotoDetectorSD::getInstance();
  SDman->AddNewDetector( aDetectorSD );
  logicWorld->SetSensitiveDetector( aDetectorSD );

  G4RotationMatrix *rotate = new G4RotationMatrix();
  MocotoVolumeTarget* target = new MocotoVolumeTarget();
  rotate->rotateZ(targetRotate);
  if( target_d != 0 ) target->GetDiffSizeOfTarget( target_d, logicWorld );
  
  MocotoVolumeMCT* mctdet = new MocotoVolumeMCT();
  mctdet->GetModuleVolume(logicWorld,detnumber);
  mctdet->GetCollimatorVolume(logicWorld,colnumber);

  return physiWorld;
}
