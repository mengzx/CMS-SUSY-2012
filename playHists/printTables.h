#ifndef printTables_h
#define printTables_h

#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TH2D.h"
#include "TLine.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "TCanvas.h"
#include "TStyle.h"
#include "vectors.h"

#include "playHist2D.h"

using namespace std;

class printTables: public vectors{
 public:
  printTables();
  ~printTables(){}

  vector<vector<double> > readHist( TH2D* factorh);
  vector<vector<double> > readHist_Err( TH2D* factorh);
  vector<vector<TString> > readHist_WithErr( TH2D* factorh);

  vector<vector<double> > readNumerMCHist( bool MuAddOrNot, bool fullesti, TString HTBin );
  vector<vector<double> > readDominMCHist( bool MuAddOrNot, bool fullesti, TString HTBin );
  vector<vector<double> > readFactorHist( bool MuAddOrNot, bool fullesti, TString HTBin, bool isData );
  vector<vector<double> > readControlDataHist( bool MuAddOrNot, bool fullesti, TString HTBin);
  vector<vector<double> > readYieldDataHist( bool MuAddOrNot, bool fullesti, TString HTBin);
  vector<vector<double> > readPredBGHist( bool MuAddOrNot, bool fullesti, TString HTBin);
  vector<vector<TString> > readNumerMCHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin );
  vector<vector<TString> > readDominMCHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin );
  vector<vector<TString> > readFactorHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, bool isData );
  vector<vector<TString> > readControlDataHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin);
  vector<vector<TString> > readYieldDataHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin);
  vector<vector<TString> > readPredBGHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin);
  void printout_first( FILE *infile, vector<vector<double> > invector, vector<vector<TString> > inString, int digit, int irow, int colum_n, TString firstcol, bool withErr );
  void printout_second( FILE *infile, vector<vector<double> > invector, vector<vector<TString> > inString, int digit, int irow, int colum_f, int colum_n, TString firstcol, bool withErr );
  void printout_final( FILE *infile, vector<vector<double> > invector, vector<vector<TString> > inString, int digit, int irow, int colum_f, int colum_n, TString firstcol, bool withErr );
  void Tables_ForNormal();
  void Tables_ForHadTau();
  //  void Hists();
  void CompareYouAndMe();
  void PredictionOverlay();


};


#endif
