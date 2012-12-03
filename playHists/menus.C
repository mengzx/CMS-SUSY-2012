#include "menus.h"
#include "TString.h"
#include "iostream.h"
#include "TLegend.h"
//#include "vectors.h"
#include <stdio.h>
#include <stdlib.h>

menus::menus(){

  debug_=-1;
  testHTBin_="";
  testMCFile_="";
  testDataFile_="";
  normalEstimation_=true;
//0-0, 1-1, 2-14, 2-1, 3-1, 4-12
  startNJet_=1;
  nJets_=1;
  notCutAlphaT_=true;
  drawStack_=false;
  epspng_="png";
  doTrigCorr_=true;
  drawOverflow_=true;
  useBTag_=true;
  doCumulative_=false;
  mcPUS_="PUS7";
  getFitParak_=2;
  useVariantRatioPlot_=false;
  ratioPlotErr_=0.1;
  QCDkUsePosionErr_=true;
  plotRatio_=false;

  bool useLO=true; 
  hasData_=false;
  hasMCtotal_=true;
  hasWJ_=true;
  hasDY_=true;
  hasTT_=true;
  hasSingleT_=true;
  hasZinv_=true;
  hasDiBoson_=true;
  hasTTZ_=true;
  useLOXSWJ_=useLO;
  useLOXSDY_=useLO;
  useLOXSTT_=useLO;
  useLOXSZinv_=useLO;

  hasGJ_=false;
  useLOXSGJ_=useLO;

  if( hasGJ_ ){
    hasWJ_=false;
    hasDY_=false;
    hasTT_=false;
    hasSingleT_=false;
    hasZinv_=false;
    hasDiBoson_=false;
    hasTTZ_=false;
  }

  hasT2cc160_=true;
  hasT2cc300_=true;
  hasT2cc220_145_=true;
  hasT2cc220_170_=true;
  hasT2cc220_195_=true;

  TString period="";
  //  inidir_="/Users/phxzm/Work_CMS/SUSY/ForICHEP2012/myppt/TenthLookAt8TeVData_AimToICHEP_ForAproval27062012_25062012/";
  inidir_="/Users/phxzm/Work_CMS/SUSY/myppt/EightTeV2012/SeventeenthLook_25_Sep2012/";
  subdir_="/allBJets_PUReWNoTopLimi_Has2To3Jets_BScaleCorr";
  //  subdir_="/allBJets_PUReWNoTopLimi_Has2To3Jets";
  // subdir_="/allBJets_QCDk";
  folderlabel_="TwoJet_";
  //  HadTaudataset_="SingleMu2012";
  NotHadTaudataset_="HT2012"+period;
  signalTrig_="";
  signalDataset_ = "HT2012"+period;
  HadTaucontrolTrig_="SingleMuTrig";
  NotHadTaucontrolTrig_="HTATTrig";
  NormalcontrolTrig_="SingleMuTrig";
  controlDataset_ = "SingleMu2012"+period;
  QCDDataSet_="JetHT2012"+period;
  photonControlTrig_="Photon";
  photonControlDataSet_="Photon2012"+period;
  MCsample_="";
  plotTrueTauHad_=false;
  MuonNumber_ = "OneMuon_";

  datascale_=1.;

  if( doCumulative_ ){
    useCommonJson_=true;
  } else {
    useCommonJson_=false;
  }

  if( useCommonJson_ ){
    mcscale_=1.;
  }

  if( period == "AB"){
    //period AB. Sep 24
    mcscale_HT_=  51.26247;
    mcscale_SingleMu_= 50.00191;
    mcscale_DiMu_= 50.00191;
    mcscale_Photon_=50.00191;
  } else if( period == ""){
    //period ABC. Sep 24
    mcscale_HT_=  116.59247;
    mcscale_SingleMu_= 113.89191;
    mcscale_DiMu_= 113.89191;
    mcscale_Photon_=115.70;
    }

  digit1_=".1f";
  digit2_=".2f";

}

