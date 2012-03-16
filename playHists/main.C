#include "playHist2D.h"
#include "playHist1D.h"
#include "getTranslationFactor.h"
#include "basicPlots.h"
#include "project2DHists.h"
#include "TrueWPt.h"
#include "printTables.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <TChain.h>

using namespace std;

int main()
{

  //  TrueWPt *WPt=new TrueWPt();
  //  WPt->getResults();
    printTables *table=new printTables();
    table->Tables();
  //  basicPlots *bp=new basicPlots();
  //  bp->AlphaT();
  return 0;
}

