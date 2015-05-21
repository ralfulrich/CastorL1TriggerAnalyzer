#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1.h"
#include "TH2.h"
#include "TTree.h"

#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/CastorRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/METReco/interface/HcalCaloFlagLabels.h"

#include "CalibFormats/CastorObjects/interface/CastorCoderDb.h"
#include "CalibFormats/CastorObjects/interface/CastorCalibrations.h"
#include "CalibFormats/CastorObjects/interface/CastorDbService.h"
#include "CalibFormats/CastorObjects/interface/CastorDbRecord.h"


struct CASTOR_RECORD {
  int event, bcn, ls, run, time, orbit;
  float recoRHe[14][16];
  float newRHe[14][16];
  int newRHs[14][16];
  float signal[14][16][10];
  int signalADC[14][16][10];
};

class SaturationCorrStudy : public edm::EDAnalyzer {
public:
  explicit SaturationCorrStudy(const edm::ParameterSet&);
  ~SaturationCorrStudy();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  edm::InputTag NewCastorRecHitColl_;
  edm::InputTag CastorDigiColl_;
  bool PrintInfo_;

  edm::Service<TFileService> fs;

  TH1* hNewRecHitSize;
  TH1* hSatur;
  TH2* hSatBitVsEnergy;

  TTree* tree;
  CASTOR_RECORD fTreeRecord;

  unsigned int cntSatEvents;
  unsigned int cntTotEvents;
  unsigned int cntShiftedTSEvents;

  CASTOR_RECORD minSatEnergyRecHit;
  CASTOR_RECORD maxNoSEnergyRecHit;

  int InvestMod_;
  int InvestSec_;

  unsigned int cntSatRecHits;
  unsigned int cntNoSRecHits;
};


SaturationCorrStudy::SaturationCorrStudy(const edm::ParameterSet& iConfig)
{
  NewCastorRecHitColl_ = iConfig.getParameter<edm::InputTag>("NewCastorRecHitColl");
  CastorDigiColl_   = iConfig.getParameter<edm::InputTag>("CastorDigiColl");
  PrintInfo_   = iConfig.getParameter<bool>("PrintInfo");
  InvestMod_   = iConfig.getParameter<int>("InvestMod");
  InvestSec_   = iConfig.getParameter<int>("InvestSec");

  //fs->file().SetCompressionLevel(1);

  hNewRecHitSize = fs->make<TH1F>("hNewRecHitSize","",300,0,300);
  hSatur = fs->make<TH1F>("hSatur","",10,0,10);
  hSatBitVsEnergy = fs->make<TH2F>("hSatBitVsEnergy","",100,0,100000,2,0,2);

  tree = fs->make<TTree>("CastorRecoSample","Entry per Event and Channel");
  tree->Branch("CastorRecord",&fTreeRecord,"event/I:bcn/I:ls/I:run/I:time/I:orbit/I:recoRHe[14][16]/F:newRHe[14][16]/F:newRHs[14][16]/I:signal[14][16][10]/F:signalADC[14][16][10]/I");

  cntSatEvents       = 0;
  cntTotEvents       = 0;
  cntShiftedTSEvents = 0;

  cntSatRecHits = 0;
  cntNoSRecHits = 0;
}

SaturationCorrStudy::~SaturationCorrStudy()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}
  
