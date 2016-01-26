//############################################################
//#                         _ooOoo_                          #
//#                        o8888888o                         #
//#                        88" . "88                         #
//#                        (| -_- |)                         #
//#                         O\ = /O                          #
//#                     ____/`---'\____                      #
//#                   .   ' \\| |// `.                       #
//#                    / \\||| : |||// \                     #
//#                  / _||||| -:- |||||- \                   #
//#                    | | \\\ - /// | |                     #
//#                  | \_| ''\---/'' | |                     #
//#                   \ .-\__ `-` ___/-. /                   #
//#                ___`. .' /--.--\ `. . __                  #
//#             ."" '< `.____<|>_/___.' >'"".                #
//#            | | : `- \`.;` _ /`;.`/ - ` : | |             #
//#              \ \ `-. \_ __\ /__ _/ .-` / /               #
//#      ======`-.____`-.___\_____/___.-`____.-'======       #
//#                         `=---='                          #
//#                                                          #
//#      .............................................       #
//#             Buddha bless me, No bug forever              #
//#                                                          #
//############################################################
//# Author       : ZhuHaiWen                                 #
//# Email        : zhuhw@ihep.ac.cn/zhwren0211@whu.edu.cn    #
//# Last modified: 2016-01-05 17:03:1451984603
//# Filename     : MCDataFiles.hh
//# Phone Number : 18625272373                               #
//# Discription  :                                           #
//############################################################
#ifndef MCDATAFILES_H
#define MCDATAFILES_H 1

#include "TFile.h"
#include "TTree.h"

class TString;
class MCDataFiles
{
  public:
    MCDataFiles();
    ~MCDataFiles();

  private:
    TFile*   file;
    TTree*   tree;
    Int_t    nAngles, angleInc;
    Int_t    nHits, Scattering;
    Int_t    number[30];
    Int_t    anglelist;
    TString  filename;
    Float_t* detector;
    Double_t energy[30];

  private:
    void SetBranchAddress(Int_t i);
    void GetEachEvent();

  public:
    void getNAnglesData(Int_t angles = 1000);
    void SaveAs(TString name);
    void getEmptyAndAirData();

};

#endif
