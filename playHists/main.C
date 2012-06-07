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

      int startNJet[6]={0, 1, 2, 2, 3, 4 };
      int nJet[6]     ={0, 1, 14, 1, 1, 12 };
  //  int startNJet[5]={1, 2, 0, 3, 2};
  //  int nJet[5]     ={1, 14, 0, 1, 1};
      //  int startNJet[1]={0};
      ///  int nJet[1]     ={0};

	     /*
             for( int i=0; i< 5; i++){
            basicPlots *bp=new basicPlots();
           bp->getResults("all", "OneMu", startNJet[i], nJet[i] );
            delete bp;
          }

	     for( int i=0; i< 5; i++){
       basicPlots *bp=new basicPlots();
     bp->getResults("lowHTBins", "OneMu", startNJet[i], nJet[i] );
       delete bp;
       }


      for( int i=0; i< 5; i++){
       basicPlots *bp=new basicPlots();
       bp->getResults("highHTBins", "OneMu", startNJet[i], nJet[i] );
       delete bp;
       }
	     */
       for( int i=0; i< 6; i++){
       basicPlots *bp=new basicPlots();
       bp->getResults("all", "HadSele", startNJet[i], nJet[i] );
       delete bp;
     }

                 for( int i=0; i< 5; i++){
       basicPlots *bp=new basicPlots();
       bp->getResults("lowHTBins", "HadSele", startNJet[i], nJet[i] );
       delete bp;
       }
     for( int i=0; i< 5; i++){
       basicPlots *bp=new basicPlots();
       bp->getResults("highHTBins", "HadSele", startNJet[i], nJet[i] );
       delete bp;
       }





  return 0;
}

