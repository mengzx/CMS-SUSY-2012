#include "menus.h"
#include "TString.h"
#include "iostream.h"
#include "TLegend.h"

menus::menus(){
  testHTBin_="";
  testMCFile_="";
  testDataFile_="";
  normalEstimation_=true;
  startNJet_=0;
  nJets_=0;
  notCutAlphaT_=true;

  len_=new TLegend( 0.75, 0.75, 0.995, 0.995 );
  inidir_="/Users/phxzm/Work_CMS/SUSY/ForICHEP2012/myppt/RA1_forHPA03052012_02052012/";
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
  MCsample_="";
  plotTrueTauHad_=false;
  MuonNumber_ = "OneMuon_";

  datascale_=1.;
  mcscale_=3.63715;

  digit1_=".1f";
  digit2_=".2f";

}

