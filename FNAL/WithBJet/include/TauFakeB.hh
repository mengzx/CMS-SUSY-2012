#ifndef hadronic_TauFakeB_hh
#define hadronic_TauFakeB_hh

#include "PlottingBase.hh"
#include "Utils.hh"
#include "Types.hh"
#include "JetData.hh"
#include "EventData.hh"
#include "GenObject.hh"
class TH1D;
class TH2D;

namespace Operation {

  class TauFakeB : public PlottingBase {

  public:

    TauFakeB( const Utils::ParameterSet& );
    ~TauFakeB();

    void Start( Event::Data& );
    bool Process( Event::Data& );

    std::ostream& Description( std::ostream& );

  private:

    void BookHistos();
    std::string dirName_;
    UInt_t nMin_;
    UInt_t nMax_;

    double minDR_;
    double mCut_;

    bool isData_;
    bool truetau_;
    bool usebtag_;
    std::string mode_;
    int balgo_;
    double balgo_cut_;
    double threshold_;

    vector<double> setBin_CommonAlphaT_vs_HT( Event::Data& ev );
    vector<double> setBin_HadronicAlphaT_vs_HT( Event::Data& ev );
    vector<double> setBin_HadronicAlphaTTakeMu_vs_HT( Event::Data& ev );
    vector<double> setBin_HadronicAlphaTTakeMu_vs_HTTakeMu( Event::Data& ev );
    bool hasTrueTauMatchedToCommonJet( Event::Data& ev );
    bool isTrueTauMatchedToCommonJet( Event::Data& ev, const Event::GenObject& gob );
    bool hasTrueTauHad( Event::Data& ev );
    bool hasTrueTauLep( Event::Data& ev );
    vector<Event::GenObject>  theTrueTauHad( Event::Data& ev );
    vector<int> theTrueTauHadMotherIndex(  Event::Data& ev, std::vector<Event::GenObject>::const_iterator igen_in );
    bool isTrueTauHad( Event::Data& ev, const Event::GenObject& gob );
    bool isTrueW( const Event::GenObject& gob );
    vector<double> TrueWPt( const Event::Data& ev );
    bool isTrueTauLep( Event::Data& ev, const Event::GenObject& gob );
    bool hasTrueVLep( const Event::Data& ev );
    bool isTrueVLep( const Event::GenObject& gob );
    bool isTrueLep( const Event::GenObject& gob );
    std::vector<int> theDaughterID(Event::Data * ev, int mID);
    double MatchedDR( const Event::Jet& aParticle, const Event::GenObject& gob);
    bool IsMatched( const Event::Jet& aParticle, const Event::GenObject& gob, float minDR);
    std::vector<Event::Jet> TaggedBJetMatchToTrueTau( Event::Data& ev);
    std::vector<double> mhtandmet( Event::Data& ev );
    std::vector<double> mhtTakeMuandmetTakeMu( Event::Data& ev );
    int verticesN( Event::Data& ev );


    bool StandardPlots_;

    std::vector<TH1D*> AlphaT_Empty_h_;
    std::vector<TH2D*> njet_Empty_h_;
    std::vector<TH2D*> nbjet_Empty_h_;
    std::vector<TH2D*> HT_Empty_h_;
    std::vector<TH2D*> AlphaT_vs_HT_Empty_h_;

    std::vector<TH1D*> totalEvents_h_;
    std::vector<TH1D*> nVertex_h_;
    std::vector<TH1D*> totalEvents_CommJet_h_;
    std::vector<TH1D*> totalEvents_CommObj_h_;

