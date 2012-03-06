#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"

vector<TH1D*> getHists( TFile *f, vector<TString> folders, TString hname ) {
  vector<TH1D*> inh;

  for( unsigned int i=0; i<folders.size(); i++ ){

    TDirectory *TDir = (TDirectory*)( f->Get( folders[i] ) );

    inh.push_back( (TH1D*)( TDir->Get( hname ) ) );
  }
  cout<<"here1"<<endl;
  return inh;
}

TH1D* getHists( TFile *f, TString folders, TString hname ) {

  TDirectory *TDir = (TDirectory*)( f->Get( folders ) );

  TH1D* inh= (TH1D*)( TDir->Get( hname ) );
  cout<<"here2"<<endl;
  return inh;
}



double getEntries( TH1D* inh, double scale) {

  double entries=0;

  entries = inh->Integral(1,100000000);
  cout<<"here3"<<endl;

  return entries*scale;
}

double getEntries( std::vector<TH1D*> inh, double scale) {

  double entries=0;

  for( unsigned int i=0; i<inh.size(); i++ ){

    entries = entries + (inh[i])->Integral(1,1000000000);
  }
  cout<<"here4"<<endl;

  return entries*scale;
}


double getResults( TString filename, TString folder, TString hname, double scale ) {
  TFile *f=new TFile( filename );
  TH1D* inh = getHists( f, folder, hname);
  cout<<"here5"<<endl;
  return getEntries( inh, scale );
}


double getResults( TString filename, std::vector<TString> folders, TString hname, double scale ){
  TFile *f=new TFile( filename );

  vector<TH1D*> inh = getHists( f, folders, hname );
  cout<<"here6"<<endl;

  return getEntries( inh, scale );
}



vector<double> CompositionSumOfDiffSamples( vector<TString> hnames, vector<TString> filenames, TString folder, double scale ){

  vector<double> totalentries;
  for( unsigned int i=0; i <hnames.size(); i++ ){
    double total=0;
    for(unsigned int ifile=0; ifile <filenames.size(); ifile++ ){;
      double entries = getResults( filenames[ifile], folder, hnames[i], scale);
      total = total + entries;
    }
    totalentries.push_back(total);
  }
  return totalentries;
}


vector<double> CompositionsInDiffSamples(vector<TString> hnames, TString filename, TString folder, double scale){
  vector<double> hao;
  for(unsigned int i=0; i <hnames.size(); i++ ){
    double entries = getResults( filename, folder, hnames[i], scale);
    hao.push_back(entries);
  }
  return hao;
}

vector<TString>  hname_pushback( TString AlhaTBin, bool weight){
  vector<TString> hname;
  if( weight ){
    hname.push_back("totalEvents_HadAT"+AlhaTBin+"_h_1");
    hname.push_back("hasTrueVLep_HadAT"+AlhaTBin+"_h_1");
    hname.push_back("hasTrueTauHad_HadAT"+AlhaTBin+"_h_1");
    hname.push_back("hasTrueTauLep_HadAT"+AlhaTBin+"_h_1");
    hname.push_back("hasTrueTauHadMatchedToCommonJet_HadAT"+AlhaTBin+"_h_1");
  } else {
    hname.push_back("totalEvents_HadAT"+AlhaTBin+"_h_all");
    hname.push_back("hasTrueVLep_HadAT"+AlhaTBin+"_h_all");
    hname.push_back("hasTrueTauHad_HadAT"+AlhaTBin+"_h_all");
    hname.push_back("hasTrueTauLep_HadAT"+AlhaTBin+"_h_all");
    hname.push_back("hasTrueTauHadMatchedToCommonJet_HadAT"+AlhaTBin+"_h_all");
  }
  return hname;
}

vector<double>  AlphaTCut_pushback( TString AlhaTBin){
  vector<double> hname;
  if( AlhaTBin.CompareTo("g055") == 0 ){
    hname.push_back(0.55);
    hname.push_back(1E30);
  }
  if( AlhaTBin.CompareTo("052To053") == 0 ){
    hname.push_back(0.52);
    hname.push_back(0.53);
  }
  if( AlhaTBin.CompareTo("053To055") == 0 ){
    hname.push_back(0.53);
    hname.push_back(0.55);
  }
  return hname;
}


