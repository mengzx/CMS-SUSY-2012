#include "QCDk.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TF1.h"
#include "TH2D.h"
#include "TLine.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include "TLegend.h"

#include "tdrstyle.h"
#include "playHist2D.h"
#include "playHist1D.h"
#include "project2DHists.h"
#include "getTranslationFactor.h"
#include "THStack.h"
#include "menus.h"

using namespace std;

QCDk::QCDk(){}

TH1D* QCDk::getTailBulk( TString label, TString bslices, double lowy, double highy ) {
  playHist2D hf2d=playHist2D();
  playHist1D hf1d=playHist1D();
  project2DHists pf=project2DHists();
  vector<TFile*> invf;
  TFile *f1=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/DataJetHT2012_PUS0LowHTBinsHadSele275QCDkgood.root");
  TFile *f2=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/DataJetHT2012_PUS0LowHTBinsHadSele325QCDkgood.root");
  TFile *f3=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/DataJetHT2012_PUS0HigHTBinsHadSeleQCDkgood.root");
  invf.push_back(f1);
  invf.push_back(f2);
  invf.push_back(f3);
  vector<TString> vdirname;
  vdirname.push_back(label+"275_325");
  vdirname.push_back(label+"325_375");
  vdirname.push_back(label+"375_475");
  vdirname.push_back(label+"475_575");
  vector<TString> vhname;
  vhname.push_back("AlphaT_vs_HT_CommJetgeq2_h_"+bslices);
  vector<double> nominaltrigeff=nominaltrigeff_pushback("all");
  TH2D* hT=hf2d.addHistForDiffFoldersFilesHists2D( invf, vdirname, vhname, nominaltrigeff );
  TH1D* hTalphaTSlices=pf.projectX( hT, lowy, highy );

  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, 1, "", "" , 275., 574.9999, 1 );

  return formathT;
}

TH1D* QCDk::getRATvsHT( TString label, TString bslices, double lowy, double highy ){
  TH1D *tail=getTailBulk( label, bslices, lowy, highy );
  TH1D *bulk=getTailBulk( label, bslices, 0, lowy );

  TH1D *tailoverbulk=(TH1D*)(tail->Clone("tailoverbulk"));
  tailoverbulk->Divide(tailoverbulk,bulk);
  return tailoverbulk;
}

void QCDk::fitRATvsHT( TString region, TString bslices ){
  TCanvas *c1=new TCanvas("c1","c1",1);
  TPad *pad1=new TPad("pad1","",0,0,1,1);
  pad1->Draw();
  pad1->cd();
  pad1->SetLeftMargin(0.25);

  TString label="";
  double lowy=0.;
  double highy=0.;
  if( region == "B" ){
    label="";
    lowy=0.52;
    highy=0.55;
  } 

  if( region == "C1" ){
    label="NoMHToverMET_";
    lowy=0.54;
    highy=0.55;
  } 

  if( region == "C2" ){
    label="NoMHToverMET_";
    lowy=0.53;
    highy=0.54;
  } 

  if( region == "C3" ){
    label="NoMHToverMET_";
    lowy=0.52;
    highy=0.53;
  } 

  TH1D *ratio=getRATvsHT(label, bslices, lowy, highy);
  ratio->SetLineColor(1);
  ratio->GetXaxis()->SetTitle("H_{T} (GeV)");
  ratio->GetYaxis()->SetTitle("R_{#alpha_{T}}");
  ratio->GetYaxis()->SetTitleOffset(2.2);
  TF1* fit = new TF1("fit","expo",275.,575.);
  ratio->Fit(fit,"R");
  ratio->Draw("same");

  ofstream outputfile;

  outputfile.open (region+"_"+bslices+".txt");

  outputfile<< "Region: "<<region<<"  N_bjets: "<< bslices<<endl;
  outputfile << " A: " << fit->GetParameter(0)
	     << "     A error: " << fit->GetParError(0) <<endl;
  outputfile << " k: " << fit->GetParameter(1)
	     << "     k error: " << fit->GetParError(1) <<endl;
  outputfile << " chi2: " << fit->GetChisquare() <<endl;
  outputfile << " ndof: " << fit->GetNDF() <<endl;
  outputfile << " p-value: " << fit->GetProb() <<endl;
  outputfile<<endl;
  outputfile<<endl;
  ratio->Draw("e1");
  c1->SaveAs(region+"_"+bslices+".eps");
  c1->Update();
  delete c1;
}

void QCDk::getResults( ){
  fitRATvsHT("B","all");
  fitRATvsHT("C1","all");
  fitRATvsHT("C2","all");
  fitRATvsHT("C3","all");
}
