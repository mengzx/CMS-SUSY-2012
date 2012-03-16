#include "getTranslationFactor.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TH2D.h"
#include "TLine.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "TCanvas.h"
#include "TStyle.h"

#include "tdrstyle.h"
#include "playHist2D.h"

using namespace std;


getTranslationFactor::getTranslationFactor():
  scale_(1.),
  digit1_(".1f"),
  digit2_(".2f"),
  inidir_("/Users/zmeng/Work_CMS/SUSY/myppt/BGEstimation_16022012/"),
  subdir_("/geq2jets")
{}



// -----------------------------------------------------------------------------
//
vector<TFile*> getTranslationFactor::MCvf_pushback( TString dir, TString sele, TString sTreeThr){

  vector<TFile*> vf;

  if( sTreeThr == "100"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_PUS4HigHTBins"+sele+".root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "86"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBins"+sele+"325.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"325.root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "73"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"275.root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "all"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"275.root");
    TFile *f3=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBins"+sele+"325.root");
    TFile *f4=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"325.root");
    TFile *f5=new TFile(dir+"/"+"NoSmearALL_PUS4HigHTBins"+sele+".root");
    TFile *f6=new TFile(dir+"/"+"NoSmearDiBoson_PUS6HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f3);
    vf.push_back(f4);
    vf.push_back(f5);
    vf.push_back(f6);
  }

  return vf;
}

