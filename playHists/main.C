#include "playHist2D.h"
#include "playHist1D.h"
#include "getTranslationFactor.h"
#include "basicPlots.h"
#include "project2DHists.h"
#include "TrueWPt.h"
#include "printTables.h"
#include "QCDk.h"
//#include "NBjets.h"
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
#include "menus.h"

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
    int n=15;
    int startNJet[3]={0, 2, 4 };
    int nJet[3]     ={0, 2, n-4+1 };
    int start = 0;
    int end = 3;

    for( int i=start; i< end; i++ ){
      qcdk->getResults("", startNJet[i], nJet[i], 0.50);
      qcdk->getResults("_LowAT0.5", startNJet[i], nJet[i], 0.50);
    }

  }

  if( word == "TrueWPt" ){
    TrueWPt *WPt=new TrueWPt();
    WPt->getResults();
  }

  /*  if( word == "NBjets" ){
    NBjets *nb=new NBjets();
    nb->getResults();
    }*/

  if( word == "printTables" ){
    printTables *table=new printTables();
    /*    table->Tables_ForNormal( "", 0, 0, 0, 0, "OneMuon_", 0, 0);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "OneMuon_", 1, 1);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "OneMuon_", 2, 1);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "OneMuon_", 3, 1);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "OneMuon_", 4, 1);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "OneMuon_", 5, 1);*/

    table->Tables_ForNormal( "", 0, 0, 0, 0, "DiMuon_", 0, 0);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "DiMuon_", 1, 1);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "DiMuon_", 2, 1);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "DiMuon_", 3, 1);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "DiMuon_", 4, 1);
    table->Tables_ForNormal( "", 0, 0, 0, 0, "DiMuon_", 5, 1);

    /*    table->Tables_ForNormal( "iTojJet", 1, 1, 2,1, "OneMuon_", 0, 0);
    table->Tables_ForNormal( "iTojJet", 2, 1, 3, 1, "OneMuon_", 0, 0);
    table->Tables_ForNormal( "iTojJet", 3, 1, 3, 13, "OneMuon_", 0, 0);

    table->Tables_ForNormal( "", 0, 0, 0, 0, "DiMuon_", 0, 0);
    table->Tables_ForNormal( "iTojJet", 1, 1, 2,1, "DiMuon_", 0, 0);
    table->Tables_ForNormal( "iTojJet", 2, 1, 3, 1, "DiMuon_", 0, 0);
    table->Tables_ForNormal( "iTojJet", 3, 1, 3, 13, "DiMuon_", 0, 0);*/


    //    table->Tables_ForNormal( "1To2Mu", 0, 0, 0, 0, "", 0, 0 );
  //  table->CompareYouAndMe();
  }

  if( word == "getTranslationFactor" ){
    getTranslationFactor *fa=new getTranslationFactor();
    fa->getResults( "", 0, 0, 0, 0, "OneMuon_", 0, 1 );
    fa->getResults( "1To2Mu", 0, 0, 0, 0, "OneMuon_", 0, 1);
    fa->getResults( "iTojJet", 1, 1, 2, 15, "OneMuon_", 0, 1 );
  }

  if( word == "basicPlots" || word == "basicPlots_OneMuon" || word == "basicPlots_DiMuon" || word == "basicPlots_Had" ){

    vector<TString> folder;
    folder.push_back("");
    folder.push_back("TwoJet_");
    folder.push_back("ThreeJet_");
    folder.push_back("FourJet_");
    folder.push_back("MoreThreeJet_");
    folder.push_back("MoreFourJet_");
    vector<TString> HTBins;
    HTBins.push_back("all");
    HTBins.push_back("lowHTBins");
    HTBins.push_back("highHTBins");
    vector<int> folder_n;
    folder_n.push_back(10);
    folder_n.push_back(2);
    folder_n.push_back(3);
    folder_n.push_back(4);
    folder_n.push_back(10);
    folder_n.push_back(10);

    int n=15;
    int startNJet[16]={2, 3, 2, 4, 4, 5, 6, 0, 1, 2, 3, 4, 5, 5, 2, 4};
    int nJet[16]     ={1, 1, 2, n-4+2, 1, 1, 1, 0, 1, 1, 1, 1, 1, n-5+2, n-2+2, n-4+2 };
    int start = 7;
    int end = 16;

    menus *listmenus=new menus();
    if( !(listmenus->useBTag_) ){
      start = 0;
      end = 8;
    }

    if( word == "basicPlots" || word == "basicPlots_OneMuon"){
      for( int i=start; i< end; i++){
	for( unsigned int ibin=0; ibin<HTBins.size();ibin++){
	  for( unsigned int il=0; il<folder.size(); il++){ 
	    cout<<  startNJet[i] - 1 << " *****  " << folder_n[il] <<endl;
	    if( ( startNJet[i] - 1 ) > folder_n[il] ) continue;
	    basicPlots *bp=new basicPlots();
	    bp->getResults(HTBins[ibin], "OneMu", startNJet[i], nJet[i], "OneMuon_", folder[il] );
	    delete bp;
	  }
	}
      }
    }

    if( word == "basicPlots" || word == "basicPlots_DiMuon" ){
      for( int i=start; i< end; i++){
	for( unsigned int ibin=0; ibin<HTBins.size();ibin++){
	  for( unsigned int il=0; il<folder.size(); il++){ 
	    basicPlots *bp=new basicPlots();
	    bp->getResults(HTBins[ibin], "OneMu", startNJet[i], nJet[i], "DiMuon_", folder[il] );
	    delete bp;
	  }
	}
      }

    }



    if( word == "basicPlots" || word == "basicPlots_Had" ){
      for( int i=start; i< end; i++){
	for( unsigned int ibin=0; ibin<HTBins.size();ibin++){
	  for( unsigned int il=0; il<folder.size(); il++){ 
	    basicPlots *bp=new basicPlots();
	    bp->getResults(HTBins[ibin], "HadSele", startNJet[i], nJet[i], "", folder[il] );
	    delete bp;
	  }
	}
      }

    }
  }
  return 0;
}

