#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>


TH1D* getHist( TFile *f, TString dirname, TString hname){
  TDirectory *TDir = (TDirectory*)( f->Get( dirname ) );
  TH1D* inh= (TH1D*)( TDir->Get( hname ) );
  return inh;
}


double getHistEntries( TH1D* inh, vector<int> binrange, double scale){
  double entries=0;
  entries = inh->Integral(binrange[0], binrange[1]);
  return entries*scale;
}


double getHistEntriesSumDiffFiles( vector<TFile*> vf, TString dirname, TString hname, vector<int> binrange, double scale ){
  double entries=0;
  for( unsigned int ifile=0; ifile < vf.size(); ifile++ ){
    TH1D *h = getHist(vf[ifile], dirname, hname);
    entries = entries + getHistEntries( h, binrange, scale );
  }

  return entries;
}

vector<double> vEntriesDiffDir( vector<TFile*> vf, vector<TString> vdirname, TString hname, vector<int> binrange, double scale ){

  vector<double> ventries;
  for( unsigned int idir=0; idir < vdirname.size(); idir++){
    double entries = getHistEntriesSumDiffFiles( vf, vdirname[idir], hname, binrange, scale );
    ventries.push_back(entries);
  }

  return ventries;
}

vector<double> vEntriesDiffHist( vector<TFile*> vf, TString dirname, vector<TString> vhname, vector<int> binrange, double scale ){
  vector<double> ventries;
  for( unsigned int ih=0; ih < vhname.size(); ih++){
    double entries = getHistEntriesSumDiffFiles( vf, dirname, vhname[ih], binrange, scale );
    ventries.push_back(entries);
  }

  return ventries;
}


