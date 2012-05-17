#include "printTables.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TH2D.h"
#include "TLine.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include <stdio.h>
#include "TLegend.h"
#include "TMath.h"
#include "TStyle.h"
#include "getTranslationFactor.h"

using namespace std;

printTables::printTables(){}

vector<vector<double> > printTables::readHist( TH2D* factor){
  TH2D *factorh=(TH2D*)(factor->Clone("factorh"));
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

vector<vector<TString> > printTables::readHist_WithErr( TH2D* factor, TString digit ){
  TH2D *factorh=(TH2D*)(factor->Clone("factorh"));

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
	  TString svalue=Form(digit, value);
	  TString serror=Form(digit, error);
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


vector<vector<double> > printTables::readHist_Err( TH2D* factor){
  TH2D *factorh=(TH2D*)(factor->Clone("factorh"));

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
	  double error=factorh->GetBinError(ix, iy);
	  factor.push_back(error);
	}
      }
      factorre.push_back(factor);
    }

    if((int)(ybinlow*10000.) == 5300 ){
      vector<double> factor;
      for( int ix=1; ix <= nxbins; ix++){
	double xbinlow=factorh->GetXaxis()->GetBinLowEdge(ix);
	if( (int)(xbinlow*10.) >= 5750){
	  double error=factorh->GetBinError(ix, iy);
	  factor.push_back(error);
	}
      }
      factorre.push_back(factor);
    }

    if((int)(ybinlow*10000.) == 5200 ){
      vector<double> factor;
      for( int ix=1; ix <= nxbins; ix++){
	double xbinlow=factorh->GetXaxis()->GetBinLowEdge(ix);
	if( (int)(xbinlow*10.) >= 5750 && (int)(xbinlow*10.) < 7750){
	  factor.push_back(0);
	}
	if( (int)(xbinlow*10.) >= 7750){
	  double error=factorh->GetBinError(ix, iy);
	  factor.push_back(error);
	}
      }
      factorre.push_back(factor);
    }
  }
  return factorre;
}



vector<vector<double> > printTables::readNumerMCHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getNumerMC( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );

  return factorre;
}

vector<vector<double> > printTables::readDominMCHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getDominMC( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );

  return factorre;
}

vector<vector<double> > printTables::readFactorHist( bool MuAddOrNot, bool fullesti, TString HTBin, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getFactor( MuAddOrNot, fullesti, HTBin, isData, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );

  return factorre;
}

vector<vector<double> > printTables::readControlDataHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getControlData( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );
  return factorre;
}

vector<vector<double> > printTables::readYieldDataHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getYieldData( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );
  return factorre;
}

vector<vector<double> > printTables::readPredBGHist( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getPredBG( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<double> > factorre;
  factorre=readHist( factorh );
  return factorre;
}


vector<vector<TString> > printTables::readNumerMCHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getNumerMC( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh, digit );
  return factorre;
}

vector<vector<TString> > printTables::readDominMCHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getDominMC( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh, digit );
  return factorre;
}


vector<vector<TString> > printTables::readFactorHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, bool isData, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getFactor( MuAddOrNot, fullesti, HTBin, isData, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh, digit );

  return factorre;
}

vector<vector<TString> > printTables::readControlDataHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getControlData( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh, digit );
  return factorre;
}

vector<vector<TString> > printTables::readYieldDataHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getYieldData( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh, digit );
  return factorre;
}

