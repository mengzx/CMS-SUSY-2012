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

TH1D* basicPlots::Hist1D( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin, TString xAxisName, TString yAxisName, double xAxisRange1, double xAxisRange2, vector<double> trigeff) {

  playHist1D hf1d=playHist1D();

  TH1D *alT=hf1d.addHistForDiffFoldersFilesHists1D(invf, vdirname, vhname, trigeff );
  TH1D* formatalT=hf1d.formatHist(alT, inscale, xAxisName, yAxisName, xAxisRange1, xAxisRange2, rebin );
  return formatalT;
}




TH1D* basicPlots::Hist2D( vector<TFile*> invf, vector<TString> vdirname, vector<TString> vhname, double inscale, int rebin, TString xAxisName, TString yAxisName, double xAxisRange1, double xAxisRange2, double lowy, double highy, vector<double> trigeff ) {

  playHist2D hf2d=playHist2D();
  playHist1D hf1d=playHist1D();
  project2DHists pf=project2DHists();

  TH2D* hT=hf2d.addHistForDiffFoldersFilesHists2D( invf, vdirname, vhname, trigeff );
  TH1D* hTalphaTSlices=pf.projectX( hT, lowy, highy );
  TH1D* formathT=hf1d.formatHist(hTalphaTSlices, inscale, xAxisName, yAxisName, xAxisRange1, xAxisRange2, rebin );
  return formathT;
}


