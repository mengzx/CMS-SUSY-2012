#include "vectors.h"
#include "TH2D.h"
#include "TFile.h"
#include "TString.h"

#include <vector>

#include "menus.h"

using namespace std;


menus *listmenus=new menus();

vectors::vectors(){}



TH2D* vectors::ZinvPredBG(){
  double xbins[13]={75.,125.,175.,225.,275.,325.,375.,475.,575.,675.,775.,875.,975.};
  double ybins[9]={0., 0.10, 0.20, 0.50, 0.51, 0.52, 0.53, 0.55, 0.56};
  int nxbins=12;
  int nybins=8;
  //Not the two bins (275GeV, >0.55) and (325GeV, >0.55) are from Z->mumu prediction while others are all from gammam+jets prediction. Because at high HT bins, Z->mumu statistic is limited, but with alphaT > 0.52 and < 0.55 bins, no out put from Z->mumu and gammajets prediction in the note, so set to zero
  TH2D *Zinv=new TH2D( "Zinv","Prediced Z(#rightarrow#nu#nu) + jets background from Z(#rightarrow#mu#mu) + jets and #gamma + jets events", nxbins, xbins, nybins, ybins );
  Zinv->Sumw2();
  Zinv->SetBinContent(5, 8, 1458.15 );
  Zinv->SetBinContent(6, 8, 602.57 );
  Zinv->SetBinContent(7, 8, 398.90 );
  Zinv->SetBinContent(8, 8, 159.80 );
  Zinv->SetBinContent(9, 8, 52.18 );
  Zinv->SetBinContent(10, 8, 24.81 );
  Zinv->SetBinContent(11, 8, 9.18 );
  Zinv->SetBinContent(12, 8, 7.04 );

  Zinv->SetBinContent(9, 7, 0 );
  Zinv->SetBinContent(10, 7, 0);
  Zinv->SetBinContent(11, 7, 0);
  Zinv->SetBinContent(12, 7, 0);

  Zinv->SetBinContent(11, 6, 0);
  Zinv->SetBinContent(12, 6, 0);

  Zinv->SetBinError(5, 8, 159.59 );
  Zinv->SetBinError(6, 8, 88.72 );
  Zinv->SetBinError(7, 8, 18.16 );
  Zinv->SetBinError(8, 8, 13.69 );
  Zinv->SetBinError(9, 8, 6.17 );
  Zinv->SetBinError(10, 8, 5.02 );
  Zinv->SetBinError(11, 8, 3.27 );
  Zinv->SetBinError(12, 8, 2.53 );

  Zinv->SetBinError(9, 7, 0 );
  Zinv->SetBinError(10, 7, 0 );
  Zinv->SetBinError(11, 7, 0 );
  Zinv->SetBinError(12, 7, 0 );

  Zinv->SetBinError(11, 6, 0 );
  Zinv->SetBinError(12, 6, 0 );

  return Zinv;
}

