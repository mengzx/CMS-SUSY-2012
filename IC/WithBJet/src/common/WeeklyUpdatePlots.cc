#include "WeeklyUpdatePlots.hh"
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

using namespace Operation;

// -----------------------------------------------------------------------------
WeeklyUpdatePlots::WeeklyUpdatePlots( const Utils::ParameterSet& ps ) :
// Misc
dirName_( ps.Get<std::string>("DirName") ),
  nMin_( ps.Get<int>("MinObjects") ),
  nMax_( ps.Get<int>("MaxObjects") ),
// MT2
  StandardPlots_( ps.Get<bool>("StandardPlots") )

  {}

// -----------------------------------------------------------------------------
//
WeeklyUpdatePlots::~WeeklyUpdatePlots() {}

// -----------------------------------------------------------------------------
//
void WeeklyUpdatePlots::Start( Event::Data& ev ) {
  initDir( ev.OutputFile(), dirName_.c_str() );
  BookHistos();
}

// -----------------------------------------------------------------------------
//
void WeeklyUpdatePlots::BookHistos() {
  if ( StandardPlots_ )           { StandardPlots(); }
}

// -----------------------------------------------------------------------------
//
bool WeeklyUpdatePlots::Process( Event::Data& ev ) {
  if ( StandardPlots_ )               { StandardPlots(ev); }
  return true;
}

// -----------------------------------------------------------------------------
//
std::ostream& WeeklyUpdatePlots::Description( std::ostream& ostrm ) {
  ostrm << "Hadronic Common Plots ";
  ostrm << "(bins " << nMin_ << " to " << nMax_ << ") ";
  return ostrm;
}

