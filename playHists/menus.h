#ifndef menus_h
#define menus_h

#include "TString.h"
#include "TLegend.h"

class menus{

 public:
  menus();
  ~menus(){;}

  TString testHTBin_;
  TString testMCFile_;
  TString testDataFile_;
  bool notCutAlphaT_;
  int startNJet_;
  int nJets_;
  bool normalEstimation_;
  bool drawStack_;
  TString  epspng_;

  bool hasData_;
  bool hasMCtotal_;
  bool hasWJ_;
  bool hasDY_;
  bool hasTT_;
  bool hasSingleT_;
  bool hasZinv_;
  bool hasDiBoson_;
  bool hasZinvFromDY_;
  bool hasWJveryHighHT_;
  TString inidir_;
  TString subdir_;
  TString folderlabel_;
  TString HadTaudataset_;
  TString NotHadTaudataset_;
  TString signalDataset_;
  TString signalTrig_;
  TString HadTaucontrolTrig_;
  TString NotHadTaucontrolTrig_;
  TString NormalcontrolTrig_;
  TString controlDataset_;
  TString MCsample_;
  bool plotTrueTauHad_;
  TString MuonNumber_;

  double datascale_;
  bool useCommentJson_;
  double mcscale_;
  double mcscale_HT_;
  double mcscale_SingleMu_;
  double mcscale_DiMu_;

  TString digit1_;
  TString digit2_;
}; //end of menus
#endif