vector<TH1D*> basicPlots::getHists( bool MuAddOrNot, TString HTBins, int whichpart, int rebin, TString xAxisName, TString yAxisName, double xAxisRange1, double xAxisRange2, int dataMC, TString whichplot, bool separateSample, TString singleMCsample, double lowy, double highy, int OneDTwoD, int startNJet, int nJets, TString MuonNumber ){

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
  vector<double> nominaltrigeff=nominaltrigeff_pushback(HTBins);
  vector<double> HTATtrigeff=HTATTrigEff_pushback(HTBins);
  vector<double> SingleMutrigeff=SingleMuTrigEff_pushback(HTBins);
  vector<double> DiMutrigeff=DiMuTrigEff_pushback(HTBins);
  if( whichpart == 1 ){
    if( dataMC == 1 ){
      Datavf=Datavf_pushback(dir, signalDataset_, "HadSele"+signalTrig_, HTBins );
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
      Datavf=Datavf_pushback(dir, HadTaudataset_, "MuonAdded"+HadTaucontrolTrig_, HTBins );
    } else if( dataMC == 2 ){
      MCvf=MCvf_pushback(dir, MCsample_, "MuonAdded"+HadTaucontrolTrig_, HTBins, separateSample, singleMCsample );
    } else if( dataMC == 0 ){
      Datavf=Datavf_pushback(dir, HadTaudataset_, "MuonAdded"+HadTaucontrolTrig_, HTBins);
      MCvf=MCvf_pushback(dir, MCsample_, "MuonAdded"+HadTaucontrolTrig_, HTBins, separateSample, singleMCsample );
    }
    vdirname=dirName_pushback(folderlabel_ + MuonNumber, HTBins);
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
    vdirname=dirName_pushback(folderlabel_ + MuonNumber, HTBins);
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
    vdirname=dirName_pushback(folderlabel_ + MuonNumber, HTBins);
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
      Datah=Hist1D( Datavf, vdirname, vhname, datascale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
      vh.push_back( Datah );
    } else if( dataMC == 2 ){
      if( useCommonJson_ ){
	if( whichpart == 1 ){
	  if( doTrigCorr_ ){
	    MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, HTATtrigeff );
	    vh.push_back( MCh );
	  } else {
	    MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	    vh.push_back( MCh );
	  }
	} else {
	  if(  MuonNumber == "OneMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist1D( MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, SingleMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist1D( MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  } else if ( MuonNumber == "DiMuon_" ){
            if( doTrigCorr_ ){
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, DiMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  }
	} 
      } else {
	if( whichpart == 1 ){
	  if( doTrigCorr_ ){
	    MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_HT_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, HTATtrigeff );
	    vh.push_back( MCh );
	  } else {
	    MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_HT_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	    vh.push_back( MCh );
	  }
	} else {
	  if(  MuonNumber == "OneMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_SingleMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, SingleMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_SingleMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  } else if( MuonNumber == "DiMuon_" ){
            if( doTrigCorr_ ){
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_DiMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, DiMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_DiMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  }
	}
      }
      if( plotTrueTauHad_ ){
	MCh_truetau=Hist1D(  MCvf_truetauhad, vdirname_truetauhad, vhname_truetauhad, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	vh.push_back( MCh_truetau );
      }
    } else if( dataMC == 0){
      if( useCommonJson_ ){
	if( whichpart == 1 ){
	  if( doTrigCorr_ ){
	    MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, HTATtrigeff );
	    vh.push_back( MCh );
	  } else {
	    MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	    vh.push_back( MCh );
	  }
	} else {
	  if(  MuonNumber == "OneMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, SingleMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  } else if( MuonNumber == "DiMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, DiMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  }
	}
      } else {
	if( whichpart == 1 ){
	  if( doTrigCorr_ ){
	    MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_HT_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, HTATtrigeff );
	    vh.push_back( MCh );
	  } else {
	    MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_HT_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	    vh.push_back( MCh );
	  }
	} else {
	  if(  MuonNumber == "OneMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_SingleMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, SingleMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_SingleMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  } else if( MuonNumber == "DiMuon_" ){
            if( doTrigCorr_ ){
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_DiMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, DiMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist1D(  MCvf, vdirname, vhname, mcscale_DiMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  }
	}
      }
      Datah=Hist1D( Datavf, vdirname, vhname, datascale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
      vh.push_back( Datah );
      if( plotTrueTauHad_ ){
	MCh_truetau=Hist1D(  MCvf_truetauhad, vdirname_truetauhad, vhname_truetauhad, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, nominaltrigeff );
	vh.push_back( MCh_truetau );
      }
    }
  } else if( OneDTwoD == 2 ) {
    if( dataMC == 1 ){
      Datah=Hist2D( Datavf, vdirname, vhname, datascale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
      vh.push_back( Datah );
    } else if( dataMC == 2 ){
      if( useCommonJson_ ){
	if( whichpart == 1 ){
	  if( doTrigCorr_ ){
	    MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, HTATtrigeff );
	    vh.push_back( MCh );
	  } else {
	    MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	    vh.push_back( MCh );
	  }
	} else {
	  if(  MuonNumber == "OneMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, SingleMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  } else if( MuonNumber == "DiMuon_" ){
            if( doTrigCorr_ ){
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, DiMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  }
	}
      } else {
	if( whichpart == 1 ){
	  if( doTrigCorr_ ){
	    MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_HT_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, HTATtrigeff );
	    vh.push_back( MCh );
	  } else {
	    MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_HT_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	    vh.push_back( MCh );
	  }
	} else {
	  if(  MuonNumber == "OneMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_SingleMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, SingleMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_SingleMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  } else if( MuonNumber == "DiMuon_" ){
            if( doTrigCorr_ ){
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_DiMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, DiMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_DiMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  }
	}
      }
      if( plotTrueTauHad_ ){
	MCh_truetau=Hist2D(  MCvf_truetauhad, vdirname_truetauhad, vhname_truetauhad, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	vh.push_back( MCh_truetau );
      }
    } else if( dataMC == 0){
      if( useCommonJson_ ){
	if( whichpart == 1 ){
	  if( doTrigCorr_ ){
	    MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, HTATtrigeff );
	    vh.push_back( MCh );
	  } else {
	    MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	    vh.push_back( MCh );
	  }
	} else {
	  if(  MuonNumber == "OneMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, SingleMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  } else if( MuonNumber == "DiMuon_" ){
            if( doTrigCorr_ ){
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, DiMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  }
	}
      } else {
	if( whichpart == 1 ){
	  if( doTrigCorr_ ){
	    MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_HT_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, HTATtrigeff );
	    vh.push_back( MCh );
	  } else {
	    MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_HT_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	    vh.push_back( MCh );
	  }
	} else {
	  if(  MuonNumber == "OneMuon_" ){
	    if( doTrigCorr_ ){
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_SingleMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, SingleMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_SingleMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  } else if( MuonNumber == "DiMuon_" ){
            if( doTrigCorr_ ){
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_DiMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, DiMutrigeff );
	      vh.push_back( MCh );
	    } else {
	      MCh=Hist2D(  MCvf, vdirname, vhname, mcscale_DiMu_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	      vh.push_back( MCh );
	    }
	  }
	}
      }
      Datah=Hist2D( Datavf, vdirname, vhname, datascale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
      vh.push_back( Datah );
      if( plotTrueTauHad_ ){
	MCh_truetau=Hist2D(  MCvf_truetauhad, vdirname_truetauhad, vhname_truetauhad, mcscale_, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, lowy, highy, nominaltrigeff );
	vh.push_back( MCh_truetau );
      }
    }
  }
  return vh;
}



void basicPlots::drawHists( bool MuAddOrNot, TString HTBins, int whichpart, int rebin, TString xAxisName, TString yAxisName, double xAxisRange1, double xAxisRange2, TString whichplot, TLegend * len, double lowy, double highy, int OneDTwoD, int startNJet, int nJets, TString MuonNumber ){

  TCanvas *c1=new TCanvas("c1","c1", 1);

  getTranslationFactor tf=getTranslationFactor();
  playHist1D pf1d=playHist1D();

  vector<TString> vlenname;
  vector<TString> vhnames;
  vector<TH1D*> vh;

  if( hasData_ ){
    TH1D *Datah= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 1, whichplot, false, "", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(Datah);
    vlenname.push_back("Data");
    vhnames.push_back("Data");
  }

  if( hasMCtotal_ ){
    TH1D *MCh_total= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, false, "", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    if( hasZinvFromDY_ && whichpart == 1){
      TH1D *MCh_ZinvFromDY= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "ZinvFromDY", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
      TH1D* MCh_ZinvFromDYcopy=(TH1D*)(MCh_ZinvFromDY->Clone("MCh_ZinvFromDYcopy"));
      MCh_ZinvFromDYcopy->Scale(-1);
      MCh_total->Add(MCh_total,MCh_ZinvFromDYcopy);
      MCh_ZinvFromDY->Scale(3.);
      MCh_total->Add(MCh_total,MCh_ZinvFromDY);
    } else if ( hasZinvFromDY_ && whichpart != 1){
      TH1D *MCh_ZinvFromDY= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "ZinvFromDY", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
      TH1D* MCh_ZinvFromDYcopy=(TH1D*)(MCh_ZinvFromDY->Clone("MCh_ZinvFromDYcopy"));
      MCh_ZinvFromDYcopy->Scale(-1);
      MCh_total->Add(MCh_total,MCh_ZinvFromDYcopy);
    }
    vh.push_back(MCh_total);
    vlenname.push_back("Total MC");
    vhnames.push_back("MCtotal");
  }

  if( hasWJ_ ){
    TH1D *MCh_WJ= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "WJ", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_WJ);
    vlenname.push_back("W+jets");
    vhnames.push_back("WJ");
  }

  if( hasDY_ ){
    TH1D *MCh_DY= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "DY", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_DY);
    vlenname.push_back("Drell-Yan");
    vhnames.push_back("DY");
  }
  if( hasZinvFromDY_ && whichpart == 1){
    TH1D *MCh_ZinvFromDY= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "ZinvFromDY", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    MCh_ZinvFromDY->Scale(3.);
    vh.push_back(MCh_ZinvFromDY);
    vlenname.push_back("Z#rightarrow#nu#nu+jets");
    vhnames.push_back("ZinvFromDY");
  }
  if( hasTT_ ){
    TH1D *MCh_TT= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "TT", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_TT);
    vlenname.push_back("t#bar{t}");
    vhnames.push_back("TT");
  }
  if( hasSingleT_ ){
    TH1D *MCh_SingleT= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "SingleT", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_SingleT);
    vlenname.push_back("Single top");
    vhnames.push_back("SingleT");
  }
  if( hasZinv_ ){
    TH1D *MCh_Zinv= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "Zinv", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_Zinv);
    vlenname.push_back("Z#rightarrow#nu#nu+jets");
    vhnames.push_back("Zinv");
  }

  if( hasZinv_HT50To100_ ){
    TH1D *MCh_Zinv_HT50To100= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "Zinv_HT50To100", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_Zinv_HT50To100);
    vlenname.push_back("Z#rightarrow#nu#nu+jets (50<HT<100)");
    vhnames.push_back("Zinv_HT50To100");
  }

  if( hasZinv_FastSim_HT100To200_ ){
    TH1D *MCh_Zinv_FastSim_HT100To200= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "Zinv_FastSim_HT100To200", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_Zinv_FastSim_HT100To200);
    vlenname.push_back("Z#rightarrow#nu#nu+jets (100<HT<200, Fast)");
    vhnames.push_back("Zinv_FastSim_HT100To200");
  }

  if( hasZinv_FastSim_HT200To400_ ){
    TH1D *MCh_Zinv_FastSim_HT200To400= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "Zinv_FastSim_HT200To400", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_Zinv_FastSim_HT200To400);
    vlenname.push_back("Z#rightarrow#nu#nu+jets (200<HT<400, Fast)");
    vhnames.push_back("Zinv_FastSim_HT200To400");
  }

  if( hasZinv_HT400Toinf_ ){
    TH1D *MCh_Zinv_HT400Toinf= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "Zinv_HT400Toinf", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_Zinv_HT400Toinf);
    vlenname.push_back("Z#rightarrow#nu#nu+jets (HT>400)");
    vhnames.push_back("Zinv_HT400Toinf");
  }


  if( hasWJ_inclusive_ ){
    TH1D *MCh_WJ_inclusive= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "WJpartonHT_inclusive", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_WJ_inclusive);
    vlenname.push_back("W+jets (HT<250)");
    vhnames.push_back("WJ_inclusive");
  }

  if( hasWJ_FastSim_HT250To300_ ){
    TH1D *MCh_WJ_FastSim_HT250To300= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "WJpartonHT_FastSim_HT250To300", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_WJ_FastSim_HT250To300);
    vlenname.push_back("W+jets (250<HT<300, Fast)");
    vhnames.push_back("WJ_FastSim_HT250To300");
  }

  if( hasWJ_FastSim_HT300To400_ ){
    TH1D *MCh_WJ_FastSim_HT300To400= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "WJpartonHT_FastSim_HT300To400", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_WJ_FastSim_HT300To400);
    vlenname.push_back("W+jets (300<HT<400, Fast)");
    vhnames.push_back("WJ_FastSim_HT300To400");
  }

  if( hasWJ_HT250To300_ ){
    TH1D *MCh_WJ_HT250To300= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "WJpartonHT_HT250To300", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_WJ_HT250To300);
    vlenname.push_back("W+jets (250<HT<300)");
    vhnames.push_back("WJ_HT250To300");
  }

  if( hasWJ_HT300To400_ ){
    TH1D *MCh_WJ_HT300To400= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "WJpartonHT_HT300To400", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_WJ_HT300To400);
    vlenname.push_back("W+jets (300<HT<400)");
    vhnames.push_back("WJ_HT300To400");
  }

  if( hasWJ_HT400Toinf_ ){
    TH1D *MCh_WJ_HT400Toinf= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "WJpartonHT_HT400Toinf", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_WJ_HT400Toinf);
    vlenname.push_back("W+jets (HT>400)");
    vhnames.push_back("WJ_HT400Toinf");
  }


  if( hasDiBoson_ ){
    TH1D *MCh_DiBoson= (getHists( MuAddOrNot, HTBins, whichpart, rebin, xAxisName, yAxisName, xAxisRange1, xAxisRange2, 2, whichplot, true, "DiBoson", lowy, highy, OneDTwoD, startNJet, nJets, MuonNumber ))[0];
    vh.push_back(MCh_DiBoson);
    vlenname.push_back("Di-Boson");
    vhnames.push_back("DiBoson");
  }

  /*  //  MCh_TT->Scale(1.429822);
  TH1D *MCh_total_aftercorr=(TH1D*)(MCh_TT->Clone("MCh_total_aftercorr"));
  MCh_total_aftercorr->Add(MCh_total_aftercorr, MCh_Zinv);
  MCh_total_aftercorr->Add(MCh_total_aftercorr, MCh_DY);
  MCh_total_aftercorr->Add(MCh_total_aftercorr, MCh_WJ);
  MCh_total_aftercorr->Add(MCh_total_aftercorr, MCh_SingleT);
  MCh_total_aftercorr->Add(MCh_total_aftercorr, MCh_DiBoson);
  */


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
      if( vhnames[ svh_index[i] ] != "Data" && vhnames[ svh_index[i] ] != "MCtotal"){
	if( vhnames[ svh_index[i] ] == "WJ" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(2);
	  svh[i]->SetFillColor(2);
	  svh[i]->SetMarkerColor(2);
	} else if( vhnames[ svh_index[i] ] == "DY" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kViolet+1);
	  svh[i]->SetFillColor(kViolet+1);
	  svh[i]->SetMarkerColor(kViolet+1);
	} else if( vhnames[ svh_index[i] ] == "ZinvFromDY" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kYellow-3);
	  svh[i]->SetFillColor(kYellow-3);
	  svh[i]->SetMarkerColor(kYellow-3);
	} else if( vhnames[ svh_index[i] ] == "TT" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(4);
	  svh[i]->SetFillColor(4);
	  svh[i]->SetMarkerColor(4);
	} else if( vhnames[ svh_index[i] ] == "SingleT" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(5);
	  svh[i]->SetFillColor(5);
	  svh[i]->SetMarkerColor(5);
	} else if( vhnames[ svh_index[i] ] == "Zinv" ){
	  svh[i]->Draw("same HIST 9" );
	  svh[i]->SetLineColor(6);
	  svh[i]->SetFillColor(6);
	  svh[i]->SetMarkerColor(6);
	} else if( vhnames[ svh_index[i] ] == "DiBoson" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(7);
	  svh[i]->SetFillColor(7);
	  svh[i]->SetMarkerColor(7);
       	} else if( vhnames[ svh_index[i] ] == "Zinv_HT50To100" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kCyan-10);
	  svh[i]->SetFillColor(kCyan-10);
	  svh[i]->SetMarkerColor(kCyan-10);
	} else if( vhnames[ svh_index[i] ] == "Zinv_FastSim_HT100To200" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kCyan+1);
	  svh[i]->SetFillColor(kCyan+1);
	  svh[i]->SetMarkerColor(kCyan+1);
	} else if( vhnames[ svh_index[i] ] == "Zinv_FastSim_HT200To400" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kCyan+2);
	  svh[i]->SetFillColor(kCyan+2);
	  svh[i]->SetMarkerColor(kCyan+2);
	} else if( vhnames[ svh_index[i] ] == "Zinv_HT400Toinf" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kCyan+3);
	  svh[i]->SetFillColor(kCyan+3);
	  svh[i]->SetMarkerColor(kCyan+3);
       	} else if( vhnames[ svh_index[i] ] == "WJ_inclusive" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kRed-10);
	  svh[i]->SetFillColor(kRed-10);
	  svh[i]->SetMarkerColor(kRed-10);
	} else if( vhnames[ svh_index[i] ] == "WJ_FastSim_HT250To300" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kMagenta-10);
	  svh[i]->SetFillColor(kMagenta-10);
	  svh[i]->SetMarkerColor(kMagenta-10);
	} else if( vhnames[ svh_index[i] ] == "WJ_FastSim_HT300To400" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kMagenta-9);
	  svh[i]->SetFillColor(kMagenta-9);
	  svh[i]->SetMarkerColor(kMagenta-9);
	} else if( vhnames[ svh_index[i] ] == "WJ_HT250To300" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kRed-8);
	  svh[i]->SetFillColor(kRed-8);
	  svh[i]->SetMarkerColor(kRed-8);
	} else if( vhnames[ svh_index[i] ] == "WJ_HT300To400" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kRed-5);
	  svh[i]->SetFillColor(kRed-5);
	  svh[i]->SetMarkerColor(kRed-5);
	} else if( vhnames[ svh_index[i] ] == "WJ_HT400Toinf" ){
	  svh[i]->Draw("same HIST 9");
	  svh[i]->SetLineColor(kRed-1);
	  svh[i]->SetFillColor(kRed-1);
	  svh[i]->SetMarkerColor(kRed-1);
	} else if( vhnames[ svh_index[i] ] == "MCtotal" ){
	  svh[i]->SetLineColor(3);
	  svh[i]->SetLineWidth(2);
	  svh[i]->SetFillColor(3);
	  svh[i]->SetMarkerColor(3);
	//	svh[i]->Draw("same HIST");
	}
      }
    }

    if( vh.size() > 1 && hasMCtotal_){
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
      delete mche;
    }

    for( unsigned int i=0; i<svh.size(); i++ ){
      if( vhnames[ svh_index[i] ] == "Data" ){
	svh[i]->Draw("same P 9");
	svh[i]->SetLineColor(1);
	svh[i]->SetLineWidth(2);
	svh[i]->SetMarkerSize(1);
	svh[i]->SetMarkerStyle(20);
	svh[i]->SetMarkerColor(1);
      }
    }


    if( vh.size() > 0 && vhnames[0] == "Data"){
      len->AddEntry(vh[0], "Data");
    }    
    if( hasMCtotal_ && hasData_ ){
      for( unsigned int i=2; i<svh.size(); i++ ){
	len->AddEntry(vh[i], vlenname[i]);
      }
    } else{
      for( unsigned int i=0; i<vh.size(); i++ ){
	len->AddEntry(vh[i], vlenname[i]);
      }
    }
    if( vh.size() > 1 && hasMCtotal_){
      len->AddEntry(vh[1], "Total MC");
    }

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
      if( vhnames[ invsvh_index[i] ] != "Data" && vhnames[ invsvh_index[i] ] != "MCtotal"){
          if( vhnames[ invsvh_index[i] ] == "WJ" ){
	  invsvh[i]->SetLineColor(2);
	  invsvh[i]->SetFillColor(2);
	  invsvh[i]->SetMarkerColor(2);
	  hs->Add(invsvh[i]);
	  //	  cout<<"sample: "<< vhnames[ invsvh_index[i] ]<<" number: "<<invsvh[i]->Integral(1,10000)<<endl;
	} else if( vhnames[ invsvh_index[i] ] == "DY" ){
	  invsvh[i]->SetLineColor(kViolet+1);
	  invsvh[i]->SetFillColor(kViolet+1);
	  invsvh[i]->SetMarkerColor(kViolet+1);
	  hs->Add(invsvh[i]);
	  //	  cout<<"sample: "<< vhnames[ invsvh_index[i] ]<<" number: "<<invsvh[i]->Integral(1,10000)<<endl;
	} else if( vhnames[ invsvh_index[i] ] == "ZinvFromDY" ){
	  invsvh[i]->SetLineColor(kYellow-3);
	  invsvh[i]->SetFillColor(kYellow-3);
	  invsvh[i]->SetMarkerColor(kYellow-3);
	  hs->Add(invsvh[i]);
	  //	  cout<<"sample: "<< vhnames[ invsvh_index[i] ]<<" number: "<<invsvh[i]->Integral(1,10000)<<endl;
	} else if( vhnames[ invsvh_index[i] ] == "TT" ){
	  invsvh[i]->SetLineColor(4);
	  invsvh[i]->SetFillColor(4);
	  invsvh[i]->SetMarkerColor(4);
	  hs->Add(invsvh[i]);
	  //	  cout<<"sample: "<< vhnames[ invsvh_index[i] ]<<" number: "<<invsvh[i]->Integral(1,10000)<<endl;
	} else if( vhnames[ invsvh_index[i] ] == "SingleT" ){
	  invsvh[i]->SetLineColor(3);
	  invsvh[i]->SetFillColor(3);
	  invsvh[i]->SetMarkerColor(3);
	  hs->Add(invsvh[i]);
	  //	  cout<<"sample: "<< vhnames[ invsvh_index[i] ]<<" number: "<<invsvh[i]->Integral(1,10000)<<endl;
       	} else if( vhnames[ invsvh_index[i] ] == "Zinv" ){
	  invsvh[i]->SetLineColor(6);
	  invsvh[i]->SetFillColor(6);
	  invsvh[i]->SetMarkerColor(6);
	  hs->Add(invsvh[i]);
	  //	  cout<<"sample: "<< vhnames[ invsvh_index[i] ]<<" number: "<<invsvh[i]->Integral(1,10000)<<endl;
       	} else if( vhnames[ invsvh_index[i] ] == "DiBoson" ){
	  invsvh[i]->SetLineColor(7);
	  invsvh[i]->SetFillColor(7);
	  invsvh[i]->SetMarkerColor(7);
	  hs->Add(invsvh[i]);
	  //	  cout<<"sample: "<< vhnames[ invsvh_index[i] ]<<" number: "<<invsvh[i]->Integral(1,10000)<<endl;
       	} else if( vhnames[ invsvh_index[i] ] == "Zinv_HT50To100" ){
	  invsvh[i]->SetLineColor(kCyan-10);
	  invsvh[i]->SetFillColor(kCyan-10);
	  invsvh[i]->SetMarkerColor(kCyan-10);
	  hs->Add(invsvh[i]);
	} else if( vhnames[ invsvh_index[i] ] == "Zinv_FastSim_HT100To200" ){
	  invsvh[i]->SetLineColor(kCyan+1);
	  invsvh[i]->SetFillColor(kCyan+1);
	  invsvh[i]->SetMarkerColor(kCyan+1);
	  hs->Add(invsvh[i]);
	} else if( vhnames[ invsvh_index[i] ] == "Zinv_FastSim_HT200To400" ){
	  invsvh[i]->SetLineColor(kCyan+2);
	  invsvh[i]->SetFillColor(kCyan+2);
	  invsvh[i]->SetMarkerColor(kCyan+2);
	  hs->Add(invsvh[i]);
	} else if( vhnames[ invsvh_index[i] ] == "Zinv_HT400Toinf" ){
	  invsvh[i]->SetLineColor(kCyan+3);
	  invsvh[i]->SetFillColor(kCyan+3);
	  invsvh[i]->SetMarkerColor(kCyan+3);
	  hs->Add(invsvh[i]);
       	} else if( vhnames[ invsvh_index[i] ] == "WJ_inclusive" ){
	  invsvh[i]->SetLineColor(kRed-10);
	  invsvh[i]->SetFillColor(kRed-10);
	  invsvh[i]->SetMarkerColor(kRed-10);
	  hs->Add(invsvh[i]);
	} else if( vhnames[ invsvh_index[i] ] == "WJ_FastSim_HT250To300" ){
	  invsvh[i]->SetLineColor(kMagenta-10);
	  invsvh[i]->SetFillColor(kMagenta-10);
	  invsvh[i]->SetMarkerColor(kMagenta-10);
	  hs->Add(invsvh[i]);
	} else if( vhnames[ invsvh_index[i] ] == "WJ_FastSim_HT300To400" ){
	  invsvh[i]->SetLineColor(kMagenta-9);
	  invsvh[i]->SetFillColor(kMagenta-9);
	  invsvh[i]->SetMarkerColor(kMagenta-9);
	  hs->Add(invsvh[i]);
	} else if( vhnames[ invsvh_index[i] ] == "WJ_HT250To300" ){
	  invsvh[i]->SetLineColor(kRed-8);
	  invsvh[i]->SetFillColor(kRed-8);
	  invsvh[i]->SetMarkerColor(kRed-8);
	  hs->Add(invsvh[i]);
	} else if( vhnames[ invsvh_index[i] ] == "WJ_HT300To400" ){
	  invsvh[i]->SetLineColor(kRed-5);
	  invsvh[i]->SetFillColor(kRed-5);
	  invsvh[i]->SetMarkerColor(kRed-5);
	  hs->Add(invsvh[i]);
	} else if( vhnames[ invsvh_index[i] ] == "WJ_HT400Toinf" ){
	  invsvh[i]->SetLineColor(kRed-1);
	  invsvh[i]->SetFillColor(kRed-1);
	  invsvh[i]->SetMarkerColor(kRed-1);
	  hs->Add(invsvh[i]);
	}
      }
    }
    

    hs->Draw("HIST 9 same");

    if( vh.size() > 1 && hasMCtotal_){
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
    }

    for( unsigned int i=0; i<invsvh.size(); i++ ){
      if( vhnames[ invsvh_index[i] ] == "Data" ){
	invsvh[i]->Draw("same P 9");
	invsvh[i]->SetLineColor(1);
	invsvh[i]->SetLineWidth(2);
	invsvh[i]->SetMarkerSize(1);
	invsvh[i]->SetMarkerStyle(20);
	invsvh[i]->SetMarkerColor(1);
      }
    }

    if( vh.size() > 0 && vhnames[0] == "Data"){
      len->AddEntry(vh[0], "Data");
    }
    if( hasMCtotal_ && hasData_ ){
      for( unsigned int i=2; i<vh.size(); i++ ){
	len->AddEntry(vh[i], vlenname[i]);
      }
    } else{
      for( unsigned int i=0; i<vh.size(); i++ ){
	len->AddEntry(vh[i], vlenname[i]);
      }
    }
  }

  //  TLegend *len1=new TLegend( 0.56, 0.70, 0.93, 0.90 );
  //  len1->AddEntry("", "CMS Preliminary 2012 8 TeV","");
  //  len1->AddEntry("", Form("#int L dt = %.2f fb^{-1}", mcscale_/10.),"");
  TLegend *len1=new TLegend( 0.20, 0.9, 0.65, 0.97 );
  if( useCommonJson_ ){
    len1->AddEntry("", Form("CMS Preliminary 2012 8 TeV, #int L dt = %.2f fb^{-1}", mcscale_/10.),"");
  } else {
    if( whichpart == 1 ){
      len1->AddEntry("", Form("CMS Preliminary 2012 8 TeV, #int L dt = %.2f fb^{-1}", mcscale_HT_/10.),"");
    } else {
      if( MuonNumber == "OneMuon_"){
	len1->AddEntry("", Form("CMS Preliminary 2012 8 TeV, #int L dt = %.2f fb^{-1}", mcscale_SingleMu_/10.),"");
      } else if( MuonNumber == "DiMuon_"){
	len1->AddEntry("", Form("CMS Preliminary 2012 8 TeV, #int L dt = %.2f fb^{-1}", mcscale_DiMu_/10.),"");
      }
    }
  }
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
  if( vh.size() > 1 && vhnames[0] == "Data"){
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
  }
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
    c1->SaveAs( Form( "%s"+whichplot+"_Muon_%s_%s%iTo%ib.%s", stack.Data(), HTBins.Data(), MuonNumber.Data(), startNJet-1, nJets+startNJet-2, epspng_.Data() ) );
    pad1->SetLogy();
    c1->SaveAs( Form( "%s"+whichplot+"_Muon_%s_%s%iTo%ib_log.%s",  stack.Data(), HTBins.Data(), MuonNumber.Data(), startNJet-1, nJets+startNJet-2, epspng_.Data() ) );
  }

  delete pad1;
  delete pad2;
  delete c1;
  vlenname.clear();
  vhnames.clear();
  vh.clear();
  svh.clear();
  delete len1;
  len->Clear();
  closefV();
}




