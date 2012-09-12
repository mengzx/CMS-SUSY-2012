#include "NBjets.h"

using namespace std;


NBjets::NBjets(){}

NBjets::Ebsion( vector<TFile*> invf, vector<TString> vdirname ){
  vector<TString> vhname_num;
  vector<TString> vhname_dom;
  vhname.push_back("");
  playHist1D hf1d=playHist1D();
  TH1D *alT=hf1d.addHistForDiffFoldersFilesHists1D(invf, vdirname, vhname, trigeff );

}
