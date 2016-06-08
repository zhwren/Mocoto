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
    void SetPrimaryInfomation(Double_t,Double_t,Double_t);
    void SetNbScattering(Int_t i) { nScattering = i; }
    void SetDepositInfo(Int_t,Int_t*,Double_t*);

  private:
    typedef struct { Float_t x,y,z; } VECTOR;
    VECTOR   primary,position;
    TFile*   newFile;
    TTree*   evtTree;
    TString  filename;
    bool     m_ifFill;
    Int_t    m_evtID;
    Int_t    nScattering;
    Int_t    nStep;
    Int_t    *detNumber;
    Double_t *detEnergy;
};
#endif
