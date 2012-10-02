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

TH1D* QCDk::getTailBulk( TString label, TString hname, int startNJet, int nJets, double lowy, double highy ) {
  playHist2D hf2d=playHist2D();
  playHist1D hf1d=playHist1D();
  project2DHists pf=project2DHists();
  vector<TFile*> invf;
  TFile *f1=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/"+JetHTDataset_+"_PUS0LowHTBinsHadSele275.root");
  TFile *f2=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/"+JetHTDataset_+"_PUS0LowHTBinsHadSele325.root");
  TFile *f3=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/"+JetHTDataset_+"_PUS0HigHTBinsHadSele.root");
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
  if( startNJet == 0 ){
    vhname.push_back(hname+"all" );
      cout<<hname+"all"<<endl;
  } else {
    for( int i=startNJet; i< startNJet+nJets; i++){
      cout<<Form( "%s%i", hname.Data(), i )<<endl;
      vhname.push_back(Form( "%s%i", hname.Data(), i ) );
    }
  }
  vector<double> nominaltrigeff=nominaltrigeff_pushback("all");
  TH2D* hT=hf2d.addHistForDiffFoldersFilesHists2D( invf, vdirname, vhname, nominaltrigeff );
  TH1D* hTalphaTSlices=pf.projectX( hT, lowy, highy );

  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, 1, "", "" , 275., 574.9999, 1 );

  return formathT;
}

void QCDk::getBulkYield( int startNJet, int nJets, double higAT ){
  TH1D *bulk1=getTailBulk( "preselection_", "AlphaT_vs_HT_CommJetgeq2_h_", startNJet, nJets, 0., higAT );
  TH1D *weightedht=getTailBulk( "preselection_", "AlphaT_vs_HT_CommJetgeq2_HTWeighted_h_", startNJet, nJets, 0., higAT );

  FILE * outputfile;
  char buffer[100];
  if( useBTag_ ){
    sprintf (buffer, "BulkYield_%iTo%ib_AT%.2f.txt", startNJet-1, startNJet+nJets-2, higAT );
  } else {
    sprintf (buffer, "BulkYield_%iTo%ij_AT%.2f.txt", startNJet, startNJet+nJets-1, higAT );
  }
  outputfile = fopen (buffer,"w");

  //  ofstream outputfile;
  //  outputfile.open ("BulkYield_"+bslices+".txt");

  double HT=375.;
  for( unsigned int i=5; i<13;i++){
    if( i == 5){
      fprintf(outputfile, "275-325:  Bulk Yied: %f +- %f;   Bulk with HT weighted yield: %f +- %f. \n", bulk1->GetBinContent(i), bulk1->GetBinError(i), weightedht->GetBinContent(i), weightedht->GetBinError(i) );
      double num=weightedht->GetBinContent(i);
      double numerr=weightedht->GetBinError(i);
      double dom=bulk1->GetBinContent(i);
      double domerr = bulk1->GetBinError(i);
      double err2=numerr*numerr/dom + num/(dom*dom)*(domerr*domerr);
      fprintf( outputfile, " ==> 275-325: Weighted HT (meanHT) %f +- %f. \n\n",  (weightedht->GetBinContent(i))/(bulk1->GetBinContent(i)), sqrt(err2) );
    } else if( i == 6){
      fprintf(outputfile, "325-375:  Bulk Yied: %f +- %f;   Bulk with HT weighted yield: %f +- %f. \n", bulk1->GetBinContent(i), bulk1->GetBinError(i), weightedht->GetBinContent(i), weightedht->GetBinError(i) );
      double num=weightedht->GetBinContent(i);
      double numerr=weightedht->GetBinError(i);
      double dom=bulk1->GetBinContent(i);
      double domerr = bulk1->GetBinError(i);
      double err2=numerr*numerr/dom + num/(dom*dom)*(domerr*domerr);
      fprintf( outputfile, " ==> 325-375: Weighted HT (meanHT) %f +- %f. \n\n",  (weightedht->GetBinContent(i))/(bulk1->GetBinContent(i)), sqrt(err2) );
    } else{
      fprintf(outputfile, "%.0f-%.0f:  Bulk Yied: %f +- %f;   Bulk with HT weighted yield: %f +- %f. \n", HT, HT+100, bulk1->GetBinContent(i), bulk1->GetBinError(i), weightedht->GetBinContent(i), weightedht->GetBinError(i) );
      double num=weightedht->GetBinContent(i);
      double numerr=weightedht->GetBinError(i);
      double dom=bulk1->GetBinContent(i);
      double domerr = bulk1->GetBinError(i);
      double err2=numerr*numerr/dom + num/(dom*dom)*(domerr*domerr);
      fprintf( outputfile, " ==> %.0f-%.0f: Weighted HT (meanHT) %f +- %f. \n\n", HT, HT+100, (weightedht->GetBinContent(i))/(bulk1->GetBinContent(i)), sqrt(err2) );
      HT=HT+100;
    }
  }
  fclose( outputfile );
}

