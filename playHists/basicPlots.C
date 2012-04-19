#include "basicPlots.h"
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
#include "TLegend.h"

#include "tdrstyle.h"
#include "playHist2D.h"
#include "playHist1D.h"
#include "project2DHists.h"
#include "getTranslationFactor.h"
#include "menus.h"

using namespace std;

basicPlots::basicPlots(){}

TH1D* basicPlots::AlphaT( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin ){

  playHist1D hf1d=playHist1D();

  TH1D *alT=hf1d.addHistForDiffFoldersFilesHists1D(invf, vdirname, vhname);

  TH1D* formatalT=hf1d.formatHist(alT, inscale, "#alpha_{T}", "", 0.46, 0.59, rebin );
  return formatalT;
}


TH1D* basicPlots::njet( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin ){

  playHist1D hf1d=playHist1D();

  TH1D *alT=hf1d.addHistForDiffFoldersFilesHists1D(invf, vdirname, vhname);

  TH1D* formatalT=hf1d.formatHist(alT, inscale, "#alpha_{T}", "", 0, 8, rebin );
  return formatalT;
}

TH1D* basicPlots::nbjet( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin ){

  playHist1D hf1d=playHist1D();

  TH1D *alT=hf1d.addHistForDiffFoldersFilesHists1D(invf, vdirname, vhname);

  TH1D* formatalT=hf1d.formatHist(alT, inscale, "#alpha_{T}", "", 0, 5, rebin );
  return formatalT;
}



TH1D* basicPlots::NVertex( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin ){

  playHist1D hf1d=playHist1D();

  TH1D *alT=hf1d.addHistForDiffFoldersFilesHists1D(invf, vdirname, vhname);

  TH1D* formatalT=hf1d.formatHist(alT, inscale, "#alpha_{T}", "", 0., 50., rebin );
  return formatalT;
}


TH1D* basicPlots::HT( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin, double lowalphaT, double highalphaT ){

  playHist2D hf2d=playHist2D();
  playHist1D hf1d=playHist1D();
  project2DHists pf=project2DHists();

  TH2D* hT=hf2d.addHistForDiffFoldersFilesHists2D( invf, vdirname, vhname );
  TH1D* hTalphaTSlices=pf.projectX( hT, lowalphaT, highalphaT );


  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, inscale, "H_{T} (GeV)", "", 275., 1400., rebin );

  return formathT;
}


