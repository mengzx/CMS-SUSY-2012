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
  TH2D* getFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData);
  TH2D* getNumerMC( bool MuAddOrNot, bool fullesti, TString HTBins );
  TH2D* getDominMC( bool MuAddOrNot, bool fullesti, TString HTBins );
  TH2D* getControlData( bool MuAddOrNot, bool fullesti, TString HTBins );
  TH2D* getYieldData( bool MuAddOrNot, bool fullesti, TString HTBins );
  TH2D* getPredBG( bool MuAddOrNot, bool fullesti, TString HTBins );
  void baseCheck( bool MuAddOrNot, bool fullesti, TString HTBins, TString plotname, bool isData);
  void getResults();
  // private:

}; //class getTranslationFactor

#endif


