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
#include "TMath.h"
#include "math.h"
#include "tdrstyle.h"
#include "playHist2D.h"
#include "playHist1D.h"
#include "project2DHists.h"
#include "getTranslationFactor.h"
#include "THStack.h"
#include "menus.h"

using namespace std;

QCDk::QCDk(){}

TH1D* QCDk::getTailBulk( TString label, TString hname, TString bslices, double lowy, double highy ) {
  playHist2D hf2d=playHist2D();
  playHist1D hf1d=playHist1D();
  project2DHists pf=project2DHists();
  vector<TFile*> invf;
  TFile *f1=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/DataJetHT2012_PUS0LowHTBinsHadSele275.root");
  TFile *f2=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/DataJetHT2012_PUS0LowHTBinsHadSele325.root");
  TFile *f3=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/DataJetHT2012_PUS0HigHTBinsHadSele.root");
  invf.push_back(f1);
  invf.push_back(f2);
  invf.push_back(f3);
  vector<TString> vdirname;
  vdirname.push_back(label+"275_325");
  vdirname.push_back(label+"325_375");
  vdirname.push_back(label+"375_475");
  vdirname.push_back(label+"475_575");
  vdirname.push_back(label+"575_675");
  vdirname.push_back(label+"675_775");
  vdirname.push_back(label+"775_875");
  vdirname.push_back(label+"875");
  vector<TString> vhname;
  vhname.push_back(hname+bslices);
  vector<double> nominaltrigeff=nominaltrigeff_pushback("all");
  TH2D* hT=hf2d.addHistForDiffFoldersFilesHists2D( invf, vdirname, vhname, nominaltrigeff );
  TH1D* hTalphaTSlices=pf.projectX( hT, lowy, highy );

  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, 1, "", "" , 275., 574.9999, 1 );

  return formathT;
}

void QCDk::getBulkYield( TString bslices ){
  TH1D *bulk1=getTailBulk( "preselection_", "AlphaT_vs_HT_CommJetgeq2_h_", bslices, 0, 0.55 );
  TH1D *weightedht=getTailBulk( "preselection_", "AlphaT_vs_HT_CommJetgeq2_HTWeighted_h_", bslices, 0, 0.55 );

  ofstream outputfile;
  outputfile.open ("BulkYield_"+bslices+".txt");

  double HT=375.;
  for( unsigned int i=5; i<13;i++){
    if( i == 5){
      outputfile<<"275-325: "<<" Bulk Yied: " <<bulk1->GetBinContent(i)<<" +- "<<bulk1->GetBinError(i)<<"   Bulk with HT weighted yield: "<<weightedht->GetBinContent(i)<<" +- "<<weightedht->GetBinError(i)<<endl;
      double num=weightedht->GetBinContent(i);
      double numerr=weightedht->GetBinError(i);
      double dom=bulk1->GetBinContent(i);
      double domerr = bulk1->GetBinError(i);
      double err2=numerr*numerr/dom + num/(dom*dom)*(domerr*domerr);
      outputfile<<" ==> 275-325: Weighted HT (meanHT)"<< (weightedht->GetBinContent(i))/(bulk1->GetBinContent(i))<<" +- "<< sqrt(err2)<<endl;
      outputfile<<endl;
      outputfile<<endl;
    } else if( i == 6){
      outputfile<<"325-375: "<<" Bulk Yied: " <<bulk1->GetBinContent(i)<<" +- "<<bulk1->GetBinError(i)<<"   Bulk with HT weighted yield: "<<weightedht->GetBinContent(i)<<" +- "<<weightedht->GetBinError(i)<<endl;
      double num=weightedht->GetBinContent(i);
      double numerr=weightedht->GetBinError(i);
      double dom=bulk1->GetBinContent(i);
      double domerr = bulk1->GetBinError(i);
      double err2=numerr*numerr/dom + num/(dom*dom)*(domerr*domerr);
      outputfile<<" ==> 325-375: Weighted HT (meanHT)"<< (weightedht->GetBinContent(i))/(bulk1->GetBinContent(i))<<" +- "<< sqrt(err2)<<endl;
      outputfile<<endl;
      outputfile<<endl;
    } else{
      outputfile<<HT<<"-"<<HT+100<<": "<<" Bulk Yied: " <<bulk1->GetBinContent(i)<<" +- "<<bulk1->GetBinError(i)<<"   Bulk with HT weighted yield: "<<weightedht->GetBinContent(i)<<" +- "<<weightedht->GetBinError(i)<<endl;
      double num=weightedht->GetBinContent(i);
      double numerr=weightedht->GetBinError(i);
      double dom=bulk1->GetBinContent(i);
      double domerr = bulk1->GetBinError(i);
      double err2=numerr*numerr/dom + num/(dom*dom)*(domerr*domerr);
      outputfile<<" ==> "<<HT<<"-"<<HT+100<<": Weighted HT (meanHT)"<< (weightedht->GetBinContent(i))/(bulk1->GetBinContent(i))<<" +- "<< sqrt(err2)<<endl;
      outputfile<<endl;
      outputfile<<endl;
      HT=HT+100;
    }
  }
  outputfile.close();
}

