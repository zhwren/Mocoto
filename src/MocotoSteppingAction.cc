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
  if( VolumeName=="pTarget" || VolumeName=="pHolder" )
    TargetSteppingAction( fStep );
  if( VolumeName=="pWorld" )
    WorldSteppingAction( fStep );
  if( VolumeName=="pColumnDetail" )
    StripSteppingAction( fStep );
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
  analysis->SetifFill( true );
  G4int column = fTrack->GetTouchable()->GetCopyNumber(0);
//  G4int row    = fTrack->GetTouchable()->GetCopyNumber(1);
  G4int detec  = fTrack->GetTouchable()->GetCopyNumber(2);
//  if( fStep->IsFirstStepInVolume() )
//  {
//    G4double secondE = fTrack->GetKineticEnergy()+fStep->GetTotalEnergyDeposit();
//    analysis->HitCrystal(detec*24+column, secondE );
//  }
  analysis->DepositCrystal(detec*24+column, fStep->GetTotalEnergyDeposit() );
}
