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
vector<TH2D*> getTranslationFactor::TranslationFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, TString MuonNumber, int startNJet, int nJets ){
  playHist2D factor=playHist2D();
  vector<double> nominaltrigeff=nominaltrigeff_pushback(HTBins);

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
  double scalein_numer=1.;
  double scalein_domin=1.;
  TString digit1in="";
  if( isData == true ){
    scalein_numer=datascale_;
    scalein_domin=datascale_;
    digit1in="g";
  } else {
    if( useCommonJson_ ){
      scalein_numer = mcscale_;
      scalein_domin = mcscale_;
    } else {
      scalein_numer = mcscale_HT_;
      if( MuonNumber == "OneMuon_" ){
	scalein_domin = mcscale_SingleMu_;
      } else if ( MuonNumber == "DiMuon_"){
	scalein_domin = mcscale_DiMu_;
      }
    }
    digit1in=digit1_;
  }

  vector<TString> dirNamehad=dirName_pushback(folderlabel_ + "", HTBins);
  vector<TString> dirName1mu=dirName_pushback(folderlabel_ + MuonNumber, HTBins);

  vector<TString> hNamehad;
  vector<TString> hName1mu=vhname_pusback_domin(MuAddOrNot, fullesti, startNJet, nJets);

  if( isData == true ){
    hNamehad=vhname_pusback_data(MuAddOrNot, fullesti, startNJet, nJets);
  } else{
    hNamehad=vhname_pusback_numer(MuAddOrNot, fullesti, startNJet, nJets);
  }

  if( MuAddOrNot == true  && normalEstimation_ == false ){
    vector<TH2D*> reh2d;

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D( vf_had, dirNamehad, hNamehad, nominaltrigeff );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D( vf_1mu, dirName1mu, hName1mu, nominaltrigeff );

    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }
    
    TH2D* factor_h=(TH2D*)( AlphaT_vs_HT_numer->Clone( "factor_h" ) );
    factor_h->Divide( AlphaT_vs_HT_numer, AlphaT_vs_HT_domin );

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein_numer, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein_domin, digit1in ) );
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

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersAndFiles_SubtrackHists2D(vf_had, dirNamehad, vhname_first, vhname_second, nominaltrigeff );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu, nominaltrigeff );

    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }
    
    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein_numer, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein_domin, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    
    return reh2d;
  }

  if( MuAddOrNot == false && fullesti == false && normalEstimation_ == false ){
    vector<TH2D*> reh2d;

    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad, nominaltrigeff );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu, nominaltrigeff );

    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }
    
    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein_numer, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein_domin, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }

  if( normalEstimation_ == true ){
    vector<TH2D*> reh2d;
    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad, nominaltrigeff );
    cout<<" dirName1mu="<<dirName1mu[0]<<" hName1mu="<<hName1mu[0]<<" nominaltrigeff="<<nominaltrigeff[0]<<endl;
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu, nominaltrigeff );
    cout<<"hi"<<endl;
    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }

    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein_numer, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein_domin, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }

}




