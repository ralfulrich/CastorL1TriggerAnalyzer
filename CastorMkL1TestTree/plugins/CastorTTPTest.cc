// -*- C++ -*-
//
// Package:    CastorL1Valid/CastorL1Test
// Class:      CastorL1Test
// 
/**\class CastorL1Test CastorL1Test.cc CastorL1Valid/CastorL1Test/plugins/CastorL1Test.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Clemens Wohrmann
//         Created:  Wed, 24 Sep 2014 14:54:14 GMT
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

// include root files
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"


// // user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// // include tracks
// #include "DataFormats/TrackReco/interface/Track.h"
// #include "DataFormats/TrackReco/interface/TrackFwd.h"

// // include vertices
// #include "DataFormats/VertexReco/interface/Vertex.h"
// #include "DataFormats/VertexReco/interface/VertexFwd.h"

// // include electrons
// #include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
// #include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

// // include HF electrons
// #include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
// #include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"

// // HCAL & ECAL RecHit
// #include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
// #include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

// // HCAL Towers
// #include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

// // include castorrechits
// #include "DataFormats/HcalRecHit/interface/CastorRecHit.h"
// #include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

// // include castortowers
// #include "DataFormats/CastorReco/interface/CastorTower.h"

// // include castorjets
// #include "DataFormats/JetReco/interface/BasicJet.h"
// #include "DataFormats/JetReco/interface/CastorJetID.h"
// #include "DataFormats/Common/interface/ValueMap.h"

// // include ZDC digis
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
// #include "DataFormats/HcalRecHit/interface/ZDCRecHit.h"

// // include digi converter
// #include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
// #include "CalibFormats/HcalObjects/interface/HcalDbService.h"
// #include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

// // include MET
// #include "DataFormats/METReco/interface/PFMET.h"
// #include "DataFormats/METReco/interface/PFMETFwd.h"

// // include GenParticles
// #include "DataFormats/HepMCCandidate/interface/GenParticle.h"
// #include "DataFormats/JetReco/interface/GenJet.h"
// #include "DataFormats/JetReco/interface/GenJetCollection.h"

// // include SimVertices
// #include "SimDataFormats/Vertex/interface/SimVertex.h"
// #include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

// // geometry
// #include "Geometry/CaloTopology/interface/HcalTopology.h"
// #include "Geometry/CaloGeometry/interface/CaloGeometry.h"
// #include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
// #include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
// #include "Geometry/Records/interface/CaloGeometryRecord.h"

// // HLT Trigger
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"

// L1 Trigger DataFormats
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
// //#include "L1Trigger/GlobalTrigger/interface/L1GlobalTrigger.h"

// // Pileup Information
// #include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMask.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskAlgoTrigRcd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskTechTrigRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"


// Castor Digi Info
// #include "DataFormats/HcalDigi/interface/CastorDataFrame.h"
// #include "DataFormats/HcalDetId/interface/HcalCastorDetId.h"

// #include "CondFormats/CastorObjects/interface/CastorQIEShape.h"
// #include "CondFormats/CastorObjects/interface/CastorQIECoder.h"
#include "CalibFormats/CastorObjects/interface/CastorCoderDb.h"
#include "CalibFormats/CastorObjects/interface/CastorDbService.h"
#include "CalibFormats/CastorObjects/interface/CastorDbRecord.h"
#include "CalibFormats/CastorObjects/interface/CastorCoder.h"
// #include "CalibFormats/CastorObjects/interface/CastorChannelCoder.h"

// // include cmssw-lorentzvector (is pointing over typedef's to root TLorentzVector)
// #include "DataFormats/Candidate/interface/LeafCandidate.h"

#define UNUSED(x) ((void)(x))

//
// class declaration
//

class CastorTTPTest : public edm::EDAnalyzer {
   public:
      //-- trigger helper struct
      struct MyCastorTrig {
        short int sample;               /**< Time sample; 0 corresponds to the triggering sample */ 
        //  std::vector<bool> ttpInput;     /**< ttp Inputs; more infor from Alan Camplell */ 
        bool octantsA[8];               /**< octant-wise trigger info for threshold A */ 
        bool octantsEM[8];              /**< octant-wise EM trigger  */ 
        bool octantsHADveto[8];         /**< octant-wise veto on HAD */ 
        bool octantsMuon[8];            /**< octant-wise muon trigger */
        unsigned int TTP_Bits[8];       /*** Hauke: TTP trigger word I guess ***/
        // TPGa_data_Bits only usefull for sample -2 to 1
        unsigned int TPGa_data_Bits[8]; /*** Hauke: HTR trigger word I guess ***/

        void clear() {
          sample = 0;
          for(int i=0; i<8; i++) {
            octantsA[i]       = false;
            octantsEM[i]      = false;
            octantsHADveto[i] = false;
            octantsMuon[i]    = false;
            TTP_Bits[i]       = 0;
            TPGa_data_Bits[i] = 0;
          }
        }

        void print() {
          std::cout << "sample# " << sample << "\n";
          for ( int tpg = 0; tpg < 8 ; tpg+=1 ) {
            std::cout << tpg << "   " 
                      << octantsMuon[tpg]    << "  " 
                      << octantsHADveto[tpg] << "  "  // Hadron veto
                      << octantsA[tpg]       << "  "     // summ
                      << octantsEM[tpg]      << "  "     // EM
                      <<  "\t" 
                      << TTP_Bits[tpg]       << "  " 
                      << TPGa_data_Bits[tpg] << std::endl;
          }
        }

      };


      explicit CastorTTPTest(const edm::ParameterSet&);
      ~CastorTTPTest();

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
      bool GetCollections(const edm::Event& iEvent);

      void SetMuonTriggerSum(const edm::EventSetup&);
      CastorTTPTest::MyCastorTrig GetTTPperTSshift(const HcalTTPDigi&, const int&, const int&, const int&);
      void SetTPGaBits(unsigned int*, const int&, const int&);

      void GetL1TTResults(const edm::Event&, const edm::EventSetup&);

      // ----------member data ---------------------------
      bool debugInfo;
      L1GtUtils m_l1GtUtils;
      bool show_trigger_menu;
      std::map<int,std::string> L1TT_Menu;

      double MuonTriggerSum_fC_Per_Sector_PositionFrontMiddleBack_TS[16][3][10];

      // --------- input labels for collections ----------

      // --------- collection handel ---------------------
      edm::Handle<CastorTrigPrimDigiCollection> castortpg;
      edm::Handle<HcalTTPDigiCollection>        castorttp;
      edm::Handle<CastorDigiCollection>         digicoll;

      // --------- tree variables ------------------------
      // TTree* myTree;
      std::map<std::string,TH1*> h1;
      std::map<std::string,TH2*> h2;

      edm::Service<TFileService> fs;

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
CastorTTPTest::CastorTTPTest(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  GetParameterSet(iConfig);

  // myTree = fs->make<TTree>("myTree","myTree");

  h1["hRelBxMuOct"]   = fs->make<TH1D>("hRelBxMuOct","",10,-3.5,6.5);
  h1["hRelBxTotEOct"] = fs->make<TH1D>("hRelBxTotEOct","",10,-3.5,6.5);

  h1["hBxMuOct"]   = fs->make<TH1D>("hBxMuOct","",4000,0,4000);
  h1["hBxTotEOct"] = fs->make<TH1D>("hBxTotEOct","",4000,0,4000);
  h1["hBxAllEvt"]  = fs->make<TH1D>("hBxAllEvt","",4000,0,4000);

  h1["hOctATrig"] = fs->make<TH1D>("hOctATrig","",8,0,8);
}