vector<TFile*> getTranslationFactor::Datavf_pushback( TString dir, TString sele, TString sTreeThr){

  vector<TFile*> vf;

  if( sTreeThr == "100"){
    TFile *f1=new TFile(dir+"/"+"Data2011AB_PUS0HigHTBins"+sele+".root");
    vf.push_back(f1);
  } else if( sTreeThr == "86"){
    TFile *f1=new TFile(dir+"/"+"Data2011AB_PUS0LowHTBins"+sele+"325.root");
    vf.push_back(f1);
  } else if( sTreeThr == "73"){
    TFile *f1=new TFile(dir+"/"+"Data2011AB_PUS0LowHTBins"+sele+"275.root");
    vf.push_back(f1);
  } else if( sTreeThr == "all"){
    TFile *f1=new TFile(dir+"/"+"Data2011AB_PUS0LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"Data2011AB_PUS0LowHTBins"+sele+"325.root");
    TFile *f3=new TFile(dir+"/"+"Data2011AB_PUS0HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f3);
  }

  return vf;
}


vector<TString> getTranslationFactor::dirName_pushback(TString label, TString sTreeThr){
  vector<TString> dirname;

  if( sTreeThr == "100" ){
    dirname.push_back(label+"375_475");
    dirname.push_back(label+"475_575");
    dirname.push_back(label+"575_675");
    dirname.push_back(label+"675_775");
    dirname.push_back(label+"775_875");
    dirname.push_back(label+"875");
  } else if ( sTreeThr == "86" ){
    dirname.push_back(label+"325_375");
  } else if ( sTreeThr == "73" ){
    dirname.push_back(label+"275_325");
  } else if ( sTreeThr == "all"){
    dirname.push_back(label+"275_325");
    dirname.push_back(label+"325_375");
    dirname.push_back(label+"375_475");
    dirname.push_back(label+"475_575");
    dirname.push_back(label+"575_675");
    dirname.push_back(label+"675_775");
    dirname.push_back(label+"775_875");
    dirname.push_back(label+"875");
  }
  return dirname;
}

vector<TString> getTranslationFactor::vhname_pusback_numer( bool MuAddOrNot, bool fullesti){
  vector<TString> reh;
  if( MuAddOrNot == true && ( fullesti == true || fullesti == false) ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_all");
  } else if ( MuAddOrNot == false && fullesti == true ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_all");
  } else if ( MuAddOrNot == false && fullesti == false ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_all");
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueVlep_h_all");
  }
  return reh;
}

vector<TString> getTranslationFactor::vhname_pusback_data( bool MuAddOrNot, bool fullesti){
  vector<TString> reh;
  if( MuAddOrNot == true && ( fullesti == true || fullesti == false) ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
  } else if ( MuAddOrNot == false && fullesti == true ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_15");
  } else if ( MuAddOrNot == false && fullesti == false ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
  }
  return reh;
}

vector<TString> getTranslationFactor::vhname_pusback_domin( bool MuAddOrNot, bool fullesti){
  vector<TString> reh;
  if( MuAddOrNot == true ){
    reh.push_back("AlphaT_vs_HTTakeMu_JetMugeq2_h_all");
  } else if ( MuAddOrNot == false && fullesti == true ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
  } else if ( MuAddOrNot == false && fullesti == false ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
  }
  return reh;
}

// -----------------------------------------------------------------------------
//
vector<TH2D*> getTranslationFactor::TranslationFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData){
  playHist2D factor=playHist2D();
  //  TString dirhad="/Users/zmeng/Work_CMS/SUSY/myppt/BGEstimation_16022012/rootfiles/hadronicSele"+subdir_;
  TString dirhad = inidir_ + "rootfiles/hadronicSele" + subdir_;

  TString dir1mu="";
  if( MuAddOrNot == true){
    dir1mu = inidir_ + "rootfiles/oneMuonSele/muonpT50GeV" + subdir_;
  } else{
    dir1mu = inidir_ + "rootfiles/oneMuonSele/muonpT10GeV" + subdir_;
  }

  vector<TFile*> vf_had;
  if( isData == true ){
    vf_had=Datavf_pushback(dirhad, "HadSele", HTBins);
  } else {
    vf_had=MCvf_pushback(dirhad, "HadSele", HTBins);
  }

  vector<TFile*> vf_1mu;
  vector<TFile*> Datavf_1mu;
  if( MuAddOrNot == true){
    if( isData == true ){
      vf_1mu=Datavf_pushback(dir1mu, "MuonAddedHTATTrig", HTBins);
    } else vf_1mu=MCvf_pushback(dir1mu, "MuonAddedHTATTrig", HTBins);
  } else{
    if( isData == true ){
      vf_1mu=Datavf_pushback(dir1mu, "MuonHTATTrig", HTBins);
    } else vf_1mu=MCvf_pushback(dir1mu, "MuonHTATTrig", HTBins);
  }

  double scalein=1.;
  TString digit1in="";
  if( isData == true ){
    scalein=1.;
    digit1in="g";
  } else {
    scalein = scale_;
    digit1in=digit1_;
  }

  vector<TString> dirNamehad=dirName_pushback("", HTBins);
  vector<TString> dirName1mu=dirName_pushback("OneMuon_", HTBins);

  vector<TString> hNamehad;
  vector<TString> hName1mu=vhname_pusback_domin(MuAddOrNot, fullesti);

  if( isData == true ){
    hNamehad=vhname_pusback_data(MuAddOrNot, fullesti);
  } else{
    hNamehad=vhname_pusback_numer(MuAddOrNot, fullesti);
  }

  //  TH2D* AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_had=addHistForDiffFoldersAndFiles2D(vf_had, dirNamehad, "AlphaT_vs_HT_"+numerHist+"_h_all");
  //  TH2D* AlphaT_vs_HT_JetMugeq2_1mu=addHistForDiffFoldersAndFiles2D(vf_1mu, dirName1mu, "AlphaT_vs_HT_"+domiHist+"_h_all");

  if( MuAddOrNot == true ){
    vector<TH2D*> reh2d;

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D( vf_had, dirNamehad, hNamehad );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D( vf_1mu, dirName1mu, hName1mu );
    
    TH2D* factor_h=(TH2D*)( AlphaT_vs_HT_numer->Clone( "factor_h" ) );
    factor_h->Divide( AlphaT_vs_HT_numer, AlphaT_vs_HT_domin );

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }

  if( MuAddOrNot == false and fullesti == true ){
    vector<TH2D*> reh2d;

    vector<TString> vhname_first;
    vector<TString> vhname_second;
    vhname_first.push_back(hNamehad[0]);
    vhname_second.push_back(hNamehad[1]);

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersAndFiles_SubtrackHists2D(vf_had, dirNamehad, vhname_first, vhname_second );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu );
    
    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }

  if( MuAddOrNot == false and fullesti == false ){
    vector<TH2D*> reh2d;

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu );
    
    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }
}

// -----------------------------------------------------------------------------
//
TH2D* getTranslationFactor::getFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData){

  vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor( MuAddOrNot, fullesti, HTBins, isData );

  return factorHist_hasTauHadToMuAdded[2];
}

