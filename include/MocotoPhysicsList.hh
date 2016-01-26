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
 * Last modified: 2015-09-09 16:58:1441789123
 * Filename     : MocotoPhysicsList.hh
 * Phone Number : 18625272373                               *
 * Discription  :                                           *
 ***********************************************************/
#ifndef MocotoPhysicsList_h
#define MocotoPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;

class MocotoPhysicsList : public G4VUserPhysicsList
{
  public:
    MocotoPhysicsList();
    virtual ~MocotoPhysicsList();

    void ConstructParticle();
    void ConstructGeneral();

    void ConstructProcess();
    virtual void SetCuts();
    void SetCutForGamma(G4double);
    void SetCutForElectron(G4double);
    void SetCutForPositron(G4double);

  private:
    G4double defaultCutValue;
    G4double cutForGamma;
    G4double cutForElectron;
    G4double cutForPositron;
    G4VPhysicsConstructor* emPhysicsList;
};

#endif
