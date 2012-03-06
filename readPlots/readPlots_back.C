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

  return inh;
}

TH1D* getHists( TFile *f, TString folders, TString hname ) {

  TDirectory *TDir = (TDirectory*)( f->Get( folders ) );

  TH1D* inh= (TH1D*)( TDir->Get( hname ) );

  return inh;
}



double getEntries( TH1D* inh, double scale) {

  double entries=0;

  entries = inh->Integral(1,10000);

  return entries*scale;
}

double getEntries( std::vector<TH1D*> inh, double scale) {

  double entries=0;

  for( unsigned int i=0; i<inh.size(); i++ ){

    entries = entries + (inh[i])->Integral(1,10000);
  }

  return entries*scale;
}


double getResults( TString filename, TString folder, TString hname, double scale ) {
  TFile *f=new TFile( filename );

  TH1D* inh = getHists( f, folder, hname);

  return getEntries( inh, scale );
}


double getResults( TString filename, std::vector<TString> folders, TString hname, double scale ){
  TFile *f=new TFile( filename );

  vector<TH1D*> inh = getHists( f, folders, hname );

  return getEntries( inh, scale );
}



double CompositionSumOfDiffSamples( TString hnames, vector<TString> filenames, TString folder, double scale ){

  double totalentries=0;

  for(unsigned int ifile=0; ifile <filenames.size(); ifile++ ){
    double entries = getResults( filenames[ifile], folder, hnames ,scale);
    totalentries = totalentries + entries;
  }

  return totalentries;
}


vector<double> CompositionsInDiffSamples(vector<TString> hnames, TString filename, TString folder, double scale){
  vector<double> hao;
  for(unsigned int i=0; i <hnames.size(); i++ ){
    double entries = getResults( filename, folder, hnames[i], scale);
    hao.push_back(entries);
  }
  return entries;
}

vector<TString>  hname_pushback(){
  vector<TString> hname;
  hname.push_back("totalEvents_HadATg055_h_1");
  hname.push_back("hasTrueVLep_HadATg055_h_1");
  hname.push_back("hasTrueTauHad_HadATg055_h_1");
  hname.push_back("hasTrueTauLep_HadATg055_h_1");
  hname.push_back("hasTrueTauHadMatchedToCommonJet_HadATg055_h_1");

  return hname;
}


vector<TString> filename_pushback(TString Bins, bool highbinsStudy, TString dir){
  vector<TString> filename;

  if(highbinsStudy){
  filename.push_back( dir+"/"+"NoSmearZinv_PUS4HigHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearWJ_PUS4HigHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearTT_PUS4HigHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearSingleT_PUS4HigHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearDiBoson_PUS6HigHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearDiMuon_PUS4HigHTBinsHadSele"+Bins+".root");
  } else {
  filename.push_back( dir+"/"+"NoSmearZinv_PUS4LowHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearWJ_PUS4LowHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearTT_PUS4LowHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearSingleT_PUS4LowHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearDiBoson_PUS6LowHTBinsHadSele"+Bins+".root");
  filename.push_back( dir+"/"+"NoSmearDiMuon_PUS4LowHTBinsHadSele"+Bins+".root");
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
    foldernames.push_back("875--$\infty$");
  } else {
    foldernames.push_back( Bins+"--"+Bins_end );
  }
  return foldernames;
}

vector<TString> samplenames_pushback(){
  vector<TString> samplenames;

  samplename.push_back("$Z(\rightarrow\nu\nu)+Jets$");
  samplename.push_back("$W+Jets$");
  samplename.push_back("$t\bar{t}$");
  samplename.push_back("$Single Top$");
  samplename.push_back("$WW/ZZ/WZ$");
  samplename.push_back("$Drell-Yan$");

}




