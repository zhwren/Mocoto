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
*    >  File Name   : VarianPaxScanDigitalImagerReceptor.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 14:01                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef VarianPaxScanDigitalImagerReceptor_h
#define VarianPaxScanDigitalImagerReceptor_h 1

#include "MocotoVolumeBase.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

class VarianPaxScanDigitalImagerReceptor : public MocotoVolumeBase
{
  public:
    VarianPaxScanDigitalImagerReceptor();
    ~VarianPaxScanDigitalImagerReceptor();
    virtual G4VPhysicalVolume* GetVolume(G4LogicalVolume*,G4Transform3D);
};
#endif