// -----------------------------------------------------------------------------
//
void WeeklyUpdatePlots::StandardPlots() {




  BookHistArray( vertexPtovHT_,
    "vertexPtovHT",
    ";VertexPt / HT (GeV);Events/0.01;",
    1000, 0., 10.,
    nMax_+1, 0, 1, true );

  BookHistArray( NumberVerticiesAfterAlphaT_,
    "Number_Primary_verticies_after_alphaT",
    ";No.Vertercies;Events;",
    10,0.,10,
    nMax_+1, 0, 1, true );

  BookHistArray( NumberVerticies_,
    "Number_Primary_verticies_",
    ";No.Vertercies;Events;",
    10,0.,10,
    nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_components_,
    "AlphaT_Components",
    ";#slashed{H}_{T}/H_{T};#Delta)H_{T}/H_{T}",
    20, 0., 1.,
    20, 0., 1.,
    nMax_+1, 0, 1, true );

  BookHistArray( DPhi_MHT_MHTBaby_,
    "CosDetlaPhi_MHT_MHTBaby_",
    ";#Delta Cos#phi(MHT,MHTbaby); Events/0.65 rad;",
    40, -1., 1,
    nMax_+1, 0, 1, true );

  BookHistArray( DPhi_MHT_MHTbaby_AfterAlphaT_,
    "DPhi_MHT_MHTbaby_AfterAlphaT_",
    ";Cos #Delta #phi(MHT,MHTbaby); Events/0.65 rad;",
    40, -1., 1.,
    nMax_+1, 0, 1, true );

  BookHistArray( MinBiasDphi_EtaPhiMap_,
    "MinBiasDphi_EtaPhiMap_",
    ";#eta;#phi",
    60, -3., 3.,
    64, -3.2, 3.2,
    nMax_+1, 0, 1, true );


  BookHistArray( MissedHT_,
    "MHTRatio_after_alphaT_55",
    ";MHT30/MHT10;Events/0.1;",
    100, 0., 10,
    nMax_+1, 0, 1, true );

  BookHistArray( MHTovMET_,
    "MHTovMET_afterAlphaT",
    ";MHT/MET;Events/0.1;",
    1000, 0., 100,
    nMax_+1, 0, 1, true );

  BookHistArray( DetlaPhi_LeadingJets_,
    "DetlaPhi_LeadingJets_",
    ";#Delta #phi(j_{1},j_{i}); Events/0.65 rad;",
    40, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );

  BookHistArray( DetlaPhi_NextToLeadingJets_,
    "DetlaPhi_NextToLeadingJets_",
    ";#Delta #phi(j_{2},j_{3}); Events/0.65 rad;",
    40, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );


  BookHistArray( AlphaT_,
    "AlphaT",
    ";#alpha_{T};Events/0.025;",
    1000,0.,10.,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_Zoomed_,
    "AlphaT_Zoomed",
    ";#alpha_{T}; Events/0.0025;",
    60,0.45,0.6,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphaT_METCut_,
    "AlphaT_after_MHTRatio",
    ";#alpha_{T};Events/0.025;",
    400,0.,10.,
    nMax_+1, 0, 1, true );



  BookHistArray( AlphatCut_Meff_,
    "EffectiveMass_after_alphaT_55",
    ";M_{eff} (GeV); Events/40 GeV;",
    75, 0., 3000.,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphatCut_HT_,
    "HT_after_alphaT",
    ";H_{T} (GeV); Events/25 (GeV);",
    80,0.,2000.,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphatBefore_HT_,
    "HT_before_alphaT",
    ";H_{T} (GeV); Events/25 (GeV);",
    80,0.,2000.,
    nMax_+1, 0, 1, true );

  BookHistArray( HT_,
    "HT",
    ";H_{T} (GeV); Events/25 GeV;",
    100,0.,2500.,
    nMax_+1, 0, 1, true );

  BookHistArray( HT_vs_AlphaT_Hadronic_,
    "HT_vs_AlphaT_Hadronic",
    ";H_{T} (GeV);#alpha_{T};",
    100,0.,2500.,500,0.,5.,
    nMax_+1, 0, 1, true );


  BookHistArray( Meff_,
    "EffectiveMass",
    ";M_{eff} (GeV); Events/40 GeV;",
    75, 0., 3000.,
    nMax_+1, 0, 1, true );

  BookHistArray( AlphatCut_BiasedDphi_,
    "BiasedDeltaPhi_after_alphaT_55",
    ";#Delta #phi^{*} (rad); Events/0.05 rad;",
    60, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );

  BookHistArray( BiasedDphi_,
    "BiasedDeltaPhi",
    ";#Delta #phi^{*} (rad); Events/0.05 rad;",
    60, 0., TMath::Pi(),
    nMax_+1, 0, 1, true );

  BookHistArray( MHToverHT_,
    "MHToverHT",
    ";#slash{H}_{T}/H_{T};Events/0.025;",
    40,0.,1.,
    nMax_+1, 0, 1, true );

  BookHistArray( MHT_,
    "MHT",
    ";#slash{H}_{T} (GeV); Events/10 GeV;",
    60,0.,600.,
    nMax_+1, 0, 1, true );

  BookHistArray( HT_forRatio_,
    "HT_forRatioPlots",
    ";H_{T} (GeV); Events/25 GeV;",
    80,0.,2000.,
    nMax_+1, 0, 1, true );

  BookHistArray( MultiplicityAfteraT_,
    "JetMultiplicityAfterAlphaT",
    ";n",
    15,0.,15.,
    nMax_+1, 0, 1, true );

  BookHistArray( Multiplicity_,
    "JetMultiplicity",
    ";n",
    15,0.,15.,
    nMax_+1, 0, 1, true );

  BookHistArray( JetEta_,
    "JetEta_",
    ";#eta ; Events/1 eta;",
    60,-5.,5.,
    nMax_+1, 0, 1, true );

  BookHistArray( JetPt_,
    "JetPt_",
    ";GeV ; Events/1 eta ",
    75,0.,1500.,
    nMax_+1, 0, 1, true );

  BookHistArray( hLepPt_,
    "MuPt_",
    ";P_{T} [GeV];",
    2000,10.,2010.,
    nMax_+1, 0, 1, true );


  BookHistArray( hSecondLepPt_,
    "Second_MuPt_",
    ";P_{T} [GeV];",
    2000,10.,2010.,
    nMax_+1, 0, 1, true );

  BookHistArray( hLepTrIso_,
    "MuTrIso_",
    ";Trk Iso;",
    2000,0.,2.,
    nMax_+1, 0, 1, true );


  BookHistArray( hLepEIso_,
    "MuEIso_",
    ";E Iso;",
    2000,0.,2.,
    nMax_+1, 0, 1, true );


  BookHistArray( hLepHIso_,
    "MuHIso_",
    ";H Iso;",
    2000,0.,2.,
    nMax_+1, 0, 1, true );

  BookHistArray( hLepCIso_,
    "MuCso_",
    ";Combined_Iso;",
    2000,0.,2.,
    nMax_+1, 0, 1, true );

  BookHistArray( hMT_,
    "MT_",
    ";M){T} [GeV];",
    2000,0.,2000.,
    nMax_+1, 0, 1, true );


  BookHistArray( hSecondLepTrIso_,
    "Second_MuTrIso_",
    ";Trk Iso;",
    2000,0.,2.,
    nMax_+1, 0, 1, true );


  BookHistArray( hSecondLepEIso_,
    "Second_MuEIso_",
    ";E Iso;",
    2000,0.,2.,
    nMax_+1, 0, 1, true );


  BookHistArray( hSecondLepHIso_,
    "Second_MuHIso_",
    ";H Iso;",
    2000,0.,2.,
    nMax_+1, 0, 1, true );

  BookHistArray( hSecondLepCIso_,
    "Second_MuCso_",
    ";Second_Combined_Iso;",
    2000,0.,2.,
    nMax_+1, 0, 1, true );

  BookHistArray( BtagPreAlphaT_4_,
    "Btag_Pre_AlphaT_4_",
    ";Number of Btags;",
    6,0.,6.,
    nMax_+1, 0, 1, true );

  BookHistArray( BtagAfterAlphaT_4_,
    "Btag_Post_AlphaT_4_",
    ";Number of Btags;",
    6,0.,6.,
    nMax_+1, 0, 1, true );

  BookHistArray( BtagPreAlphaT_5_,
    "Btag_Pre_AlphaT_5_",
    ";Number of Btags;",
    6,0.,6.,
    nMax_+1, 0, 1, true );

  BookHistArray( BtagAfterAlphaT_5_,
    "Btag_Post_AlphaT_5_",
    ";Number of Btags;",
    6,0.,6.,
    nMax_+1, 0, 1, true );
}
// -----------------------------------------------------------------------------
//

