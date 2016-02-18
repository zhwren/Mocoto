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
//  evtTree->Branch("evtID", &m_evtID, "evtID/I");
//  evtTree->Branch("targetDeposit", &mTargetDeposit, "targetDeposit/D");
//  evtTree->Branch("detected", &mDetected, "detected/D");
//  evtTree->Branch("outOfWorld", &mOutOfWorld, "outOfWorld/D");
//  evtTree->Branch("targetReflect", &mTargetReflected, "targetReflect/D");
//  evtTree->Branch("apronReflect", &mApronReflected, "apronReflect/D");
//  evtTree->Branch("transminnion", &mTransmission, "transmission/D");
//  evtTree->Branch("apronDeposit", &mApronDeposit, "apronDeposit/D");
//  evtTree->Branch("deathInTarget", &nDeathInTarget, "deathInTarget/I");
//  evtTree->Branch("Scattering", &nScattering, "Scattering/I");
//  evtTree->Branch("Rayle",&nRayle, "Rayle/I");
//  evtTree->Branch("Compt",&nCpmpt, "Compt/I");
//  evtTree->Branch("NHits", &nHits, "NHits/I");
//  evtTree->Branch("NRows", &nRows, "NRows/I");
//  evtTree->Branch("NColumns", &nColumns, "NColumns/I");
//  evtTree->Branch("NDetectors", &nDetectors, "NDetectors/I");
//  evtTree->Branch("RowNumber", RowNumbers, "RowNumber[NHits]/I");
//  evtTree->Branch("ColumnNumber", ColumnNumbers, "ColumnNumber[NHits]/I");
//  evtTree->Branch("DetecterNumber", DetectorNumbers, "DetecterNumber[NHits]/I");
//  evtTree->Branch("AttachCrystal", mAttachCrystal, "AttachCrystal[NHits]/D");
//  evtTree->Branch("EscapeFromCrystal", mEscapeFromCrystal, "EscapeFromCrystal[NHits]/D");
//  evtTree->Branch("CreateN", &nCreateGammas, "CreateN/I");
//  evtTree->Branch("CreateE", mCreateGamma, "CreateE[CreateN]/D");
//  evtTree->Branch("CreateTh", mCreateGammaTheta, "CreateTh[CreateN]/D");
//  evtTree->Branch("CreatePh", mCreateGammaPhi, "CreatePh[CreateN]/D");
//  evtTree->Branch("primary", &primary, "energy/F:theta/F:phi/F");
//  evtTree->Branch("position", &position, "x/F:y/F:z/F");
//  evtTree->Branch("nstep", &stepNO, "nstep/I");
//  evtTree->Branch("totalEdep", &totalEdep, "totalEdep/D");
//  evtTree->Branch("edepEachStep", eDepEachStep, "edep[nstep]/D");
  evtTree->Branch("nHits", &nCrystalsHit, "nHits/I");
  evtTree->Branch("HitCrystalNumber", HitCrystalNumber, "HitCrystalNumber[nHits]/I");
  evtTree->Branch("EnergyHitCrystal", EnergyHitCrystal, "EnergyHitCrystal[nHits]/D");
//  evtTree->Branch("nEscape", &nCrystalsEscape, "nEscape/I");
//  evtTree->Branch("EscapeCrystalNumber", EscapeCrystalNumber, "EscapeCrystalNumber[nEscape]/I");
//  evtTree->Branch("EnergyEscapeCrystal", EnergyEscapeCrystal, "EnergyEscapeCrystal[nEscape]/D");
//  evtTree->Branch("x", px, "x[nstep]/F");
//  evtTree->Branch("y", py, "y[nstep]/F");
//  evtTree->Branch("z", pz, "z[nstep]/F");
}

void MocotoAnalysisManager::BeginOfRun()
{
  newFile = new TFile(filename, "RECREATE");
//  h2 = new TH2F("h2","CTDose",420,-210,210,420,-210,210);
  bookEventTree();
}

void MocotoAnalysisManager::EndOfRun()
{
  newFile->cd();
//  h2->Write();
  evtTree->Write();
  newFile->Close();
}

void MocotoAnalysisManager::BeginOfEvent()
{
  nCpmpt       = 0;
  nRayle       = 0;
  nScattering  = 0;
  nDeathInTarget       = 0;
  mTargetDeposit        = 0.0;
  mDetected        = 0.0;
  mTargetReflected        = 0.0;
  mTransmission        = 0.0;
  mApronDeposit        = 0.0;
  mApronReflected        = 0.0;
  mEscape    = 0.0;
  mAttach    = 0.0;
  mOutOfWorld   = 0.0;
  m_ifFill      = false;
  nCreateGammas = 0;
  for(int i=0; i<10; i++) {
    mCreateGamma[i] = 0;
    mCreateGammaTheta[i] = 100;
    mCreateGammaPhi[i] = 100;
  }
  nHits       = 0;
  nRows       = 0;
  nColumns    = 0;
  nDetectors  = 0;
  for(int i=0; i<30; i++) {
    RowNumbers[i] = 0;
    ColumnNumbers[i] = -1;
    DetectorNumbers[i] = 0;
    mEscapeFromCrystal[i] = 0;
    mAttachCrystal[i] = 0;
    HitCrystalNumber[i] = 0;
    EscapeCrystalNumber[i] = 0;
    EnergyHitCrystal[i] = 0;
    EnergyEscapeCrystal[i] = 0;
  }
  stepNO = 0;
  totalEdep = 0;
  nCrystalsHit = 0;
  nCrystalsEscape = 0;
  for(Int_t i=0; i<300; i++)
  {
    eDepEachStep[i] = 0;
    px[i] = 0;
    py[i] = 0;
    pz[i] = 0;
  }
  HitInfomation.clear();
}

