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
 * Last modified: 2015-08-28 10:49:1440730169
 * Filename     : MocotoPrimaryGeneratorMessenger.hh
 * Phone Number : 18625272373                               *
 * Discription  :                                           *
 ***********************************************************/
#ifndef MocotoPrimaryGeneratorMessenger_h
#define MocotoPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class MocotoPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithADoubleAndUnit;

class MocotoPrimaryGeneratorMessenger : public G4UImessenger
{
  public:
    MocotoPrimaryGeneratorMessenger(MocotoPrimaryGeneratorAction*);
    ~MocotoPrimaryGeneratorMessenger();

    void SetNewValue(G4UIcommand*, G4String);
  private:
    MocotoPrimaryGeneratorAction* gen;
    G4UIdirectory*                genDir;
    G4UIcmdWithADoubleAndUnit*    genEnergy;
    G4UIcmdWith3VectorAndUnit*    genThetaPhi;
    G4UIcmdWithAString*           genParticle;
    G4UIcmdWith3VectorAndUnit*    genPosition;
    G4UIcmdWith3VectorAndUnit*    genDeltaThetaPhi;
};
#endif