Double_t WeeklyUpdatePlots::MT2_Leading( Event::Data& ev ){
  mt2_bisect::mt2 mt2_event;
  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;
  
  LorentzV lv1 = *jet[0];
  LorentzV lv2 = *jet[1];

  double pa[3]; // px py m of object 1
  double pb[3]; // px py m of object 2
  double pm[3];       //jet1
  pa[1] = lv1.Px();
  pa[2] = lv1.Py();
  pa[0] = 0.;//KS_MT(objects[0]);
            //jet2
  pb[1] = lv2.Px();
  pb[2] = lv2.Py();
  pb[0] = 0.;//KS_MT(objects[1]);

  pm[1]= ev.CommonMHT().Px();
  pm[2]= ev.CommonMHT().Py();

  // set invisable mass
  double mn = 0.;
  mt2_event.set_momenta(pa,pb,pm);
  mt2_event.set_mn(mn);

  return mt2_event.get_mt2();

}


Double_t WeeklyUpdatePlots::DeltaHT( Event::Data& ev){
  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;
  UInt_t n = jet.size();

  LorentzV lv1(0.,0.,0.,0.);
  LorentzV lv2(0.,0.,0.,0.);

  // Alpha_t variable
  std::vector<bool> pseudo;
  AlphaT()( jet, pseudo, false );
  if ( pseudo.size() != jet.size() ) { abort(); }
    // use this to get the pseudo jets

  if ( n == 2 ) {
    if ( jet[0] ) lv1 = *jet[0];
    if ( jet[1] ) lv2 = *jet[1];
  } else if ( n > 2 ) {
    for ( unsigned int i = 0; i < jet.size(); ++i ) {
      if ( jet[i] ) {
        if ( pseudo[i] ) { lv1 += *jet[i];

        }
        else             { lv2 += *jet[i];

        }
      }
    }
    if ( lv2.Pt() > lv1.Pt() ) { LorentzV tmp = lv1; lv1 = lv2; lv2 = tmp; }

  }

  return lv1.Et()-lv2.Et();

}

