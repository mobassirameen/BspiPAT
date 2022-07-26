#ifndef _Bspi_h
#define _Bspi_h

// system include files
#include <memory>

// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFit/interface/MassKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/TransientTrackKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "RecoVertex/AdaptiveVertexFit/interface/AdaptiveVertexFitter.h"


#include "TrackingTools/TransientTrack/interface/TransientTrackFromFTSFactory.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/V0Candidate/interface/V0Candidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h" // muy importante para MiniAOD
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"

#include "RecoVertex/VertexPrimitives/interface/BasicSingleVertexState.h"
#include "RecoVertex/VertexPrimitives/interface/VertexState.h"

#include "TFile.h"
#include "TTree.h"
#include <vector>
#include "TLorentzVector.h"
#include "TVector3.h"
#include <utility>
#include <string>



//
// class decleration
//

class Bspi : public edm::EDAnalyzer {
public:
  explicit Bspi(const edm::ParameterSet&);
  ~Bspi();
  bool IsTheSame(const pat::GenericParticle& tk, const pat::Muon& mu);
  bool   isAncestor(const reco::Candidate*, const reco::Candidate*);
  double GetLifetime(TLorentzVector, TVector3, TVector3);
  reco::Vertex getPVConstrainedToBS(const edm::Event& iEvent,const edm::EventSetup& iSetup, reco::Vertex pv);

  double calEta(double, double, double);
  double calPhi(double, double, double);
  double calEtaPhiDistance (double, double, double, double, double, double);
  void saveTruthMatch(const edm::Event& iEvent);

  void saveIP(const RefCountedKinematicTree& vertexFitTreeBspi,
	      const reco::VertexCollection& vertices, int & pvIndex);
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

 // TH1D* h_deltaR;
  
    // ----------member data ---------------------------
  edm::EDGetTokenT<edm::View<pat::Muon>> dimuon_Label;
  edm::EDGetTokenT<edm::View<pat::PackedCandidate>> trakCollection_label;
  edm::EDGetTokenT<edm::View<pat::PackedCandidate>> trakCollection_label_lostTracks;
  edm::EDGetTokenT<reco::GenParticleCollection> genCands_;
  edm::EDGetTokenT<pat::PackedGenParticleCollection> packedGenToken_;
  edm::EDGetTokenT<reco::VertexCollection> primaryVertices_Label;
  edm::EDGetTokenT<edm::TriggerResults> triggerResults_Label;
  edm::EDGetTokenT<reco::BeamSpot> BSLabel_;


  bool OnlyBest_;
  bool isMC_;
  bool OnlyGen_;
  double Trkmass_;
  std::vector<double> TrkTrkMasscut_;
  std::vector<double> BarebMasscut_;
  std::vector<double> bMasscut_;

  // bool doMC_;
  //std::string genParticles_;

  TTree*      tree_;
  int mupCategory;
  int mumCategory;
  int mupME1Clean;
  int mumME1Clean;

  std::vector<float>       *mumC2;
  std::vector<int>         *mumAngT, *mumNHits, *mumNPHits; 
  std::vector<float>       *mupC2;
  std::vector<int>         *mupAngT, *mupNHits, *mupNPHits;
  std::vector<float>       *mumdxy, *mupdxy, *mumdz, *mupdz;
  std::vector<float>       *muon_dca;
  //std::vector<double>      *ElsigJpsi;

  std::vector<int>         *tri_Dim25, *tri_JpsiTk, *tri_JpsiTkTk; 

  std::vector<bool>        *mu1soft, *mu2soft, *mu1tight, *mu2tight;  
  std::vector<bool>        *mu1PF, *mu2PF, *mu1loose, *mu2loose;  

  int                     muAcc, muTrig, weight;

  // *************************************
  unsigned int             nB;
  unsigned int             nMu;
  
  //std::vector<float>       *Bspi_mass_vertex, *Bspion_mass;
  std::vector<float>       *Bc_mass, *Bc_pt, *Bc_px, *Bc_py, *Bc_pz, *Bc_eta, *Bc_phi, *Bc_ct;
  std::vector<int>         *Bc_charge;
  std::vector<double>      *Bcvtxcl, *Bc_prob;
  std::vector<float>       *deltaMass;
  std::vector<float>       *T_Bspion_mass, *Notmatch_Bspion_mass;

  std::vector<float>    *Bc_DecayVtxX        , *Bc_DecayVtxY      , *Bc_DecayVtxZ;
  std::vector<float>    *Bc_DecayVtxXE       , *Bc_DecayVtxYE     , *Bc_DecayVtxZE;
  std::vector<double>   *Bc_DecayVtxXYE      , *Bc_DecayVtxXZE    , *Bc_DecayVtxYZE;

  //std::vector<float>    *Bc_DecayVtx_vtxfit_X        , *Bc_DecayVtx_vtxfit_Y      , *Bc_DecayVtx_vtxfit_Z;
  //std::vector<float>    *Bc_DecayVtx_vtxfit_XE       , *Bc_DecayVtx_vtxfit_YE     , *Bc_DecayVtx_vtxfit_ZE;
  //std::vector<float>    *Bc_DecayVtx_vtxfit_XYE       , *Bc_DecayVtx_vtxfit_XZE     , *Bc_DecayVtx_vtxfit_YZE;

  std::vector<float>       *B_mass, *B_px, *B_py, *B_pz, *B_pt, *B_eta, *B_phi;

  //std::vector<float>       *B_pion_px,  *B_pion_py,  *B_pion_pz;
  std::vector<float>       *pion_track_normchi2;
  std::vector<int>         *pion_NumHits,  *pion_NumPixelHits;
  std::vector<float>       *pion_dxy, *pion_dz;
  std::vector<float>       *pion_dxy_, *pion_dz_;
  std::vector<int>         *pion_NTrackerLayers,  *pion_NPixelLayers;
  std::vector<float>       *B_pion_px_track, *B_pion_py_track, *B_pion_pz_track;
  std::vector<float>       *B_pion_pt_track;
  std::vector<int>         *B_pion_charge;

