#ifndef NBjets_h
#define NBjets_h

#include "menus.h"
#include "vectors.h"
#include "TH1D.h"
#include "TString.h"
#include "TFile.h"

class NBjets : public menus, public vectors{
 public:
  NBjets();
  ~NBjets(){;}

  double Ebsion( vector<TFile*> invf, vector<TString> vdirname, int inibin );
  double Im( vector<TFile*> invf, vector<TString> vdirname, int inibin );
  double N_bs( vector<TFile*> invf, vector<TString> vdirname, int inibin );
  double N_bmatch( vector<TFile*> invf, vector<TString> vdirname, int inibin );
  double N_nonbmatch( vector<TFile*> invf, vector<TString> vdirname, int inibin );

  double Nb0( vector<TFile*> invf, vector<TString> vdirname, int inibin );

};//NBjets

#endif
