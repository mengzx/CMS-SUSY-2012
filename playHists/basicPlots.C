#include "basicPlots.h"
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
#include "TStyle.h"
#include "TLegend.h"

#include "tdrstyle.h"
#include "playHist2D.h"
#include "playHist1D.h"
#include "project2DHists.h"
#include "getTranslationFactor.h"

using namespace std;


basicPlots::basicPlots(){
}

void basicPlots::AlphaT(){
  getTranslationFactor tf=getTranslationFactor();
  project2DHists pf=project2DHists();
  playHist1D hf1d=playHist1D();
  TH2D *controlData=tf.getControlData(true, false, "all" );
  TH2D *controlMC=tf.TranslationFactor(true, false, "all", false)[1];

  TH1D *alphaT_275To375_controlData=pf.projectX(controlData, 275., 375.);
  TH1D *alphaT_275To375_controlMC=pf.projectX(controlMC, 275., 375.);

  TCanvas *c1=new TCanvas();
  TH1D *c1_alphaT_275To375_controlData=hf1d.formatHist( alphaT_275To375_controlData, 0., "#alpha_{T}", "", 0., 10., 1. );
  c1_alphaT_275To375_controlData->Draw();
  TH1D *c1_alphaT_275To375_controlMC=hf1d.formatHist( alphaT_275To375_controlMC, 0., "#alpha_{T}", "", 0., 10., 1. );
  c1_alphaT_275To375_controlData->Draw();
  c1_alphaT_275To375_controlMC->Draw("samekRed");
  TLegend *len=new TLegend( 0.75, 0.75, 0.995, 0.995 );
  len->AddEntry(c1_alphaT_275To375_controlMC, "MC");
  len->AddEntry(c1_alphaT_275To375_controlData, "Data");
  c1->SaveAs("test.eps");
}
