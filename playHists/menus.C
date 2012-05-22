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

  inidir_="/Users/phxzm/Work_CMS/SUSY/ForICHEP2012/myppt/SeventhLookAt8TeVData_AimToICHEP_ForSUSY22052012_19052012/";
  subdir_="/allBJets_BAMHToverMET";
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
  mcscale_=8.09551;

  digit1_=".1f";
  digit2_=".2f";

}

