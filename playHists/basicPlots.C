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

basicPlots::basicPlots(){}

TH1D* basicPlots::Hist1D( vector<TFile*> &invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin, TString xAxisName, TString yAxisName, double xAxisRange1, double xAxisRange2) {

  playHist1D hf1d=playHist1D();

  TH1D *alT=hf1d.addHistForDiffFoldersFilesHists1D(invf, vdirname, vhname);

  TH1D* formatalT=hf1d.formatHist(alT, inscale, xAxisName, yAxisName, xAxisRange1, xAxisRange2, rebin );
  return formatalT;
}




TH1D* basicPlots::Hist2D( vector<TFile*> &invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin, TString xAxisName, TString yAxisName, double xAxisRange1, double xAxisRange2, double lowy, double highy) {

  playHist2D hf2d=playHist2D();
  playHist1D hf1d=playHist1D();
  project2DHists pf=project2DHists();

  TH2D* hT=hf2d.addHistForDiffFoldersFilesHists2D( invf, vdirname, vhname );
  TH1D* hTalphaTSlices=pf.projectX( hT, lowy, highy );


  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, inscale, xAxisName, yAxisName, xAxisRange1, xAxisRange2, rebin );
  return formathT;
}


vector<TH1D*> basicPlots::getHists( bool MuAddOrNot, TString HTBins, int whichpart, int rebin, TString xAxisName, TString yAxisName, double xAxisRange1, double xAxisRange2, int dataMC, TString whichplot, bool separateSample, TString singleMCsample, double lowy, double highy, int OneDTwoD, int startNJet, int nJets ){

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
    
  vector<TFile*> Datavf;
  vector<TFile*> MCvf;
  vector<TString> vdirname;
  vector<TString> vhname;
  vector<TFile*> MCvf_truetauhad;
  vector<TString> vdirname_truetauhad;
  vector<TString> vhname_truetauhad;

  if( whichpart == 1 ){
    if( dataMC == 1 ){
      Datavf=Datavf_pushback(dir, signalDataset_, "HadSele"+signalTrig_, HTBins);
    } else if ( dataMC == 2 ){
      MCvf=MCvf_pushback(dir, MCsample_, "HadSele"+signalTrig_, HTBins, separateSample, singleMCsample );
    } else if ( dataMC == 0){
      Datavf=Datavf_pushback(dir, signalDataset_, "HadSele"+signalTrig_, HTBins);
      MCvf=MCvf_pushback(dir, MCsample_, "HadSele"+signalTrig_, HTBins, separateSample, singleMCsample );
    }
    vdirname=dirName_pushback(folderlabel_+"", HTBins);
    if( startNJet == 0 ){
      vhname.push_back(whichplot+"_CommJetgeq2_h_all");
    } else {
      for( int i=startNJet; i< startNJet+nJets; i++ ){
	vhname.push_back( Form(whichplot+"_CommJetgeq2_h_%d", i ) );
      }
    }
  } else if ( whichpart != 1 && MuAddOrNot == true && normalEstimation_ == false ){
    if( dataMC == 1 ){
      Datavf=Datavf_pushback(dir, HadTaudataset_, "MuonAdded"+HadTaucontrolTrig_, HTBins);
    } else if( dataMC == 2 ){
      MCvf=MCvf_pushback(dir, MCsample_, "MuonAdded"+HadTaucontrolTrig_, HTBins, separateSample, singleMCsample );
    } else if( dataMC == 0 ){
      Datavf=Datavf_pushback(dir, HadTaudataset_, "MuonAdded"+HadTaucontrolTrig_, HTBins);
      MCvf=MCvf_pushback(dir, MCsample_, "MuonAdded"+HadTaucontrolTrig_, HTBins, separateSample, singleMCsample );
    }
    vdirname=dirName_pushback(folderlabel_ + MuonNumber_, HTBins);
    if( startNJet == 0 ){
      vhname.push_back(whichplot+"_JetMugeq2_h_all");
    } else {
      for( int i=startNJet; i< startNJet+nJets; i++ ){
	vhname.push_back( Form( whichplot+"_JetMugeq2_h_%d", i ) );
      }
    }
    if( plotTrueTauHad_ ){
      if( startNJet == 0 ){
	vhname_truetauhad.push_back(whichplot+"_CommJetgeq2_hasTrueTauHad_h_all");
      } else {
	for( int i=startNJet; i< startNJet+nJets; i++ ){
	  vhname_truetauhad.push_back( Form( whichplot+"_CommJetgeq2_hasTrueTauHad_h_%d", i ) );
	}
      }
      MCvf_truetauhad=MCvf_pushback(dir_truetauhad, MCsample_, "HadSele"+signalTrig_, HTBins, false, "");
      vdirname_truetauhad=dirName_pushback(folderlabel_+"", HTBins);
    }
  } else if ( whichpart != 1 && MuAddOrNot == false && normalEstimation_ == false ){
    if( dataMC == 1){
      Datavf=Datavf_pushback(dir, NotHadTaudataset_, "Muon"+NotHadTaucontrolTrig_, HTBins);
    } else if( dataMC == 2 ){
      MCvf=MCvf_pushback(dir, MCsample_, "Muon"+NotHadTaucontrolTrig_, HTBins, separateSample, singleMCsample );
    } else if( dataMC == 0 ){
      Datavf=Datavf_pushback(dir, NotHadTaudataset_, "Muon"+NotHadTaucontrolTrig_, HTBins);
      MCvf=MCvf_pushback(dir, MCsample_, "Muon"+NotHadTaucontrolTrig_, HTBins, separateSample, singleMCsample );
    }
    vdirname=dirName_pushback(folderlabel_ + MuonNumber_, HTBins);
    if( startNJet == 0 ){
      vhname.push_back(whichplot+"_CommJetgeq2_h_all");
    } else {
      for( int i=startNJet; i< startNJet+nJets; i++ ){
	vhname.push_back( Form( whichplot+"_CommJetgeq2_h_%d", i ) );
      }
    }
  } else if ( whichpart != 1 && normalEstimation_ == true ) {
    if( dataMC == 1){
      Datavf=Datavf_pushback(dir, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
    } else if( dataMC == 2 ){
      MCvf=MCvf_pushback(dir, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, separateSample, singleMCsample );
    } else if(dataMC == 0 ){
      Datavf=Datavf_pushback(dir, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
      MCvf=MCvf_pushback(dir, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, separateSample, singleMCsample );
    }
    vdirname=dirName_pushback(folderlabel_ + MuonNumber_, HTBins);
    if( startNJet == 0 ){
      vhname.push_back(whichplot+"_CommJetgeq2_h_all");
    } else {
      for( int i=startNJet; i< startNJet+nJets; i++ ){
	vhname.push_back( Form( whichplot+"_CommJetgeq2_h_%d", i ) );
      }
    }
  }

  TH1D* MCh=0;
  TH1D* Datah=0;
  TH1D* MCh_truetau=0;
  vector<TH1D*> vh;

  if( OneDTwoD == 1 ){
    if( dataMC == 1 ){
      Datah=Hist1D( Datavf, vdirname, vhname, datascale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2 );
      vh.push_back( Datah );
    } else if( dataMC == 2 ){
      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2 );
      vh.push_back( MCh );
      if( plotTrueTauHad_ ){
	MCh_truetau=Hist1D(  MCvf_truetauhad, vdirname_truetauhad, vhname_truetauhad, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2 );
	vh.push_back( MCh_truetau );
      }
    } else if( dataMC == 0){
      Datah=Hist1D( Datavf, vdirname, vhname, datascale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2 );
      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2 );
      vh.push_back( MCh );
      vh.push_back( Datah );
      if( plotTrueTauHad_ ){
	MCh_truetau=Hist1D(  MCvf_truetauhad, vdirname_truetauhad, vhname_truetauhad, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2 );
	vh.push_back( MCh_truetau );
      }
    }
  } else if( OneDTwoD == 2 ) {
    if( dataMC == 1 ){
      Datah=Hist2D( Datavf, vdirname, vhname, datascale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy );
      vh.push_back( Datah );
    } else if( dataMC == 2 ){
      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy );
      vh.push_back( MCh );
      if( plotTrueTauHad_ ){
	MCh_truetau=Hist2D(  MCvf_truetauhad, vdirname_truetauhad, vhname_truetauhad, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy );
	vh.push_back( MCh_truetau );
      }
    } else if( dataMC == 0){
      Datah=Hist2D( Datavf, vdirname, vhname, datascale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy );
      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy );
      vh.push_back( MCh );
      vh.push_back( Datah );
      if( plotTrueTauHad_ ){
	MCh_truetau=Hist2D(  MCvf_truetauhad, vdirname_truetauhad, vhname_truetauhad, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy );
	vh.push_back( MCh_truetau );
      }
    }
  }

  for( unsigned int i=0; i< Datavf.size(); i++){
    Datavf.erase(Datavf.begin()+i);
  }
  for( unsigned int i=0; i< MCvf.size(); i++){
    MCvf.erase(MCvf.begin()+i);
  }
  /*  delete  Datavf;
  delete  MCvf;
  delete  MCvf_truetauhad;*/
  return vh;
}





