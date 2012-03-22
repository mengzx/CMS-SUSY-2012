#ifndef basicPlots_h
#define basicPlots_h

#include "TH1D.h"
#include "TString.h"
#include "TFile.h"

#include <vector>

using namespace std;

class basicPlots{
 public:
  basicPlots();
  ~basicPlots(){;}

  TH1D* AlphaT( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin );
  TH1D* HT( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin, double lowalphaT, double highalphaT );
  void DrawHists( bool MuAddOrNot, TString HTBins, int whichpart, TString whichplot, int rebin, double lowalphaT, double highalphaT );
  void getResults();

 private:
  TString inidir_;
  TString subdir_;
  TString folderlabel_;
  TString dataset_;
  double scale_;
  double datascale_;
  double mcscale_;
};
#endif
