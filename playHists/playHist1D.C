#include "playHist1D.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TLine.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "TCanvas.h"

#include "TStyle.h"

//#include "AtlasStyle.C"
#include "tdrstyle.h"

using namespace std;

playHist1D::playHist1D():
  linewidth(2),
  markersize(2)
{}

// -----------------------------------------------------------------------------
//
TH1D* playHist1D::getHist1D( TFile *f, TString dirname, TString hname){
  TDirectory *TDir = (TDirectory*)( f->Get( dirname ) );
  if( TDir ){
    TH1D* inh= (TH1D*)( TDir->Get( hname ) );
    return inh;
  } else return 0;
}

// -----------------------------------------------------------------------------
//
vector<unsigned int> playHist1D::getifileidir1D( vector<TFile*> vf, vector<TString> vdirname, TString hname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      if( getHist1D(vf[i], vdirname[j], hname) ){
	vector<unsigned int> rei;
	rei.push_back(i);
	rei.push_back(j);
	return rei;
      }
    }
  }
}

TH1D* playHist1D::getHistInvFandvDir1D( vector<TFile*> vf, vector<TString> vdirname, TString hname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      if( getHist1D(vf[i], vdirname[j], hname) ){
	TH1D* h=(TH1D*)(getHist1D( vf[i], vdirname[j], hname )->Clone("h"));
	return h;
      }
    }
  }
}

TH1D* playHist1D::addHistForDiffFoldersAndFiles1D(vector<TFile*> vf, vector<TString> vdirname, TString hname){

  TH1D* h=(TH1D*)(getHistInvFandvDir1D( vf, vdirname, hname)->Clone("h"));
  vector<unsigned int> ifileidir_ini=getifileidir1D( vf, vdirname, hname );
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      TH1D* h1=getHist1D(vf[i], vdirname[j], hname);
      if( h1 && h && ( !((ifileidir_ini[0] == i) && ( ifileidir_ini[1] == j)) ) ){
	h->Add(h,h1);
      }
    }
  }

  return h;
}

// -----------------------------------------------------------------------------
//
vector<unsigned int> playHist1D::getifileidirih1D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      for( unsigned int k=0; k<vhname.size(); k++ ){
	if( getHist1D(vf[i], vdirname[j], vhname[k]) ){
	  vector<unsigned int> rei;
	  rei.push_back(i);
	  rei.push_back(j);
	  rei.push_back(k);
	  return rei;
	}
      }
    }
  }
}

TH1D* playHist1D::getHistInvFvDirvH1D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      for( unsigned int k=0; k<vhname.size(); k++ ){
	if( getHist1D(vf[i], vdirname[j], vhname[k]) ){
	  TH1D* h=(TH1D*)(getHist1D( vf[i], vdirname[j], vhname[k] )->Clone("h"));
	  return h;
	}
      }
    }
  }
}

TH1D* playHist1D::addHistForDiffFoldersFilesHists1D(vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname){

  TH1D* h=(TH1D*)(getHistInvFvDirvH1D( vf, vdirname, vhname)->Clone("h"));
  vector<unsigned int> ifileidirih_ini=getifileidirih1D( vf, vdirname, vhname );
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      for( unsigned int k=0; k<vhname.size(); k++ ){
	TH1D* h1=getHist1D(vf[i], vdirname[j], vhname[k]);
	if( h1 && h && ( !( ( ifileidirih_ini[0] == i ) && ( ifileidirih_ini[1] == j ) && ( ifileidirih_ini[2] == k ) ) ) ){
	  h->Add(h,h1);
	}
      }
    }
  }
  return h;
}

// -----------------------------------------------------------------------------
//
TH1D* playHist1D::formatHist( TH1D* inh, double inscale, TString titlex, TString titley, double xlow, double xhigh, int rebin ){
  tdrstyle tdr=tdrstyle();
  tdr.setTDRStyle("g");

  TH1D* h=(TH1D*)(inh->Clone("h"));
  if(rebin > 1){
    h->Rebin(rebin);
  }
  h->GetXaxis()->SetRangeUser(xlow, xhigh);
  h->GetYaxis()->SetTitle(titley);
  h->GetXaxis()->SetTitle(titlex);
  h->SetLineWidth(linewidth);
  h->SetMarkerSize(markersize);
  if( inscale == 0. ){
    h->Scale(1.0/(h->Integral(1,100000)));
  } else {
    h->Scale(inscale);
  }

  return h;
}

TH1D* playHist1D::MaxHist( vector<TH1D*> vinh){
  double max=-1E30;
  int index=-1;
  for(unsigned int i=0; i< vinh.size(); i++){
    if( vinh[i]->GetMaximum() > max ){
      max= vinh[i]->GetMaximum();
      index=(int)(i);
    }
  }

  TH1D* h=(TH1D*)(vinh[index]->Clone("h"));

  return h;
}

int playHist1D::MaxHist_index( vector<TH1D*> vinh){
  double max=-1E30;
  int index=-1;
  for(unsigned int i=0; i< vinh.size(); i++){
    if( vinh[i]->GetMaximum() > max ){
      max= vinh[i]->GetMaximum();
      index=(int)(i);
    }
  }

  return index;
}
