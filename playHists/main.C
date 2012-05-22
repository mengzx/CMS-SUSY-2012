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
#include <TString.h>

using namespace std;

int main()
{

  //  TrueWPt *WPt=new TrueWPt();
  //  WPt->getResults();

  //  printTables *table=new printTables();
  //  table->Tables_ForNormal("", 0, 0, 0, 0);
  //  table->Tables_ForNormal("iTojJet", 1, 1, 2, 14);
  //  table->Tables_ForNormal("iTojJet", 2, 1, 3, 13);
  //  table->Tables_ForNormal("1To2Mu", 0, 0, 0, 0 );
  //  table->CompareYouAndMe();

  //  table->Tables();
  //  table->Hists();
  //  getTranslationFactor *fa=new getTranslationFactor();
  //  fa->getResults( "", 0, 0, 0, 0 );
  //  fa->getResults( "1To2Mu", 0, 0, 0, 0 );
  //  fa->getResults( "iTojJet", 1, 1, 2, 15 );

     basicPlots *bp=new basicPlots();
     bp->getResults("all", "OneMu");
     bp->getResults("lowHTBins", "OneMu");
     bp->getResults("highHTBins", "OneMu");
     bp->getResults("all", "HadSele");
     bp->getResults("lowHTBins", "HadSele");
     bp->getResults("highHTBins", "HadSele");
  return 0;
}