// -----------------------------------------------------------------------------
//
vector<TH2D*> getTranslationFactor::TranslationFactor_iTojJet( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber ){
  vector<double> nominaltrigeff=nominaltrigeff_pushback(HTBins);
  playHist2D factor=playHist2D();

  //  TString dirhad = inidir_ + "rootfiles/hadronicSele" + subdir_;
  TString dirhad = inidir_ + "rootfiles/oneMuonSele/muonpT45GeV" + subdir_;

  TString dir1mu="";
  if( normalEstimation_ == true){
    dir1mu = inidir_ + "rootfiles/oneMuonSele/muonpT45GeV" + subdir_;
  }

  vector<TFile*> vf_had;
  if( isData == true ){
    vf_had=Datavf_pushback(dirhad, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
  } else {
    vf_had=MCvf_pushback(dirhad, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, false, "");
  }

  vector<TFile*> vf_1mu;
  if( isData == true ){
    vf_1mu=Datavf_pushback(dir1mu, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
  } else vf_1mu=MCvf_pushback(dir1mu, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, false, "");

  double scalein_numer=1.;
  double scalein_domin=1.;
  TString digit1in="";
  if( isData == true ){
    scalein_numer=datascale_;
    scalein_domin=datascale_;
    digit1in="g";
  } else {
    if( useCommonJson_ ){
      scalein_numer = mcscale_;
      scalein_domin = mcscale_;
    } else {
      if( MuonNumber == "OneMuon_" ){
        scalein_numer = mcscale_SingleMu_;
	scalein_domin = mcscale_SingleMu_;
      } else if ( MuonNumber == "DiMuon_"){
	scalein_domin = mcscale_DiMu_;
	scalein_numer = mcscale_DiMu_;
      }
    }
    digit1in=digit1_;
  }


  vector<TString> dirNamehad=dirName_pushback(folderlabel_ + MuonNumber, HTBins);
  vector<TString> dirName1mu=dirName_pushback(folderlabel_ + MuonNumber, HTBins);

  vector<TString> hNamehad;
  vector<TString> hName1mu;
    //MuaddOrNot and fullesti is arbitarilly selected, because itoj jet estimation need normalestimation == true
  if( normalEstimation_ == true ){
    if( isData == true ){
      hNamehad=vhname_pusback_data(false, true, jJetStart, jJet_n);
    } else{
      hNamehad=vhname_pusback_numer(false, true, jJetStart, jJet_n);
    }
    hName1mu=vhname_pusback_domin(false, true, iJetStart, iJet_n);
  }
    //MuaddOrNot and fullesti is arbitarilly selected, because itoj jet estimation need normalestimation == true
  if( normalEstimation_ == true ){
    vector<TH2D*> reh2d;
    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad, nominaltrigeff );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu, nominaltrigeff );
    
    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
    }

    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein_numer, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein_domin, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }

}




// -----------------------------------------------------------------------------
//
vector<TH2D*> getTranslationFactor::TranslationFactor_1To2Mu( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, int startNJet, int nJets ){
  vector<double> nominaltrigeff=nominaltrigeff_pushback(HTBins);
  playHist2D factor=playHist2D();

  TString dir1mu="";
  dir1mu = inidir_ + "rootfiles/oneMuonSele/muonpT45GeV" + subdir_;

  vector<TFile*> vf_had;
  if( normalEstimation_ == true ){
    if( isData == true ){
      vf_had=Datavf_pushback(dir1mu, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
    } else {
      vf_had=MCvf_pushback(dir1mu, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, false, "");
    }
  }

  vector<TFile*> vf_1mu;
  if( isData == true ){
    vf_1mu=Datavf_pushback(dir1mu, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
  } else vf_1mu=MCvf_pushback(dir1mu, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, false, "");

  double scalein_numer=1.;
  double scalein_domin=1.;
  TString digit1in="";
  if( isData == true ){
    scalein_numer=datascale_;
    scalein_domin=datascale_;
    digit1in="g";
  } else {
    if( useCommonJson_ ){
      scalein_numer = mcscale_;
      scalein_domin = mcscale_;
    } else {
      scalein_numer = mcscale_DiMu_;
      scalein_domin = mcscale_SingleMu_;
    }
    digit1in=digit1_;
  }


  vector<TString> dirNamehad=dirName_pushback(folderlabel_ + "DiMuon_", HTBins);
  vector<TString> dirName1mu=dirName_pushback(folderlabel_ + "OneMuon_", HTBins);

  vector<TString> hNamehad;
  //MuaddOrNot and fullesti is arbitarilly selected, because 1to2 muon estimation need normalestimation == true
  vector<TString> hName1mu;
  if( normalEstimation_ == true ){
    hName1mu=vhname_pusback_domin(false, true, startNJet, nJets);
    if( isData == true ){
      hNamehad=vhname_pusback_data(false, true, startNJet, nJets);
    } else{
      hNamehad=vhname_pusback_numer(false, true, startNJet, nJets);
    }
  }
  //Above MuaddOrNot and fullesti is arbitarilly selected, because 1to2 muon estimation need normalestimation == true

  if( normalEstimation_ == true ){
    vector<TH2D*> reh2d;
    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad, nominaltrigeff );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu, nominaltrigeff );
    
    if( notCutAlphaT_ ){
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_domin_clone );
      TH2D* AlphaT_vs_HT_numer_clone=(TH2D*)(AlphaT_vs_HT_numer->Clone("AlphaT_vs_HT_numer_clone"));
      AlphaT_vs_HT_numer=factor.ReFillHist_AlphaTVSHT( AlphaT_vs_HT_numer_clone );
    }

    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein_numer, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein_domin, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }
}


