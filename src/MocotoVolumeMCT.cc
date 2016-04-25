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
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

MocotoVolumeMCT::MocotoVolumeMCT()
  :MocotoVolume()
{}

MocotoVolumeMCT::~MocotoVolumeMCT()
{}

G4VPhysicalVolume* MocotoVolumeMCT::GetVolume(G4LogicalVolume* motherVolume,G4int nModule)
{
  G4double ModuleSizeX = 1.7*mm;
  G4double ModuleSizeY = 25.614*mm;
  G4double ModuleSizeZ = 33.225*mm;
  G4double ModuleRadius = 440*mm + ModuleSizeX/2;

  solidModule = new G4Box("sModule", ModuleSizeX/2, ModuleSizeY/2, ModuleSizeZ/2);
  logicModule = new G4LogicalVolume(solidModule, matAir, "lModule");
  G4int copyNO = 0;
  if( nModule == 1 )
  {
    physiModule = new G4PVPlacement(0,
	                            G4ThreeVector(ModuleRadius-24*cm, 0, 0),
				    logicModule,
				    "pModule",
				    motherVolume,
				    false,
				    copyNO);
  }

  GetRowDetail();
  return physiModule;
}

G4VPhysicalVolume* MocotoVolumeMCT::GetRowDetail()
{
  G4double detaily[24] = {12.36475*mm, 11.34000*mm, 10.26000*mm,  9.18000*mm,  8.10000*mm,  7.02000*mm,
                           5.94000*mm,  4.86000*mm,  3.78000*mm,  2.70000*mm,  1.62000*mm,  0.54000*mm,
			  -0.54000*mm, -1.62000*mm, -2.70000*mm, -3.78000*mm, -4.86000*mm, -5.94000*mm,
			  -7.02000*mm, -8.10000*mm, -9.18000*mm,-10.26000*mm,-11.34000*mm,-12.36475*mm };

  solidRowDetail1 = new G4Box("sRowDetail", 1.4/2*mm, 0.8845/2*mm, 33.085/2*mm);
  logicRowDetail1 = new G4LogicalVolume(solidRowDetail1, matAir, "lRowDetail");
  physiRowDetail1 = new G4PVPlacement(0,
                                     G4ThreeVector(-0.15*mm, detaily[0], 0),
				     logicRowDetail1,
				     "pRowDetail",
				     logicModule,
				     false,
				     0);

  solidRowDetail2 = new G4Box("sRowDetail", 1.4/2*mm, 0.995/2*mm, 33.085/2*mm);
  logicRowDetail2 = new G4LogicalVolume( solidRowDetail2, matAir, "lRowDetail");
  for(G4int i=1; i<23; i++)
  {
    physiRowDetail2 = new G4PVPlacement(0,
	                                G4ThreeVector(-0.15*mm, detaily[i], 0),
					logicRowDetail2,
					"pRowDetail",
					logicModule,
					false,
					i);
  }

  physiRowDetail1 = new G4PVPlacement(0,
                                     G4ThreeVector(-0.15*mm, detaily[23], 0),
				     logicRowDetail1,
				     "pRowDetail",
				     logicModule,
				     false,
				     23);

  G4VisAttributes* vis = new G4VisAttributes( G4Colour(1.,0.,0.) );
  logicRowDetail1->SetVisAttributes( vis );
  logicRowDetail2->SetVisAttributes( vis );

  GetColumnDetail();
  return physiRowDetail1;
}

G4VPhysicalVolume* MocotoVolumeMCT::GetColumnDetail()
{
  G4double detailz[16] = { 15.0*mm, 13.0*mm, 11.0*mm, 9.0*mm, 7.0*mm, 5.0*mm, 3.0*mm, 1.0*mm,
                           -1.0*mm, -3.0*mm, -5.0*mm, -7.0*mm, -9.0*mm, -11.0*mm, -13.0*mm, -15.0*mm };

  solidColumnDetail = new G4Box("sColumnDetail", 1.4/2*mm, 0.8845/2*mm, 1.915/2*mm);
  logicColumnDetail = new G4LogicalVolume(solidColumnDetail, matAir, "lColumnDetail");
  for(G4int i=0; i<16; i++)
  {
    physiColumnDetail = new G4PVPlacement(0,
	                                  G4ThreeVector(0, 0, (15-2*i)*mm),
					  logicColumnDetail,
					  "pColumnDetail",
					  logicRowDetail1,
					  false,
					  i);
  }

  solidColumnDetail = new G4Box("sColumnDetail", 1.4/2*mm, 0.995/2*mm, 1.915/2*mm);
  logicColumnDetail = new G4LogicalVolume(solidColumnDetail, matAir, "lColumnDetail");
  for(G4int i=0; i<16; i++)
  {
    physiColumnDetail = new G4PVPlacement(0,
	                                  G4ThreeVector(0, 0, (15-2*i)*mm),
					  logicColumnDetail,
					  "pColumnDetail",
					  logicRowDetail2,
					  false,
					  i);
  }

  return physiColumnDetail;
}