void
SaturationCorrStudy::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  //using namespace reco;

  //+++++++++++++++++++++++++ ADC<->fC converter  +++++++++++++++++++++++++++++++++++++++++//
  edm::ESHandle<CastorDbService> conditions;
  iSetup.get<CastorDbRecord>().get(conditions);
  const CastorQIEShape* shape = conditions->getCastorShape();

  time_t LStime = (time_t) iEvent.time().unixTime();
  fTreeRecord.event = iEvent.id().event();
  fTreeRecord.bcn   = iEvent.bunchCrossing();
  fTreeRecord.ls    = iEvent.luminosityBlock();
  fTreeRecord.run   = iEvent.id().run();
  fTreeRecord.time  = LStime;
  fTreeRecord.orbit = iEvent.orbitNumber();

  Handle<CastorDigiCollection> CastorDigis;
  iEvent.getByLabel(CastorDigiColl_,CastorDigis);

  // Handle<CastorRecHitCollection> NewRechits;
  // iEvent.getByLabel(NewCastorRecHitColl_, NewRechits);

  // if(!NewRechits.isValid()) return;

  //cout << "NewRechits->size(): " << NewRechits->size() << endl;
  // hNewRecHitSize->Fill(NewRechits->size());
  // if(NewRechits->size() != 224) return;

  map<int,CastorDataFrame> mDigi;

  //============================================================================
  //=========== Looking at Castor Digis ========================================
  //============================================================================
  bool shiftedTSEvent = false;
  for (size_t i = 0; i < CastorDigis->size(); i++)
    {
      const CastorDataFrame & digi = (*CastorDigis)[i];

      int ch = 16 * (digi.id().module()-1) + digi.id().sector()-1;
      mDigi[ch] = digi;

      //+++++++++++++++++++++++++ ADC<->fC converter  +++++++++++++++++++++++++++++++++++++++++//
      HcalCastorDetId cell = digi.id();
      // DetId detcell=(DetId)cell;	  
      const CastorCalibrations& calibrations=conditions->getCastorCalibrations(cell);
	  
      const CastorQIECoder* channelCoder = conditions->getCastorCoder(cell);
      CastorCoderDb coder(*channelCoder, *shape);

      CaloSamples tool;
      coder.adc2fC(digi,tool);

      const int & mod = digi.id().module();
      const int & sec = digi.id().sector();

      for (int j = 0; j<tool.size(); j++) {
        int capid=digi[j].capid();
        float ta = (tool[j]-calibrations.pedestal(capid)); // pedestal subtraction
        ta*=calibrations.gain(capid); // fC --> GeV

        fTreeRecord.signal[mod-1][sec-1][j] = ta;
        fTreeRecord.signalADC[mod-1][sec-1][j] = digi[j].adc();
      }
      
      if(digi[4].adc() < digi[5].adc() && digi[5].adc() > 80 && mod <= 5)
      	shiftedTSEvent = true;
    }


  //============================================================================
  //================== Looking for new reconstructed RecHits ===================
  //============================================================================
  // bool satEvent = false;
  // for (size_t i = 0; i < NewRechits->size(); i++)
  //   {
  //     const CastorRecHit & rh = (*NewRechits)[i];
  //     const int & mod = rh.id().module();
  //     const int & sec = rh.id().sector();

  //     //if(rh.getADC4() < rh.getADC5() && rh.getADC5() > 100) return;

  //     int sb = static_cast<int>(rh.flagField(HcalCaloFlagLabels::ADCSaturationBit));

  //     fTreeRecord.newRHe[mod-1][sec-1] = rh.energy();
  //     fTreeRecord.newRHs[mod-1][sec-1] = sb;


  //     if(sb!=0 && mod <= 5) satEvent = true;

      
  //     if(sb!=0 && PrintInfo_)
	 //     cout << "---> Mod: " << mod << "; Sec: " << sec << " is Saturated!!!"
	 //     << "\t=>E: " << rh.energy()
	 //     << "\t=>E TS4: "   << fTreeRecord.signal[mod-1][sec-1][4]    << "; TS5: " << fTreeRecord.signal[mod-1][sec-1][5]
	 //     << "\t=>ADC TS4: " << fTreeRecord.signalADC[mod-1][sec-1][4] << "; TS5: " << fTreeRecord.signalADC[mod-1][sec-1][5] << "; TS6: " << fTreeRecord.signalADC[mod-1][sec-1][6]  << endl;
      

  //     hSatur->Fill(sb);
  //   }
  
  for(int i=0; i<14; i++) for(int j=0; j<16; j++) {
    fTreeRecord.recoRHe[i][j]=0;
    fTreeRecord.newRHe[i][j]=0;
    fTreeRecord.newRHs[i][j]=0;
  }


  // const int & sb = fTreeRecord.newRHs[InvestMod_-1][InvestSec_-1];
  // const float & energy = fTreeRecord.newRHe[InvestMod_-1][InvestSec_-1];
  // hSatBitVsEnergy->Fill(energy,sb);
  // if(sb!=0)
  //   {
  //     if(minSatEnergyRecHit.newRHe[InvestMod_-1][InvestSec_-1] > energy)
  //       minSatEnergyRecHit = fTreeRecord;
  //     cntSatRecHits++;
  //   }
  // else
  //   {
  //     if(maxNoSEnergyRecHit.newRHe[InvestMod_-1][InvestSec_-1] < energy)
  //       maxNoSEnergyRecHit = fTreeRecord;
  //     cntNoSRecHits++;
  //   }

  tree->Fill();

  // if(satEvent) cntSatEvents++;
  if(shiftedTSEvent) cntShiftedTSEvents++;
  cntTotEvents++;
}

