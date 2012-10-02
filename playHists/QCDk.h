#ifndef QCDk_h
#define QCDk_h

#include "TH1D.h"
#include "TString.h"
#include "menus.h"
#include "vectors.h"
#include <vector>

using namespace std;

class QCDk : public menus, public vectors{
 public:
  QCDk();
  ~QCDk(){;}
  TH1D* getTailBulk( TString label, TString hname, int startNJet, int nJets, double lowy, double highy );
  void getBulkYield( int startNJet, int nJets, double higAT );
  TH1D* getRATvsHT( TString label, int startNJet, int nJets, double lowy, double highy, double lowybulk );
  void fitRATvsHT( TString region, int startNJet, int nJets, TString output, double higAT );
  void getResults( TString output, int startNJet, int nJetsm, double higAT );

};// QCDk

#endif