    std::vector<TH2D*> nVertex_CommJetgeq2_h_;
    std::vector<TH2D*> MHToverMET_CommJetgeq2_h_;
    std::vector<TH2D*> MET_CommJetgeq2_h_;
    std::vector<TH2D*> MHT_CommJetgeq2_h_;
    std::vector<TH1D*> AlphaT_CommJetgeq2_h_;
    std::vector<TH2D*> TrueWPt_CommJetgeq2_h_;
    std::vector<TH2D*> njet_CommJetgeq2_h_;
    std::vector<TH2D*> nbjet_CommJetgeq2_h_;
    std::vector<TH2D*> HT_CommJetgeq2_h_;
    std::vector<TH2D*> muPt_CommJetgeq2_h_;
    std::vector<TH2D*> muPt2_CommJetgeq2_h_;
    std::vector<TH2D*> AlphaT_vs_HT_CommJetgeq2_h_;
    std::vector<TH1D*> AlphaT_CommJetgeq2_hasTrueTauHad_h_;
    std::vector<TH2D*> HT_CommJetgeq2_hasTrueTauHad_h_;
    std::vector<TH2D*> AlphaT_vs_HT_CommJetgeq2_hasTrueTauHad_h_;
    std::vector<TH1D*> AlphaT_CommJetgeq2_hasTrueTauLep_h_;
    std::vector<TH2D*> HT_CommJetgeq2_hasTrueTauLep_h_;
    std::vector<TH2D*> AlphaT_vs_HT_CommJetgeq2_hasTrueTauLep_h_;
    std::vector<TH1D*> AlphaT_CommJetgeq2_hasTrueVLep_h_;
    std::vector<TH2D*> HT_CommJetgeq2_hasTrueVLep_h_;
    std::vector<TH2D*> AlphaT_vs_HT_CommJetgeq2_hasTrueVLep_h_;
    std::vector<TH1D*> AlphaT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_;
    std::vector<TH2D*> HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_;
    std::vector<TH2D*> AlphaT_vs_HT_CommJetgeq2_hasTrueTauHadMatchedToCommJet_h_;


    std::vector<TH2D*> nVertex_JetMugeq2_h_;
    std::vector<TH2D*> MHToverMET_JetMugeq2_h_;
    std::vector<TH2D*> MET_JetMugeq2_h_;
    std::vector<TH2D*> MHT_JetMugeq2_h_;
    std::vector<TH1D*> AlphaT_JetMugeq2_h_;
    std::vector<TH2D*> HTTakeMu_JetMugeq2_h_;
    std::vector<TH2D*> njet_JetMugeq2_h_;
    std::vector<TH2D*> nbjet_JetMugeq2_h_;
    std::vector<TH2D*> HT_JetMugeq2_h_;
    std::vector<TH2D*> muPt_JetMugeq2_h_;
    std::vector<TH2D*> muPt2_JetMugeq2_h_;
    std::vector<TH2D*> AlphaT_vs_HT_JetMugeq2_h_;
    std::vector<TH2D*> AlphaT_vs_HTTakeMu_JetMugeq2_h_;
    std::vector<TH1D*> AlphaT_JetMugeq2_hasTrueTauHad_h_;
    std::vector<TH2D*> HTTakeMu_JetMugeq2_hasTrueTauHad_h_;
    std::vector<TH2D*> HT_JetMugeq2_hasTrueTauHad_h_;
    std::vector<TH2D*> AlphaT_vs_HT_JetMugeq2_hasTrueTauHad_h_;
    std::vector<TH2D*> AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHad_h_;
    std::vector<TH1D*> AlphaT_JetMugeq2_hasTrueTauLep_h_;
    std::vector<TH2D*> HTTakeMu_JetMugeq2_hasTrueTauLep_h_;
    std::vector<TH2D*> HT_JetMugeq2_hasTrueTauLep_h_;
    std::vector<TH2D*> AlphaT_vs_HT_JetMugeq2_hasTrueTauLep_h_;
    std::vector<TH2D*> AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauLep_h_;
    std::vector<TH1D*> AlphaT_JetMugeq2_hasTrueVLep_h_;
    std::vector<TH2D*> HTTakeMu_JetMugeq2_hasTrueVLep_h_;
    std::vector<TH2D*> HT_JetMugeq2_hasTrueVLep_h_;
    std::vector<TH2D*> AlphaT_vs_HT_JetMugeq2_hasTrueVLep_h_;
    std::vector<TH2D*> AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueVLep_h_;
    std::vector<TH1D*> AlphaT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_;
    std::vector<TH2D*> HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_;
    std::vector<TH2D*> HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_;
    std::vector<TH2D*> AlphaT_vs_HT_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_;
    std::vector<TH2D*> AlphaT_vs_HTTakeMu_JetMugeq2_hasTrueTauHadMatchedToCommJet_h_;

    std::vector<TH1D*> theTrueTauHad_And_CommonJet_DR_h_;

    void StandardPlots();
    bool StandardPlots( Event::Data& );

  };

}

#endif //TauFakeB_hh
