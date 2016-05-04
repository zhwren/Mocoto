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
************************************************************
*    >  CopyRight   :                                      *
*    >  File Name   : MocotoVolumeMCT.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-04-25 10:14                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "MocotoVolumeMCT.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"

MocotoVolumeMCT::MocotoVolumeMCT()
  :MocotoVolume()
{
  ModuleSizeX = 1.7*mm;
  ModuleSizeY = 25.614*mm;
  ModuleSizeZ = 33.225*mm;
  ModuleRadius = 440*mm + ModuleSizeX/2;
  CollimatorSizeX = 12.*mm;
  CollimatorSizeY = 0.16*mm;
  CollimatorSizeZ = 33.225*mm;
}

MocotoVolumeMCT::~MocotoVolumeMCT()
{}

G4VPhysicalVolume* MocotoVolumeMCT::GetModuleVolume(G4LogicalVolume* motherVolume,G4int nModule)
{
  solidModule = new G4Box("sModule", ModuleSizeX/2, ModuleSizeY/2, ModuleSizeZ/2);
  logicModule = new G4LogicalVolume(solidModule, matAir, "lModule");
  if( nModule == 1 )
  {
    physiModule = new G4PVPlacement(0,
	                            G4ThreeVector(ModuleRadius-24*cm, 0, 0),
				    logicModule,
				    "pModule",
				    motherVolume,
				    false,
				    0);
  }
  else
  {
    for(G4int i=0; i<nModule; i++)
    {
      rotateAngle = (35-i*3.5)*deg;
      G4double tmpx = ModuleRadius*cos(rotateAngle)-24*cm;
      G4double tmpy = ModuleRadius*sin(rotateAngle);
      rotate = new G4RotationMatrix();
      rotate->rotateZ(-1*rotateAngle);
      physiModule = new G4PVPlacement(rotate,
	                              G4ThreeVector(tmpx, tmpy, 0),
				      logicModule,
				      "pModule",
				      motherVolume,
				      false,
				      i);
    }
  }
 
  GetModuleRowDetail();
  return physiModule;
}

G4VPhysicalVolume* MocotoVolumeMCT::GetModuleRowDetail()
{
  solidRowDetail = new G4Box("sRowDetail", 1.4/2*mm, ModuleSizeY/2, 1.915/2*mm);
  logicRowDetail = new G4LogicalVolume(solidRowDetail, matAir, "lRowDetail");
  for(G4int i=8; i<9; i++)
  {
    physiRowDetail = new G4PVPlacement(0,
	                               G4ThreeVector(-0.15*mm, 0, (15-i*2)*mm),
				       logicRowDetail,
				       "pRowDetail",
				       logicModule,
				       false,
				       i);
  }

  GetModuleColumnDetail();
  return physiRowDetail;
}

G4VPhysicalVolume* MocotoVolumeMCT::GetModuleColumnDetail()
{
  G4double detaily[24] = {12.36475*mm, 11.34000*mm, 10.26000*mm,  9.18000*mm,  8.10000*mm,  7.02000*mm,
                           5.94000*mm,  4.86000*mm,  3.78000*mm,  2.70000*mm,  1.62000*mm,  0.54000*mm,
		  	  -0.54000*mm, -1.62000*mm, -2.70000*mm, -3.78000*mm, -4.86000*mm, -5.94000*mm,
		  	  -7.02000*mm, -8.10000*mm, -9.18000*mm,-10.26000*mm,-11.34000*mm,-12.36475*mm };

  solidColumnDetail = new G4Box("sColumnDetail", 1.4/2*mm, 0.8845/2*mm, 1.915/2*mm);
  logicColumnDetail = new G4LogicalVolume(solidColumnDetail, matGOS, "lColumnDetail");
  physiColumnDetail = new G4PVPlacement(0,
                                        G4ThreeVector(0, detaily[0], 0),
					logicColumnDetail,
					"pColumnDetail",
					logicRowDetail,
					false,
					0);
  physiColumnDetail = new G4PVPlacement(0,
                                        G4ThreeVector(0, detaily[23], 0),
					logicColumnDetail,
					"pColumnDetail",
					logicRowDetail,
					false,
					23);
  G4VisAttributes* vis = new G4VisAttributes( G4Colour(1,0,0) );
  vis->SetForceSolid( true );
  logicColumnDetail->SetVisAttributes( vis );

  solidColumnDetail = new G4Box("sColumnDetail", 1.4/2*mm, 0.995/2*mm, 1.915/2*mm);
  logicColumnDetail = new G4LogicalVolume(solidColumnDetail, matGOS, "lColumnDetail");
  logicColumnDetail->SetVisAttributes( vis );
  for(G4int i=1; i<23; i++)
  {
    physiColumnDetail = new G4PVPlacement(0,
	                                  G4ThreeVector(0,detaily[i],0),
					  logicColumnDetail,
					  "pColumnDetail",
					  logicRowDetail,
					  false,
					  i);
  }
  return physiColumnDetail;
}

