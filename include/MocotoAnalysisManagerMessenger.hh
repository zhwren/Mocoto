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
 * Last modified: 2015-07-27 11:15
 * Filename     : MocotoAnalysisManagerMessenger.hh
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/
#ifndef MocotoAnalysisManagerMessenger_h
#define MocotoAnalysisManagerMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class MocotoAnalysisManager;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;

class MocotoAnalysisManagerMessenger : public G4UImessenger
{
  public:
    MocotoAnalysisManagerMessenger(MocotoAnalysisManager*);
    ~MocotoAnalysisManagerMessenger();

    void SetNewValue(G4UIcommand*, G4String );

  private:
    MocotoAnalysisManager* histo;

    G4UIdirectory*         histoDir;
    G4UIcmdWithAString*    factoryCmd;
};

#endif
