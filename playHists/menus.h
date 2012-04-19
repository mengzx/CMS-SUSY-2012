#ifndef menus_h
#define menus_h

#include "TString.h"

class menus{

 public:
  menus();
  ~menus(){;}

  TString testHTBin_;
  TString testMCFile_;
  TString testDataFile_;
  bool normalEstimation_;
  bool notCutAlphaT_;

  int startNJet_;
  int nJets_;
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

  double datascale_;
  double mcscale_;

  TString digit1_;
  TString digit2_;

}; //end of menus
#endif
