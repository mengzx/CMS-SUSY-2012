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

  hasData_=true;
  hasMCtotal_=true;
  hasWJ_=true;
  hasDY_=true;
  hasTT_=true;
  hasSingleT_=true;
  hasZinv_=false;
  hasDiBoson_=false;
  hasZinvFromDY_=true;
  hasWJveryHighHT_=true;

  inidir_="/Users/phxzm/Work_CMS/SUSY/ForICHEP2012/myppt/EighthLookAt8TeVData_AimToICHEP_ForDocumentAproval01062012_27052012/";
  subdir_="/allBJets_MC8TeVData8TeV_WithRecoVertexWeight_CaloMETNoEtraAddofMuElPho";
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
  mcscale_=15.33;
  mcscale_HT_=15.66;
  mcscale_SingleMu_=15.61;
  mcscale_DiMu_=15.61;

  digit1_=".1f";
  digit2_=".2f";
}

