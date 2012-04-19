#include "menus.h"
#include "TString.h"
#include "iostream.h"


menus::menus(){
  testHTBin_="";
  testMCFile_="";
  testDataFile_="";
  normalEstimation_=true;
  startNJet_=0;
  nJets_=15;
  notCutAlphaT_=true;

  inidir_="/Users/phxzm/Work_CMS/SUSY/myppt/PhysicWeekApr2012_FirstLookAt8TeVData_AimToICHEP_17042012/";
  subdir_="/allBJets";
  folderlabel_="";
  HadTaudataset_="SingleMu2012A";
  NotHadTaudataset_="HT2012A";
  signalTrig_="";
  signalDataset_ = "HT2012A";
  HadTaucontrolTrig_="SingleMuTrig";
  NotHadTaucontrolTrig_="HTATTrig";
  NormalcontrolTrig_="SingleMuTrig";
  controlDataset_ = "SingleMu2012A";
  datascale_=1.;
  mcscale_=1.633;
  MCsample_="";
  plotTrueTauHad_=false;


  digit1_=".1f";
  digit2_=".2f";

}

