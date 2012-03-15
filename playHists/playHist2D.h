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
  TH2D* formatHist(TH2D* inh, double inscale, TString digit);
  vector<TLine*> Lines();

}; //class playHist2D

#endif