void getResults( TString outputfilename ){
  TString dir="/Users/zmeng/Work_CMS/SUSY/myppt/BGEstimation_16022012/rootfiles/oneMuonSele";
  vector<TFile *> vfLow275;
  TFile *low275_1=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBinsMuonHTATTrig275.root");
  TFile *low275_2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBinsMuonHTATTrig275.root");
  vfLow275.push_back(low275_1);
  vfLow275.push_back(low275_2);
  vector<TFile *> vfLow325;
  TFile *low325_1=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBinsMuonHTATTrig325.root");
  TFile *low325_2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBinsMuonHTATTrig325.root");
  vfLow325.push_back(low325_1);
  vfLow325.push_back(low325_2);
  vector<TFile *> vfHig;
  TFile *hig_1=new TFile(dir+"/"+"NoSmearALL_PUS4HigHTBinsMuonHTATTrig.root");
  TFile *hig_2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6HigHTBinsMuonHTATTrig.root");
  vfHig.push_back(hig_1);
  vfHig.push_back(hig_2);

  vector<int> vbinrangeLow275;
  vbinrangeLow275.push_back(53);
  vbinrangeLow275.push_back(53);
  vector<int> vbinrangeLow325;
  vbinrangeLow325.push_back(54);
  vbinrangeLow325.push_back(55);
  vector<int> vbinrangeHig;
  vbinrangeHig.push_back(56);
  vbinrangeHig.push_back(10000000);

  vector<TString> vhname;
  vhname.push_back("AlphaT_CommJetgeq2_h_all");
  vhname.push_back("AlphaT_CommJetgeq2_hasTrueVLep_h_all");
  vhname.push_back("AlphaT_CommJetgeq2_hasTrueTauHad_h_all");
  vhname.push_back("AlphaT_CommJetgeq2_hasTrueTauLep_h_all");
  vhname.push_back("AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_all");

  vector<TString> vdirnameLow275;
  vdirnameLow275.push_back("OneMuon_275_325");
  vector<TString> vdirnameLow325;
  vdirnameLow325.push_back("OneMuon_325_375");
  vector<TString> vdirnameHig;
  vdirnameHig.push_back("OneMuon_375_475");
  vdirnameHig.push_back("OneMuon_475_575");
  vdirnameHig.push_back("OneMuon_575_675");
  vdirnameHig.push_back("OneMuon_675_775");
  vdirnameHig.push_back("OneMuon_775_875");
  vdirnameHig.push_back("OneMuon_875");

  vector<TString> vHTnameLow275;
  vHTnameLow275.push_back("275--325");
  vector<TString> vHTnameLow325;
  vHTnameLow325.push_back("325--375");
  vector<TString> vHTnameHig;
  vHTnameHig.push_back("375--475");
  vHTnameHig.push_back("475--575");
  vHTnameHig.push_back("575--675");
  vHTnameHig.push_back("675--775");
  vHTnameHig.push_back("775--875");
  vHTnameHig.push_back("875--$\\infty$");

  double scale = 46.5;

  //  std::ofstream outputhadtau;
  FILE * outputhadtau;
  outputhadtau = fopen (outputfilename,"w");

  fprintf(outputhadtau, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputhadtau, "\\begin{document} \n");

  fprintf(outputhadtau, "\\begin{table}[ht] \n");

  fprintf(outputhadtau, "\\caption{Event type compositons of single muon selection in background MC samples}\n");
  fprintf(outputhadtau, "\\centering\n");
  fprintf(outputhadtau, " \\begin{tabular}{ c|ccccc }\n");

  fprintf(outputhadtau, "\\hline\n");
  fprintf(outputhadtau, "   &  \\multicolumn{5}{c}{$\\alpha_T > $ 0.55}\\\\ \n ");
  fprintf(outputhadtau, "HT Bins & Total NO. events& W to e/$\\mu$ & $\\tau_{had}$ & $\\tau$ to e/$\\mu$ & $\\tau_{had}$ matched jet\\\\ \n");
  fprintf(outputhadtau, "\\hline\n");

  for( unsigned int idir=0; idir<vdirnameLow275.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameLow275[idir].Data());

    vector<double> entry=vEntriesDiffHist( vfLow275, vdirnameLow275[idir], vhname, vbinrangeHig, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf (outputhadtau, " & %.2f", entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n");
  }

  for( unsigned int idir=0; idir<vdirnameLow325.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameLow325[idir].Data());

    vector<double> entry=vEntriesDiffHist( vfLow325, vdirnameLow325[idir], vhname, vbinrangeHig, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf(outputhadtau, " & %.2f",entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n");
  }

  for( unsigned int idir=0; idir<vdirnameHig.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameHig[idir].Data() );

    vector<double> entry=vEntriesDiffHist( vfHig, vdirnameHig[idir], vhname, vbinrangeHig, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf(outputhadtau, " & %.2f", entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n");
  }

  fprintf(outputhadtau, "\\hline \n");
  fprintf(outputhadtau, "\\hline\n");
  fprintf(outputhadtau, "   &  \\multicolumn{5}{c}{0.53 $ < \\alpha_T \\leq $ 0.55}\\\\ \n");
  fprintf(outputhadtau, "HT Bins & Total NO. events& W to e/$\\mu$ & $\\tau_{had}$ & $\\tau$ to e/$\\mu$ & $\\tau_{had}$ matched jet\\\\ \n");
  fprintf(outputhadtau, "\\hline\n");
  for( unsigned int idir=2; idir<vdirnameHig.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameHig[idir].Data());

    vector<double> entry=vEntriesDiffHist( vfHig, vdirnameHig[idir], vhname, vbinrangeLow325, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf(outputhadtau, " & %.2f", entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n");
  }

  fprintf(outputhadtau, "\\hline \n");
  fprintf(outputhadtau, "\\hline \n");
  fprintf(outputhadtau, "   &  \\multicolumn{5}{c}{0.52 $ < \\alpha_T \\leq $ 0.53}\\\\ \n");
  fprintf(outputhadtau, "HT Bins & Total NO. events& W to e/$\\mu$ & $\\tau_{had}$ & $\\tau$ to e/$\\mu$ & $\\tau_{had}$ matched jet\\\\ \n");
  fprintf(outputhadtau, "\\hline \n");
  for( unsigned int idir=4; idir<vdirnameHig.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameHig[idir].Data());

    vector<double> entry=vEntriesDiffHist( vfHig, vdirnameHig[idir], vhname, vbinrangeLow275, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf(outputhadtau, " & %.2f", entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n ");
  }



  fprintf(outputhadtau, "\\hline \n");
  fprintf(outputhadtau, " \\end{tabular}\n");
  fprintf(outputhadtau, "\\label{tab:bg-compositions-singlemusele}\n");
  fprintf(outputhadtau, " \\end{table}\n\n\n\n");

  fprintf(outputhadtau,"\\end{document}\n\n\n");

  fclose(outputhadtau);

}


void getSignalResults( TString outputfilename, TString Signalname ){
  TString dir="/Users/zmeng/Work_CMS/SUSY/myppt/BGEstimation_16022012/rootfiles/oneMuonSele";
  vector<TFile *> vfLow275;
  TFile *low275_1=new TFile(dir+"/"+"NoSmear"+Signalname+"_PUS0LowHTBinsMuonHTATTrig275.root");
  vfLow275.push_back(low275_1);
  vector<TFile *> vfLow325;
  TFile *low325_1=new TFile(dir+"/"+"NoSmear"+Signalname+"_PUS0LowHTBinsMuonHTATTrig325.root");
  vfLow325.push_back(low325_1);
  vector<TFile *> vfHig;
  TFile *hig_1=new TFile(dir+"/"+"NoSmear"+Signalname+"_PUS0HigHTBinsMuonHTATTrig.root");
  vfHig.push_back(hig_1);

  vector<int> vbinrangeLow275;
  vbinrangeLow275.push_back(53);
  vbinrangeLow275.push_back(53);
  vector<int> vbinrangeLow325;
  vbinrangeLow325.push_back(54);
  vbinrangeLow325.push_back(55);
  vector<int> vbinrangeHig;
  vbinrangeHig.push_back(56);
  vbinrangeHig.push_back(10000000);

  vector<TString> vhname;
  vhname.push_back("AlphaT_CommJetgeq2_h_all");
  vhname.push_back("AlphaT_CommJetgeq2_hasTrueVLep_h_all");
  vhname.push_back("AlphaT_CommJetgeq2_hasTrueTauHad_h_all");
  vhname.push_back("AlphaT_CommJetgeq2_hasTrueTauLep_h_all");
  vhname.push_back("AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_all");

  vector<TString> vdirnameLow275;
  vdirnameLow275.push_back("OneMuon_275_325");
  vector<TString> vdirnameLow325;
  vdirnameLow325.push_back("OneMuon_325_375");
  vector<TString> vdirnameHig;
  vdirnameHig.push_back("OneMuon_375_475");
  vdirnameHig.push_back("OneMuon_475_575");
  vdirnameHig.push_back("OneMuon_575_675");
  vdirnameHig.push_back("OneMuon_675_775");
  vdirnameHig.push_back("OneMuon_775_875");
  vdirnameHig.push_back("OneMuon_875");

  vector<TString> vHTnameLow275;
  vHTnameLow275.push_back("275--325");
  vector<TString> vHTnameLow325;
  vHTnameLow325.push_back("325--375");
  vector<TString> vHTnameHig;
  vHTnameHig.push_back("375--475");
  vHTnameHig.push_back("475--575");
  vHTnameHig.push_back("575--675");
  vHTnameHig.push_back("675--775");
  vHTnameHig.push_back("775--875");
  vHTnameHig.push_back("875--$\\infty$");

  double scale = 1.;

  //  std::ofstream outputhadtau;
  FILE * outputhadtau;
  outputhadtau = fopen (outputfilename,"w");

  fprintf(outputhadtau, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputhadtau, "\\begin{document} \n");

  fprintf(outputhadtau, "\\begin{table}[ht] \n");

  fprintf(outputhadtau, "\\caption{Event type compositons of single muon selection in signal MC samples}\n");
  fprintf(outputhadtau, "\\centering\n");
  fprintf(outputhadtau, " \\begin{tabular}{ c|ccccc }\n");

  fprintf(outputhadtau, "\\hline\n");
  fprintf(outputhadtau, "   &  \\multicolumn{5}{c}{$\\alpha_T > $ 0.55}\\\\ \n ");
  fprintf(outputhadtau, "HT Bins & Total NO. events& W to e/$\\mu$ & $\\tau_{had}$ & $\\tau$ to e/$\\mu$ & $\\tau_{had}$ matched jet\\\\ \n");
  fprintf(outputhadtau, "\\hline\n");

  for( unsigned int idir=0; idir<vdirnameLow275.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameLow275[idir].Data());

    vector<double> entry=vEntriesDiffHist( vfLow275, vdirnameLow275[idir], vhname, vbinrangeHig, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf (outputhadtau, " & %.2f", entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n");
  }

  for( unsigned int idir=0; idir<vdirnameLow325.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameLow325[idir].Data());

    vector<double> entry=vEntriesDiffHist( vfLow325, vdirnameLow325[idir], vhname, vbinrangeHig, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf(outputhadtau, " & %.2f",entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n");
  }

  for( unsigned int idir=0; idir<vdirnameHig.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameHig[idir].Data() );

    vector<double> entry=vEntriesDiffHist( vfHig, vdirnameHig[idir], vhname, vbinrangeHig, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf(outputhadtau, " & %.2f", entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n");
  }

  fprintf(outputhadtau, "\\hline \n");
  fprintf(outputhadtau, "\\hline\n");
  fprintf(outputhadtau, "   &  \\multicolumn{5}{c}{0.53 $ < \\alpha_T \\leq $ 0.55}\\\\ \n");
  fprintf(outputhadtau, "HT Bins & Total NO. events& W to e/$\\mu$ & $\\tau_{had}$ & $\\tau$ to e/$\\mu$ & $\\tau_{had}$ matched jet\\\\ \n");
  fprintf(outputhadtau, "\\hline\n");
  for( unsigned int idir=2; idir<vdirnameHig.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameHig[idir].Data());

    vector<double> entry=vEntriesDiffHist( vfHig, vdirnameHig[idir], vhname, vbinrangeLow325, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf(outputhadtau, " & %.2f", entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n");
  }

  fprintf(outputhadtau, "\\hline \n");
  fprintf(outputhadtau, "\\hline \n");
  fprintf(outputhadtau, "   &  \\multicolumn{5}{c}{0.52 $ < \\alpha_T \\leq $ 0.53}\\\\ \n");
  fprintf(outputhadtau, "HT Bins & Total NO. events& W to e/$\\mu$ & $\\tau_{had}$ & $\\tau$ to e/$\\mu$ & $\\tau_{had}$ matched jet\\\\ \n");
  fprintf(outputhadtau, "\\hline \n");
  for( unsigned int idir=4; idir<vdirnameHig.size(); idir++ ){

    fprintf(outputhadtau, "%s", vHTnameHig[idir].Data());

    vector<double> entry=vEntriesDiffHist( vfHig, vdirnameHig[idir], vhname, vbinrangeLow275, scale );
    for(unsigned int i=0; i < entry.size(); i++){
      if( i==0 ) fprintf(outputhadtau, " & %.1f", entry[i]);
      else {
	fprintf(outputhadtau, " & %.2f", entry[i]/entry[0]);
      }
    }
    fprintf(outputhadtau, " \\\\ \n ");
  }



  fprintf(outputhadtau, "\\hline \n");
  fprintf(outputhadtau, " \\end{tabular}\n");
  fprintf(outputhadtau, "\\label{tab:bg-compositions-singlemusele}\n");
  fprintf(outputhadtau, " \\end{table}\n\n\n\n");

  fprintf(outputhadtau,"\\end{document}\n\n\n");

  fclose(outputhadtau);

}


