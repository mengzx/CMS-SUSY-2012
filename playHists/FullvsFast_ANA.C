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

#include "tdrstyle.h"
#include "playHist2D.h"
#include "playHist1D.h"


fullVsFast::fullVsFast()
{}


vector<TH1D*> fullVsFast::getBJetMultiHist(TString inFileName)
{
	//want to get the plots nbjet_CommJetgeq2_h_<N>;1

	vector<TString> vHTBins;
	vector<TString> vInFileNames;
	vector<TString> hNames;

	playHist2D factor=playHist2D();

	//fill vectors
	//vHTBins->push_back("275-325");
	//vHTBins->push_back("325-375");
	vHTBins->push_back("375-475");
	vHTBins->push_back("475-575");
	vHTBins->push_back("575-675");
	vHTBins->push_back("675-775");
	vHTBins->push_back("775-875");
	vHTBins->push_back("875");

	vInFileNames->push_back(inFileName);

	for(int i=1;i<17;i++){
		std::ostringstream inFileName;
		inFileName << "nbjet_CommJetgeq2_h_" << i <<";1";
		TFile *inFile = TFile::Open(inFileName.str().c_str()); //open the file
	}

	//sum every nbjets=0 plot
	TH2D* nBJets_1 = factor.addHistForDiffFoldersAndFiles2D(vInFileNames,vHTBins, "nbjet_CommJetgeq2_h_1;1");

	//get bin entries and collapse into a TH1D

	//add this to vector

	//return the vector

	return nBJets_1;
}