G4VPhysicalVolume* MocotoVolumeMCT::GetCollimatorVolume(G4LogicalVolume* motherVolume,G4int nCollimator)
{
  G4double rMax = 440*mm;
  G4double rMin = (439.8-CollimatorSizeX)*mm;
  CollimatorCentral = (rMax + rMin)/2;
  solidCollimatorTub = new G4Tubs("sCollimatorTub", rMin, rMax, CollimatorSizeZ*0.5, -1.7*deg, 3.4*deg);
  logicCollimatorTub = new G4LogicalVolume(solidCollimatorTub, matAir, "lCollimatorTub");
  if( nCollimator==1 )
  {
    physiCollimatorTub = new G4PVPlacement(0,
	                                   G4ThreeVector(-24*cm, 0, 0),
				           logicCollimatorTub,
				           "pCollimatorTub",
				           motherVolume,
				           false,
				           0);
  }
  else
  {
    for(G4int i=0; i<nCollimator; i++)
    {
      rotateAngle = (35-i*3.5)*deg;
      rotate = new G4RotationMatrix();
      rotate->rotateZ(-1*rotateAngle);
      physiCollimatorTub = new G4PVPlacement(rotate,
	                                     G4ThreeVector(-24*cm,0,0),
					     logicCollimatorTub,
					     "pCollimatorTub",
					     motherVolume,
					     false,
					     0);
    }
  }
  logicCollimatorTub->SetVisAttributes( G4VisAttributes::Invisible );

  GetCollimatorSheets();
  return physiCollimatorTub;
}

G4VPhysicalVolume* MocotoVolumeMCT::GetCollimatorSheets()
{
  solidCollimator = new G4Box("sCollimator", CollimatorSizeX/2, CollimatorSizeY/2, CollimatorSizeZ/2);
  logicCollimator = new G4LogicalVolume(solidCollimator, matWolfram, "lCollimator");
  G4double tmpx, tmpy;
  for(G4int i=0; i<13; i++)
  {
    rotateAngle = i*0.1403*deg;
    tmpx = CollimatorCentral*cos(rotateAngle);
    tmpy = CollimatorCentral*sin(rotateAngle);
    rotate = new G4RotationMatrix();
    rotate->rotateZ((-1)*rotateAngle);
    physiCollimator = new G4PVPlacement(rotate,
	                                G4ThreeVector(tmpx, tmpy, 0),
					logicCollimator,
					"pCollimator",
					logicCollimatorTub,
					false,
					0);
    if( i != 0 )
    {
      rotate = new G4RotationMatrix();
      rotate->rotateZ(rotateAngle);
      physiCollimator = new G4PVPlacement(rotate,
	                                  G4ThreeVector(tmpx, -1*tmpy, 0),
					  logicCollimator,
					  "pCollimator",
					  logicCollimatorTub,
					  false,
					  0);
    }
  }
  G4VisAttributes* vis = new G4VisAttributes(G4Colour(0.3,0.3,0));
  vis->SetForceSolid( true );
  logicCollimator->SetVisAttributes( vis );
  return physiCollimator;
}

G4VPhysicalVolume* MocotoVolumeMCT::GetComptSheets(G4LogicalVolume* motherVolume)
{
  G4double mComptSheetRadius = 440.85*mm;

  solidComptSheet = new G4Box("sComptSheet", 0.7*mm, 0.55*mm, 1.915/2*mm);
  logicComptSheet = new G4LogicalVolume(solidComptSheet, matGOS, "lComptSheet");
  for(G4int i=0; i<20; i++)
  {
    rotateAngle = (33.25-i*3.5)*deg;
    rotate = new G4RotationMatrix();
    rotate->rotateZ(-1*rotateAngle);
    G4double tmpx = mComptSheetRadius*cos(rotateAngle)-24*cm;
    G4double tmpy = mComptSheetRadius*sin(rotateAngle);
    physiComptSheet = new G4PVPlacement(rotate,
	                                G4ThreeVector(tmpx, tmpy, -1*mm),
					logicComptSheet,
					"pComptSheet",
					motherVolume,
					false,
					0);
  }

  G4VisAttributes* vis = new G4VisAttributes(G4Colour(0,1,0));
  vis->SetForceSolid( true );
  logicComptSheet->SetVisAttributes(vis);

  return physiComptSheet;
}

G4VPhysicalVolume* MocotoVolumeMCT::GetTubsDetector(G4LogicalVolume* motherVolume)
{
  solidRowDetail = new G4Tubs("sRowDetail", 440*mm, 441.4*mm, 1.915/2*mm, -36.5*deg, 73*deg);
  logicRowDetail = new G4LogicalVolume(solidRowDetail, matGOS, "lRowDetail");
  physiRowDetail = new G4PVPlacement(0,
                                     G4ThreeVector(-24*cm,0,-1*mm),
				     logicRowDetail,
				     "pRowDetail",
				     motherVolume,
				     false,
				     0);

  G4VisAttributes* vis = new G4VisAttributes( G4Colour(1,0,0) );
  vis->SetForceSolid( true );
  logicRowDetail->SetVisAttributes( vis );
  return physiRowDetail;
}
