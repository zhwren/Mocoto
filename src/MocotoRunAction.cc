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
 * Last modified: 2015-07-14 14:12
 * Filename     : MocotoRunAction.cc
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/

#include "MocotoRunAction.hh"
#include "MocotoAnalysisManager.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

MocotoRunAction::MocotoRunAction()
{}

MocotoRunAction::~MocotoRunAction()
{}

void MocotoRunAction::BeginOfRunAction(const G4Run* aRun)
{
  MocotoAnalysisManager* analysis = MocotoAnalysisManager::getInstance();
  analysis->BeginOfRun();

  G4int RunNo = aRun->GetRunID();
  G4cout << "### Begin Of Run------>" << RunNo << G4endl;
}

void MocotoRunAction::EndOfRunAction(const G4Run* aRun)
{
  MocotoAnalysisManager* analysis = MocotoAnalysisManager::getInstance();

  G4int RunNo = aRun->GetRunID();
  G4cout << "##### End Of Run------>" << RunNo << G4endl;

  analysis->EndOfRun();
}
