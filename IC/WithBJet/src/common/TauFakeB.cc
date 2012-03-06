#include "TauFakeB.hh"
#include "CommonOps.hh"
#include "EventData.hh"
#include "KinSuite.hh"
#include "TH1D.h"
#include "TH2D.h"
#include "Types.hh"
#include "mt2_bisect.hh"
#include "AlphaT.hh"
#include "Jet.hh"
#include "Math/VectorUtil.h"
#include "JetData.hh"
#include "TMath.h"
//Added by Zhaoxia Meng
#include "GenMatrixBin.hh"
#include "GenObject.hh"
#include "Compute_Variable.hh"
//vvvv

using namespace Operation;

// -----------------------------------------------------------------------------
TauFakeB::TauFakeB( const Utils::ParameterSet& ps) :
  //Misc
  dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
  minDR_( ps.Get<double>("minDR") ),
  mCut_( ps.Get<double>("mCut") ),
  isData_( ps.Get<bool>("isData") ),
  //MT2
  StandardPlots_( ps.Get<bool>("StandardPlots") )

{}

// -----------------------------------------------------------------------------
//
TauFakeB::~TauFakeB() {}
// -----------------------------------------------------------------------------
//

void TauFakeB::Start( Event::Data& ev ) {
  initDir( ev.OutputFile(), dirName_.c_str() );
  BookHistos();
}

// -----------------------------------------------------------------------------
//
void TauFakeB::BookHistos() {
  if ( StandardPlots_ ) { StandardPlots(); }
}

// -----------------------------------------------------------------------------
//
bool TauFakeB::Process ( Event::Data& ev ) {
  if ( StandardPlots_ ) { StandardPlots(ev); }
  return true;
}

// -----------------------------------------------------------------------------
//
std::ostream& TauFakeB::Description( std::ostream& ostrm ){
  ostrm << "Tau-jet fake B-jet plots";
  ostrm << "" << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}