CastorTTPTest::~CastorTTPTest()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
CastorTTPTest::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  // Get all necessary collections
  if( !GetCollections(iEvent) ) return;

  // if( debugInfo ) std::cout << "NEW EVENT" << std::endl;

  int evtnbr = iEvent.id().event();
  int evtbx  = iEvent.bunchCrossing();

  h1["hBxAllEvt"]->Fill(evtbx);

  SetMuonTriggerSum(iSetup);

  std::vector< CastorTTPTest::MyCastorTrig > castorTrigger; castorTrigger.clear();
  

  int ttp_offset    = 0; // ts of ttp data used wrt SOI
  int ts_tpg_offset = 0; // ts of tpg used wrt SOI
  const HcalTTPDigi t = (const HcalTTPDigi)(*(castorttp->begin()));

  for(int tsshift = -2; tsshift < 6; tsshift++){
    CastorTTPTest::MyCastorTrig trigger = GetTTPperTSshift(t,tsshift,ttp_offset,ts_tpg_offset);
    

    bool fillmuocttrig = true;
    bool filltoteocttrig = true;
    bool print = false;
    for ( int tpg = 0; tpg < 8 ; tpg+=2 ) {
    
      if( debugInfo ) {
        if( trigger.octantsMuon[tpg] ) {
          std::cout << "Muon         Triggered on Octant:" << tpg << " with tsshift:" << tsshift << std::endl;
        }
        // if( trigger.octantsA[tpg] ) {
        //   std::cout << "Total Energy Triggered on Octant:" << tpg << " with tsshift:" << tsshift << std::endl;
        // }
        if( trigger.octantsMuon[tpg+1] ) {
          std::cout << "Muon         Triggered on Octant:" << tpg+1 << " with tsshift:" << tsshift << std::endl;
        }
        // if( trigger.octantsA[tpg+1] ) {
        //   std::cout << "Total Energy Triggered on Octant:" << tpg+1 << " with tsshift:" << tsshift << std::endl;
        // }
      }

      if( (trigger.TTP_Bits[tpg] != trigger.TPGa_data_Bits[tpg]) || (trigger.TTP_Bits[tpg+1] != trigger.TPGa_data_Bits[tpg+1]) ) {
        print = true;
      }

      if( fillmuocttrig && (trigger.octantsMuon[tpg] || trigger.octantsMuon[tpg+1]) ) {
        h1["hRelBxMuOct"]->Fill(tsshift);
        h1["hBxMuOct"]->Fill(evtbx+tsshift);
        fillmuocttrig = false;
      }
      if( filltoteocttrig && (trigger.octantsA[tpg] || trigger.octantsA[tpg+1]) ) {
        h1["hRelBxTotEOct"]->Fill(tsshift);
        h1["hBxTotEOct"]->Fill(evtbx+tsshift);
        filltoteocttrig = false;
      }

      if( trigger.octantsA[tpg] ) h1["hOctATrig"]->Fill(tpg);
      if( trigger.octantsA[tpg+1] ) h1["hOctATrig"]->Fill(tpg+1);
    } // end for tpg


    if( tsshift >= -2 && tsshift <= 1 ) {
      if(print) trigger.print();
    }

    int noct_muon = 0;
    int noct_tot  = 0;
    for( int ioct=0; ioct<8; ioct++) {
      if( trigger.octantsMuon[ioct] ) noct_muon++;
      if( trigger.octantsA[ioct] ) noct_tot++;
    }
    if( noct_muon == 1 && noct_tot == 0 ) 
      std::cout << "**(TTP)** In Event:" << evtnbr << " Castor Muon should trigger with tsshift:" << trigger.sample << std::endl;

    // if(CastorDigiAndTrigDebug) trigger.Print();
    castorTrigger.push_back(trigger);
      
  } // loop over tsshift


  GetL1TTResults(iEvent,iSetup);

  

}