void MocotoAnalysisManager::EndOfEvent()
{
  if( m_ifFill )
  {
    map<G4int,G4double>::iterator it;
    for(it=HitInfomation.begin();it!=HitInfomation.end();it++)
    {
      HitCrystalNumber[nCrystalsHit] = it->first;
      EnergyHitCrystal[nCrystalsHit] = it->second;
      nCrystalsHit++;
    }
    evtTree->Fill();
  }
}

void MocotoAnalysisManager::SetProcess(G4String name)
{
  if( name == "compt" ) nCpmpt++;
  if( name == "Rayl"  ) nRayle++;
  if( nCpmpt + nRayle ) nScattering = 1;
}

void MocotoAnalysisManager::SetCreateGamma(G4double create,G4ThreeVector direction)
{
  Double_t tmpTheta,tmpPhi,tmpLength;
  mCreateGamma[nCreateGammas] = create;
  tmpLength = sqrt( direction.x()*direction.x()
                   +direction.y()*direction.y()
      	           +direction.z()*direction.z() );
  tmpPhi = atan( direction.y()/direction.x() );
  tmpTheta = acos( direction.z()/tmpLength );
  mCreateGammaTheta[nCreateGammas] = tmpTheta*180/3.141592;
  mCreateGammaPhi[nCreateGammas] = tmpPhi*180/3.141592;
  nCreateGammas++;
}

void MocotoAnalysisManager::SetCrystalCopyNO(G4Track* fTrack)
{
  Int_t column   = fTrack->GetTouchable()->GetCopyNumber(0);
  Int_t row      = fTrack->GetTouchable()->GetCopyNumber(1);
  Int_t detector = fTrack->GetTouchable()->GetCopyNumber(2);
  if( !Find( RowNumbers, row) ||
      !Find( ColumnNumbers, column) ||
      !Find( DetectorNumbers, detector))
  {

    if( !Find( RowNumbers, row) ) nRows++;
    if( !Find( ColumnNumbers, column) ) nColumns++;
    if( !Find( DetectorNumbers, detector) ) nDetectors++;

    RowNumbers[nHits] = row;
    ColumnNumbers[nHits] = column;
    DetectorNumbers[nHits] = detector;
    mAttachCrystal[nHits] = mAttach;
    nHits++;
  }
}

bool MocotoAnalysisManager::Find(Int_t* list, Int_t num)
{
  bool find = false;
  for(Int_t i=0; i<30; i++)
  {
    if( num == list[i] )
    {
      find = true;
      break;
    }
  }
  return find;
}
void MocotoAnalysisManager::SetPrimaryInfomation(Double_t m_energy, Double_t m_theta, Double_t m_phi)
{
  primary.x = Float_t( m_energy );
  primary.y = Float_t( m_theta*180/3.141592);
  primary.z = Float_t( m_phi*180/3.141592);
}

void MocotoAnalysisManager::SetEscapePosotion(G4ThreeVector apos)
{
  position.x = apos.x();
  position.y = apos.y();
  position.z = apos.z();
}

void MocotoAnalysisManager::SetEnergyDepositInWorfarm(G4double energy,G4ThreeVector pos)
{
  eDepEachStep[stepNO] = energy;
  totalEdep += energy;
  px[stepNO] = pos.x();
  py[stepNO] = pos.y();
  pz[stepNO] = pos.z();
  stepNO++;
}

void MocotoAnalysisManager::HitCrystal(G4int number,G4double energy)
{
  HitInfomation[number] += energy;
}

void MocotoAnalysisManager::EscapeCrystal(G4int number,G4double energy,G4ThreeVector pos)
{
  EscapeCrystalNumber[nCrystalsEscape] = number;
  EnergyEscapeCrystal[nCrystalsEscape] = energy;
  px[nCrystalsEscape] = pos.x();
  py[nCrystalsEscape] = pos.y();
  pz[nCrystalsEscape] = pos.z();
  nCrystalsEscape++;
}

void MocotoAnalysisManager::AddDoseInfo(G4ThreeVector point, G4double e)
{
  h2->Fill(point.x(),point.y(),e);
}