void basicPlots::drawHists( bool MuAddOrNot, TString HTBins, int whichpart, int rebin, TString xAxisName, TString yAxisName, double xAxisRange1, double xAxisRange2, TString whichplot, TLegend * len, double lowy, double highy, int OneDTwoD, int startNJet, int nJets ){

  TCanvas *c1=new TCanvas("c1","c1", 1);

  getTranslationFactor tf=getTranslationFactor();
  playHist1D pf1d=playHist1D();

  TH1D *Datah= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 1, whichplot, false, "", lowy, highy, OneDTwoD, startNJet, nJets ))[0];
  TH1D *MCh_total= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, false, "", lowy, highy, OneDTwoD, startNJet, nJets ))[0];
  TH1D *MCh_Zinv= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "Zinv", lowy, highy, OneDTwoD, startNJet, nJets ))[0];
  TH1D *MCh_TT= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "TT", lowy, highy, OneDTwoD, startNJet, nJets ))[0];
  TH1D *MCh_DY= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "DY", lowy, highy, OneDTwoD, startNJet, nJets ))[0];
  TH1D *MCh_WJ= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "WJ", lowy, highy, OneDTwoD, startNJet, nJets ))[0];
  TH1D *MCh_SingleT= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "SingleT", lowy, highy, OneDTwoD, startNJet, nJets ))[0];
  TH1D *MCh_DiBoson= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "DiBoson", lowy, highy, OneDTwoD, startNJet, nJets ))[0];

  vector<TString> vlenname;
  vlenname.push_back("Data");
  vlenname.push_back("Total MC");
  vlenname.push_back("W+jets");
  vlenname.push_back("Drell-Yan");
  vlenname.push_back("t#bar{t}");
  vlenname.push_back("Single top");
  vlenname.push_back("Z#rightarrow#nu#nu+jets");
  vlenname.push_back("Di-Boson");

  vector<TH1D*> vh;
  vh.push_back(Datah);
  vh.push_back(MCh_total);
  vh.push_back(MCh_WJ);
  vh.push_back(MCh_DY);
  vh.push_back(MCh_TT);
  vh.push_back(MCh_SingleT);
  vh.push_back(MCh_Zinv);
  vh.push_back(MCh_DiBoson);

  vector<TH1D*> svh=pf1d.SortHists(vh);
  vector<unsigned int> svh_index=pf1d.SortHists_index(vh);
  vector<TH1D*> invsvh=pf1d.invSortHists(vh);
  vector<unsigned int> invsvh_index=pf1d.invSortHists_index(vh);

  c1->cd();
  TPad *pad1=new TPad("pad1","",0,0.3,1,1);
  pad1->Draw();
  pad1->cd();
  pad1->SetTopMargin(0.1);

  if( !drawStack_ ){
    TH1D* svh0clone=(TH1D*)(svh[0]->Clone("svh0clone"));
    svh0clone->Scale(1.5);
    svh0clone->SetLineColor(0);
    svh0clone->SetMarkerColor(0);
    svh0clone->Draw();
    svh0clone->GetXaxis()->SetLabelFont(63);
    svh0clone->GetXaxis()->SetLabelSize(18);
    svh0clone->GetYaxis()->SetLabelFont(63);
    svh0clone->GetYaxis()->SetLabelSize(18);
    svh0clone->GetXaxis()->SetTitleSize(0.06);
    svh0clone->GetYaxis()->SetTitleSize(0.06);
    svh0clone->SetMinimum(0.5);
    for( unsigned int i=0; i<svh.size(); i++ ){
      if( svh_index[i] != 0 && svh_index[i] != 1){
	if( svh_index[i] == 2 ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(2);
	  svh[i]->SetFillColor(2);
	  svh[i]->SetMarkerColor(2);
	} else if( svh_index[i] == 3 ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kViolet+1);
	  svh[i]->SetFillColor(kViolet+1);
	  svh[i]->SetMarkerColor(kViolet+1);
	} else if( svh_index[i] == 4 ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(4);
	  svh[i]->SetFillColor(4);
	  svh[i]->SetMarkerColor(4);
	} else if( svh_index[i] == 5 ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(5);
	  svh[i]->SetFillColor(5);
	  svh[i]->SetMarkerColor(5);
	} else if( svh_index[i] == 6 ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(6);
	  svh[i]->SetFillColor(6);
	  svh[i]->SetMarkerColor(6);
	} else if( svh_index[i] == 7 ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(7);
	  svh[i]->SetFillColor(7);
	  svh[i]->SetMarkerColor(7);
	}
      } else if( svh_index[i] == 1 ){
	svh[i]->SetLineColor(3);
	svh[i]->SetLineWidth(2);
	svh[i]->SetFillColor(3);
	svh[i]->SetMarkerColor(3);
	//	svh[i]->Draw("same HIST");
      }
    }

    double lowmche=vh[1]->GetBinLowEdge(1);
    double highmche=vh[1]->GetBinLowEdge(vh[1]->GetNbinsX())+vh[1]->GetBinWidth(1);
    TH1D *mche=new TH1D("mche","mche",vh[1]->GetNbinsX(), lowmche, highmche);
    for( int ib=1; ib<=mche->GetNbinsX(); ib++ ){
      mche->SetBinContent(ib, vh[1]->GetBinContent(ib) );
      mche->SetBinError(ib, vh[1]->GetBinError(ib) );
    }
    mche->SetFillColor(kOrange-3);
    mche->SetFillStyle(3001);
    mche->SetLineColor(3);
    mche->SetLineWidth(2);
    mche->SetMarkerSize(0);
    mche->Draw("e2same");

    for( unsigned int i=0; i<svh.size(); i++ ){
      if( svh_index[i] == 0 ){
	svh[i]->Draw("same P 9");
	svh[i]->SetLineColor(1);
	svh[i]->SetLineWidth(2);
	svh[i]->SetMarkerSize(1);
	svh[i]->SetMarkerStyle(20);
	svh[i]->SetMarkerColor(1);
      }
    }


    len->AddEntry(vh[0], "Data");
    
    for( unsigned int i=2; i<svh.size(); i++ ){
      len->AddEntry(vh[i], vlenname[i]);
    }
    len->AddEntry(vh[1], "Total MC");

  } else  if( drawStack_ ){

    TH1D* svh0clone=(TH1D*)(svh[0]->Clone("svh0clone"));
    svh0clone->Scale(1.5);
    svh0clone->SetLineColor(0);
    svh0clone->SetMarkerColor(0);
    svh0clone->Draw();
    svh0clone->GetXaxis()->SetLabelFont(63);
    svh0clone->GetXaxis()->SetLabelSize(18);
    svh0clone->GetYaxis()->SetLabelFont(63);
    svh0clone->GetYaxis()->SetLabelSize(18);
    svh0clone->GetXaxis()->SetTitleSize(0.06);
    svh0clone->GetYaxis()->SetTitleSize(0.06);
    svh0clone->SetMinimum(0.5);

    THStack *hs=new THStack("hs","");
    for( unsigned int i=0; i<invsvh.size(); i++ ){
      if( invsvh_index[i] != 0 && invsvh_index[i] != 1){
	if( invsvh_index[i] == 2 ){
	  invsvh[i]->SetLineColor(2);
	  invsvh[i]->SetFillColor(2);
	  invsvh[i]->SetMarkerColor(2);
	  hs->Add(invsvh[i]);
	} else if( invsvh_index[i] == 3 ){
	  invsvh[i]->SetLineColor(kViolet+1);
	  invsvh[i]->SetFillColor(kViolet+1);
	  invsvh[i]->SetMarkerColor(kViolet+1);
	  hs->Add(invsvh[i]);
	} else if( invsvh_index[i] == 4 ){
	  invsvh[i]->SetLineColor(4);
	  invsvh[i]->SetFillColor(4);
	  invsvh[i]->SetMarkerColor(4);
	  hs->Add(invsvh[i]);
	} else if( invsvh_index[i] == 5 ){
	  invsvh[i]->SetLineColor(3);
	  invsvh[i]->SetFillColor(3);
	  invsvh[i]->SetMarkerColor(3);
	  hs->Add(invsvh[i]);
       	} else if( invsvh_index[i] == 6 ){
	  invsvh[i]->SetLineColor(6);
	  invsvh[i]->SetFillColor(6);
	  invsvh[i]->SetMarkerColor(6);
	  hs->Add(invsvh[i]);
       	} else if( invsvh_index[i] == 7 ){
	  invsvh[i]->SetLineColor(7);
	  invsvh[i]->SetFillColor(7);
	  invsvh[i]->SetMarkerColor(7);
	  hs->Add(invsvh[i]);
	}
      }
    }
    
    /*    vh[1]->SetLineColor(3);
    vh[1]->SetLineWidth(2);
    vh[1]->SetFillColor(3);
    vh[1]->SetMarkerColor(3);
    vh[1]->Draw("same HIST");*/

    hs->Draw("HIST 9 same");

    double lowmche=vh[1]->GetBinLowEdge(1);
    double highmche=vh[1]->GetBinLowEdge(vh[1]->GetNbinsX())+vh[1]->GetBinWidth(1);
    TH1D *mche=new TH1D("mche","mche",vh[1]->GetNbinsX(), lowmche, highmche);
    for( int ib=1; ib<=mche->GetNbinsX(); ib++ ){
      mche->SetBinContent(ib, vh[1]->GetBinContent(ib) );
      mche->SetBinError(ib, vh[1]->GetBinError(ib) );
    }
    mche->SetFillColor(5);
    mche->SetFillStyle(3001);
    mche->SetLineColor(5);
    mche->SetLineWidth(2);
    mche->SetMarkerSize(0);
    mche->Draw("e2same");


    for( unsigned int i=0; i<invsvh.size(); i++ ){
      if( invsvh_index[i] == 0 ){
	invsvh[i]->Draw("same P 9");
	invsvh[i]->SetLineColor(1);
	invsvh[i]->SetLineWidth(2);
	invsvh[i]->SetMarkerSize(1);
	invsvh[i]->SetMarkerStyle(20);
	invsvh[i]->SetMarkerColor(1);
      }
    }


    len->AddEntry(vh[0], "Data");
    
    for( unsigned int i=2; i<vh.size(); i++ ){
      len->AddEntry(vh[i], vlenname[i]);
    }
    //    len->AddEntry(vh[1], "Total MC");
  }

  //  TLegend *len1=new TLegend( 0.56, 0.70, 0.93, 0.90 );
  TLegend *len1=new TLegend( 0.20, 0.9, 0.65, 0.97 );
  len1->AddEntry("", Form("CMS Preliminary 2012 8 TeV, #int L dt = %.2f fb^{-1}", mcscale_/10.),"");
  //  len1->AddEntry("", "CMS Preliminary 2012 8 TeV","");
  //  len1->AddEntry("", Form("#int L dt = %.2f fb^{-1}", mcscale_/10.),"");
  len1->SetFillColor(0);
  len1->SetMargin(0.01);
  len1->SetLineColor(0);
  len1->SetBorderSize(0);
  len1->Draw();
  len->Draw();

  //Ration plots
  c1->cd();
  TPad *pad2=new TPad("pad2","",0,0.03,1,0.3);
  pad2->SetGridy();
  pad2->Draw();
  pad2->cd();

  TH1D* datah=(TH1D*)(vh[0]->Clone("datah"));
  TH1D* mch=(TH1D*)(vh[1]->Clone("mch"));
  datah->Divide(datah, mch);
  datah->GetXaxis()->SetLabelFont(63);
  datah->GetXaxis()->SetLabelSize(18);
  datah->GetXaxis()->SetTitleOffset(10);

  datah->GetYaxis()->SetNdivisions(2,0,0,kFALSE);
  datah->GetYaxis()->SetLabelFont(63);
  datah->GetYaxis()->SetLabelSize(18);
  datah->GetYaxis()->SetTitle("Data/MC");
  datah->GetYaxis()->SetTitleSize(0.15);
  datah->GetYaxis()->SetTitleOffset(0.3);
  datah->SetMarkerSize(0.5);
  datah->GetYaxis()->SetRangeUser(0.,2.);

  double lowmch=datah->GetBinLowEdge(1);
  double highmch=datah->GetBinLowEdge(datah->GetNbinsX())+datah->GetBinWidth(1);

  TH1D *mch1=new TH1D("mch1","mch1",datah->GetNbinsX(), lowmch, highmch);
  for( int ib=1; ib<=mch1->GetNbinsX(); ib++ ){
    mch1->SetBinContent(ib, 1.);
    if(vh[1]->GetBinContent(ib) > 1E-2){
      mch1->SetBinError(ib, vh[1]->GetBinError(ib)/vh[1]->GetBinContent(ib) );
      if( ib == 1 && whichplot == "nbjet" &&  startNJet > 0 ){
	mch1->SetBinError(ib, 0 );
      }
      if( ( ib == 1 || ib ==2 ) && whichplot == "njet" && ( normalEstimation_ == true || MuAddOrNot == false || whichpart == 1) ){
	mch1->SetBinError(ib, 0 );
      } else if ( ib == 1 && whichplot == "njet" && MuAddOrNot == true ){
	mch1->SetBinError(ib, 0 );
      }
    }
  }
  mch1->SetFillColor(kGray+1);
  mch1->SetFillStyle(3008);
  mch1->SetLineColor(0);
  mch1->SetMarkerSize(0);

  TH1D *mch11=new TH1D("mch11","mch11",datah->GetNbinsX(), lowmch, highmch);
  for( int ib=1; ib<=mch11->GetNbinsX(); ib++ ){
    mch11->SetBinContent(ib, 1.);
  }
  mch11->SetLineWidth(1);
  mch11->SetLineColor(1);
  mch11->SetMarkerSize(0);

  TH1D *datah1=new TH1D("datah1","datah1",datah->GetNbinsX(), lowmch, highmch);
  for( int ib=1; ib<=datah1->GetNbinsX(); ib++ ){
    datah1->SetBinContent(ib, datah->GetBinContent(ib));
    if( vh[0]->GetBinContent(ib) > 0 ){
      datah1->SetBinError(ib, vh[0]->GetBinError(ib)/vh[0]->GetBinContent(ib));
    }
  }


  datah->Draw("hist");
  datah->SetLineColor(0);
  datah->SetMarkerColor(0);
  mch1->Draw("e2same");
  mch11->Draw("same L hist");
  datah1->Draw("same");

  TString stack="";
  if(drawStack_){
    stack="Stack_";
  }

  if( whichpart == 1 ){
    pad1->SetLogy(0);
    c1->SaveAs( Form( "%s"+whichplot+"_HadSele_%s_%iTo%ib.%s",  stack.Data(), HTBins.Data(), startNJet-1, nJets+startNJet-2, epspng_.Data() ) );
    pad1->SetLogy();
    c1->SaveAs( Form( "%s"+whichplot+"_HadSele_%s_%iTo%ib_log.%s",  stack.Data(), HTBins.Data(), startNJet-1, nJets+startNJet-2, epspng_.Data() ) );
  } else if ( whichpart != 1 && MuAddOrNot == true && normalEstimation_ == false ){
    pad1->SetLogy(0);
    c1->SaveAs( Form( "%s"+whichplot+"_MuonAdded_%s_TrueTauHad%d_%s_%iTo%ib.%s", stack.Data(), HTBins.Data(), (int)(plotTrueTauHad_), HadTaucontrolTrig_.Data(), startNJet-1, nJets-startNJet-2, epspng_.Data() ) );
    pad1->SetLogy();
    c1->SaveAs( Form( "%s"+whichplot+"_MuonAdded_%s_TrueTauHad%d_%s_%iTo%ib_log.%s",  stack.Data(), HTBins.Data(), (int)(plotTrueTauHad_), HadTaucontrolTrig_.Data(), startNJet-1, nJets-startNJet-2, epspng_.Data()  ) );
  } else if ( whichpart !=1 && MuAddOrNot == false  && normalEstimation_ == false ){
    pad1->SetLogy(0);
    c1->SaveAs( Form( "%s"+whichplot+"_MuonNotAdded_%s_%iTo%ib.%s", stack.Data(), HTBins.Data(), startNJet-1, nJets+startNJet-2, epspng_.Data() ) );
    pad1->SetLogy();
    c1->SaveAs( Form( "%s"+whichplot+"_MuonNotAdded_%s_%iTo%ib_log.%s",  stack.Data(), HTBins.Data(), startNJet-1, nJets+startNJet-2, epspng_.Data() ) );
  } else if ( normalEstimation_ == true ){
    pad1->SetLogy(0);
    c1->SaveAs( Form( "%s"+whichplot+"_Muon_%s_%s%iTo%ib.%s", stack.Data(), HTBins.Data(), MuonNumber_.Data(), startNJet-1, nJets+startNJet-2, epspng_.Data() ) );
    pad1->SetLogy();
    c1->SaveAs( Form( "%s"+whichplot+"_Muon_%s_%s%iTo%ib_log.%s",  stack.Data(), HTBins.Data(), MuonNumber_.Data(), startNJet-1, nJets+startNJet-2, epspng_.Data() ) );
  }

  delete c1;
  delete Datah;
  delete MCh_total;
  delete MCh_TT;
  delete MCh_DY;
  delete MCh_WJ;
  delete MCh_SingleT;
  vlenname.clear();
  vh.clear();
  svh.clear();
  delete len1;
  len->Clear();
}




