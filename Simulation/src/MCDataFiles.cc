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
//# Last modified: 2016-01-05 17:08:1451984902
//# Filename     : MCDataFiles.cc
//# Phone Number : 18625272373                               #
//# Discription  :                                           #
//############################################################
#include "MCDataFiles.hh"
#include "TString.h"
#include <iostream>
#include <fstream>
using namespace std;

MCDataFiles::MCDataFiles()
{
  anglelist = 0;
}

MCDataFiles::~MCDataFiles()
{
  delete file;
  delete tree;
}

void MCDataFiles::getNAnglesData(Int_t angles)
{
  nAngles  = angles;
  angleInc = 1000/nAngles;
  detector = new Float_t[504*nAngles];
  for(Int_t i=0; i<504*nAngles; i++)
    detector[i] = 0;

  for(Int_t i=0; i<1000; i+=angleInc)
  {
    cout << i << endl;
    this->SetBranchAddress(i);
    this->GetEachEvent();
    anglelist++;
    file->Close();
  }
}

void MCDataFiles::SetBranchAddress(Int_t i)
{
  filename = "/home/zhwren/Workfs/Mocoto/Job/TargetMove/targetRotate_";
  filename += i;
  filename += ".root";
  file = new TFile( filename );
  tree = (TTree*) file->Get("evt");
  tree->SetBranchAddress("nHits", &nHits);
  tree->SetBranchAddress("Scattering", &Scattering);
  tree->SetBranchAddress("HitCrystalNumber", number);
  tree->SetBranchAddress("EnergyHitCrystal", energy);
}

void MCDataFiles::GetEachEvent()
{
  for(Int_t i=0; i<tree->GetEntries(); i++)
  {
    tree->GetEntry(i);
//    if( Scattering == 1 ) continue;
    for(Int_t hit=0; hit<nHits; hit++)
      detector[number[hit]+anglelist*504] += energy[hit];
  }
//    if( detector[i+anglelist*504] == 0)
//      detector[i+anglelist*504] = detector[i+anglelist*504-1];
}

void MCDataFiles::SaveAs(TString name)
{
  ofstream output;
  output.open(name,ios::binary);
  output.write(reinterpret_cast<char*>(detector),sizeof(Float_t)*504*nAngles);
  output.close();
}

void MCDataFiles::getEmptyAndAirData()
{
  nAngles = 1;
  anglelist = 0;
  detector = new Float_t[504];
  memset(detector, 0, sizeof(Float_t)*504);
  this->SaveAs("TargetMove1cm/dark.bin");

  nAngles = 1000;
  detector = new Float_t[504*1000];
  this->SetBranchAddress(1000);
  this->GetEachEvent();
  for(Int_t i=0; i<504*1000; i++)
    detector[i] = detector[i%504];
  this->SaveAs("TargetMove1cm/air.bin");
}
