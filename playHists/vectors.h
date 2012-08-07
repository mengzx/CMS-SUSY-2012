#ifndef vectors_h
#define vectors_h

#include "TH2D.h"
#include "TFile.h"
#include "TString.h"
#include "menus.h"
#include <iostream>
#include <vector>

using namespace std;

class vectors{
 public:
  vectors();
  ~vectors(){

    for (unsigned int index=0; index<vf_save.size(); ++index){
      delete vf_save[index];
    }

   for (unsigned int index=0; index<vfdata_save.size(); ++index){
      delete vfdata_save[index];
    }

   for (unsigned int index=0; index<vfdata.size(); ++index){
      vfdata[index]->Close();
      delete vfdata[index];
   }
   vfdata.clear();
   for (unsigned int index=0; index<vf.size(); ++index){
      vf[index]->Close();
      delete vf[index];
    }
   vf.clear();
  }

  void closefV();

  vector<double> xbinsv;
  vector<double> ybinsv;
  int nxbins;
  int nybins;

  TH2D* ZinvPredBG();
  TH2D* NormalWJPredBG();
  TH2D* HT_ATTrigEff();
  TH2D* SingleMuTrigEff();

  vector<TFile*> MCvf_pushback( TString dir, TString dataset, TString sele, TString sTreeThr, bool separateSample, TString separateSampleName );
  vector<TFile*> Datavf_pushback( TString dir, TString dataset, TString sele, TString sTreeThr);
  vector<TString> dirName_pushback(TString label, TString sTreeThr);
  vector<TString> vhname_pusback_numer( bool MuAddOrNot, bool fullesti, int startnjet, int njets);
  vector<TString> vhname_pusback_data( bool MuAddOrNot, bool fullesti, int startnjet, int njets);
  vector<TString> vhname_pusback_domin( bool MuAddOrNot, bool fullesti, int startnjet, int njets);
  vector<double> DiMuTrigEff_pushback(TString sTreeThr);
  vector<double> SingleMuTrigEff_pushback(TString sTreeThr);
  vector<double> HTATTrigEff_pushback(TString sTreeThr);
  vector<double> nominaltrigeff_pushback(TString sTreeThr);

  vector<TFile*> vf;
  vector<TFile*> vfdata;
  vector<TFile*> vf_save;
  vector<TFile*> vfdata_save;
}; //end vectors
#endif