void basicPlots::DrawHists( bool MuAddOrNot, TString HTBins, int whichpart, TString whichplot, int rebin, double lowalphaT, double highalphaT ){ // whichpart: if == 1 ==> numberator, if == 2 ==> dominator

  getTranslationFactor tf=getTranslationFactor();
  playHist1D pf1d=playHist1D();

  TString dir;

  TString dir_truetauhad;
  if( whichpart == 1 ){
    dir = inidir_ + "rootfiles/hadronicSele" + subdir_;
  } else if ( whichpart != 1 && MuAddOrNot == true && normalEstimation_ == false){
    dir = inidir_ + "rootfiles/oneMuonSele/muonpT50GeV" + subdir_;
    if( plotTrueTauHad_ ){
      dir_truetauhad = inidir_ + "rootfiles/hadronicSele" + subdir_;
    }
  } else if ( whichpart !=1 && MuAddOrNot == false && normalEstimation_ == false){
    dir = inidir_ + "rootfiles/oneMuonSele/muonpT10GeV" + subdir_;
  } else if ( whichpart !=1 && normalEstimation_ == true){
    dir = inidir_ + "rootfiles/oneMuonSele/muonpT45GeV" + subdir_;
  }
  cout<<"  "<<inidir_<<endl;

    
  vector<TFile*> Datavf;
  vector<TFile*> MCvf;
  vector<TString> vdirname;
  vector<TString> vhname_HT;
  vector<TString> vhname_AlphaT;
  vector<TString> vhname_AlphaT_truetauhad;
  vector<TFile*> MCvf_truetauhad;
  vector<TString> vdirname_truetauhad;

  if( whichpart == 1 ){
    Datavf=tf.Datavf_pushback(dir, signalDataset_, "HadSele"+signalTrig_, HTBins);
    MCvf=tf.MCvf_pushback(dir, MCsample_, "HadSele"+signalTrig_, HTBins, false, "");
    vdirname=tf.dirName_pushback(folderlabel_+"", HTBins);
    if( startNJet_ == 0 ){
      vhname_HT.push_back("HT_CommJetgeq2_h_all");
      vhname_AlphaT.push_back("AlphaT_CommJetgeq2_h_all");
    } else {
      for( int i=startNJet_; i< startNJet_+nJets_; i++ ){
	vhname_HT.push_back( Form("HT_CommJetgeq2_h_%d", i ) );
	vhname_AlphaT.push_back( Form("AlphaT_CommJetgeq2_h_%d", i ) );
      }
    }
  } else if ( whichpart != 1 && MuAddOrNot == true && normalEstimation_ == false ){
    Datavf=tf.Datavf_pushback(dir, HadTaudataset_, "MuonAdded"+HadTaucontrolTrig_, HTBins);
    MCvf=tf.MCvf_pushback(dir, MCsample_, "MuonAdded"+HadTaucontrolTrig_, HTBins, false, "");
    vdirname=tf.dirName_pushback(folderlabel_+"OneMuon_", HTBins);
    if( startNJet_ == 0 ){
      vhname_HT.push_back("HTTakeMu_JetMugeq2_h_all");
      vhname_AlphaT.push_back("AlphaT_JetMugeq2_h_all");
    } else {
      for( int i=startNJet_; i< startNJet_+nJets_; i++ ){
	vhname_HT.push_back( Form( "HTTakeMu_JetMugeq2_h_%d", i ) );
	vhname_AlphaT.push_back( Form( "AlphaT_JetMugeq2_h_%d", i ) );
      }
    }
    if( plotTrueTauHad_ ){
      if( startNJet_ == 0 ){
	vhname_AlphaT_truetauhad.push_back("AlphaT_CommJetgeq2_hasTrueTauHad_h_all");
      } else {
	for( int i=startNJet_; i< startNJet_+nJets_; i++ ){
	  vhname_AlphaT_truetauhad.push_back( Form( "AlphaT_CommJetgeq2_hasTrueTauHad_h_%d", i ) );
	}
      }
      MCvf_truetauhad=tf.MCvf_pushback(dir_truetauhad, MCsample_, "HadSele"+signalTrig_, HTBins, false, "");
      vdirname_truetauhad=tf.dirName_pushback(folderlabel_+"", HTBins);
    }
  } else if ( whichpart != 1 && MuAddOrNot == false && normalEstimation_ == false ){
    Datavf=tf.Datavf_pushback(dir, NotHadTaudataset_, "Muon"+NotHadTaucontrolTrig_, HTBins);
    MCvf=tf.MCvf_pushback(dir, MCsample_, "Muon"+NotHadTaucontrolTrig_, HTBins, false, "");
    vdirname=tf.dirName_pushback(folderlabel_+"OneMuon_", HTBins);
    if( startNJet_ == 0 ){
      vhname_HT.push_back("HT_CommJetgeq2_h_all");
      vhname_AlphaT.push_back("AlphaT_CommJetgeq2_h_all");
    } else {
      for( int i=startNJet_; i< startNJet_+nJets_; i++ ){
	vhname_HT.push_back( Form( "HT_CommJetgeq2_h_%d", i ) );
	vhname_AlphaT.push_back( Form( "AlphaT_CommJetgeq2_h_%d", i ) );
      }
    }
  } else if ( whichpart != 1 && normalEstimation_ == true ) {
    Datavf=tf.Datavf_pushback(dir, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
    MCvf=tf.MCvf_pushback(dir, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, false, "");
    vdirname=tf.dirName_pushback(folderlabel_+"OneMuon_", HTBins);
    if( startNJet_ == 0 ){
      vhname_HT.push_back("HT_CommJetgeq2_h_all");
      vhname_AlphaT.push_back("AlphaT_CommJetgeq2_h_all");
    } else {
      for( int i=startNJet_; i< startNJet_+nJets_; i++ ){
	vhname_HT.push_back( Form( "HT_CommJetgeq2_h_%d", i ) );
	vhname_AlphaT.push_back( Form( "AlphaT_CommJetgeq2_h_%d", i ) );
      }
    }
  }

  tdrstyle tdr=tdrstyle();
  tdr.setTDRStyle("g");

  TCanvas *c1=new TCanvas();

  if( whichplot == "HT"){
    TH1D* MCh=HT( MCvf, vdirname, vhname_HT, mcscale_, rebin, lowalphaT, highalphaT );
    TH1D* Datah=HT( Datavf, vdirname, vhname_HT, datascale_, rebin, lowalphaT, highalphaT );

    vector<TH1D*> vh;
    vh.push_back(MCh);
    vh.push_back(Datah);

    TLegend *len=new TLegend( 0.75, 0.75, 0.995, 0.995 );

    TH1D* maxh=pf1d.MaxHist( vh );
    maxh->Draw();
    MCh->Draw("same");
    MCh->SetLineColor(2);
    MCh->SetMarkerColor(2);
    MCh->SetMarkerStyle(22);
    len->AddEntry(MCh, "Total MC");
    Datah->Draw("same");
    Datah->SetMarkerStyle(24);
    len->AddEntry(Datah, "Data");
    len->Draw();

    if( whichpart == 1 ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "HT_HadSele_AT%dTo%d.eps", (int)(lowalphaT*100), (int)(highalphaT*100) ) );
      c1->SetLogy();
      c1->SaveAs( Form( "HT_HadSele_AT%dTo%d_log.eps", (int)(lowalphaT*100), (int)(highalphaT*100) ) );
    } else if ( whichpart != 1 && MuAddOrNot == true && normalEstimation_ == false ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "HT_MuonAdded_AT%dTo%d_%s.eps", (int)(lowalphaT*100), (int)(highalphaT*100), HadTaucontrolTrig_.Data() ) );
      c1->SetLogy();
      c1->SaveAs( Form( "HT_MuonAdded_AT%dTo%d_%s_log.eps", (int)(lowalphaT*100), (int)(highalphaT*100), HadTaucontrolTrig_.Data() ) );
    } else if ( whichpart !=1 && MuAddOrNot == false && normalEstimation_ == false ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "HT_MuonNotAdded_AT%dTo%d.eps", (int)(lowalphaT*100), (int)(highalphaT*100) ) );
      c1->SetLogy();
      c1->SaveAs( Form( "HT_MuonNotAdded_AT%dTo%d_log.eps", (int)(lowalphaT*100), (int)(highalphaT*100) ) );
    } else if ( whichpart !=1  && normalEstimation_ == true ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "HT_AT%dTo%d.eps", (int)(lowalphaT*100), (int)(highalphaT*100) ) );
      c1->SetLogy();
      c1->SaveAs( Form( "HT_AT%dTo%d_log.eps", (int)(lowalphaT*100), (int)(highalphaT*100) ) );
    }

  }

  if( whichplot == "AlphaT"){
    TH1D* MCh=AlphaT( MCvf, vdirname, vhname_AlphaT, mcscale_, rebin );
    TH1D* Datah=AlphaT( Datavf, vdirname, vhname_AlphaT, datascale_, rebin );

    TH1D* MCh_truetauhad=0;
    if( plotTrueTauHad_ ){
      AlphaT( MCvf_truetauhad, vdirname_truetauhad, vhname_AlphaT_truetauhad, mcscale_, rebin );
    }

    vector<TH1D*> vh;
    vh.push_back(MCh);
    vh.push_back(Datah);

    TLegend *len=new TLegend( 0.70, 0.75, 0.995, 0.995 );

    TH1D* maxh=pf1d.MaxHist( vh );
    maxh->Draw();
    MCh->Draw("same");
    MCh->SetLineColor(2);
    MCh->SetMarkerColor(2);
    MCh->SetMarkerStyle(22);
    len->AddEntry(MCh, "Total MC");
    Datah->Draw("same");
    Datah->SetMarkerStyle(24);
    Datah->SetLineColor(1);
    len->AddEntry(Datah, "Data");
    if( plotTrueTauHad_ ){
      MCh_truetauhad->Draw("same");
      MCh_truetauhad->SetLineColor(3);
      MCh_truetauhad->SetMarkerColor(3);;
      MCh_truetauhad->SetMarkerStyle(22);;
      len->AddEntry(MCh_truetauhad, "true #tau_{h}");
    }
    len->Draw();

    cout<<"hi1"<<endl;
    if( whichpart == 1 ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "AlphaT_HadSele_%s.eps",  HTBins.Data() ) );
      c1->SetLogy();
      c1->SaveAs( Form( "AlphaT_HadSele_%s_log.eps",  HTBins.Data() ) );
    } else if ( whichpart != 1 && MuAddOrNot == true ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "AlphaT_MuonAdded_%s_TrueTauHad%d_%s.eps", HTBins.Data(), (int)(plotTrueTauHad_), HadTaucontrolTrig_.Data() ) );
      c1->SetLogy();
      c1->SaveAs( Form( "AlphaT_MuonAdded_%s_TrueTauHad%d_%s_log.eps",  HTBins.Data(), (int)(plotTrueTauHad_), HadTaucontrolTrig_.Data() ) );
    } else if ( whichpart !=1 && MuAddOrNot == false ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "AlphaT_MuonNotAdded_%s.eps", HTBins.Data() ) );
      c1->SetLogy();
      c1->SaveAs( Form( "AlphaT_MuonNotAdded_%s_log.eps",  HTBins.Data() ) );
    }

  }

}

