#ifndef getTranslationFactor_h
#define getTranslationFactor_h

#include <vector>
#include <iostream>
#include <fstream>
#include "TH2D.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>

using namespace std;


class getTranslationFactor{
 public:
  getTranslationFactor();
  ~getTranslationFactor(){;}

  vector<TFile*> MCvf_pushback( TString dir, TString sele, TString sTreeThr);
  vector<TFile*> Datavf_pushback( TString dir, TString sele, TString sTreeThr);
  vector<TString> dirName_pushback(TString label, TString sTreeThr);
  vector<TString> vhname_pusback_numer( bool MuAddOrNot, bool fullesti);
  vector<TString> vhname_pusback_data( bool MuAddOrNot, bool fullesti);
  vector<TString> vhname_pusback_domin( bool MuAddOrNot, bool fullesti);
  vector<TH2D*> TranslationFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData);
  TH2D* getFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData);
  TH2D* getControlData( bool MuAddOrNot, bool fullesti, TString HTBins );
  TH2D* getYieldData( bool MuAddOrNot, bool fullesti, TString HTBins );
  TH2D* getPredBG( bool MuAddOrNot, bool fullesti, TString HTBins );
  void baseCheck( bool MuAddOrNot, bool fullesti, TString HTBins, TString plotname, bool isData);
  void getResults();
 private:
  double scale_;
  TString digit1_;
  TString digit2_;
  TString inidir_;
  TString subdir_;
  TString folderlabel_;
  TString dataset_;

}; //class getTranslationFactor

#endif


