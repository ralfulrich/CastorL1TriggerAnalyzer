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

// // HLT Trigger
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"

// L1 Trigger DataFormats
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMask.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskAlgoTrigRcd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskTechTrigRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"

// Hcal Digi Info
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

// Castor Digi Info
#include "CalibFormats/CastorObjects/interface/CastorCoderDb.h"
#include "CalibFormats/CastorObjects/interface/CastorDbService.h"
#include "CalibFormats/CastorObjects/interface/CastorDbRecord.h"
#include "CalibFormats/CastorObjects/interface/CastorCoder.h"


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

        bool sector_muon_trigger[16][12]; /*** Hauke: channel above threshold for muon ***/

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
          for(int i=0; i<16; i++)
            for(int j=0; j<12; j++)
              sector_muon_trigger[i][j] = false;
        }

        void print() const {
          std::cout << "sample# " << sample << std::endl;
          std::cout << "tpg M  Hv A  EM " << "\t" << "TTP TPGa" << std::endl;
          for ( int tpg = 0; tpg < 8 ; tpg+=1 ) {
            std::cout << tpg << "   " 
                      << octantsMuon[tpg]    << "  " 
                      << octantsHADveto[tpg] << "  "  // Hadron veto
                      << octantsA[tpg]       << "  "     // summ
                      << octantsEM[tpg]      << "  "     // EM
                      << "\t" 
                      << TTP_Bits[tpg]       << "  " 
                      << TPGa_data_Bits[tpg] << std::endl;
          }
        }

        void detail_print() const {
          std::cout << "sample# " << sample << std::endl;
          std::cout << "tpg M  Hv A  EM " << "\t" << "TTP TPGa\tN_ch>Noise" << std::endl;
          for ( int tpg = 0; tpg < 8 ; tpg+=1 ) {
            std::cout << tpg << "   " 
                      << octantsMuon[tpg]    << "  " 
                      << octantsHADveto[tpg] << "  "  // Hadron veto
                      << octantsA[tpg]       << "  "     // summ
                      << octantsEM[tpg]      << "  "     // EM
                      << "\t" 
                      << TTP_Bits[tpg]       << "   " 
                      << TPGa_data_Bits[tpg] << "   "
                      << "\t";
            for(int i=0; i<12; i++) std::cout << sector_muon_trigger[tpg*2][i] << " ";
            std::cout << std::endl;
            std::cout << "                \t        \t";
            for(int i=0; i<12; i++) std::cout << sector_muon_trigger[tpg*2+1][i] << " ";
            std::cout << std::endl;
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

      CastorTTPTest::MyCastorTrig GetTTPperTSshift(const HcalTTPDigi&, const int&, const int&, const int&);
      unsigned long int CreateTTPBitWord(const CastorTTPTest::MyCastorTrig&, const int&);
      void SetTPGaBits(unsigned int*, const int&, const int&);

      // create only muon and octantA trigger correctly NOT the other ones
      CastorTTPTest::MyCastorTrig GetTTPperTSshiftFromDigis(const int&, const int&);

      bool IsCastorMuon(const CastorTTPTest::MyCastorTrig&);

      void GetL1TTResults(const edm::Event&, const edm::EventSetup&);

      // ----------member data ---------------------------
      bool debugInfo;
      L1GtUtils m_l1GtUtils;
      bool show_trigger_menu;
      std::map<int,std::string> L1TT_Menu;
      std::map<int,std::string> L1Algo_Menu;

      // --------- input labels for collections ----------

      // --------- collection handel ---------------------
      edm::Handle<CastorTrigPrimDigiCollection> castortpg; // HTR card output
      edm::Handle<HcalTTPDigiCollection>        castorttp; // TTP input
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

const unsigned int kNCastorDigiTimeSlices = 6;
const unsigned int kNCastorSectors = 16;
const unsigned int kNCastorModules = 14;
const unsigned int kMuonThresholdTableAdc[2][12] = {{12,11,11,10,11,12,10,11,10,15,11,10},
                                                    {11,11,10,11,10,10,11,11,11,12,10,10}};

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

  int nBxBins = 4000;
  double minBx = 0, maxBx = 4000;

  h1["hRelBxMuOct"]   = fs->make<TH1D>("hRelBxMuOct","",10,-3.5,6.5);
  h1["hRelBxTotEOct"] = fs->make<TH1D>("hRelBxTotEOct","",10,-3.5,6.5);
  h1["hRelBxGlCasMu"] = fs->make<TH1D>("hRelBxGlCasMu","",10,-3.5,6.5);

  h1["hBxMuOct"]   = fs->make<TH1D>("hBxMuOct","",nBxBins,minBx,maxBx);
  h1["hBxTotEOct"] = fs->make<TH1D>("hBxTotEOct","",nBxBins,minBx,maxBx);
  h1["hBxAllEvt"]  = fs->make<TH1D>("hBxAllEvt","",nBxBins,minBx,maxBx);
  h1["hBxGlCasMu"] = fs->make<TH1D>("hBxGlCasMu","",nBxBins,minBx,maxBx);

  char buf[128];
  for(int ioct=0; ioct<8; ioct++) {
    sprintf(buf,"hBxMuOct_%d",ioct);
    h1[buf] = fs->make<TH1D>(buf,"",nBxBins,minBx,maxBx);

    sprintf(buf,"hBxTotEOct_%d",ioct);
    h1[buf] = fs->make<TH1D>(buf,"",nBxBins,minBx,maxBx);
  }

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

  std::vector< CastorTTPTest::MyCastorTrig > castorTrigger; castorTrigger.clear();
  
  int ttp_offset     = 0; // ts of ttp data used wrt SOI
  int ts_tpg_offset  = 0; // ts of tpg used wrt SOI
  int ts_digi_offset = 4; // ts of digi compared to ttp=0
  const HcalTTPDigi t = (const HcalTTPDigi)(*(castorttp->begin()));

  // for(int tsshift = -2; tsshift < 6; tsshift++){
  // change from 6 to 2 because with a ts_digi_offset of 4 tsshift=2 means look at digi ts 6 which is already the last one
  for(int tsshift = -2; tsshift < 2; tsshift++){
    const CastorTTPTest::MyCastorTrig trigger      = GetTTPperTSshift(t,tsshift,ttp_offset,ts_tpg_offset);
    const CastorTTPTest::MyCastorTrig digi_trigger = GetTTPperTSshiftFromDigis(tsshift+ts_digi_offset,ts_digi_offset);

    bool fillmuocttrig = true;
    bool filltoteocttrig = true;
    bool htr_ttp_diff_print = false;
    bool muon_trig_print = false;
    for ( int ioct = 0; ioct < 8 ; ioct++ ) {

      char buf[128];

      if( trigger.octantsMuon[ioct] ) {
        muon_trig_print = true;

        sprintf(buf,"hBxMuOct_%d",ioct);
        h1[buf]->Fill(evtbx+tsshift);

        if( fillmuocttrig ) {
          h1["hRelBxMuOct"]->Fill(tsshift);
          h1["hBxMuOct"]->Fill(evtbx+tsshift);
          fillmuocttrig = false;
        }
      }
    
      if( !trigger.octantsA[ioct] ) {
        sprintf(buf,"hBxTotEOct_%d",ioct);
        h1[buf]->Fill(evtbx+tsshift);

        if( filltoteocttrig ) {
          h1["hRelBxTotEOct"]->Fill(tsshift);
          h1["hBxTotEOct"]->Fill(evtbx+tsshift);
          filltoteocttrig = false;
        }

        h1["hOctATrig"]->Fill(ioct);
      }

      if( trigger.TTP_Bits[ioct] != trigger.TPGa_data_Bits[ioct] ) {  
        htr_ttp_diff_print = true;
      }
    } // end for ioct

    // region for CastorTrigPrimDigiCollection is just from -2 to 1
    if( tsshift >= -2 && tsshift <= 1 ) {
      if(htr_ttp_diff_print) {
        std::cout << "*** TTP Input != HTR output with tsshift:" << tsshift << std::endl;
        trigger.print();
      }
    }

    if( muon_trig_print && debugInfo ) {
      std::cout << "*** Muon Triggered on at least one Octant:" << std::endl;
      trigger.print();
      std::cout << "    from own digi reco:" << std::endl;
      digi_trigger.detail_print();
    }

    if( IsCastorMuon(trigger) ) {
      h1["hRelBxGlCasMu"]->Fill(tsshift);
      h1["hBxGlCasMu"]->Fill(evtbx+tsshift);

      std::cout << "**(TTP)** In Event:" << evtnbr 
                << " Castor Muon should trigger with tsshift:" << trigger.sample 
                << std::endl;
      trigger.print();
    }

    // if(CastorDigiAndTrigDebug) trigger.Print();
    castorTrigger.push_back(trigger);
      
  } // loop over tsshift

  GetTTPperTSshiftFromDigis(0,0);

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
  try{ iEvent.getByLabel("castorDigis", castorttp); }
  catch(...) { edm::LogWarning(" HcalTTPDigiCollection ") << " Cannot get HcalTTPDigiCollection " << std::endl; }
  
  if( !castorttp.isValid() || castorttp.failedToGet() ) {
    edm::LogWarning(" HcalTTPDigiCollection ") << " Cannot read HcalTTPDigiCollection " << std::endl;
    return false;
  }

  try{ iEvent.getByLabel("castorDigis", digicoll); }
  catch(...) { edm::LogWarning(" CastorDigiCollection ") << " Cannot get CastorDigiCollection " << std::endl; }
  
  if( !digicoll.isValid() || digicoll.failedToGet() ) {
    edm::LogWarning(" CastorDigiCollection ") << " Cannot read CastorDigiCollection " << std::endl;
    return false;
  }

  try{ iEvent.getByLabel("castorDigis", castortpg); }
  catch(...) { edm::LogWarning(" CastorTrigPrimDigiCollection ") << " Cannot get CastorTrigPrimDigiCollection " << std::endl; }
  
  if( !castortpg.isValid() || castortpg.failedToGet() ) {
    edm::LogWarning(" CastorTrigPrimDigiCollection ") << " Cannot read CastorTrigPrimDigiCollection " << std::endl;
    return false;
  }

  return true;
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
    trigger.TTP_Bits[tpg]         = CreateTTPBitWord(trigger,tpg);
    trigger.TTP_Bits[tpg+1]       = CreateTTPBitWord(trigger,tpg+1);
  }

  if( tsshift >= -2 && tsshift <= 1 ) {
    SetTPGaBits(trigger.TPGa_data_Bits,tsshift,ts_tpg_offset);
  }

  return trigger;
}