void getResults_all( TString outputfilename, TString Bins, TString Bins_end, bool highbinsStudy ){

  vector<TString> hname=hname_pushback();

  TString dir="/Users/zmeng/Work_CMS/SUSY/myppt/BGCompositions_20012012/rootfiles/hadronicSele";
  vector<TString> filename_Low275=filename_pushback("275", false, dir);
  vector<TString> filename_Low325=filename_pushback("325", false, dir);
  vector<TString> filename_High=filename_pushback("", true, dir);

  vector<TString> folders_Low275=folders_pushback("275", "325", false);
  vector<TString> folders_Low325=folders_pushback("325", "375", false);
  vector<TString> folders_High=folders_pushback("", "", true);

  vector<TString> foldernames_Low275=foldernames_pushback("275", "325", false);
  vector<TString> foldernames_Low325=foldernames_pushback("325", "375", false);
  vector<TString> foldernames_High=foldernames_pushback("", "", true);


  vector<TString> samplenames=samplenames_pushback();

  double scale=4.65*1000./100.;


  //Hadronic selection



  std::ofstream outputhadtau;
  outputhadtau.open( outputfilename );


  outputhadtau<< "HT Bins& & &"<< samplename[0] << "&&"  <<endl;

  for( unsigned int ifolder=0; ifolder < folders.size(); ifolder++ ){
    outputhadtau<<"HTBins &"<< 
  }



  for( unsigned int ifolder=0; ifolder < folders.size(); ifolder++ ){

    outputhadtau<<"Bin "<<folders[ifolder]<<" ::::::::::::::::::::::::::::: "<< endl;

    vector<double> histv;
    double totalentries=0;
    double totalentries_VLep=0;
    double totalentries_TauHad=0;
    double totalentries_TauLep=0;
    double totalentries_TauHadMatch=0;
    for ( unsigned int ihist=0; ihist < hname.size(); ihist++) {
      if ( ihist == hname.size() - 1) continue;
      for(unsigned int ifile=0; ifile <filename.size(); ifile++ ){
	if ( ifile == 3 ) continue;
	double entries = getResults( filename[ifile], folders[ifolder], hname[ihist] ,scale);
	if( ihist == 0){
	  totalentries = totalentries + entries;
	}
	if( ihist == 1){

	  totalentries_VLep = totalentries_VLep + entries;
	}
	if( ihist == 2){

	  totalentries_TauHad = totalentries_TauHad + entries;
	}
	if( ihist == 3){

	  totalentries_TauLep = totalentries_TauLep + entries;
	}
      }

    }
    for ( unsigned int ihist=0; ihist < hname.size(); ihist++) {
      for(unsigned int ifile=0; ifile <filename.size(); ifile++ ){
	if ( ifile == 3 ) continue;
	if( ihist == 4){
	double entries = getResults( filename[ifile], folders[ifolder], hname[ihist] ,scale);
	  totalentries_TauHadMatch = totalentries_TauHadMatch + entries;
	}
      }
    }

      histv.push_back(totalentries);
      histv.push_back(totalentries_VLep);
      histv.push_back(totalentries_TauHad);
      histv.push_back(totalentries_TauLep);
      histv.push_back(totalentries_TauHadMatch);
    for ( unsigned int ihist=0; ihist < hname.size(); ihist++) {
      outputhadtau<<hname[ihist]<<": ratio(%) : "<< histv[ihist]/histv[0]*100.<<endl;
    }
  }




  for( unsigned int ifolder=0; ifolder < folders.size(); ifolder++ ){

    outputhadtau<<"Bin "<<folders[ifolder]<<" ::::: Include Z->invisible ******* "<< endl;

    vector<double> histv;
    double totalentries=0;
    double totalentries_VLep=0;
    double totalentries_TauHad=0;
    double totalentries_TauLep=0;
    double totalentries_TauHadMatch=0;
    for ( unsigned int ihist=0; ihist < hname.size(); ihist++) {
      if ( ihist == hname.size() - 1) continue;
      for(unsigned int ifile=0; ifile <filename.size(); ifile++ ){
	double entries = getResults( filename[ifile], folders[ifolder], hname[ihist] ,scale);
	if( ihist == 0){
	  totalentries = totalentries + entries;
	}
	if( ihist == 1){

	  totalentries_VLep = totalentries_VLep + entries;
	}
	if( ihist == 2){

	  totalentries_TauHad = totalentries_TauHad + entries;
	}
	if( ihist == 3){

	  totalentries_TauLep = totalentries_TauLep + entries;
	}
      }

    }
    for ( unsigned int ihist=0; ihist < hname.size(); ihist++) {
      for(unsigned int ifile=0; ifile <filename.size(); ifile++ ){
	if( ihist == 4){
	double entries = getResults( filename[ifile], folders[ifolder], hname[ihist] ,scale);
	  totalentries_TauHadMatch = totalentries_TauHadMatch + entries;
	}
      }
    }

      histv.push_back(totalentries);
      histv.push_back(totalentries_VLep);
      histv.push_back(totalentries_TauHad);
      histv.push_back(totalentries_TauLep);
      histv.push_back(totalentries_TauHadMatch);
    for ( unsigned int ihist=0; ihist < hname.size(); ihist++) {
      outputhadtau<<hname[ihist]<<": ratio(%) : "<< histv[ihist]/histv[0]*100.<<endl;
    }
  }



  for( unsigned int ifile=0; ifile <filename.size(); ifile++ ){
    outputhadtau<<filename[ifile]<<":::::::::::"<<endl;
    for(unsigned int ihist=0; ihist < hname.size(); ihist++ ){
      double entries=getResults( filename[ifile], folders, hname[ihist], scale );
      outputhadtau<<hname[ihist]<<" : "<<entries<<endl;
    }
  }



  for( unsigned int ifile=0; ifile <filename.size(); ifile++ ){
    outputhadtau<<filename[ifile]<<":::::::::::"<<endl;

    for(unsigned int ihist=0; ihist < hname.size(); ihist++ ){
      outputhadtau<<hname[ihist]<<":::::::::::::::::::::::"<<endl;
      for(unsigned int ifolder=0; ifolder < folders.size(); ifolder++ ){
	double entries=getResults( filename[ifile], folders[ifolder], hname[ihist] ,scale);
	outputhadtau<<"Bin "<<folders[ifolder]<<" : "<<entries<<endl;
      }
    }
  }


}



