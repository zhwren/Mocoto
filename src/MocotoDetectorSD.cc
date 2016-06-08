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
    if( pName!="Rayl" && pName!="compt") return false;

    MocotoDetectorHit* hit = new MocotoDetectorHit();
    hit->SetProcessName( pName );
    MocotoCollection->insert( hit );
   
    return true;
  }
  if( volName=="pColumnDetail" )
  {
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4Track* fTrack = aStep->GetTrack();
    G4int col = fTrack->GetTouchable()->GetCopyNumber(0);
    G4int row = fTrack->GetTouchable()->GetCopyNumber(1);
    G4int det = fTrack->GetTouchable()->GetCopyNumber(2);
    MocotoDetectorHit* hit = new MocotoDetectorHit();
    hit->SetEdep( edep );
    hit->SetDetNumber(row*504+det*24+col);
    MocotoCollection->insert( hit );
  }
  return false;
}

void MocotoDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
//  G4double edep = 0;
  G4int NbfScatter = 0;
//  map<G4int, G4double> DepositInfo;
//  G4int NbHits = MocotoCollection->entries();
//  for(G4int i=0; i<NbHits; i++)
//  {
//    G4String pName = (*MocotoCollection)[i]->GetProcessName();
//    if( pName=="Rayl" || pName=="compt" )
//      NbfScatter++;
//    G4int m_DetNumber = (*MocotoCollection)[i]->GetDetNumber();
//    DepositInfo[m_DetNumber] += (*MocotoCollection)[i]->GetEdep();
//    edep += (*MocotoCollection)[i]->GetEdep();
//  }
  G4int ndet = 0;
  G4int detNumber[20];
  G4double detEnergy[20];
//  map<G4int, G4double>::iterator it;
//  for(it=DepositInfo.begin(); it!=DepositInfo.end(); it++)
//  {
//    detNumber[ndet] = it->first;
//    detEnergy[ndet] = it->second;
//    ndet++;
//  }
  MocotoAnalysisManager::getInstance()->SetNbScattering( NbfScatter );
  MocotoAnalysisManager::getInstance()->SetDepositInfo( ndet, detNumber, detEnergy);
//  if( edep!=0 )
//    MocotoAnalysisManager::getInstance()->SetifFill( true );
}
