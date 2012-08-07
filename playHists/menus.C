#include "menus.h"
#include "TString.h"
#include "iostream.h"
#include "TLegend.h"
#include "vectors.h"
#include <stdio.h>
#include <stdlib.h>

menus::menus(){

  debug_=0;
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
  drawOverflow_=false;

  hasData_=true;
  hasMCtotal_=false;
  hasWJ_=false;
  hasDY_=false;
  hasTT_=false;
  hasSingleT_=false;
  hasZinv_=false;
  hasDiBoson_=false;
  hasTTZ_=false;

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
  hasT2tt_smallScan_350_100_=false;
  hasT2tt_smallScan_200_0_=false;
  hasT2bw_smallScan_05_200_0_=false;
  hasT2bw_smallScan_075_150_30_=false;
  hasT2bw_smallScan_075_120_0_=false;

  hasT2tt_smallScan_350_50_=false;
  hasT2bw_smallScan_05_350_50_=false;
  hasT2bw_smallScan_075_350_50_=false;
  hasT2tt_smallScan_500_50_=false;

  //  inidir_="/Users/phxzm/Work_CMS/SUSY/ForICHEP2012/myppt/TenthLookAt8TeVData_AimToICHEP_ForAproval27062012_25062012/";
  inidir_="/Users/phxzm/Work_CMS/SUSY/myppt/EightTeV2012/ThirteenthLook_07Aug2012/";
  subdir_="/allBJets_HadSeleMuIso012";
  folderlabel_="";
  //  HadTaudataset_="SingleMu2012";
  NotHadTaudataset_="HT2012";
  signalTrig_="";
  signalDataset_ = "HT2012";
  HadTaucontrolTrig_="SingleMuTrig";
  NotHadTaucontrolTrig_="HTATTrig";
  NormalcontrolTrig_="SingleMuTrig";
  controlDataset_ = "SingleMu2012";
  MCsample_="";
  plotTrueTauHad_=false;
  MuonNumber_ = "OneMuon_";

  datascale_=1.;
  useCommonJson_=false;
  mcscale_=1.;
  mcscale_HT_=  70.20;
  mcscale_SingleMu_= 70.23553;
  mcscale_DiMu_=70.23553;

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

