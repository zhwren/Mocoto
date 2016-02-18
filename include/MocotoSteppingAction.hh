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
 * Last modified: 2015-07-14 14:40
 * Filename     : MocotoSteppingAction.hh
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/

#ifndef MocotoSteppingAction_h
#define MocotoSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

class MocotoAnalysisManager;
class MocotoSteppingAction : public G4UserSteppingAction
{
  public:
    MocotoSteppingAction();
    ~MocotoSteppingAction();
    virtual void UserSteppingAction(const G4Step*);
  private:
    void WorldSteppingAction(const G4Step* aStep);
    void TargetSteppingAction(const G4Step* aStep);
    void CrystalSteppingAction(const G4Step* aStep);
    void StripSteppingAction(const G4Step* aStep);
    void FlatPanelSteppingAction(const G4Step* aStep);
    void OnPixelDoIt(const G4Step* aStep);
  private:
    G4Track* fTrack;
    MocotoAnalysisManager* analysis;
    G4String nextVolumeName;
    G4String particleName;
    G4ThreeVector position;
    G4ThreeVector ApronTranslation;
    G4ThreeVector TargetTranslation;
};

#endif