vector<vector<TString> > printTables::readPredBGHist_WithErr( bool MuAddOrNot, bool fullesti, TString HTBin, TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n, TString digit ){
  getTranslationFactor factor=getTranslationFactor();
  TH2D* factorh=factor.getPredBG( MuAddOrNot, fullesti, HTBin, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  vector<vector<TString> > factorre;
  factorre=readHist_WithErr( factorh, digit );
  return factorre;
}

void printTables::printout_first_WithErr( FILE *infile, vector<vector<TString> > invString, int irow, int digit, int colum_n, TString firstcol ){

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
}

void printTables::printout_first( FILE *infile, vector<vector<double> > invector, int irow, int digit, int colum_n, TString firstcol ){

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


void printTables::printout_second_WithErr( FILE *infile, vector<vector<TString> > invString, int irow, int digit, int colum_f, int colum_n, TString firstcol ){

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

}

void printTables::printout_second( FILE *infile, vector<vector<double> > invector, int irow, int digit, int colum_f, int colum_n, TString firstcol ){
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

void printTables::printout_final_WithErr( FILE *infile, vector<vector<TString> > invString, int irow, int digit, int colum_f, int colum_n, TString firstcol ){

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
}

void printTables::printout_final( FILE *infile, vector<vector<double> > invector, int irow, int digit, int colum_f, int colum_n, TString firstcol ){

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

void printTables::Tables_ForHadTau( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n ){

  getTranslationFactor factor=getTranslationFactor();

  TH2D *HT_ATTrigeff = factor.HT_ATTrigEff();
  TH2D *SingleMuTrigeff = factor.SingleMuTrigEff();

  //had tau
  TH2D *numerMC_HadTau_h=factor.getNumerMC( true, false, "allHTBins", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *dominMC_HadTau_h=factor.getDominMC( true, false, "allHTBins", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *factor_HadTau_h=factor.getFactor( true, false, "allHTBins", false, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *controlData_HadTau_h=factor.getControlData( true, false, "allHTBins", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *predBG_HadTau_h=factor.getPredBG( true, false, "allHTBins", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );

  TH2D *dominMC_HadTau_h_trigcorr=(TH2D*)( dominMC_HadTau_h->Clone("dominMC_HadTau_h_trigcorr") );
  dominMC_HadTau_h_trigcorr->Multiply(dominMC_HadTau_h_trigcorr, SingleMuTrigeff);


  TH2D *factor_HadTau_h_trigcorr=(TH2D*)( factor_HadTau_h->Clone("factor_HadTau_h_trigcorr") );
  factor_HadTau_h_trigcorr->Divide(factor_HadTau_h_trigcorr, SingleMuTrigeff);

  TH2D *controlData_HadTau_h_trigcorr=(TH2D*)( controlData_HadTau_h->Clone("controlData_HadTau_h_trigcorr") );
  //  controlData_HadTau_h_trigcorr->Multiply(controlData_HadTau_h_trigcorr, HT_ATTrigeff);
  //  controlData_HadTau_h_trigcorr->Divide(controlData_HadTau_h_trigcorr, SingleMuTrigeff);

  TH2D *predBG_HadTau_h_trigcorr=(TH2D*)( predBG_HadTau_h->Clone("predBG_HadTau_h_trigcorr") );
  predBG_HadTau_h_trigcorr->Multiply(predBG_HadTau_h_trigcorr, HT_ATTrigeff);
  predBG_HadTau_h_trigcorr->Divide(predBG_HadTau_h_trigcorr, SingleMuTrigeff);
  //  predBG_HadTau_h_trigcorr->Divide(predBG_HadTau_h_trigcorr, SingleMuTrigeff);

  TString digit="%.1f";
  vector<vector<TString> > numerMC_HadTau_WithErr=readHist_WithErr( numerMC_HadTau_h, digit );
  vector<vector<TString> > dominMC_HadTau_WithErr=readHist_WithErr( dominMC_HadTau_h_trigcorr, digit );
  vector<vector<TString> > factor_HadTau_WithErr=readHist_WithErr( factor_HadTau_h_trigcorr, digit );
  vector<vector<TString> > controlData_HadTau_WithErr=readHist_WithErr( controlData_HadTau_h_trigcorr, digit );
  vector<vector<TString> > predBG_HadTau_WithErr=readHist_WithErr( predBG_HadTau_h_trigcorr, digit );




  TH2D *numerMC_NotHadTau_h=factor.getNumerMC( false, true, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *dominMC_NotHadTau_h=factor.getDominMC( false, true, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *factor_NotHadTau_h=factor.getFactor( false, true, "all", false, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *controlData_NotHadTau_h=factor.getControlData( false, true, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *predBG_NotHadTau_h=factor.getPredBG( false, true, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );

  TH2D *dominMC_NotHadTau_h_trigcorr=(TH2D*)( dominMC_NotHadTau_h->Clone("dominMC_NotHadTau_h_trigcorr") );
  dominMC_NotHadTau_h_trigcorr->Multiply(dominMC_NotHadTau_h_trigcorr, HT_ATTrigeff);

  TH2D *factor_NotHadTau_h_trigcorr=(TH2D*)( factor_NotHadTau_h->Clone("factor_NotHadTau_h_trigcorr") );
  factor_NotHadTau_h_trigcorr->Divide(factor_NotHadTau_h_trigcorr, HT_ATTrigeff);

  TH2D *predBG_NotHadTau_h_trigcorr=(TH2D*)( predBG_NotHadTau_h->Clone("predBG_NotHadTau_h_trigcorr") );
  predBG_NotHadTau_h_trigcorr->Divide(predBG_NotHadTau_h_trigcorr, HT_ATTrigeff);


  vector<vector<TString> > numerMC_NotHadTau_WithErr=readHist_WithErr( numerMC_NotHadTau_h, digit );
  vector<vector<TString> > dominMC_NotHadTau_WithErr=readHist_WithErr( dominMC_NotHadTau_h_trigcorr, digit );
  vector<vector<TString> > factor_NotHadTau_WithErr=readHist_WithErr( factor_NotHadTau_h_trigcorr, digit );
  vector<vector<TString> > controlData_NotHadTau_WithErr=readHist_WithErr( controlData_NotHadTau_h, digit );
  vector<vector<TString> > predBG_NotHadTau_WithErr=readHist_WithErr( predBG_NotHadTau_h_trigcorr, digit );


  TH2D *Zinvh=ZinvPredBG();
  vector<vector<TString> > predBG_Zinv_WithErr=readHist_WithErr( Zinvh, digit );

  TH2D *predBG_totalh_withZinvpred=(TH2D*)(predBG_HadTau_h_trigcorr->Clone("predBG_totalh_withZinvpred"));
  predBG_totalh_withZinvpred->Add(predBG_totalh_withZinvpred, predBG_NotHadTau_h_trigcorr);
  predBG_totalh_withZinvpred->Add(predBG_totalh_withZinvpred, Zinvh );
  vector<vector<TString> > predBG_total_withZinvpred_WithErr=readHist_WithErr( predBG_totalh_withZinvpred, digit );



  vector<vector<TString> > yieldData_WithErr=readYieldDataHist_WithErr( false, true, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n, digit );

  int column_n=4;

  FILE * outputfile;

  outputfile = fopen ("test.tex","w");

  fprintf(outputfile, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputfile, "\\begin{document} \n");

  fprintf(outputfile, "\\begin{table}[htl] \n");

  fprintf(outputfile, "\\caption{Backgroupd predictions.}\n");
  fprintf(outputfile, " \\begin{flushleft}\n");
  fprintf(outputfile, " \\begin{tabular}{ c|cccc }\n");

  fprintf(outputfile, "\\hline\n");

  for(vector<vector<double> >::size_type iAT=0; iAT<factor_HadTau_WithErr.size(); iAT++){

    if(iAT == 0){
      fprintf(outputfile, "$ \\alpha_T $ range   &  \\multicolumn{4}{c}{$\\alpha_T > $ 0.55}\\\\ \n ");
      fprintf(outputfile, " HT (GeV) & 275--325 & 325--375 & 375--475 & 475--575 \\\\ \n ");
      printout_first_WithErr( outputfile, numerMC_HadTau_WithErr, iAT, 2, column_n, "hadronic MC ($\\tau_h$)" );
      printout_first_WithErr( outputfile, dominMC_HadTau_WithErr, iAT, 2, column_n, "$\\mu + jets$ MC ($\\tau_h$)" );
      printout_first_WithErr( outputfile, controlData_HadTau_WithErr, iAT, 0, column_n, "Control Data ($\\tau_h$)" );
      printout_first_WithErr( outputfile, factor_HadTau_WithErr, iAT, 2, column_n, "Translation factor ($\\tau_h$)" );
      printout_first_WithErr( outputfile, predBG_HadTau_WithErr, iAT, 1, column_n, "Predicted BG ($\\tau_h$)" );
      fprintf(outputfile, "\\hline\n");
      printout_first_WithErr( outputfile, numerMC_NotHadTau_WithErr, iAT, 2, column_n, "hadronic MC (e, $\\mu$)" );
      printout_first_WithErr( outputfile, dominMC_NotHadTau_WithErr, iAT, 2, column_n, "$\\mu + jets$ MC (e, $\\mu$)" );
      printout_first_WithErr( outputfile, controlData_NotHadTau_WithErr, iAT, 0, column_n, "Control Data (e, $\\mu$)" );
      printout_first_WithErr( outputfile, factor_NotHadTau_WithErr, iAT, 2, column_n, "Translation factor (e, $\\mu$)" );
      printout_first_WithErr( outputfile, predBG_NotHadTau_WithErr, iAT, 1, column_n, "Predicted BG (e, $\\mu$)" );
      fprintf(outputfile, "\\hline\n");
      printout_first_WithErr( outputfile, predBG_Zinv_WithErr, iAT, 1, column_n, "Predicted Z~$\\rightarrow\\nu\\nu$ + jets" );
      fprintf(outputfile, "\\hline\n");
      printout_first_WithErr( outputfile, predBG_total_withZinvpred_WithErr, iAT, 1, column_n, "Total Predicted BG" );
      printout_first_WithErr( outputfile, yieldData_WithErr, iAT, 1, column_n, "Data Hadronic Yield" );
      fprintf(outputfile, "\\hline\n");

      fprintf(outputfile, " HT (GeV) & 575--675 & 675--775 & 775--875 & 875--$\\infty$ \\\\ \n ");
      printout_second_WithErr( outputfile, numerMC_HadTau_WithErr, iAT, 2, 4, column_n, "hadronic MC ($\\tau_h$)" );
      printout_second_WithErr( outputfile, dominMC_HadTau_WithErr, iAT, 2, 4, column_n, "$\\mu + jets$ MC ($\\tau_h$)" );
      printout_second_WithErr( outputfile, controlData_HadTau_WithErr, iAT, 0, 4, column_n, "Control Data ($\\tau_h$)" );
      printout_second_WithErr( outputfile, factor_HadTau_WithErr, iAT, 2, 4, column_n, "Translation factor ($\\tau_h$)" );
      printout_second_WithErr( outputfile, predBG_HadTau_WithErr, iAT, 1, 4, column_n, "Predicted BG ($\\tau_h$)" );
      fprintf(outputfile, "\\hline\n");
      printout_second_WithErr( outputfile, numerMC_NotHadTau_WithErr, iAT, 2, 4, column_n, "hadronic MC (e, $\\mu$)" );
      printout_second_WithErr( outputfile, dominMC_NotHadTau_WithErr, iAT, 2, 4, column_n, "$\\mu + jets$ MC (e, $\\mu$)" );
      printout_second_WithErr( outputfile, controlData_NotHadTau_WithErr, iAT, 0, 4, column_n, "Control Data (e, $\\mu$)" );
      printout_second_WithErr( outputfile, factor_NotHadTau_WithErr, iAT, 2, 4, column_n, "Translation factor (e, $\\mu$)" );
      printout_second_WithErr( outputfile, predBG_NotHadTau_WithErr, iAT, 1, 4, column_n, "Predicted BG (e, $\\mu$)" );
      fprintf(outputfile, "\\hline\n");
      printout_second_WithErr( outputfile, predBG_Zinv_WithErr, iAT, 1, 4, column_n, "Predicted Z~$\\rightarrow\\nu\\nu$ + jets" );
      fprintf(outputfile, "\\hline\n");
      printout_second_WithErr( outputfile, predBG_total_withZinvpred_WithErr, iAT, 1, 4, column_n, "Total Predicted BG" );
      printout_second_WithErr( outputfile, yieldData_WithErr, iAT, 1, 4, column_n, "Data Hadronic Yield" );
      fprintf(outputfile, "\\hline\n");
    }
  }

  fprintf(outputfile, " \\end{tabular}\n");
  fprintf(outputfile, " \\end{flushleft}\n");
  fprintf(outputfile, "\\label{tab:bg-esti-tauhad-1}\n");
  fprintf(outputfile, " \\end{table}\n\n\n\n");


  fprintf(outputfile,"\\end{document}\n\n\n");

  fclose( outputfile );

}


int printTables::Tables_ForNormal( TString closureTests, int iJetStart, int iJet_n, int jJetStart, int jJet_n ){

  if ( normalEstimation_ != true ){
    cout<< "Note: Not normal Estimation" <<endl;
    return 0;
  }
  getTranslationFactor factor=getTranslationFactor();

  TH2D *HT_ATTrigeff = HT_ATTrigEff();

  TH2D *numerMC_h=factor.getNumerMC( false, true, "allHTBins", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *dominMC_h=factor.getDominMC( false, true, "allHTBins", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *factor_h=factor.getFactor( false, true, "allHTBins", false, closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *controlData_h=factor.getControlData( false, true, "allHTBins", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *predBG_h=factor.getPredBG( false, true, "allHTBins", closureTests, iJetStart, iJet_n, jJetStart, jJet_n );
  TH2D *dominMC_h_trigcorr=(TH2D*)( dominMC_h->Clone("dominMC_h_trigcorr") );
  //  dominMC_h_trigcorr->Multiply(dominMC_h_trigcorr, HT_ATTrigeff);

  TH2D *factor_h_trigcorr=(TH2D*)( factor_h->Clone("factor_h_trigcorr") );
  //  factor_h_trigcorr->Divide(factor_h_trigcorr, HT_ATTrigeff);

  TH2D *predBG_h_trigcorr=(TH2D*)( predBG_h->Clone("predBG_h_trigcorr") );
  //  predBG_h_trigcorr->Divide(predBG_h_trigcorr, HT_ATTrigeff);

  TString digit="%.1f";
  vector<vector<TString> > numerMC_WithErr=readHist_WithErr( numerMC_h, digit );
  vector<vector<TString> > dominMC_WithErr=readHist_WithErr( dominMC_h_trigcorr, digit );
  vector<vector<TString> > factor_WithErr=readHist_WithErr( factor_h_trigcorr, "%.2f" );
  vector<vector<TString> > controlData_WithErr=readHist_WithErr( controlData_h, digit );
  vector<vector<TString> > predBG_WithErr=readHist_WithErr( predBG_h_trigcorr, digit );


  TH2D *Zinvh=ZinvPredBG();
  vector<vector<TString> > predBG_Zinv_WithErr=readHist_WithErr( Zinvh, digit );

  TH2D *predBG_totalh_withZinvpred=(TH2D*)(predBG_h_trigcorr->Clone("predBG_totalh_withZinvpred"));
  predBG_totalh_withZinvpred->Add(predBG_totalh_withZinvpred, Zinvh );
  vector<vector<TString> > predBG_total_withZinvpred_WithErr=readHist_WithErr( predBG_totalh_withZinvpred, digit );

  vector<vector<TString> > yieldData_WithErr=readYieldDataHist_WithErr( false, true, "all", closureTests, iJetStart, iJet_n, jJetStart, jJet_n, digit );



  int column_n=4;

  FILE * outputfile;
  if( closureTests == "iTojJet" ){
    char buffer[100];
    sprintf (buffer, "table_iTojJet_%d_%dTo%d_%db.tex", iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2);
    outputfile = fopen (buffer,"w");
  } else if( closureTests == "1To2Mu"){
    char buffer[100];
    sprintf (buffer, "table_1To2Mu_%dTo%db.tex", startNJet_-1, startNJet_+nJets_-2);
    outputfile = fopen (buffer,"w");
  } else {
    char buffer[100];
    sprintf (buffer, "table_%dTo%db.tex", startNJet_-1, startNJet_+nJets_-2);
    outputfile = fopen (buffer,"w");
  }
  fprintf(outputfile, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputfile, "\\begin{document} \n");

  fprintf(outputfile, "\\begin{table}[htl] \n");

  fprintf(outputfile, "\\caption{Backgroupd predictions.}\n");
  fprintf(outputfile, " \\begin{flushleft}\n");
  fprintf(outputfile, " \\begin{tabular}{ c|cccc }\n");

  fprintf(outputfile, "\\hline\n");

  for(vector<vector<double> >::size_type iAT=0; iAT<factor_WithErr.size(); iAT++){

    if(iAT == 0){

      //      fprintf(outputfile, "$ \\alpha_T $ range   &  \\multicolumn{4}{c}{$\\alpha_T > $ 0.55}\\\\ \n ");
      if( closureTests == "iTojJet" ){
	if( jJet_n < 15 ){
	  fprintf(outputfile, "$ \\alpha_T $ range   &  \\multicolumn{4}{c}{no $\\alpha_T$ cut ( Closure test: b-jets %d--%d $\\rightarrow$ %d--%d )}\\\\ \n ", iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2 );
	} else{
	  fprintf(outputfile, "$ \\alpha_T $ range   &  \\multicolumn{4}{c}{no $\\alpha_T$ cut ( Closure test: b-jets %d--%d $\\rightarrow$ %d--$\\infty$ )}\\\\ \n ", iJetStart-1, iJetStart+iJet_n-2, jJetStart-1 );
	}
      } else if( closureTests == "1To2Mu" ){
	fprintf(outputfile, "$ \\alpha_T $ range   &  \\multicolumn{4}{c}{no $\\alpha_T$ cut ( Closure test: $\\mu \\rightarrow \\mu\\mu$, %d--%d b-jets )}\\\\ \n ", startNJet_-1, startNJet_+nJets_-2 );
      } else {
	fprintf(outputfile, "$ \\alpha_T $ range   &  \\multicolumn{4}{c}{no $\\alpha_T$ cut (%d--%d b-jets) }\\\\ \n ",  startNJet_-1, startNJet_+nJets_-2 );
      }
      fprintf(outputfile, " HT (GeV) & 275--325 & 325--375 & 375--475 & 475--575 \\\\ \n ");

      //      printout_first_WithErr( outputfile, numerMC_WithErr, iAT, 2, column_n, "hadronic MC" );
      if( closureTests == "1To2Mu" ){
        printout_first_WithErr( outputfile, numerMC_WithErr, iAT, 2, column_n, "$\\mu\\mu + jets$ MC" );
	printout_first_WithErr( outputfile, dominMC_WithErr, iAT, 2, column_n, "$\\mu + jets$ MC" );
      } else if ( closureTests == "iTojJet" ){
	TString outputnum=Form("%d--%d b-jets", jJetStart-1, jJetStart+jJet_n-2);
	TString outputdom=Form("%d--%d b-jets", iJetStart-1, iJetStart+iJet_n-2);
	if( MuonNumber_ == "DiMuon_"){
          printout_first_WithErr( outputfile, numerMC_WithErr, iAT, 2, column_n, "$\\mu\\mu + jets$ MC ("+outputnum+")" );
	  printout_first_WithErr( outputfile, dominMC_WithErr, iAT, 2, column_n, "$\\mu\\mu + jets$ MC ("+outputdom+")" );
	} else {
          printout_first_WithErr( outputfile, numerMC_WithErr, iAT, 2, column_n, "$\\mu + jets$ MC ("+outputnum+")" );
	  printout_first_WithErr( outputfile, dominMC_WithErr, iAT, 2, column_n, "$\\mu + jets$ MC ("+outputdom+")" );
	}
      } else {
	if( MuonNumber_ == "DiMuon_"){
	  printout_first_WithErr( outputfile, dominMC_WithErr, iAT, 2, column_n, "$\\mu\\mu + jets$ MC" );
	} else if ( MuonNumber_ == "OneMuon_" ){
	  printout_first_WithErr( outputfile, dominMC_WithErr, iAT, 2, column_n, "$\\mu + jets$ MC" );
	}
      }
      printout_first_WithErr( outputfile, factor_WithErr, iAT, 2, column_n, "Translation factor" );
      printout_first_WithErr( outputfile, controlData_WithErr, iAT, 0, column_n, "Control Data" );
      printout_first_WithErr( outputfile, predBG_WithErr, iAT, 1, column_n, "Prediction" );
      //      printout_first_WithErr( outputfile, predBG_Zinv_WithErr, iAT, 1, column_n, "Predicted Z~$\\rightarrow\\nu\\nu$ + jets" );
      //      fprintf(outputfile, "\\hline\n");
      if( closureTests == "1To2Mu" ){
	printout_first_WithErr( outputfile, yieldData_WithErr, iAT, 1, column_n, "Data Yield ($\\mu\\mu + jets$)" );
      } else if ( closureTests == "iTojJet" ){
        if( MuonNumber_ == "DiMuon_"){
	  printout_first_WithErr( outputfile, yieldData_WithErr, iAT, 1, column_n, "Data Yield ($\\mu\\mu + jets$)" );
	} else {
	  printout_first_WithErr( outputfile, yieldData_WithErr, iAT, 1, column_n, "Data Yield ($\\mu + jets$)" );
	}
      } else {
	  printout_first_WithErr( outputfile, yieldData_WithErr, iAT, 1, column_n, "Data Yield (hadronic)" );
      }
      fprintf(outputfile, "\\hline\n");

      fprintf(outputfile, " HT (GeV) & 575--675 & 675--775 & 775--875 & 875--$\\infty$ \\\\ \n ");
      //      printout_second_WithErr( outputfile, numerMC_WithErr, iAT, 2, 4, column_n, "hadronic MC" );
      if( closureTests == "1To2Mu" ){
	printout_second_WithErr( outputfile, numerMC_WithErr, iAT, 2, 4, column_n, "$\\mu\\mu + jets$ MC" );
	printout_second_WithErr( outputfile, dominMC_WithErr, iAT, 2, 4, column_n, "$\\mu + jets$ MC" );
      } else if(  closureTests == "iTojJet" ){
	TString outputnum=Form("%d--%d b-jets", jJetStart-1, jJetStart+jJet_n-2);
	TString outputdom=Form("%d--%d b-jets", iJetStart-1, iJetStart+iJet_n-2);
	if( MuonNumber_ == "DiMuon"){
	  printout_second_WithErr( outputfile, numerMC_WithErr, iAT, 2, 4, column_n, "$\\mu\\mu + jets$ MC ("+outputnum+")" );;
	  printout_second_WithErr( outputfile, dominMC_WithErr, iAT, 2, 4, column_n, "$\\mu\\mu + jets$ MC ("+outputdom+")" );
	} else {
	  printout_second_WithErr( outputfile, numerMC_WithErr, iAT, 2, 4, column_n, "$\\mu + jets$ MC ("+outputnum+")" );
	  printout_second_WithErr( outputfile, dominMC_WithErr, iAT, 2, 4, column_n, "$\\mu + jets$ MC ("+outputdom+")" );
	}
      } else {
	if( MuonNumber_ == "DiMuon"){
	  printout_second_WithErr( outputfile, dominMC_WithErr, iAT, 2, 4, column_n, "$\\mu\\mu + jets$ MC" );
	} else {
	  printout_second_WithErr( outputfile, dominMC_WithErr, iAT, 2, 4, column_n, "$\\mu + jets$ MC" );
	}
      }
      printout_second_WithErr( outputfile, factor_WithErr, iAT, 2, 4, column_n, "Translation factor" );
      printout_second_WithErr( outputfile, controlData_WithErr, iAT, 0, 4, column_n, "Control Data" );
      printout_second_WithErr( outputfile, predBG_WithErr, iAT, 1, 4, column_n, "Prediction" );
      //      fprintf(outputfile, "\\hline\n");
      //      printout_second_WithErr( outputfile, predBG_Zinv_WithErr, iAT, 1, 4, column_n, "Predicted Z~$\\rightarrow\\nu\\nu$ + jets" );
      //      fprintf(outputfile, "\\hline\n");
      //      printout_second_WithErr( outputfile, predBG_total_withZinvpred_WithErr, iAT, 1, 4, column_n, "Total Predicted BG" );
      if( closureTests == "1To2Mu" ){
	printout_second_WithErr( outputfile, yieldData_WithErr, iAT, 1, 4, column_n, "Data Yield ($\\mu\\mu + jets$)" );
      } else if ( closureTests == "iTojJet" ){
        if( MuonNumber_ == "DiMuon_"){
	  printout_second_WithErr( outputfile, yieldData_WithErr, iAT, 1, 4, column_n, "Data Yield ($\\mu\\mu + jets$)" );
	} else {
	  printout_second_WithErr( outputfile, yieldData_WithErr, iAT, 1, 4, column_n, "Data Yield ($\\mu + jets$)" );
	}
      } else {
	printout_second_WithErr( outputfile, yieldData_WithErr, iAT, 1, 4, column_n, "Data Hadronic Yield" );
      }
      fprintf(outputfile, "\\hline\n");
    }

  }

  fprintf(outputfile, " \\end{tabular}\n");
  fprintf(outputfile, " \\end{flushleft}\n");
  if( closureTests == "iTojJet" ){
    fprintf(outputfile, "\\label{tab:bg-esti-iTojJet-%d_%dTo%d_%db}\n", iJetStart-1, iJetStart+iJet_n-2, jJetStart-1, jJetStart+jJet_n-2);
  } else if( closureTests == "1To2Mu" ){
    fprintf(outputfile, "\\label{tab:bg-esti-1To2Mu-%dTo%db}\n", startNJet_-1, startNJet_+nJets_-2);
  } else {
    fprintf(outputfile, "\\label{tab:bg-esti-iTojJet-%dTo%db}\n", startNJet_-1, startNJet_+nJets_-2);
  }

  fprintf(outputfile, " \\end{table}\n\n\n\n");


  fprintf(outputfile,"\\end{document}\n\n\n");

  fclose( outputfile );

  return 1;
}



/*void printTables::PredictionOverlay(){

  getTranslationFactor factor=getTranslationFactor();

  TH2D *HT_ATTrigeff = factor.HT_ATTrigEff();
  TH2D *SingleMuTrigeff = factor.SingleMuTrigEff();

  //had tau
  TH2D *predBG_HadTau_h=factor.getPredBG( true, false, "all" );
  TH2D *predBG_HadTau_h_trigcorr=(TH2D*)( predBG_HadTau_h->Clone("predBG_HadTau_h_trigcorr") );
  predBG_HadTau_h_trigcorr->Multiply(predBG_HadTau_h_trigcorr, HT_ATTrigeff);
  predBG_HadTau_h_trigcorr->Divide(predBG_HadTau_h_trigcorr, SingleMuTrigeff);

  vector<vector<double> > predBG_HadTau_WithErr=readHist_Err( predBG_HadTau_h_trigcorr );
  vector<vector<double> > predBG_HadTau=readHist( predBG_HadTau_h_trigcorr );




  TH2D *predBG_NotHadTau_h=factor.getPredBG( false, true, "all" );

  TH2D *predBG_NotHadTau_h_trigcorr=(TH2D*)( predBG_NotHadTau_h->Clone("predBG_NotHadTau_h_trigcorr") );
  predBG_NotHadTau_h_trigcorr->Divide(predBG_NotHadTau_h_trigcorr, HT_ATTrigeff);

  vector<vector<double> > predBG_NotHadTau_WithErr=readHist_Err( predBG_NotHadTau_h_trigcorr );
  vector<vector<double> > predBG_NotHadTau=readHist( predBG_NotHadTau_h_trigcorr );



  TH2D *predBG_totalh=(TH2D*)(predBG_HadTau_h_trigcorr->Clone("predBG_totalh"));
  predBG_totalh->Add(predBG_totalh, predBG_NotHadTau_h_trigcorr);
  vector<vector<double> > predBG_total=readHist( predBG_totalh );
  vector<vector<double> > predBG_total_WithErr=readHist_Err( predBG_totalh );

  TH2D *Zinvh=ZinvPredBG();
  vector<vector<double> > predBG_Zinv=readHist( Zinvh );
  vector<vector<double> > predBG_Zinv_WithErr=readHist_Err( Zinvh );

  TH2D *predBG_totalh_withZinvpred=(TH2D*)(predBG_HadTau_h_trigcorr->Clone("predBG_totalh_withZinvpred"));
  predBG_totalh_withZinvpred->Add(predBG_totalh_withZinvpred, predBG_NotHadTau_h_trigcorr);
  predBG_totalh_withZinvpred->Add(predBG_totalh_withZinvpred, Zinvh );
  vector<vector<double> > predBG_total_withZinvpred=readHist( predBG_totalh_withZinvpred );
  vector<vector<double> > predBG_total_withZinvpred_WithErr=readHist_Err( predBG_totalh_withZinvpred );



  TH2D *yieldDatah=factor.getYieldData(false, true, "all" );
  vector<vector<double> > yieldData=readHist( yieldDatah );
  vector<vector<double> > yieldData_WithErr=readHist_Err( yieldDatah );


  TCanvas *c1=new TCanvas();
  TLegend *len=new TLegend(0.65,0.75,0.995,0.995);


  double xbins[9]={275.,325.,375.,475.,575.,675.,775.,875.,975.};
  int nxbins=8;

  TH1D *hZinv=new TH1D("hZinv", "hZinv", nxbins, xbins);
  TH1D *hTauHad=new TH1D("hTauHad", "hTauHad", nxbins, xbins );
  TH1D *hNotTauHad=new TH1D("hNotTauHad", "hNotTauHad", nxbins, xbins );
  TH1D *htotal=new TH1D("htotal", "htotal", nxbins, xbins );
  TH1D* hdata=new TH1D("hdata", "hdata", nxbins, xbins );

  hZinv->Sumw2();
  hTauHad->Sumw2();
  hNotTauHad->Sumw2();
  htotal->Sumw2();
  hdata->Sumw2();

  for(vector<vector<double> >::size_type iAT=0; iAT<yieldData.size(); iAT++){

    if(iAT == 0){
      for(int iHT = 0; iHT <= 7; iHT++ ){
	hNotTauHad->SetBinContent( iHT+1, predBG_NotHadTau[iAT][iHT] );
	hZinv->SetBinContent( iHT+1, predBG_Zinv[iAT][iHT] );
	hTauHad->SetBinContent( iHT+1, predBG_HadTau[iAT][iHT] );
	htotal->SetBinContent( iHT+1, predBG_total_withZinvpred[iAT][iHT] );
	hdata->SetBinContent( iHT+1, yieldData[iAT][iHT] );

	hNotTauHad->SetBinError( iHT+1, predBG_NotHadTau_WithErr[iAT][iHT] );
	hZinv->SetBinError( iHT+1, predBG_Zinv_WithErr[iAT][iHT] );
	hTauHad->SetBinError( iHT+1, predBG_HadTau_WithErr[iAT][iHT] );
	htotal->SetBinError( iHT+1, predBG_total_withZinvpred_WithErr[iAT][iHT] );
	hdata->SetBinError( iHT+1, yieldData_WithErr[iAT][iHT] );
      }
    }
  }

  TH1D *hclone=(TH1D*)(hdata->Clone("hclone"));
  hclone->Scale(1.3);
  hclone->Draw();
  hclone->SetLineColor(0);
  hclone->SetMarkerColor(0);

  hdata->Draw("same");
  hdata->SetLineColor(1);
  hdata->SetLineWidth(2);
  hdata->SetMarkerColor(1);
  hdata->SetMarkerStyle(20);

  htotal->Draw("same");
  htotal->SetLineColor(2);
  htotal->SetLineWidth(2);
  htotal->SetMarkerColor(2);
  htotal->SetFillColor(2);

  TH1D *htau=(TH1D*)(hNotTauHad->Clone("htau"));
  htau->Add(htau, hTauHad);
  htau->Draw("same");
  htau->SetLineColor(4);
  htau->SetLineWidth(2);
  htau->SetMarkerColor(4);
  htau->SetFillColor(4);

  hTauHad->Draw("same");
  hTauHad->SetLineColor(3);
  hTauHad->SetLineWidth(2);
  hTauHad->SetMarkerColor(3);
  hTauHad->SetFillColor(3);

//  hZinv->Draw("same");
//  hZinv->SetLineColor(5);
//  hZinv->SetMarkerColor(5);


  //  len->AddEntry( hZinv, "Z#rightarrow#nu#nu + jets");
  len->AddEntry( hTauHad, "Predicted #tau_{h} BG");
  len->AddEntry( htau, "Predicted #tau_{h}, e and #mu BG");
  len->AddEntry( htotal, "Total predicted BG");
  len->AddEntry( hdata, "Data");

  len->Draw();
  c1->SetLogy(0);
  c1->SaveAs("yield_pred.eps");
  c1->SetLogy(1);
  c1->SaveAs("yield_pred_log.eps");
  c1->Update();

}
*/


/*void printTables::CompareYouAndMe(){
  getTranslationFactor factor=getTranslationFactor();

  TH2D *HT_ATTrigeff = factor.HT_ATTrigEff();
  TH2D *SingleMuTrigeff = factor.SingleMuTrigEff();


  TH2D *predBG_HadTau_h=factor.getPredBG( true, false, "all" );
  TH2D *predBG_HadTau_h_trigcorr=(TH2D*)( predBG_HadTau_h->Clone("predBG_HadTau_h_trigcorr") );
  predBG_HadTau_h_trigcorr->Multiply(predBG_HadTau_h_trigcorr, HT_ATTrigeff);
  predBG_HadTau_h_trigcorr->Divide(predBG_HadTau_h_trigcorr, SingleMuTrigeff);
  vector<vector<double> > predBG_HadTau_WithErr=readHist_Err( predBG_HadTau_h_trigcorr );
  vector<vector<double> > predBG_HadTau=readHist( predBG_HadTau_h_trigcorr );


  TH2D *predBG_NotHadTau_h=factor.getPredBG( false, true, "all" );
  TH2D *predBG_NotHadTau_h_trigcorr=(TH2D*)( predBG_NotHadTau_h->Clone("predBG_NotHadTau_h_trigcorr") );
  predBG_NotHadTau_h_trigcorr->Divide(predBG_NotHadTau_h_trigcorr, HT_ATTrigeff);
  vector<vector<double> > predBG_NotHadTau_WithErr=readHist_Err( predBG_NotHadTau_h_trigcorr );
  vector<vector<double> > predBG_NotHadTau=readHist( predBG_NotHadTau_h_trigcorr );


  TH2D* Normalh = NormalWJPredBG();
  vector<vector<double> > predBG_Normal=readHist( Normalh );
  vector<vector<double> > predBG_Normal_WithErr=readHist_Err( Normalh );



  TH2D *dominMC_HadTau_h=factor.getDominMC( true, false, "all" );
  TH2D *controlData_HadTau_h=factor.getControlData( true, false, "all" );
  TH2D *dominMC_HadTau_h_trigcorr=(TH2D*)( dominMC_HadTau_h->Clone("dominMC_HadTau_h_trigcorr") );
  dominMC_HadTau_h_trigcorr->Multiply(dominMC_HadTau_h_trigcorr, SingleMuTrigeff);
  TH2D *controlData_HadTau_h_trigcorr=(TH2D*)( controlData_HadTau_h->Clone("controlData_HadTau_h_trigcorr") );

  vector<vector<double> > dominMC_HadTau_WithErr=readHist_Err( dominMC_HadTau_h_trigcorr );
  vector<vector<double> > controlData_HadTau_WithErr=readHist_Err( controlData_HadTau_h_trigcorr );
  vector<vector<double> > dominMC_HadTau=readHist( dominMC_HadTau_h_trigcorr );
  vector<vector<double> > controlData_HadTau=readHist( controlData_HadTau_h );


  TH2D *dominMC_NotHadTau_h=factor.getDominMC( false, true, "all" );
  TH2D *controlData_NotHadTau_h=factor.getControlData( false, true, "all" );
  TH2D *dominMC_NotHadTau_h_trigcorr=(TH2D*)( dominMC_NotHadTau_h->Clone("dominMC_NotHadTau_h_trigcorr") );
  dominMC_NotHadTau_h_trigcorr->Multiply(dominMC_NotHadTau_h_trigcorr, HT_ATTrigeff);

  vector<vector<double> > dominMC_NotHadTau_WithErr=readHist_Err( dominMC_NotHadTau_h_trigcorr );
  vector<vector<double> > controlData_NotHadTau_WithErr=readHist_Err( controlData_NotHadTau_h );
  vector<vector<double> > dominMC_NotHadTau=readHist( dominMC_NotHadTau_h_trigcorr );
  vector<vector<double> > controlData_NotHadTau=readHist( controlData_NotHadTau_h );


  TCanvas *c1=new TCanvas();
  TLegend *len=new TLegend(0.15,0.65,0.45,0.995);

  double xbins[9]={275.,325.,375.,475.,575.,675.,775.,875.,975.};
  int nxbins=8;

  TH1D *hTauHad=new TH1D("hTauHad", "hTauHad", nxbins, xbins );
  TH1D *hNotTauHad=new TH1D("hNotTauHad", "hNotTauHad", nxbins, xbins );
  TH1D *hnormal=new TH1D("hnormal", "hnormal", nxbins, xbins );
  TH1D *hMCDataCompTauHad=new TH1D("hMCDataCompTauHad", "hMCDataCompTauHad", nxbins, xbins);
  TH1D *hMCDataCompNotTauHad=new TH1D("hMCDataCompNotTauHad", "hMCDataCompNotTauHad", nxbins, xbins);
  TH1D *hMCDataComptotal=new TH1D("hMCDataComptotal", "hMCDataComptotal", nxbins, xbins);

  hTauHad->Sumw2();
  hNotTauHad->Sumw2();
  hnormal->Sumw2();

  hMCDataCompTauHad->Sumw2();
  hMCDataCompNotTauHad->Sumw2();
  hMCDataComptotal->Sumw2();

  for(vector<vector<double> >::size_type iAT=0; iAT<predBG_HadTau.size(); iAT++){

    if(iAT == 0){
      for(int iHT = 0; iHT <= 7; iHT++ ){
	hTauHad->SetBinContent( iHT+1, predBG_HadTau[iAT][iHT] );
	hNotTauHad->SetBinContent( iHT+1, predBG_NotHadTau[iAT][iHT] );
	hnormal->SetBinContent( iHT+1, predBG_Normal[iAT][iHT] );
	hMCDataCompTauHad->SetBinContent( iHT+1, (controlData_HadTau[iAT][iHT]-dominMC_HadTau[iAT][iHT])/controlData_HadTau[iAT][iHT] );
	hMCDataCompNotTauHad->SetBinContent( iHT+1, (-dominMC_NotHadTau[iAT][iHT]+controlData_NotHadTau[iAT][iHT])/controlData_NotHadTau[iAT][iHT] );
	hMCDataComptotal->SetBinContent(iHT+1, (-dominMC_HadTau[iAT][iHT]-dominMC_NotHadTau[iAT][iHT]+controlData_HadTau[iAT][iHT]+controlData_NotHadTau[iAT][iHT])/(controlData_HadTau[iAT][iHT]+controlData_NotHadTau[iAT][iHT]));

	hTauHad->SetBinError( iHT+1, predBG_HadTau_WithErr[iAT][iHT] );
	hNotTauHad->SetBinError( iHT+1, predBG_NotHadTau_WithErr[iAT][iHT] );
	hnormal->SetBinError( iHT+1, predBG_Normal_WithErr[iAT][iHT] );
	hMCDataCompTauHad->SetBinError(iHT+1, 0);
	hMCDataCompNotTauHad->SetBinError(iHT+1, 0);
	hMCDataComptotal->SetBinError(iHT+1, 0);
      }
    }
  }



  TH1D *htau1=(TH1D*)(hNotTauHad->Clone("htau1"));
  htau1->Add(htau1, hTauHad);
  hnormal->Scale(-1.);
  htau1->Add(htau1, hnormal);

//  for(vector<vector<double> >::size_type iAT=0; iAT<yieldData.size(); iAT++){

//    if(iAT == 0){
//      for(int iHT = 0; iHT <= 7; iHT++ ){
//	int i=iHT+1;
//	double a=htau1->GetBinContent(i);
//	double a2=(htau1->GetBinContent(i))*(htau1->GetBinContent(i));
//	double b=0. - hnormal->GetBinContent(i);
//	double b2=(hnormal->GetBinContent(i))*(hnormal->GetBinContent(i));
//	double ae2=(htau1->GetBinError(i))*(htau1->GetBinError(i));
//	double be2=(hnormal->GetBinError(i))*(hnormal->GetBinError(i));

//	double err=fabs(a/b)*(sqrt(ae2/a2+be2/b2 - 2*(sqrt(ae2/a2*(be2/b2)))));
//	htau1->SetBinError( i, err );
//        cout<<a/b*(sqrt(ae2/a2+be2/b2 - 2*(sqrt(ae2/a2*(be2/b2)))))<<endl;

//      }
//    }
//    }

  htau1->Divide(htau1, hnormal);
  htau1->Draw();
  htau1->Scale(-1.);
  htau1->GetXaxis()->SetTitle("H_{T} (GeV)");
  htau1->GetYaxis()->SetRangeUser(-1.,1.5);
  //  htau1->SetLineColor(0);
  htau1->SetMarkerStyle(22);

  hMCDataCompTauHad->Draw("samee");
  hMCDataCompTauHad->SetLineColor(2);
  hMCDataCompTauHad->SetMarkerColor(2);

  hMCDataCompNotTauHad->Draw("samee");
  hMCDataCompNotTauHad->SetLineColor(3);
  hMCDataCompNotTauHad->SetMarkerColor(3);

  hMCDataComptotal->Draw("samee");
  hMCDataComptotal->SetLineColor(4);
  hMCDataComptotal->SetMarkerColor(4);

  len->AddEntry(htau1, "(N_{sep}-N_{global})/N_{global}");
  len->AddEntry(hMCDataCompTauHad, "(N^{#tau_{h}}_{data,control}-N^{#tau_{h}}_{MC,control})/N^{#tau_{h}}_{data,control}");
  len->AddEntry(hMCDataCompNotTauHad, "(N^{e,#mu}_{data,control}-N^{e,#mu}_{MC,control})/N^{e,#mu}_{data,control}");
  len->AddEntry(hMCDataComptotal, "(N_{data,control}-N_{MC,control})/N_{data,control}");
  len->Draw();
  c1->SetLogy(0);
  c1->SaveAs("compareSepNotSep.eps");

}
*/


