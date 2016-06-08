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
 * Filename     : MocotoAnalysisManager.cc
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/
#define PI 3.14159
#include "MocotoAnalysisManager.hh"

MocotoAnalysisManager* MocotoAnalysisManager::fManager = 0;

MocotoAnalysisManager* MocotoAnalysisManager::getInstance()
{
  if( !fManager )
    fManager = new MocotoAnalysisManager();
  return fManager;
}

void MocotoAnalysisManager::dispose()
{
  delete fManager;
  fManager = 0;
}

MocotoAnalysisManager::MocotoAnalysisManager()
{
  evtTree = 0;
  messenger = new MocotoAnalysisManagerMessenger(this);
  filename = "test.root";
}

MocotoAnalysisManager::~MocotoAnalysisManager()
{}

void MocotoAnalysisManager::bookEventTree()
{
  evtTree = new TTree("evt", "evtInfo");
  evtTree->Branch("Scattering", &nScattering, "Scattering/I");
  evtTree->Branch("nStep", &nStep, "nStep/I");
  evtTree->Branch("detNumber", detNumber, "detNumber[nStep]/I");
  evtTree->Branch("detEnergy", detEnergy, "detEnergy[nStep]/D");
}

void MocotoAnalysisManager::BeginOfRun()
{
  newFile = new TFile(filename, "RECREATE");
  bookEventTree();
}

void MocotoAnalysisManager::EndOfRun()
{
  newFile->cd();
  evtTree->Write();
  newFile->Close();
}

void MocotoAnalysisManager::BeginOfEvent()
{
  nScattering   = 0;
  m_ifFill      = false;
}

void MocotoAnalysisManager::EndOfEvent()
{
  if( m_ifFill )
    evtTree->Fill();
}

void MocotoAnalysisManager::SetPrimaryInfomation(Double_t m_energy, Double_t m_theta, Double_t m_phi)
{
  primary.x = Float_t( m_energy );
  primary.y = Float_t( m_theta*180/3.141592);
  primary.z = Float_t( m_phi*180/3.141592);
}

void MocotoAnalysisManager::SetDepositInfo(Int_t ndet, Int_t* number, Double_t* energy)
{
  nStep = ndet;
  detNumber = number;
  detEnergy = energy;
}
