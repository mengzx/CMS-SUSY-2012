#ifndef hadronic_include_WeeklyUpdatePlots_hh
#define hadronic_include_WeeklyUpdatePlots_hh

#include "PlottingBase.hh"
#include "Utils.hh"
#include "Types.hh"

class TH1D;
class TH2D;

namespace Operation {

  class WeeklyUpdatePlots : public PlottingBase {

  public:

    WeeklyUpdatePlots( const Utils::ParameterSet& );
    ~WeeklyUpdatePlots();

    void Start( Event::Data& );
    bool Process( Event::Data& );

    std::ostream& Description( std::ostream& );

  private:

    void BookHistos();
    Double_t MT2( Event::Data& );
    Double_t MT2_Leading( Event::Data& );
    Double_t DeltaHT( Event::Data& );
    std::pair<LorentzV,LorentzV> PsudoJets(Event::Data&);
    std::string dirName_;
    UInt_t nMin_;
    UInt_t nMax_;

    bool StandardPlots_;
    std::vector<TH1D*>  DPhi_MHT_MHTBaby_;
    std::vector<TH1D*>  DPhi_MET_MHTBaby_;
    std::vector<TH1D*>  DPhi_MET_MHT_;
    std::vector<TH1D*>  MHToverHT_;
    std::vector<TH1D*>  MissedHT_;
    std::vector<TH1D*>  HT_forRatio_;
    std::vector<TH1D*>  BiasedDphi_;
    std::vector<TH2D*>  HT_vs_AlphaT_Hadronic_;
    std::vector<TH1D*>  AlphatCut_BiasedDphi_;
    std::vector<TH1D*>  DetlaPhi_LeadingJets_;
    std::vector<TH1D*>  DetlaPhi_NextToLeadingJets_;
    std::vector<TH1D*>  Meff_;
    std::vector<TH1D*>  AlphaT_;
    std::vector<TH1D*>  AlphaT_Zoomed_;
    std::vector<TH1D*>  vertexPtovHT_;
    std::vector<TH1D*>  MHT_;
    std::vector<TH1D*>  HT_;
    std::vector<TH1D*>  AlphatCut_Meff_;
    std::vector<TH1D*>  AlphatCut_HT_;
    std::vector<TH1D*>  Multiplicity_;
    std::vector<TH1D*>  JetPt_;
    std::vector<TH1D*>  JetEta_;
    std::vector<TH1D*>  AlphaT_METCut_;
    std::vector<TH1D*>  DPhi_MHT_MHTbaby_AfterAlphaT_;

    std::vector<TH2D*>  AlphaT_components_;
    std::vector<TH1D*>  MultiplicityAfteraT_;
    std::vector<TH1D*>  MHTovMET_;
    std::vector<TH1D*>  NumberVerticies_;
    std::vector<TH1D*>  NumberVerticiesAfterAlphaT_;
    std::vector<TH1D*>  hLepPt_;
    std::vector<TH1D*>  hSecondLepPt_;
    std::vector<TH1D*>  hLepTrIso_;
    std::vector<TH1D*>  hSecondLepTrIso_;
    std::vector<TH1D*>  hLepEIso_;
    std::vector<TH1D*>  hSecondLepEIso_;
    std::vector<TH1D*>  hLepHIso_;
    std::vector<TH1D*>  hSecondLepHIso_;
    std::vector<TH1D*>  hLepCIso_;
    std::vector<TH1D*>  hSecondLepCIso_;
    std::vector<TH1D*>  hMT_;
    std::vector<TH1D*>  BtagPreAlphaT_4_;
    std::vector<TH1D*>  BtagAfterAlphaT_4_;
    std::vector<TH1D*>  BtagPreAlphaT_5_;
    std::vector<TH1D*>  BtagAfterAlphaT_5_;
    std::vector<TH2D*> MinBiasDphi_EtaPhiMap_;

    std::vector<TH1D*> AlphatBefore_HT_;
    // //DeadECAL Plots
    // std::vector<TH1D*>  BiasedDphi_;
    // std::vector<TH1D*> BadJetECALDR_;
    // std::vector<TH1D*> allMinECALDR_;
    // std::vector<TH1D*> TPMHT_;
    // std::vector<TH1D*> TPHT_;
    // std::vector<TH1D*> TPMHTRatio_;
    // std::vector<TH2D*> TPHT_vs_BadJetECALDR_;

    void StandardPlots();
    bool StandardPlots( Event::Data& );

  };

}

#endif // hadronic_include_WeeklyUpdatePlots_hh
