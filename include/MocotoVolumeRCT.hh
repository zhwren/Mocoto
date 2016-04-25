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
*    >  File Name   : MocotoVolumeRCT.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-03-31 13:46                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MocotoVolumeRCT_h
#define MocotoVolumeRCT_h 1

#include "MocotoVolume.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4Box;

class MocotoVolumeRCT : public MocotoVolume
{
  public:
    MocotoVolumeRCT();
    ~MocotoVolumeRCT();

  public:
    G4VPhysicalVolume* GetVolume(G4LogicalVolume*);

  private:
    G4Box*             solidVarian;
    G4LogicalVolume*   logicVarian;
    G4VPhysicalVolume* physiVarian;

    G4Box*             solidPixel;
    G4LogicalVolume*   logicPixel;
    G4VPhysicalVolume* physiPixel;
};
#endif
