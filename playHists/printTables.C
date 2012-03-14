#include "printTables.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TH2D.h"
#include "TLine.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "TCanvas.h"
#include <stdio.h>

#include "TStyle.h"
#include "playHist2D.h"

using namespace std;

printTables::printTables(){}


vector<vector<double> > printTables::readHist( TH2D* factorh){
  vector<vector<double> > factorre;
  int nxbins=factorh->GetXaxis()->GetNbins();
  int nybins=factorh->GetYaxis()->GetNbins();

  for( int iy=nybins; iy >= 1; iy--){
    double ybinlow=factorh->GetYaxis()->GetBinLowEdge(iy);
    if((int)(ybinlow*10000.) == 5500 ){
      vector<double> factor;
      for( int ix=1; ix <= nxbins; ix++){
	double xbinlow=factorh->GetXaxis()->GetBinLowEdge(ix);
	if( (int)(xbinlow*10.) >= 2750){
	  factor.push_back(factorh->GetBinContent(ix, iy));
	}
      }
      factorre.push_back(factor);
    }
    if((int)(ybinlow*10000.) == 5300 ){
      vector<double> factor;
      for( int ix=1; ix <= nxbins; ix++){
	double xbinlow=factorh->GetXaxis()->GetBinLowEdge(ix);
	if( (int)(xbinlow*10.) >= 5750){
	  factor.push_back(factorh->GetBinContent(ix, iy));
	}
      }
      factorre.push_back(factor);
    }

    if((int)(ybinlow*10000.) == 5200 ){
      vector<double> factor;
      for( int ix=1; ix <= nxbins; ix++){
	double xbinlow=factorh->GetXaxis()->GetBinLowEdge(ix);
	if( (int)(xbinlow*10.) >= 5750 && (int)(xbinlow*10.) < 7750){
	  factor.push_back(-1.);
	}
	if( (int)(xbinlow*10.) >= 7750){
	  factor.push_back(factorh->GetBinContent(ix, iy));
	}
      }
      factorre.push_back(factor);
    }
  }
  return factorre;
}

vector<vector<TString> > printTables::readHist_WithErr( TH2D* factorh){

  vector<vector<TString> > factorre;
  int nxbins=factorh->GetXaxis()->GetNbins();
  int nybins=factorh->GetYaxis()->GetNbins();

  for( int iy=nybins; iy >= 1; iy--){
    double ybinlow=factorh->GetYaxis()->GetBinLowEdge(iy);
    if((int)(ybinlow*10000.) == 5500 ){
      vector<TString> factor;
      for( int ix=1; ix <= nxbins; ix++){
	double xbinlow=factorh->GetXaxis()->GetBinLowEdge(ix);
	if( (int)(xbinlow*10.) >= 2750){
	  double value=factorh->GetBinContent(ix, iy);
	  double error=factorh->GetBinError(ix, iy);
	  TString svalue=Form("%.1f", value);
	  TString serror=Form("%.1f", error);
	  factor.push_back(svalue+" $\\pm$ "+serror);
	}
      }
      factorre.push_back(factor);
    }

    if((int)(ybinlow*10000.) == 5300 ){
      vector<TString> factor;
      for( int ix=1; ix <= nxbins; ix++){
	double xbinlow=factorh->GetXaxis()->GetBinLowEdge(ix);
	if( (int)(xbinlow*10.) >= 5750){
	  double value=factorh->GetBinContent(ix, iy);
	  double error=factorh->GetBinError(ix, iy);
	  TString svalue=Form("%.1f", value);
	  TString serror=Form("%.1f", error);
	  factor.push_back(svalue+" $\\pm$ "+serror);
	}
      }
      factorre.push_back(factor);
    }

    if((int)(ybinlow*10000.) == 5200 ){
      vector<TString> factor;
      for( int ix=1; ix <= nxbins; ix++){
	double xbinlow=factorh->GetXaxis()->GetBinLowEdge(ix);
	if( (int)(xbinlow*10.) >= 5750 && (int)(xbinlow*10.) < 7750){
	  factor.push_back("--");
	}
	if( (int)(xbinlow*10.) >= 7750){
	  double value=factorh->GetBinContent(ix, iy);
	  double error=factorh->GetBinError(ix, iy);
	  TString svalue=Form("%.1f", value);
	  TString serror=Form("%.1f", error);
	  factor.push_back(svalue+" $\\pm$ "+serror);
	}
      }
      factorre.push_back(factor);
    }
  }
  return factorre;
}



