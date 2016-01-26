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
  private:
    TFile* newFile;
    TTree* evtTree;
    TString filename;
    bool m_ifFill;
    Int_t m_evtID;
    TH2F* h2;
  public:
    void AddDoseInfo(G4ThreeVector,G4double);
  private:
    
    Double_t mDetected;
    Double_t mTargetDeposit;
    Double_t mTargetReflected;
    Double_t mTransmission;
    Double_t mApronDeposit;
    Double_t mApronReflected;
    Double_t mAttach;
    Double_t mEscape;

    Int_t nHits;
    Int_t nRows;
    Int_t nColumns;
    Int_t nDetectors;
    Int_t RowNumbers[30];
    Int_t ColumnNumbers[30];
    Int_t DetectorNumbers[30];

    Int_t nCpmpt;
    Int_t nRayle;
    Int_t nScattering;
    Int_t nDeathInTarget;
    Int_t nCreateGammas;
    Double_t mOutOfWorld;
    Double_t mCreateGamma[10];
    Double_t mCreateGammaTheta[10];
    Double_t mCreateGammaPhi[10];
    Double_t mEscapeFromCrystal[30];
    Double_t mAttachCrystal[30];
    typedef struct { Float_t x,y,z; } VECTOR;
    VECTOR primary,position;
    Int_t stepNO;
    Double_t eDepEachStep[300], totalEdep;
    Float_t px[300],py[300],pz[300];
    map<G4int,G4double> HitInfomation;

  public:
    bool Find(Int_t*,Int_t);
    void SetEventID(Int_t evtid) { m_evtID = evtid; }
    void SetifFill(bool i) { m_ifFill = i; }
    void SetEnergyDeposit(Double_t energy)  { mTargetDeposit += energy; }
    void SetEnergyDetected(Double_t energy) { mDetected += energy; }
    void SetTargetReflected(Double_t energy){ mTargetReflected += energy; }
    void SetThoughEnergy(Double_t energy)   { mTransmission = energy; }
    void SetEnergyApron(Double_t energy)    { mApronDeposit += energy; }
    void SetApronReflected(Double_t energy) { mApronReflected += energy; }
    void SetProcess(G4String name);
    void SetEnergyOut(G4double i) { mOutOfWorld = i; }
    void SetDeathInTarget(G4int i) { nDeathInTarget = i; }
    void SetCreateGamma(G4double,G4ThreeVector);
    void SetCrystalCopyNO(G4Track*);
    void SetPrimaryInfomation(Double_t,Double_t,Double_t);
    void SetEscapeEnergy(G4double i) { mEscapeFromCrystal[nHits] = i; }
    void SetAttachEnergy(G4double i) { mAttach = i; }
    void SetEscapePosotion(G4ThreeVector);
    void SetEnergyDepositInWorfarm(G4double,G4ThreeVector);

  private:
    Int_t nCrystalsHit;
    Int_t nCrystalsEscape;
    Int_t HitCrystalNumber[30];
    Int_t EscapeCrystalNumber[30];
    Double_t EnergyHitCrystal[30];
    Double_t EnergyEscapeCrystal[30];

  public:
    void HitCrystal(G4int,G4double);
    void EscapeCrystal(G4int,G4double,G4ThreeVector);
};
#endif
