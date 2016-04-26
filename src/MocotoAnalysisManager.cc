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
  evtTree->Branch("nHits", &nCrystalsHit, "nHits/I");
  evtTree->Branch("HitNumber", HitCrystalNumber, "HitNumber[nHits]/I");
  evtTree->Branch("HitEnergy", EnergyHitCrystal, "HitEnergy[nHits]/D");
//  evtTree->Branch("nLeak", &nCrystalsLeak, "nLeak/I");
//  evtTree->Branch("LeakNumber", LeakCrystalNumber, "LeakNumber[nLeak]/I");
//  evtTree->Branch("LeakEnergy", EnergyLeakCrystal, "LeakEnergy[nLeak]/D");
  evtTree->Branch("nEdep", &nDeposit, "nEdep/I");
  evtTree->Branch("DepositNumber", DepositNumber, "DepositNumber[nEdep]/I");
  evtTree->Branch("EnergyDeposit", EnergyDeposit, "EnergyDeposit[nEdep]/D");
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
  edep.clear();
  nCpmpt        = 0;
  nRayle        = 0;
  nDeposit      = 0;
  nScattering   = 0;
  nCrystalsHit  = 0;
  nCrystalsLeak = 0;
  m_ifFill      = false;
  for(int i=0; i<20; i++)
  {
    DepositNumber[i]    = 0;
    EnergyDeposit[i]    = 0;
    HitCrystalNumber[i] = 0;
    EnergyHitCrystal[i] = 0;
    LeakCrystalNumber[i]= 0;
    EnergyLeakCrystal[i]= 0;
  }
}

void MocotoAnalysisManager::EndOfEvent()
{
  map<G4int,G4double>::iterator it;
  for(it=edep.begin(); it!=edep.end(); it++)
  {
    DepositNumber[nDeposit] = it->first;
    EnergyDeposit[nDeposit] = it->second;
    nDeposit++;
  }

  if( m_ifFill )  evtTree->Fill();
}

void MocotoAnalysisManager::SetProcess(G4String name)
{
  if( name == "compt" ) nCpmpt++;
  if( name == "Rayl"  ) nRayle++;
  if( nCpmpt + nRayle ) nScattering = 1;
}

void MocotoAnalysisManager::SetPrimaryInfomation(Double_t m_energy, Double_t m_theta, Double_t m_phi)
{
  primary.x = Float_t( m_energy );
  primary.y = Float_t( m_theta*180/3.141592);
  primary.z = Float_t( m_phi*180/3.141592);
}

void MocotoAnalysisManager::HitCrystal(G4int number,G4double energy)
{
  HitCrystalNumber[nCrystalsHit] = number;
  EnergyHitCrystal[nCrystalsHit] = energy;
  nCrystalsHit++;
}

void MocotoAnalysisManager::LeakCrystal(G4int number,G4double energy)
{
  LeakCrystalNumber[nCrystalsLeak] = number;
  EnergyLeakCrystal[nCrystalsLeak] = energy;
  nCrystalsLeak++;
}

void MocotoAnalysisManager::DepositCrystal(G4int number,G4double energy)
{
  edep[number] += energy;
}
