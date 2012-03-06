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

//#include "AtlasStyle.C"
#include "tdrstyle.C"

double scale=46.5;

TH1D* getHist1D( TFile *f, TString dirname, TString hname){
  TDirectory *TDir = (TDirectory*)( f->Get( dirname ) );
  if( TDir ){
    TH1D* inh= (TH1D*)( TDir->Get( hname ) );
    return inh;
  } else return 0;
}

vector<unsigned int> getifileidir1D( vector<TFile*> vf, vector<TString> vdirname, TString hname ){
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

TH1D* getHistInvFandvDir1D( vector<TFile*> vf, vector<TString> vdirname, TString hname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      if( getHist1D(vf[i], vdirname[j], hname) ){
	TH1D* h=(TH1D*)(getHist1D( vf[i], vdirname[j], hname )->Clone("h"));
	return h;
      }
    }
  }
}

TH1D* addHistForDiffFoldersAndFiles1D(vector<TFile*> vf, vector<TString> vdirname, TString hname){

  TH1D* h=(TH1D*)(getHistInvFandvDir1D( vf, vdirname, hname)->Clone("h"));
  cout<<"before add h entries"<< h->GetEntries()<<endl;
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



TH2D* getHist2D( TFile *f, TString dirname, TString hname){
  TDirectory *TDir = (TDirectory*)( f->Get( dirname ) );
  if( TDir ){
    TH2D* inh= (TH2D*)( TDir->Get( hname ) );
    return inh;
  } else return 0;
}

vector<unsigned int> getifileidir2D( vector<TFile*> vf, vector<TString> vdirname, TString hname ){
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

TH2D* getHistInvFandvDir2D( vector<TFile*> vf, vector<TString> vdirname, TString hname ){
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      if( getHist2D(vf[i], vdirname[j], hname) ){
	TH2D* h=(TH2D*)(getHist2D( vf[i], vdirname[j], hname )->Clone("h"));
	return h;
      }
    }
  }
}

