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
*    >  CopyRight   :                                      *
*    >  File Name   : MctSimulation.hh
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-05-13 10:08                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#ifndef MctSimulation_h
#define MctSimulation_h 1

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

class MctSimulation
{
    private:
        TFile* file;
        TTree* tree;
	TString path;
	Float_t* mScanData;
  
    public:
        MctSimulation(TString);
        ~MctSimulation();
	Float_t* GetScanDataImage();
	Float_t* GetAirScanImage();
	Float_t* GetDarkImage();

    private:
        void Root2Binary(bool sino=true);
	void AnalysisSingleFile(Int_t);
};

#endif
