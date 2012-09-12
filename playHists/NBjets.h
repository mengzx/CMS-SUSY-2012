#ifndef NBjets_h
#define NBjets_h

#include "menus.h"
#include "vectors.h"
#include "TH1D.h"
#include "TString.h"
#include "TFile.h"

class NBjets : public menus, public vectors{
 public:
  NBjets();
  ~NBjets(){;}

  double Ebsion();
  double Aem();
  double N_bs();
  double N_bmatch();
  double N_nonbmatch();

};//NBjets

#endif
