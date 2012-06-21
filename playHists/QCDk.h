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
  TH1D* getTailBulk( TString label, TString hname, TString bslices, double lowy, double highy );
  TH1D* getRATvsHT( TString label, TString bslices, double lowy, double highy );
  void getBulkYield( TString bslices );
  void fitRATvsHT( TString region, TString bslices );
  void getResults();

};// QCDk

#endif