vector<TString> filename_pushback(TString Bins, bool highbinsStudy, TString dir, int singalorBGorAll){
  vector<TString> filename;

  if(highbinsStudy){
    if( singalorBGorAll == 0){
      filename.push_back( dir+"/"+"NoSmearZinv_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearWJ_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTT_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearSingleT_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearDiBoson_PUS6HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearDiMuon_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTanB10_1800_280_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTanB10_320_520_PUS4HigHTBinsHadSele"+Bins+".root");
    }
    if( singalorBGorAll == 1){
      filename.push_back( dir+"/"+"NoSmearTanB10_1800_280_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTanB10_320_520_PUS4HigHTBinsHadSele"+Bins+".root");
    }
    if( singalorBGorAll == 2){
      filename.push_back( dir+"/"+"NoSmearZinv_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearWJ_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTT_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearSingleT_PUS4HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearDiBoson_PUS6HigHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearDiMuon_PUS4HigHTBinsHadSele"+Bins+".root");
    }
  } else {
    if( singalorBGorAll == 0){
      filename.push_back( dir+"/"+"NoSmearZinv_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearWJ_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTT_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearSingleT_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearDiBoson_PUS6LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearDiMuon_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTanB10_1800_280_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTanB10_320_520_PUS4LowHTBinsHadSele"+Bins+".root");
    }
    if( singalorBGorAll == 1){
      filename.push_back( dir+"/"+"NoSmearTanB10_1800_280_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTanB10_320_520_PUS4LowHTBinsHadSele"+Bins+".root");
    }

    if( singalorBGorAll == 2){
      filename.push_back( dir+"/"+"NoSmearZinv_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearWJ_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearTT_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearSingleT_PUS4LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearDiBoson_PUS6LowHTBinsHadSele"+Bins+".root");
      filename.push_back( dir+"/"+"NoSmearDiMuon_PUS4LowHTBinsHadSele"+Bins+".root");
    }
  }
  return filename;
}

vector<TString> folders_pushback( TString Bins, TString Bins_end, bool highbinsStudy ){
  vector<TString> folders;
  if(highbinsStudy){
    folders.push_back( "375_475" );
    folders.push_back( "475_575" );
    folders.push_back( "575_675" );
    folders.push_back( "675_775" );
    folders.push_back( "775_875" );
    folders.push_back( "875" );
  } else {
    folders.push_back( Bins+"_"+Bins_end );
  }
  return folders;
}


vector<TString> foldernames_pushback( TString Bins, TString Bins_end, bool highbinsStudy ){
  vector<TString> foldernames;
  if(highbinsStudy){
    foldernames.push_back("375--475");
    foldernames.push_back("475--575");
    foldernames.push_back("575--675");
    foldernames.push_back("675--775");
    foldernames.push_back("775--875");
    foldernames.push_back("875--$\\infty$");
  } else {
    foldernames.push_back( Bins+"--"+Bins_end );
  }
  return foldernames;
}

vector<TString> samplenames_pushback(){
  vector<TString> samplenames;

  samplenames.push_back("$Z(\\rightarrow\\nu\\nu)$ + Jets");
  samplenames.push_back("W + Jets");
  samplenames.push_back("$t\\bar{t}$");
  samplenames.push_back("Single Top");
  samplenames.push_back("WW/ZZ/WZ");
  samplenames.push_back("Drell-Yan");
  samplenames.push_back("Signal TB10 1800-280");
  samplenames.push_back("Signal TB10 320-520");
  return samplenames;
}

