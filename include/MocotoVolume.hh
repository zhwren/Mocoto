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
*    >  File Name   : MocotoVolume.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 16:34                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MocotoVolume_h
#define MocotoVolume_h 1

#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4Transform3D.hh"
#include "MocotoDetectorSD.hh"
#include "G4SDManager.hh"
class G4Material;

class MocotoVolume
{
  protected:
    G4Material* matAl;
    G4Material* matIron;
    G4Material* matCsI;
    G4Material* matWater;
    G4Material* matAir;
    G4Material* matBlood;
    G4Material* matBrain;
    G4Material* matAdiposeTissue;
    G4Material* matAmber;
    G4Material* matBone;
    G4Material* matMuscle;
    G4Material* matWolfram;
    G4Material* matGOS;
    G4SDManager* SDman;
    MocotoDetectorSD* aDetectorSD;

  private:
    void DefineMaterials();

  public:
    MocotoVolume();
    ~MocotoVolume();

};

#endif
