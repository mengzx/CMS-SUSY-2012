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

  vector<TH2D*> TranslationFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, TString MuonNumber, int StartNJet, int NJet );
  vector<TH2D*> TranslationFactor_iTojJet( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber );
  vector<TH2D*> TranslationFactor_1To2Mu( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, int StartNJet, int nJets );
  vector<TH2D*> TranslationFactor_AT( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, int startNJet, int nJets, TString MuonNumber, TString closuretestformat );
  TH2D* getFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJet );
  TH2D* getNumerMC( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJet );
  TH2D* getDominMC( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJet );
  TH2D* getControlData( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJet );
  TH2D* getYieldData( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJet );
  TH2D* getPredBG( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJet );
  void baseCheck( bool MuAddOrNot, bool fullesti, TString HTBins, TString plotname, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJet );
  void getResults( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJet );
  // private:

}; //class getTranslationFactor

#endif


