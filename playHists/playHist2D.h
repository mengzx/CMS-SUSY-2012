#ifndef playHist2D_h
#define playHist2D_h

#include <vector>
#include <iostream>
#include <fstream>
#include "TH2D.h"
#include "TLine.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "TCanvas.h"

#include "TStyle.h"

using namespace std;

class playHist2D{

 public:
  playHist2D();
  ~playHist2D(){;}

  TH2D* getHist2D( TFile *f, TString dirname, TString hname);
  vector<unsigned int> getifileidir2D( vector<TFile*> vf, vector<TString> vdirname, TString hname );
  TH2D* getHistInvFandvDir2D( vector<TFile*> vf, vector<TString> vdirname, TString hname );
  TH2D* addHistForDiffFoldersAndFiles2D(vector<TFile*> vf, vector<TString> vdirname, TString hname);
  vector<unsigned int> getifileidirih2D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname );
  TH2D* getHistInvFvDirvH2D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname );
  TH2D* addHistForDiffFoldersFilesHists2D(vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname);
  TH2D* addHistForDiffFoldersAndFiles_SubtrackHists2D(vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname_first, vector<TString> vhname_second);
  vector<TFile*> MCvf_pushback( TString dir, TString sele, TString sTreeThr);
  vector<TFile*> Datavf_pushback( TString dir, TString sele, TString sTreeThr);
  vector<TString> dirName_pushback(TString label, TString sTreeThr);
  vector<TString> vhname_pusback_numer( bool MuAddOrNot, bool fullesti);
  vector<TString> vhname_pusback_data( bool MuAddOrNot, bool fullesti);
  vector<TString> vhname_pusback_domin( bool MuAddOrNot, bool fullesti);
  TH2D* formatHist(TH2D* inh, double inscale, TString digit);
  vector<TH2D*> TranslationFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData);
  vector<TLine*> Lines();
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

}; //class playHist2D

#endif
