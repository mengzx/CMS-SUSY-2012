#include "project2DHists.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "TCanvas.h"

#include "TStyle.h"

//#include "AtlasStyle.C"
#include "tdrstyle.h"

using namespace std;

project2DHists::project2DHists()
{}

TH1D* project2DHists::projectX( TH2D* inh, double reqlowe, double requpe ){

  TH1D* re1dh=(TH1D*)( ( inh->ProjectionY() ) -> Clone("re1dh") );
  int nbiny=inh->GetNbinsY();
  for( int iy=1; iy<= nbiny; iy++ ){
    re1dh->SetBinContent( iy, 0. );
  }
  re1dh->SetEntries(0);

  int nbinx=inh->GetNbinsX();
  int lowbin=-1;
  int upbin=-1;
  for( int ix=1; ix<=nbinx; ix++){
    int low=(int)( ( inh->GetXaxis()->GetBinLowEdge( ix ) ) * 100000. );
    int up=(int)( ( inh->GetXaxis()->GetBinUpEdge( ix ) ) * 100000. );
    if( low == (int)( reqlowe * 100000. ) ){
      lowbin = ix;
    }
    if( up == (int)( requpe * 100000. ) ){
      upbin = ix;
    }
  }

  for( int i=lowbin; i<=upbin; i++){
    for( int j=1; j<=nbiny; j++ ){
      double con=inh->GetBinContent(i,j);
      re1dh->Fill(con);
    }
  }

  return re1dh;
}


TH1D* project2DHists::projectY( TH2D* inh, double reqlowe, double requpe ){

  TH1D* re1dh=(TH1D*)( ( inh->ProjectionX() ) -> Clone("re1dh") );
  int nbinx=inh->GetNbinsX();
  for( int ix=1; ix<= nbinx; ix++ ){
    re1dh->SetBinContent( ix, 0. );
  }
  re1dh->SetEntries(0);

  int nbiny=inh->GetNbinsY();
  int lowbin=-1;
  int upbin=-1;
  for( int iy=1; iy<=nbiny; iy++){
    int low=(int)( ( inh->GetYaxis()->GetBinLowEdge( iy ) ) * 100000. );
    int up=(int)( ( inh->GetYaxis()->GetBinUpEdge( iy ) ) * 100000. );
    if( low == (int)( reqlowe * 100000. ) ){
      lowbin = iy;
    }
    if( up == (int)( requpe * 100000. ) ){
      upbin = iy;
    }
  }

  for( int i=lowbin; i<=upbin; i++){
    for( int j=1; j<=nbinx; j++ ){
      double con=inh->GetBinContent(j,i);
      re1dh->Fill(con);
    }
  }

  return re1dh;
}


