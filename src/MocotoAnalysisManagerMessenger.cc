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
 * Last modified: 2015-07-27 11:20
 * Filename     : MocotoAnalysisManagerMessenger.cc
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/
#include "MocotoAnalysisManagerMessenger.hh"
#include <sstream>
#include "MocotoAnalysisManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAnInteger.hh"

MocotoAnalysisManagerMessenger::MocotoAnalysisManagerMessenger(MocotoAnalysisManager* manager)
  :histo(manager)
{
  histoDir = new G4UIdirectory("/histo/");
  histoDir->SetGuidance("histogram control");

  factoryCmd = new G4UIcmdWithAString("/histo/fileName",this);
  factoryCmd->SetGuidance("set name of the histogram file");
  factoryCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

MocotoAnalysisManagerMessenger::~MocotoAnalysisManagerMessenger()
{
  delete histoDir;
  delete factoryCmd;
}

void MocotoAnalysisManagerMessenger::SetNewValue(G4UIcommand* command,G4String newValues)
{
  if( command == factoryCmd )
    histo->SetFileName(newValues);
}
