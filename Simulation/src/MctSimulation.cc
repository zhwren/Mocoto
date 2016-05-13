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
*    >  File Name   : MctSimulation.cc
*    >  Author      : zhuhaiwen                            *
*    >  mail        : zhwren0211@whu.edu.cn                *
*    >  Created Time: 2016-05-13 10:10                     *
*    >  PhoneNumber : 18625272373                          *
***********************************************************/
#include "MctSimulation.hh"

#include <iostream>
using namespace std;

MctSimulation::MctSimulation(TString rootpath)
{
    path = rootpath;
    mScanData = new Float_t[504*16*1250];
    memset(mScanData, 0, sizeof(Float_t)*504*16*1250);
}

MctSimulation::~MctSimulation()
{
    delete file;
    delete tree;
    delete mScanData;
}

void MctSimulation::Root2Binary(bool sino)
{
    TString filename;
    if( !sino )
    {
	filename  = path + "/Air.root";
	file = new TFile( filename );
	this->AnalysisSingleFile(0);
	return;
    }

    for(Int_t iFile=0; iFile<10; iFile++)
    {
	filename  = path + "/Angle_";
	filename += iFile;
	filename += ".root";
	cout << filename << endl;
	file = new TFile( filename );
	this->AnalysisSingleFile( iFile );
    }
}

void MctSimulation::AnalysisSingleFile(Int_t iFile)
{
    tree = (TTree*)file->Get("evt");
    Int_t nEdep, Scattering, DepositNumber[20];
    Double_t DepositEnergy[20];
    tree->SetBranchAddress("nEdep", &nEdep);
    tree->SetBranchAddress("Scattering", &Scattering);
    tree->SetBranchAddress("DepositNumber", DepositNumber);
    tree->SetBranchAddress("DepositEnergy", DepositEnergy);
    Int_t entries = tree->GetEntries();
    for(Int_t iEvt=0; iEvt<entries; iEvt++)
    {
	tree->GetEntry( iEvt );
	for(Int_t iDep=0; iDep<nEdep; iDep++)
	{
	    mScanData[504*16*iFile + DepositNumber[iDep]] += DepositEnergy[iDep];
	}
    }
    file->Close();
}

Float_t* MctSimulation::GetAirScanImage()
{
    this->Root2Binary( false );
    for(Int_t i=0; i<504*16*1250; i++)
	mScanData[i] = mScanData[i%(504*16)];
    return mScanData;
}

Float_t* MctSimulation::GetScanDataImage()
{
    this->Root2Binary( true );
    return mScanData;
}

Float_t* MctSimulation::GetDarkImage()
{
    mScanData = new Float_t[504*16];
    memset(mScanData, 0, sizeof(Float_t)*504*16);
    return mScanData;
}
