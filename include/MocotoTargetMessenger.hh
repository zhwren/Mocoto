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
*    >  File Name   : MocotoTargetMessenger.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-02-17 17:15                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MocotoTargetMessenger_h
#define MocotoTargetMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class MocotoTarget;
class G4UIcommand;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithADoubleAndUnit;

class MocotoTargetMessenger : public G4UImessenger
{
  public:
    MocotoTargetMessenger(MocotoTarget*);
    ~MocotoTargetMessenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    MocotoTarget*              target;
    G4UIdirectory*             dTarget;
    G4UIcmdWithADoubleAndUnit* rotate;
    G4UIcmdWith3VectorAndUnit* trans;

};

#endif
