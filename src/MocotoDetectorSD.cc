/***********************************************************
*                                                          *
*                                                          *
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
*                                                          *
*      .............................................       *
*             Buddha bless me, No bug forever              *
************************************************************
*    >  CopyRight   :                                      *
*    >  File Name   : MocotoDetectorSD.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-06-07 10:37                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4SDManager.hh"
#include "MocotoDetectorSD.hh"
#include "G4VPhysicalVolume.hh"
#include "G4HCofThisEvent.hh"
#include "MocotoAnalysisManager.hh"
using namespace std;

MocotoDetectorSD* MocotoDetectorSD::fSD = 0;

MocotoDetectorSD* MocotoDetectorSD::getInstance()
{
  if( !fSD )
    fSD = new MocotoDetectorSD("MocotoSD");
  return fSD;
}

MocotoDetectorSD::MocotoDetectorSD(G4String name)
  :G4VSensitiveDetector(name)
{
  collectionName.insert("MocotoDetectorHitCollection");
}

MocotoDetectorSD::~MocotoDetectorSD()
{}

void MocotoDetectorSD::Initialize(G4HCofThisEvent* HCE)
{
  MocotoCollection = new MocotoDetectorHitCollection
                        (SensitiveDetectorName, collectionName[0]);

  static G4int HCID = -1;
  if( HCID<0 )
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection(HCID, MocotoCollection);

  iftrig = false;
}

G4bool MocotoDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4String volName = aStep->GetTrack()->GetVolume()->GetName();

  if( volName=="pTarget" || volName=="pWorld" )
  {
    const G4VProcess* aProcess = aStep->GetPostStepPoint()->GetProcessDefinedStep();
    if( !aProcess ) return false;
    G4String pName = aProcess->GetProcessName();
    MocotoDetectorHit* hit = new MocotoDetectorHit();
    hit->SetScattering( pName );
    MocotoCollection->insert( hit );
   
    return true;
  }
  else if( volName=="pColumnDetail" )
  {
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4Track* fTrack = aStep->GetTrack();
    G4int col = fTrack->GetTouchable()->GetCopyNumber(0);
    G4int row = fTrack->GetTouchable()->GetCopyNumber(1);
    G4int det = fTrack->GetTouchable()->GetCopyNumber(2);
    if( row!=8 ) return false;
    MocotoDetectorHit* hit = new MocotoDetectorHit();
    hit->SetEdep( edep );
    hit->SetDetNumber(det*24+col);//+row*504);
    MocotoCollection->insert( hit );
  }
  return false;
}

void MocotoDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  G4double edep = 0;
  G4int NbfScatter = 0;
  map<G4int, G4double> DepositInfo;
  G4int NbHits = MocotoCollection->entries();
  for(G4int i=0; i<NbHits; i++)
  {
    NbfScatter += (*MocotoCollection)[i]->GetScattering();
    G4int m_DetNumber = (*MocotoCollection)[i]->GetDetNumber();
    G4double energy = (*MocotoCollection)[i]->GetEdep();
    if( energy!=0 )
    {
      DepositInfo[m_DetNumber] += energy;
      edep += energy;
    }
  }

  if( edep!=0 )
  {
    MocotoAnalysisManager::getInstance()->SetScattering( NbfScatter );
    MocotoAnalysisManager::getInstance()->SetDepositInfo( DepositInfo );
    MocotoAnalysisManager::getInstance()->SetifFill( true );
  }
}
