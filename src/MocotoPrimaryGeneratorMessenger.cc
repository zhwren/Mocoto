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
 * Last modified: 2015-08-28 10:52:1440730374
 * Filename     : MocotoPrimaryGeneratorMessenger.cc
 * Phone Number : 18625272373                               *
 * Discription  :                                           *
 ***********************************************************/
#include "MocotoPrimaryGeneratorMessenger.hh"
#include "MocotoPrimaryGeneratorAction.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include <sstream>

MocotoPrimaryGeneratorMessenger::MocotoPrimaryGeneratorMessenger(MocotoPrimaryGeneratorAction* particle)
  :gen(particle)
{
  genDir = new G4UIdirectory("/gen/");
  genDir->SetGuidance("particle control");

  genParticle = new G4UIcmdWithAString("/gen/particle",this);
  genParticle->SetGuidance("select particle");
  genParticle->SetDefaultValue("gamma");

  genEnergy = new G4UIcmdWithADoubleAndUnit("/gen/particle/energy",this);
  genEnergy->SetGuidance("set generate energy");
  genEnergy->SetDefaultValue(100.);
  genEnergy->SetDefaultUnit("keV");

  genThetaPhi = new G4UIcmdWith3VectorAndUnit("/gen/particle/momentumDirection",this);
  genThetaPhi->SetGuidance("set particle direction");
  genThetaPhi->SetDefaultValue(G4ThreeVector(0,90,0));
  genThetaPhi->SetDefaultUnit("degree");

  genDeltaThetaPhi = new G4UIcmdWith3VectorAndUnit("/gen/particle/deltaThetaPhi",this);
  genDeltaThetaPhi->SetGuidance("set delta theta and delta phi");
  genDeltaThetaPhi->SetDefaultValue(G4ThreeVector(0,0,0));
  genDeltaThetaPhi->SetDefaultUnit("degree");

  genPosition = new G4UIcmdWith3VectorAndUnit("/gen/particle/position",this);
  genPosition->SetGuidance("set position");
  genPosition->SetDefaultValue(G4ThreeVector(0,0,0));
  genPosition->SetDefaultUnit("cm");
}

MocotoPrimaryGeneratorMessenger::~MocotoPrimaryGeneratorMessenger()
{
  delete genDir;
  delete genEnergy;
  delete genThetaPhi;
  delete genDeltaThetaPhi;
  delete genParticle;
  delete genPosition;
}

void MocotoPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,G4String newValues)
{
  if(command == genEnergy)
    gen->SetGeneratorEnergy( genEnergy->GetNewDoubleValue(newValues) );
  
  if(command == genParticle)
    gen->SetParticle(newValues);

  if(command == genPosition)
    gen->SetPosition( genPosition->GetNew3VectorValue(newValues) );

  if(command == genThetaPhi)
    gen->SetMomentumDirection( genThetaPhi->GetNew3VectorValue(newValues) );

  if(command == genDeltaThetaPhi)
    gen->SetDeltaThetaPhi( genDeltaThetaPhi->GetNew3VectorValue(newValues) );
}