void basicPlots::getResults(){

  int whichpart=1;
  bool MuAddOrNot=true;
  int rebin=1;
  //  DrawHists(MuAddOrNot, "low", whichpart, "AlphaT", rebin, 0., 0. );
  //  DrawHists(MuAddOrNot, "100", whichpart, "AlphaT", rebin, 0., 0. );
  /*  DrawHists(MuAddOrNot, "73", whichpart, "AlphaT", rebin, 0., 0. );
  DrawHists(MuAddOrNot, "86", whichpart, "AlphaT", rebin, 0., 0. );
  */
  DrawHists(MuAddOrNot, "all", whichpart, "AlphaT", rebin, 0., 0. );

  whichpart=2;
  MuAddOrNot=false;
  //  DrawHists(MuAddOrNot, "low", whichpart, "AlphaT", rebin, 0., 0. );
  DrawHists(MuAddOrNot, "100", whichpart, "AlphaT", rebin, 0., 0. );
  //  DrawHists(MuAddOrNot, "73", whichpart, "AlphaT", rebin, 0., 0. );
  //  DrawHists(MuAddOrNot, "86", whichpart, "AlphaT", rebin, 0., 0. );
  DrawHists(MuAddOrNot, "all", whichpart, "AlphaT", rebin, 0., 0. );

  /*  whichpart=1;
  MuAddOrNot=true;
  DrawHists(MuAddOrNot, "low", whichpart, "AlphaT", rebin, 0., 0. );
  DrawHists(MuAddOrNot, "100", whichpart, "AlphaT", rebin, 0., 0. );
  DrawHists(MuAddOrNot, "73", whichpart, "AlphaT", rebin, 0., 0. );
  DrawHists(MuAddOrNot, "86", whichpart, "AlphaT", rebin, 0., 0. );
  DrawHists(MuAddOrNot, "all", whichpart, "AlphaT", rebin, 0., 0. );
   */

  //HT
  whichpart=1;
  MuAddOrNot=true;
  rebin=20;
  //  DrawHists(MuAddOrNot, "100", whichpart, "HT", rebin, 0.52, 0.55 );
  DrawHists(MuAddOrNot, "all", whichpart, "HT", rebin, 0.55, 10. );

  whichpart=2;
  MuAddOrNot=false;
  //  DrawHists(MuAddOrNot, "100", whichpart, "HT", rebin, 0.52, 0.55 );
  DrawHists(MuAddOrNot, "all", whichpart, "HT", rebin, 0.55, 10. );

  /*  whichpart=1;
  MuAddOrNot=false;
  DrawHists(MuAddOrNot, "100", whichpart, "HT", rebin, 0.52, 0.55 );
  DrawHists(MuAddOrNot, "all", whichpart, "HT", rebin, 0.55, 10. );
  */
}
