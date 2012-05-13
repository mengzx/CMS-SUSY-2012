#ifndef fullVsFast_h
#define fullVsFast_h

#include <vector>
#include <iostream>
#include <fstream>
#include "TH2D.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "menus.h"
#include "vectors.h"

using namespace std;


class fullVsFast : public menus, public vectors{
	public:
		fullVsFast(); //constructor
		~fullVsFast(){;} //destructor

		vector<TH1D*> getBJetMultiHist(TString fileName);
		//vector<TH1D*> getJetMultiHist(TString fileName);
		void runAnalysis();

	//private:
}

#endif
