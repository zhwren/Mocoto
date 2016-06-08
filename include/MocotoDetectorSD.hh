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
*    >  File Name   : MocotoDetectorSD.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-06-07 10:34                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MocotoDetectorSD_h
#define MocotoDetectorSD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "MocotoDetectorHit.hh"

class MocotoDetectorSD : public G4VSensitiveDetector
{
  private:
    MocotoDetectorSD(G4String name);
    static MocotoDetectorSD* fSD;
  public:
    ~MocotoDetectorSD();
    static MocotoDetectorSD* getInstance();

    void Initialize(G4HCofThisEvent* HCE);
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
    void EndOfEvent(G4HCofThisEvent* HCE);

  private:
    MocotoDetectorHitCollection* MocotoCollection;
    bool iftrig;
};

#endif
