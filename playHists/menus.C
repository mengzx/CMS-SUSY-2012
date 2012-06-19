#include "menus.h"
#include "TString.h"
#include "iostream.h"
#include "TLegend.h"
#include "vectors.h"

menus::menus(){
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

  hasData_=true;
  hasMCtotal_=true;
  hasWJ_=true;
  hasDY_=true;
  hasTT_=true;
  hasSingleT_=true;
  hasZinv_=true;
  hasDiBoson_=true;

  hasZinvFromDY_=false;
  hasWJveryHighHT_=false;
  hasZinv_HT50To100_=false;
  hasZinv_FastSim_HT100To200_=false;
  hasZinv_FastSim_HT200To400_=false;
  hasZinv_HT400Toinf_=false;
  hasWJ_inclusive_=false;
  hasWJ_FastSim_HT250To300_=false;
  hasWJ_FastSim_HT300To400_=false;
  hasWJ_HT400Toinf_=false;

  inidir_="/Users/phxzm/Work_CMS/SUSY/ForICHEP2012/myppt/NinthLookAt8TeVData_AimToICHEP_ForAproval27062012_18062012/";
  subdir_="/allBJets";
  folderlabel_="";
  HadTaudataset_="SingleMu2012";
  NotHadTaudataset_="HT2012";
  signalTrig_="";
  signalDataset_ = "HT2012";
  HadTaucontrolTrig_="SingleMuTrig";
  NotHadTaucontrolTrig_="HTATTrig";
  NormalcontrolTrig_="SingleMuTrig";
  controlDataset_ = "SingleMu2012";
  MCsample_="";
  plotTrueTauHad_=false;
  MuonNumber_ = "DiMuon_";

  datascale_=1.;
  //  mcscale_=5.56788; //6th look
  //  mcscale_=8.09551; // 7th look
  useCommentJson_=false;
  mcscale_=1.;
  mcscale_HT_=38.71;
  mcscale_SingleMu_=36.6607;
  mcscale_DiMu_=36.6607;

  digit1_=".1f";
  digit2_=".2f";
}