// ------------ methods to get detector collections --------------------------------------
void
CastorTTPTest::GetParameterSet(const edm::ParameterSet& iConfig)
{
  // define collections
  debugInfo = iConfig.getParameter<bool>("debugInfo");
  show_trigger_menu = iConfig.getParameter<bool>("ShowTriggerMenu");
}

bool 
CastorTTPTest::GetCollections(const edm::Event& iEvent)
{
  // the collection types are defined in  DataFormats/HcalDigi/interface/HcalDigiCollections.h
  // iEvent.getByType(castorttp);
  iEvent.getByLabel("castorDigis",castorttp);
  iEvent.getByLabel("castorDigis",digicoll);
  iEvent.getByLabel("castorDigis",castortpg);


  return true;
}

void 
CastorTTPTest::SetMuonTriggerSum(const edm::EventSetup& iSetup)
{
  // first clean array
  for( int isec = 0; isec < 16; isec++ ) {
    for( int ipos = 0; ipos < 3; ipos++ ) {
      for( int iTS = 0; iTS < 10; iTS++ ) {
        MuonTriggerSum_fC_Per_Sector_PositionFrontMiddleBack_TS[isec][ipos][iTS] = 0;
      }
    }
  }


  // QIE coder to convert to fC
  // get conditions
  edm::ESHandle<CastorDbService> conditions;
  iSetup.get<CastorDbRecord>().get(conditions);
  const CastorQIEShape* shape = conditions->getCastorShape ();
  
  //-- loop over the digi collection (224 digis)
  for(size_t i = 0; i < digicoll->size(); i++) { 
  
    CastorDataFrame digi = (*digicoll)[i];
    HcalCastorDetId castorid = digi.id();
    
    const CastorQIECoder* channelCoder = conditions->getCastorCoder (castorid);
    CastorCoderDb coder (*channelCoder, *shape);
    CaloSamples tool;
    coder.adc2fC(digi,tool);

    // castorDigis[i].mod = castorid.module();
    // castorDigis[i].sec = castorid.sector();
    // castorDigis[i].cha = 16*(castorid.module()-1) + castorid.sector();
    
    int isec = castorid.sector()-1;
    int imod = castorid.module()-1;
    int ipos = imod > 11 ? -1 : ( imod > 7 ? 2 : ( imod > 3 ? 1 : 0 ) );

    //-- loop over the 6 or 10 time slices for each digi
    for (int ts = 0; ts < digi.size(); ts++) {   
      // castorDigis[i].adc.push_back(digi[ts].adc());
      // castorDigis[i].fC.push_back(tool[ts]);
      if( ipos != -1 ) MuonTriggerSum_fC_Per_Sector_PositionFrontMiddleBack_TS[isec][ipos][ts] += tool[ts];
    }
  }
}

