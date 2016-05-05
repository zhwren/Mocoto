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
 * Last modified: 2015-07-14 14:25
 * Filename     : MocotoEventAction.cc
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/

#include "MocotoEventAction.hh"
#include "G4ios.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "MocotoAnalysisManager.hh"

MocotoEventAction::MocotoEventAction()
{}

MocotoEventAction::~MocotoEventAction()
{}

void MocotoEventAction::BeginOfEventAction(const G4Event* anEvent)
{
//  if(anEvent->GetEventID()%2500==0)
  G4cout << "Begin Of Event ---> " << anEvent->GetEventID() << G4endl;
  MocotoAnalysisManager::getInstance()->BeginOfEvent();
  MocotoAnalysisManager::getInstance()->SetEventID(anEvent->GetEventID());
}

void MocotoEventAction::EndOfEventAction(const G4Event* anEvent)
{
//  G4int evtID = anEvent->GetEventID();
//  if( (evtID%1000) == 0 )
//    G4cout << "  End Of Event ---> " << anEvent->GetEventID() << G4endl;
  MocotoAnalysisManager::getInstance()->EndOfEvent();
}
