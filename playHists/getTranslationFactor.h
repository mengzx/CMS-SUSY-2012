#ifndef getTranslationFactor_h
#define getTranslationFactor_h

#include <vector>
#include <iostream>
#include <fstream>
#include "TH2D.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "menus.h"
#include "vectors.h"

using namespace std;


class getTranslationFactor : public menus, public vectors{
 public:
  getTranslationFactor();
  ~getTranslationFactor(){;}

  vector<TH2D*> TranslationFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData);
  vector<TH2D*> TranslationFactor_iTojJet( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  vector<TH2D*> TranslationFactor_1To2Mu( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData);
  TH2D* getFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  TH2D* getNumerMC( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  TH2D* getDominMC( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  TH2D* getControlData( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  TH2D* getYieldData( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  TH2D* getPredBG( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  void baseCheck( bool MuAddOrNot, bool fullesti, TString HTBins, TString plotname, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  void getResults( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n );
  // private:

}; //class getTranslationFactor

#endif


