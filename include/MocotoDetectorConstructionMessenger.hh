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
 * Last modified: 2015-07-28 15:31
 * Filename     : MocotoDetectorConstructionMessenger.hh
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/
#ifndef MocotoDetectorConstructionMessenger_h
#define MocotoDetectorConstructionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class MocotoDetectorConstruction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;

class MocotoDetectorConstructionMessenger : public G4UImessenger
{
  public:
    MocotoDetectorConstructionMessenger(MocotoDetectorConstruction*);
    ~MocotoDetectorConstructionMessenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    MocotoDetectorConstruction* det;
    G4UIdirectory*              detDir;
    G4UIcmdWithAnInteger*       detNumber;
    G4UIcmdWithAnInteger*       colnumber;
    G4UIcmdWithADoubleAndUnit*  target_d;
    G4UIcmdWithADoubleAndUnit*  targetRot;
    G4UIcmdWith3VectorAndUnit*  targetPosition;
};
#endif