void basicPlots::getResults( TString HTBins, TString selection, int startNJet, int nJets, TString MuonNumber ){

  TLegend *len=new TLegend( 0.70, 0.60, 0.93, 0.85 );
  //  TLegend *len=new TLegend( 0.70, 0.50, 0.93, 0.75 );
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
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MET (GeV)", "", 0, 800, "MET", len, 0.55, 10, 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MHT (GeV)", "", 0, 800, "MHT", len, 0.55, 10, 2, startNJet, nJets, MuonNumber );
    rebin=50;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "HT (GeV)", "", 0., 1075., "HT", len, 0.55, 10., 2, startNJet, nJets, MuonNumber );
    rebin=20;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MHT/MET", "", 0, 3, "MHToverMET", len, 0.55, 10, 2, startNJet, nJets, MuonNumber );
    rebin=1;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of b-jets", "", 0, 15, "nbjet", len, 0.55, 10, 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of jets", "", 0, 15, "njet", len, 0.55, 10, 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of Vertex", "", 0, 50 , "nVertex", len, 0.55, 10, 2, startNJet, nJets, MuonNumber );
    rebin=5;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "#alpha_{T}", "", 0.5, 1.2, "AlphaT", len, 0, 0, 1, startNJet, nJets, MuonNumber );
  }

  whichpart=2;
  MuAddOrNot=false;
  if( selection != "HadSele"){
    rebin=50;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MET (GeV)", "", 0, 800, "MET", len, 0, 10, 2, startNJet, nJets, MuonNumber );
    rebin=2;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "M_{Z} (GeV)", "", 50., 150, "Zmass", len, 0, 10., 2, startNJet, nJets, MuonNumber );
    rebin=1;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Iso_{#mu}", "", 0, 0.15, "muonIso", len, 0, 10., 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Iso_{#mu}^{ECAL}", "", 0, 0.15, "muonIsoECAL", len, 0, 10., 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Iso_{#mu}^{HCAL}", "", 0, 0.15, "muonIsoHCAL", len, 0, 10., 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Iso_{#mu}^{Trk}", "", 0, 0.15, "muonIsoTrk", len, 0, 10., 2, startNJet, nJets, MuonNumber );
    rebin=20;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "#mu p_{T} (GeV)", "", 0., 600, "muPt", len, 0, 10., 2, startNJet, nJets, MuonNumber );
    rebin=50;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "HT (GeV)", "", 0., 1075, "HT", len, 0, 10., 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MHT (GeV)", "", 0, 800, "MHT", len, 0, 10, 2, startNJet, nJets, MuonNumber );
    rebin=20;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "MHT/MET", "", 0, 3, "MHToverMET", len, 0, 10, 2, startNJet, nJets, MuonNumber );

    rebin=1;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of jets", "", 0, 15, "njet", len, 0., 10, 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of b-jets", "", 0, 15, "nbjet", len, 0., 10, 2, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Number of Vertex", "", 0, 50 , "nVertex", len, 0, 10, 2, startNJet, nJets, MuonNumber );
    rebin=5;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "#alpha_{T}", "", 0.2, 2.0, "AlphaT", len, 0, 0, 1, startNJet, nJets, MuonNumber );
    /*   rebin=1;
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Trigger Precale (Mu13_Mu8)", "", 0, 3000, "trigMu13Mu8prescale", len, 0, 0, 1, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Trigger Precale (Mu17_Mu8)", "", 0, 3000, "trigMu17Mu8prescale", len, 0, 0, 1, startNJet, nJets, MuonNumber );
    drawHists( MuAddOrNot, HTBins, whichpart, rebin, "Trigger Precale (Mu17_TkMu8)", "", 0, 3000, "trigMu17TkMu8prescale", len, 0, 0, 1, startNJet, nJets, MuonNumber );
    */

  }

  delete len;
}




