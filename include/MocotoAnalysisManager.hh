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
 * Last modified: 2015-07-14 13:42
 * Filename     : MocotoAnalysisManager.hh
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/

#ifndef MocotoAnalysisManager_h
#define MocotoAnalysisManager_h 1

#include "globals.hh"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "TObjString.h"
#include <fstream>
#include "MocotoAnalysisManagerMessenger.hh"
#include <vector>
#include <map>
using namespace std;

class MocotoAnalysisManager
{
  public:
    static MocotoAnalysisManager* getInstance();
    static void dispose();

  private:
    MocotoAnalysisManager();
    ~MocotoAnalysisManager();
    static MocotoAnalysisManager* fManager;
    MocotoAnalysisManagerMessenger* messenger;
  
  public:
    void bookEventTree();
    void BeginOfRun();
    void EndOfRun();
    void BeginOfEvent();
    void EndOfEvent();
    void SetFileName(TString i) { filename = i; }

    void SetEventID(Int_t evtid) { m_evtID = evtid; }
    void SetifFill(bool i) { m_ifFill = i; }
    void SetProcess(G4String name);
    void SetPrimaryInfomation(Double_t,Double_t,Double_t);
    void HitCrystal(G4int,G4double);
    void LeakCrystal(G4int,G4double);
    void DepositCrystal(G4int,G4double);
    void PhotReactionHappened() { NbfPhot += 1; }
    void ComptReactionHappened() { NbfCompt+=1; }

  private:
    typedef struct { Float_t x,y,z; } VECTOR;
    map<G4int,G4double> edep;
    TFile*   newFile;
    TTree*   evtTree;
    TString  filename;
    bool     m_ifFill;
    Int_t    m_evtID;
    Int_t    nCpmpt;
    Int_t    nRayle;
    Int_t    nScattering;
    VECTOR   primary,position;
    Int_t    nCrystalsHit;
    Int_t    nCrystalsLeak;
    Int_t    HitCrystalNumber[20];
    Double_t EnergyHitCrystal[20];
    Int_t    LeakCrystalNumber[20];
    Double_t EnergyLeakCrystal[20];
    Int_t    nDeposit;
    Int_t    DepositNumber[20];
    Double_t EnergyDeposit[20];
    Int_t    NbfCompt;
    Int_t    NbfPhot;
};
#endif