TH2D* vectors::NormalWJPredBG(){
  double xbins[13]={75.,125.,175.,225.,275.,325.,375.,475.,575.,675.,775.,875.,975.};
  double ybins[9]={0., 0.10, 0.20, 0.50, 0.51, 0.52, 0.53, 0.55, 0.56};
  int nxbins=12;
  int nybins=8;
  //Not the two bins (275GeV, >0.55) and (325GeV, >0.55) are from Z->mumu prediction while others are all from gammam+jets prediction. Because at high HT bins, Z->mumu statistic is limited, but with alphaT > 0.52 and < 0.55 bins, no out put from Z->mumu and gammajets prediction in the note, so set to zero
  TH2D *Zinv=new TH2D( "Zinv1","Prediced Z(#rightarrow#nu#nu) + jets background from Z(#rightarrow#mu#mu) + jets and #gamma + jets events", nxbins, xbins, nybins, ybins );
  Zinv->Sumw2();
  Zinv->SetBinContent(5, 8, 1886.58 );
  Zinv->SetBinContent(6, 8, 731.33 );
  Zinv->SetBinContent(7, 8, 563.33 );
  Zinv->SetBinContent(8, 8, 192.53 );
  Zinv->SetBinContent(9, 8, 51.47 );
  Zinv->SetBinContent(10, 8, 24.71 );
  Zinv->SetBinContent(11, 8, 9.00 );
  Zinv->SetBinContent(12, 8, 1.18 );

  Zinv->SetBinContent(9, 7, 0 );
  Zinv->SetBinContent(10, 7, 0);
  Zinv->SetBinContent(11, 7, 0);
  Zinv->SetBinContent(12, 7, 0);

  Zinv->SetBinContent(11, 6, 0);
  Zinv->SetBinContent(12, 6, 0);

  Zinv->SetBinError(5, 8, 108.27 );
  Zinv->SetBinError(6, 8, 65.58 );
  Zinv->SetBinError(7, 8, 27.74 );
  Zinv->SetBinError(8, 8, 20.67 );
  Zinv->SetBinError(9, 8, 8.40 );
  Zinv->SetBinError(10, 8, 6.45 );
  Zinv->SetBinError(11, 8, 3.43 );
  Zinv->SetBinError(12, 8, 1.62 );

  Zinv->SetBinError(9, 7, 0 );
  Zinv->SetBinError(10, 7, 0 );
  Zinv->SetBinError(11, 7, 0 );
  Zinv->SetBinError(12, 7, 0 );

  Zinv->SetBinError(11, 6, 0 );
  Zinv->SetBinError(12, 6, 0 );

  return Zinv;
}


TH2D* vectors::HT_ATTrigEff(){
  double xbins[13]={75.,125.,175.,225.,275.,325.,375.,475.,575.,675.,775.,875.,975.};
  double ybins[9]={0., 0.10, 0.20, 0.50, 0.51, 0.52, 0.53, 0.55, 0.56};
  int nxbins=12;
  int nybins=8;
  //Note the two bins 
  TH2D *Zinv=new TH2D( "Zinv1","HT_AlphaT trigger efficiency", nxbins, xbins, nybins, ybins );
  Zinv->Sumw2();
  Zinv->SetBinContent(5, 8, 0.727 );
  Zinv->SetBinContent(6, 8, 0.869 );
  Zinv->SetBinContent(7, 8, 0.943 );
  Zinv->SetBinContent(8, 8, 1.0 );
  Zinv->SetBinContent(9, 8, 1.0 );
  Zinv->SetBinContent(10, 8, 1.0 );
  Zinv->SetBinContent(11, 8, 1.0 );
  Zinv->SetBinContent(12, 8, 1.0 );

  Zinv->SetBinContent(9, 7, 1.0 );
  Zinv->SetBinContent(10, 7, 1.0);
  Zinv->SetBinContent(11, 7, 1.0);
  Zinv->SetBinContent(12, 7, 1.0);

  Zinv->SetBinContent(11, 6, 1.0);
  Zinv->SetBinContent(12, 6, 1.0);

  Zinv->SetBinError(5, 8, 0.0 );
  Zinv->SetBinError(6, 8, 0.0 );
  Zinv->SetBinError(7, 8, 0.0 );
  Zinv->SetBinError(8, 8, 0.0 );
  Zinv->SetBinError(9, 8, 0.0 );
  Zinv->SetBinError(10, 8, 0.0 );
  Zinv->SetBinError(11, 8, 0.0 );
  Zinv->SetBinError(12, 8, 0.0 );

  Zinv->SetBinError(9, 7, 0 );
  Zinv->SetBinError(10, 7, 0 );
  Zinv->SetBinError(11, 7, 0 );
  Zinv->SetBinError(12, 7, 0 );

  Zinv->SetBinError(11, 6, 0 );
  Zinv->SetBinError(12, 6, 0 );

  return Zinv;

}