CastorTTPTest::MyCastorTrig 
CastorTTPTest::GetTTPperTSshift(const HcalTTPDigi& t, const int& tsshift, const int& ttp_offset, const int& ts_tpg_offset)
{
  CastorTTPTest::MyCastorTrig trigger;
  trigger.clear();

  std::vector<bool> ttpInput = t.inputPattern(ttp_offset+tsshift); // at ts = ttp_offset from nominal zero ttp_offset
  // sequence is Atop,Abot,Bbot,Btop,raptop,rapbot,muonbot,muontop                                    
  // htr 3t 3b 4t 4b 5t 5b 7t 7b map to tpg 0..7  

  trigger.sample   = tsshift;

  for ( int tpg = 0; tpg < 8 ; tpg+=2 ) {
    trigger.octantsA[tpg]         = ttpInput[0+(8*(tpg/2))];
    trigger.octantsA[tpg+1]       = ttpInput[1+(8*(tpg/2))];
    trigger.octantsEM[tpg]        = ttpInput[3+(8*(tpg/2))];
    trigger.octantsEM[tpg+1]      = ttpInput[2+(8*(tpg/2))];
    trigger.octantsHADveto[tpg]   = ttpInput[4+(8*(tpg/2))];
    trigger.octantsHADveto[tpg+1] = ttpInput[5+(8*(tpg/2))];
    trigger.octantsMuon[tpg]      = ttpInput[7+(8*(tpg/2))];
    trigger.octantsMuon[tpg+1]    = ttpInput[6+(8*(tpg/2))];
    trigger.TTP_Bits[tpg]         = ((trigger.octantsMuon[tpg] ? 1 : 0)<<3) |
                                    ((trigger.octantsHADveto[tpg] ? 0 : 1)<<2) |
                                    ((trigger.octantsA[tpg] ? 0 : 1)<<1) |
                                    (trigger.octantsEM[tpg] ? 1 : 0);
    trigger.TTP_Bits[tpg+1]       = ((trigger.octantsMuon[tpg+1] ? 1 : 0)<<3) |
                                    ((trigger.octantsHADveto[tpg+1] ? 0 : 1)<<2) |
                                    ((trigger.octantsA[tpg+1] ? 0 : 1)<<1) |
                                    (trigger.octantsEM[tpg+1] ? 1 : 0);
  }

  if( tsshift >= -2 && tsshift <= 1 ) {
    SetTPGaBits(trigger.TPGa_data_Bits,tsshift,ts_tpg_offset);
  }

  return trigger;
}

