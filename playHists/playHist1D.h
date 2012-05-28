#ifndef playHist1D_h
#define playHist1D_h

#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>

using namespace std;

class playHist1D{

 public:
  playHist1D();
  ~playHist1D(){;}

  TH1D* getHist1D( TFile *f, TString dirname, TString hname);
  vector<unsigned int> getifileidir1D( vector<TFile*> vf, vector<TString> vdirname, TString hname );
  TH1D* getHistInvFandvDir1D( vector<TFile*> vf, vector<TString> vdirname, TString hname );
  TH1D* addHistForDiffFoldersAndFiles1D(vector<TFile*> vf, vector<TString> vdirname, TString hname);
  vector<unsigned int> getifileidirih1D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname );
  TH1D* getHistInvFvDirvH1D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname );
  TH1D* addHistForDiffFoldersFilesHists1D(vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname);

  TH1D* formatHist( TH1D* inh, double inscale, TString titlex, TString titley, double xlow, double xhigh, int rebin);
  TH1D* MaxHist( vector<TH1D*> vinh);
  vector<TH1D*> SortHists( vector<TH1D*> vinh);
  vector<unsigned int> SortHists_index( vector<TH1D*> vinh);
  vector<TH1D*> invSortHists( vector<TH1D*> vinh);
  vector<unsigned int> invSortHists_index( vector<TH1D*> vinh);
  int MaxHist_index( vector<TH1D*> vinh);

 private:
  int linewidth;
  int markersize;
};

#endif