// -----------------------------------------------------------------------------
//
vector<TH2D*> getTranslationFactor::TranslationFactor_AT( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, int startNJet, int nJets, TString MuonNumber, TString closuretestformat ){
  vector<double> nominaltrigeff=nominaltrigeff_pushback(HTBins);
  playHist2D factor=playHist2D();

  TString dir1mu="";
  dir1mu = inidir_ + "rootfiles/oneMuonSele/muonpT45GeV" + subdir_;

  vector<TFile*> vf_had;
  if( normalEstimation_ == true ){
    if( isData == true ){
      vf_had=Datavf_pushback(dir1mu, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
    } else {
      vf_had=MCvf_pushback(dir1mu, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, false, "");
    }
  }

  vector<TFile*> vf_1mu;
  if( isData == true ){
    vf_1mu=Datavf_pushback(dir1mu, controlDataset_, "Muon"+NormalcontrolTrig_, HTBins);
  } else vf_1mu=MCvf_pushback(dir1mu, MCsample_, "Muon"+NormalcontrolTrig_, HTBins, false, "");

  double scalein_numer=1.;
  double scalein_domin=1.;
  TString digit1in="";
  if( isData == true ){
    scalein_numer=datascale_;
    scalein_domin=datascale_;
    digit1in="g";
  } else {
    if( useCommonJson_ ){
      scalein_numer = mcscale_;
      scalein_domin = mcscale_;
    } else {
      scalein_numer = mcscale_DiMu_;
      scalein_domin = mcscale_SingleMu_;
    }
    digit1in=digit1_;
  }


  vector<TString> dirNamehad=dirName_pushback(folderlabel_ + MuonNumber, HTBins);
  vector<TString> dirName1mu=dirName_pushback(folderlabel_ + MuonNumber, HTBins);

  vector<TString> hNamehad;
  //MuaddOrNot and fullesti is arbitarilly selected, because 1to2 muon estimation need normalestimation == true
  vector<TString> hName1mu;
  if( normalEstimation_ == true ){
    hName1mu=vhname_pusback_domin(false, true, startNJet, nJets);
    if( isData == true ){
      hNamehad=vhname_pusback_data(false, true, startNJet, nJets);
    } else{
      hNamehad=vhname_pusback_numer(false, true, startNJet, nJets);
    }
  }
  //Above MuaddOrNot and fullesti is arbitarilly selected, because 1to2 muon estimation need normalestimation == true

  if( normalEstimation_ == true ){
    vector<TH2D*> reh2d;
    TH2D* AlphaT_vs_HT_numer=factor.addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad, nominaltrigeff );
    TH2D* AlphaT_vs_HT_domin=factor.addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu, nominaltrigeff );
    
      TH2D* AlphaT_vs_HT_domin_clone=(TH2D*)(AlphaT_vs_HT_domin->Clone("AlphaT_vs_HT_domin_clone"));
      AlphaT_vs_HT_domin=factor.ReFillHist_low( AlphaT_vs_HT_domin_clone, 0.55 );
      TH2D* AlphaT_vs_HT_numer_clone=(TH2D*)(AlphaT_vs_HT_numer->Clone("AlphaT_vs_HT_numer_clone"));
      AlphaT_vs_HT_numer=factor.ReFillHist_high( AlphaT_vs_HT_numer_clone, 0.55);

    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_numer, scalein_numer, digit1in ) );
    reh2d.push_back( factor.formatHist( AlphaT_vs_HT_domin, scalein_domin, digit1in ) );
    reh2d.push_back( factor.formatHist( factor_h, 1., digit2_ ) );
    return reh2d;
  }
}


