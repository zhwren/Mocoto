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
 * Last modified: 2015-11-06 13:50:1446789037
 * Filename     : MocotoPrimaryGeneratorAction.hh
 * Phone Number : 18625272373                               *
 * Discription  :                                           *
 ***********************************************************/
#ifndef MocotoPrimaryGeneratorAction_h
#define MocotoPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "TString.h"

class TFile;
class G4Event;
class G4ParticleGun;
class G4ParticleTable;
class G4ParticleDefinition;
class MocotoPrimaryGeneratorMessenger;

class MocotoPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    MocotoPrimaryGeneratorAction();
    ~MocotoPrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);
  private:
    TFile*      file;
    G4int       nofParticles;
    G4String    particleName;
    G4double    particleEnergy;
    G4ThreeVector           position;
    G4ParticleGun*          fParticleGun;
    G4ParticleDefinition*   particle;
    G4ParticleTable*        particleTable;
    G4ThreeVector           momentumDirection;
    MocotoPrimaryGeneratorMessenger* messenger;
    G4ThreeVector                    generateDelteAngle;
  public:
    void SetGeneratorEnergy(G4double i) { particleEnergy = i; }
    void SetParticle(TString i) { particleName = i; }
    void SetPosition(G4ThreeVector pos) { position = pos; }
    void SetDeltaThetaPhi(G4ThreeVector delta) { generateDelteAngle = delta; }
    void SetMomentumDirection(G4ThreeVector direction) { momentumDirection = direction; }
  private:
    G4ThreeVector ParticleMomentum();
    void GetSpectrumFromFile();
};

#endif
