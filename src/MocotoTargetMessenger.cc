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
************************************************************
*    >  File Name   : MocotoTargetMessenger.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 17:20                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "MocotoTargetMessenger.hh"
#include "MocotoTarget.hh"

#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"

MocotoTargetMessenger::MocotoTargetMessenger(MocotoTarget* vTarget)
  :target(vTarget)
{
  dTarget = new G4UIdirectory("/target/");
  dTarget->SetGuidance("target control");

  rotate = new G4UIcmdWithADoubleAndUnit("/target/rotate",this);
  rotate->SetGuidance("set target rotate angle");
  rotate->SetDefaultValue(0);
  rotate->SetDefaultUnit("degree");

  trans = new G4UIcmdWith3VectorAndUnit("/target/position",this);
  trans->SetGuidance("set target position");
  trans->SetDefaultValue(G4ThreeVector(0,0,0));
  trans->SetDefaultUnit("mm");
}

MocotoTargetMessenger::~MocotoTargetMessenger()
{
  delete dTarget;
  delete rotate;
  delete trans;
}

void MocotoTargetMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
  if( command == rotate )
    target->SetRotateAngle( rotate->GetNewDoubleValue( newValues ) );

  if( command == trans )
    target->SetTranslation( trans->GetNew3VectorValue( newValues ) );
}
