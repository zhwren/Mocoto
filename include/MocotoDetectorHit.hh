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
*    >  File Name   : MocotoDetectorHit.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-06-07 10:24                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MocotoDetectorHit_h
#define MocotoDetectorHit_h 1

#include "G4VHit.hh"
#include "G4VProcess.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class MocotoDetectorHit : public G4VHit
{
  public:
    MocotoDetectorHit();
    ~MocotoDetectorHit();

    inline void* operator new(size_t);
    inline void  operator delete(void*);

  public:
    void ScatterCount(const G4VProcess*);
    G4int GetScattering() { return m_Scatter; }
  private:
    G4int m_Scatter;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<MocotoDetectorHit> MocotoDetectorHitCollection;

extern G4Allocator<MocotoDetectorHit> MocotoDetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* MocotoDetectorHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) MocotoDetectorHitAllocator.MallocSingle();
  return aHit;
}

inline void MocotoDetectorHit::operator delete(void* aHit)
{
  MocotoDetectorHitAllocator.FreeSingle( (MocotoDetectorHit*) aHit );
}

#endif
