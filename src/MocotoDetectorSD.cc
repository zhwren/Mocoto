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
using namespace std;

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
  MocotoDetectorHit* hit = new MocotoDetectorHit();
  hit->SetN(1);
  MocotoCollection->insert( hit );
  return false;
}

void MocotoDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  G4cout << MocotoCollection->entries() << G4endl;
}
