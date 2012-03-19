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

using namespace std;


basicPlots::basicPlots():
  inidir_("/Users/phxzm/Work_CMS/SUSY/myppt/BGEstimation_16022012/"),
  subdir_("/FullyTreatMuonAsJet/alljets"),
  folderlabel_("")
{}

TH1D* basicPlots::AlphaT( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin ){

  playHist1D hf1d=playHist1D();

  TH1D *alT=hf1d.addHistForDiffFoldersFilesHists1D(invf, vdirname, vhname);

  TH1D* formatalT=hf1d.formatHist(alT, inscale, "#alpha_{T}", "", 0.2, 2., rebin );

  return formatalT;
}


TH1D* basicPlots::HT( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin, double lowalphaT, double highalphaT ){

  playHist2D hf2d=playHist2D();
  playHist1D hf1d=playHist1D();
  project2DHists pf=project2DHists();

  TH2D* hT=hf2d.addHistForDiffFoldersFilesHists2D( invf, vdirname, vhname );

  TH1D* hTalphaTSlices=pf.projectY( hT, lowalphaT, highalphaT );

  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, inscale, "H_{T} (GeV)", "", 275., 1100., rebin );

  return formathT;
}


void basicPlots::DrawHists( bool MuAddOrNot, TString HTBins, int whichpart, TString whichplot, double inscale, int rebin, double lowalphaT, double highalphaT ){ // whichpart: if == 1 ==> numberator, if == 2 ==> dominator

  getTranslationFactor tf=getTranslationFactor();
  playHist1D pf1d=playHist1D();

  TString dir;

  if( whichpart == 1 ){
    dir = inidir_ + "rootfiles/hadronicSele" + subdir_;
  } else if ( whichpart != 1 && MuAddOrNot == true ){
    dir = inidir_ + "rootfiles/oneMuonSele/muonpT50GeV" + subdir_;
  } else if ( whichpart !=1 && MuAddOrNot == false ){
    dir = inidir_ + "rootfiles/oneMuonSele/muonpT10GeV" + subdir_;
  }

  vector<TFile*> Datavf;
  vector<TFile*> MCvf;
  vector<TString> vdirname;
  vector<TString> vhname_HT;
  vector<TString> vhname_AlphaT;

  if( whichpart == 1 ){
    Datavf=tf.Datavf_pushback(dir, "HadSele", HTBins);
    MCvf=tf.MCvf_pushback(dir, "HadSele", HTBins);
    vdirname=tf.dirName_pushback(folderlabel_+"", HTBins);
    vhname_HT.push_back("HT_CommJetgeq2_h_all");
    vhname_AlphaT.push_back("AlphaT_CommJetgeq2_h_all");
  } else if ( whichpart != 1 && MuAddOrNot == true ){
    Datavf=tf.Datavf_pushback(dir, "MuonAddedHTATTrig", HTBins);
    MCvf=tf.MCvf_pushback(dir, "MuonAddedHTATTrig", HTBins);
    vdirname=tf.dirName_pushback(folderlabel_+"OneMuon_", HTBins);
    vhname_HT.push_back("HT_JetMugeq2_h_all");
    vhname_AlphaT.push_back("AlphaT_JetMugeq2_h_all");
  } else if ( whichpart != 1 && MuAddOrNot == false ){
    Datavf=tf.Datavf_pushback(dir, "MuonHTATTrig", HTBins);
    MCvf=tf.MCvf_pushback(dir, "MuonHTATTrig", HTBins);
    vdirname=tf.dirName_pushback(folderlabel_+"OneMuon_", HTBins);
    vhname_HT.push_back("HT_CommJetgeq2_h_all");
    vhname_AlphaT.push_back("AlphaT_CommJetgeq2_h_all");
  }

  tdrstyle tdr=tdrstyle();
  tdr.setTDRStyle("g");

  TCanvas *c1=new TCanvas();

  if( whichplot == "HT"){
    TH1D* MCh=HT( MCvf, vdirname, vhname_HT, inscale, rebin, lowalphaT, highalphaT );
    TH1D* Datah=HT( Datavf, vdirname, vhname_HT, inscale, rebin, lowalphaT, highalphaT );

    vector<TH1D*> vh;
    vh.push_back(MCh);
    vh.push_back(Datah);

    TLegend *len=new TLegend( 0.75, 0.75, 0.995, 0.995 );

    TH1D* maxh=pf1d.MaxHist( vh );
    maxh->Draw();
    MCh->Draw("same");
    MCh->SetLineColor(2);
    len->AddEntry(MCh, "Total MC");
    Datah->Draw("same");
    len->AddEntry(Datah, "Data");
    len->Draw();

    if( whichpart == 1 ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "HT_HadSele_AT%fTo%f.eps", lowalphaT, highalphaT ) );
      c1->SetLogy();
      c1->SaveAs( Form( "HT_HadSele_AT%fTo%f_log.eps", lowalphaT, highalphaT ) );
    } else if ( whichpart != 1 && MuAddOrNot == true ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "HT_MuonAdded_AT%fTo%f.eps", lowalphaT, highalphaT ) );
      c1->SetLogy();
      c1->SaveAs( Form( "HT_MuonAdded_AT%fTo%f_log.eps", lowalphaT, highalphaT ) );
    } else if ( whichpart !=1 && MuAddOrNot == false ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "HT_MuonNotAdded_AT%fTo%f.eps", lowalphaT, highalphaT ) );
      c1->SetLogy();
      c1->SaveAs( Form( "HT_MuonNotAdded_AT%fTo%f_log.eps", lowalphaT, highalphaT ) );
    }

  }

  if( whichplot == "AlphaT"){
    TH1D* MCh=AlphaT( MCvf, vdirname, vhname_AlphaT, inscale, rebin );
    TH1D* Datah=AlphaT( Datavf, vdirname, vhname_AlphaT, inscale, rebin );

    vector<TH1D*> vh;
    vh.push_back(MCh);
    vh.push_back(Datah);

    TLegend *len=new TLegend( 0.75, 0.75, 0.995, 0.995 );

    TH1D* maxh=pf1d.MaxHist( vh );
    maxh->Draw();
    MCh->Draw("same");
    MCh->SetLineColor(2);
    len->AddEntry(MCh, "Total MC");
    Datah->Draw("same");
    len->AddEntry(Datah, "Data");
    len->Draw();

    if( whichpart == 1 ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "AlphaT_HadSele_%s.eps",  HTBins.Data() ) );
      c1->SetLogy();
      c1->SaveAs( Form( "AlphaT_HadSele_%s_log.eps",  HTBins.Data() ) );
    } else if ( whichpart != 1 && MuAddOrNot == true ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "AlphaT_MuonAdded_%s.eps", HTBins.Data() ) );
      c1->SetLogy();
      c1->SaveAs( Form( "AlphaT_MuonAdded_%s_log.eps",  HTBins.Data() ) );
    } else if ( whichpart !=1 && MuAddOrNot == false ){
      c1->SetLogy(0);
      c1->SaveAs( Form( "AlphaT_MuonNotAdded_%s.eps", HTBins.Data() ) );
      c1->SetLogy();
      c1->SaveAs( Form( "AlphaT_MuonNotAdded_%s_log.eps",  HTBins.Data() ) );
    }

  }

}

