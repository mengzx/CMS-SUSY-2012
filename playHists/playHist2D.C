#include "playHist2D.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TH1.h"
#include "TH2D.h"
#include "TLine.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "TCanvas.h"
#include "math.h"
#include "TMath.h"
#include "TStyle.h"

//#include "AtlasStyle.C"
#include "tdrstyle.h"

using namespace std;

playHist2D::playHist2D()
{}

// -----------------------------------------------------------------------------
//
TH2D* playHist2D::getHist2D( TFile *f, TString dirname, TString hname){
  //  TH1::AddDirectory(kFALSE);
  TDirectory *TDir = (TDirectory*)( f->Get( dirname ) );
  if( TDir ){
    TH2D* hh= (TH2D*)( TDir->Get( hname ) );
    //    TH2D *reh=cloneHist2D(hh);
    //    hh->SetDirectory(0);
    //    f->Close();
    return hh;
  } else { return 0; }
}

TH2D* playHist2D::cloneHist2D( TH2D *hh ){
  TH2D *inh=new TH2D( ( hh->GetName() ), ( hh->GetTitle() ), hh->GetNbinsX(), hh->GetXaxis()->GetBinLowEdge(1), hh->GetXaxis()->GetBinLowEdge(hh->GetNbinsX()+1), hh->GetNbinsY(), hh->GetYaxis()->GetBinLowEdge(1), hh->GetYaxis()->GetBinLowEdge(hh->GetNbinsY()+1) );
  inh->Sumw2();
  for( int i=1; i<= inh->GetNbinsX(); i++ ){
    for( int j=1; j<= inh->GetNbinsY(); j++ ){
      inh->SetBinContent(i,j, hh->GetBinContent(i,j));
      inh->SetBinError(i,j, hh->GetBinError(i,j));
    }
  }
  return inh;
}
// -----------------------------------------------------------------------------
//
vector<unsigned int> playHist2D::getifileidir2D( vector<TFile*> vf, vector<TString> vdirname, TString hname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      if( getHist2D(vf[i], vdirname[j], hname) ){
	vector<unsigned int> rei;
	rei.push_back(i);
	rei.push_back(j);
	return rei;
      }
    }
  }
}

TH2D* playHist2D::getHistInvFandvDir2D( vector<TFile*> vf, vector<TString> vdirname, TString hname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      if( getHist2D(vf[i], vdirname[j], hname) ){
	TH2D* h=(TH2D*)(getHist2D( vf[i], vdirname[j], hname )->Clone("h"));
	return h;
      }
    }
  }
}

TH2D* playHist2D::addHistForDiffFoldersAndFiles2D(vector<TFile*> vf, vector<TString> vdirname, TString hname){

  TH2D* h=(TH2D*)(getHistInvFandvDir2D( vf, vdirname, hname)->Clone("h"));
  vector<unsigned int> ifileidir_ini=getifileidir2D( vf, vdirname, hname );
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      TH2D* h1=getHist2D(vf[i], vdirname[j], hname);
      if( h1 && h && ( !((ifileidir_ini[0] == i) && ( ifileidir_ini[1] == j)) ) ){
	h->Add(h,h1);
      }
    }
  }

  return h;
}



// -----------------------------------------------------------------------------
//
vector<unsigned int> playHist2D::getifileidirih2D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      for( unsigned int k=0; k<vhname.size(); k++ ){
	if( getHist2D(vf[i], vdirname[j], vhname[k]) ){
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


// -----------------------------------------------------------------------------
//
TH2D* playHist2D::getHistInvFvDirvH2D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      for( unsigned int k=0; k<vhname.size(); k++ ){
	if( getHist2D(vf[i], vdirname[j], vhname[k]) ){
	  TH2D* h=(TH2D*)(getHist2D( vf[i], vdirname[j], vhname[k] )->Clone("h"));
	  return h;
	}
      }
    }
  }
}


TH2D* playHist2D::addHistForDiffFoldersFilesHists2D(vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname, vector<double> trigeff){

  TH2D* h=(TH2D*)(getHistInvFvDirvH2D( vf, vdirname, vhname)->Clone("h"));
  vector<unsigned int> ifileidirih_ini=getifileidirih2D( vf, vdirname, vhname );
  h->Scale(trigeff[ ifileidirih_ini[1] ]);
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      for( unsigned int k=0; k<vhname.size(); k++ ){
	TH2D* h1=getHist2D(vf[i], vdirname[j], vhname[k]);
	if( h1 && h && ( !( ( ifileidirih_ini[0] == i ) && ( ifileidirih_ini[1] == j ) && ( ifileidirih_ini[2] == k ) ) ) ){
	  h1->Scale(trigeff[j]);
	  h->Add(h,h1);
	}
      }
    }
  }
  return h;
}


// -----------------------------------------------------------------------------
//
TH2D* playHist2D::addHistForDiffFoldersAndFiles_SubtrackHists2D(vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname_first, vector<TString> vhname_second, vector<double> trigeff ){

  TH2D* h_first=(TH2D*)(addHistForDiffFoldersFilesHists2D( vf, vdirname, vhname_first, trigeff )->Clone("h_first") );
  TH2D* h_second=(TH2D*)(addHistForDiffFoldersFilesHists2D( vf, vdirname, vhname_second, trigeff )->Clone("h_second") );
  TH2D* h=(TH2D*)(h_first->Clone("h"));
  TH2D* h1=(TH2D*)(h_second->Clone("h1"));
  h1->Scale(-1.);
  h->Add(h,h1);
  return h;
}

// -----------------------------------------------------------------------------
//
TH2D* playHist2D::ReFillHist_AlphaTVSHT(TH2D* inh ){
  int nxbins=12;
  int nybins=8;

  TH2D* h=(TH2D*)(inh->Clone("h"));
  for( int ih=1; ih<nxbins+1; ih++){
    double iaih=inh->Integral(ih, ih, 1, 8);
    h->SetBinContent(ih, 8, iaih);
    double err2=0;
    for(int j=1; j<nybins+1; j++){
      err2=err2+( h->GetBinError( ih, j ) )*(h->GetBinError( ih, j ));
    }
    h->SetBinError(ih, 8, sqrt(err2) );
  }

  return h;
}



// -----------------------------------------------------------------------------
//
TH2D* playHist2D::formatHist(TH2D* inh, double inscale, TString digit){
  tdrstyle tdr=tdrstyle();
  tdr.setTDRStyle( digit );

  TH2D* h=(TH2D*)(inh->Clone("h"));
  h->GetYaxis()->SetRangeUser(0.5,0.56);
  h->GetXaxis()->SetRangeUser(275,975);
  h->GetYaxis()->SetTitle("#alpha_{T}");
  h->GetXaxis()->SetTitle("HT (GeV)");
  h->Scale(inscale);

  return h;
}

// -----------------------------------------------------------------------------
//
vector<TLine*> playHist2D::Lines(){
  TLine *l1=new TLine(275., 0.55, 575., 0.55);
  TLine *l2=new TLine(575., 0.53, 775., 0.53);
  TLine *l3=new TLine(775., 0.52, 975., 0.52);
  TLine *l4=new TLine(575., 0.53, 575., 0.55);
  TLine *l5=new TLine(775., 0.52, 775., 0.53);

  l1->SetLineWidth(3);
  l2->SetLineWidth(3);
  l3->SetLineWidth(3);
  l4->SetLineWidth(3);
  l5->SetLineWidth(3);

  vector<TLine*> lines;
  lines.push_back(l1);
  lines.push_back(l2);
  lines.push_back(l3);
  lines.push_back(l4);
  lines.push_back(l5);

  return lines;
}


