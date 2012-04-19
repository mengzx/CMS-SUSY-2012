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



getTranslationFactor::getTranslationFactor()
{}

// -----------------------------------------------------------------------------
//
vector<TH2D*> getTranslationFactor::TranslationFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData){
  playHist2D factor=playHist2D();

  TString dirhad = inidir_ + "rootfiles/hadronicSele" + subdir_;

  TString dir1mu="";
  if( normalEstimation_ == true){
    dir1mu = inidir_ + "rootfiles/oneMuonSele/muonpT45GeV" + subdir_;
  } else{
    if( MuAddOrNot == true ){
      dir1mu = inidir_ + "rootfiles/oneMuonSele/muonpT50GeV" + subdir_;
    } else{
      dir1mu = inidir_ + "rootfiles/oneMuonSele/muonpT10GeV" + subdir_;
    }
  }

  vector<TFile*> vf_had;
  if( isData == true ){
    vf_had=Datavf_pushback(dirhad, signalDataset_, "HadSele"+signalTrig_, HTBins);
  } else {
    vf_had=MCvf_pushback(dirhad, MCsample_, "HadSele"+signalTrig_, HTBins, false, "");
  }

  vector<TFile*> vf_1mu;
  if( normalEstimation_ == true ){
    if( isData == true ){
      vf_1mu=Datavf_pushback(dir1mu, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
    } else vf_1mu=MCvf_pushback(dir1mu, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, false, "");
  } else {
    if( MuAddOrNot == true){
      if( isData == true ){
	vf_1mu=Datavf_pushback(dir1mu, HadTaudataset_, "MuonAdded"+HadTaucontrolTrig_, HTBins);
      } else vf_1mu=MCvf_pushback(dir1mu, MCsample_, "MuonAdded"+HadTaucontrolTrig_, HTBins, false, "");
    } else{
      if( isData == true ){
	vf_1mu=Datavf_pushback(dir1mu, NotHadTaudataset_, "Muon"+NotHadTaucontrolTrig_, HTBins);
      } else vf_1mu=MCvf_pushback(dir1mu, MCsample_, "Muon"+NotHadTaucontrolTrig_, HTBins, false, "" );
    }
  }
  double scalein=1.;
  TString digit1in="";
  if( isData == true ){
    scalein=datascale_;
    digit1in="g";
  } else {
    scalein = mcscale_;
    digit1in=digit1_;
  }

  vector<TString> dirNamehad=dirName_pushback(folderlabel_ + "", HTBins);
  vector<TString> dirName1mu=dirName_pushback(folderlabel_ + "OneMuon_", HTBins);

  vector<TString> hNamehad;
  vector<TString> hName1mu=vhname_pusback_domin(MuAddOrNot, fullesti, startNJet_, nJets_);

  if( isData == true ){
    hNamehad=vhname_pusback_data(MuAddOrNot, fullesti, startNJet_, nJets_);
  } else{
    hNamehad=vhname_pusback_numer(MuAddOrNot, fullesti, startNJet_, nJets_);
  }

  if( MuAddOrNot == true  && normalEstimation_ == false ){
    vector<TH2D*> reh2d;

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D( vf_had, dirNamehad, hNamehad );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D( vf_1mu, dirName1mu, hName1mu );

    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }
    
    TH2D* factor_h=(TH2D*)( AlphaT_vs_HT_numer->Clone( "factor_h" ) );
    factor_h->Divide( AlphaT_vs_HT_numer, AlphaT_vs_HT_domin );

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }

  if( MuAddOrNot == false && fullesti == true  && normalEstimation_ == false ){
    vector<TH2D*> reh2d;

    vector<TString> vhname_first;
    vector<TString> vhname_second;
    for( int i=0; i<hNamehad.size(); i++){
      if(i<(hNamehad.size())/2){
	vhname_first.push_back(hNamehad[i]);
      } else {
	vhname_second.push_back(hNamehad[i]);
      }
    }

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersAndFiles_SubtrackHists2D(vf_had, dirNamehad, vhname_first, vhname_second );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu );

    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }
    
    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    
    return reh2d;
  }

  if( MuAddOrNot == false && fullesti == false && normalEstimation_ == false ){
    vector<TH2D*> reh2d;

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu );
    
    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }
    
    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }

  if( normalEstimation_ == true ){
    vector<TH2D*> reh2d;
    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu );
    
    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }

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
TH2D* getTranslationFactor::getNumerMC( bool MuAddOrNot, bool fullesti, TString HTBins ){

  vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor( MuAddOrNot, fullesti, HTBins, false );

  return factorHist_hasTauHadToMuAdded[0];
}

// -----------------------------------------------------------------------------
//
TH2D* getTranslationFactor::getDominMC( bool MuAddOrNot, bool fullesti, TString HTBins ){

  vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor( MuAddOrNot, fullesti, HTBins, false );

  return factorHist_hasTauHadToMuAdded[1];
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

  if(normalEstimation_ == true ){
    baseCheck( false, true, "all", "NotTauHadEsti_NotAddMuToAT", false );
    baseCheck( true, false, "all", "tauHadEsti_AddMuToAT_Data", true );
  } else {
    baseCheck( true, false, "all", "tauHadEsti_AddMuToAT", false );
    baseCheck( true, false, "all", "tauHadEsti_AddMuToAT", false );
    baseCheck( false, false, "all", "LepEsti_NotAddMuToAT", false );
    baseCheck( false, false, "all", "LepEsti_NotAddMuToAT_Data", true );
  }

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