std::pair<LorentzV,LorentzV> WeeklyUpdatePlots::PsudoJets( Event::Data & ev ){
  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;
  UInt_t n = jet.size();
  LorentzV lv1(0.,0.,0.,0.);
  LorentzV lv2(0.,0.,0.,0.);

  // Alpha_t variable
  std::vector<bool> pseudo;
  AlphaT()( jet, pseudo, false );
  if ( pseudo.size() != jet.size() ) { abort(); }
    // use this to get the pseudo jets

  if ( n == 2 ) {
    if ( jet[0] ) lv1 = *jet[0];
    if ( jet[1] ) lv2 = *jet[1];
  } else if ( n > 2 ) {
    for ( unsigned int i = 0; i < jet.size(); ++i ) {
      if ( jet[i] ) {
        if ( pseudo[i] ) { lv1 += *jet[i];

        }
        else             { lv2 += *jet[i];

        }
      }
    }
    if ( lv2.Pt() > lv1.Pt() ) { LorentzV tmp = lv1; lv1 = lv2; lv2 = tmp; }

  }
  std::pair<LorentzV,LorentzV> a(lv1,lv2);
  return a;

}

Double_t WeeklyUpdatePlots::MT2( Event::Data& ev){

  std::vector<Event::Jet const *> jet = ev.JD_CommonJets().accepted;
  UInt_t n = jet.size();

  mt2_bisect::mt2 mt2_event;

  LorentzV lv1(0.,0.,0.,0.);
  LorentzV lv2(0.,0.,0.,0.);

  // Alpha_t variable
  std::vector<bool> pseudo;
  AlphaT()( jet, pseudo, false );
  if ( pseudo.size() != jet.size() ) { abort(); }
    // use this to get the pseudo jets

  if ( n == 2 ) {
    if ( jet[0] ) lv1 = *jet[0];
    if ( jet[1] ) lv2 = *jet[1];
  } else if ( n > 2 ) {
    for ( unsigned int i = 0; i < jet.size(); ++i ) {
      if ( jet[i] ) {
        if ( pseudo[i] ) { lv1 += *jet[i];

        }
        else             { lv2 += *jet[i];

        }
      }
    }
    if ( lv2.Pt() > lv1.Pt() ) { LorentzV tmp = lv1; lv1 = lv2; lv2 = tmp; }

  }

  double pa[3]; //m, px, py, of object 1
  double pb[3]; //m, px ,py, of object 2
  double pm[3];       //jet1
  pa[1] = lv1.Px();
  pa[2] = lv1.Py();
  pa[0] = 0.;//KS_MT(objects[0]);
            //jet2
  pb[1] = lv2.Px();
  pb[2] = lv2.Py();
  pb[0] = 0.;//KS_MT(objects[1]);

  pm[1]= ev.CommonMHT().Px();
  pm[2]= ev.CommonMHT().Py();

  // set invisable mass
  double mn = 0.;
  mt2_event.set_momenta(pa,pb,pm);
  mt2_event.set_mn(mn);
  // mt2_event.print();
  return mt2_event.get_mt2();
}


