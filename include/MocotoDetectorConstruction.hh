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
 * Last modified: 2015-07-14 09:46
 * Filename     : MocotoDetectorConstruction.hh
 * Phone Number : 18627814293                               *
 * Discription  :                                           *
 ***********************************************************/

#ifndef MocotoDetectorConstruction_h
#define MocotoDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "TString.h"
#include "G4ThreeVector.hh"
using namespace std;

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Sphere;
class G4Tubs;
class G4Box;
class G4VSolid;
class G4Material;
class MocotoDetectorConstructionMessenger;

class MocotoDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MocotoDetectorConstruction();
    virtual ~MocotoDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
  private:
    void DefineMaterials();
    void ConstructHouse();

    G4Material* matAir;
    G4Material* matIron;
    G4Material* matGlass;
    G4Material* matWater;
    G4Material* matWolfram;
    G4Material* matCsI;
    G4Material* matAl;
    G4Material* matCu;
    G4Material* Galactic;
    G4Material* matTi;
    G4Material* matPb;
    G4Material* matPOLYETHYLENE;
    G4Material* matBoneCompact;
    G4Material* matBoneCortical;
    G4Material* matBrain;
  public:
    G4VPhysicalVolume* MakeDetectorVolume(G4int);
    G4VPhysicalVolume* MakeCollimatorLogical(G4int);
    G4VPhysicalVolume* MakeDetectorLinePhysical(G4LogicalVolume*);
    G4VPhysicalVolume* MakeDetectorRowPhysical(G4LogicalVolume*,G4double);

  private:
    G4Box*             solidWorld;
    G4LogicalVolume*   logicWorld;
    G4VPhysicalVolume* physiWorld;

    G4VSolid*          solidTarget;
    G4LogicalVolume*   logicTarget;
    G4VPhysicalVolume* physiTarget;

    G4VSolid*          solidTargetHolder;
    G4LogicalVolume*   logicTargetHolder;
    G4VPhysicalVolume* physiTargetHolder;

    G4VSolid*          solidDetector;
    G4LogicalVolume*   logicDetector;
    G4VPhysicalVolume* physiDetector;

    G4Box*             solidCollimator;
    G4LogicalVolume*   logicCollimator;
    G4VPhysicalVolume* physiCollimator;

    G4Tubs*            solidCollimatorTub;
    G4LogicalVolume*   logicCollimatorTub;
    G4VPhysicalVolume* physiCollimatorTub;

  public:
    void SetDetNumber(TString i) { detnumber = std::atoi(i); }
    void SetColNumber(TString i) { colnumber = std::atoi(i); }
    void SetTargetDiameter(G4double i) { target_d = i; }
    void SetTargetRotateAngle(G4double i) { targetRotate = i; }
    void SetCopperThickness(TString i) { m_copper = std::atof(i); }
    void SetAluminumThickness(TString i) { m_aluminum = std::atof(i); }
    void SetWolframThickness(TString i) { m_wolfram = std::atof(i); }
    void SetTubDetector(TString i) { tubdetector = std::atoi(i); }
    void SetTargetPosition(G4ThreeVector pos) { position = pos; }
  private:
    G4int detnumber;
    G4int colnumber;
    G4int tubdetector;
    G4int target_d;
    G4double targetRotate;
    G4float m_copper;
    G4float m_aluminum;
    G4float m_wolfram;
    G4ThreeVector position;
    MocotoDetectorConstructionMessenger* messenger;

};

#endif
