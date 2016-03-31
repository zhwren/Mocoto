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
*    >  File Name   : MocotoRCTDetector.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-03-31 13:46                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MocotoRCTDetector_h
#define MocotoRCTDetector_h 1

#include "MocotoVolumeBase.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

class MocotoRCTDetector : public MocotoVolumeBase
{
  public:
    MocotoRCTDetector();
    ~MocotoRCTDetector();
    virtual G4VPhysicalVolume* GetVolume(G4LogicalVolume*,G4Transform3D);
};
#endif