vector<unsigned int> getifileidirih2D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname ){
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


TH2D* getHistInvFvDirvH2D( vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname ){
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

TH2D* addHistForDiffFoldersAndFiles2D(vector<TFile*> vf, vector<TString> vdirname, TString hname){

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


TH2D* addHistForDiffFoldersFilesHists2D(vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname){

  TH2D* h=(TH2D*)(getHistInvFvDirvH2D( vf, vdirname, vhname)->Clone("h"));
  vector<unsigned int> ifileidirih_ini=getifileidirih2D( vf, vdirname, vhname );
  for( unsigned int i=0; i< vf.size(); i++ ){
    for( unsigned int j=0; j<vdirname.size(); j++ ){
      for( unsigned int k=0; k<vhname.size(); k++ ){
	TH2D* h1=getHist2D(vf[i], vdirname[j], vhname[k]);
	if( h1 && h && ( !( ( ifileidirih_ini[0] == i ) && ( ifileidirih_ini[1] == j ) && ( ifileidirih_ini[2] == k ) ) ) ){
	  h->Add(h,h1);
	}
      }
    }
  }
  return h;
}


TH2D* addHistForDiffFoldersAndFiles_SubtrackHists2D(vector<TFile*> vf, vector<TString> vdirname, vector<TString> vhname_first, vector<TString> vhname_second){

  TH2D* h_first=(TH2D*)(addHistForDiffFoldersFilesHists2D( vf, vdirname, vhname_first)->Clone("h_first"));
  TH2D* h_second=(TH2D*)(addHistForDiffFoldersFilesHists2D( vf, vdirname, vhname_second)->Clone("h_second"));
  TH2D* h=(TH2D*)(h_first->Clone("h"));
  TH2D* h1=(TH2D*)(h_second->Clone("h1"));
  cout<<"h integral="<<h->Integral(1,1000,1,1000)<<endl;
  h1->Scale(-1.);
  cout<<"h1 integral="<<h1->Integral(1,1000,1,1000)<<endl;
  h->Add(h,h1);
  cout<<"after h integral="<<h->Integral(1,1000,1,1000)<<endl;
  return h;
}



vector<TFile*> MCvf_pushback( TString dir, TString sele, TString sTreeThr){

  vector<TFile*> vf;

  if( sTreeThr == "100"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_PUS4HigHTBins"+sele+".root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "86"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBins"+sele+"325.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"325.root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "73"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"275.root");
    vf.push_back(f1);
    vf.push_back(f2);
  } else if( sTreeThr == "all"){
    TFile *f1=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"275.root");
    TFile *f3=new TFile(dir+"/"+"NoSmearALL_PUS4LowHTBins"+sele+"325.root");
    TFile *f4=new TFile(dir+"/"+"NoSmearDiBoson_PUS6LowHTBins"+sele+"325.root");
    TFile *f5=new TFile(dir+"/"+"NoSmearALL_PUS4HigHTBins"+sele+".root");
    TFile *f6=new TFile(dir+"/"+"NoSmearDiBoson_PUS6HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f3);
    vf.push_back(f4);
    vf.push_back(f5);
    vf.push_back(f6);
  }

  return vf;
}

vector<TFile*> Datavf_pushback( TString dir, TString sele, TString sTreeThr){

  vector<TFile*> vf;

  if( sTreeThr == "100"){
    TFile *f1=new TFile(dir+"/"+"Data2011AB_PUS0HigHTBins"+sele+".root");
    vf.push_back(f1);
  } else if( sTreeThr == "86"){
    TFile *f1=new TFile(dir+"/"+"Data2011AB_PUS0LowHTBins"+sele+"325.root");
    vf.push_back(f1);
  } else if( sTreeThr == "73"){
    TFile *f1=new TFile(dir+"/"+"Data2011AB_PUS0LowHTBins"+sele+"275.root");
    vf.push_back(f1);
  } else if( sTreeThr == "all"){
    TFile *f1=new TFile(dir+"/"+"Data2011AB_PUS0LowHTBins"+sele+"275.root");
    TFile *f2=new TFile(dir+"/"+"Data2011AB_PUS0LowHTBins"+sele+"325.root");
    TFile *f3=new TFile(dir+"/"+"Data2011AB_PUS0HigHTBins"+sele+".root");
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f3);
  }

  return vf;
}


vector<TString> dirName_pushback(TString label, TString sTreeThr){
  vector<TString> dirname;

  if( sTreeThr == "100" ){
    dirname.push_back(label+"375_475");
    dirname.push_back(label+"475_575");
    dirname.push_back(label+"575_675");
    dirname.push_back(label+"675_775");
    dirname.push_back(label+"775_875");
    dirname.push_back(label+"875");
  } else if ( sTreeThr == "86" ){
    dirname.push_back(label+"325_375");
  } else if ( sTreeThr == "73" ){
    dirname.push_back(label+"275_325");
  } else if ( sTreeThr == "all"){
    dirname.push_back(label+"275_325");
    dirname.push_back(label+"325_375");
    dirname.push_back(label+"375_475");
    dirname.push_back(label+"475_575");
    dirname.push_back(label+"575_675");
    dirname.push_back(label+"675_775");
    dirname.push_back(label+"775_875");
    dirname.push_back(label+"875");
  }
  return dirname;
}

vector<TString> vhname_pusback_numer( bool MuAddOrNot, bool fullesti){
  vector<TString> reh;
  if( MuAddOrNot == true && ( fullesti == true || fullesti == false) ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_all");
  } else if ( MuAddOrNot == false && fullesti == true ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_all");
  } else if ( MuAddOrNot == false && fullesti == false ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_all");
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueVlep_h_all");
  }
  return reh;
}

vector<TString> vhname_pusback_data( bool MuAddOrNot, bool fullesti){
  vector<TString> reh;
  if( MuAddOrNot == true && ( fullesti == true || fullesti == false) ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
  } else if ( MuAddOrNot == false && fullesti == true ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_all");
  } else if ( MuAddOrNot == false && fullesti == false ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
  }
  return reh;
}

vector<TString> vhname_pusback_domin( bool MuAddOrNot, bool fullesti){
  vector<TString> reh;
  if( MuAddOrNot == true ){
    reh.push_back("AlphaT_vs_HTTakeMu_JetMugeq2_h_all");
  } else if ( MuAddOrNot == false && fullesti == true ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
  } else if ( MuAddOrNot == false && fullesti == false ){
    reh.push_back("AlphaT_vs_HT_CommJetgeq2_h_all");
  }
  return reh;
}



TH2D* formatHist(TH2D* inh, double inscale){
  setTDRStyle();
  TH2D* h=(TH2D*)(inh->Clone("h"));
  h->GetYaxis()->SetRangeUser(0.5,0.56);
  h->GetXaxis()->SetRangeUser(275,975);
  h->Scale(inscale);

  return h;
}

vector<TH2D*> getTranslationFactor( bool MuAddOrNot, bool fullesti, TString HTBins, bool isData){
  TString dirhad="/Users/zmeng/Work_CMS/SUSY/myppt/BGEstimation_16022012/rootfiles/hadronicSele";

  TString dir1mu="";
  if( MuAddOrNot == true){
    dir1mu="/Users/zmeng/Work_CMS/SUSY/myppt/BGEstimation_16022012/rootfiles/oneMuonSele/muonpT50GeV";
  } else{
    dir1mu="/Users/zmeng/Work_CMS/SUSY/myppt/BGEstimation_16022012/rootfiles/oneMuonSele/muonpT10GeVATHTTrigger";
  }

  vector<TFile*> vf_had;
  if( isData == true ){
    vf_had=Datavf_pushback(dirhad, "HadSele", HTBins);
  } else {
    vf_had=MCvf_pushback(dirhad, "HadSele", HTBins);
  }

  vector<TFile*> vf_1mu;
  vector<TFile*> Datavf_1mu;
  if( MuAddOrNot == true){
    if( isData == true ){
      vf_1mu=Datavf_pushback(dir1mu, "MuonAddedMuHTTrig", HTBins);
    } else vf_1mu=MCvf_pushback(dir1mu, "MuonAddedMuHTTrig", HTBins);
  } else{
    if( isData == true ){
      vf_1mu=Datavf_pushback(dir1mu, "MuonHTATTrig", HTBins);
    } else vf_1mu=MCvf_pushback(dir1mu, "MuonHTATTrig", HTBins);
  }


  vector<TString> dirNamehad=dirName_pushback("", HTBins);
  vector<TString> dirName1mu=dirName_pushback("OneMuon_", HTBins);

  vector<TString> hNamehad;
  vector<TString> hName1mu=vhname_pusback_domin(MuAddOrNot, fullesti);

  if( isData == true ){
    hNamehad=vhname_pusback_data(MuAddOrNot, fullesti);
  } else{
    hNamehad=vhname_pusback_numer(MuAddOrNot, fullesti);
  }

  //  TH2D* AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_had=addHistForDiffFoldersAndFiles2D(vf_had, dirNamehad, "AlphaT_vs_HT_"+numerHist+"_h_all");
  //  TH2D* AlphaT_vs_HT_JetMugeq2_1mu=addHistForDiffFoldersAndFiles2D(vf_1mu, dirName1mu, "AlphaT_vs_HT_"+domiHist+"_h_all");

  if( MuAddOrNot == true ){
    vector<TH2D*> reh2d;

    TH2D* AlphaT_vs_HT_numer=addHistForDiffFoldersFilesHists2D( vf_had, dirNamehad, hNamehad );
    TH2D* AlphaT_vs_HT_domin=addHistForDiffFoldersFilesHists2D( vf_1mu, dirName1mu, hName1mu );
    
    TH2D* factor_h=(TH2D*)( AlphaT_vs_HT_numer->Clone( "factor_h" ) );
    factor_h->Divide( AlphaT_vs_HT_numer, AlphaT_vs_HT_domin );

    reh2d.push_back( formatHist( AlphaT_vs_HT_numer, scale ) );
    reh2d.push_back( formatHist( AlphaT_vs_HT_domin, scale ) );
    reh2d.push_back( formatHist( factor_h, 1. ) );
    return reh2d;
  }

  if( MuAddOrNot == false and fullesti == true ){
    vector<TH2D*> reh2d;

    vector<TString> vhname_first;
    vector<TString> vhname_second;
    vhname_first.push_back(hNamehad[0]);
    vhname_second.push_back(hNamehad[1]);

    TH2D* AlphaT_vs_HT_numer=addHistForDiffFoldersAndFiles_SubtrackHists2D(vf_had, dirNamehad, vhname_first, vhname_second );
    TH2D* AlphaT_vs_HT_domin=addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu );
    
    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( formatHist( AlphaT_vs_HT_numer, scale ) );
    reh2d.push_back( formatHist( AlphaT_vs_HT_domin, scale ) );
    reh2d.push_back( formatHist( factor_h, 1. ) );
    return reh2d;
  }

  if( MuAddOrNot == false and fullesti == false ){
    vector<TH2D*> reh2d;

    TH2D* AlphaT_vs_HT_numer=addHistForDiffFoldersFilesHists2D(vf_had, dirNamehad, hNamehad );
    TH2D* AlphaT_vs_HT_domin=addHistForDiffFoldersFilesHists2D(vf_1mu, dirName1mu, hName1mu );
    
    TH2D* factor_h=(TH2D*)(AlphaT_vs_HT_numer->Clone("factor_h"));
    factor_h->Divide(AlphaT_vs_HT_numer, AlphaT_vs_HT_domin);

    reh2d.push_back( formatHist( AlphaT_vs_HT_numer, scale ) );
    reh2d.push_back( formatHist( AlphaT_vs_HT_domin, scale ) );
    reh2d.push_back( formatHist( factor_h, 1. ) );
    return reh2d;
  }

}

vector<TLine*> Lines(){
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

TH2D* getFactor( bool MuAddOrNot, bool fullesti, TString HTBins, TString plotname, bool isData){

  TCanvas *c1=new TCanvas();
  vector<TLine*> lines=Lines();

  vector<TH2D*> factorHist_hasTauHadToMuAdded=getTranslationFactor( MuAddOrNot, fullesti, HTBins, isData );
  factorHist_hasTauHadToMuAdded[2]->Draw("colz");
  factorHist_hasTauHadToMuAdded[2]->Draw("textsame");

  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("factor_"+plotname+".png");
  //  c1->SaveAs("factor_"+plotname+".eps");
  c1->Update();
  c1->Clear();

  return factorHist_hasTauHadToMuAdded[2];
}

TH2D* getData1mu( bool MuAddOrNot, bool fullesti, TString HTBins ){

  vector<TH2D*> Data1mu=getTranslationFactor( MuAddOrNot, fullesti, HTBins, true );

  return Data1mu[1];
}

void baseCheck( bool MuAddOrNot, bool fullesti, TString HTBins, TString plotname, bool isData){

  TCanvas *c1=new TCanvas();
  vector<TLine*> lines=Lines();

  vector<TH2D*> factorHist=getTranslationFactor( MuAddOrNot, fullesti, HTBins, isData );
  factorHist[0]->Draw("colz");
  factorHist[0]->Draw("textsame");

  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("numer_"+plotname+".png");
  //  c1->SaveAs("numer_"+plotname+".eps");
  c1->Update();
  c1->Clear();

  factorHist[1]->Draw("colz");
  factorHist[1]->Draw("textsame");

  for( unsigned int il=0; il<lines.size(); il++){
    (lines[il])->Draw("same");
  }
  c1->SaveAs("domin_"+plotname+".png");
  //  c1->SaveAs("domin_"+plotname+".eps");
  c1->Update();
  c1->Clear();
}

void getResults(){

  baseCheck( true, false, "all", "tauHadEsti_AddMuToAT", false );
  baseCheck( false, false, "all", "LepEsti_NotAddMuToAT", false );
  baseCheck( false, true, "all", "NotTauHadEsti_NotAddMuToAT", false );
  baseCheck( true, false, "all", "tauHadEsti_AddMuToAT", true );
  baseCheck( false, false, "all", "LepEsti_NotAddMuToAT", true );

  TH2D* factorh_AddMu=getFactor( true, false, "all", "tauHadEsti_AddMuToAT", false );
  TH2D* factorh_Lep=getFactor( false, false, "all", "LepEsti_NotAddMuToAT", false );
  TH2D* factorh_NotTauHad=getFactor( false, true, "all", "NotTauHadEsti_NotAddMuToAT", false );

  TH2D* Data1mu_AddMu=getData1mu(true, false, "all");
  TH2D* Data1mu_NotAddMu=getData1mu(false, false, "all");

  TH2D* pred_AddMu=(TH2D*)(Data1mu_AddMu->Clone("pred_AddMu"));
  TH2D* pred_Lep=(TH2D*)(Data1mu_NotAddMu->Clone("pred_Lep"));
  TH2D* pred_NotTauHad=(TH2D*)(Data1mu_NotAddMu->Clone("pred_NotTauHad"));

  pred_AddMu->Multiply(pred_AddMu, factorh_AddMu);
  pred_Lep->Multiply(pred_Lep, factorh_Lep);
  pred_NotTauHad->Multiply(pred_NotTauHad, factorh_NotTauHad);

  TH2D* pred_AddMu_c1=formatHist(pred_AddMu, 1.);
  TH2D* pred_Lep_c1=formatHist(pred_Lep, 1.);
  TH2D* pred_NotTauHad_c1=formatHist(pred_NotTauHad, 1.);

  TCanvas *c1=new TCanvas();
  pred_AddMu_c1->Draw("colz");
  pred_AddMu_c1->Draw("sametext");
  c1->SaveAs("pred_AddMu.png");
  c1->Update();
  c1->Clear();
  pred_Lep_c1->Draw("colz");
  pred_Lep_c1->Draw("sametext");
  c1->SaveAs("pred_Lep.png");
  c1->Update();
  c1->Clear();
  pred_NotTauHad_c1->Draw("colz");
  pred_NotTauHad_c1->Draw("sametext");
  c1->SaveAs("pred_NotTauHad.png");
  c1->Update();
  c1->Clear();


}
