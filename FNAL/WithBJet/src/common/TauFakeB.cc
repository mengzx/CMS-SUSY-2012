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
  truetau_( ps.Get<bool>("trueTau") ),
  mode_( ps.Get<std::string>("mode") ),
  balgo_( ps.Get<int>("BTagAlgo") ),
  balgo_cut_( ps.Get<double>("BTagAlgoCut") ),
  usebtag_( ps.Get<bool>("useBTag") ),
  //tmp
  threshold_( ps.Get<double>("threshold_") ),
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

  double xbins[13]={75.,125.,175.,225.,275.,325.,375.,475.,575.,675.,775.,875.,975.};
  double ybins[9]={0., 0.10, 0.20, 0.50, 0.51, 0.52, 0.53, 0.55, 0.56};
  double zbins[17]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  int nxbins=12;
  int nybins=8;
  int nzbins=16;

  BookHistArray( AlphaT_Empty_h_,
		 "AlphaT_Empty_h",
		 "#alpha_{T} distribution of jets #geq 2",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );

  BookHistArray( njet_Empty_h_,
		 "njet_Empty_h",
		 "n-jets of jets #geq 2",
		 nzbins, zbins,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( nbjet_Empty_h_,
		 "nbjet_Empty_h",
		 "number of b-tagged jets of jets #geq 2",
		 nzbins, zbins,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_Empty_h_,
		 "HT_Empty_h",
		 "HT distribution of jets #geq 2",
		 1500, 0, 1500.,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_Empty_h_,
		 "AlphaT_vs_HT_Empty_h",
		 "#alpha_{T} vs HT of jets #geq 2",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );



  BookHistArray( nVertex_h_,
		 "nVertex_h",
		 "Number of Vertices",
		 50, 0, 50,
		 2, 0, 1, true );


  BookHistArray( totalEvents_h_,
		 "totalEvents_h",
		 "Total number of events",
		 2, 0, 2.,
		 2, 0, 1, true );


  BookHistArray( totalEvents_CommJet_h_,
		 "totalEvents_CommJet_h",
		 "Total number of events with jets #geq 2",
		 2, 0, 2.,
		 2, 0, 1, true );

  BookHistArray( totalEvents_CommObj_h_,
		 "totalEvents_CommObj_h",
		 "Total number of events with objects #geq 2",
		 2, 0, 2.,
		 2, 0, 1, true );


  //When njet >=2 -----------------------------
  size_t found=mode_.find("Muon_Add");
  cout<<" found found found "<<(int)(found)<<endl;
  if ( (int)(found) <= -1 ){
  BookHistArray( nVertex_CommJetgeq2_h_,
		 "nVertex_CommJetgeq2_h",
		 "Number of Vertices of jets #geq 2",
		 50, 0, 50,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );


    BookHistArray( MHToverMET_CommJetgeq2_h_,
		   "MHToverMET_CommJetgeq2_h",
		   "MHT/MET distribution of jets #geq 2",
		   1000, 0, 10.,
                   nybins, ybins,
		   nMax_+2, 0, 1, true );

    BookHistArray( MHT_CommJetgeq2_h_,
		   "MHT_CommJetgeq2_h",
		   "MHT distribution of jets #geq 2",
		   1500, 0, 1500.,
                   nybins, ybins,
		   nMax_+2, 0, 1, true );

    BookHistArray( MET_CommJetgeq2_h_,
		   "MET_CommJetgeq2_h",
		   "MET distribution of jets #geq 2",
		   1500, 0, 1500.,
                   nybins, ybins,
		   nMax_+2, 0, 1, true );

    BookHistArray( AlphaT_CommJetgeq2_h_,
		 "AlphaT_CommJetgeq2_h",
		 "#alpha_{T} distribution of jets #geq 2",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );

  BookHistArray( njet_CommJetgeq2_h_,
		 "njet_CommJetgeq2_h",
		 "n-jets of jets #geq 2",
		 nzbins, zbins,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( nbjet_CommJetgeq2_h_,
		 "nbjet_CommJetgeq2_h",
		 "number of b-tagged jets of jets #geq 2",
		 nzbins, zbins,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( TrueWPt_CommJetgeq2_h_,
		 "TrueWPt_CommJetgeq2_h",
		 "True W {p_{T}} distribution of jets #geq 2",
		 1500, 0, 1500.,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_CommJetgeq2_h_,
		 "HT_CommJetgeq2_h",
		 "HT distribution of jets #geq 2",
		 1500, 0, 1500.,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( muPt_CommJetgeq2_h_,
		 "muPt_CommJetgeq2_h",
		 "#mu p_{T} distribution of jets #geq 2",
		 1500, 0, 1500.,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( muPt2_CommJetgeq2_h_,
		 "muPt2_CommJetgeq2_h",
		 "Second #mu p_{T} distribution of jets #geq 2",
		 1500, 0, 1500.,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommJetgeq2_h_,
		 "AlphaT_vs_HT_CommJetgeq2_h",
		 "#alpha_{T} vs HT of jets #geq 2",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  if( !isData_ && truetau_ ){

  //AlphaT and HT distribution for event with tau->had
  BookHistArray( AlphaT_CommJetgeq2_hasTrueTauHad_h_,
		 "AlphaT_CommJetgeq2_hasTrueTauHad_h",
		 "#alpha_{T} distribution of jets #geq 2 and #tau_{h} > 0",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );

  BookHistArray( HT_CommJetgeq2_hasTrueTauHad_h_,
		 "HT_CommJetgeq2_hasTrueTauHad_h",
		 "HT distribution of jets #geq 2 and #tau_{h} > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_,
		 "AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h",
		 "#alpha_{T} vs HT of jets #geq 2 and #tau_{h} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );



  //AlphaT and HT distribution for event with tau->lep
  BookHistArray( AlphaT_CommJetgeq2_hasTrueTauLep_h_,
		 "AlphaT_CommJetgeq2_hasTrueTauLep_h",
		 "#alpha_{T} distribution of jets #geq 2 and #tau_{l} > 0",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );

  BookHistArray( HT_CommJetgeq2_hasTrueTauLep_h_,
		 "HT_CommJetgeq2_hasTrueTauLep_h",
		 "HT distribution of jets #geq 2 and #tau_{l} > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_,
		 "AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h",
		 "#alpha_{T} vs HT of jets #geq 2 and #tau_{l} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );



  //AlphaT and HT distribution for event with V->lep
  BookHistArray( AlphaT_CommJetgeq2_hasTrueVLep_h_,
		 "AlphaT_CommJetgeq2_hasTrueVLep_h",
		 "#alpha_{T} distribution of jets #geq 2 and lepton from W/Z > 0",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_CommJetgeq2_hasTrueVLep_h_,
		 "HT_CommJetgeq2_hasTrueVLep_h",
		 "HT distribution of jets #geq 2 and lepton from W/Z > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_,
		 "AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h",
		 "#alpha_{T} vs HT of jets #geq 2 and lepton from W/Z > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );



  //AlphaT and HT distribution for event with tau_had matched to jet
  BookHistArray( AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} distribution of jets #geq 2 and #tau_{had} matched to jet> 0",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "HT distribution of jets #geq 2 and #tau_{had} matched to jet> 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );




  BookHistArray( AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} vs HT of jets #geq 2 and #tau_{had} matched to jet> 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

    }
  }


  //When njet+mu >=2 -----------------------------
  if( (int)(found) >= 0 ){
  BookHistArray( nVertex_JetMugeq2_h_,
		 "nVertex_JetMugeq2_h",
		 "Number of Vertices of jets and #mu #geq 2",
		 50, 0, 50,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );


    BookHistArray( MHToverMET_JetMugeq2_h_,
		   "MHToverMET_JetMugeq3_h",
		   "MHT/MET distribution of jets and #mu #geq 2",
		   1000, 0, 10.,
                   nybins, ybins,
		   nMax_+2, 0, 1, true );

    BookHistArray( MHT_JetMugeq2_h_,
		   "MHT_JetMugeq2_h",
		   "MHT distribution of jets and #mu #geq 2",
		   1500, 0, 1500.,
                   nybins, ybins,
		   nMax_+2, 0, 1, true );

    BookHistArray( MET_JetMugeq2_h_,
		   "MET_JetMugeq2_h",
		   "MET distribution of jets and #mu #geq 2",
		   1500, 0, 1500.,
                   nybins, ybins,
		   nMax_+2, 0, 1, true );
   BookHistArray( AlphaT_JetMugeq2_h_,
		 "AlphaT_JetMugeq2_h",
		 "#alpha_{T} distribution of jets and #mu #geq 2",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );


  BookHistArray( njet_JetMugeq2_h_,
		 "njet_JetMugeq2_h",
		 "n-jets of jets and #mu #geq 2",
		 nzbins, zbins,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( nbjet_JetMugeq2_h_,
		 "nbjet_JetMugeq2_h",
		 "number of b-tagged jets of jets and #mu #geq 2",
		 nzbins, zbins,
		 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_JetMugeq2_h_,
		 "HT_JetMugeq2_h",
		 "HT distribution of jets and #mu #geq 2",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( muPt_JetMugeq2_h_,
		 "muPt_JetMugeq2_h",
		 "#mu p_{T} distribution of jets and #mu #geq 2",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( muPt2_JetMugeq2_h_,
		 "muPt2_JetMugeq2_h",
		 "Second #mu p_{T} distribution of jets and #mu #geq 2",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( HTTakeMu_JetMugeq2_h_,
		 "HTTakeMu_JetMugeq2_h",
		 "HT(#mu into) distribution of jets and #mu #geq 2",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_h_,
		 "AlphaT_vs_HT_JetMugeq2_h",
		 "#alpha_{T} vs HT of jets and #mu #geq 2",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_h",
		 "#alpha_{T} vs HT(#mu into) of jets and #mu #geq 2",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  if( !isData_ && truetau_ ){
  //AlphaT and HT distribution for event with tau->had
  BookHistArray( AlphaT_JetMugeq2_hasTrueTauHad_h_,
		 "AlphaT_JetMugeq2_hasTrueTauHad_h",
		 "#alpha_{T} distribution of jets and #mu #geq 2 and #tau_{h} > 0",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_JetMugeq2_hasTrueTauHad_h_,
		 "HT_JetMugeq2_hasTrueTauHad_h",
		 "HT distribution of jets and #mu #geq 2 and #tau_{h} > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_hasTrueTauHad_h_,
		 "HTTakeMu_JetMugeq2_hasTrueTauHad_h",
		 "HT(#mu into) distribution of jets and #mu #geq 2 and #tau_{h} > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_,
		 "AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h",
		 "#alpha_{T} vs HT of jets and #mu #geq 2 and #tau_{h} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h",
		 "#alpha_{T} vs HT(#mu into) of jets and #mu #geq 2 and #tau_{h} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );



  //AlphaT and HT distribution for event with tau->lep
  BookHistArray( AlphaT_JetMugeq2_hasTrueTauLep_h_,
		 "AlphaT_JetMugeq2_hasTrueTauLep_h",
		 "#alpha_{T} distribution of jets and #mu #geq 2 and #tau_{l} > 0",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_JetMugeq2_hasTrueTauLep_h_,
		 "HT_JetMugeq2_hasTrueTauLep_h",
		 "HT distribution of jets and #mu #geq 2 and #tau_{l} > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_hasTrueTauLep_h_,
		 "HTTakeMu_JetMugeq2_hasTrueTauLep_h",
		 "HT(#mu into) distribution of jets and #mu #geq 2 and #tau_{l} > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_,
		 "AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h",
		 "#alpha_{T} vs HT of jets and #mu #geq 2 and #tau_{l} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h",
		 "#alpha_{T} vs HT(#mu into) of jets and #mu #geq 2 and #tau_{l} > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );



  //AlphaT and HT distribution for event with V->lep
  BookHistArray( AlphaT_JetMugeq2_hasTrueVLep_h_,
		 "AlphaT_JetMugeq2_hasTrueVLep_h",
		 "#alpha_{T} distribution of jets and #mu #geq 2 and lepton from W/Z > 0",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_JetMugeq2_hasTrueVLep_h_,
		 "HT_JetMugeq2_hasTrueVLep_h",
		 "HT distribution of jets and #mu #geq 2 and lepton from W/Z > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_hasTrueVLep_h_,
		 "HTTakeMu_JetMugeq2_hasTrueVLep_h",
		 "HT(#mu into) distribution of jets and #mu #geq 2 and lepton from W/Z > 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_,
		 "AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h",
		 "#alpha_{T} vs HT of jets and #mu #geq 2 and lepton from W/Z > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h",
		 "#alpha_{T} vs HT(#mu into) of jets and #mu #geq 2 and lepton from W/Z > 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );



  //AlphaT and HT distribution for event with tau_had matched to jet
  BookHistArray( AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} distribution of jets and #mu #geq 2 #tau_{had} matched to jet> 0",
		 1000, 0, 10.,
		 nMax_+2, 0, 1, true );


  BookHistArray( HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "HT distribution of jets and #mu #geq 2 #tau_{had} matched to jet> 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "HT(#mu into) distribution of jets and #mu #geq 2 #tau_{had} matched to jet> 0",
		 1500, 0, 1500.,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );


  BookHistArray( AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} vs HT of jets and #mu #geq 2 #tau_{had} matched to jet> 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );

  BookHistArray( AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_,
		 "AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h",
		 "#alpha_{T} vs HT(#mu into) of jets and #mu #geq 2 #tau_{had} matched to jet> 0",
		 nxbins, xbins,
                 nybins, ybins,
		 nMax_+2, 0, 1, true );
   }
  }

  if( !isData_ && truetau_ ){
  BookHistArray( theTrueTauHad_And_CommonJet_DR_h_,
		 "theTrueTauHad_And_CommonJet_DR_h",
		 "#Delta R (true #tau_{had}, jet)",
		 1000, 0, 1.,
		 2, 0, 1, true );
  }

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

  double muonfirstPt = -1;
  double muonsecondPt = -1;
  if (ev.LD_CommonMuons().accepted.size() > 0) {
    muonfirstPt=ev.LD_CommonMuons().accepted.at(0)->Pt();
  }
  if (ev.LD_CommonMuons().accepted.size() > 1) {
    muonsecondPt=ev.LD_CommonMuons().accepted.at(1)->Pt();
  }
  unsigned int nbjet = 0;
  for(unsigned int i=0; i<ev.JD_CommonJets().accepted.size(); i++) {
  // std::cout << "we are on jet " << i << " the btag discriminator is " << ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), 4) << std::endl;
    if(ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), balgo_) > balgo_cut_) {
     nbjet++;
         //if we make it into here, the jet has passed the b-tag requirement
    } 
  }



  double commalphaT = ev.CommonAlphaT();
  double commHT = ev.CommonHT();
  double hadronicalphaT = ev.HadronicAlphaT();
  double hadronicalphaTTakeMu=ev.HadronicAlphaTTakeMu();
  double HTTakeMu = ev.CommonHTTakeMu();

  vector<double> CommAlphaTHT = setBin_CommonAlphaT_vs_HT( ev );
  vector<double> HadronicAlphaTHT = setBin_HadronicAlphaT_vs_HT( ev );
  vector<double> HadronicAlphaTTakeMuHTTakeMu = setBin_HadronicAlphaTTakeMu_vs_HTTakeMu( ev );
  vector<double> HadronicAlphaTTakeMuHT = setBin_HadronicAlphaTTakeMu_vs_HT( ev );

  vector<double> vmhtandmet=mhtandmet( ev );
  vector<double> vmhtTakeMuandmetTakeMu = mhtTakeMuandmetTakeMu( ev );
  int nVertex=verticesN( ev );

  //  cout<<"njet=="<<njet<<" njetandmu="<<njetandmu<<" nbjet="<<nbjet<<endl;
  cout<<"mode="<<mode_<<" mode_.find="<<mode_.find("Muon_Add")<< " int find=" <<(int)(mode_.find("Muon_Add")) <<endl;
  //  cout<<"mhtovermet="<<mhtovermet<<" calomet="<<calomet.Pt()<<"mHT.Pt()"<<mHT.Pt()<<endl;

  if ( StandardPlots_ ) {

    //total number of events

    nVertex_h_[0]->Fill(nVertex);
    nVertex_h_[1]->Fill(nVertex, weight);

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


  size_t found=mode_.find("Muon_Add");
  cout<<"found="<<found<< "int found "<<(int)(found)<<endl;
  if( (int)(found) <= -1 ){
    //When njet >= nMin_
    if( njet >= nMin_ && njet <= nMax_){

      //--------------------------------
      //
      //Fill AlphaT and HT
      if(1){

        if( njet < nVertex_CommJetgeq2_h_.size() ){
	  nVertex_CommJetgeq2_h_[0]->Fill(nVertex, HadronicAlphaTHT[1], weight);
          if( usebtag_ ){
	    nVertex_CommJetgeq2_h_[nbjet+1]->Fill(nVertex, HadronicAlphaTHT[1], weight);
	  } else {
	    nVertex_CommJetgeq2_h_[njet]->Fill(nVertex, HadronicAlphaTHT[1], weight);
	  }
	}

        if( njet < MET_CommJetgeq2_h_.size() ){
          MET_CommJetgeq2_h_[0]->Fill( vmhtandmet[1], HadronicAlphaTHT[1], weight );
          if( usebtag_ ){
            MET_CommJetgeq2_h_[nbjet+1]->Fill( vmhtandmet[1], HadronicAlphaTHT[1], weight );
          } else {
            MET_CommJetgeq2_h_[njet]->Fill( vmhtandmet[1], HadronicAlphaTHT[1], weight );
          }
        }

        if( njet < MHToverMET_CommJetgeq2_h_.size() ){
          MHToverMET_CommJetgeq2_h_[0]->Fill( vmhtandmet[2], HadronicAlphaTHT[1], weight );
          if( usebtag_ ){
            MHToverMET_CommJetgeq2_h_[nbjet+1]->Fill( vmhtandmet[2], HadronicAlphaTHT[1], weight );
          } else {
            MHToverMET_CommJetgeq2_h_[njet]->Fill( vmhtandmet[2], HadronicAlphaTHT[1], weight );
          }
        }

        if( njet < MHT_CommJetgeq2_h_.size() ){
          MHT_CommJetgeq2_h_[0]->Fill(vmhtandmet[0], HadronicAlphaTHT[1], weight );
          if( usebtag_ ){
            MHT_CommJetgeq2_h_[nbjet+1]->Fill( vmhtandmet[0], HadronicAlphaTHT[1], weight );
          } else {
            MHT_CommJetgeq2_h_[njet]->Fill( vmhtandmet[0], HadronicAlphaTHT[1], weight );
          }
        }

	if( njet < AlphaT_CommJetgeq2_h_.size() ){
	  AlphaT_CommJetgeq2_h_[0]->Fill( hadronicalphaT, weight );
	  if( usebtag_ ){
	    AlphaT_CommJetgeq2_h_[nbjet+1]->Fill( hadronicalphaT, weight );
	  } else{
	    AlphaT_CommJetgeq2_h_[njet]->Fill( hadronicalphaT, weight );
	  }
	}
	
	if( !isData_ && truetau_){
	  if( njet < TrueWPt_CommJetgeq2_h_.size() ){
	    vector<double> wpt=TrueWPt( ev );
	    for( unsigned int i=0; i< wpt.size(); i++ ){
	      TrueWPt_CommJetgeq2_h_[0]->Fill( wpt[i], HadronicAlphaTHT[1], weight );
	      if( usebtag_ ){
		TrueWPt_CommJetgeq2_h_[nbjet+1]->Fill( wpt[i], HadronicAlphaTHT[1], weight );
	      } else{
		TrueWPt_CommJetgeq2_h_[njet]->Fill( wpt[i], HadronicAlphaTHT[1], weight );
	      }
	    }
	  }
	}

	if( njet < njet_CommJetgeq2_h_.size() ){
	  njet_CommJetgeq2_h_[0]->Fill( njet, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    njet_CommJetgeq2_h_[nbjet+1]->Fill( njet, HadronicAlphaTHT[1], weight );
	  } else{
	    njet_CommJetgeq2_h_[njet]->Fill( njet, HadronicAlphaTHT[1], weight );
	  }
	}

	if( nbjet < njet_CommJetgeq2_h_.size() ){
	  nbjet_CommJetgeq2_h_[0]->Fill( nbjet, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    nbjet_CommJetgeq2_h_[nbjet+1]->Fill( nbjet, HadronicAlphaTHT[1], weight );
	  } else {
	    nbjet_CommJetgeq2_h_[njet]->Fill( nbjet, HadronicAlphaTHT[1], weight );
	  }
	}

	if( njet < HT_CommJetgeq2_h_.size() ){
	  HT_CommJetgeq2_h_[0]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    HT_CommJetgeq2_h_[nbjet+1]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  } else{
	    HT_CommJetgeq2_h_[njet]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  }
	}

	if( njet < muPt_CommJetgeq2_h_.size() ){
	  muPt_CommJetgeq2_h_[0]->Fill( muonfirstPt, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    muPt_CommJetgeq2_h_[nbjet+1]->Fill( muonfirstPt, HadronicAlphaTHT[1], weight );
	  } else{
	    muPt_CommJetgeq2_h_[njet]->Fill( muonfirstPt, HadronicAlphaTHT[1], weight );
	  }
	}

	if( njet < muPt2_CommJetgeq2_h_.size() ){
	  muPt2_CommJetgeq2_h_[0]->Fill( muonsecondPt, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    muPt2_CommJetgeq2_h_[nbjet+1]->Fill( muonsecondPt, HadronicAlphaTHT[1], weight );
	  } else{
	    muPt2_CommJetgeq2_h_[njet]->Fill( muonsecondPt, HadronicAlphaTHT[1], weight );
	  }
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_CommJetgeq2_h_[nbjet+1]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  } else {
	    AlphaT_vs_HT_CommJetgeq2_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  }
	}

      }       //Fill AlphaT and HT

      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had found
      if( !isData_ && truetau_ ){

      if( hasTrueTauHad( ev) ){

	if( njet < AlphaT_CommJetgeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_CommJetgeq2_hasTrueTauHad_h_[0]->Fill( hadronicalphaT, weight );
	  if( usebtag_ ){
	    AlphaT_CommJetgeq2_hasTrueTauHad_h_[nbjet+1]->Fill( hadronicalphaT, weight );
	  } else {
	    AlphaT_CommJetgeq2_hasTrueTauHad_h_[njet]->Fill( hadronicalphaT, weight );
	  }
	}

	if( njet < HT_CommJetgeq2_hasTrueTauHad_h_.size() ){
	  HT_CommJetgeq2_hasTrueTauHad_h_[0]->Fill(  commHT, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    HT_CommJetgeq2_hasTrueTauHad_h_[nbjet+1]->Fill(  commHT, HadronicAlphaTHT[1], weight );
	  } else {
	    HT_CommJetgeq2_hasTrueTauHad_h_[njet]->Fill(  commHT, HadronicAlphaTHT[1], weight );
	  }
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_[nbjet+1]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  } else{
	    AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  }
	}

      }      //Fill AlphaT and HT if tau_had found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_lep found
      if( hasTrueTauLep( ev) ){

	if( njet < AlphaT_CommJetgeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_CommJetgeq2_hasTrueTauLep_h_[0]->Fill( hadronicalphaT, weight );
	  if( usebtag_ ){
	    AlphaT_CommJetgeq2_hasTrueTauLep_h_[nbjet+1]->Fill( hadronicalphaT, weight );
	  } else{
	    AlphaT_CommJetgeq2_hasTrueTauLep_h_[njet]->Fill( hadronicalphaT, weight );
	  }
	}

	if( njet < HT_CommJetgeq2_hasTrueTauLep_h_.size() ){
	  HT_CommJetgeq2_hasTrueTauLep_h_[0]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    HT_CommJetgeq2_hasTrueTauLep_h_[nbjet+1]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  } else{
	    HT_CommJetgeq2_hasTrueTauLep_h_[njet]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  }
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_[nbjet+1]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  } else{
	    AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  }
	}

      }      //Fill AlphaT and HT if tau_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if V_lep found
      if( hasTrueVLep( ev) ){

	if( njet < AlphaT_CommJetgeq2_hasTrueVLep_h_.size() ){
	  AlphaT_CommJetgeq2_hasTrueVLep_h_[0]->Fill( hadronicalphaT, weight );
	  if( usebtag_ ){
	    AlphaT_CommJetgeq2_hasTrueVLep_h_[nbjet+1]->Fill( hadronicalphaT, weight );
	  } else{
	    AlphaT_CommJetgeq2_hasTrueVLep_h_[njet]->Fill( hadronicalphaT, weight );
	  }
	}

	if( njet < HT_CommJetgeq2_hasTrueVLep_h_.size() ){
	  HT_CommJetgeq2_hasTrueVLep_h_[0]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    HT_CommJetgeq2_hasTrueVLep_h_[nbjet+1]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  } else{
	    HT_CommJetgeq2_hasTrueVLep_h_[njet]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  }
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_[nbjet+1]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  } else{
	    AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  }
	}

      }      //Fill AlphaT and HT if V_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had mached to a jet is found
      if( hasTrueTauMatchedToCommonJet (ev) ){

	if( njet < AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( hadronicalphaT, weight );
	  if( usebtag_ ){
	    AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[nbjet+1]->Fill( hadronicalphaT, weight );
	  } else{
	    AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( hadronicalphaT, weight );
	  }
	}

	if( njet < HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  if( usebtag_ ){
	    HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[nbjet+1]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  } else{
	    HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( commHT, HadronicAlphaTHT[1], weight );
	  }
	}

	if(njet < AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[nbjet+1]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  } else{
	    AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( HadronicAlphaTHT[0], HadronicAlphaTHT[1], weight);
	  }
	}
      }      //Fill AlphaT and HT if tau_had mached to a jet is found

      }
      //++++++++++++++++++++++++
    }// if jet >= nMin

  } //mode


  if( (int)(found) >= 0 ){
    //When njet + nmu >= nMin_
    if( njetandmu >= nMin_ && njetandmu <= nMax_){

      //--------------------------------
      //
      //Fill AlphaT and HT
      if(1){
        if( njetandmu < nVertex_JetMugeq2_h_.size() ){
	  nVertex_JetMugeq2_h_[0]->Fill(nVertex, HadronicAlphaTTakeMuHTTakeMu[1], weight);
          if( usebtag_ ){
	    nVertex_JetMugeq2_h_[nbjet+1]->Fill(nVertex, HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  } else {
	    nVertex_JetMugeq2_h_[njet]->Fill(nVertex, HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  }
	}

	if( njetandmu < MET_JetMugeq2_h_.size() ){
          MET_JetMugeq2_h_[0]->Fill( vmhtTakeMuandmetTakeMu[1], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          if( usebtag_ ){
            MET_JetMugeq2_h_[nbjet+1]->Fill( vmhtTakeMuandmetTakeMu[1], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          } else {
            MET_JetMugeq2_h_[njet]->Fill( vmhtTakeMuandmetTakeMu[1], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          }
        }

        if( njetandmu < MHToverMET_JetMugeq2_h_.size() ){
          MHToverMET_JetMugeq2_h_[0]->Fill( vmhtTakeMuandmetTakeMu[2], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          if( usebtag_ ){
            MHToverMET_JetMugeq2_h_[nbjet+1]->Fill( vmhtTakeMuandmetTakeMu[2], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          } else {
            MHToverMET_JetMugeq2_h_[njet]->Fill( vmhtTakeMuandmetTakeMu[2], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          }
        }

        if( njetandmu < MHT_JetMugeq2_h_.size() ){
          MHT_JetMugeq2_h_[0]->Fill(vmhtTakeMuandmetTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          if( usebtag_ ){
            MHT_JetMugeq2_h_[nbjet+1]->Fill( vmhtTakeMuandmetTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          } else {
            MHT_JetMugeq2_h_[njet]->Fill( vmhtTakeMuandmetTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight );
          }
        }

	if( njetandmu < AlphaT_JetMugeq2_h_.size() ){
	  AlphaT_JetMugeq2_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  if( usebtag_ ){
	    AlphaT_JetMugeq2_h_[nbjet+1]->Fill( hadronicalphaTTakeMu, weight );
	  } else {
	    AlphaT_JetMugeq2_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	  }
	}
	
	if( njetandmu < njet_JetMugeq2_h_.size() ){
	  njet_JetMugeq2_h_[0]->Fill( njet, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  if( usebtag_ ){
	    njet_JetMugeq2_h_[nbjet+1]->Fill( njet, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  } else {
	    njet_JetMugeq2_h_[njet]->Fill( njet, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  }
	}

	if( njetandmu < nbjet_JetMugeq2_h_.size() ){
	  nbjet_JetMugeq2_h_[0]->Fill( nbjet, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  if( usebtag_ ){
	    nbjet_JetMugeq2_h_[nbjet+1]->Fill( nbjet, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  } else {
	    nbjet_JetMugeq2_h_[njet]->Fill( nbjet, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  }
	}

	if( njetandmu < HTTakeMu_JetMugeq2_h_.size() ){
	  HTTakeMu_JetMugeq2_h_[0]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  if( usebtag_ ){
	    HTTakeMu_JetMugeq2_h_[nbjet+1]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  } else {
	    HTTakeMu_JetMugeq2_h_[njet]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  }
	}

	if( njetandmu < HT_JetMugeq2_h_.size() ){
	  HT_JetMugeq2_h_[0]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  if( usebtag_ ){
	    HT_JetMugeq2_h_[nbjet+1]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  } else {
	    HT_JetMugeq2_h_[njet]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  }
	}

	if( njetandmu < muPt_JetMugeq2_h_.size() ){
	  muPt_JetMugeq2_h_[0]->Fill( muonfirstPt, HadronicAlphaTTakeMuHT[1], weight );
	  if( usebtag_ ){
	    muPt_JetMugeq2_h_[nbjet+1]->Fill( muonfirstPt, HadronicAlphaTTakeMuHT[1], weight );
	  } else {
	    muPt_JetMugeq2_h_[njet]->Fill( muonfirstPt, HadronicAlphaTTakeMuHT[1], weight );
	  }
	}

	if( njetandmu < muPt2_JetMugeq2_h_.size() ){
	  muPt2_JetMugeq2_h_[0]->Fill( muonsecondPt, HadronicAlphaTTakeMuHT[1], weight );
	  if( usebtag_ ){
	    muPt2_JetMugeq2_h_[nbjet+1]->Fill( muonsecondPt, HadronicAlphaTTakeMuHT[1], weight );
	  } else {
	    muPt2_JetMugeq2_h_[njet]->Fill( muonsecondPt, HadronicAlphaTTakeMuHT[1], weight );
	  }
	}

	if(njetandmu < AlphaT_vs_HT_JetMugeq2_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_JetMugeq2_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  } else {
	    AlphaT_vs_HT_JetMugeq2_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  }
	}

	if(njetandmu < AlphaT_vs_HTTakeMu_JetMugeq2_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HTTakeMu_JetMugeq2_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  } else {
	    AlphaT_vs_HTTakeMu_JetMugeq2_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  }
	}
      }       //Fill AlphaT and HT

      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had found
      if( !isData_ && truetau_ ){

      if( hasTrueTauHad( ev) ){

	if( njetandmu < AlphaT_JetMugeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_JetMugeq2_hasTrueTauHad_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  if( usebtag_ ){
	    AlphaT_JetMugeq2_hasTrueTauHad_h_[nbjet+1]->Fill( hadronicalphaTTakeMu, weight );
	  } else {
	    AlphaT_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	  }
	}
	
	if( njetandmu < HTTakeMu_JetMugeq2_hasTrueTauHad_h_.size() ){
	  HTTakeMu_JetMugeq2_hasTrueTauHad_h_[0]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  if( usebtag_ ){
	    HTTakeMu_JetMugeq2_hasTrueTauHad_h_[nbjet+1]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  } else {
	    HTTakeMu_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  }
	}

	if( njetandmu < HT_JetMugeq2_hasTrueTauHad_h_.size() ){
	  HT_JetMugeq2_hasTrueTauHad_h_[0]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  if( usebtag_ ){
	    HT_JetMugeq2_hasTrueTauHad_h_[nbjet+1]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  } else {
	    HT_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  }
	}

	if(njetandmu < AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  } else {
	    AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  }
	}

	if(njetandmu < AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  } else {
	    AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  }
	}

      }      //Fill AlphaT and HT if tau_had found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_lep found
      if( hasTrueTauLep( ev) ){

	if( njetandmu < AlphaT_JetMugeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_JetMugeq2_hasTrueTauLep_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  if( usebtag_ ){
	    AlphaT_JetMugeq2_hasTrueTauLep_h_[nbjet+1]->Fill( hadronicalphaTTakeMu, weight );
	  } else {
	    AlphaT_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	  }
	}
	
	if( njetandmu < HTTakeMu_JetMugeq2_hasTrueTauLep_h_.size() ){
	  HTTakeMu_JetMugeq2_hasTrueTauLep_h_[0]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  if( usebtag_ ){
	    HTTakeMu_JetMugeq2_hasTrueTauLep_h_[nbjet+1]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  } else {
	    HTTakeMu_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  }
	}

	if( njetandmu < HT_JetMugeq2_hasTrueTauLep_h_.size() ){
	  HT_JetMugeq2_hasTrueTauLep_h_[0]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  if( usebtag_ ){
	    HT_JetMugeq2_hasTrueTauLep_h_[nbjet+1]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  } else {
	    HT_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  }
	}

	if(njetandmu < AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  } else {
	    AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  }
	}

	if(njetandmu < AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  } else {
	    AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  }
	}

      }      //Fill AlphaT and HT if tau_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if V_lep found
      if( hasTrueVLep( ev) ){

	if( njetandmu < AlphaT_JetMugeq2_hasTrueVLep_h_.size() ){
	  AlphaT_JetMugeq2_hasTrueVLep_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  if( usebtag_ ){
	    AlphaT_JetMugeq2_hasTrueVLep_h_[nbjet+1]->Fill( hadronicalphaTTakeMu, weight );
	  } else {
	    AlphaT_JetMugeq2_hasTrueVLep_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	  }
	}
	
	if( njetandmu < HTTakeMu_JetMugeq2_hasTrueVLep_h_.size() ){
	  HTTakeMu_JetMugeq2_hasTrueVLep_h_[0]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  if( usebtag_ ){
	    HTTakeMu_JetMugeq2_hasTrueVLep_h_[nbjet+1]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  } else {
	    HTTakeMu_JetMugeq2_hasTrueVLep_h_[njet]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  }
	}

	if( njetandmu < HT_JetMugeq2_hasTrueVLep_h_.size() ){
	  HT_JetMugeq2_hasTrueVLep_h_[0]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  if( usebtag_ ){
	    HT_JetMugeq2_hasTrueVLep_h_[nbjet+1]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  } else {
	    HT_JetMugeq2_hasTrueVLep_h_[njet]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  }
	}

	if(njetandmu < AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  } else {
	    AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  }
	}

	if(njetandmu < AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  } else {
	    AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  }
	}

      }      //Fill AlphaT and HT if V_lep found


      //--------------------------------
      //
      //Fill AlphaT and HT if tau_had mached to a jet is found
      if( hasTrueTauMatchedToCommonJet (ev) ){

	if( njetandmu < AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( hadronicalphaTTakeMu, weight );
	  if( usebtag_ ){
	    AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[nbjet+1]->Fill( hadronicalphaTTakeMu, weight );
	  } else {
	    AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( hadronicalphaTTakeMu, weight );
	  }
	}
	
	if( njetandmu < HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  if( usebtag_ ){
	    HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[nbjet+1]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  } else {
	    HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( HTTakeMu, HadronicAlphaTTakeMuHTTakeMu[1], weight );
	  }
	}

	if( njetandmu < HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  if( usebtag_ ){
	    HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[nbjet+1]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  } else {
	    HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( commHT, HadronicAlphaTTakeMuHT[1], weight );
	  }
	}

	if(njetandmu < AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  } else {
	    AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( HadronicAlphaTTakeMuHT[0], HadronicAlphaTTakeMuHT[1], weight);
	  }
	}

	if(njetandmu < AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_.size() ){
	  AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[0]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  if( usebtag_ ){
	    AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[nbjet+1]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  } else {
	    AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_[njet]->Fill( HadronicAlphaTTakeMuHTTakeMu[0], HadronicAlphaTTakeMuHTTakeMu[1], weight);
	  }
	}
      }      //Fill AlphaT and HT if tau_had mached to a jet is found

      }
      //++++++++++++++++++++++++
    }// if jet + mu>= nMin
  }//mode


    //True tau-had distance to common jets (DR)
    if( !isData_ && truetau_ ){
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
  revalue.push_back(tmpHT);
  revalue.push_back(tmpAlphaT);

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

  revalue.push_back(tmpHT);
  revalue.push_back(tmpAlphaT);

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

  revalue.push_back(tmpHT);
  revalue.push_back(tmpAlphaT);

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

  revalue.push_back(tmpHT);
  revalue.push_back(tmpAlphaT);

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
vector<double> TauFakeB::TrueWPt( const Event::Data& ev ){
  vector<double> WPt;
  for( std::vector<Event::GenObject>::const_iterator igen = ev.GenParticles().begin(); igen != ev.GenParticles().end(); ++igen ) {
    if( isTrueW( (*igen) ) ){
      WPt.push_back( (*igen).Pt() );
    }
  }
  return WPt;
}

bool TauFakeB::isTrueW( const Event::GenObject& gob ){
  bool isW=false;
  if(gob.GetStatus() == 3 ) {
    if(fabs( gob.GetID() ) == 24 ) {
      isW=true;
    }
  }
  return isW;
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



vector<double> TauFakeB::mhtandmet( Event::Data& ev ){

  vector<double> rev;

  PolarLorentzV mHT(0.,0.,0.,0.);
  std::vector<Event::Jet const *>::const_iterator ijet = ev.JD_CommonJets().accepted.begin();
  std::vector<Event::Jet const *>::const_iterator jjet = ev.JD_CommonJets().accepted.end();
  std::vector<Event::Jet const *>::const_iterator ibaby = ev.JD_CommonJets().baby.begin();
  std::vector<Event::Jet const *>::const_iterator jbaby = ev.JD_CommonJets().baby.end();

  for(; ijet!=jjet; ++ijet){
    if( (*ijet)->Pt() > threshold_ ){
      mHT -= (**ijet);
    }
  }
  for( ; ibaby!=jbaby; ++ibaby){
    if( (*ibaby)->pt() > threshold_ ){
      mHT -= (**ibaby);
    }
  }

  LorentzV calomet = LorentzV(*ev.metP4calo());
  //  LorentzV calomet = LorentzV(*ev.metP4caloTypeI());

  for(int i = 0; i < int(ev.LD_CommonElectrons().accepted.size());i++){
    calomet = calomet+(*ev.LD_CommonElectrons().accepted[i]);
  }
  for(int i = 0; i < int(ev.PD_CommonPhotons().accepted.size());i++){
    calomet = calomet+(*ev.PD_CommonPhotons().accepted[i]);
  }
  for(int i = 0; i < int(ev.LD_CommonMuons().accepted.size());i++){
    calomet = calomet+(*ev.LD_CommonMuons().accepted[i]);
  }

  double mhtovermet = mHT.Pt()/calomet.Pt();

  rev.push_back(mHT.Pt());
  rev.push_back(calomet.Pt());
  rev.push_back( mhtovermet );
  return rev;
}


vector<double> TauFakeB::mhtTakeMuandmetTakeMu( Event::Data& ev ){

  PolarLorentzV mHTTakeMu(0.,0.,0.,0.);
  std::vector<Event::Jet const *>::const_iterator ijet = ev.JD_CommonJets().accepted.begin();
  std::vector<Event::Jet const *>::const_iterator jjet = ev.JD_CommonJets().accepted.end();
  std::vector<Event::Jet const *>::const_iterator ibaby = ev.JD_CommonJets().baby.begin();
  std::vector<Event::Jet const *>::const_iterator jbaby = ev.JD_CommonJets().baby.end();

  for(; ijet!=jjet; ++ijet){
    if( (*ijet)->Pt() > threshold_ ){
      mHTTakeMu -= (**ijet);
    }
  }
  for( ; ibaby!=jbaby; ++ibaby){
    if( (*ibaby)->pt() > threshold_ ){
      mHTTakeMu -= (**ibaby);
    }
  }
  std::vector<Event::Lepton const *>::const_iterator imu=ev.LD_CommonMuons().accepted.begin();
  std::vector<Event::Lepton const *>::const_iterator jmu=ev.LD_CommonMuons().accepted.end();
  for(; imu!=jmu; ++imu){
    mHTTakeMu -= (**imu);
  }


  LorentzV calometTakeMu = LorentzV(*ev.metP4calo());
  //  LorentzV calometTakeMu = LorentzV(*ev.metP4caloTypeI());

  for(int i = 0; i < int(ev.LD_CommonElectrons().accepted.size());i++){
    calometTakeMu = calometTakeMu+(*ev.LD_CommonElectrons().accepted[i]);
  }
  for(int i = 0; i < int(ev.PD_CommonPhotons().accepted.size());i++){
    calometTakeMu = calometTakeMu+(*ev.PD_CommonPhotons().accepted[i]);
  }

  double mhtTakeMuovermetTakeMu = mHTTakeMu.Pt()/calometTakeMu.Pt();

  vector<double> rev;
  rev.push_back( mHTTakeMu.Pt() );
  rev.push_back( calometTakeMu.Pt() );
  rev.push_back( mhtTakeMuovermetTakeMu );
  return rev;

}

int TauFakeB::verticesN( Event::Data& ev ){
  int nVertex=0;
  for(std::vector<float>::const_iterator vtx= ev.vertexSumPt()->begin();vtx != ev.vertexSumPt()->end();++vtx){
    if(!ev.vertexIsFake()->at( vtx-ev.vertexSumPt()->begin()) && 
       fabs((ev.vertexPosition()->at( vtx-ev.vertexSumPt()->begin())).Z()) < 24.0 &&
       ev.vertexNdof()->at( vtx-ev.vertexSumPt()->begin() ) > 4 &&
       (ev.vertexPosition()->at( vtx-ev.vertexSumPt()->begin())).Rho() < 2.0 ){
      nVertex++;
    }
  } 
  return nVertex;
}