// -----------------------------------------------------------------------------
//
TH2D* getTranslationFactor::getFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int startNJet, int nJets ){
  if( closureTests == "1To2Mu" ){
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor_1To2Mu( MuAddOrNot, fullesti, HTBins, isData, startNJet, nJets );
    return factorHist_hasTauHadToMuAdded[2];
  } else if ( closureTests == "iTojJet"){
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor_iTojJet( MuAddOrNot, fullesti, HTBins, isData, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber );
    return factorHist_hasTauHadToMuAdded[2];
  }else {
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor( MuAddOrNot, fullesti, HTBins, isData, MuonNumber, startNJet, nJets );
    return factorHist_hasTauHadToMuAdded[2];
  }
}

// -----------------------------------------------------------------------------
//
TH2D* getTranslationFactor::getNumerMC( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int startNJet, int nJets ){
  if( closureTests == "1To2Mu" ){
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor_1To2Mu( MuAddOrNot, fullesti, HTBins, false, startNJet, nJets );
    return factorHist_hasTauHadToMuAdded[0];
  } else if ( closureTests == "iTojJet"){
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor_iTojJet( MuAddOrNot, fullesti, HTBins, false, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber );
    return factorHist_hasTauHadToMuAdded[0];
  } else {
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor( MuAddOrNot, fullesti, HTBins, false, MuonNumber, startNJet, nJets );
    return factorHist_hasTauHadToMuAdded[0];
  }
}

// -----------------------------------------------------------------------------
//
TH2D* getTranslationFactor::getDominMC( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJets ){
  if( closureTests == "1To2Mu" ){
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor_1To2Mu( MuAddOrNot, fullesti, HTBins, false, StartNJet, NJets );
    return factorHist_hasTauHadToMuAdded[1];
  } else if ( closureTests == "iTojJet"){
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor_iTojJet( MuAddOrNot, fullesti, HTBins, false, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber );
    return factorHist_hasTauHadToMuAdded[1];
  } else {
    vector<TH2D*> factorHist_hasTauHadToMuAdded=TranslationFactor( MuAddOrNot, fullesti, HTBins, false, MuonNumber, StartNJet, NJets );
    return factorHist_hasTauHadToMuAdded[1];
  }
}

// -----------------------------------------------------------------------------
//
TH2D* getTranslationFactor::getControlData( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJets  ){
  if( closureTests == "1To2Mu" ){
    vector<TH2D*> Data1mu=TranslationFactor_1To2Mu( MuAddOrNot, fullesti, HTBins, true, StartNJet, NJets );
    return Data1mu[1];
  } else if ( closureTests == "iTojJet"){
    vector<TH2D*> Data1mu=TranslationFactor_iTojJet( MuAddOrNot, fullesti, HTBins, true, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber );
    return Data1mu[1];
  } else {
    vector<TH2D*> Data1mu=TranslationFactor( MuAddOrNot, fullesti, HTBins, true, MuonNumber, StartNJet, NJets );
    return Data1mu[1];
  }
}

TH2D* getTranslationFactor::getYieldData( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJets ){
  if( closureTests == "1To2Mu" ){
    vector<TH2D*> Data1mu=TranslationFactor_1To2Mu( MuAddOrNot, fullesti, HTBins, true, StartNJet, NJets );
    return Data1mu[0];
  } else if ( closureTests == "iTojJet"){
    vector<TH2D*> Data1mu=TranslationFactor_iTojJet( MuAddOrNot, fullesti, HTBins, true, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber );
    return Data1mu[0];
  } else{
    vector<TH2D*> Data1mu=TranslationFactor( MuAddOrNot, fullesti, HTBins, true, MuonNumber, StartNJet, NJets );
    return Data1mu[0];
  }
}


