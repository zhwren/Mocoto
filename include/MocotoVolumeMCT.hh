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
class G4Tubs;
class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;

class MocotoVolumeMCT : public MocotoVolume
{
  public:
    MocotoVolumeMCT();
    ~MocotoVolumeMCT();

  public:
    G4VPhysicalVolume* GetModuleVolume(G4LogicalVolume*,G4int nModule=1);
    G4VPhysicalVolume* GetCollimatorVolume(G4LogicalVolume*,G4int nCollimator=1);
    G4VPhysicalVolume* GetComptSheets(G4LogicalVolume*);
    G4VPhysicalVolume* GetTubsDetector(G4LogicalVolume*);

  private:
    G4VPhysicalVolume* GetModuleRowDetail();
    G4VPhysicalVolume* GetModuleColumnDetail();
    G4VPhysicalVolume* GetCollimatorSheets();

  private:
    G4Box*             solidModule;
    G4LogicalVolume*   logicModule;
    G4VPhysicalVolume* physiModule;

    G4VSolid*          solidRowDetail;
    G4LogicalVolume*   logicRowDetail;
    G4VPhysicalVolume* physiRowDetail;

    G4Box*             solidColumnDetail;
    G4LogicalVolume*   logicColumnDetail;
    G4VPhysicalVolume* physiColumnDetail;

    G4Tubs*            solidCollimatorTub;
    G4LogicalVolume*   logicCollimatorTub;
    G4VPhysicalVolume* physiCollimatorTub;

    G4Box*             solidCollimator;
    G4LogicalVolume*   logicCollimator;
    G4VPhysicalVolume* physiCollimator;

    G4Box*             solidComptSheet;
    G4LogicalVolume*   logicComptSheet;
    G4VPhysicalVolume* physiComptSheet;

  private:
    G4double ModuleSizeX;
    G4double ModuleSizeY;
    G4double ModuleSizeZ;
    G4double ModuleRadius;
    G4double CollimatorSizeX;
    G4double CollimatorSizeY;
    G4double CollimatorSizeZ;
    G4double CollimatorCentral;
    G4double rotateAngle;
    G4RotationMatrix* rotate;
};
#endif