  std::vector<int>         *pion_PV;
  
  std::vector<float>       *B_phi_mass;
  std::vector<float>       *B_phi_px, *B_phi_py, *B_phi_pz;
  std::vector<float>       *B_phi_pt, *B_phi_eta, *B_phi_phi;

  std::vector<float>       *B_phi_px1, *B_phi_py1, *B_phi_pz1, *B_phi_pt1;
  std::vector<float>       *B_phi_eta1, *B_phi_phi1;
  std::vector<float>       *B_phi_px2, *B_phi_py2, *B_phi_pz2, *B_phi_pt2;
  std::vector<float>       *B_phi_eta2, *B_phi_phi2;

  std::vector<float>       *B_phi_px1_track, *B_phi_py1_track, *B_phi_pz1_track;
  std::vector<float>       *B_phi_px2_track, *B_phi_py2_track, *B_phi_pz2_track;

  std::vector<int>         *B_phi_charge1, *B_phi_charge2;
  std::vector<float>       *k1dxy, *k2dxy, *k1dz, *k2dz;
  std::vector<float>       *k1dxy_e, *k2dxy_e, *k1dz_e, *k2dz_e;
  std::vector<float>       *k1InnerHits, *k2InnerHits;

  std::vector<float>       *B_J_mass, *B_J_px, *B_J_py, *B_J_pz;
  std::vector<float>       *B_J_pt, *B_J_eta, *B_J_phi;

  std::vector<float>       *B_J_pt1;
  std::vector<float>       *B_J_eta1, *B_J_phi1;
  std::vector<float>       *B_J_px1, *B_J_py1, *B_J_pz1;
  std::vector<float>       *B_J_pt2;
  std::vector<float>       *B_J_eta2, *B_J_phi2;
  std::vector<float>       *B_J_px2, *B_J_py2, *B_J_pz2;
  std::vector<int>         *B_J_charge1, *B_J_charge2;

  unsigned int             nVtx;
  float                    priVtxX, priVtxY, priVtxZ, priVtxXE, priVtxYE, priVtxZE, priVtxCL;
  float                    priVtxXYE, priVtxXZE, priVtxYZE;

  TH1F       *hDzTrkPV;
  
  // ********************************** ************************************************************************
  
  std::vector<float>       *pVtxIPX,  *pVtxIPY, *pVtxIPZ, *pVtxIPXE, *pVtxIPYE, *pVtxIPZE, *pVtxIPCL;
  std::vector<float>       *pVtxIPXYE,  *pVtxIPXZE, *pVtxIPYZE;
  
  std::vector<float>       *B_l3d,  *B_l3dE,  /* *B_lxy,*/ *Bc_lxy, *B_lxyE ;
  std::vector<float>       *B_cosalpha , /* *B_cosalphaxy,*/ *Bc_cosalphaxy, *alpha; //, *B_treco ,  *B_trecoe,  *B_trecoxy, *B_trecoxye;
  std::vector<float>       *B_pvip , *B_pviperr, *B_pvips, *B_pvlzip, *B_pvlziperr,*B_pvlzips;
  std::vector<float>       *B_pv2ip , *B_pv2iperr, *B_pv2ips, *B_pv2lzip, *B_pv2lziperr,*B_pv2lzips;
  std::vector<float>       *B_l3d_pv2,  *B_l3dE_pv2;
  
  //std::vector<float>       *Bs_lxy, *Bs_lxyE ; 
  //std::vector<float>       *ElsigBs;
  //std::vector<float>       *Bs_cosalphaxy;
  // ********************************** ************************************************************************

  std::vector<float>       *Bc_chi2, *B_chi2, *B_J_chi2;
  std::vector<float>       *B_Prob, *B_J_Prob;

  std::vector<float>       *B_DecayVtxX,  *B_DecayVtxY,  *B_DecayVtxZ;
  std::vector<double>      *B_DecayVtxXE, *B_DecayVtxYE, *B_DecayVtxZE;
  std::vector<double>      *B_DecayVtxXYE, *B_DecayVtxXZE, *B_DecayVtxYZE;

  std::vector<float>       *B_J_DecayVtxX,   *B_J_DecayVtxY,   *B_J_DecayVtxZ;
  std::vector<float>       *B_J_DecayVtxXE,  *B_J_DecayVtxYE,  *B_J_DecayVtxZE;
  std::vector<float>       *B_J_DecayVtxXYE, *B_J_DecayVtxXZE, *B_J_DecayVtxYZE;

  std::vector<double>      *deltaRmum,  *deltaRmup,  *deltaRkp,  *deltaRkm,  *deltaRbs,  *deltaRpion; 
  std::vector<bool>        *istruemum,  *istruemup,  *istruekp,  *istruekm,  *istruebs,  *istruepion,  *istruebc;

  int  run, event;
  int lumiblock;

  TLorentzVector gen_bc_p4,gen_phi_p4,gen_kaon1_p4,gen_kaon2_p4,gen_jpsi_p4,gen_muon1_p4,gen_muon2_p4;
  TLorentzVector gen_bs_p4,gen_pion_p4; 
  TLorentzVector gen_b_p4; 
  //TLorentzVector gen_bs_p4,gen_pion1_p4,gen_pion2_p4; 
  TVector3       gen_bc_vtx;
  TVector3       gen_bs_vtx;
  TVector3       gen_b_vtx;
  TVector3       gen_jpsi_vtx;
  float          gen_b_ct;

};
#endif
