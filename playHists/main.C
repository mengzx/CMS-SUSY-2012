#include "playHist2D.h"
#include "playHist1D.h"
#include "getTranslationFactor.h"
#include "basicPlots.h"
#include "project2DHists.h"
#include "TrueWPt.h"
#include "printTables.h"
#include "QCDk.h"
#include "BGCompositions.h"
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

int main( int argc, char* argv[] )
{
  std::string word = argv[1];
  if( word == "BGCompositions" ){
    BGCompositions *bg=new BGCompositions();
    bg->printout( "MuonSingleMuTrig", -1 );
    bg->printout( "MuonSingleMuTrig", 0 );
    bg->printout( "MuonSingleMuTrig", 1 );
    bg->printout( "MuonSingleMuTrig", 2 );
    bg->printout( "HadSele", -1 );
    bg->printout( "HadSele", 0 );
    bg->printout( "HadSele", 1 );
    bg->printout( "HadSele", 2 );
  }

  if( word == "QCDk" ){
    QCDk *qcdk=new QCDk();
    qcdk->getResults("");
    qcdk->getResults("_LowAT0.5");
  }

  if( word == "TrueWPt" ){
    TrueWPt *WPt=new TrueWPt();
    WPt->getResults();
  }

  if( word == "printTables" ){
    printTables *table=new printTables();
    table->Tables_ForNormal( "", 0, 0, 0, 0, "OneMuon_", 0, 1);
    table->Tables_ForNormal( "iTojJet", 1, 1, 2,1, "OneMuon_", 0, 1);
    table->Tables_ForNormal( "iTojJet", 2, 1, 3, 1, "OneMuon_", 0, 1);
    table->Tables_ForNormal( "iTojJet", 3, 1, 3, 13, "OneMuon_", 0, 1);

    table->Tables_ForNormal( "", 0, 0, 0, 0, "DiMuon_", 0, 1);
    table->Tables_ForNormal( "iTojJet", 1, 1, 2,1, "DiMuon_", 0, 1);
    table->Tables_ForNormal( "iTojJet", 2, 1, 3, 1, "DiMuon_", 0, 1);
    table->Tables_ForNormal( "iTojJet", 3, 1, 3, 13, "DiMuon_", 0, 1);


    table->Tables_ForNormal( "1To2Mu", 0, 0, 0, 0, "", 0, 1 );
  //  table->CompareYouAndMe();
  }

  if( word == "getTranslationFactor" ){
    getTranslationFactor *fa=new getTranslationFactor();
    fa->getResults( "", 0, 0, 0, 0, "OneMuon_", 0, 1 );
    fa->getResults( "1To2Mu", 0, 0, 0, 0, "OneMuon_", 0, 1);
    fa->getResults( "iTojJet", 1, 1, 2, 15, "OneMuon_", 0, 1 );
  }

  if( word == "basicPlots" || word == "basicPlots_OneMuon" || word == "basicPlots_DiMuon" || word == "basicPlots_Had" ){
    int startNJet[9]={0, 1, 2, 2, 3, 4, 4, 5 , 5};
    int nJet[9]     ={0, 1, 14, 1, 1, 12, 1, 1, 12 };
    
    int start = 0;
    int end = 9;

    if( word == "basicPlots" || word == "basicPlots_OneMuon"){
      for( int i=start; i< end; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("all", "OneMu", startNJet[i], nJet[i], "OneMuon_" );
	delete bp;
      }


      for( int i=start; i< end; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("lowHTBins", "OneMu", startNJet[i], nJet[i], "OneMuon_" );
	delete bp;
      }


      for( int i=start; i< end; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("highHTBins", "OneMu", startNJet[i], nJet[i], "OneMuon_" );
	delete bp;
      }
    }

    if( word == "basicPlots" || word == "basicPlots_DiMuon" ){
      for( int i=start; i< end; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("all", "OneMu", startNJet[i], nJet[i], "DiMuon_" );
	delete bp;
      }


      for( int i=start; i< end; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("lowHTBins", "OneMu", startNJet[i], nJet[i], "DiMuon_" );
	delete bp;
      }


      for( int i=start; i< end; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("highHTBins", "OneMu", startNJet[i], nJet[i], "DiMuon_" );
	delete bp;
      }
    }



    if( word == "basicPlots" || word == "basicPlots_Had" ){
      for( int i=start; i< end; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("all", "HadSele", startNJet[i], nJet[i], "" );
	delete bp;
      }


      for( int i=0; i< 9; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("lowHTBins", "HadSele", startNJet[i], nJet[i], "" );
	delete bp;
      }



      for( int i=0; i< 9; i++){
	basicPlots *bp=new basicPlots();
	bp->getResults("highHTBins", "HadSele", startNJet[i], nJet[i], "" );
	delete bp;
      }
    }
  }
  return 0;
}