void basicPlots::getResults( TString HTBins, TString selection, int startNJet, int nJets ){

  TLegend *len=new TLegend( 0.70, 0.60, 0.93, 0.85 );
  //  TLegend *len=new TLegend( 0.70, 0.42, 0.93, 0.695 );
  len->SetColumnSeparation(0.2);
  len->SetFillColor(0);
  len->SetMargin(0.2);
  len->SetLineColor(0);
  len->SetBorderSize(0);
  //  len->SetTextSize(0.15);
  //  len->SetTextFont(13);
  len->SetTextAlign(22);
  int whichpart=1;
  bool MuAddOrNot=true;
  int rebin=50;
  if( selection == "HadSele"){
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MET (GeV)", "", 0, 800, "MET", len, 0.55, 10, 2, startNJet, nJets );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "HT (GeV)", "", 0., 1500, "HT", len, 0.55, 10., 2, startNJet, nJets );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MHT (GeV)", "", 0, 800, "MHT", len, 0.55, 10, 2, startNJet, nJets );
    rebin=20;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MHT/MET", "", 0, 3, "MHToverMET", len, 0.55, 10, 2, startNJet, nJets );
    rebin=1;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of b-jets", "", 0, 15, "nbjet", len, 0.55, 10, 2, startNJet, nJets );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of jets", "", 0, 15, "njet", len, 0.55, 10, 2, startNJet, nJets );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of Vertex", "", 0, 50 , "nVertex", len, 0.55, 10, 2, startNJet, nJets );
    rebin=5;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "#alpha_{T}", "", 0.5, 1.2, "AlphaT", len, 0, 0, 1, startNJet, nJets );
  }

  whichpart=2;
  MuAddOrNot=false;
  if( selection != "HadSele"){
    rebin=50;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MET (GeV)", "", 0, 800, "MET", len, 0, 10, 2, startNJet, nJets );
    rebin=2;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "M_{Z} (GeV)", "", 50., 150, "Zmass", len, 0, 10., 2, startNJet, nJets );
    rebin=1;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Iso_{#mu}", "", 0, 0.15, "muonIso", len, 0, 10., 2, startNJet, nJets );
    rebin=20;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "#mu p_{T} (GeV)", "", 0., 600, "muPt", len, 0, 10., 2, startNJet, nJets );
    rebin=50;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "HT (GeV)", "", 0., 1500, "HT", len, 0, 10., 2, startNJet, nJets );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MHT (GeV)", "", 0, 800, "MHT", len, 0, 10, 2, startNJet, nJets );
    rebin=20;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MHT/MET", "", 0, 3, "MHToverMET", len, 0, 10, 2, startNJet, nJets );

    rebin=1;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of jets", "", 0, 15, "njet", len, 0, 10, 2, startNJet, nJets);
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of b-jets", "", 0, 15, "nbjet", len, 0, 10, 2, startNJet, nJets);
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of Vertex", "", 0, 50 , "nVertex", len, 0, 10, 2, startNJet, nJets);
    rebin=5;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "#alpha_{T}", "", 0.2, 2.0, "AlphaT", len, 0, 0, 1, startNJet, nJets);
  }

}



/*void basicPlots::DrawHists( bool MuAddOrNot, TString HTBins, int whichpart, TString whichplot, int rebin, double lowalphaT, double highalphaT ){ // whichpart: if == 1 ==> numberator, if == 2 ==> dominator

  TCanvas *c1=new TCanvas();

  if( whichplot == "HT"){
    TH1D* MCh=HT( MCvf, vdirname, vhname_HT, mcscale_, rebin, lowalphaT, highalphaT );
    TH1D* Datah=HT( Datavf, vdirname, vhname_HT, datascale_, rebin, lowalphaT, highalphaT );

    vector<TH1D*> vh;
    vh.push_back(MCh);
    vh.push_back(Datah);

    TLegend *len=new TLegend( 0.65, 0.45, 0.85, 0.85 );

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
  }*/


