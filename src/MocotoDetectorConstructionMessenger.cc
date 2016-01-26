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
 * Last modified: 2015-07-28 15:36
 * Filename     : MocotoDetectorConstructionMessenger.cc
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/
#include "MocotoDetectorConstructionMessenger.hh"
#include "MocotoDetectorConstruction.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include <sstream>

MocotoDetectorConstructionMessenger::MocotoDetectorConstructionMessenger(MocotoDetectorConstruction* detector)
  :det(detector)
{
  detDir = new G4UIdirectory("/det/");
  detDir->SetGuidance("detector control");

  detNumber = new G4UIcmdWithAnInteger("/det/detector/Number",this);
  detNumber->SetGuidance("set detector number");
  detNumber->SetDefaultValue(1);

  colnumber = new G4UIcmdWithAnInteger("/det/collimator/Number",this);
  colnumber->SetGuidance("set if collimator");
  colnumber->SetDefaultValue(1);

  target_d = new G4UIcmdWithADoubleAndUnit("/det/target/diameter",this);
  target_d->SetGuidance("set target diameter");
  target_d->SetDefaultValue(10);
  target_d->SetDefaultUnit("cm");

  targetRot = new G4UIcmdWithADoubleAndUnit("/det/target/rotateAngle",this);
  targetRot->SetGuidance("set Target Rotate Angle");
  targetRot->SetDefaultValue(0);
  targetRot->SetDefaultUnit("degree");

  m_copper = new G4UIcmdWithADoubleAndUnit("/det/Apron/Copper/thickness",this);
  m_copper->SetGuidance("Copper Apron Thickness");
  m_copper->SetDefaultValue(0);
  m_copper->SetDefaultUnit("mm");

  m_aluminum = new G4UIcmdWithADoubleAndUnit("/det/Apron/Aluminum/thickness",this);
  m_aluminum->SetGuidance("Aluminum Apron Thickness");
  m_aluminum->SetDefaultValue(0);
  m_aluminum->SetDefaultUnit("mm");

  m_wolfram = new G4UIcmdWithADoubleAndUnit("/det/Apron/Wolfram/thickness",this);
  m_wolfram->SetGuidance("Wolfram Apron Thickness");
  m_wolfram->SetDefaultValue(0);
  m_wolfram->SetDefaultUnit("mm");

  tubdetector = new G4UIcmdWithAnInteger("/det/tubdetector",this);
  tubdetector->SetGuidance("tub or not");
  tubdetector->SetDefaultValue(0);

  flatpanel = new G4UIcmdWithAnInteger("/det/flatpanel",this);
  flatpanel->SetGuidance("flat panel detector");
  flatpanel->SetDefaultValue(0);

  targetPosition = new G4UIcmdWith3VectorAndUnit("/det/target/position",this);
  targetPosition->SetGuidance("set target position");
  targetPosition->SetDefaultValue(G4ThreeVector(0,0,0));
  targetPosition->SetDefaultUnit("mm");

}

MocotoDetectorConstructionMessenger::~MocotoDetectorConstructionMessenger()
{
  delete detDir;
  delete detNumber;
  delete colnumber;
  delete target_d;
  delete targetRot;
  delete m_copper;
  delete m_aluminum;
  delete tubdetector;
  delete flatpanel;
  delete m_wolfram;
  delete targetPosition;
}

void MocotoDetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
  if(command == detNumber )
    det->SetDetNumber(newValues);
  if(command == colnumber)
    det->SetColNumber(newValues);
  if(command == target_d)
    det->SetTargetDiameter( target_d->GetNewDoubleValue(newValues) );
  if(command == targetRot)
    det->SetTargetRotateAngle(targetRot->GetNewDoubleValue(newValues));
  if(command == m_copper)
    det->SetCopperThickness(newValues);
  if(command == m_aluminum)
    det->SetAluminumThickness(newValues);
  if(command == tubdetector)
    det->SetTubDetector(newValues);
  if(command == flatpanel )
    det->SetFlatPanel(newValues);
  if(command == m_wolfram)
    det->SetWolframThickness(newValues);
  if(command == targetPosition)
    det->SetTargetPosition(targetPosition->GetNew3VectorValue(newValues));
}
