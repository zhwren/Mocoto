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
*    >  File Name   : MocotoVolumeTarget.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 16:46                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "MocotoVolumeTarget.hh"

#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"

MocotoVolumeTarget::MocotoVolumeTarget()
  :MocotoVolume()
{}

MocotoVolumeTarget::~MocotoVolumeTarget()
{}

G4VPhysicalVolume* MocotoVolumeTarget::GetVolume(G4LogicalVolume* motherVolume, G4Transform3D placement)
{}

G4VPhysicalVolume* MocotoVolumeTarget::GetPhantomVolume(G4LogicalVolume* motherVolume,G4Transform3D placement)
{
  G4VSolid* solidHolder = new G4Tubs("sHolder", 0, 8.*cm, 15./2*cm, 0, 360.*deg);
  G4VSolid* solidTarget = new G4Tubs("sTarget", 0, 1.3/2*cm, 15*cm, 0, 360.*deg);
  solidHolder = new G4SubtractionSolid("sHolder", solidHolder, solidTarget);
  G4RotationMatrix* rot = new G4RotationMatrix();
  solidHolder = new G4SubtractionSolid("sHolder", solidHolder, solidTarget, G4Transform3D(*rot, G4ThreeVector(6.5*cm,0,0)));
  solidHolder = new G4SubtractionSolid("sHolder", solidHolder, solidTarget, G4Transform3D(*rot, G4ThreeVector(-6.5*cm,0,0)));
  solidHolder = new G4SubtractionSolid("sHolder", solidHolder, solidTarget, G4Transform3D(*rot, G4ThreeVector(0,6.5*cm,0)));
  solidHolder = new G4SubtractionSolid("sHolder", solidHolder, solidTarget, G4Transform3D(*rot, G4ThreeVector(0,-6.5*cm,0)));
  
  G4LogicalVolume* logicHolder = new G4LogicalVolume(solidHolder, matWater, "lHolder");
  G4VPhysicalVolume* physiHolder = new G4PVPlacement(placement,
						     logicHolder,
						     "pHolder",
						     motherVolume,
						     false,
						     0);
  G4VisAttributes* VisAtt = new G4VisAttributes( G4Colour(0.5,0.5,0.5) );
  VisAtt->SetForceSolid( true );
  logicHolder->SetVisAttributes( VisAtt );

}