TH2D* vectors::SingleMuTrigEff(){
  double xbins[13]={75.,125.,175.,225.,275.,325.,375.,475.,575.,675.,775.,875.,975.};
  double ybins[9]={0., 0.10, 0.20, 0.50, 0.51, 0.52, 0.53, 0.55, 0.56};
  int nxbins=12;
  int nybins=8;
  //Note the two bins 
  TH2D *Zinv=new TH2D( "Zinv","Single Muon trigger efficiency", nxbins, xbins, nybins, ybins );
  Zinv->Sumw2();
  Zinv->SetBinContent(5, 8, 0.913 );
  Zinv->SetBinContent(6, 8, 0.913 );
  Zinv->SetBinContent(7, 8, 0.913 );
  Zinv->SetBinContent(8, 8, 0.913 );
  Zinv->SetBinContent(9, 8, 0.913 );
  Zinv->SetBinContent(10, 8, 0.913 );
  Zinv->SetBinContent(11, 8, 0.913 );
  Zinv->SetBinContent(12, 8, 0.913 );

  Zinv->SetBinContent(9, 7, 0.913 );
  Zinv->SetBinContent(10, 7, 0.913 );
  Zinv->SetBinContent(11, 7, 0.913 );
  Zinv->SetBinContent(12, 7, 0.913 );

  Zinv->SetBinContent(11, 6, 0.913 );
  Zinv->SetBinContent(12, 6, 0.913 );

  Zinv->SetBinError(5, 8, 0.0 );
  Zinv->SetBinError(6, 8, 0.0 );
  Zinv->SetBinError(7, 8, 0.0 );
  Zinv->SetBinError(8, 8, 0.0 );
  Zinv->SetBinError(9, 8, 0.0 );
  Zinv->SetBinError(10, 8, 0.0 );
  Zinv->SetBinError(11, 8, 0.0 );
  Zinv->SetBinError(12, 8, 0.0 );

  Zinv->SetBinError(9, 7, 0 );
  Zinv->SetBinError(10, 7, 0 );
  Zinv->SetBinError(11, 7, 0 );
  Zinv->SetBinError(12, 7, 0 );

  Zinv->SetBinError(11, 6, 0 );
  Zinv->SetBinError(12, 6, 0 );

  return Zinv;

}