// -----------------------------------------------------------------------------
//
TH2D* getTranslationFactor::getControlData( bool MuAddOrNot, bool fullesti, TString HTBins ){

  vector<TH2D*> Data1mu=TranslationFactor( MuAddOrNot, fullesti, HTBins, true );

  return Data1mu[1];
}

TH2D* getTranslationFactor::getYieldData( bool MuAddOrNot, bool fullesti, TString HTBins ){

  vector<TH2D*> Data1mu=TranslationFactor( MuAddOrNot, fullesti, HTBins, true );

  return Data1mu[0];
}


TH2D* getTranslationFactor::getPredBG( bool MuAddOrNot, bool fullesti, TString HTBins ){
  TH2D* factorh=getFactor( MuAddOrNot, fullesti, HTBins, false);
  TH2D* Data1mu=getControlData( MuAddOrNot, fullesti, HTBins );
  TH2D* pred=(TH2D*)(Data1mu->Clone("pred"));
  pred->Multiply(pred, factorh);
  return pred;
}


// -----------------------------------------------------------------------------
//
void getTranslationFactor::baseCheck( bool MuAddOrNot, bool fullesti, TString HTBins, TString plotname, bool isData){
  playHist2D factor=playHist2D();
  TCanvas *c1=new TCanvas();
  vector<TLine*> lines=factor.Lines();

  vector<TH2D*> factorHist=TranslationFactor( MuAddOrNot, fullesti, HTBins, isData );
  factorHist[0]->Draw("colz");
  factorHist[0]->Draw("text30same");

  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("numer_"+plotname+".png");
  c1->SaveAs("numer_"+plotname+".eps");
  c1->Update();
  c1->Clear();

  factorHist[1]->Draw("colz");
  factorHist[1]->Draw("text30same");

  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("domin_"+plotname+".png");
  c1->SaveAs("domin_"+plotname+".eps");
  c1->Update();
  c1->Clear();


  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  factorHist[2]->Draw("colz");
  factorHist[2]->Draw("text30same");

  c1->SaveAs("factor_"+plotname+".png");
  c1->SaveAs("factor_"+plotname+".eps");
  c1->Update();
  c1->Clear();


}

void getTranslationFactor::getResults(){
  playHist2D factor=playHist2D();

  baseCheck( true, false, "all", "tauHadEsti_AddMuToAT", false );
  baseCheck( false, false, "all", "LepEsti_NotAddMuToAT", false );
  baseCheck( false, true, "all", "NotTauHadEsti_NotAddMuToAT", false );
  baseCheck( true, false, "all", "tauHadEsti_AddMuToAT_Data", true );
  baseCheck( false, false, "all", "LepEsti_NotAddMuToAT_Data", true );

  TH2D* pred_AddMu=getPredBG( true, false, "all" );
  TH2D* pred_NotTauHad=getPredBG( false, true, "all" );
  TH2D* pred_Lep=getPredBG( false, false, "all" );

  TH2D* pred_AddMu_c1=factor.formatHist(pred_AddMu, 1., digit1_);
  TH2D* pred_Lep_c1=factor.formatHist(pred_Lep, 1., digit1_);
  TH2D* pred_NotTauHad_c1=factor.formatHist(pred_NotTauHad, 1., digit1_);

  vector<TLine*> lines=factor.Lines();

  TCanvas *c1=new TCanvas();
  pred_AddMu_c1->Draw("colz");
  pred_AddMu_c1->Draw("sametext45");
  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("pred_AddMu.png");
  c1->SaveAs("pred_AddMu.eps");
  c1->Update();
  c1->Clear();
  pred_Lep_c1->Draw("colz");
  pred_Lep_c1->Draw("sametext45");
  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("pred_Lep.png");
  c1->SaveAs("pred_Lep.eps");
  c1->Update();
  c1->Clear();
  pred_NotTauHad_c1->Draw("colz");
  pred_NotTauHad_c1->Draw("sametext45");
  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("pred_NotTauHad.png");
  c1->SaveAs("pred_NotTauHad.eps");
  c1->Update();
  c1->Clear();

  TH2D* totalpre=(TH2D*)(pred_AddMu_c1->Clone("totalpre"));
  totalpre->Add(totalpre, pred_NotTauHad_c1);
  totalpre->Draw("colz");
  totalpre->Draw("sametext45");
  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("pred_Total.png");
  c1->SaveAs("pred_Total.eps");
  c1->Update();
  c1->Clear();

}

