//############################################################
//#                         _ooOoo_                          #
//#                        o8888888o                         #
//#                        88" . "88                         #
//#                        (| -_- |)                         #
//#                         O\ = /O                          #
//#                     ____/`---'\____                      #
//#                   .   ' \\| |// `.                       #
//#                    / \\||| : |||// \                     #
//#                  / _||||| -:- |||||- \                   #
//#                    | | \\\ - /// | |                     #
//#                  | \_| ''\---/'' | |                     #
//#                   \ .-\__ `-` ___/-. /                   #
//#                ___`. .' /--.--\ `. . __                  #
//#             ."" '< `.____<|>_/___.' >'"".                #
//#            | | : `- \`.;` _ /`;.`/ - ` : | |             #
//#              \ \ `-. \_ __\ /__ _/ .-` / /               #
//#      ======`-.____`-.___\_____/___.-`____.-'======       #
//#                         `=---='                          #
//#                                                          #
//#      .............................................       #
//#             Buddha bless me, No bug forever              #
//#                                                          #
//############################################################
//# Author       : ZhuHaiWen                                 #
//# Email        : zhuhw@ihep.ac.cn/zhwren0211@whu.edu.cn    #
//# Last modified: 2015-11-30 14:33:1448865210
//# Filename     : MocotoSteppingAction.cc
//# Phone Number : 18625272373                               #
//# Discription  :                                           #
//############################################################
#include "G4ios.hh"
#include "G4Track.hh"
#include "G4UImanager.hh"
#include "G4SteppingManager.hh"
#include "MocotoAnalysisManager.hh"
#include "MocotoSteppingAction.hh"

MocotoSteppingAction::MocotoSteppingAction()
{
  analysis = MocotoAnalysisManager::getInstance();
}

MocotoSteppingAction::~MocotoSteppingAction()
{}

void MocotoSteppingAction::UserSteppingAction(const G4Step* fStep)
{
  fTrack = fStep->GetTrack();
  particleName = fTrack->GetParticleDefinition()->GetParticleName();
  G4String VolumeName = fTrack->GetVolume()->GetName();
  G4double edep = fStep->GetTotalEnergyDeposit();
  G4ThreeVector position = fTrack->GetPosition();
//  if( VolumeName=="pCrystal" )
//    CrystalSteppingAction( fStep );
  if( VolumeName=="pTarget" || VolumeName=="pHolder" )
    TargetSteppingAction( fStep );
  if( VolumeName=="pWorld" )
    WorldSteppingAction( fStep );
  if( VolumeName=="pStrip" )
    StripSteppingAction( fStep );
  if( VolumeName=="pPixel" )
    OnPixelDoIt( fStep );
}

void MocotoSteppingAction::CrystalSteppingAction(const G4Step* fStep)
{
  analysis->SetifFill( true );
  G4int row = fTrack->GetTouchable()->GetCopyNumber(1);
  G4int column = fTrack->GetTouchable()->GetCopyNumber(0);
  if( fStep->IsFirstStepInVolume() )
    analysis->HitCrystal( column+row, fTrack->GetKineticEnergy() );

  if( fStep->IsLastStepInVolume() )
    analysis->EscapeCrystal( column+row, fTrack->GetKineticEnergy(), fTrack->GetPosition() );
}

void MocotoSteppingAction::TargetSteppingAction(const G4Step* fStep)
{
  const G4VProcess* process = fStep->GetPostStepPoint()->GetProcessDefinedStep();
  if( particleName=="gamma" && process )
    analysis->SetProcess( process->GetProcessName() );
}

void MocotoSteppingAction::WorldSteppingAction(const G4Step* fStep)
{
  const G4VProcess* process = fStep->GetPostStepPoint()->GetProcessDefinedStep();
  if( particleName=="gamma" && process )
    analysis->SetProcess( process->GetProcessName() );
}

void MocotoSteppingAction::StripSteppingAction(const G4Step* fStep)
{
  analysis->SetifFill(true);
  G4int strip = fTrack->GetTouchable()->GetCopyNumber(0);
  
  if( fStep->IsFirstStepInVolume() &&particleName=="gamma" )
  {
    const std::vector<const G4Track*>* secondaries = fStep->GetSecondaryInCurrentStep();
    G4int nbtrk = (*secondaries).size();
    G4double secondaryEnergy = 0;
    for(G4int i=0; i<nbtrk; i++) {
      const G4Track* trk = (*secondaries)[i];
      secondaryEnergy += trk->GetKineticEnergy();
    }

    analysis->HitCrystal( strip, fTrack->GetKineticEnergy()+secondaryEnergy );
    G4cout << "First Step: " << fTrack->GetKineticEnergy()+secondaryEnergy << G4endl;
  }

  if( fStep->IsLastStepInVolume() && particleName=="gamma" )
    analysis->EscapeCrystal( strip, fTrack->GetKineticEnergy(), fTrack->GetPosition() );
}

void MocotoSteppingAction::FlatPanelSteppingAction(const G4Step* fStep)
{
  analysis->SetifFill(true);
  analysis->SetThoughEnergy( fTrack->GetKineticEnergy() );
  fTrack->SetTrackStatus( fStopAndKill );
}

void MocotoSteppingAction::OnPixelDoIt(const G4Step* fStep)
{
  analysis->HitCrystal( fTrack->GetTouchable()->GetCopyNumber(0),
                        fStep->GetTotalEnergyDeposit() );
//  G4cout << fTrack->GetTouchable()->GetCopyNumber(0) << G4endl;
//  G4cout << fStep->GetTotalEnergyDeposit() << G4endl;
  analysis->SetifFill( true );
}