vector<vector<double> > printTables::readFactorHist( bool MuAddOrNot, bool fullesti, TString HTBin, bool isData ){
  playHist2D factor=playHist2D();
  TH2D* factorh=factor.getFactor( MuAddOrNot, fullesti, HTBin, isData );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );

  return factorre;
}

vector<vector<double> > printTables::readControlDataHist( bool MuAddOrNot, bool fullesti, TString HTBin){
  playHist2D factor=playHist2D();
  TH2D* factorh=factor.getControlData( MuAddOrNot, fullesti, HTBin );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );
  return factorre;
}

vector<vector<double> > printTables::readYieldDataHist( bool MuAddOrNot, bool fullesti, TString HTBin){
  playHist2D factor=playHist2D();
  TH2D* factorh=factor.getYieldData( MuAddOrNot, fullesti, HTBin );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );
  return factorre;
}

vector<vector<double> > printTables::readPredBGHist( bool MuAddOrNot, bool fullesti, TString HTBin){
  playHist2D factor=playHist2D();
  TH2D* factorh=factor.getPredBG( MuAddOrNot, fullesti, HTBin );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );
  return factorre;
}



vector<vector<TString> > printTables::readFactorHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, bool isData ){
  playHist2D factor=playHist2D();
  TH2D* factorh=factor.getFactor( MuAddOrNot, fullesti, HTBin, isData );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh );

  return factorre;
}

vector<vector<TString> > printTables::readControlDataHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin){
  playHist2D factor=playHist2D();
  TH2D* factorh=factor.getControlData( MuAddOrNot, fullesti, HTBin );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh );
  return factorre;
}

vector<vector<TString> > printTables::readYieldDataHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin){
  playHist2D factor=playHist2D();
  TH2D* factorh=factor.getYieldData( MuAddOrNot, fullesti, HTBin );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh );
  return factorre;
}

vector<vector<TString> > printTables::readPredBGHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin){
  playHist2D factor=playHist2D();
  TH2D* factorh=factor.getPredBG( MuAddOrNot, fullesti, HTBin );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh );
  return factorre;
}


void printTables::printout_first( FILE *infile, vector<vector<double> > invector, vector<vector<TString> > invString, int irow, int digit, int colum_n, TString firstcol, bool withErr ){

  if( withErr == true){
    for(vector<TString>::size_type icol=0; icol<invString[irow].size(); icol++){
      if( icol + colum_n == colum_n){
	fprintf(infile, "%s", firstcol.Data());
      }
      if( icol < colum_n ){
	fprintf(infile, " & %s ",  (invString[irow][icol]).Data() );
	if( icol+1 == colum_n ){
	  fprintf( infile, "\\\\ \n");
	}
      } 
    }
  } else{
    for(vector<double>::size_type icol=0; icol<invector[irow].size(); icol++){
      if( icol + colum_n == colum_n){
	fprintf(infile, "%s", firstcol.Data());
      }
      if( icol < colum_n ){
	if( invector[irow][icol] == -1. ){
	  fprintf(infile, " & -- ");
	}else{
	  fprintf(infile, " & %.2f ",  invector[irow][icol] );
	}
	if( icol+1 == colum_n ){
	  fprintf( infile, "\\\\ \n");
	}
      }
    }
  }
}

void printTables::printout_second( FILE *infile, vector<vector<double> > invector, vector<vector<TString> > invString, int irow, int digit, int colum_f, int colum_n, TString firstcol, bool withErr ){

  if( withErr == true){
  for(vector<TString>::size_type icol=0; icol<invString[irow].size(); icol++){
    if( icol + colum_n == colum_f + colum_n){
      fprintf(infile, "%s", firstcol.Data());
    }
    if( icol >= colum_f ){
      //      fprintf(infile, (" & %.%df ",  invector[irow][icol] ), digit);
      fprintf(infile, " & %s ",  (invString[irow][icol]).Data() );
      if(icol+1 == colum_f + colum_n ){
	fprintf( infile, "\\\\ \n");
      }
    } 
  }
  } else{
  for(vector<double>::size_type icol=0; icol<invector[irow].size(); icol++){
    if( icol + colum_n == colum_f + colum_n){
      fprintf(infile, "%s", firstcol.Data());
    }
    if( icol >= colum_f ){
      if( invector[irow][icol] == -1. ){
	fprintf(infile, " & -- ");
      }else{
	fprintf(infile, " & %.2f ",  invector[irow][icol] );
      }
      if(icol+1 == colum_f + colum_n ){
	fprintf( infile, "\\\\ \n");
      }
    } 
  }
  }
}