// -----------------------------------------------------------------------------
//
void TauFakeB::StandardPlots() {


  /*  BookHistArray( TrueTauPt_vs_TaggedBPt_,
		 "TrueTauPt_vs_TaggedBPt",
		 ";True #tau-jet p_{T} (GeV);# b-jet p_{T} (GeV)",
		 120, 0., 500.,
		 240, 0., 1200.,
		 nMax_+1, 0, 1, true );*/

  BookHistArray( totalEvents_h_,
		 "totalEvents_h",
		 "Total number of events",
		 2, 0, 2.,
		 nMax_+1, 0, 1, true );


  BookHistArray( totalEvents_CommJet_h_,
		 "totalEvents_CommJet_h",
		 "Total number of events with jets #geq 2",
		 2, 0, 2.,
		 nMax_+1, 0, 1, true );

  BookHistArray( totalEvents_CommObj_h_,
		 "totalEvents_CommObj_h",
		 "Total number of events with objects #geq 2",
		 2, 0, 2.,
		 nMax_+1, 0, 1, true );



  //When nobj >=2 -----------------------------

  //AlphaT and HT distribution
  BookHistArray( AlphaT_CommObjgeq2_h_,
		 "AlphaT_CommObjgeq2_h",
		 "#alpha_{T} distribution of objects #geq 2",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HT_CommObjgeq2_h_,
		 "HT_CommObjgeq2_h",
		 "#HT distribution of objects #geq 2",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommObjgeq2_h_,
		 "AlphaT_vs_HT_CommObjgeq2_h",
		 "#alpha_{T} vs HT of objects #geq 2",
		 56, 0., 0.56,
		 9, 75., 975.,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with tau->had
  double xbins[13]={75.,125.,175.,225.,275.,325.,375.,475.,575.,675.,775.,875.,975.};
  double ybins[6]={0.50,0.51,0.52,0.53,0.55,0.56};
  int nxbins=12;
  int nybins=5;

  BookHistArray( AlphaT_CommObjgeq2_hasTrueTauHad_h_,
		 "AlphaT_CommObjgeq2_hasTrueTauHad_h",
		 "#alpha_{T} distribution of objects #geq 2 and #tau_{h} > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HT_CommObjgeq2_hasTrueTauHad_h_,
		 "HT_CommObjgeq2_hasTrueTauHad_h",
		 "HT distribution of objects #geq 2 and #tau_{h} > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  //  BookHistArray( AlphaT_vs_HT_CommObjgeq2_hasTrueTauHad_h_,
  //		 "AlphaT_vs_HT_CommObjgeq2_hasTrueTauHad_h",
  //		 "#alpha_{T} vs HT of objects #geq 2 and #tau_{h} > 0",
		 //		 56, 0., 0.56,
		 //                 9, 75., 975.,
		 //		 nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_CommObjgeq2_hasTrueTauHad_h_,
		 "AlphaT_vs_HT_CommObjgeq2_hasTrueTauHad_h",
		 "#alpha_{T} vs HT of objects #geq 2 and #tau_{h} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with tau->lep
  BookHistArray( AlphaT_CommObjgeq2_hasTrueTauLep_h_,
		 "AlphaT_CommObjgeq2_hasTrueTauLep_h",
		 "#alpha_{T} distribution of objects #geq 2 and #tau_{l} > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HT_CommObjgeq2_hasTrueTauLep_h_,
		 "HT_CommObjgeq2_hasTrueTauLep_h",
		 "HT distribution of objects #geq 2 and #tau_{l} > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommObjgeq2_hasTrueTauLep_h_,
		 "AlphaT_vs_HT_CommObjgeq2_hasTrueTauLep_h",
		 "#alpha_{T} vs HT of objects #geq 2 and #tau_{l} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with V->lep
  BookHistArray( AlphaT_CommObjgeq2_hasTrueVLep_h_,
		 "AlphaT_CommObjgeq2_hasTrueVLep_h",
		 "#alpha_{T} distribution of objects #geq 2 and lepton from W/Z > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HT_CommObjgeq2_hasTrueVLep_h_,
		 "HT_CommObjgeq2_hasTrueVLep_h",
		 "HT distribution of objects #geq 2 and lepton from W/Z > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommObjgeq2_hasTrueVLep_h_,
		 "AlphaT_vs_HT_CommObjgeq2_hasTrueVLep_h",
		 "#alpha_{T} vs HT of objects #geq 2 and lepton from W/Z > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );


  //AlphaT and HT distribution for event with tau_had matched to jet
  BookHistArray( AlphaT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} distribution of objects #geq 2 and #tau_{had} matched to jet> 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "HT distribution of objects #geq 2 and #tau_{had} matched to jet> 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_vs_HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} vs HT of objects #geq 2 and #tau_{had} matched to jet> 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );




  //When njet >=2 -----------------------------

  BookHistArray( AlphaT_CommJetgeq2_h_,
		 "AlphaT_CommJetgeq2_h",
		 "#alpha_{T} distribution of jets #geq 2",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );


  BookHistArray( HT_CommJetgeq2_h_,
		 "HT_CommJetgeq2_h",
		 "HT distribution of jets #geq 2",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommJetgeq2_h_,
		 "AlphaT_vs_HT_CommJetgeq2_h",
		 "#alpha_{T} vs HT of jets #geq 2",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with tau->had
  BookHistArray( AlphaT_CommJetgeq2_hasTrueTauHad_h_,
		 "AlphaT_CommJetgeq2_hasTrueTauHad_h",
		 "#alpha_{T} distribution of jets #geq 2 and #tau_{h} > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HT_CommJetgeq2_hasTrueTauHad_h_,
		 "HT_CommJetgeq2_hasTrueTauHad_h",
		 "HT distribution of jets #geq 2 and #tau_{h} > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_,
		 "AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h",
		 "#alpha_{T} vs HT of jets #geq 2 and #tau_{h} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with tau->lep
  BookHistArray( AlphaT_CommJetgeq2_hasTrueTauLep_h_,
		 "AlphaT_CommJetgeq2_hasTrueTauLep_h",
		 "#alpha_{T} distribution of jets #geq 2 and #tau_{l} > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HT_CommJetgeq2_hasTrueTauLep_h_,
		 "HT_CommJetgeq2_hasTrueTauLep_h",
		 "HT distribution of jets #geq 2 and #tau_{l} > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_,
		 "AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h",
		 "#alpha_{T} vs HT of jets #geq 2 and #tau_{l} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with V->lep
  BookHistArray( AlphaT_CommJetgeq2_hasTrueVLep_h_,
		 "AlphaT_CommJetgeq2_hasTrueVLep_h",
		 "#alpha_{T} distribution of jets #geq 2 and lepton from W/Z > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );


  BookHistArray( HT_CommJetgeq2_hasTrueVLep_h_,
		 "HT_CommJetgeq2_hasTrueVLep_h",
		 "HT distribution of jets #geq 2 and lepton from W/Z > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_,
		 "AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h",
		 "#alpha_{T} vs HT of jets #geq 2 and lepton from W/Z > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with tau_had matched to jet
  BookHistArray( AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} distribution of jets #geq 2 and #tau_{had} matched to jet> 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );


  BookHistArray( HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "HT distribution of jets #geq 2 and #tau_{had} matched to jet> 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );




  BookHistArray( AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} vs HT of jets #geq 2 and #tau_{had} matched to jet> 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );




  //When njet+mu >=2 -----------------------------

  BookHistArray( AlphaT_JetMugeq2_h_,
		 "AlphaT_JetMugeq2_h",
		 "#alpha_{T} distribution of jets and #muon #geq 2",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );


  BookHistArray( HT_JetMugeq2_h_,
		 "HT_JetMugeq2_h",
		 "HT distribution of jets and #muon #geq 2",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_h_,
		 "HTTakeMu_JetMugeq2_h",
		 "HT(#muon into) distribution of jets and #muon #geq 2",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_h_,
		 "AlphaT_vs_HT_JetMugeq2_h",
		 "#alpha_{T} vs HT of jets and #muon #geq 2",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_h",
		 "#alpha_{T} vs HT(#muon into) of jets and #muon #geq 2",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with tau->had
  BookHistArray( AlphaT_JetMugeq2_hasTrueTauHad_h_,
		 "AlphaT_JetMugeq2_hasTrueTauHad_h",
		 "#alpha_{T} distribution of jets and #muon #geq 2 and #tau_{h} > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );


  BookHistArray( HT_JetMugeq2_hasTrueTauHad_h_,
		 "HT_JetMugeq2_hasTrueTauHad_h",
		 "HT distribution of jets and #muon #geq 2 and #tau_{h} > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_hasTrueTauHad_h_,
		 "HTTakeMu_JetMugeq2_hasTrueTauHad_h",
		 "HT(#muon into) distribution of jets and #muon #geq 2 and #tau_{h} > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_,
		 "AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h",
		 "#alpha_{T} vs HT of jets and #muon #geq 2 and #tau_{h} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h",
		 "#alpha_{T} vs HT(#muon into) of jets and #muon #geq 2 and #tau_{h} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with tau->lep
  BookHistArray( AlphaT_JetMugeq2_hasTrueTauLep_h_,
		 "AlphaT_JetMugeq2_hasTrueTauLep_h",
		 "#alpha_{T} distribution of jets and #muon #geq 2 and #tau_{l} > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );


  BookHistArray( HT_JetMugeq2_hasTrueTauLep_h_,
		 "HT_JetMugeq2_hasTrueTauLep_h",
		 "HT distribution of jets and #muon #geq 2 and #tau_{l} > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_hasTrueTauLep_h_,
		 "HTTakeMu_JetMugeq2_hasTrueTauLep_h",
		 "HT(#muon into) distribution of jets and #muon #geq 2 and #tau_{l} > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_,
		 "AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h",
		 "#alpha_{T} vs HT of jets and #muon #geq 2 and #tau_{l} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h",
		 "#alpha_{T} vs HT(#muon into) of jets and #muon #geq 2 and #tau_{l} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with V->lep
  BookHistArray( AlphaT_JetMugeq2_hasTrueVLep_h_,
		 "AlphaT_JetMugeq2_hasTrueVLep_h",
		 "#alpha_{T} distribution of jets and #muon #geq 2 and lepton from W/Z > 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );


  BookHistArray( HT_JetMugeq2_hasTrueVLep_h_,
		 "HT_JetMugeq2_hasTrueVLep_h",
		 "HT distribution of jets and #muon #geq 2 and lepton from W/Z > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_hasTrueVLep_h_,
		 "HTTakeMu_JetMugeq2_hasTrueVLep_h",
		 "HT(#muon into) distribution of jets and #muon #geq 2 and lepton from W/Z > 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_,
		 "AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h",
		 "#alpha_{T} vs HT of jets and #muon #geq 2 and lepton from W/Z > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h",
		 "#alpha_{T} vs HT(#muon into) of jets and #muon #geq 2 and lepton from W/Z > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  //AlphaT and HT distribution for event with tau_had matched to jet
  BookHistArray( AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} distribution of jets and #muon #geq 2 #tau_{had} matched to jet> 0",
		 1000, 0, 10.,
		 nMax_+1, 0, 1, true );


  BookHistArray( HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "HT distribution of jets and #muon #geq 2 #tau_{had} matched to jet> 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "HT(#muon into) distribution of jets and #muon #geq 2 #tau_{had} matched to jet> 0",
		 1500, 0, 1500.,
		 nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} vs HT of jets and #muon #geq 2 #tau_{had} matched to jet> 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} vs HT(#muon into) of jets and #muon #geq 2 #tau_{had} matched to jet> 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+1, 0, 1, true );



  BookHistArray( theTrueTauHad_And_CommonJet_DR_h_,
		 "theTrueTauHad_And_CommonJet_DR_h",
		 "#Delta R (true #tau_{had}, jet)",
		 1000, 0, 1.,
		 nMax_+1, 0, 1, true );

}

// -----------------------------------------------------------------------------
//


// -----------------------------------------------------------------------------
//
bool TauFakeB::StandardPlots( Event::Data& ev) {
  //  UInt_t n = ev.NumCommonBtagJets( ">=", ).size();
  double weight = ev.GetEventWeight();
  unsigned int nobj = ev.CommonObjects().size();
  unsigned int njet = ev.JD_CommonJets().accepted.size();
  unsigned int njetandmu = ev.CommonJetsAndMuons().size();

  double commalphaT = ev.CommonAlphaT();
  double commHT = ev.CommonHT();
  double hadronicalphaT = ev.HadronicAlphaT();
  double hadronicalphaTTakeMu=ev.HadronicAlphaTTakeMu();
  double HTTakeMu = ev.CommonHTTakeMu();

  vector<double> CommAlphaTHT = setBin_CommonAlphaT_vs_HT( ev );
  vector<double> HadronicAlphaTHT = setBin_HadronicAlphaT_vs_HT( ev );
  vector<double> HadronicAlphaTTakeMuHTTakeMu = setBin_HadronicAlphaTTakeMu_vs_HTTakeMu( ev );
  vector<double> HadronicAlphaTTakeMuHT = setBin_HadronicAlphaTTakeMu_vs_HT( ev );

  if ( StandardPlots_ ) {

    //total number of events

    totalEvents_h_[0]->Fill(1.);
    totalEvents_h_[1]->Fill(1., weight);

    if( njet >= nMin_ && njet <= nMax_ && njet < totalEvents_CommJet_h_.size() ){
      totalEvents_CommJet_h_[0]->Fill(1.);
      totalEvents_CommJet_h_[1]->Fill(1., weight);
    }

    if( nobj >= nMin_ && nobj <= nMax_ && nobj < totalEvents_CommObj_h_.size() ){
      totalEvents_CommObj_h_[0]->Fill(1.);
      totalEvents_CommObj_h_[1]->Fill(1., weight);
    }


    //When nobj >= nMin_
    if( nobj >= nMin_ && nobj <= nMax_){

      //--------------------------------
      //
      //Fill AlphaT and HT
      if(1){
	if( nobj < AlphaT_CommObjgeq2_h_.size() ){
	  AlphaT_CommObjgeq2_h_[0]->Fill( commalphaT, weight );
	  AlphaT_CommObjgeq2_h_[nobj]->Fill( commalphaT, weight );
	}
	
	if( nobj < HT_CommObjgeq2_h_.size() ){
	  HT_CommObjgeq2_h_[0]->Fill( commHT, weight );
	  HT_CommObjgeq2_h_[nobj]->Fill( commHT, weight );
	}

	if(nobj < AlphaT_vs_HT_CommObjgeq2_h_.size() ){
	  AlphaT_vs_HT_CommObjgeq2_h_[0]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommObjgeq2_h_[nobj]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	}

      }       //Fill AlphaT and HT

      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had found
      if( !isData_ ){

      if( hasTrueTauHad( ev) ){

	if( nobj < AlphaT_CommObjgeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_CommObjgeq2_hasTrueTauHad_h_[0]->Fill( commalphaT, weight );
	  AlphaT_CommObjgeq2_hasTrueTauHad_h_[nobj]->Fill( commalphaT, weight );
	}

	if( nobj < HT_CommObjgeq2_hasTrueTauHad_h_.size() ){
	  HT_CommObjgeq2_hasTrueTauHad_h_[0]->Fill( commHT, weight );
	  HT_CommObjgeq2_hasTrueTauHad_h_[nobj]->Fill( commHT, weight );
	}

	if(nobj < AlphaT_vs_HT_CommObjgeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_vs_HT_CommObjgeq2_hasTrueTauHad_h_[0]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommObjgeq2_hasTrueTauHad_h_[nobj]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	}

      }      //Fill AlphaT and HT if tau_had found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_lep found
      if( hasTrueTauLep( ev) ){

	if( nobj < AlphaT_CommObjgeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_CommObjgeq2_hasTrueTauLep_h_[0]->Fill( commalphaT, weight );
	  AlphaT_CommObjgeq2_hasTrueTauLep_h_[nobj]->Fill( commalphaT, weight );
	}

	if( nobj < HT_CommObjgeq2_hasTrueTauLep_h_.size() ){
	  HT_CommObjgeq2_hasTrueTauLep_h_[0]->Fill( commHT, weight );
	  HT_CommObjgeq2_hasTrueTauLep_h_[nobj]->Fill( commHT, weight );
	}

	if(nobj < AlphaT_vs_HT_CommObjgeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_vs_HT_CommObjgeq2_hasTrueTauLep_h_[0]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommObjgeq2_hasTrueTauLep_h_[nobj]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	}

      }      //Fill AlphaT and HT if tau_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if V_lep found
      if( hasTrueVLep( ev) ){

	if( nobj < AlphaT_CommObjgeq2_hasTrueVLep_h_.size() ){
	  AlphaT_CommObjgeq2_hasTrueVLep_h_[0]->Fill( commalphaT, weight );
	  AlphaT_CommObjgeq2_hasTrueVLep_h_[nobj]->Fill( commalphaT, weight );
	}

	if( nobj < HT_CommObjgeq2_hasTrueVLep_h_.size() ){
	  HT_CommObjgeq2_hasTrueVLep_h_[0]->Fill( commHT, weight );
	  HT_CommObjgeq2_hasTrueVLep_h_[nobj]->Fill( commHT, weight );
	}

	if(nobj < AlphaT_vs_HT_CommObjgeq2_hasTrueVLep_h_.size() ){
	  AlphaT_vs_HT_CommObjgeq2_hasTrueVLep_h_[0]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommObjgeq2_hasTrueVLep_h_[nobj]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	}

      }      //Fill AlphaT and HT if V_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had mached to a jet is found
      if( hasTrueTauMatchedToCommonJet (ev) ){

	if( nobj < AlphaT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( commalphaT, weight );
	  AlphaT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_[nobj]->Fill( commalphaT, weight );
	}

	if( nobj < HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( commHT, weight );
	  HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_[nobj]->Fill( commHT, weight );
	}

	if(nobj < AlphaT_vs_HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_vs_HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommObjgeq2_hasTrueTauHadMatchedToCommJet_h_[nobj]->Fill( CommAlphaTHT[0], CommAlphaTHT[1], weight);
	}

      }      //Fill AlphaT and HT if tau_had mached to a jet is found
      }
      //++++++++++++++++++++++++
    }// if obj >= nMin






    //When njet >= nMin_
    if( njet >= nMin_ && njet <= nMax_){

      //--------------------------------
      //
      //Fill AlphaT and HT
      if(1){
	if( njet < AlphaT_CommJetgeq2_h_.size() ){
	  AlphaT_CommJetgeq2_h_[0]->Fill( hadronicalphaT, weight );
	  AlphaT_CommJetgeq2_h_[njet]->Fill( hadronicalphaT, weight );
	}
	
	if( njet < HT_CommJetgeq2_h_.size() ){
	  HT_CommJetgeq2_h_[0]->Fill( commHT, weight );
	  HT_CommJetgeq2_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommJetgeq2_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	}

      }       //Fill AlphaT and HT

      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had found
      if( !isData_ ){

      if( hasTrueTauHad( ev) ){

	if( njet < AlphaT_CommJetgeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_CommJetgeq2_hasTrueTauHad_h_[0]->Fill( hadronicalphaT, weight );
	  AlphaT_CommJetgeq2_hasTrueTauHad_h_[njet]->Fill( hadronicalphaT, weight );
	}

	if( njet < HT_CommJetgeq2_hasTrueTauHad_h_.size() ){
	  HT_CommJetgeq2_hasTrueTauHad_h_[0]->Fill(  commHT, weight );
	  HT_CommJetgeq2_hasTrueTauHad_h_[njet]->Fill(  commHT, weight );
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	}

      }      //Fill AlphaT and HT if tau_had found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_lep found
      if( hasTrueTauLep( ev) ){

	if( njet < AlphaT_CommJetgeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_CommJetgeq2_hasTrueTauLep_h_[0]->Fill( hadronicalphaT, weight );
	  AlphaT_CommJetgeq2_hasTrueTauLep_h_[njet]->Fill( hadronicalphaT, weight );
	}

	if( njet < HT_CommJetgeq2_hasTrueTauLep_h_.size() ){
	  HT_CommJetgeq2_hasTrueTauLep_h_[0]->Fill( commHT, weight );
	  HT_CommJetgeq2_hasTrueTauLep_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	}

      }      //Fill AlphaT and HT if tau_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if V_lep found
      if( hasTrueVLep( ev) ){

	if( njet < AlphaT_CommJetgeq2_hasTrueVLep_h_.size() ){
	  AlphaT_CommJetgeq2_hasTrueVLep_h_[0]->Fill( hadronicalphaT, weight );
	  AlphaT_CommJetgeq2_hasTrueVLep_h_[njet]->Fill( hadronicalphaT, weight );
	}

	if( njet < HT_CommJetgeq2_hasTrueVLep_h_.size() ){
	  HT_CommJetgeq2_hasTrueVLep_h_[0]->Fill( commHT, weight );
	  HT_CommJetgeq2_hasTrueVLep_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	}

      }      //Fill AlphaT and HT if V_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had mached to a jet is found
      if( hasTrueTauMatchedToCommonJet (ev) ){

	if( njet < AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( hadronicalphaT, weight );
	  AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( hadronicalphaT, weight );
	}

	if( njet < HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( commHT, weight );
	  HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);

	}
      }      //Fill AlphaT and HT if tau_had mached to a jet is found

      }
      //++++++++++++++++++++++++
    }// if jet >= nMin




    //When njet + nmu >= nMin_
    if( njetandmu >= nMin_ && njetandmu <= nMax_){

      //--------------------------------
      //
      //Fill AlphaT and HT
      if(1){
	if( njet < AlphaT_JetMugeq2_h_.size() ){
	  AlphaT_JetMugeq2_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  AlphaT_JetMugeq2_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	}
	
	if( njet < HTTakeMu_JetMugeq2_h_.size() ){
	  HTTakeMu_JetMugeq2_h_[0]->Fill( HTTakeMu, weight );
	  HTTakeMu_JetMugeq2_h_[njet]->Fill( HTTakeMu, weight );
	}

	if( njet < HT_JetMugeq2_h_.size() ){
	  HT_JetMugeq2_h_[0]->Fill( commHT, weight );
	  HT_JetMugeq2_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_JetMugeq2_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  AlphaT_vs_HT_JetMugeq2_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	}

	if(njet < AlphaT_vs_HTTakeMu_JetMugeq2_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  AlphaT_vs_HTTakeMu_JetMugeq2_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	}

      }       //Fill AlphaT and HT

      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had found
      if( !isData_ ){

      if( hasTrueTauHad( ev) ){

	if( njet < AlphaT_JetMugeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_JetMugeq2_hasTrueTauHad_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  AlphaT_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	}
	
	if( njet < HTTakeMu_JetMugeq2_hasTrueTauHad_h_.size() ){
	  HTTakeMu_JetMugeq2_hasTrueTauHad_h_[0]->Fill( HTTakeMu, weight );
	  HTTakeMu_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( HTTakeMu, weight );
	}

	if( njet < HT_JetMugeq2_hasTrueTauHad_h_.size() ){
	  HT_JetMugeq2_hasTrueTauHad_h_[0]->Fill( commHT, weight );
	  HT_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	}

	if(njet < AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	}

      }      //Fill AlphaT and HT if tau_had found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_lep found
      if( hasTrueTauLep( ev) ){

	if( njet < AlphaT_JetMugeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_JetMugeq2_hasTrueTauLep_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  AlphaT_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	}
	
	if( njet < HTTakeMu_JetMugeq2_hasTrueTauLep_h_.size() ){
	  HTTakeMu_JetMugeq2_hasTrueTauLep_h_[0]->Fill( HTTakeMu, weight );
	  HTTakeMu_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( HTTakeMu, weight );
	}

	if( njet < HT_JetMugeq2_hasTrueTauLep_h_.size() ){
	  HT_JetMugeq2_hasTrueTauLep_h_[0]->Fill( commHT, weight );
	  HT_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	}

	if(njet < AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	}

      }      //Fill AlphaT and HT if tau_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if V_lep found
      if( hasTrueVLep( ev) ){

	if( njet < AlphaT_JetMugeq2_hasTrueVLep_h_.size() ){
	  AlphaT_JetMugeq2_hasTrueVLep_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  AlphaT_JetMugeq2_hasTrueVLep_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	}
	
	if( njet < HTTakeMu_JetMugeq2_hasTrueVLep_h_.size() ){
	  HTTakeMu_JetMugeq2_hasTrueVLep_h_[0]->Fill( HTTakeMu, weight );
	  HTTakeMu_JetMugeq2_hasTrueVLep_h_[njet]->Fill( HTTakeMu, weight );
	}

	if( njet < HT_JetMugeq2_hasTrueVLep_h_.size() ){
	  HT_JetMugeq2_hasTrueVLep_h_[0]->Fill( commHT, weight );
	  HT_JetMugeq2_hasTrueVLep_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	}

	if(njet < AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	}

      }      //Fill AlphaT and HT if V_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had mached to a jet is found
      if( hasTrueTauMatchedToCommonJet (ev) ){

	if( njet < AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	}
	
	if( njet < HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( HTTakeMu, weight );
	  HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( HTTakeMu, weight );
	}

	if( njet < HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( commHT, weight );
	  HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( commHT, weight );
	}

	if(njet < AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	}

	if(njet < AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	}

      }      //Fill AlphaT and HT if tau_had mached to a jet is found

      }
      //++++++++++++++++++++++++
    }// if jet + mu>= nMin



    //True tau-had distance to common jets (DR)
    if( !isData_ ){
    for ( unsigned int ib=0; ib<ev.JD_CommonJets().accepted.size(); ib++ ) {

      for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {

	if( isTrueTauHad( ev, (*igen) ) ){

	  theTrueTauHad_And_CommonJet_DR_h_[0]->Fill( MatchedDR( *(ev.JD_CommonJets().accepted.at(ib)),  (*igen) ) );
	  theTrueTauHad_And_CommonJet_DR_h_[1]->Fill( MatchedDR( *(ev.JD_CommonJets().accepted.at(ib)),  (*igen) ), weight );

	}
      }
    }
    }
  }//if stardardplots

  return true;
}


// -----------------------------------------------------------------------------
//
vector<double> TauFakeB::setBin_CommonAlphaT_vs_HT( Event::Data& ev ){
  vector<double> revalue;

  double tmpAlphaT = -1.;
  double tmpHT = -1.;

  double alphaT = ev.CommonAlphaT();
  double HT = ev.CommonHT();

  if( alphaT >= 0.56 && HT < 975. ){
    tmpAlphaT=0.555;
    tmpHT = HT;

  } else if( alphaT >= 0.56 && HT >= 975. ){
    tmpAlphaT=0.555;
    tmpHT = 900.;
	    
  } else if( alphaT < 0.56 && HT >= 975. ){
    tmpAlphaT = alphaT;
    tmpHT = 900.;

  } else {
    tmpAlphaT = alphaT;
    tmpHT = HT;

  }
  revalue.push_back(tmpAlphaT);
  revalue.push_back(tmpHT);

  return revalue;
}

vector<double> TauFakeB::setBin_HadronicAlphaT_vs_HT( Event::Data& ev ){
  vector<double> revalue;

  double tmpAlphaT = -1.;
  double tmpHT = -1.;

  double alphaT = ev.HadronicAlphaT();
  double HT = ev.CommonHT();

  if( alphaT >= 0.56 &&  HT < 975. ){
    tmpAlphaT=0.555;
    tmpHT = HT;

  } else if( alphaT >= 0.56 && HT >= 975. ){
    tmpAlphaT=0.555;
    tmpHT = 900.;
	    
  } else if( alphaT < 0.56 && HT >= 975. ){
    tmpAlphaT = alphaT;
    tmpHT = 900.;

  } else {
    tmpAlphaT = alphaT;
    tmpHT = HT;

  }

  revalue.push_back(tmpAlphaT);
  revalue.push_back(tmpHT);

  return revalue;
}


vector<double> TauFakeB::setBin_HadronicAlphaTTakeMu_vs_HTTakeMu( Event::Data& ev ){
  vector<double> revalue;

  double tmpAlphaT = -1.;
  double tmpHT = -1.;

  double alphaT = ev.HadronicAlphaTTakeMu();
  double HT = ev.CommonHTTakeMu();

  if( alphaT >= 0.56 &&  HT < 975. ){
    tmpAlphaT=0.555;
    tmpHT = HT;

  } else if( alphaT >= 0.56 && HT >= 975. ){
    tmpAlphaT=0.555;
    tmpHT = 900.;
	    
  } else if( alphaT < 0.56 && HT >= 975. ){
    tmpAlphaT = alphaT;
    tmpHT = 900.;

  } else {
    tmpAlphaT = alphaT;
    tmpHT = HT;

  }

  revalue.push_back(tmpAlphaT);
  revalue.push_back(tmpHT);

  return revalue;
}


vector<double> TauFakeB::setBin_HadronicAlphaTTakeMu_vs_HT( Event::Data& ev ){
  vector<double> revalue;

  double tmpAlphaT = -1.;
  double tmpHT = -1.;

  double alphaT = ev.HadronicAlphaTTakeMu();
  double HT = ev.CommonHT();

  if( alphaT >= 0.56 &&  HT < 975. ){
    tmpAlphaT=0.555;
    tmpHT = HT;

  } else if( alphaT >= 0.56 && HT >= 975. ){
    tmpAlphaT=0.555;
    tmpHT = 900.;
	    
  } else if( alphaT < 0.56 && HT >= 975. ){
    tmpAlphaT = alphaT;
    tmpHT = 900.;

  } else {
    tmpAlphaT = alphaT;
    tmpHT = HT;

  }

  revalue.push_back(tmpAlphaT);
  revalue.push_back(tmpHT);

  return revalue;
}


// -----------------------------------------------------------------------------
//
bool TauFakeB::hasTrueTauMatchedToCommonJet( Event::Data& ev ){

  for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {
    if( isTrueTauMatchedToCommonJet(ev, (*igen) ) ){
      return true;
    }
  }
  return false;
}


// -----------------------------------------------------------------------------
//
bool TauFakeB::isTrueTauMatchedToCommonJet(  Event::Data& ev, const Event::GenObject& gob ){
  bool match=false;
  if( isTrueTauHad ( ev, gob ) ){
    int ma=0;
    for ( unsigned int ij=0; ij<ev.JD_CommonJets().accepted.size(); ij++ ) {
      if( IsMatched ( *( ev.JD_CommonJets().accepted.at(ij) ), gob, minDR_ ) ) {
	ma++;
      }
    }
    if( ma > 0 ) match=true;
  }
  return match;
}


// -----------------------------------------------------------------------------
//
bool TauFakeB::hasTrueTauHad( Event::Data& ev){

  for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {

    if( isTrueTauHad( ev, (*igen) ) ){
      return true;
    }
  }
  return false;
}


bool TauFakeB::hasTrueTauLep( Event::Data& ev){
  for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {
    
    if( isTrueTauLep( ev, (*igen) ) ){
      return true;
    }

  }
      return false;
}

// -----------------------------------------------------------------------------
//
bool TauFakeB::isTrueTauHad( Event::Data& ev, const Event::GenObject& gob ){
  bool ishad=false;

    //is on-shell
  if( gob.GetStatus() == 3 ) {

    if( fabs( gob.GetID() ) == 15 ){

      if( gob.Pt() > 0 && fabs( gob.Eta() ) < 15. ){

      //is not true tau lepton
        if( !isTrueTauLep( ev, gob ) ){

	  ishad = true;

	}
      }
    }
  }

  return ishad;
}


// -----------------------------------------------------------------------------
//
bool TauFakeB::isTrueTauLep( Event::Data& ev, const Event::GenObject& gob ){
  bool islep=false;

    //is on-shell
  if( gob.GetStatus() == 3 ) {

    //is a tau
     if( fabs( gob.GetID() ) == 15 ){

      //has lepton daughter
      int truetaulep=0;
      //      vector<int> dID=theDaughterID( &(ev), gob.GetIndex() );
      vector<int> dID=theDaughterID( &(ev), gob.GetID() );
      for( unsigned int i=0; i < dID.size(); i++ ){
	bool islepin=( fabs( dID[i] ) == 11 ) || ( fabs( dID[i] ) == 12 ) || ( fabs( dID[i] ) == 13 ) || ( fabs( dID[i] ) == 14 );

	if( islepin ){

	  truetaulep++;
	}
      }

      if( truetaulep > 0 ) islep=true;
    }
  }

  return islep;
}


// -----------------------------------------------------------------------------
//
std::vector<int> TauFakeB::theDaughterID(Event::Data * ev, int mID)//mID is motherID. if use index, it always GetMother()+2=input mother index
{
  std::vector<int> dtype;
  for ( std::vector<Event::GenObject>::const_iterator j = ev->GenParticles().begin();  j != ev->GenParticles().end(); ++j ) {

    //status can not be 3
    if( j->GetStatus()==3 ) continue;

    //has mother
    if( j->GetMother()!=-1 ){

      //mother ID
      //      if(j->GetMother()==index ) {dtype.push_back(j->GetID()); cout<<"ID="<<j->GetID()<<endl;}
      if( j->GetMotherID()==mID ) dtype.push_back( j->GetID() );
    }
  }
  return dtype;
}


// -----------------------------------------------------------------------------
//
//bool TauFakeB::IsMatched( LorentzV aParticle, const Event::GenObject& gob, float minDR){
double TauFakeB::MatchedDR( const Event::Jet &aParticle, const Event::GenObject& gob){

  return fabs(ROOT::Math::VectorUtil::DeltaR(gob,aParticle));
}


// -----------------------------------------------------------------------------
//
bool TauFakeB::IsMatched( const Event::Jet &aParticle, const Event::GenObject& gob, float minDR){
  bool isMatched = false;

  if( fabs(ROOT::Math::VectorUtil::DeltaR(gob,aParticle)) < minDR ){

    isMatched = true;
  }

  return isMatched;
}


// -----------------------------------------------------------------------------
//
vector<Event::GenObject> TauFakeB::theTrueTauHad( Event::Data& ev){

  vector<Event::GenObject> regob;

  //Loop all the GenObjects in the event
  for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {

    //If is a true tau had
    if( isTrueTauHad( ev, (*igen) ) ) {

      LorentzV gen = *igen;

      //loop all the GenObjects after the object's mother
      std::vector<Event::GenObject>::const_iterator igen_in1 = igen+1;
      vector<int> motherid=theTrueTauHadMotherIndex( ev, igen_in1 );

      for( unsigned int im=0; im<motherid.size(); im++){
	if( motherid[ im ] == (*igen).GetMother() ) {

	  gen+=(*igen_in1);

	}
      }

      int idx=(*igen).GetMother();
      int pid=(*igen).GetMotherID();
      int status=3;
      bool hasMother=ev.GenParticles().at(idx).GetMother()>=0 ? -1 : true;
      bool motherStored=ev.GenParticles().at(idx).GetMother()>=0 ? -1 : true;
      int mother=ev.GenParticles().at(idx).GetMother();
      int imotherid=ev.GenParticles().at(idx).GetMotherID();

      Event::GenObject ob=Event::GenObject(gen, idx, pid, status, hasMother, motherStored, mother, imotherid);
      regob.push_back( ob );

    }
  }
  return regob;
}
 

// -----------------------------------------------------------------------------
//
vector<int> TauFakeB::theTrueTauHadMotherIndex( Event::Data& ev, std::vector<Event::GenObject>::const_iterator igen_in ) { //Used to delete the hadronic production has the same tau mother which means duplicate

  vector<int> motherid;

  //Loop all the GenObjects in the event
  for( std::vector<Event::GenObject>::const_iterator igen = igen_in; igen != ev.GenParticles().end(); ++igen ) {

    //If is a true tau had
    if( isTrueTauHad( ev, (*igen) ) ) {

      //Push the mother index 
      motherid.push_back( (*igen).GetMother() );

    }
  }

  return motherid;

}


// -----------------------------------------------------------------------------
//
bool TauFakeB::hasTrueVLep( const Event::Data& ev ){

  for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {
    if( isTrueVLep( (*igen) ) ){
      return true;
    }
  }
  return false;
}


// -----------------------------------------------------------------------------
//
bool TauFakeB::isTrueVLep( const Event::GenObject& gob ){
  bool islep=false;
  if(gob.GetStatus() == 3 ) {
    if(fabs( gob.GetID() ) == 13 || fabs ( gob.GetID() ) == 11) {
      if(fabs( gob.GetMotherID() ) == 24 || fabs( gob.GetMotherID() ) == 23) {
	islep=true;
      }
    }
  }
  return islep;
}


// -----------------------------------------------------------------------------
//
bool TauFakeB::isTrueLep( const Event::GenObject& gob ){
  bool islep=false;

    //is on-shell
  if( gob.GetStatus() == 3 ) {

      //is lepton
    if( fabs( gob.GetID() ) == 13 || fabs ( gob.GetID() ) == 11 || fabs ( gob.GetID() ) == 12 || fabs ( gob.GetID() ) == 14 || fabs ( gob.GetID() ) == 16 ) {

      islep = true;
    }
  }
  return islep;
}


// -----------------------------------------------------------------------------
//
std::vector<Event::Jet> TauFakeB::TaggedBJetMatchToTrueTau( Event::Data& ev) {
  std::vector<Event::Jet> rejet;
  //loop all b=jets

  GenMatrixBin genbin=GenMatrixBin( &ev );

  for ( unsigned int ib=0; ib<ev.JD_CommonJets().accepted.size(); ib++ ) {

    if( ev.GetBTagResponse( ev.JD_CommonJets().accepted.at(ib)->GetIndex(), 4 ) > mCut_ ) {

      //loop all true particles
      for ( std::vector<Event::GenObject>::const_iterator itau=ev.GenParticles().begin(); itau != ev.GenParticles().end(); ++itau ) {

	  //is a hadronic tau
	if( isTrueTauHad ( ev, (*itau) ) ) {

	    //the b jet matched to a true had tau
	  if( IsMatched ( *(ev.JD_CommonJets().accepted.at(ib)), (*itau), minDR_) ) {

	    rejet.push_back( *(ev.JD_CommonJets().accepted.at(ib)) );

	  }
	}
      }
    }
  }
  return rejet;
}


