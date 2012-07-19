#include "BGCompositions.h"
#include "playHist2D.h"
#include "project2DHists.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include <stdio.h>

using namespace std;


BGCompositions::BGCompositions()
{}

// -----------------------------------------------------------------------------
//
TH2D* BGCompositions::getHist2D_i( TString dir, TString fname, TString dirname, TString hname, TString sele, TString HTBins ){
  playHist2D p2d=playHist2D();
  TFile *f=(MCvf_pushback( inidir_+dir+subdir_, "", sele, HTBins, true, fname ))[0];
  TH2D *h=p2d.getHist2D( f, dirname, hname );
  closefV();
  return h;
}

TH2D* BGCompositions::getHist2D_all( TString dir, TString dirname, TString hname, TString sele, TString HTBins ){
  playHist2D p2d=playHist2D();
  vector<TFile*> f=MCvf_pushback( inidir_+dir+subdir_, "", sele, HTBins, false, "" );
  TH2D *h=p2d.getHist2D( f[0], dirname, hname );
  for( unsigned int i=1; i<f.size(); i++ ){
    TH2D *h1=p2d.getHist2D( f[i], dirname, hname );
    h->Add(h,h1);
  }
  closefV();
  return h;
}


void BGCompositions::printout( TString sele, int nbjets ){
  project2DHists pf=project2DHists();
  TString dir="";
  TString label="";
  if( sele == "HadSele" ){
    dir="rootfiles/hadronicSele";
    label="";
  } else if( sele == "MuonSingleMuTrig" ){
    dir="rootfiles/oneMuonSele/muonpT45GeV";
    label="OneMuon_";
  }
  vector<TString> vfname;
  vfname.push_back( "Zinv" );
  vfname.push_back( "WJ" );
  vfname.push_back( "TT" );
  vfname.push_back( "DY" );
  vfname.push_back( "SingleT" );
  vfname.push_back( "DiBoson" );
  vector<TString> vfsample;
  vfsample.push_back( "$Z\\rightarrow\\nu\\nu+jets$" );
  vfsample.push_back( "W+jets" );
  vfsample.push_back( "$t\\bar{t}$" );
  vfsample.push_back( "Drell-Yan" );
  vfsample.push_back( "Single top" );
  vfsample.push_back( "Di-Boson" );
  vector<TString> vdirname;
  vdirname.push_back(label+"275_325");
  vdirname.push_back(label+"325_375");
  vdirname.push_back(label+"375_475");
  vdirname.push_back(label+"475_575");
  vdirname.push_back(label+"575_675");
  vdirname.push_back(label+"675_775");
  vdirname.push_back(label+"775_875");
  vdirname.push_back(label+"875");

  vector<TString> vdir;
  vdir.push_back("275--325");
  vdir.push_back("325--375");
  vdir.push_back("375--475");
  vdir.push_back("475--575");
  vdir.push_back("575--675");
  vdir.push_back("675--775");
  vdir.push_back("775--875");
  vdir.push_back("875--$\\infty$");

  vector<TString> vHTBins;
  vHTBins.push_back("73");
  vHTBins.push_back("86");
  vHTBins.push_back("375");
  vHTBins.push_back("475");
  vHTBins.push_back("575");
  vHTBins.push_back("675");
  vHTBins.push_back("775");
  vHTBins.push_back("875");
  //  TString sele="HadSele";
  //  TString sele="MuonSingleMuTrig";
  vector<TString> vhname;
  vector<TString> vcomname;
  vcomname.push_back("$W\\rightarrow\\mu(e)\\nu$");
  vcomname.push_back("$\\tau\\rightarrow had$");
  vcomname.push_back("$\\tau\\rightarrow lep$");
  if( nbjets >= 0 ){
  vhname.push_back(Form("AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_%d", nbjets+1));
  vhname.push_back(Form("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_%d", nbjets+1));
  vhname.push_back(Form("AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_%d", nbjets+1));
  }else{
    vhname.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_all");
    vhname.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_all");
    vhname.push_back("AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_all");
  }

  TString hname ="AlphaT_vs_HT_CommJetgeq2_h_all";
  if( nbjets >=0 ){
    hname=Form("AlphaT_vs_HT_CommJetgeq2_h_%d", nbjets+1);
  }
  double lowy=0.55;
  double highy=10.;

  FILE * outputfile;

  //Sample composition

  char buffer[100];
  sprintf (buffer, "Composition_Sample_%ib_%s.tex", nbjets, sele.Data());
  outputfile = fopen (buffer,"w");
  outputfile = fopen (buffer,"w");

  fprintf(outputfile, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputfile, "\\begin{document} \n");

  fprintf(outputfile, "\\begin{table}[htl] \n");

  fprintf(outputfile, "\\caption{Backgroupd predictions.}\n");
  fprintf(outputfile, " \\begin{flushleft}\n");
  fprintf(outputfile, " \\begin{tabular}{ c|ccccccc }\n");

  fprintf(outputfile, "\\hline\n");

  fprintf(outputfile, "& Total");
  for( unsigned int isam=0; isam<vfname.size(); isam++){
    fprintf(outputfile, "& %s", (vfsample[isam]).Data());
  }
    fprintf( outputfile, "\\\\ \n");
  for( unsigned int idir=0; idir<vdirname.size(); idir++){
    fprintf( outputfile, "%s", (vdir[idir]).Data());
    TH2D *allh=getHist2D_all( dir, vdirname[idir], hname, sele, vHTBins[idir] );
    TH1D* hTalphaTSlices=pf.projectX( allh, lowy, highy );
    double out=(hTalphaTSlices->GetBinContent(idir+5))*mcscale_HT_;
    fprintf(outputfile, "& %.2f", out); 
    for( unsigned int isam=0; isam<vfname.size(); isam++){
      TH2D *ih=getHist2D_i( dir, vfname[isam], vdirname[idir], hname, sele, vHTBins[idir] );
      TH1D *hTalphaTSlices_i=pf.projectX( ih, lowy, highy );
      fprintf(outputfile, "& %.2f", (hTalphaTSlices_i->GetBinContent(idir+5))/hTalphaTSlices->GetBinContent(idir+5) );
    }
    fprintf( outputfile, "\\\\ \n");
  }

  fprintf(outputfile, "\\hline\n");
  fprintf( outputfile, "\n");
  fprintf( outputfile, "\n");

  fprintf(outputfile, " \\end{tabular}\n");
  fprintf(outputfile, " \\end{flushleft}\n");
  fprintf(outputfile, "\\label{tab:Composition_Sample_%i}\n", nbjets);
  fprintf(outputfile, " \\end{table}\n\n");


  fprintf(outputfile,"\\end{document}\n\n\n");

  fclose( outputfile );



  //Sample composition Nevents
  char buffer12[100];
  sprintf (buffer12, "NEvents_Sample_%ib_%s.tex", nbjets, sele.Data());
  outputfile = fopen (buffer12,"w");
  outputfile = fopen (buffer12,"w");

  fprintf(outputfile, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputfile, "\\begin{document} \n");

  fprintf(outputfile, "\\begin{table}[htl] \n");

  fprintf(outputfile, "\\caption{Backgroupd predictions.}\n");
  fprintf(outputfile, " \\begin{flushleft}\n");
  fprintf(outputfile, " \\begin{tabular}{ c|ccccccc }\n");

  fprintf(outputfile, "\\hline\n");
  fprintf(outputfile, "& Total");
  for( unsigned int isam=0; isam<vfname.size(); isam++){
    fprintf(outputfile, "& %s", (vfsample[isam]).Data());
  }
    fprintf( outputfile, "\\\\ \n");
  for( unsigned int idir=0; idir<vdirname.size(); idir++){
    fprintf( outputfile, "%s", (vdir[idir]).Data());
    TH2D *allh=getHist2D_all( dir, vdirname[idir], hname, sele, vHTBins[idir] );
    TH1D* hTalphaTSlices=pf.projectX( allh, lowy, highy );
    double out=(hTalphaTSlices->GetBinContent(idir+5))*mcscale_HT_;
    fprintf(outputfile, "& %.2f", out); 
    for( unsigned int isam=0; isam<vfname.size(); isam++){
      TH2D *ih=getHist2D_i( dir, vfname[isam], vdirname[idir], hname, sele, vHTBins[idir] );
      TH1D *hTalphaTSlices_i=pf.projectX( ih, lowy, highy );
      fprintf(outputfile, "& %.1f", (hTalphaTSlices_i->GetBinContent(idir+5))*mcscale_HT_);
    }
    fprintf( outputfile, "\\\\ \n");

  }
  fprintf(outputfile, "\\hline\n");
  fprintf( outputfile, "\n");
  fprintf( outputfile, "\n");

  fprintf(outputfile, " \\end{tabular}\n");
  fprintf(outputfile, " \\end{flushleft}\n");
  fprintf(outputfile, "\\label{tab:NEvents_Sample_%i}\n", nbjets);
  fprintf(outputfile, " \\end{table}\n\n");


  fprintf(outputfile,"\\end{document}\n\n\n");

  fclose( outputfile );


  //particle composition Nevents

  char buffer1[100];
  sprintf (buffer1, "NEvents_Particle_%ib_%s.tex", nbjets, sele.Data());
  outputfile = fopen (buffer1,"w");
  outputfile = fopen (buffer1,"w");

  fprintf(outputfile, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputfile, "\\begin{document} \n");

  fprintf(outputfile, "\\begin{table}[htl] \n");

  fprintf(outputfile, "\\caption{Backgroupd predictions.}\n");
  fprintf(outputfile, " \\begin{flushleft}\n");
  fprintf(outputfile, " \\begin{tabular}{ c|ccccc }\n");

  fprintf(outputfile, "\\hline\n");

  fprintf(outputfile, "& Total & $Z\\rightarrow\\nu\\nu+jets$" );
  for( unsigned int isam=0; isam<vhname.size(); isam++){
    fprintf(outputfile, "& %s", (vcomname[isam]).Data());
  }
    fprintf( outputfile, "\\\\ \n");
  for( unsigned int idir=0; idir<vdirname.size(); idir++){
    fprintf( outputfile, "%s", (vdir[idir]).Data());
    TH2D *allh=getHist2D_all( dir, vdirname[idir], hname, sele, vHTBins[idir] );
    TH1D* hTalphaTSlices=pf.projectX( allh, lowy, highy );
    double out=(hTalphaTSlices->GetBinContent(idir+5))*mcscale_HT_;
    fprintf(outputfile, "& %.2f", out); 
    for( unsigned int isam=0; isam<vfname.size(); isam++){
      TH2D *ih=getHist2D_i( dir, vfname[isam], vdirname[idir], hname, sele, vHTBins[idir] );
      TH1D *hTalphaTSlices_i=pf.projectX( ih, lowy, highy );
      if( vfname[isam] == "Zinv"){
      fprintf(outputfile, "& %.2f", (hTalphaTSlices_i->GetBinContent(idir+5))*mcscale_HT_);
      }
    }
    for( unsigned int isam=0; isam<vhname.size(); isam++){
      TH2D *allh_i=getHist2D_all( dir, vdirname[idir], vhname[isam], sele, vHTBins[idir] );
      TH1D *hTalphaTSlices_i=pf.projectX( allh_i, lowy, highy );

      fprintf(outputfile, "& %.2f", (hTalphaTSlices_i->GetBinContent(idir+5))*mcscale_HT_);

    }
    fprintf( outputfile, "\\\\ \n");
  }
  fprintf(outputfile, "\\hline\n");



  fprintf( outputfile, "\n");
  fprintf( outputfile, "\n");

  fprintf(outputfile, " \\end{tabular}\n");
  fprintf(outputfile, " \\end{flushleft}\n");
  fprintf(outputfile, "\\label{tab:NEvents_Particle_%i}\n", nbjets);
  fprintf(outputfile, " \\end{table}\n\n");


  fprintf(outputfile,"\\end{document}\n\n\n");

  fclose( outputfile );



  //particle composition
  char buffer11[100];
  sprintf (buffer11, "Composition_Particle_%ib_%s.tex", nbjets, sele.Data());
  outputfile = fopen (buffer11,"w");
  outputfile = fopen (buffer11,"w");

  fprintf(outputfile, "\\documentclass[a4paper,12pt]{article} \n");
  fprintf(outputfile, "\\begin{document} \n");

  fprintf(outputfile, "\\begin{table}[htl] \n");

  fprintf(outputfile, "\\caption{Backgroupd predictions.}\n");
  fprintf(outputfile, " \\begin{flushleft}\n");
  fprintf(outputfile, " \\begin{tabular}{ c|ccccc }\n");

  fprintf(outputfile, "\\hline\n");

  fprintf(outputfile, "& Total & $Z\\rightarrow\\nu\\nu+jets$" );
  for( unsigned int isam=0; isam<vhname.size(); isam++){
    fprintf(outputfile, "& %s", (vcomname[isam]).Data());
  }
  fprintf( outputfile, "\\\\ \n");
  for( unsigned int idir=0; idir<vdirname.size(); idir++){
    fprintf( outputfile, "%s", (vdir[idir]).Data());
    TH2D *allh=getHist2D_all( dir, vdirname[idir], hname, sele, vHTBins[idir] );
    TH1D* hTalphaTSlices=pf.projectX( allh, lowy, highy );
    double out=(hTalphaTSlices->GetBinContent(idir+5))*mcscale_HT_;
    fprintf(outputfile, "& %.2f", out); 
    for( unsigned int isam=0; isam<vfname.size(); isam++){
      TH2D *ih=getHist2D_i( dir, vfname[isam], vdirname[idir], hname, sele, vHTBins[idir] );
      TH1D *hTalphaTSlices_i=pf.projectX( ih, lowy, highy );
      if( vfname[isam] == "Zinv"){
        fprintf(outputfile, "& %.2f", (hTalphaTSlices_i->GetBinContent(idir+5))/(hTalphaTSlices->GetBinContent(idir+5)) );
      }
    }
    for( unsigned int isam=0; isam<vhname.size(); isam++){
      TH2D *allh_i=getHist2D_all( dir, vdirname[idir], vhname[isam], sele, vHTBins[idir] );
      TH1D *hTalphaTSlices_i=pf.projectX( allh_i, lowy, highy );
      fprintf(outputfile, "& %.2f", (hTalphaTSlices_i->GetBinContent(idir+5))/(hTalphaTSlices->GetBinContent(idir+5)) );
    }
    fprintf( outputfile, "\\\\ \n");
  }

  fprintf(outputfile, "\\hline\n");
  fprintf( outputfile, "\n");
  fprintf( outputfile, "\n");

  fprintf(outputfile, " \\end{tabular}\n");
  fprintf(outputfile, " \\end{flushleft}\n");
  fprintf(outputfile, "\\label{tab:Composition_Particle_%i}\n", nbjets);
  fprintf(outputfile, " \\end{table}\n\n");


  fprintf(outputfile,"\\end{document}\n\n\n");

  fclose( outputfile );

}

