#include "menus.h"
#include "TString.h"
#include "iostream.h"
#include "TLegend.h"

menus::menus(){
  testHTBin_="";
  testMCFile_="";
  testDataFile_="";
  normalEstimation_=true;
//0-0, 1-1, 2-14, 2-1, 3-1, 4-12
  startNJet_=0;
  nJets_=0;
  notCutAlphaT_=true;
  drawStack_=true;
  epspng_="png";

  hasDY_=true;
  hasTT_=true;
  hasWJ_=true;
  hasSingleT_=true;
  hasZinv_=false;
  hasDiBoson_=false;

  inidir_="/Users/phxzm/Work_CMS/SUSY/ForICHEP2012/myppt/EighthLookAt8TeVData_AimToICHEP_ForDocumentAproval01062012_27052012/";
  subdir_="/allBJets_NoECALnoiseNoMHToverMETNoZmass_MC7TeVData8TeV";
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
  MuonNumber_ = "OneMuon_";

  datascale_=1.;
  //  mcscale_=5.56788; //6th look
  //  mcscale_=8.09551; // 7th look
  mcscale_=15.33;

  digit1_=".1f";
  digit2_=".2f";

}