unsigned long int
CastorTTPTest::CreateTTPBitWord(const CastorTTPTest::MyCastorTrig& trigger, const int& tpg)
{
  std::bitset<4> Bits;

  Bits[0] = trigger.octantsEM[tpg];
  // needs to be inverted because veto
  Bits[1] = !trigger.octantsA[tpg];
  Bits[2] = !trigger.octantsHADveto[tpg];

  Bits[3] = trigger.octantsMuon[tpg];

  return Bits.to_ulong();
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


// create only muon and octantA trigger correctly NOT the other ones
CastorTTPTest::MyCastorTrig
CastorTTPTest::GetTTPperTSshiftFromDigis(const int& ts, const int& ts_offset)
{
  CastorTTPTest::MyCastorTrig trigger;
  trigger.clear();

  unsigned int digi_adc_sector_module[kNCastorSectors][kNCastorModules];

  CastorDigiCollection::const_iterator const_iterator_digi;
  for(const_iterator_digi = digicoll->begin(); const_iterator_digi != digicoll->end(); const_iterator_digi++) {
    const CastorDataFrame& digi = *const_iterator_digi;

    int digi_sector = digi.id().sector() - 1;
    int digi_module = digi.id().module() - 1;

    digi_adc_sector_module[digi_sector][digi_module] = digi[ts].adc();
  }

  // the last two hadronic modules are not considered
  const unsigned int trigger_modules = kNCastorModules - 2;

  trigger.sample = ts;
  // reset all to true means all octants have NO veto
  // check later if veto is given
  for(unsigned int ioct=0; ioct<8; ioct++) trigger.octantsA[ioct] = true;

  for(unsigned int isec=0; isec<kNCastorSectors; isec++) {
    // for the muon trigger the modules 1-12 in every sector a seperated
    // into four segements 1-3,...,9-12 called tower
    // has nothing todo with castor tower
    unsigned int NChannelsAboveNoisePerTower[4] = {0,0,0,0};
    unsigned int NChannelsAboveNoise = 0;
    unsigned int NTowersAboveNoise = 0;

    for(unsigned int imod=0; imod<trigger_modules; imod++) {
      if( digi_adc_sector_module[isec][imod] >= kMuonThresholdTableAdc[isec%2][imod] ) {
        trigger.sector_muon_trigger[isec][imod] = true;
        NChannelsAboveNoisePerTower[imod/3]++;
        NChannelsAboveNoise++;
      }
    }

    for(unsigned int itow=0; itow<4; itow++)
      if( NChannelsAboveNoisePerTower[itow] > 0 ) NTowersAboveNoise++;

    if( NTowersAboveNoise > 2 )        trigger.octantsMuon[isec/2] = true;
    else if( NChannelsAboveNoise > 3 ) trigger.octantsA[isec/2]    = false;
  }

  return trigger;
}

bool
CastorTTPTest::IsCastorMuon(const CastorTTPTest::MyCastorTrig& trigger)
{
  int noct_muon = 0;
  int noct_tot  = 0;

  for( int ioct=0; ioct<8; ioct++) {
    if( trigger.octantsMuon[ioct] ) noct_muon++;
    if( trigger.octantsA[ioct] ) noct_tot++;
  }

  // if( noct_muon == 1 && noct_tot == 0 ) 
  if( noct_muon >= 1 && noct_tot >= 7 ) return true;

  return false;
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


  for (CItAlgo itAlgo = technicalTriggerMap.begin(); itAlgo != technicalTriggerMap.end(); itAlgo++) {
    std::string algName      = itAlgo->first;
    int algoBitNumber        = ( itAlgo->second ).algoBitNumber();
    bool decision            = m_l1GtUtils.decision(iEvent, itAlgo->first, iErrorCode);

    if( show_trigger_menu ) {
      L1TT_Menu[algoBitNumber] = algName;
    }
    if( decision && debugInfo ) //&& (algoBitNumber>=60 && algoBitNumber<=63) ) 
      std::cout << "**(L1)** " << evtnbr << " => TechnicalTrigger Bit " << algoBitNumber << " triggered" << std::endl;
  }

  for (CItAlgo itAlgo = algorithmMap.begin(); itAlgo != algorithmMap.end(); itAlgo++) {
    std::string algName      = itAlgo->first;
    int algoBitNumber        = ( itAlgo->second ).algoBitNumber();
    bool decision            = m_l1GtUtils.decision(iEvent, itAlgo->first, iErrorCode);


    if( show_trigger_menu ) {
      L1Algo_Menu[algoBitNumber] = algName;
    }
    if( decision && debugInfo && (algoBitNumber>=60 && algoBitNumber<=63) ) 
      std::cout << "**(L1)** " << evtnbr << " => AlgoTrigger Bit " << algoBitNumber << " triggered" << std::endl;
  }


  if( show_trigger_menu ) {
    std::cout << "*** L1 TechnicalTrigger Menu ***" << std::endl;
    for(std::map<int,std::string>::iterator it = L1TT_Menu.begin(); it != L1TT_Menu.end(); it++)
      std::cout << "   *** L1 TT Bit[" << it->first << "] = " << it->second << std::endl;
    std::cout << "*** L1 AlgoTrigger Menu ***" << std::endl;
    for(std::map<int,std::string>::iterator it = L1Algo_Menu.begin(); it != L1Algo_Menu.end(); it++)
      std::cout << "   *** L1 Algo Bit[" << it->first << "] = " << it->second << std::endl;

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