TH2D* getTranslationFactor::getPredBG( bool MuAddOrNot, bool fullesti, TString HTBins, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJets ){
  TH2D* factorh=getFactor( MuAddOrNot, fullesti, HTBins, false, closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
  TH2D* Data1mu=getControlData( MuAddOrNot, fullesti, HTBins, closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
  TH2D* pred=(TH2D*)(Data1mu->Clone("pred"));
  pred->Multiply(pred, factorh);
  return pred;
}


// -----------------------------------------------------------------------------
//
void getTranslationFactor::baseCheck( bool MuAddOrNot, bool fullesti, TString HTBins, TString plotname, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJets ){
  playHist2D factor=playHist2D();
  TCanvas *c1=new TCanvas();
  vector<TLine*> lines=factor.Lines();

  vector<TH2D*> factorHist;
  if( closureTests == "1To2Mu"){
    factorHist=TranslationFactor_1To2Mu( MuAddOrNot, fullesti, HTBins, isData, StartNJet, NJets );
  } else if ( closureTests == "iTojJet" ){
    factorHist=TranslationFactor_iTojJet( MuAddOrNot, fullesti, HTBins, isData, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber );
  } else {
    factorHist=TranslationFactor( MuAddOrNot, fullesti, HTBins, isData, MuonNumber, StartNJet, NJets );
  }
  factorHist[0]->Draw("colz");
  factorHist[0]->Draw("text30same");

  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  if( closureTests == "1To2Mu"){
    c1->SaveAs("numer"+plotname+"_"+closureTests+".eps");
  } else if( closureTests == "iTojJet" ){
    c1->SaveAs( Form( "numer"+plotname+"_"+closureTests+"_%s%d_%dTo%d_%d.eps", MuonNumber.Data(), iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 ) );
  } else {
    c1->SaveAs("numer"+MuonNumber+plotname+"_"+closureTests+".eps");
  }
  c1->Update();
  c1->Clear();

  factorHist[1]->Draw("colz");
  factorHist[1]->Draw("text30same");

  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }

  if( closureTests == "1To2Mu"){
    c1->SaveAs("domin"+plotname+"_"+closureTests+".eps");
  } else if( closureTests == "iTojJet" ){
    c1->SaveAs( Form( "domin"+plotname+"_"+closureTests+"_%s%d_%dTo%d_%d.eps", MuonNumber.Data(), iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 ) );
  } else {
    c1->SaveAs("domin"+MuonNumber+plotname+"_"+closureTests+".eps");
  }
  c1->Update();
  c1->Clear();


  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  factorHist[2]->Draw("colz");
  factorHist[2]->Draw("text30same");

  if( closureTests == "1To2Mu"){
    c1->SaveAs("factor"+plotname+"_"+closureTests+".eps");
  } else if( closureTests == "iTojJet" ){
    c1->SaveAs( Form( "factor"+plotname+"_"+closureTests+"_%d_%dTo%d_%d.eps", iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 ) );
  } else {
    c1->SaveAs("factor"+plotname+"_"+closureTests+".eps");
  }
  c1->Update();
  c1->Clear();
}

void getTranslationFactor::getResults( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString MuonNumber, int StartNJet, int NJets ){
  playHist2D factor=playHist2D();

  if(normalEstimation_ == true ){
    baseCheck( false, true, "all", "", false, closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
    baseCheck( false, true, "all", "_Data", true, closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
  } else {
    baseCheck( true, false, "all", "tauHadEsti_AddMuToAT", false, closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
    baseCheck( true, false, "all", "tauHadEsti_AddMuToAT", false, closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
    baseCheck( false, false, "all", "LepEsti_NotAddMuToAT", false, closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
    baseCheck( false, false, "all", "LepEsti_NotAddMuToAT_Data", true, closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
  }

  TH2D* pred_AddMu;
  TH2D* pred_NotTauHad;
  TH2D* pred_Lep;
  if(normalEstimation_ == true ){
    pred_AddMu=getPredBG( true, false, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
  } else{
    pred_AddMu=getPredBG( true, false, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
    pred_NotTauHad=getPredBG( false, true, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
    pred_Lep=getPredBG( false, false, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n, MuonNumber, StartNJet, NJets );
  }


  TH2D* pred_AddMu_c1;
  TH2D* pred_NotTauHad_c1;
  TH2D* pred_Lep_c1;
  if(normalEstimation_ == true ){
    pred_AddMu_c1=factor.formatHist(pred_AddMu, 1., digit1_);
  } else {
    pred_AddMu_c1=factor.formatHist(pred_AddMu, 1., digit1_);
    pred_Lep_c1=factor.formatHist(pred_Lep, 1., digit1_);
    pred_NotTauHad_c1=factor.formatHist(pred_NotTauHad, 1., digit1_);
  }

  vector<TLine*> lines=factor.Lines();

  TCanvas *c1=new TCanvas();
  pred_AddMu_c1->Draw("colz");
  pred_AddMu_c1->Draw("sametext45");
  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  if( normalEstimation_ == true ){
    if( closureTests == "1To2Mu"){
      c1->SaveAs("pred_"+closureTests+".eps");
    } else if( closureTests == "iTojJet" ){
      c1->SaveAs( Form( "pred_"+closureTests+"_%s%d_%dTo%d_%d.eps", MuonNumber.Data(), iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 ) );
    } else {
      c1->SaveAs("pred_"+closureTests+MuonNumber+".eps");
    }
  } else {
    if( closureTests == "1To2Mu"){
      c1->SaveAs("pred_TauHad_"+closureTests+".eps");
    } else if( closureTests == "iTojJet" ){
      c1->SaveAs( Form( "pred_TauHad_"+closureTests+"_%s%d_%dTo%d_%d.eps", MuonNumber.Data(), iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 ) );
    } else {
      c1->SaveAs("pred_TauHad_"+closureTests+MuonNumber+".eps");
    }
  }
  c1->Update();
  c1->Clear();

  if(normalEstimation_ == false ){

    pred_Lep_c1->Draw("colz");
    pred_Lep_c1->Draw("sametext45");
    for( unsigned int il=0; il<lines.size(); il++){
      (lines[il])->Draw("same");
    }
    if( closureTests == "1To2Mu"){
      c1->SaveAs("pred_Lep_"+closureTests+".eps");
    } else if( closureTests == "iTojJet" ){
      c1->SaveAs(Form( "pred_Lep_"+closureTests+"_%s%d_%dTo%d_%d.eps", MuonNumber.Data(), iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 ) );
    } else {
      c1->SaveAs("pred_Lep_"+closureTests+MuonNumber+".eps");
    }
    c1->Update();
    c1->Clear();
    pred_NotTauHad_c1->Draw("colz");
    pred_NotTauHad_c1->Draw("sametext45");
    for( unsigned int il=0; il<lines.size(); il++){
      (lines[il])->Draw("same");
    }
    if( closureTests == "1To2Mu"){
      c1->SaveAs("pred_NotTauHad_"+closureTests+".eps");
    } else if( closureTests == "iTojJet" ){
      c1->SaveAs(Form( "pred_NotTauHad_"+closureTests+"_%s%d_%dTo%d_%d.eps", MuonNumber.Data(), iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 ) );
    } else {
      c1->SaveAs("pred_NotTauHad_"+closureTests+MuonNumber+".eps");
    }
    c1->Update();
    c1->Clear();

    TH2D* totalpre=(TH2D*)(pred_AddMu_c1->Clone("totalpre"));
    totalpre->Add(totalpre, pred_NotTauHad_c1);
    totalpre->Draw("colz");
    totalpre->Draw("sametext45");
    for( unsigned int il=0; il<lines.size(); il++){
      (lines[il])->Draw("same");
    }
    if( closureTests == "1To2Mu"){
      c1->SaveAs("pred_total_"+closureTests+".eps");
    } else if( closureTests == "iTojJet" ){
      c1->SaveAs(Form( "pred_total_"+closureTests+"_%s%d_%dTo%d_%d.eps", MuonNumber.Data(), iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 ) );
    } else {
      c1->SaveAs("pred_total_"+closureTests+MuonNumber+".eps");
    }
    c1->Update();
    c1->Clear();
  }
}

