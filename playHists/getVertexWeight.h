#ifndef getVertexWeight_h
#define getVertexWeight_h

#include "TH1D.h"
#include "TString.h"
#include "menus.h"
#include "vectors.h"
#include <vector>

using namespace std;

class getVertexWeight : public menus, public vectors{
 public:
  getVertexWeight();
  ~getVertexWeight(){}
  TH1D *addHists(TString label);
  TH1D *getWeight();

}; //class getVertexWeight

#endif