TH1D* QCDk::getRATvsHT( TString label, int startNJet, int nJets, double lowy, double highy, double lowybulk ){
  TH1D *tail=getTailBulk( label, "AlphaT_vs_HT_CommJetgeq2_h_", startNJet, nJets, lowy, highy );
  TH1D *bulk=getTailBulk( label, "AlphaT_vs_HT_CommJetgeq2_h_", startNJet, nJets, 0, lowybulk );
  TH1D *tailoverbulk=(TH1D*)(tail->Clone("tailoverbulk"));
  tailoverbulk->Divide(tailoverbulk,bulk);
  return tailoverbulk;
}

void QCDk::fitRATvsHT( TString region, int startNJet, int nJets, TString output, double higAT ){
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
  double lowybulk=0.;
  //  TString output="_LowAT0.5";
  //  TString output="";
  if( region == "B" ){
    label="";
    lowy=0.52;
    highy=0.55;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C1" ){
    label="NoMHToverMET_";
    lowy=0.54;
    highy=0.55;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C2" ){
    label="NoMHToverMET_";
    lowy=0.53;
    highy=0.54;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C3" ){
    label="NoMHToverMET_";
    lowy=0.52;
    highy=0.53;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C1_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.54;
    highy=0.55;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C2_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.53;
    highy=0.54;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C3_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.52;
    highy=0.53;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  TH1D *ratio=getRATvsHT(label, startNJet, nJets, lowy, highy, lowybulk);
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


  FILE * outputfile;
  char buffer[100];
  if(useBTag_){
    sprintf (buffer, "%s_%iTo%ib%s_bulkAT%.2f.txt", region.Data(), startNJet-1, startNJet+nJets-2, output.Data(), higAT);
  } else {
    sprintf (buffer, "%s_%iTo%ij%s_bulkAT%.2f.txt", region.Data(), startNJet, startNJet+nJets-1, output.Data(), higAT);
  }
  outputfile = fopen (buffer,"w");

  //  ofstream outputfile;
  //  outputfile.open (region+"_"+bslices+output+".txt");

  if(useBTag_){
    fprintf(outputfile, "Region: %s    N_bjets: %i to %i \n", region.Data(), startNJet-1, startNJet+nJets-2 );
  } else {
    fprintf(outputfile, "Region: %s    N_jets: %i to %i \n", region.Data(), startNJet, startNJet+nJets-1 );
  }
  fprintf(outputfile, " A: %f \n", fit->GetParameter(0) );
  fprintf(outputfile, "     A error: %f \n", fit->GetParError(0) );
  fprintf(outputfile, " k: %f \n", fit->GetParameter(1) );
  fprintf(outputfile, "     k error: %f \n", fit->GetParError(1) );
  fprintf(outputfile, " chi2: %f\n", fit->GetChisquare() );
  fprintf(outputfile, " ndof: %i\n", fit->GetNDF() );
  fprintf(outputfile, " p-value: %f\n", fit->GetProb() );
  fprintf(outputfile, "\n\n");
  fclose(outputfile);
  ratio->Draw("e1");
  if( useBTag_){
    c1->SaveAs(Form("%s_%iTo%ib%s_bulkAT%.2f.eps", region.Data(), startNJet-1, startNJet+nJets-2, output.Data(), higAT));
    c1->SaveAs(Form("%s_%iTo%ib%s_bulkAT%.2f.png", region.Data(), startNJet-1, startNJet+nJets-2, output.Data(), higAT));
  } else {
    c1->SaveAs(Form("%s_%iTo%ij%s_bulkAT%.2f.eps", region.Data(), startNJet, startNJet+nJets-1, output.Data(), higAT));
    c1->SaveAs(Form("%s_%iTo%ij%s_bulkAT%.2f.png", region.Data(), startNJet, startNJet+nJets-1, output.Data(), higAT));
  }
  c1->Update();
  delete c1;
}

void QCDk::getResults( TString output, int startNJet, int nJets, double higAT ){

  fitRATvsHT("B", startNJet, nJets, output, higAT);
  fitRATvsHT("C1", startNJet, nJets, output, higAT);
  fitRATvsHT("C2", startNJet, nJets, output, higAT);
  fitRATvsHT("C3", startNJet, nJets, output, higAT);
  fitRATvsHT("C1_ReverseMHToverMHT", startNJet, nJets, output, higAT);
  fitRATvsHT("C2_ReverseMHToverMHT", startNJet, nJets, output, higAT);
  fitRATvsHT("C3_ReverseMHToverMHT", startNJet, nJets, output, higAT);

  getBulkYield(startNJet, nJets, higAT);

}
