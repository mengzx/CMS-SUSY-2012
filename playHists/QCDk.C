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

TH1D* QCDk::getTailBulk( TString label, TString hname, int startNJet, int nJets, double lowy, double highy, bool HTto1075, TString DataSet) {
  playHist2D hf2d=playHist2D();
  playHist1D hf1d=playHist1D();
  project2DHists pf=project2DHists();
  vector<TFile*> invf;
  TFile *f1=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/"+DataSet+"_PUS0LowHTBinsHadSele275.root");
  TFile *f2=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/"+DataSet+"_PUS0LowHTBinsHadSele325.root");
  TFile *f3=new TFile(inidir_+"rootfiles/hadronicSele"+subdir_+"/"+DataSet+"_PUS0HigHTBinsHadSele.root");
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
  if( HTto1075 ){
  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, 1, "", "" , 275., 1174.9999, 1 );
  return formathT;
  } else {
  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, 1, "", "" , 275., 974.9999, 1 );
  return formathT;
  }
}

void QCDk::getBulkYield( int startNJet, int nJets, double higAT, bool HTto1075, TString DataSet, TString jetmulti ){
  TString hist="";
  TString histW="";
  if( HTto1075 ){
    hist="to1075_";
    histW="to1075";
  } else {
    hist="";
    histW="";
  }
  TH1D *bulk1=getTailBulk( jetmulti+"preselection_", "AlphaT_vs_HT_CommJetgeq2_"+hist+"h_", startNJet, nJets, 0., higAT, HTto1075, DataSet );
  TH1D *weightedht=getTailBulk( jetmulti+"preselection_", "AlphaT_vs_HT_CommJetgeq2_HTWeighted_"+histW+"h_", startNJet, nJets, 0., higAT, HTto1075, DataSet );
  FILE * outputfile;
  char buffer[100];
  if( useBTag_ ){
    if( HTto1075 ) {
      sprintf (buffer, "BulkYield_%s%iTo%ib_AT%.2f_HTto1075_DataSet%s.txt", jetmulti.Data(), startNJet-1, startNJet+nJets-2, higAT, DataSet.Data() );
    } else {
      sprintf (buffer, "BulkYield_%s%iTo%ib_AT%.2f_DataSet%s.txt", jetmulti.Data(), startNJet-1, startNJet+nJets-2, higAT, DataSet.Data() );
    }
  } else {
    if( HTto1075 ) {
      sprintf (buffer, "BulkYield_%iTo%ij_AT%.2f_HTto1075_DataSet%s.txt", startNJet, startNJet+nJets-1, higAT, DataSet.Data() );
    } else {
      sprintf (buffer, "BulkYield_%iTo%ij_AT%.2f_DataSet%s.txt", startNJet, startNJet+nJets-1, higAT, DataSet.Data() );
    }
  }
  outputfile = fopen (buffer,"w");

  //  ofstream outputfile;
  //  outputfile.open ("BulkYield_"+bslices+".txt");

  double HT=375.;
  for( unsigned int i=5; i<15;i++){
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
    } else {
      if ( !HTto1075 && i < 13 ) {
	fprintf(outputfile, "%.0f-%.0f:  Bulk Yied: %f +- %f;   Bulk with HT weighted yield: %f +- %f. \n", HT, HT+100, bulk1->GetBinContent(i), bulk1->GetBinError(i), weightedht->GetBinContent(i), weightedht->GetBinError(i) );
	double num=weightedht->GetBinContent(i);
	double numerr=weightedht->GetBinError(i);
	double dom=bulk1->GetBinContent(i);
	double domerr = bulk1->GetBinError(i);
	double err2=numerr*numerr/dom + num/(dom*dom)*(domerr*domerr);
	fprintf( outputfile, " ==> %.0f-%.0f: Weighted HT (meanHT) %f +- %f. \n\n", HT, HT+100, (weightedht->GetBinContent(i))/(bulk1->GetBinContent(i)), sqrt(err2) );
	HT=HT+100;
      } else if (HTto1075 && i < 15) {
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
  }
  fclose( outputfile );
}

TH1D* QCDk::getRATvsHT( TString label, int startNJet, int nJets, double lowy, double highy, double lowybulk, bool HTto1075, TString DataSet ){
  TH1D *tail=getTailBulk( label, "AlphaT_vs_HT_CommJetgeq2_h_", startNJet, nJets, lowy, highy, HTto1075, DataSet );
  TH1D *bulk=getTailBulk( label, "AlphaT_vs_HT_CommJetgeq2_h_", startNJet, nJets, 0, lowybulk, HTto1075, DataSet );
  TH1D *tailoverbulk=(TH1D*)(tail->Clone("tailoverbulk"));
  tailoverbulk->Divide(tailoverbulk,bulk);
  return tailoverbulk;
}

void QCDk::fitRATvsHT( TString region, int startNJet, int nJets, TString output, bool HTto1075, TString DataSet, TString jetmulti ){
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
  if( region == "B0" ){
    label="";
    lowy=0.50;
    highy=0.51;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "B1" ){
    label="";
    lowy=0.51;
    highy=0.52;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "B2" ){
    label="";
    lowy=0.52;
    highy=0.55;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "Signal" ){
    label="";
    lowy=0.55;
    highy=10;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.55;
    }
  } 

  if( region == "C0" ){
    label="NoMHToverMET_";
    lowy=0.50;
    highy=0.51;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C1" ){
    label="NoMHToverMET_";
    lowy=0.51;
    highy=0.52;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C2" ){
    label="NoMHToverMET_";
    lowy=0.52;
    highy=0.53;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C3" ){
    label="NoMHToverMET_";
    lowy=0.53;
    highy=0.54;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C4" ){
    label="NoMHToverMET_";
    lowy=0.54;
    highy=0.55;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "D" ){
    label="NoMHToverMET_";
    lowy=0.55;
    highy=10.;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=lowy;
    }
  } 

  if( region == "C0_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.50;
    highy=0.51;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C1_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.51;
    highy=0.52;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C2_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.52;
    highy=0.53;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C3_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.53;
    highy=0.54;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "C4_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.54;
    highy=0.55;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=0.5;
    }
  } 

  if( region == "D_ReverseMHToverMHT" ){
    label="ReverseMHToverMET_";
    lowy=0.55;
    highy=10.;
    if( output == "" ){
      lowybulk=lowy;
    } else if( output == "_LowAT0.5") {
      lowybulk=lowy;
    }
  } 

  TH1D *ratio=getRATvsHT(jetmulti+label, startNJet, nJets, lowy, highy, lowybulk, HTto1075, DataSet);
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
  double higfit=975.;
  if( HTto1075 ){ 
    higfit=1175.;
  }
  TF1* fit = new TF1("fit","expo",275.,higfit);
  ratio->Fit(fit,"R");
  ratio->Draw("same");


  FILE * outputfile;
  char buffer[100];
  if(useBTag_){
    if( HTto1075 ) {
      sprintf (buffer, "%s_%s%iTo%ib%s_HTto1075_DataSet%s.txt", region.Data(), jetmulti.Data(), startNJet-1, startNJet+nJets-2, output.Data(), DataSet.Data() );
    } else {
      sprintf (buffer, "%s_%s%iTo%ib%s_DataSet%s.txt", region.Data(), jetmulti.Data(), startNJet-1, startNJet+nJets-2, output.Data(), DataSet.Data() );
    }
  } else {
    if( HTto1075 ) {
      sprintf (buffer, "%s_%iTo%ij%s_HTto1075_DataSet%s.txt", region.Data(), startNJet, startNJet+nJets-1, output.Data(), DataSet.Data() );
    } else {
      sprintf (buffer, "%s_%iTo%ij%s_DataSet%s.txt", region.Data(), startNJet, startNJet+nJets-1, output.Data(), DataSet.Data() );
    }
  }
  outputfile = fopen (buffer,"w");

  //  ofstream outputfile;
  //  outputfile.open (region+"_"+bslices+output+".txt");

  if(useBTag_){
    fprintf(outputfile, "Region: %s, N_jets: %s    N_bjets: %i to %i \n", region.Data(), jetmulti.Data(), startNJet-1, startNJet+nJets-2 );
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
    if( HTto1075 ) {
      c1->SaveAs(Form("%s_%s%iTo%ib%s_HTto1075_DataSet%s.eps", region.Data(), jetmulti.Data(), startNJet-1, startNJet+nJets-2, output.Data(), DataSet.Data() ));
      c1->SaveAs(Form("%s_%s%iTo%ib%s_HTto1075_DataSet%s.png", region.Data(), jetmulti.Data(), startNJet-1, startNJet+nJets-2, output.Data(), DataSet.Data() ));
    } else {
      c1->SaveAs(Form("%s_%s%iTo%ib%s_DataSet%s.eps", region.Data(), jetmulti.Data(), startNJet-1, startNJet+nJets-2, output.Data(), DataSet.Data() ));
      c1->SaveAs(Form("%s_%s%iTo%ib%s_DataSet%s.png", region.Data(), jetmulti.Data(), startNJet-1, startNJet+nJets-2, output.Data(), DataSet.Data() ));
    }
  } else {
    if( HTto1075 ) {
      c1->SaveAs(Form("%s_%iTo%ij%s_HTto1075_DataSet%s.eps", region.Data(), startNJet, startNJet+nJets-1, output.Data(), DataSet.Data() ));
      c1->SaveAs(Form("%s_%iTo%ij%s_HTto1075_DataSet%s.png", region.Data(), startNJet, startNJet+nJets-1, output.Data(), DataSet.Data() ));
    } else {
      c1->SaveAs(Form("%s_%iTo%ij%s_DataSet%s.eps", region.Data(), startNJet, startNJet+nJets-1, output.Data(), DataSet.Data() ));
      c1->SaveAs(Form("%s_%iTo%ij%s_DataSet%s.png", region.Data(), startNJet, startNJet+nJets-1, output.Data(), DataSet.Data() ));
    }
  }
  c1->Update();
  delete c1;
}

void QCDk::getResults( TString output, int startNJet, int nJets, double higAT, bool HTto1075, TString DataSet, TString jetmulti ){

  fitRATvsHT("B0", startNJet, nJets, "", HTto1075, DataSet, jetmulti );
  fitRATvsHT("B1", startNJet, nJets, "", HTto1075, DataSet, jetmulti );
  fitRATvsHT("B2", startNJet, nJets, "", HTto1075, DataSet, jetmulti );
  fitRATvsHT("Signal", startNJet, nJets, "", HTto1075, DataSet, jetmulti );
  /*  fitRATvsHT("C1", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("C2", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("C3", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("C4", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("C5", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("D", startNJet, nJets, "", HTto1075, DataSet );*/
  fitRATvsHT("C0_ReverseMHToverMHT", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("C1_ReverseMHToverMHT", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("C2_ReverseMHToverMHT", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("C3_ReverseMHToverMHT", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("C4_ReverseMHToverMHT", startNJet, nJets, output, HTto1075, DataSet, jetmulti );
  fitRATvsHT("D_ReverseMHToverMHT", startNJet, nJets, "", HTto1075, DataSet, jetmulti );

  getBulkYield(startNJet, nJets, higAT, HTto1075, DataSet, jetmulti);

}