void output_textable_sumoverSamples(std::ofstream &outputhadtau, vector<TString> hnames, vector<double> AlphaTCut, vector<TString> filename_Low275, vector<TString> filename_Low325, vector<TString> filename_High, vector<TString> folders_Low275, vector<TString> folders_Low325, vector<TString> folders_High, vector<TString> foldernames_Low275, vector<TString> foldernames_Low325, vector<TString> foldernames_High, double scale){

  outputhadtau<< "\\begin{table}[ht]"<<endl;
  if( AlphaTCut[0] == 0.55 ){
    outputhadtau<< "\\caption{Background compositons of hadronic selection in MC samples, with alphaT cut between "<< AlphaTCut[0] << " and $\\infty$.}" <<endl;
  } else {
    outputhadtau<< "\\caption{Background compositons of hadronic selection in MC samples, with alphaT cut between "<< AlphaTCut[0] << " and "<< AlphaTCut[1]<<" .}" <<endl;
  }

  outputhadtau<< "\\centering"<<endl;
  outputhadtau<<" \\begin{tabular}{ c|ccccc } "<<endl;
  //  outputhadtau<<" \\footnotesize"<<endl;

  outputhadtau<<"\\hline"<<endl;
  outputhadtau<<"HT Bins & Total NO. events& W to e/$\\mu$ & $\\tau_{had}$ & $\\tau$ to e/$\\mu$ & $\\tau_{had}$ matched jet\\\\ "<<endl;
  outputhadtau<<"\\hline"<<endl;

  if( AlphaTCut[0] == 0.55 ){
    for( unsigned int ifolder=0; ifolder < folders_Low275.size(); ifolder++ ){
      vector<double> entry=CompositionSumOfDiffSamples(hnames, filename_Low275, folders_Low275[ifolder], scale);
      outputhadtau<<foldernames_Low275[ifolder];
      for(unsigned int i=0; i < entry.size(); i++){
	outputhadtau<<" & " << entry[i];
      }
      outputhadtau<<" \\\\ " <<endl;
    }

    for( unsigned int ifolder=0; ifolder < folders_Low325.size(); ifolder++ ){
      vector<double> entry=CompositionSumOfDiffSamples(hnames, filename_Low325, folders_Low325[ifolder], scale);
      outputhadtau<<foldernames_Low325[ifolder];
      for(unsigned int i=0; i < entry.size(); i++){
	outputhadtau<<" & " << entry[i];
      }
      outputhadtau<<" \\\\ " <<endl;
    }
  }


  for( unsigned int ifolder=0; ifolder < folders_High.size(); ifolder++ ){

    if( AlphaTCut[0] == 0.52 && ( (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
      outputhadtau<<foldernames_High[ifolder];
    }
    if( AlphaTCut[0] == 0.53 && ((folders_High[ifolder]).CompareTo("575_675") == 0 || (folders_High[ifolder]).CompareTo("675_775") == 0 || (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
      outputhadtau<<foldernames_High[ifolder];
    }
    if( AlphaTCut[0] == 0.55 ){
      outputhadtau<<foldernames_High[ifolder];
    }

    vector<double> entry=CompositionSumOfDiffSamples(hnames, filename_High, folders_High[ifolder], scale);

    for(unsigned int i=0; i < entry.size(); i++){
      if( AlphaTCut[0] == 0.52 && ( (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
	outputhadtau<<" & " << entry[i];
      } else if( AlphaTCut[0] == 0.53 && ((folders_High[ifolder]).CompareTo("575_675") == 0 || (folders_High[ifolder]).CompareTo("675_775") == 0 || (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
	outputhadtau<<" & " << entry[i];
      } else if( AlphaTCut[0] == 0.55 ){
	outputhadtau<<" & " << entry[i];
      }	
    }
    if( AlphaTCut[0] == 0.52 && ( (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
      outputhadtau<<" \\\\ " <<endl;
    }
    if( AlphaTCut[0] == 0.53 && ((folders_High[ifolder]).CompareTo("575_675") == 0 || (folders_High[ifolder]).CompareTo("675_775") == 0 || (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
      outputhadtau<<" \\\\ " <<endl;
    }
    if( AlphaTCut[0] == 0.55 ){
      outputhadtau<<" \\\\ " <<endl;
    }
  }

  outputhadtau<<"\\hline " <<endl;
  outputhadtau<< " \\end{tabular}" <<endl;
  outputhadtau<< "\\label{tab:bg-compositions-WJ}"<<endl;
  outputhadtau<< " \\end{table}" <<endl;
  outputhadtau<< "\n"<<endl;
  outputhadtau<< "\n"<<endl;
  outputhadtau<< "\n"<<endl;


}

void output_textable(unsigned int ifileindex, std::ofstream &outputhadtau, vector<TString> hnames, vector<double> AlphaTCut, vector<TString> filename_Low275, vector<TString> filename_Low325, vector<TString> filename_High, vector<TString> folders_Low275, vector<TString> folders_Low325, vector<TString> folders_High, vector<TString> foldernames_Low275, vector<TString> foldernames_Low325, vector<TString> foldernames_High, vector<TString> samplenames, double scale){

  outputhadtau<< "\\begin{table}[ht]"<<endl;
  if( AlphaTCut[0] == 0.55 ){
    outputhadtau<< "\\caption{Background compositons of hadronic selection in MC samples, with alphaT cut between "<< AlphaTCut[0] << " and $\\infty$.}" <<endl;
  } else {
    outputhadtau<< "\\caption{Background compositons of hadronic selection in MC samples, with alphaT cut between "<< AlphaTCut[0] << " and "<< AlphaTCut[1]<<" .}" <<endl;
  }
  outputhadtau<< "\\centering"<<endl;
  outputhadtau<<" \\begin{tabular}{ c|ccccc } "<<endl;
  //  outputhadtau<<" \\footnotesize"<<endl;

  outputhadtau<<"\\hline"<<endl;
  outputhadtau<<"& & &"<<samplenames[ifileindex]<<" & & \\\\ "<<endl;
  outputhadtau<<"\\hline"<<endl;
  outputhadtau<<"HT Bins & Total NO. events& W to e/$\\mu$ & $\\tau_{had}$ & $\\tau$ to e/$\\mu$ & $\\tau_{had}$ matched jet\\\\ "<<endl;
  outputhadtau<<"\\hline"<<endl;

  if( AlphaTCut[0] == 0.55 ){
    for( unsigned int ifolder=0; ifolder < folders_Low275.size(); ifolder++ ){
      vector<double> entry=CompositionsInDiffSamples(hnames, filename_Low275[ifileindex], folders_Low275[ifolder], scale);
      outputhadtau<<foldernames_Low275[ifolder];
      for(unsigned int i=0; i < entry.size(); i++){
	outputhadtau<<" & " << entry[i];
      }
      outputhadtau<<" \\\\ " <<endl;
    }

    for( unsigned int ifolder=0; ifolder < folders_Low325.size(); ifolder++ ){
      vector<double> entry=CompositionsInDiffSamples(hnames, filename_Low325[ifileindex], folders_Low325[ifolder], scale);
      outputhadtau<<foldernames_Low325[ifolder];
      for(unsigned int i=0; i < entry.size(); i++){
	outputhadtau<<" & " << entry[i];
      }
      outputhadtau<<" \\\\ " <<endl;
    }
  }

  for( unsigned int ifolder=0; ifolder < folders_High.size(); ifolder++ ){

    if( AlphaTCut[0] == 0.52 && ( (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
      outputhadtau<<foldernames_High[ifolder];
    }
    if( AlphaTCut[0] == 0.53 && ((folders_High[ifolder]).CompareTo("575_675") == 0 || (folders_High[ifolder]).CompareTo("675_775") == 0 || (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
      outputhadtau<<foldernames_High[ifolder];
    }
    if( AlphaTCut[0] == 0.55 ){
      outputhadtau<<foldernames_High[ifolder];
    }

    vector<double> entry=CompositionsInDiffSamples(hnames, filename_High[ifileindex], folders_High[ifolder], scale);

    for(unsigned int i=0; i < entry.size(); i++){
      if( AlphaTCut[0] == 0.52 && ( (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
	outputhadtau<<" & " << entry[i];
      } else if( AlphaTCut[0] == 0.53 && ((folders_High[ifolder]).CompareTo("575_675") == 0 || (folders_High[ifolder]).CompareTo("675_775") == 0 || (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
	outputhadtau<<" & " << entry[i];
      } else if( AlphaTCut[0] == 0.55 ){
	outputhadtau<<" & " << entry[i];
      }	
    }
    if( AlphaTCut[0] == 0.52 && ( (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
      outputhadtau<<" \\\\ " <<endl;
    }
    if( AlphaTCut[0] == 0.53 && ((folders_High[ifolder]).CompareTo("575_675") == 0 || (folders_High[ifolder]).CompareTo("675_775") == 0 || (folders_High[ifolder]).CompareTo("775_875") == 0 || (folders_High[ifolder]).CompareTo("875") == 0 ) ){
      outputhadtau<<" \\\\ " <<endl;
    }
    if( AlphaTCut[0] == 0.55 ){
      outputhadtau<<" \\\\ " <<endl;
    }
  }

  outputhadtau<<"\\hline " <<endl;
  outputhadtau<< " \\end{tabular}" <<endl;
  outputhadtau<< "\\label{tab:bg-compositions-WJ}"<<endl;
  outputhadtau<< " \\end{table}" <<endl;
  outputhadtau<< "\n"<<endl;
  outputhadtau<< "\n"<<endl;
  outputhadtau<< "\n"<<endl;

}

void getResults_all( TString outputfilename ){


  //Hadronic selection
  vector<TString> hnamesg055=hname_pushback("g055", true);
  vector<double> AlphaTCutg055=AlphaTCut_pushback("g055");
  vector<TString> hnames052To053=hname_pushback("052To053", true);
  vector<double> AlphaTCut052To053=AlphaTCut_pushback("052To053");
  vector<TString> hnames053To055=hname_pushback("053To055", true);
  vector<double> AlphaTCut053To055=AlphaTCut_pushback("053To055");

  TString dir="/Users/zmeng/Work_CMS/SUSY/myppt/BGCompositions_20012012/rootfiles/hadronicSele/MuonID_vbtfMuonId_cff";
  vector<TString> filename_Low275=filename_pushback("275", false, dir, 0);
  vector<TString> filename_Low325=filename_pushback("325", false, dir, 0);
  vector<TString> filename_High=filename_pushback("", true, dir, 0);

  vector<TString> filename_Low275_BG=filename_pushback("275", false, dir, 2);
  vector<TString> filename_Low325_BG=filename_pushback("325", false, dir, 2);
  vector<TString> filename_High_BG=filename_pushback("", true, dir, 2);

  vector<TString> folders_Low275=folders_pushback("275", "325", false);
  vector<TString> folders_Low325=folders_pushback("325", "375", false);
  vector<TString> folders_High=folders_pushback("", "", true);

  vector<TString> foldernames_Low275=foldernames_pushback("275", "325", false);
  vector<TString> foldernames_Low325=foldernames_pushback("325", "375", false);
  vector<TString> foldernames_High=foldernames_pushback("", "", true);

  vector<TString> samplenames=samplenames_pushback();

  double scale=4.65*1000./100.;
  //  double scale=1.0;




  std::ofstream outputhadtau;
  outputhadtau.open( outputfilename );
  outputhadtau<<"\\documentclass[a4paper,12pt]{article}" <<endl;
  outputhadtau<<"\\begin{document}"<<endl;
  //In different samples

  /*  output_textable_sumoverSamples( outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275_BG, filename_Low325_BG, filename_High_BG, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, scale);
      output_textable_sumoverSamples( outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275_BG, filename_Low325_BG, filename_High_BG, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, scale);
      output_textable_sumoverSamples( outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275_BG, filename_Low325_BG, filename_High_BG, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, scale);
  */
  /*    output_textable( 6, outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
	output_textable( 7, outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
	output_textable( 6, outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
	output_textable( 7, outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
	output_textable( 6, outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
	output_textable( 7, outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  */


  output_textable( 0, outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 1, outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 2, outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 3, outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 4, outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 5, outputhadtau, hnamesg055, AlphaTCutg055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  /*  output_textable( 0, outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 1, outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 2, outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 3, outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 4, outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 5, outputhadtau, hnames053To055, AlphaTCut053To055, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);

 output_textable( 0, outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 1, outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 2, outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 3, outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 4, outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  output_textable( 5, outputhadtau, hnames052To053, AlphaTCut052To053, filename_Low275, filename_Low325, filename_High, folders_Low275, folders_Low325, folders_High, foldernames_Low275, foldernames_Low325, foldernames_High, samplenames, scale);
  */
  outputhadtau<<"\\end{document}"<<endl;
  outputhadtau.close();

}



