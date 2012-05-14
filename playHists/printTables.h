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

class printTables: public vectors, public menus{
 public:
  printTables();
  ~printTables(){}

  vector<vector<double> > readHist( TH2D* factorh);
  vector<vector<double> > readHist_Err( TH2D* factorh);
  vector<vector<TString> > readHist_WithErr( TH2D* factorh, TString digit);

  vector<vector<double> > readNumerMCHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  vector<vector<double> > readDominMCHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  vector<vector<double> > readFactorHist( bool MuAddOrNot, bool fullesti, TString HTBin, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  vector<vector<double> > readControlDataHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  vector<vector<double> > readYieldDataHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  vector<vector<double> > readPredBGHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  vector<vector<TString> > readNumerMCHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit );
  vector<vector<TString> > readDominMCHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit );
  vector<vector<TString> > readFactorHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit );
  vector<vector<TString> > readControlDataHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit );
  vector<vector<TString> > readYieldDataHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit );
  vector<vector<TString> > readPredBGHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit );
  void printout_first( FILE *infile, vector<vector<double> > invector, int digit, int irow, int colum_n, TString firstcol );
  void printout_second( FILE *infile, vector<vector<double> > invector, int digit, int irow, int colum_f, int colum_n, TString firstcol );
  void printout_final( FILE *infile, vector<vector<double> > invector, int digit, int irow, int colum_f, int colum_n, TString firstcol );
  void printout_first_WithErr( FILE *infile, vector<vector<TString> > inString, int digit, int irow, int colum_n, TString firstcol );
  void printout_second_WithErr( FILE *infile, vector<vector<TString> > inString, int digit, int irow, int colum_f, int colum_n, TString firstcol );
  void printout_final_WithErr( FILE *infile, vector<vector<TString> > inString, int digit, int irow, int colum_f, int colum_n, TString firstcol );
  int Tables_ForNormal( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  void Tables_ForHadTau( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  //  void Hists();
  void CompareYouAndMe( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  void PredictionOverlay( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );


};


#endif
