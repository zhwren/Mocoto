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
 *                                                          *
 ************************************************************
 * Author       : ZhuHaiWen                                 *
 * Email        : zhuhw@ihep.ac.cn/zhwren0211@whu.edu.cn    *
 * Last modified: 2015-07-14 09:46
 * Filename     : MocotoDetectorConstruction.hh
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/

#ifndef MocotoDetectorConstruction_h
#define MocotoDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "TString.h"
#include "G4ThreeVector.hh"
using namespace std;

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Box;
class MocotoDetectorConstructionMessenger;

class MocotoDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MocotoDetectorConstruction();
    virtual ~MocotoDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

  private:
    G4Box*             solidWorld;
    G4LogicalVolume*   logicWorld;
    G4VPhysicalVolume* physiWorld;

  public:
    void SetDetNumber(TString i) { detnumber = std::atoi(i); }
    void SetColNumber(TString i) { colnumber = std::atoi(i); }
    void SetTargetDiameter(G4double i) { target_d = i; }
    void SetTargetRotateAngle(G4double i) { targetRotate = i; }
    void SetTargetPosition(G4ThreeVector pos) { position = pos; }
  private:
    G4int detnumber;
    G4int colnumber;
    G4int tubdetector;
    G4int target_d;
    G4double targetRotate;
    G4ThreeVector position;
    MocotoDetectorConstructionMessenger* messenger;
};

#endif