// ------------ method called once each job just before starting event loop  ------------
void
SaturationCorrStudy::beginJob()
{
  minSatEnergyRecHit.newRHe[InvestMod_-1][InvestSec_-1] = 1e10;
  maxNoSEnergyRecHit.newRHe[InvestMod_-1][InvestSec_-1] = 0;
}

// ------------ method called once each job just after ending the event loop  ------------
void
SaturationCorrStudy::endJob()
{
  using namespace std;

  cout << "============================================================" << endl;
  cout << "====================== First checks ========================" << endl;
  cout << "============================================================" << endl;
  cout << endl;
  cout << "============================================================" << endl;
  cout << "Events with Saturated RecHits :  " << cntSatEvents            << endl;
  cout << "Events with shifted TS RecHits : " << cntShiftedTSEvents      << endl;
  cout << "Total Number of Events :         " << cntTotEvents            << endl;
  cout << "============================================================" << endl;
  cout << endl;
  cout << "=======> highest non saturated Energy: " << maxNoSEnergyRecHit.newRHe[InvestMod_-1][InvestSec_-1] << endl;
  cout << "=======> lowest saturated Energy:      " << minSatEnergyRecHit.newRHe[InvestMod_-1][InvestSec_-1] << endl;
  cout << endl;
  cout << "=======> highest non saturated Energy in TS4: " << maxNoSEnergyRecHit.signal[InvestMod_-1][InvestSec_-1][4] << "; TS5: " << maxNoSEnergyRecHit.signal[InvestMod_-1][InvestSec_-1][5] << endl;
  cout << "=======> lowest saturated Energy in TS4: " << minSatEnergyRecHit.signal[InvestMod_-1][InvestSec_-1][4]  << "; TS5: " << minSatEnergyRecHit.signal[InvestMod_-1][InvestSec_-1][5] << endl;
  cout << endl;
  cout << "=======> highest non saturated ADC in TS4: " <<  maxNoSEnergyRecHit.signalADC[InvestMod_-1][InvestSec_-1][4] << "; TS5: " << maxNoSEnergyRecHit.signalADC[InvestMod_-1][InvestSec_-1][5] << endl;
  cout << "=======> lowest saturated ADC in TS4: " << minSatEnergyRecHit.signalADC[InvestMod_-1][InvestSec_-1][4] << "; TS5: " << minSatEnergyRecHit.signalADC[InvestMod_-1][InvestSec_-1][5] << endl;
  cout << endl;
  cout << "=======> Number of saturated RecHits:     " << cntSatRecHits << endl;
  cout << "=======> Number of non saturated RecHits: " << cntNoSRecHits << endl;
}

// ------------ method called when starting to processes a run  ------------
void
SaturationCorrStudy::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
SaturationCorrStudy::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
SaturationCorrStudy::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
SaturationCorrStudy::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SaturationCorrStudy::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SaturationCorrStudy);
