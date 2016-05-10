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

G4VPhysicalVolume* MocotoVolumeTarget::GetPhantomVolume(G4LogicalVolume* motherVolume,G4Transform3D placement)
{
  solidTarget = new G4Tubs("sTarget", 0, 8.*cm, 15./2*cm, 0, 360.*deg);
  solidHolder = new G4Tubs("sHolder", 0, 1.3/2*cm, 15*cm, 0, 360.*deg);
  solidTarget = new G4SubtractionSolid("sTarget", solidTarget, solidHolder);
  G4RotationMatrix* rot = new G4RotationMatrix();
  solidTarget = new G4SubtractionSolid("sTarget", solidTarget, solidHolder, G4Transform3D(*rot, G4ThreeVector(6.5*cm,0,0)));
  solidTarget = new G4SubtractionSolid("sTarget", solidTarget, solidHolder, G4Transform3D(*rot, G4ThreeVector(-6.5*cm,0,0)));
  solidTarget = new G4SubtractionSolid("sTarget", solidTarget, solidHolder, G4Transform3D(*rot, G4ThreeVector(0,6.5*cm,0)));
  solidTarget = new G4SubtractionSolid("sTarget", solidTarget, solidHolder, G4Transform3D(*rot, G4ThreeVector(0,-6.5*cm,0)));
  
  logicTarget = new G4LogicalVolume(solidTarget, matWater, "lTarget");
  physiTarget = new G4PVPlacement(placement,
				  logicTarget,
				  "pTarget",
				  motherVolume,
				  false,
				  0);
  G4VisAttributes* VisAtt = new G4VisAttributes( G4Colour(0.5,0.5,0.5) );
  VisAtt->SetForceSolid( true );
  logicTarget->SetVisAttributes( VisAtt );

  return physiTarget;
}

G4VPhysicalVolume* MocotoVolumeTarget::GetDiffSizeOfTarget(G4int target_d, G4LogicalVolume* motherVolume)
{
  solidTarget = new G4Tubs("sHolder", 0, target_d/2, 15./2*cm, 0, 360.*deg);
  logicTarget = new G4LogicalVolume(solidTarget, matWater, "lTarget");
  physiTarget = new G4PVPlacement(0,
                                  G4ThreeVector(0,0,0),
  				  logicTarget,
  				  "pTarget",
  				  motherVolume,
  				  false,
  				  0);
  G4VisAttributes* VisAtt = new G4VisAttributes( G4Colour(0.5,0.5,0.5) );
  VisAtt->SetForceSolid( true );
  logicTarget->SetVisAttributes( VisAtt );

  return physiTarget;
}

G4VPhysicalVolume* MocotoVolumeTarget::GetTubsTarget(G4int rMin, G4int rMax, G4LogicalVolume* motherVolume)
{
  solidTarget = new G4Tubs("sTarget", rMin, rMax, 15./2*cm, -40*deg, 80.*deg);
  logicTarget = new G4LogicalVolume(solidTarget, matWater, "lTarget");
  physiTarget = new G4PVPlacement(0,
                                  G4ThreeVector(-240*mm,0,0),
				  logicTarget,
				  "pTarget",
				  motherVolume,
				  false,
				  0);
  G4VisAttributes* VisAtt = new G4VisAttributes( G4Colour(0,0,0.5) );
  VisAtt->SetForceSolid( true );
  logicTarget->SetVisAttributes( VisAtt );

  return physiTarget;
}