bool WeeklyUpdatePlots::StandardPlots( Event::Data& ev ) {

  std::vector <Event::Lepton const *> theLepton;

  UInt_t nBtags_four = 0;
  UInt_t nBtags_five = 0;
  for(unsigned int i=0; i<ev.JD_CommonJets().accepted.size(); i++) {
  // std::cout << "we are on jet " << i << " the btag discriminator is " << ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), 4) << std::endl;
  if(ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), 4) > 0.679) {
  nBtags_four++;
         //if we make it into here, the jet has passed the b-tag requirement
   } 
  if(ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), 5) > 2.0) {
  nBtags_five++;
         //if we make it into here, the jet has passed the b-tag requirement
   } 
   
  }


  bool isMu= false;
  bool isLep=false;
  bool isdoubleMu = false;

  if (ev.LD_CommonMuons().accepted.size() + ev.LD_CommonElectrons().accepted.size() != 0){
    isLep=true;}

  if(ev.LD_CommonMuons().accepted.size()>0&&ev.LD_CommonElectrons().accepted.size()==0)
    {
      theLepton = ev.LD_CommonMuons().accepted;
      isMu = true;
    }  

  if(ev.LD_CommonMuons().accepted.size()>1&&ev.LD_CommonElectrons().accepted.size()==0)
    {
      theLepton = ev.LD_CommonMuons().accepted;
      isdoubleMu = true;
   } 

  if(ev.LD_CommonMuons().accepted.size()==0&&ev.LD_CommonElectrons().accepted.size()>0)
    {
      theLepton = ev.LD_CommonElectrons().accepted;
    }  

  if(ev.LD_CommonMuons().accepted.size()>0&&ev.LD_CommonElectrons().accepted.size()>0)
    {
      cout << "WARNING: ttWPlottingOps has common muon AND Electron, it does not know what to plot!!!"<<endl;
       return true;
     }


  UInt_t n = ev.JD_CommonJets().accepted.size();

  Double_t weight = ev.GetEventWeight();

  int count_ = 0;
  double biasedDPhi = 100.;
  double biasedDPhi_baby = 100.;
  int counter_ = 0;
  int counterBaby_ = 0;
  int countBaby_ = 0;

  LorentzV loweredMHT = ev.CommonRecoilMET();
  for(std::vector<Event::Jet const*>::const_iterator iM = ev.JD_CommonJets().baby.begin();iM != ev.JD_CommonJets().baby.end();++iM){
    if( (*iM)->Pt() > 30.)
      loweredMHT -= (**iM);
  }



  for( std::vector<Event::Jet const *>::const_iterator i = ev.JD_CommonJets().accepted.begin();
  i != ev.JD_CommonJets().accepted.end();
  ++i ){
    double newBiasDPhi = fabs(ROOT::Math::VectorUtil::DeltaPhi(**i,loweredMHT + (**i))) ;
    if(newBiasDPhi < biasedDPhi){
      biasedDPhi = newBiasDPhi;
      count_ = counter_;
    }
    counter_++;
  }
  for( std::vector<Event::Jet const*>::const_iterator iI = ev.JD_CommonJets().baby.begin(); iI != ev.JD_CommonJets().baby.end();
  ++iI) {
    if((*iI)->Pt() > 30.){
      double newBiasDPhi_2 = fabs( ROOT::Math::VectorUtil::DeltaPhi(**iI, loweredMHT + (**iI) ) );
      if(newBiasDPhi_2 < biasedDPhi_baby){
        biasedDPhi_baby = newBiasDPhi_2;
        countBaby_ = counterBaby_;
      }
    }
    counterBaby_++;
  }

  if( biasedDPhi < biasedDPhi_baby){
    if ( n >= nMin_ && n <= nMax_ && n < MinBiasDphi_EtaPhiMap_.size()) {
      MinBiasDphi_EtaPhiMap_[0]->Fill(ev.JD_CommonJets().accepted[count_]->Eta(), ev.JD_CommonJets().accepted[count_]->Phi(),weight);
      MinBiasDphi_EtaPhiMap_[n]->Fill(ev.JD_CommonJets().accepted[count_]->Eta(), ev.JD_CommonJets().accepted[count_]->Phi(),weight);
    }
  }
  if( biasedDPhi > biasedDPhi_baby){
    if ( n >= nMin_ && n <= nMax_ && n < MinBiasDphi_EtaPhiMap_.size()) {
      MinBiasDphi_EtaPhiMap_[0]->Fill(ev.JD_CommonJets().baby[countBaby_]->Eta(), ev.JD_CommonJets().baby[countBaby_]->Phi(),weight);
      MinBiasDphi_EtaPhiMap_[n]->Fill(ev.JD_CommonJets().baby[countBaby_]->Eta(), ev.JD_CommonJets().baby[countBaby_]->Phi(),weight);
    }
  }


  BtagPreAlphaT_4_[0]->Fill( nBtags_four, weight );
  BtagPreAlphaT_5_[0]->Fill( nBtags_five, weight );





  int nVertex = 0;
  //Make the vertex sum PT for later plots
  double  VertexPt = 0.;
  for(std::vector<floatle>::const_iterator vtx =
    ev.vertexSumPt()->begin();
  vtx != ev.vertexSumPt()->end();++vtx){
    if(!ev.vertexIsFake()->at( vtx-ev.vertexSumPt()->begin()) && fabs((ev.vertexPosition()->at( vtx-ev.vertexSumPt()->begin())).Z()) < 24.0 && ev.vertexNdof()->at( vtx-ev.vertexSumPt()->begin() ) > 4&& (ev.vertexPosition()->at( vtx-ev.vertexSumPt()->begin())).Rho() < 2.0 ){  VertexPt += *vtx;}
  }


  for(std::vector<float>::const_iterator vtx =
    ev.vertexSumPt()->begin();
  vtx != ev.vertexSumPt()->end();++vtx){
    if(!ev.vertexIsFake()->at( vtx-ev.vertexSumPt()->begin()) &&
      fabs((ev.vertexPosition()->at( vtx-ev.vertexSumPt()->begin())).Z()) < 24.0 &&
      ev.vertexNdof()->at( vtx-ev.vertexSumPt()->begin() ) > 4 &&
      (ev.vertexPosition()->at( vtx-ev.vertexSumPt()->begin())).Rho() < 2.0 ){  nVertex++; }
  }

  if ( StandardPlots_ ){

    std::pair<LorentzV,LorentzV> PsudoJets = WeeklyUpdatePlots::PsudoJets( ev );




    if ( n >= nMin_ && n <= nMax_ && n < HT_vs_AlphaT_Hadronic_.size()) {
      HT_vs_AlphaT_Hadronic_[0]->Fill(ev.CommonHT(),ev.HadronicAlphaT(),weight);
      HT_vs_AlphaT_Hadronic_[n]->Fill(ev.CommonHT(),ev.HadronicAlphaT(),weight);
    }


    if ( n >= nMin_ && n <= nMax_ && n < vertexPtovHT_.size()) {
      vertexPtovHT_[0]->Fill(VertexPt/ev.CommonHT(),weight);
      vertexPtovHT_[n]->Fill(VertexPt/ev.CommonHT(),weight);
    }



    if ( n >= nMin_ && n <= nMax_ && n < NumberVerticies_.size()) {
      NumberVerticies_[0]->Fill(nVertex,weight);
      NumberVerticies_[n]->Fill(nVertex,weight);
    }



    


    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MHT_MHTBaby_.size()) {
      DPhi_MHT_MHTBaby_[0]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),weight);
      DPhi_MHT_MHTBaby_[n]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),weight);

    }

    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MET_MHTBaby_.size()) {
      DPhi_MET_MHTBaby_[0]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.JD_CommonJets().babyHT)),weight);
      DPhi_MET_MHTBaby_[n]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.JD_CommonJets().babyHT)),weight);

    }

    if ( n >= nMin_ && n <= nMax_ && n < DPhi_MET_MHT_.size()) {
      DPhi_MET_MHT_[0]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.CommonMHT())),weight);
      DPhi_MET_MHT_[n]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(ev.PFMET(),ev.CommonMHT())),weight);

    }


    if ( n >= nMin_ && n <= nMax_ && n < Multiplicity_.size()) {
      Multiplicity_[0]->Fill( n, weight );
      Multiplicity_[n]->Fill( n, weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < MHT_.size()) {
      MHT_[0]->Fill( ev.CommonMHT().Pt(), weight );
      MHT_[n]->Fill( ev.CommonMHT().Pt(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < HT_.size() ) {
      HT_[0]->Fill( ev.CommonHT(), weight );
      HT_[n]->Fill( ev.CommonHT(), weight );
    }


    if ( n >= nMin_ && n <= nMax_ && n < MHToverHT_.size() ) {
      MHToverHT_[0]->Fill( ev.CommonMHT().Pt()/ev.CommonHT(), weight );
      MHToverHT_[n]->Fill( ev.CommonMHT().Pt()/ev.CommonHT(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < Meff_.size()) {
      Meff_[0]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
      Meff_[n]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
    }


    if ( n >= nMin_ && n <= nMax_ && n < AlphaT_Zoomed_.size()  ) {
      AlphaT_Zoomed_[0]->Fill( ev.HadronicAlphaT(), weight );
      AlphaT_Zoomed_[n]->Fill( ev.HadronicAlphaT(), weight );
    }

    if ( n >= nMin_ && n <= nMax_ && n < AlphaT_.size()  ) {
      AlphaT_[0]->Fill( ev.HadronicAlphaT(), weight );
      AlphaT_[n]->Fill( ev.HadronicAlphaT(), weight );
    }


    if( biasedDPhi < biasedDPhi_baby){
      if ( n >= nMin_ && n <= nMax_ && n < BiasedDphi_.size()) {
      MinBiasDphi_EtaPhiMap_[0]->Fill(biasedDPhi,weight);
      MinBiasDphi_EtaPhiMap_[n]->Fill(biasedDPhi,weight);
      }
    }
    if( biasedDPhi > biasedDPhi_baby){
      if ( n >= nMin_ && n <= nMax_ && n < BiasedDphi_.size()) {
      BiasedDphi_[0]->Fill(biasedDPhi_baby,weight);
      BiasedDphi_[n]->Fill(biasedDPhi_baby,weight);
      }
    }


    if( n >= nMin_ && n <= nMax_ && n < DetlaPhi_LeadingJets_.size() ){
      DetlaPhi_LeadingJets_[1]->Fill( fabs( ROOT::Math::VectorUtil::DeltaPhi(*ev.JD_CommonJets().accepted[0],*ev.JD_CommonJets().accepted[1])),weight);
      if(n <2){
        DetlaPhi_NextToLeadingJets_[2]->Fill(fabs(ROOT::Math::VectorUtil::DeltaPhi(*ev.JD_CommonJets().accepted[1],*ev.JD_CommonJets().accepted[2])),weight);

      }
    }


    for(unsigned int i = 0; i < ev.JD_CommonJets().accepted.size() && i < 3; i++){
      JetPt_[0]->Fill(ev.JD_CommonJets().accepted[i]->Pt(),weight);
      JetEta_[0]->Fill(ev.JD_CommonJets().accepted[i]->Eta(),weight);
      JetPt_[i+1]->Fill(ev.JD_CommonJets().accepted[i]->Pt(),weight);
      JetEta_[i+1]->Fill(ev.JD_CommonJets().accepted[i]->Eta(),weight);
    }



    if( n >= nMin_ && n <= nMax_ && n < AlphaT_components_.size() ){
      AlphaT_components_[0]->Fill(ev.CommonMHT().Pt()/ev.CommonHT(),WeeklyUpdatePlots::DeltaHT(ev)/ev.CommonHT(),weight);
      AlphaT_components_[n]->Fill(ev.CommonMHT().Pt()/ev.CommonHT(),WeeklyUpdatePlots::DeltaHT(ev)/ev.CommonHT(),weight);
    }



    if (isLep){

    Double_t aMT =  sqrt(2.0 * ev.PFMET().Pt() * (theLepton.at(0))->Pt() * (1.0 - cos(ROOT::Math::VectorUtil::DeltaPhi(*(theLepton.at(0)), ev.PFMET() ) )));
     hLepPt_[0]->Fill(theLepton.at(0)->Pt(),weight);
     hMT_[0]->Fill(aMT,weight);
   
   

     hLepTrIso_[0]->Fill(((theLepton.at(0))->GetTrkIsolation())/((theLepton.at(0))->Pt()),weight);
     hLepEIso_[0]->Fill(((theLepton.at(0))->GetEcalIsolation())/((theLepton.at(0))->Et()),weight);
     hLepHIso_[0]->Fill(((theLepton.at(0))->GetHcalIsolation())/((theLepton.at(0))->Et()),weight);
     hLepCIso_[0]->Fill((theLepton.at(0))->GetCombIsolation(),weight);

     if(isdoubleMu){
      UInt_t iM  = (theLepton.at(1))->GetIndex();
      hSecondLepTrIso_[0]->Fill(((theLepton.at(1))->GetTrkIsolation())/((theLepton.at(1))->Pt()),weight);
      hSecondLepEIso_[0]->Fill(((theLepton.at(1))->GetEcalIsolation())/((theLepton.at(1))->Et()),weight);
      hSecondLepHIso_[0]->Fill(((theLepton.at(1))->GetHcalIsolation())/((theLepton.at(1))->Et()),weight);
      hSecondLepCIso_[0]->Fill((theLepton.at(1))->GetCombIsolation(),weight);
      hSecondLepPt_[0]->Fill(theLepton.at(1)->Pt(),weight);
    }
    }
      

    if(ev.HadronicAlphaT() < 0.55){
      if ( n >= nMin_ && n <= nMax_ && n < AlphatBefore_HT_.size() ) {
        AlphatBefore_HT_[0]->Fill( ev.CommonHT(), weight );
        AlphatBefore_HT_[n]->Fill( ev.CommonHT(), weight );
      }
    }

    if(ev.HadronicAlphaT() > 0.55){

      UInt_t nBtags_AT_four = 0;
      UInt_t nBtags_AT_five = 0;
      for(unsigned int i=0; i<ev.JD_CommonJets().accepted.size(); i++) {
      // std::cout << "we are on jet " << i << " the btag discriminator is " << ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), 4) << std::endl;
      if(ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), 4) > 0.679) {
      nBtags_AT_four++;
            //if we make it into here, the jet has passed the b-tag requirement
      } 
      if(ev.GetBTagResponse(ev.JD_CommonJets().accepted.at(i)->GetIndex(), 5) > 2.0) {
      nBtags_AT_five++;
             //if we make it into here, the jet has passed the b-tag requirement
      } 
   
      }
      BtagAfterAlphaT_4_[0]->Fill( nBtags_AT_four, weight );
      BtagAfterAlphaT_5_[0]->Fill( nBtags_AT_five, weight );


      if ( n >= nMin_ && n <= nMax_ && n < NumberVerticiesAfterAlphaT_.size()) {
        NumberVerticiesAfterAlphaT_[0]->Fill(nVertex,weight);
        NumberVerticiesAfterAlphaT_[n]->Fill(nVertex,weight);
      }

      if ( n >= nMin_ && n <= nMax_ && n < MultiplicityAfteraT_.size()) {
        MultiplicityAfteraT_[0]->Fill( n, weight );
        MultiplicityAfteraT_[n]->Fill( n, weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < HT_forRatio_.size() ) {
        HT_forRatio_[0]->Fill(  ev.CommonHT(), weight );
        HT_forRatio_[n]->Fill( ev.CommonHT(), weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < MHTovMET_.size() ) {
        MHTovMET_[0]->Fill(  ev.CommonMHT().Pt()/LorentzV(*ev.metP4caloTypeII()).Pt(), weight );
        MHTovMET_[n]->Fill(  ev.CommonMHT().Pt()/LorentzV(*ev.metP4caloTypeII()).Pt(), weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < MissedHT_.size() ) {
        MissedHT_[0]->Fill(  ev.CommonRecoilMET().Pt()/(ev.CommonRecoilMET()+ev.JD_CommonJets().babyHT).Pt(), weight );
        MissedHT_[n]->Fill( ev.CommonRecoilMET().Pt()/(ev.CommonRecoilMET()+ev.JD_CommonJets().babyHT).Pt(), weight );
      }



      if ( n >= nMin_ && n <= nMax_ && n < DPhi_MHT_MHTbaby_AfterAlphaT_.size()) {
        DPhi_MHT_MHTbaby_AfterAlphaT_[0]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),weight);
        DPhi_MHT_MHTbaby_AfterAlphaT_[n]->Fill(cos(ROOT::Math::VectorUtil::DeltaPhi(ev.CommonMHT(),ev.JD_CommonJets().babyHT)),weight);
      }

      if ( n >= nMin_ && n <= nMax_ && n < AlphatCut_HT_.size() ) {
        AlphatCut_HT_[0]->Fill( ev.CommonHT(), weight );
        AlphatCut_HT_[n]->Fill( ev.CommonHT(), weight );
      }

      if ( n >= nMin_ && n <= nMax_ && n < AlphatCut_Meff_.size()) {
        AlphatCut_Meff_[0]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
        AlphatCut_Meff_[n]->Fill( ev.CommonMHT().Pt()+ev.CommonHT(), weight );
      }

    if( biasedDPhi < biasedDPhi_baby){
      if ( n >= nMin_ && n <= nMax_ && n < AlphatCut_BiasedDphi_.size()) {
      AlphatCut_BiasedDphi_[0]->Fill(biasedDPhi,weight);
      AlphatCut_BiasedDphi_[n]->Fill(biasedDPhi,weight);
      }
    }
    if( biasedDPhi > biasedDPhi_baby){
      if ( n >= nMin_ && n <= nMax_ && n < AlphatCut_BiasedDphi_.size()) {
      AlphatCut_BiasedDphi_[0]->Fill(biasedDPhi_baby,weight);
      AlphatCut_BiasedDphi_[n]->Fill(biasedDPhi_baby,weight);
      }
    }

    }

  }







  return true;

}
