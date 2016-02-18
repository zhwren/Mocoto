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
*    >  File Name   : MocotoVolumeBase.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 16:36                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "MocotoVolumeBase.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

MocotoVolumeBase::MocotoVolumeBase()
{
  DefineMaterials();
}

MocotoVolumeBase::~MocotoVolumeBase()
{}

void MocotoVolumeBase::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();
  G4bool isotopes = false;
  matCsI = man->FindOrBuildMaterial("G4_CESIUM_IODIDE",isotopes);
  matWater = man->FindOrBuildMaterial("G4_WATER",isotopes);
  matAir = man->FindOrBuildMaterial("G4_AIR",isotopes);
  matBlood = man->FindOrBuildMaterial("G4_BLOOD_ICRP",isotopes);
}
