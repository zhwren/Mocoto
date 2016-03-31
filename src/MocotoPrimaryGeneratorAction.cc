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
 * Last modified: 2015-11-06 13:56:1446789398
 * Filename     : MocotoPrimaryGeneratorAction.cc
 * Phone Number : 18625272373                               *
 * Discription  :                                           *
 ***********************************************************/
#ifndef PI
#define PI 3.141592653589793238462643383279502884L
#endif

#include "MocotoAnalysisManager.hh"
#include "MocotoPrimaryGeneratorAction.hh"
#include "MocotoPrimaryGeneratorMessenger.hh"

#include "TH1F.h"
#include "TFile.h"
#include "G4Event.hh"
#include "Randomize.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

using namespace CLHEP;

MocotoPrimaryGeneratorAction::MocotoPrimaryGeneratorAction()
  :G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
  nofParticles = 1;
  particleName = "gamma";
  particleEnergy = 100*keV;
  position = G4ThreeVector(0,0,0);
  momentumDirection = G4ThreeVector(1,0,0);
  analysis = MocotoAnalysisManager::getInstance();
  fParticleGun = new G4ParticleGun( nofParticles );
  particleTable = G4ParticleTable::GetParticleTable();
  messenger = new MocotoPrimaryGeneratorMessenger(this);
  file = new TFile("/home/zhwren/Workfs/Mocoto/Job/xray_120keV_1mmAluminum.root");
//  file = NULL;
}

MocotoPrimaryGeneratorAction::~MocotoPrimaryGeneratorAction()
{
  delete fParticleGun;
  if( file )
  {
    file->Close();
    delete file;
  }
}

void MocotoPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  GetSpectrumFromFile();
  particle = particleTable->FindParticle( particleName );
  fParticleGun->SetParticleDefinition( particle );
  fParticleGun->SetParticleEnergy( particleEnergy );
  fParticleGun->SetParticlePosition( position );
  G4ThreeVector momentum = ParticleMomentum();
  fParticleGun->SetParticleMomentumDirection( momentum );
  fParticleGun->GeneratePrimaryVertex( anEvent );
}

G4ThreeVector MocotoPrimaryGeneratorAction::ParticleMomentum()
{
  G4double theta = momentumDirection.y() + generateDelteAngle.y()*(G4UniformRand()*2-1);
  G4double phi   = momentumDirection.z() + generateDelteAngle.z()*(G4UniformRand()*2-1);
  G4double p_x = sin( theta ) * cos( phi );
  G4double p_y = sin( theta ) * sin( phi );
  G4double p_z = cos( theta );
  analysis->SetPrimaryInfomation(particleEnergy, theta, phi);
  return G4ThreeVector(p_x, p_y, p_z);
}

void MocotoPrimaryGeneratorAction::GetSpectrumFromFile()
{
  if( !file ) return;
  TH1F* h1 = (TH1F*)file->Get("h1");
  particleEnergy = h1->GetRandom();
}
