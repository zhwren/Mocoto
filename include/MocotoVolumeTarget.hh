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
*    >  File Name   : MocotoVolumeTarget.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 16:44                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MocotoVolumeTarget_h
#define MocotoVolumeTarget_h 1

#include "MocotoVolume.hh"

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;

class MocotoVolumeTarget : public MocotoVolume
{
  public:
    MocotoVolumeTarget();
    ~MocotoVolumeTarget();

  public:
    G4VPhysicalVolume* GetPhantomVolume(G4LogicalVolume*,G4Transform3D);
    G4VPhysicalVolume* GetDiffSizeOfTarget(G4int,G4LogicalVolume*);
    G4VPhysicalVolume* GetTubsTarget(G4int,G4int,G4LogicalVolume*);

  private:
    G4VSolid*          solidHolder;
    G4VSolid*          solidTarget;
    G4LogicalVolume*   logicTarget;
    G4VPhysicalVolume* physiTarget;

};

#endif
