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
*    >  CopyRight   :                                      *
*    >  File Name   : MocotoVolumeMCT.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-04-25 10:13                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MocotoVolumeMCT_h
#define MocotoVolumeMCT_h 1

#include "MocotoVolume.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;

class MocotoVolumeMCT : public MocotoVolume
{
  public:
    MocotoVolumeMCT();
    ~MocotoVolumeMCT();

  public:
    G4VPhysicalVolume* GetVolume(G4LogicalVolume*,G4int nModule=1);

  private:
    G4VPhysicalVolume* GetRowDetail();
    G4VPhysicalVolume* GetColumnDetail();

  private:
    G4Box*             solidModule;
    G4LogicalVolume*   logicModule;
    G4VPhysicalVolume* physiModule;

    G4Box*             solidRowDetail1;
    G4LogicalVolume*   logicRowDetail1;
    G4VPhysicalVolume* physiRowDetail1;

    G4Box*             solidRowDetail2;
    G4LogicalVolume*   logicRowDetail2;
    G4VPhysicalVolume* physiRowDetail2;

    G4Box*             solidColumnDetail;
    G4LogicalVolume*   logicColumnDetail;
    G4VPhysicalVolume* physiColumnDetail;

};
#endif