void basicPlots::getResults(){

  int whichpart=2;
  bool MuAddOrNot=true;
  double inscale=1.;
  int rebin=0;
  DrawHists(MuAddOrNot, "low", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "100", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "73", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "86", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "all", whichpart, "AlphaT", rebin, inscale, 0., 0. );

  whichpart=1;
  MuAddOrNot=true;
  inscale=1.;
  rebin=0;
  DrawHists(MuAddOrNot, "low", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "100", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "73", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "86", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "all", whichpart, "AlphaT", rebin, inscale, 0., 0. );


  whichpart=2;
  MuAddOrNot=false;
  inscale=1.;
  rebin=0;
  DrawHists(MuAddOrNot, "low", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "100", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "73", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "86", whichpart, "AlphaT", rebin, inscale, 0., 0. );
  DrawHists(MuAddOrNot, "all", whichpart, "AlphaT", rebin, inscale, 0., 0. );

  //HT
  /*  whichpart=2;
  MuAddOrNot=true;
  inscale=1.;
  rebin=10;
  DrawHists(MuAddOrNot, "100", whichpart, "HT", rebin, inscale, 0.52, 0.55 );
  DrawHists(MuAddOrNot, "all", whichpart, "HT", rebin, inscale, 0.55, 10. );

  whichpart=2;
  MuAddOrNot=false;
  inscale=1.;
  rebin=10;
  DrawHists(MuAddOrNot, "100", whichpart, "HT", rebin, inscale, 0.52, 0.55 );
  DrawHists(MuAddOrNot, "100", whichpart, "HT", rebin, inscale, 0.55, 10. );

  whichpart=1;
  MuAddOrNot=false;
  inscale=1.;
  rebin=10;
  DrawHists(MuAddOrNot, "100", whichpart, "HT", rebin, inscale, 0.52, 0.55 );
  DrawHists(MuAddOrNot, "100", whichpart, "HT", rebin, inscale, 0.55, 10. );*/

}