TH1D* QCDk::getRATvsHT( TString label, TString bslices, double lowy, double highy ){
  TH1D *tail=getTailBulk( label, "AlphaT_vs_HT_CommJetgeq2_h_", bslices, lowy, highy );
  TH1D *bulk=getTailBulk( label, "AlphaT_vs_HT_CommJetgeq2_h_", bslices, 0, lowy );
  TH1D *tailoverbulk=(TH1D*)(tail->Clone("tailoverbulk"));
  tailoverbulk->Divide(tailoverbulk,bulk);
  return tailoverbulk;
}

void QCDk::fitRATvsHT( TString region, TString bslices ){
  TCanvas *c1=new TCanvas("c1","c1",600,700);
  TPad *pad1=new TPad("pad1","",0,0,1,1);
  pad1->Draw();
  pad1->cd();
  pad1->SetLeftMargin(0.2);
  pad1->SetTopMargin(0.06);
  pad1->SetBottomMargin(0.1);
  pad1->SetRightMargin(0.04);
  pad1->SetTickx();

  TString label="";
  double lowy=0.;
  double highy=0.;
  //  TString output="_LowAT0.5";
  TString output="";
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

  if( region == "C1_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.54;
    highy=0.55;
  } 

  if( region == "C2_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.53;
    highy=0.54;
  } 

  if( region == "C3_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.52;
    highy=0.53;
  } 

  TH1D *ratio=getRATvsHT(label, bslices, lowy, highy);
  ratio->SetLineColor(1);
  ratio->GetXaxis()->SetTitle("H_{T} (GeV)");
  ratio->GetYaxis()->SetTitle("R_{#alpha_{T}}");
  ratio->SetMinimum(0);
  ratio->GetYaxis()->SetTitleOffset(1.8);
  ratio->GetYaxis()->SetLabelSize(19);
  ratio->GetYaxis()->SetTitleSize(0.05);
  ratio->GetXaxis()->SetLabelSize(19);
  ratio->GetXaxis()->SetLabelFont(63);
  ratio->GetYaxis()->SetLabelFont(63);

  TF1* fit = new TF1("fit","expo",275.,575.);
  ratio->Fit(fit,"R");
  ratio->Draw("same");

  ofstream outputfile;

  outputfile.open (region+"_"+bslices+output+".txt");

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
  outputfile.close();
  ratio->Draw("e1");
  c1->SaveAs(region+"_"+bslices+output+".eps");
  c1->SaveAs(region+"_"+bslices+output+".png");
  c1->Update();
  delete c1;
}

void QCDk::getResults( ){
  fitRATvsHT("B","all");
  fitRATvsHT("C1","all");
  fitRATvsHT("C2","all");
  fitRATvsHT("C3","all");
  fitRATvsHT("C1_ReverseMHToverMHT","all");
  fitRATvsHT("C2_ReverseMHToverMHT","all");
  fitRATvsHT("C3_ReverseMHToverMHT","all");
  getBulkYield("all");

}
