#include "NBjets.h"

using namespace std;


NBjets::NBjets(){}

double NBjets::Ebsion( vector<TFile*> invf, vector<TString> vdirname, int inibin ){
  vector<TString> vhname_num;
  vectocr<TString> vhname_dom;
  vhname_num.push_back("nJetMatchBPartonAndTagged_CommJetgeq2_h_all");
  vhname_dom.push_back("nJetMatchBParton_CommJetgeq2_h_all");
  playHist2D hf2d=playHist2D();
  TH1D *numh=hf2d.addHistForDiffFoldersFilesHists2D(invf, vdirname, vhname_num, trigeff );
  TH1D *domh=hf2d.addHistForDiffFoldersFilesHists2D(invf, vdirname, vhname_dom, trigeff );

  double num=numh->Integral(1, 20, inibin, 10);
  double dom=domh->Integral(1, 10, inibin, 10);

  double ebsion=num/dom;

  return ebsion;

}

double NBjets::Im( vector<TFile*> invf, vector<TString> vdirname, int inibin ){
  vector<TString> vhname_num;
  vectocr<TString> vhname_dom;
  vhname_num.push_back("nJetMatchNonBPartonAndTagged_CommJetgeq2_h_all");
  vhname_dom.push_back("nJetMatchNonBParton_CommJetgeq2_h_all");
  playHist2D hf2d=playHist2D();
  TH1D *numh=hf2d.addHistForDiffFoldersFilesHists2D(invf, vdirname, vhname_num, trigeff );
  TH1D *domh=hf2d.addHistForDiffFoldersFilesHists2D(invf, vdirname, vhname_dom, trigeff );

  double num=numh->Integral(1, 20, inibin, 10);
  double dom=domh->Integral(1, 10, inibin, 10);

  double im=num/dom;

  return im;
}


double NBjets::N_bs( vector<TFile*> invf, vector<TString> vdirname, int inibin ){

  vector<TString> vhname_num;
  vhname_num.push_back("njet_CommJetgeq2_h_all");
  playHist2D hf2d=playHist2D();
  TH1D *numh=hf2d.addHistForDiffFoldersFilesHists2D(invf, vdirname, vhname_num, trigeff );

  double num=numh->Integral(1, 20, inibin, 10);

  return num;
}

double NBjets::N_bmatch( vector<TFile*> invf, vector<TString> vdirname, int inibin ){

  vector<TString> vhname_num;
  vhname_num.push_back("nJetMatchBParton_CommJetgeq2_h_all");
  playHist2D hf2d=playHist2D();
  TH1D *numh=hf2d.addHistForDiffFoldersFilesHists2D(invf, vdirname, vhname_num, trigeff );

  double num=numh->Integral(1, 20, inibin, 10);

  return num;
}

double NBjets::N_nonbmatch( vector<TFile*> invf, vector<TString> vdirname, int inibin ){

  vector<TString> vhname_num;
  vhname_num.push_back("nJetMatchNonBParton_CommJetgeq2_h_all");
  playHist2D hf2d=playHist2D();
  TH1D *numh=hf2d.addHistForDiffFoldersFilesHists2D(invf, vdirname, vhname_num, trigeff );

  double num=numh->Integral(1, 20, inibin, 10);

  return num;
}


double NBjets::nb0( vector<TFile*> invf, vector<TString> vdirname, int inibin ){

  double ebsion=Ebsion( invf, vdirname, inibin );
  double im=Im( invf, vdirname, inibin );
  double n_bs=N_bs( invf, vdirname, inibin );
  double n_bmatch=N_bmatch( invf, vdirname, inibin );
  double n_nonbmatch=N_nonbmatch( invf, vdirname, inibin );

nb0=
}

