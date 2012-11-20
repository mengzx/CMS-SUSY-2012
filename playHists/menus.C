#include "menus.h"
#include "TString.h"
#include "iostream.h"
#include "TLegend.h"
#include "vectors.h"
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
  drawStack_=true;
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
  doPhoton_=false;
  includeSignal_=true;

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

  hasTT_Massive_=false;
  useLOXSTT_Massive_=useLO;
  hasWJ_XSLO_=false;
  hasZinvFromDY_=false;
  hasWJveryHighHT_=false;
  hasZinv_HT50To100_=false;
  hasZinv_FastSim_HT100To200_=false;
  hasZinv_FastSim_HT200To400_=false;
  hasZinv_HT400Toinf_=false;
  hasWJ_inclusive_=false;
  hasWJ_FastSim_HT250To300_=false;
  hasWJ_FastSim_HT300To400_=false;
  hasWJ_HT250To300_=false;
  hasWJ_HT300To400_=false;
  hasWJ_HT400Toinf_=false;
  hasTTZ525_=false;
  hasTTZ532_=false;
  hasT2tt_smallScan_200_0_=false;
  hasT2bw_smallScan_05_200_0_=false;
  hasT2bw_smallScan_075_150_30_=false;
  hasT2bw_smallScan_075_120_0_=false;

  hasT2bw_smallScan_025_500_100_=false;
  hasT2tt_smallScan_500_50_=false;
  hasT2tt_smallScan_500_200_=false;
  hasT2tt_smallScan_500_100_=false;

  hasT2tt_smallScan_350_100_=false;
  hasT2tt_smallScan_350_50_=false;
  hasT2bw_smallScan_05_350_50_=false;
  hasT2bw_smallScan_075_350_50_=false;

  hasT1tttt_ = false;
  hasT2cc160_=false;
  hasT2cc300_=true;

  TString period="";
  //  inidir_="/Users/phxzm/Work_CMS/SUSY/ForICHEP2012/myppt/TenthLookAt8TeVData_AimToICHEP_ForAproval27062012_25062012/";
  inidir_="/Users/phxzm/Work_CMS/SUSY/myppt/EightTeV2012/SeventeenthLook_25_Sep2012/";
  subdir_="/allBJets_PUReWNoTopLimi_Has2To3Jets_BScaleCorr";
  //  subdir_="/allBJets_PUReWNoTopLimi_Has2To3Jets";
  // subdir_="/allBJets_QCDk";
  folderlabel_="TwoThreeJet_";
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
    mcscale_=1.;
    mcscale_HT_=  1.;
    mcscale_SingleMu_= 1.;
    mcscale_DiMu_= 1.;
  } else {
    useCommonJson_=false;
    mcscale_=1.;
    //period AB. Sep 24
    if( period == "AB"){
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
  }

  //Aug 24
  /*  mcscale_HT_=  84.74;
  mcscale_SingleMu_= 84.73;
  mcscale_DiMu_= 84.73;*/


  /*  mcscale_HT_=  80.15;
  mcscale_SingleMu_= 79.57;
  mcscale_DiMu_= 79.57;*/

  /*  mcscale_HT_=  70.20;
  mcscale_SingleMu_= 70.23553;
  mcscale_DiMu_=70.23553;
  */
  /*  mcscale_HT_= 56.92799; ABC
  mcscale_SingleMu_= 61.42799;
  mcscale_DiMu_=61.42799;
  */

  /*  mcscale_HT_=49.76; AB
  mcscale_SingleMu_=49.54071;
  mcscale_DiMu_=49.54071;*/

  digit1_=".1f";
  digit2_=".2f";

}

