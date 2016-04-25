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
*    >  File Name   : MocotoVolumeRCT.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 14:06                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "MocotoVolumeRCT.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

MocotoVolumeRCT::MocotoVolumeRCT()
  :MocotoVolume()
{}

MocotoVolumeRCT::~MocotoVolumeRCT()
{}


G4VPhysicalVolume* MocotoVolumeRCT::GetVolume(G4LogicalVolume* motherVolume)
{
  G4RotationMatrix* rot = new G4RotationMatrix();
  G4Transform3D placement = G4Transform3D(*rot, G4ThreeVector(19*cm+15.5/2*mm, 0, 0));

  solidVarian = new G4Box("sVarian", 15.5/2*mm, 279.09/2*mm, 337/2*mm);
  logicVarian = new G4LogicalVolume(solidVarian, matAir, "lVarian");
  physiVarian = new G4PVPlacement(placement,
				  logicVarian,
				  "pVarian",
				  motherVolume,
				  false,
				  0);
  logicVarian->SetVisAttributes( G4VisAttributes::Invisible );

  G4int MergedNumber = 4;
  solidPixel = new G4Box("sPixel", 3.3/2*mm, 139./2*um*MergedNumber, 139./2*um*MergedNumber);
  logicPixel = new G4LogicalVolume(solidPixel, matCsI, "lPixel");
  
  G4double positionx = 3.3/2*mm - 15.5/2*mm;
  G4double positiony, positionz;
  G4int CopyNumber = 0;
//  G4int nRows = 2172/MergedNumber;
  G4int nRows = 10;

  for(G4int iRow = 1; iRow < nRows+1; iRow++)
  {
    for(G4int iColumn = 1; iColumn < 1792/MergedNumber+1; iColumn++)
    {
      positiony = (1792/MergedNumber/2. - iColumn + 0.5) * 139.*um*MergedNumber;
      positionz = (nRows/2 - iRow + 0.5) * 139.*um*MergedNumber;
      physiPixel = new G4PVPlacement(0,
	                             G4ThreeVector(positionx, positiony, positionz),
				     logicPixel,
				     "pPixel",
				     logicVarian,
				     false,
				     CopyNumber++);
    }
  }
  G4cout << CopyNumber << G4endl;

  return physiVarian;
}