void printTables::printout_final( FILE *infile, vector<vector<double> > invector, vector<vector<TString> > invString, int irow, int digit, int colum_f, int colum_n, TString firstcol, bool withErr ){

  if( withErr == true ){
  for(vector<TString>::size_type icol=0; icol<invString[irow].size(); icol++){
    if( icol + colum_n == invString[irow].size()){
      fprintf(infile, "%s", firstcol.Data());
    }
    if( icol >= colum_f ){
      fprintf(infile, " & %s ",  (invString[irow][icol]).Data() );
      if((icol + 1) == invString[irow].size() ){
	fprintf( infile, "\\\\ \n");
      }
    } 
  }
  } else {
  for(vector<double>::size_type icol=0; icol<invector[irow].size(); icol++){
    if( icol + colum_n == invector[irow].size()){
      fprintf(infile, "%s", firstcol.Data());
    }
    if( icol >= colum_f ){
      if( invector[irow][icol] == -1. ){
	fprintf(infile, " & -- ");
      }else{
	fprintf(infile, " & %.2f ",  invector[irow][icol] );
      }
      if((icol + 1) == invector[irow].size() ){
	fprintf( infile, "\\\\ \n");
      }
    } 
  }
  }
}

void printTables::Tables(){

  playHist2D factor=playHist2D();
  TH2D *predBG_HadTauh=factor.getPredBG( true, false, "all" );
  TH2D *predBG_NotHadTauh=factor.getPredBG( false, true, "all" );

  TH2D *predBG_totalh=(TH2D*)(predBG_HadTauh->Clone("predBG_totalh"));
  predBG_totalh->Add(predBG_totalh, predBG_NotHadTauh);
  vector<vector<double> > predBG_total=readHist( predBG_totalh );
  vector<vector<TString> > predBG_total_WithErr=readHist_WithErr( predBG_totalh );

  vector<vector<double> > factor_HadTau=readFactorHist( true, false, "all", false );
  vector<vector<double> > factor_NotHadTau=readFactorHist( false, true, "all", false );
  vector<vector<double> > controlData_HadTau=readControlDataHist( true, false, "all" );
  vector<vector<double> > controlData_NotHadTau=readControlDataHist( false, true, "all" );
  vector<vector<double> > predBG_HadTau=readPredBGHist( true, false, "all" );
  vector<vector<double> > predBG_NotHadTau=readPredBGHist( false, true, "all" );

  vector<vector<double> > factor_Lep=readFactorHist( false, false, "all", false );
  vector<vector<double> > controlData_Lep=readControlDataHist( false, false, "all" );
  vector<vector<double> > predBG_Lep=readPredBGHist( false, false, "all" );

  vector<vector<double> > yieldData=readYieldDataHist( false, true, "all" );


  vector<vector<TString> > factor_HadTau_WithErr=readFactorHist_WithErr( true, false, "all", false );
  vector<vector<TString> > factor_NotHadTau_WithErr=readFactorHist_WithErr( false, true, "all", false );
  vector<vector<TString> > controlData_HadTau_WithErr=readControlDataHist_WithErr( true, false, "all" );
  vector<vector<TString> > controlData_NotHadTau_WithErr=readControlDataHist_WithErr( false, true, "all" );
  vector<vector<TString> > predBG_HadTau_WithErr=readPredBGHist_WithErr( true, false, "all" );
  vector<vector<TString> > predBG_NotHadTau_WithErr=readPredBGHist_WithErr( false, true, "all" );

  vector<vector<TString> > factor_Lep_WithErr=readFactorHist_WithErr( false, false, "all", false );
  vector<vector<TString> > controlData_Lep_WithErr=readControlDataHist_WithErr( false, false, "all" );
  vector<vector<TString> > predBG_Lep_WithErr=readPredBGHist_WithErr( false, false, "all" );

  vector<vector<TString> > yieldData_WithErr=readYieldDataHist_WithErr( false, true, "all" );


  FILE * outputfile;
  outputfile = fopen ("test.tex","w");

  fprintf(outputfile, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputfile, "\\begin{document} \n");

  fprintf(outputfile, "\\begin{table}[htl] \n");

  fprintf(outputfile, "\\caption{Event type compositons of single muon selection in background MC samples}\n");
  //  fprintf(outputfile, "\\centering\n");
  //  fprintf(outputfile, "\\centering\n");
  fprintf(outputfile, " \\begin{flushleft}\n");
  fprintf(outputfile, " \\begin{tabular}{ c|cccc }\n");

  fprintf(outputfile, "\\hline\n");

  bool withErr=true;

  for(vector<vector<double> >::size_type iAT=0; iAT<factor_HadTau.size(); iAT++){

    if(iAT == 0){
      fprintf(outputfile, "$ \\alpha_T $ range   &  \\multicolumn{4}{c}{$\\alpha_T > $ 0.55}\\\\ \n ");
      fprintf(outputfile, " HT (GeV) & 275--325 & 325--375 & 375--475 & 475--575 \\\\ \n ");
      printout_first( outputfile, factor_HadTau, factor_HadTau_WithErr, iAT, 2, 4, "Translation factor ($\\tau_h$)", withErr );
      printout_first( outputfile, controlData_HadTau, controlData_HadTau_WithErr, iAT, 0, 4, "Control Data ($\\tau_h$)", withErr );
      printout_first( outputfile, predBG_HadTau, predBG_HadTau_WithErr, iAT, 1, 4, "Predicted BG ($\\tau_h$)", withErr );
      fprintf(outputfile, "\\hline\n");
      printout_first( outputfile, factor_NotHadTau, factor_NotHadTau_WithErr, iAT, 2, 4, "Translation factor (non-$\\tau_h$)", withErr );
      printout_first( outputfile, controlData_NotHadTau, controlData_NotHadTau_WithErr, iAT, 0, 4, "Control Data (non-$\\tau_h$)", withErr );
      printout_first( outputfile, predBG_NotHadTau, predBG_NotHadTau_WithErr, iAT, 1, 4, "Predicted BG (non-$\\tau_h$)", withErr);
      fprintf(outputfile, "\\hline\n");
      printout_first( outputfile, predBG_total, predBG_total_WithErr, iAT, 1, 4, "Total Predicted BG", withErr );
      printout_first( outputfile, yieldData, yieldData_WithErr, iAT, 1, 4, "Data Hadronic Yield", withErr );
      fprintf(outputfile, "\\hline\n");

      fprintf(outputfile, " HT (GeV) & 575--675 & 675--775 & 7755--875 & 875--$\\infty$ \\\\ \n ");
      printout_second( outputfile, factor_HadTau, factor_HadTau_WithErr, iAT, 2, 4, 4, "Translation factor ($\\tau_h$)", withErr );
      printout_second( outputfile, controlData_HadTau, controlData_HadTau_WithErr, iAT, 0, 4, 4, "Control Data ($\\tau_h$)", withErr );
      printout_second( outputfile, predBG_HadTau, predBG_HadTau_WithErr, iAT, 1, 4, 4, "Predicted BG ($\\tau_h$)", withErr );
      fprintf(outputfile, "\\hline\n");
      printout_second( outputfile, factor_NotHadTau, factor_NotHadTau_WithErr, iAT, 2, 4, 4, "Translation factor (non-$\\tau_h$)", withErr );
      printout_second( outputfile, controlData_NotHadTau, controlData_NotHadTau_WithErr, iAT, 0, 4, 4, "Control Data (non-$\\tau_h$)", withErr );
      printout_second( outputfile, predBG_NotHadTau, predBG_NotHadTau_WithErr, iAT, 1, 4, 4, "Predicted BG (non-$\\tau_h$)", withErr );
      fprintf(outputfile, "\\hline\n");
      printout_second( outputfile, predBG_total, predBG_total_WithErr, iAT, 1, 4, 4, "Total Predicted BG", withErr );
      printout_second( outputfile, yieldData, yieldData_WithErr, iAT, 1, 4, 4, "Data Hadronic Yield", withErr );
      fprintf(outputfile, "\\hline\n");
    }

    if(iAT == 1){
      fprintf(outputfile, "\\hline\n");
      fprintf(outputfile, " $ \\alpha_T $ range  &  \\multicolumn{4}{c}{0.53 $ < \\alpha_T \\leq $ 0.55}\\\\ \n ");
      fprintf(outputfile, " & 575--675 & 675--775 & 7755--875 & 875--$\\infty$ \\\\ \n ");
      printout_first( outputfile, factor_HadTau, factor_HadTau_WithErr, iAT, 2, 4, "Translation factor ($\\tau_h$)", withErr );
      printout_first( outputfile, controlData_HadTau, controlData_HadTau_WithErr, iAT, 0, 4, "Control Data ($\\tau_h$)", withErr );
      printout_first( outputfile, predBG_HadTau, predBG_HadTau_WithErr, iAT, 1, 4, "Control Data ($\\tau_h$)", withErr );
      fprintf(outputfile, "\\hline\n");
      printout_first( outputfile, factor_NotHadTau, factor_NotHadTau_WithErr, iAT, 2, 4, "Predicted BG ($\\tau_h$)", withErr );
      printout_first( outputfile, controlData_NotHadTau, controlData_NotHadTau_WithErr, iAT, 0, 4, "Translation factor (non-$\\tau_h$)", withErr );
      printout_first( outputfile, predBG_NotHadTau, predBG_NotHadTau_WithErr, iAT, 1, 4, "Predicted BG (non-$\\tau_h$)", withErr );
      fprintf(outputfile, "\\hline\n");
      printout_first( outputfile, predBG_total, predBG_total_WithErr, iAT, 1, 4, "Total Predicted BG", withErr );
      printout_first( outputfile, yieldData, yieldData_WithErr, iAT, 1, 4, "Data Hadronic Yield", withErr );
      fprintf(outputfile, "\\hline\n");
    }

    if(iAT == 2){
      fprintf(outputfile, "\\hline\n");
      fprintf(outputfile, " $ \\alpha_T $ range &  \\multicolumn{4}{c}{0.52 $ < \\alpha_T \\leq $ 0.53}\\\\ \n ");
      fprintf(outputfile, " HT (GeV) &  &  & 7755--875 & 875--$\\infty$ \\\\ \n ");
      printout_first( outputfile, factor_HadTau, factor_HadTau_WithErr, iAT, 2, 4, "Translation factor ($\\tau_h$)", withErr );
      printout_first( outputfile, controlData_HadTau, controlData_HadTau_WithErr, iAT, 0, 4, "Control Data ($\\tau_h$)", withErr );
      printout_first( outputfile, predBG_HadTau, predBG_HadTau_WithErr, iAT, 1, 4, "Predicted BG ($\\tau_h$)", withErr );
      fprintf(outputfile, "\\hline\n");
      printout_first( outputfile, factor_NotHadTau, factor_NotHadTau_WithErr, iAT, 2, 4, "Translation factor (non-$\\tau_h$)", withErr );
      printout_first( outputfile, controlData_NotHadTau, controlData_NotHadTau_WithErr, iAT, 0, 4, "Control Data (non-$\\tau_h$)", withErr );
      printout_first( outputfile, predBG_NotHadTau, predBG_NotHadTau_WithErr, iAT, 1, 4, "Predicted BG (non-$\\tau_h$)", withErr );
      fprintf(outputfile, "\\hline\n");
      printout_first( outputfile, predBG_total, predBG_total_WithErr, iAT, 1, 4, "Total Predicted BG", withErr );
      printout_first( outputfile, yieldData, yieldData_WithErr, iAT, 1, 4, "Data Hadronic Yield", withErr );
      fprintf(outputfile, "\\hline\n");
    }


  }

  fprintf(outputfile, " \\end{tabular}\n");
  fprintf(outputfile, " \\end{flushleft}\n");
  fprintf(outputfile, "\\label{tab:bg-esti-tauhad}\n");
  fprintf(outputfile, " \\end{table}\n\n\n\n");

  fprintf(outputfile,"\\end{document}\n\n\n");

  fclose( outputfile );

}
