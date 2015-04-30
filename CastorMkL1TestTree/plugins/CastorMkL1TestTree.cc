// -*- C++ -*-
//
// Package:    CastorL1Valid/CastorMkL1TestTree
// Class:      CastorMkL1TestTree
// 
/**\class CastorMkL1TestTree CastorMkL1TestTree.cc CastorL1Valid/CastorMkL1TestTree/plugins/CastorMkL1TestTree.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Clemens Wohrmann
//         Created:  Fri, 24 Apr 2015 09:27:01 GMT
//
//

// system include files
#include <memory>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <bitset>
#include <string>
#include <utility>

// include root files
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// include tracks
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

// include vertices
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// include electrons
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

// include HF electrons
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"

// HCAL & ECAL RecHit
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

// HCAL Towers
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

// include castorrechits
#include "DataFormats/HcalRecHit/interface/CastorRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

// include castortowers
#include "DataFormats/CastorReco/interface/CastorTower.h"

// include castorjets
#include "DataFormats/JetReco/interface/BasicJet.h"
#include "DataFormats/JetReco/interface/CastorJetID.h"
#include "DataFormats/Common/interface/ValueMap.h"

// include ZDC digis
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/ZDCRecHit.h"

// include digi converter
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

// include MET
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETFwd.h"

// include GenParticles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

// include SimVertices
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

// geometry
#include "Geometry/CaloTopology/interface/HcalTopology.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

// HLT Trigger
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"

// L1 Trigger DataFormats
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
//#include "L1Trigger/GlobalTrigger/interface/L1GlobalTrigger.h"

// Pileup Information
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMask.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskAlgoTrigRcd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskTechTrigRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"


// include cmssw-lorentzvector (is pointing over typedef's to root TLorentzVector)
#include "DataFormats/Candidate/interface/LeafCandidate.h"

//
// class declaration
//

class CastorMkL1TestTree : public edm::EDAnalyzer {
   public:
      explicit CastorMkL1TestTree(const edm::ParameterSet&);
      ~CastorMkL1TestTree();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // --------- user functions ------------------------
      void GetParameterSet(const edm::ParameterSet& iConfig);
      void SetupTree();

      bool GetCollections(const edm::Event& iEvent);
      bool GetGeometry(const edm::EventSetup& iSetup);

      bool SetupTriggerCollections(const edm::Event&, const edm::EventSetup&);
      void GetTriggerInfo(const edm::Event&, const edm::EventSetup&);
      void GetL1TriggerInfo(const edm::Event&, const edm::EventSetup&);
      void GetHLTriggerInfo(const edm::Event&, const edm::EventSetup&);
      void ShowTriggerMenu();

      int  GetPileUp(edm::Handle< std::vector<PileupSummaryInfo> >& vPU);

      void CollectGenParticles();
      void CollectGenJets();
      void CollectCasRecHits();
      void CollectCasJets();
      void CollectVertices();

      // ----------member data ---------------------------
      const CaloGeometry * geo;
      L1GtUtils m_L1GtUtils;
      HLTConfigProvider hltConfig;

      // --------- flags ---------------------------------
      bool show_debug_info;
      bool only_check_trigger; // if true overwrite show_trigger_menu=true
      bool show_trigger_menu;

      std::bitset<64> L1TTBits;
      std::bitset<64> AlgoBits_lowRange, AlgoBits_upperRange;
      std::bitset<64> HLTBits;

      // --------- input labels for collections ----------
      edm::InputTag PileUpInfo_;

      edm::InputTag GenPartColl_;
      edm::InputTag GenJetColl_;

      edm::InputTag CasRecHitColl_;
      edm::InputTag BasicJetColl_;
      edm::InputTag CastorJetID_;

      edm::InputTag TrigResults_;
      edm::InputTag VertexColl_;

      // --------- collection handel ---------------------
      edm::Handle< std::vector<PileupSummaryInfo> > PileUpInfo;

      edm::Handle< reco::GenParticleCollection >    GenPartColl;
      edm::Handle< reco::GenJetCollection >         GenJetColl;

      edm::Handle< CastorRecHitCollection >         CasRecHitColl;
      edm::Handle< std::vector<reco::BasicJet> >    BasicJetView;
      edm::Handle< reco::CastorJetIDValueMap >      CasJetIdMap;

      edm::Handle< edm::TriggerResults >            TrigResults;
      edm::Handle<reco::VertexCollection>           VertexColl;

      // --------- other variables -----------------------
      std::vector<std::string> HLT_path_names;

      std::map<int,std::string> L1TT_Menu;
      std::map<int,std::string> L1Algo_Menu;
      std::map<int,std::string> HLT_Menu;

      // --------- tree variables ------------------------
      TTree* myTree;

      static const int max_genpart_size  = 5000;
      static const int max_jet_size      = 100;
      static const int max_vtx_size      = 50;
      int num_pu_vtx;

      TClonesArray* fspart;
      TClonesArray* genjet;
      TClonesArray* casjet;
      TClonesArray* vertex;
      int fspart_size;
      int genjet_size;
      int casjet_size;
      int vertex_size;

      double cas_energy[16][14];
      int fspart_id[max_genpart_size];
      int vtx_ndof[max_vtx_size];
      int vtx_fake[max_vtx_size];
      int totem_mpl[2]; // [0] -> posetive side; [1] -> negative side


      ULong64_t CastorL1DecisionWord;
      ULong64_t AlgoJetDecisionWord1;
      ULong64_t AlgoJetDecisionWord2;
      ULong64_t HLTDecisionWord;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
CastorMkL1TestTree::CastorMkL1TestTree(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  GetParameterSet(iConfig);
  SetupTree();
}


CastorMkL1TestTree::~CastorMkL1TestTree()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
CastorMkL1TestTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  if( !only_check_trigger ) {
    // Get all necessary collections
    if( !GetCollections(iEvent) ) return;
    
    num_pu_vtx = 0;
    num_pu_vtx = GetPileUp(PileUpInfo);
    
    CollectGenParticles();
    CollectGenJets();
    CollectCasRecHits();
    CollectCasJets();
    CollectVertices();
  }

  if( !SetupTriggerCollections(iEvent,iSetup) ) return;

  CastorL1DecisionWord = 0;
  AlgoJetDecisionWord1 = 0;
  AlgoJetDecisionWord2 = 0;
  HLTDecisionWord = 0;
  GetTriggerInfo(iEvent,iSetup);

  myTree->Fill();
}


// ------------ method to get parameter set from config ---------------------------------
void
CastorMkL1TestTree::GetParameterSet(const edm::ParameterSet& iConfig)
{
  // get flags
  show_debug_info    = iConfig.getParameter<bool>("ShowDebugInfo");
  only_check_trigger = iConfig.getParameter<bool>("OnlyCheckTrigger");
  show_trigger_menu  = iConfig.getParameter<bool>("ShowTriggerMenu");

  if( only_check_trigger ) show_trigger_menu = true;

  // define collections
  PileUpInfo_    = iConfig.getParameter<edm::InputTag>("PileUpInfo");

  GenPartColl_   = iConfig.getParameter<edm::InputTag>("GenPartColl");
  GenJetColl_    = iConfig.getParameter<edm::InputTag>("GenJetColl");

  BasicJetColl_  = iConfig.getParameter<edm::InputTag>("BasicJetColl");
  CastorJetID_   = iConfig.getParameter<edm::InputTag>("CastorJetID");
  CasRecHitColl_ = iConfig.getParameter<edm::InputTag>("CasRecHitColl");

  TrigResults_   = iConfig.getParameter<edm::InputTag>("TrigResults");
  VertexColl_    = iConfig.getParameter<edm::InputTag>("VertexColl");

  HLT_path_names = iConfig.getParameter< std::vector<std::string> >("HLTpaths");
}


// ------------ method to setup tree ----------------------------------------------------
void
CastorMkL1TestTree::SetupTree()
{
  edm::Service<TFileService> fs;

  myTree = fs->make<TTree>("myTree","myTree");

  fspart = new TClonesArray("TLorentzVector", max_genpart_size );
  genjet = new TClonesArray("TLorentzVector", max_jet_size );
  casjet = new TClonesArray("TLorentzVector", max_jet_size );
  vertex = new TClonesArray("TVector3" , max_vtx_size );

  myTree->Branch("num_pu_vtx" , &num_pu_vtx , "num_pu_vtx/I");

  myTree->Branch("fspart", "TClonesArray" , &fspart , 32000, 0);
  myTree->Branch("genjet", "TClonesArray" , &genjet , 32000, 0);
  myTree->Branch("casjet", "TClonesArray" , &casjet , 32000, 0);
  myTree->Branch("vertex", "TClonesArray" , &vertex , 32000, 0);
  myTree->Branch("fspart_size" , &fspart_size , "fspart_size/I");
  myTree->Branch("genjet_size" , &genjet_size , "genjet_size/I");
  myTree->Branch("casjet_size" , &casjet_size , "casjet_size/I");
  myTree->Branch("vertex_size" , &vertex_size , "vertex_size/I");
  myTree->Branch("cas_energy" , &cas_energy , "cas_energy[16][14]/D");
  myTree->Branch("fspart_id" , &fspart_id , "fspart_id[fspart_size]/I");
  myTree->Branch("vtx_ndof" , &vtx_ndof , "vtx_ndof[vertex_size]/I");
  myTree->Branch("vtx_fake" , &vtx_fake , "vtx_fake[vertex_size]/I");
  myTree->Branch("totem_mpl" , &totem_mpl , "totem_mpl[2]/I");
  
  myTree->Branch("CastorL1DecisionWord" , &CastorL1DecisionWord , "CastorL1DecisionWord/l");
  myTree->Branch("AlgoJetDecisionWord1" , &AlgoJetDecisionWord1 , "AlgoJetDecisionWord1/l");
  myTree->Branch("AlgoJetDecisionWord2" , &AlgoJetDecisionWord2 , "AlgoJetDecisionWord2/l");
  myTree->Branch("HLTDecisionWord" , &HLTDecisionWord , "HLTDecisionWord/l");
}

bool 
CastorMkL1TestTree::GetCollections(const edm::Event& iEvent)
{

  // ******************************** Pilup Information ************************************
  try{ iEvent.getByLabel(PileUpInfo_, PileUpInfo); }
  catch(...) { edm::LogWarning(" PileUpInfo ") << " Cannot get PileUpInfo " << std::endl; }
  
  if( !PileUpInfo.isValid() || PileUpInfo.failedToGet() ) {
    edm::LogWarning(" PileUpInfo ") << " Cannot read PileUpInfo " << std::endl;
    return false;
  }


  // ******************************** GEN Particles ************************************ 
  try{ iEvent.getByLabel(GenPartColl_, GenPartColl); }
  catch(...) { edm::LogWarning(" GenParticle ") << " Cannot get GenParticles " << std::endl; }
  
  if( !GenPartColl.isValid() || GenPartColl.failedToGet() ) {
    edm::LogWarning(" GenParticle ") << " Cannot read GenParticles " << std::endl;
    return false;
  }

  // ******************************** GEN Jets ************************************
  try{ iEvent.getByLabel(GenJetColl_, GenJetColl); }
  catch(...) { edm::LogWarning(" GenJet ") << " Cannot get GenJet" << std::endl; }
  
  if( !GenJetColl.isValid() || GenJetColl.failedToGet() ) {
    edm::LogWarning(" GenJet ") << " Cannot read GenJet " << std::endl;
    return false;
  }
  
  // ******************************** CASTOR RecHits *********************************
  try{ iEvent.getByLabel(CasRecHitColl_, CasRecHitColl); }
  catch(...) { edm::LogWarning(" CasRecHitColl ") << " Cannot get CastorRecHitsColl " << std::endl;  }

  if( !CasRecHitColl.isValid() || CasRecHitColl.failedToGet() ) {
    edm::LogWarning(" CasRecHitColl ") << " Cannot read CasRecHitColl " << std::endl;
    return false;
  }
  
  // ******************************** CASTOR Jets ************************************
  try{ iEvent.getByLabel(BasicJetColl_, BasicJetView); }
  catch(...) { edm::LogWarning(" BasicJet ") << " Cannot get BasicJet " << std::endl;  }

  if( !BasicJetView.isValid() || BasicJetView.failedToGet() ) {
    edm::LogWarning(" BasicJet ") << " Cannot read BasicJet " << std::endl;
    return false;
  }

  try{ iEvent.getByLabel(CastorJetID_, CasJetIdMap); }
  catch(...) { edm::LogWarning(" CastorJet ") << " Cannot get CastorJet " << std::endl;  }

  if( !CasJetIdMap.isValid() || CasJetIdMap.failedToGet() ) {
    edm::LogWarning(" CastorJet ") << " Cannot read CastorJet " << std::endl;
    return false;
  }
  
  // *********************************** Trigger ************************************
  try{ iEvent.getByLabel(TrigResults_, TrigResults); }
  catch(...) { edm::LogWarning(" TrigResults ") << " Cannot get TriggerResults " << std::endl;  }
  if( !TrigResults.isValid() || TrigResults.failedToGet() ) {
    edm::LogWarning(" TrigResults ") << " Cannot read TriggerResults " << std::endl;
    return false;
  }
  
  // ******************************** Vertices ***************************************
  try { iEvent.getByLabel(VertexColl_, VertexColl); }
  catch(...) { edm::LogWarning(" VertexColl ") << " Cannot get VERTICES " << std::endl; }

  if( !VertexColl.isValid() || VertexColl.failedToGet() ) {
    edm::LogWarning(" VertexColl ") << " Cannot read VERTICES " << std::endl;
    return false;
  }

  return true;
}

// ------------ method to get detector geometry -----------------------------------------
bool
CastorMkL1TestTree::GetGeometry(const edm::EventSetup& iSetup)
{
  edm::ESHandle<CaloGeometry> pG;

  try { iSetup.get<CaloGeometryRecord>().get(pG); }
  catch(...) { edm::LogWarning("GEOMETRY ") << " Cannot get CaloGeometryRecord " << std::endl; }
  
  if ( !pG.isValid() ) {
    edm::LogWarning("GEOMETRY ") << " CaloGeometryRecord is not VALID " << std::endl;
    geo = NULL;
    return false;
  }
  
  geo = pG.product();
  return true;
}

bool 
CastorMkL1TestTree::SetupTriggerCollections(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool useL1EventSetup = true;
  bool useL1GtTriggerMenuLite = true;

  m_L1GtUtils.getL1GtRunCache(iEvent, iSetup, useL1EventSetup, useL1GtTriggerMenuLite);

  int iErrorCode = -1;
  int l1ConfCode = -1;
  const bool l1Conf = m_L1GtUtils.availableL1Configuration(iErrorCode, l1ConfCode);
  if( !l1Conf ) { 
    std::cerr << " (*W*) No valid L1 trigger configuration; code: " << l1Conf << std::endl; 
    return false;
  }

  if( show_debug_info ) std::cout << "*** (DEBUG) HLT_path_names.size() = " << HLT_path_names.size() << std::endl;
  if( HLT_path_names.size() > 64 ) {
    std::cerr << "*** (HLT) Number of HLT paths of interest to high to save in tree" << std::endl;
    return false;
  }

  bool changedConfig = false;
  if (!hltConfig.init(iEvent.getRun(), iSetup, TrigResults_.process(), changedConfig)) {
    std::cerr << "*** (HLT) Initialization of HLTConfigProvider failed!!" << std::endl;
    return false;
  }

  return true;
}


void 
CastorMkL1TestTree::GetTriggerInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{ 
  if( show_trigger_menu ) {
    L1TT_Menu.clear();
    L1Algo_Menu.clear();
    HLT_Menu.clear();
  }

  L1TTBits.reset();
  AlgoBits_lowRange.reset(); AlgoBits_upperRange.reset();
  HLTBits.reset();

  GetL1TriggerInfo(iEvent,iSetup);
  GetHLTriggerInfo(iEvent,iSetup);

  CastorL1DecisionWord = (ULong64_t)L1TTBits.to_ulong();
  AlgoJetDecisionWord1 = (ULong64_t)AlgoBits_lowRange.to_ulong();
  AlgoJetDecisionWord2 = (ULong64_t)AlgoBits_upperRange.to_ulong();
  HLTDecisionWord      = (ULong64_t)HLTBits.to_ulong();

  if( show_debug_info ) {
    std::cout << "*** (DEBUG) L1TTBits = " << L1TTBits << " = " << CastorL1DecisionWord << std::endl;
    std::cout << "*** (DEBUG) AlgoBits_lowRange = " << AlgoBits_lowRange << " = " << AlgoJetDecisionWord1 << std::endl;
    std::cout << "*** (DEBUG) AlgoBits_upperRange = " << AlgoBits_upperRange << " = " << AlgoJetDecisionWord2 << std::endl;
    std::cout << "*** (DEBUG) HLTBits = " << HLTBits << " = " << HLTDecisionWord << std::endl;
  }

  if( show_trigger_menu ) {
    ShowTriggerMenu();
    show_trigger_menu = false;
  }
}

void 
CastorMkL1TestTree::GetL1TriggerInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  int iErrorCode = -1;

  const L1GtTriggerMenu* L1GtMenu            = m_L1GtUtils.ptrL1TriggerMenuEventSetup(iErrorCode);
  const AlgorithmMap&    algorithmMap        = L1GtMenu->gtAlgorithmMap();
  const AlgorithmMap&    technicalTriggerMap = L1GtMenu->gtTechnicalTriggerMap();

  if( show_debug_info ) std::cout << "*** (DEBUG) AlgorithmMap size: " << algorithmMap.size() << std::endl;
  for(CItAlgo itAlgo = algorithmMap.begin(); itAlgo != algorithmMap.end(); itAlgo++) {
    std::string algName      = itAlgo->first;
    int algoBitNumber         = ( itAlgo->second ).algoBitNumber();
    //function identical with decisionAfterMask
    bool decision            = m_L1GtUtils.decision(iEvent, itAlgo->first, iErrorCode);

    if( show_trigger_menu ) {
      L1Algo_Menu[algoBitNumber] = algName;
    }

    if( algoBitNumber < 64 ) AlgoBits_lowRange[algoBitNumber] = decision;
    else AlgoBits_upperRange[algoBitNumber-64] = decision;
  }

if( show_debug_info ) std::cout << "*** (DEBUG) TechnicalTriggerMap size: " << technicalTriggerMap.size() << std::endl;
  for (CItAlgo itAlgo = technicalTriggerMap.begin(); itAlgo != technicalTriggerMap.end(); itAlgo++) {
    std::string algName      = itAlgo->first;
    int algoBitNumber        = ( itAlgo->second ).algoBitNumber();
    bool decision            = m_L1GtUtils.decision(iEvent, itAlgo->first, iErrorCode);

    if( show_trigger_menu ) {
      L1TT_Menu[algoBitNumber] = algName;
    }

    L1TTBits[algoBitNumber] = decision;
  }
  

}

void 
CastorMkL1TestTree::GetHLTriggerInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  std::vector< std::pair<bool,int> > HLT_path_bits;
  HLT_path_bits.resize( HLT_path_names.size(), std::pair<bool,int>(false,-1) );

  for (size_t iBitHLT = 0; iBitHLT < hltConfig.triggerNames().size(); iBitHLT++) {
    for(size_t iHLTpath = 0; iHLTpath < HLT_path_names.size(); iHLTpath++)
      if( TString(hltConfig.triggerNames()[iBitHLT]).Contains(HLT_path_names[iHLTpath].c_str()) ) {
        if( show_debug_info ) 
          std::cout << "*** (DEBUG) HLT path: " << HLT_path_names[iHLTpath] 
                    << " found for HLT bit: " << iBitHLT << std::endl;
        HLT_path_bits[iHLTpath].first  = true;
        HLT_path_bits[iHLTpath].second = iBitHLT;
      }
    
    if( show_trigger_menu ) {
      HLT_Menu[iBitHLT] = std::string(hltConfig.triggerNames()[iBitHLT]);
    }
  }
  for(size_t iHLTpath = 0; iHLTpath < HLT_path_bits.size(); iHLTpath++) {
    if( HLT_path_bits[iHLTpath].first == true ) {
      if( show_debug_info ) 
          std::cout << "*** (DEBUG) HLT[" <<  HLT_path_bits[iHLTpath].second
                    << "]: " << HLT_path_names[iHLTpath] << " = " << 0 << std::endl;
      HLTBits[iHLTpath] = TrigResults->accept( HLT_path_bits[iHLTpath].second );
    }
  }
}

void
CastorMkL1TestTree::ShowTriggerMenu()
{
  std::cout << "*** L1 TechnicalTrigger Menu ***" << std::endl;
  for(std::map<int,std::string>::iterator it = L1TT_Menu.begin(); it != L1TT_Menu.end(); it++)
    std::cout << "   *** L1 TT Bit[" << it->first << "] = " << it->second << std::endl;

  std::cout << "*** L1 Algorith Menu ***" << std::endl;
  for(std::map<int,std::string>::iterator it = L1Algo_Menu.begin(); it != L1Algo_Menu.end(); it++)
    std::cout << "   *** L1 Algo Bit[" << it->first << "] = " << it->second << std::endl;

  std::cout << "*** HLT Menu ***" << std::endl;
  for(std::map<int,std::string>::iterator it = HLT_Menu.begin(); it != HLT_Menu.end(); it++)
    std::cout << "   *** HLT Bit[" << it->first << "] = " << it->second << std::endl;
}

int
CastorMkL1TestTree::GetPileUp(edm::Handle< std::vector<PileupSummaryInfo> >& vPU)
{
  for(unsigned int i=0; i<vPU->size(); i++)
  {
    // gives you number of events which were additionally added to this event
    if( vPU->at(i).getBunchCrossing() == 0 ) return vPU->at(i).getPU_NumInteractions();
  }

  return -1;
}

void
CastorMkL1TestTree::CollectGenParticles()
{
  fspart->Clear();
  fspart_size = 0;

  totem_mpl[0] = 0; totem_mpl[1] = 0;

  // GenParticles
  for(size_t i=0; i < GenPartColl->size(); i++)
    {
      const reco::GenParticle & genpart = (*GenPartColl)[i];
  
      if( genpart.status() != 1 )
        continue;

      // only t2 acceptance
      if( std::abs(genpart.eta()) > 5.4 && std::abs(genpart.eta()) < 6.6 &&
          genpart.charge() != 0 )
      {
        if( genpart.eta() > 0 ) totem_mpl[0]++;
        else totem_mpl[1]++;
      }

      // if( std::abs(genpart.pdgId()) != 13 )
      //   continue;

      TVector3 gp_mom(genpart.px(), genpart.py(), genpart.pz());
      double gp_m = genpart.mass();

      TLorentzVector lvgenpart; lvgenpart.SetVectM( gp_mom, gp_m );

      if( fspart_size < max_genpart_size ) {
        new((*fspart)[fspart_size]) TLorentzVector(lvgenpart);
        fspart_id[fspart_size] = genpart.pdgId();
      }

      fspart_size++;
    }
}

void
CastorMkL1TestTree::CollectGenJets()
{
  genjet->Clear();
  genjet_size = 0;

  for(size_t i=0; i < GenJetColl->size(); i++)
  {
    const reco::GenJet & jet = (*GenJetColl)[i];

    TLorentzVector lvjet( jet.px(), jet.py(), jet.pz(), jet.energy() );

    if( genjet_size < max_jet_size ) new((*genjet)[genjet_size]) TLorentzVector(lvjet);
    genjet_size++;
  }
}

void 
CastorMkL1TestTree::CollectCasRecHits()
{
  // Get CastorRecHits
  for (size_t i = 0; i < CasRecHitColl->size(); i++)
    {
      const CastorRecHit & rh = (*CasRecHitColl)[i];
      int isec = rh.id().sector()-1;
      int imod = rh.id().module()-1;
      cas_energy[isec][imod] = rh.energy();
    }
}

void 
CastorMkL1TestTree::CollectCasJets()
{
  casjet->Clear();
  casjet_size = 0;

  // Get CastorJets
  for(size_t i = 0; i < BasicJetView->size(); i++)
    {
      const reco::BasicJet & basicjet = (*BasicJetView)[i];
      // edm::RefToBase<reco::BasicJet> jetRef = BasicJetView->refAt(i);
      // reco::CastorJetID const & jetId = (*CasJetIdMap)[jetRef];

      TLorentzVector lvjet( basicjet.px(), basicjet.py(), basicjet.pz(), basicjet.energy() );
      
      if( casjet_size < max_jet_size ) new((*casjet)[casjet_size]) TLorentzVector(lvjet);
      casjet_size++;
    }
}

void
CastorMkL1TestTree::CollectVertices()
{
  vertex->Clear();
  vertex_size = 0;

  // Get Vertices
  for(size_t i = 0; i < VertexColl->size(); i++)
    {
      const reco::Vertex & vtx = (*VertexColl)[i];

      //if( !vtx.isValid() || vtx.isFake() ) continue;

      TVector3 vVtx( vtx.x(), vtx.y(), vtx.z() );

      if( vertex_size < max_vtx_size ) {
        new((*vertex)[vertex_size]) TVector3(vVtx);
        vtx_ndof[vertex_size] = vtx.ndof();
        vtx_fake[vertex_size] = vtx.isFake() ? 1 : 0;
        vtx_fake[vertex_size] += vtx.isValid() ? 2 : 0;
      }
      vertex_size++;
    }
}

// ------------ method called once each job just before starting event loop  ------------
void 
CastorMkL1TestTree::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CastorMkL1TestTree::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
CastorMkL1TestTree::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
CastorMkL1TestTree::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
CastorMkL1TestTree::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
CastorMkL1TestTree::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CastorMkL1TestTree::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CastorMkL1TestTree);
