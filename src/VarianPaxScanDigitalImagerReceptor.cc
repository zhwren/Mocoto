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
#include "G4Material.hh"
#include "G4NistManager.hh"

VarianPaxScanDigitalImagerReceptor::VarianPaxScanDigitalImagerReceptor()
{
  DefineMaterials();
}

VarianPaxScanDigitalImagerReceptor::~VarianPaxScanDigitalImagerReceptor()
{}

void VarianPaxScanDigitalImagerReceptor::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();
  G4bool isotopes = false;
  matCsI = man->FindOrBuildMaterial("G4_CESIUM_IODIDE",isotopes);
}

G4VPhysicalVolume* VarianPaxScanDigitalImagerReceptor::GetVolume()
{
  return 0;
}

