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
*    >  File Name   : MocotoVolume.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 16:36                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "MocotoVolume.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

MocotoVolume::MocotoVolume()
{
  DefineMaterials();
}

MocotoVolume::~MocotoVolume()
{}

void MocotoVolume::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();
  G4bool isotopes = false;
  matCsI = man->FindOrBuildMaterial("G4_CESIUM_IODIDE",isotopes);
  matWater = man->FindOrBuildMaterial("G4_WATER",isotopes);
  matAir = man->FindOrBuildMaterial("G4_AIR",isotopes);
  matBlood = man->FindOrBuildMaterial("G4_BLOOD_ICRP",isotopes);
  matBrain = man->FindOrBuildMaterial("G4_BRAIN_ICRP",isotopes);
  matAdiposeTissue = man->FindOrBuildMaterial("G4_ADIPOSE_TISSUE_ICRP",isotopes);
  matAmber = man->FindOrBuildMaterial("G4_AMBER",isotopes);
  matBone = man->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU",isotopes);
  matMuscle = man->FindOrBuildMaterial("G4_MUSCLE_WITH_SUCROSE",isotopes);
  matWolfram = man->FindOrBuildMaterial("G4_W",isotopes);
}