// -----------------------------------------------------------------------------
//
vector<TFile*> vectors::MCvf_pushback( TString dir, TString dataset, TString sele, TString sTreeThr, bool separateSample, TString separateSampleName){
  vector<TFile*> vf;
  if( sTreeThr == "100" || sTreeThr == "highHTBins" || sTreeThr == "375" || sTreeThr == "475" || sTreeThr == "575" || sTreeThr == "675" || sTreeThr == "775" || sTreeThr == "875"){
    if( separateSample ){
      TFile *f1=new TFile(dir+"/"+"NoSmear"+separateSampleName+"_"+dataset+"PUS7HigHTBins"+sele+".root");
      vf.push_back(f1);
    } else {
      TFile *f1=new TFile(dir+"/"+"NoSmearDY_"+dataset+"PUS7HigHTBins"+sele+".root");
      TFile *f2=new TFile(dir+"/"+"NoSmearTT_"+dataset+"PUS7HigHTBins"+sele+".root");
      TFile *f3=new TFile(dir+"/"+"NoSmearWJ_"+dataset+"PUS7HigHTBins"+sele+".root");
      TFile *f4=new TFile(dir+"/"+"NoSmearSingleT_"+dataset+"PUS7HigHTBins"+sele+".root");
      vf.push_back(f1);
      vf.push_back(f2);
      vf.push_back(f3);
      vf.push_back(f4);
    }
  } else if( sTreeThr == "86"){
    if( separateSample ){
      TFile *f1=new TFile(dir+"/"+"NoSmear"+separateSampleName+"_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      vf.push_back(f1);
    } else {
      TFile *f1=new TFile(dir+"/"+"NoSmearDY_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f2=new TFile(dir+"/"+"NoSmearTT_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f3=new TFile(dir+"/"+"NoSmearWJ_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f4=new TFile(dir+"/"+"NoSmearSingleT_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      vf.push_back(f1);
      vf.push_back(f2);
      vf.push_back(f3);
      vf.push_back(f4);
    }
  } else if( sTreeThr == "73"){
    if( separateSample ){
      TFile *f1=new TFile(dir+"/"+"NoSmear"+separateSampleName+"_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      vf.push_back(f1);
    } else {
      TFile *f1=new TFile(dir+"/"+"NoSmearDY_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f2=new TFile(dir+"/"+"NoSmearTT_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f3=new TFile(dir+"/"+"NoSmearWJ_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f4=new TFile(dir+"/"+"NoSmearSingleT_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      vf.push_back(f1);
      vf.push_back(f2);
      vf.push_back(f3);
      vf.push_back(f4);
    }
  } else if( sTreeThr == "all" || sTreeThr == "allHTBins"){
    if( separateSample ){
      TFile *f1=new TFile(dir+"/"+"NoSmear"+separateSampleName+"_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f2=new TFile(dir+"/"+"NoSmear"+separateSampleName+"_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f3=new TFile(dir+"/"+"NoSmear"+separateSampleName+"_"+dataset+"PUS7HigHTBins"+sele+".root");
      vf.push_back(f1);
      vf.push_back(f2);
      vf.push_back(f3);
    } else {
      TFile *f1=new TFile(dir+"/"+"NoSmearDY_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f2=new TFile(dir+"/"+"NoSmearTT_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f3=new TFile(dir+"/"+"NoSmearWJ_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f4=new TFile(dir+"/"+"NoSmearSingleT_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f5=new TFile(dir+"/"+"NoSmearDY_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f6=new TFile(dir+"/"+"NoSmearTT_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f7=new TFile(dir+"/"+"NoSmearWJ_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f8=new TFile(dir+"/"+"NoSmearSingleT_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f9=new TFile(dir+"/"+"NoSmearDY_"+dataset+"PUS7HigHTBins"+sele+".root");
      TFile *f10=new TFile(dir+"/"+"NoSmearTT_"+dataset+"PUS7HigHTBins"+sele+".root");
      TFile *f11=new TFile(dir+"/"+"NoSmearWJ_"+dataset+"PUS7HigHTBins"+sele+".root");
      TFile *f12=new TFile(dir+"/"+"NoSmearSingleT_"+dataset+"PUS7HigHTBins"+sele+".root");
      vf.push_back(f1);
      vf.push_back(f2);
      vf.push_back(f3);
      vf.push_back(f4);
      vf.push_back(f5);
      vf.push_back(f6);
      vf.push_back(f7);
      vf.push_back(f8);
      vf.push_back(f9);
      vf.push_back(f10);
      vf.push_back(f11);
      vf.push_back(f12);
    }
  } else if( sTreeThr == "low" || sTreeThr == "lowHTBins"){
    if( separateSample ){
      TFile *f1=new TFile(dir+"/"+"NoSmear"+separateSampleName+"_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f2=new TFile(dir+"/"+"NoSmear"+separateSampleName+"_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      vf.push_back(f1);
      vf.push_back(f2);
    } else {
      TFile *f1=new TFile(dir+"/"+"NoSmearDY_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f2=new TFile(dir+"/"+"NoSmearTT_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f3=new TFile(dir+"/"+"NoSmearWJ_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f4=new TFile(dir+"/"+"NoSmearSingleT_"+dataset+"PUS7LowHTBins"+sele+"275.root");
      TFile *f5=new TFile(dir+"/"+"NoSmearDY_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f6=new TFile(dir+"/"+"NoSmearTT_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f7=new TFile(dir+"/"+"NoSmearWJ_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      TFile *f8=new TFile(dir+"/"+"NoSmearSingleT_"+dataset+"PUS7LowHTBins"+sele+"325.root");
      vf.push_back(f1);
      vf.push_back(f2);
      vf.push_back(f3);
      vf.push_back(f4);
      vf.push_back(f5);
      vf.push_back(f6);
      vf.push_back(f7);
      vf.push_back(f8);
    }
  } else if( sTreeThr == "test"){
    TFile *f1=new TFile(dir+"/"+listmenus->testMCFile_);
    vf.push_back(f1);
  } 

  /*  if( sTreeThr == "100" || sTreeThr == "highHTBins"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_"+dataset+"PUS4HigHTBins"+sele+".root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "86"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_"+dataset+"PUS4LowHTBins"+sele+"325.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"325.root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "73"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_"+dataset+"PUS4LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"275.root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "all" || sTreeThr == "allHTBins"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_"+dataset+"PUS4LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"275.root");
    TFile *f3=new TFile(dir+"/"+"NoSmearALL_"+dataset+"PUS4LowHTBins"+sele+"325.root");
    TFile *f4=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"325.root");
    TFile *f5=new TFile(dir+"/"+"NoSmearALL_"+dataset+"PUS4HigHTBins"+sele+".root");
    TFile *f6=new TFile(dir+"/"+"NoSmearDiBoson_PUS6HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f3);
    vf.push_back(f4);
    vf.push_back(f5);
    vf.push_back(f6);
  } else if( sTreeThr == "low" || sTreeThr == "lowHTBins"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_"+dataset+"PUS4LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"275.root");
    TFile *f3=new TFile(dir+"/"+"NoSmearALL_"+dataset+"PUS4LowHTBins"+sele+"325.root");
    TFile *f4=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"325.root");
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f3);
    vf.push_back(f4);
  } else if( sTreeThr == "test"){
    TFile *f1=new TFile(dir+"/"+listmenus->testMCFile_);
    vf.push_back(f1);
    } */

  return vf;
}

vector<TFile*> vectors::Datavf_pushback( TString dir, TString dataset, TString sele, TString sTreeThr ){

  vector<TFile*> vf;

  if( sTreeThr == "100" || sTreeThr == "highHTBins" || sTreeThr == "375" || sTreeThr == "475" || sTreeThr == "575" || sTreeThr == "675" || sTreeThr == "775" || sTreeThr == "875"){
    TFile *f1=new TFile(dir+"/"+"Data"+dataset+"_PUS0HigHTBins"+sele+".root");
    vf.push_back(f1);
  } else if( sTreeThr == "86"){
    TFile *f1=new TFile(dir+"/"+"Data"+dataset+"_PUS0LowHTBins"+sele+"325.root");
    vf.push_back(f1);
  } else if( sTreeThr == "73"){
    TFile *f1=new TFile(dir+"/"+"Data"+dataset+"_PUS0LowHTBins"+sele+"275.root");
    vf.push_back(f1);
  } else if( sTreeThr == "all" || sTreeThr == "allHTBins"){
    TFile *f1=new TFile(dir+"/"+"Data"+dataset+"_PUS0LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"Data"+dataset+"_PUS0LowHTBins"+sele+"325.root");
    TFile *f3=new TFile(dir+"/"+"Data"+dataset+"_PUS0HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f3);
  } else if( sTreeThr == "low" || sTreeThr == "lowHTBins"){
    TFile *f1=new TFile(dir+"/"+"Data"+dataset+"_PUS0LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"Data"+dataset+"_PUS0LowHTBins"+sele+"325.root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "test"){
    TFile *f1=new TFile(dir+"/"+listmenus->testDataFile_);
    vf.push_back(f1);
 }

  return vf;
}


vector<TString> vectors::dirName_pushback(TString label, TString sTreeThr){
  vector<TString> dirname;

  if( sTreeThr == "100" || sTreeThr == "highHTBins" ){
    dirname.push_back(label+"375_475");
    dirname.push_back(label+"475_575");
    dirname.push_back(label+"575_675");
    dirname.push_back(label+"675_775");
    dirname.push_back(label+"775_875");
    dirname.push_back(label+"875");
  } else if ( sTreeThr == "375" ){
    dirname.push_back(label+"375_475");
  }  else if ( sTreeThr == "475" ){
    dirname.push_back(label+"475_575");
  }  else if ( sTreeThr == "575" ){
    dirname.push_back(label+"575_675");
  }  else if ( sTreeThr == "675" ){
    dirname.push_back(label+"675_775");
  }  else if ( sTreeThr == "775" ){
    dirname.push_back(label+"775_875");
  }  else if ( sTreeThr == "875" ){
    dirname.push_back(label+"875");
  } else if ( sTreeThr == "86" ){
    dirname.push_back(label+"325_375");
  } else if ( sTreeThr == "73" ){
    dirname.push_back(label+"275_325");
  } else if ( sTreeThr == "all" || sTreeThr == "allHTBins"){
    dirname.push_back(label+"275_325");
    dirname.push_back(label+"325_375");
    dirname.push_back(label+"375_475");
    dirname.push_back(label+"475_575");
    dirname.push_back(label+"575_675");
    dirname.push_back(label+"675_775");
    dirname.push_back(label+"775_875");
    dirname.push_back(label+"875");
  } else if ( sTreeThr == "low" || sTreeThr == "lowHTBins" ){
    dirname.push_back(label+"275_325");
    dirname.push_back(label+"325_375");
  } else if ( sTreeThr == "test" ){
    dirname.push_back(listmenus->testHTBin_);
  }

  return dirname;
}

vector<TString> vectors::vhname_pusback_numer( bool MuAddOrNot, bool fullesti, int startnjet, int njets ){
  vector<TString> reh;
  if( MuAddOrNot == true && ( fullesti == true || fullesti == false ) && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_all");
    } else {
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_%d", i));
      }
    }
  } else if ( MuAddOrNot == false && fullesti == true && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_all");
    } else {
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i));
      }
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_%d", i));
      }
    }
  } else if ( MuAddOrNot == false && fullesti == false && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_all");
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueVlep_h_all");
    } else {
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_%d", i));
      }
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_hasTrueVlep_h_%d", i));
      }
    }
  } else if ( listmenus->normalEstimation_ == true ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    } else{
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i));
      }
    }
  }
  return reh;
}

vector<TString> vectors::vhname_pusback_data( bool MuAddOrNot, bool fullesti, int startnjet, int njets){
  vector<TString> reh;
  if( MuAddOrNot == true && ( fullesti == true || fullesti == false) && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    } else{
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i));
      }
    }
  } else if ( MuAddOrNot == false && fullesti == true && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_15");
    } else {
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i) );
      }
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_Empty_h_%d", i) );
	//	reh.push_back( "AlphaT_vs_HT_CommJetgeq2_h_15" );
      }
    }
  } else if ( MuAddOrNot == false && fullesti == false && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all" );
    } else {
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i) );
      }
    }
  } else if ( listmenus->normalEstimation_ == true){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    } else {
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i) );
      }
    }
  }
  return reh;
}

vector<TString> vectors::vhname_pusback_domin( bool MuAddOrNot, bool fullesti, int startnjet, int njets){
  vector<TString> reh;
  if( MuAddOrNot == true && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HTTakeMu_JetMugeq2_h_all");
    } else{
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HTTakeMu_JetMugeq2_h_%d", i) );
      }
    }
  } else if ( MuAddOrNot == false && fullesti == true && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    } else{
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i) );
      }
    }
  } else if ( MuAddOrNot == false && fullesti == false && listmenus->normalEstimation_ == false ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    } else {
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i) );
      }
    }
  } else if ( listmenus->normalEstimation_ == true ){
    if( startnjet == 0 ){
      reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    } else{
      for (int i=startnjet; i<startnjet+njets; i++){
	reh.push_back( Form("AlphaT_vs_HT_CommJetgeq2_h_%d", i) );
      }
    }
  }
  return reh;
}