void 
CastorTTPTest::SetTPGaBits(unsigned int* TPGa_data_Bits, const int& tsshift, const int& ts_tpg_offset)
{
  for(CastorTrigPrimDigiCollection::const_iterator j=castortpg->begin(); j!=castortpg->end(); j++) {
    const CastorTriggerPrimitiveDigi ctp = (const CastorTriggerPrimitiveDigi)(*j);

    int i = ctp.presamples()+ts_tpg_offset+tsshift;
    int isec = ctp.id().sector();

    // std::cout << "CastorTriggerPrimitiveDigi bits ch " << ctp.tpchannel(i) << std::endl;
        
    if( ctp.tpchannel(i) == 4 ) {
      TPGa_data_Bits[isec/2]   = ctp.tpdata(i);
    }

    // if( debugInfo ) std::cout << "CastorTriggerPrimitiveDigi.id().sector():" << isec << std::endl;
  }
}

void 
CastorTTPTest::GetL1TTResults(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  int evtnbr = iEvent.id().event();

  bool useL1EventSetup = true;
  bool useL1GtTriggerMenuLite = true;

  m_l1GtUtils.getL1GtRunCache(iEvent, iSetup, useL1EventSetup, useL1GtTriggerMenuLite);

  int iErrorCode = -1;
  int l1ConfCode = -1;
  const bool l1Conf = m_l1GtUtils.availableL1Configuration(iErrorCode, l1ConfCode);
  if( !l1Conf ) { std::cerr << " (*W*) No valid L1 trigger configuration; code: " << l1Conf << std::endl; }

  const L1GtTriggerMenu* m_l1GtMenu          = m_l1GtUtils.ptrL1TriggerMenuEventSetup(iErrorCode);
  const AlgorithmMap&    algorithmMap        = m_l1GtMenu->gtAlgorithmMap();
  const AlgorithmMap&    technicalTriggerMap = m_l1GtMenu->gtTechnicalTriggerMap();

  UNUSED(algorithmMap);


  for (CItAlgo itAlgo = technicalTriggerMap.begin(); itAlgo != technicalTriggerMap.end(); itAlgo++) {
    std::string algName      = itAlgo->first;
    int algoBitNumber        = ( itAlgo->second ).algoBitNumber();
    // bool algResultBeforeMask = m_l1GtUtils.decisionBeforeMask(iEvent, itAlgo->first, iErrorCode);
    // bool algResultAfterMask  = m_l1GtUtils.decisionAfterMask (iEvent, itAlgo->first, iErrorCode);
    // int  triggerMask         = m_l1GtUtils.triggerMask       (iEvent, itAlgo->first, iErrorCode);
    bool decision            = m_l1GtUtils.decision          (iEvent, itAlgo->first, iErrorCode);
    // int  preScale            = m_l1GtUtils.prescaleFactor    (iEvent, itAlgo->first, iErrorCode);


    if( show_trigger_menu ) {
      L1TT_Menu[algoBitNumber] = algName;
    }
    if( decision && (algoBitNumber>=60 && algoBitNumber<=63) ) 
      std::cout << "*** In Event " << evtnbr << " => TechnicalTrigger Bit " << algoBitNumber << " triggered" << std::endl;
  }

  if( show_trigger_menu ) {
    std::cout << "*** L1 TechnicalTrigger Menu ***" << std::endl;
    for(std::map<int,std::string>::iterator it = L1TT_Menu.begin(); it != L1TT_Menu.end(); it++)
      std::cout << "   *** L1 TT Bit[" << it->first << "] = " << it->second << std::endl;

    show_trigger_menu = false;
  }
}

// ------------ method called once each job just before starting event loop  ------------
void 
CastorTTPTest::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CastorTTPTest::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
CastorTTPTest::beginRun(edm::Run const&, edm::EventSetup const&, HLTBits;
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
CastorTTPTest::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
CastorTTPTest::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
CastorTTPTest::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CastorTTPTest::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CastorTTPTest);
