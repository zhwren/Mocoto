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
*    >  File Name   : VarianPaxScanDigitalImagerReceptor.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 14:06                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "VarianPaxScanDigitalImagerReceptor.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

VarianPaxScanDigitalImagerReceptor::VarianPaxScanDigitalImagerReceptor()
  :MocotoVolumeBase()
{}

VarianPaxScanDigitalImagerReceptor::~VarianPaxScanDigitalImagerReceptor()
{}


G4VPhysicalVolume* VarianPaxScanDigitalImagerReceptor::GetVolume(G4LogicalVolume* motherVolume,G4Transform3D placement)
{
  G4Box* solidVarian = new G4Box("sVarian", 15.5/2*mm, 279.09/2*mm, 337/2*mm);
  G4LogicalVolume* logicVarian = new G4LogicalVolume(solidVarian, matAir, "lVarian");
  G4VPhysicalVolume* physiVarian = new G4PVPlacement(placement,
						     logicVarian,
						     "pVarian",
						     motherVolume,
						     false,
						     0);
  logicVarian->SetVisAttributes( G4VisAttributes::Invisible );

  G4int MergedNumber = 4;
  G4Box* solidPixel = new G4Box("sPixel", 3.3/2*mm, 139./2*um*MergedNumber, 139./2*um*MergedNumber);
  G4LogicalVolume* logicPixel = new G4LogicalVolume(solidPixel, matCsI, "lPixel");
  G4VPhysicalVolume* physiPixel;
  G4double positionx = 3.3/2*mm - 15.5/2*mm;
  G4double positiony, positionz;
  G4int CopyNumber = 0;

  for(G4int iRow = 1; iRow < 5; iRow++)
  {
//    for(G4int iRow = 1; iRow < 2176/MergedNumber+1; iRow++)
    for(G4int iColumn = 1; iColumn < 1792/MergedNumber+1; iColumn++)
    {
      positiony = (1792/MergedNumber/2. - iColumn + 0.5) * 139.*um*MergedNumber;
      positionz = (2 - iRow + 0.5) * 139.*um*MergedNumber;
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

  return 0;
}

