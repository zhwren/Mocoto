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
*    >  File Name   : MocotoTarget.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 16:46                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "MocotoTarget.hh"
#include "MocotoTargetMessenger.hh"

#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

MocotoTarget::MocotoTarget()
  :MocotoVolumeBase()
{
  messenger = new MocotoTargetMessenger(this);
}

MocotoTarget::~MocotoTarget()
{}

G4VPhysicalVolume* MocotoTarget::GetVolume(G4LogicalVolume* motherVolume)
{
  G4Tubs* solidHolder = new G4Tubs("sHolder", 0, 10.*cm, 5.*cm, 0, 360.*deg);
  G4LogicalVolume* logicHolder = new G4LogicalVolume(solidHolder, matWater, "lHolder");
  G4VPhysicalVolume* physiHolder = new G4PVPlacement(0,
                                                     G4ThreeVector(0,0,0),
						     logicHolder,
						     "pHolder",
						     motherVolume,
						     false,
						     0);
  G4VisAttributes* VisAtt = new G4VisAttributes( G4Colour(1., 0., 0.) );
  logicHolder->SetVisAttributes( VisAtt );

  G4Tubs* solidTarget = new G4Tubs("sTarget", 0, 5.*mm, 2.*cm, 0, 360.*deg);
  G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, matWater, "lTarget");
  G4VPhysicalVolume* physiTarget = new G4PVPlacement(0,
                                                     G4ThreeVector(-5*cm,0,0),
						     logicTarget,
						     "pTarget",
						     logicHolder,
						     false,
						     0);
  VisAtt = new G4VisAttributes( G4Colour(0., 1., 0.) );
  VisAtt->SetForceSolid( true );
  logicTarget->SetVisAttributes( VisAtt );

  logicTarget = new G4LogicalVolume(solidTarget, matWater, "lTarget");
  physiTarget = new G4PVPlacement(0,
                                  G4ThreeVector(5*cm,0,0),
				  logicTarget,
				  "pTarget",
				  logicHolder,
				  false,
				  0);
  VisAtt = new G4VisAttributes( G4Colour(0., 0., 1.) );
  logicTarget->SetVisAttributes( VisAtt );

  logicTarget = new G4LogicalVolume(solidTarget, matWater, "lTarget");
  physiTarget = new G4PVPlacement(0,
                                  G4ThreeVector(0,5*cm,0),
				  logicTarget,
				  "pTarget",
				  logicHolder,
				  false,
				  0);
  VisAtt = new G4VisAttributes( G4Colour(1., 0., 1.) );
  logicTarget->SetVisAttributes( VisAtt );

  return 0;
}
