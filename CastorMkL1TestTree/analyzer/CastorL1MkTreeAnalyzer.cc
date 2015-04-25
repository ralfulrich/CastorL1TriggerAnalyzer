#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TString.h"
#include "TMath.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TParticle.h"
#include "TParticlePDG.h"
#include "TStopwatch.h"

#include "progressbar.h"

#include <boost/program_options.hpp>

using namespace std;

namespace po = boost::program_options;

typedef map<TString,TH1D*> mhist1D;
typedef map<TString,TH2D*> mhist2D;

// ======================================================================
// function & class definitions
struct JetEnergySort_JetOneBiggerJetTwo { 
  bool operator() (TLorentzVector* j1, TLorentzVector* j2) { return j1->E() > j2->E(); }
};
struct JetPTSort_JetOneBiggerJetTwo {
  bool operator() (TLorentzVector* j1, TLorentzVector* j2) { return j1->Pt() > j2->Pt(); }
};
class HelperClass {
private:
public:
  HelperClass() {}

  void GetLogBins(const int nbins, const double min, const double max, double* bins) const;
  void printRate(TH1D* h) const;
  // vectors need to be sorted -> first one must have highest pt
  bool IsDiJetEvent(vector< TLorentzVector* >& vcj, vector< TLorentzVector* >& vfj, const double& ptthr) const;
  double GetMaxSectorEnergy(Double_t energy[16][14], bool bUseChannelQualityMap = false) const;
  void ScaleHist(const unsigned int& allevt, const double& xs_process, TH1D* h) const;
  void ScaleHistStringSearch(mhist1D& hist, const TString& str_pattern, const unsigned int& allevt, const double& xs_process) const;
  void GetDiMuon(vector< TLorentzVector* >& vmupl, vector< TLorentzVector* >& vmumi, 
                 vector< TLorentzVector >& dimuon, const double single_mu_ptthr) const;
};
// ======================================================================

const double absEscaleFactor = 1.49475628341732545e+02/3.38945322418397409e+04 * 7.82961248095532028e+02/1.33096168279108213e+02;// * 1.45;

//using for Katerina's value's (some correction values seem too big (for me big is all >3), some are zeros)
const bool channelQuality[16][14] =                                                         // sector
    //mod 1   2     3     4     5      6    7     8     9    10     11    12   13    14
    {{true ,true ,true ,false,true ,true ,false,true ,true ,true ,true ,true ,true ,true }, // 1
     {true ,true ,true ,true ,true ,true ,false,true ,true ,true ,true ,true ,true ,true }, // 2
     {true ,true ,true ,true ,true ,true ,false,false,false,true ,false,true ,true ,true }, // 3 //s3m9 ? 
     {true ,true ,true ,true ,true ,true ,false,false,false,true ,false,true ,false,true }, // 4
     {true ,false,true ,true ,true ,true ,false,false,false,true ,true ,true ,true ,true }, // 5
     {true ,true ,true ,true ,true ,true ,false,false,false,true ,true ,true ,true ,true }, // 6 //s6m9 ?
     {true ,true ,true ,true ,true ,true ,false,true ,true ,false,false,false,false,false}, // 7 //s7m10-14katerina?
     {true ,true ,true ,true ,true ,true ,false,false,true ,false,false,false,false,false}, // 8 //s8m10-14katerina?
     {true ,true ,true ,true ,true ,true ,false,true ,true ,true ,true ,true ,false,true }, // 9 //s9m13?
     {true ,true ,true ,true ,true ,true ,false,true ,true ,true ,true ,true ,true ,true }, // 10
     {true ,true ,true ,true ,true ,true ,false,false,true ,true ,false,true ,true ,true }, // 11 //s11m11katerina?(was also there before)
     {true ,true ,true ,true ,true ,true ,false,false,true ,true ,false,true ,true ,true }, // 12 //s12m11katerina?(was also there before)
     {true ,true ,true ,true ,true ,false,false,false,true ,true ,false,true ,true ,true }, // 13 //s13m11katerina?(was also there before)
     {true ,true ,true ,true ,true ,true ,false,false,true ,true ,false,true ,true ,true }, // 14 //s14m11katerina?(was also there before)
     {true ,true ,true ,true ,true ,true ,false,false,true ,false,true ,true ,true ,true }, // 15
     {true ,true ,true ,true ,true ,false,false,true ,true ,true ,true ,true ,true ,true }};// 16

// Katerina's values using halo muon data (w/o TOTEM), already scaled by s9m4
const double channelGainQE[16][14] =                                                                                                                          // sector
  //mod 1          2          3          4           5          6          7         8          9          10         11          12        13           14
  {{  0.7510,    0.8700,    2.7370,    0.0000,    0.3630,    0.6430,    0.0000,    0.3100,    0.2120,    0.2740,    0.3030,    0.1690,    0.2650,    0.1550}, //1
   {  0.6190,    0.6160,    1.8130,    0.8690,    0.1820,    0.6280,    0.0000,    0.5070,    0.1680,    0.2910,    0.3380,    0.1460,    0.2490,    0.1250}, //2
   {  1.0700,    0.6510,    1.4250,    0.7660,    0.3040,    0.1930,    8.2170,   13.2900,    0.4650,    0.2350,    0.0000,    0.2950,    0.3430,    0.3510}, //3
   {  0.5310,    0.3300,    0.8910,    0.8260,    0.1170,    0.3300,    0.0000,    0.0000,    0.0000,    0.6390,    0.0000,    0.3170,    0.0000,    0.4580}, //4
   {  0.6120,    0.0000,    1.3410,    0.7020,    0.1560,    0.5690,    0.8360,    0.0000,    0.0000,    0.5230,    0.2360,    0.3290,    0.3990,    0.3420}, //5
   {  1.3130,    0.4870,    1.4000,    0.6320,    0.1990,    0.7950,    1.2090,    0.0000,    0.5100,    0.7060,    0.2330,    0.2800,    0.4830,    0.4410}, //6
   {  0.4160,    0.2820,    1.0430,    0.3130,    0.1140,    0.0860,  250.6690,    0.1950,    0.4200,    6.9160,    3.4790,    1.5110,    4.8590,    3.5340}, //7
   {  0.3420,    0.2950,    1.1980,    1.4030,    0.2130,    1.0730,    0.0000,    0.2060,    0.6350,   27.2690,    9.4210,    3.3400,    3.4880,    1.0100}, //8
   {  0.3030,    0.8460,    1.4120,    1.0000,    0.2180,    0.8830,    0.0000,    0.1320,    0.1950,    0.2490,    0.2250,    0.2270,    0.2990,    0.2780}, //9
   {  0.9040,    1.4030,    2.6580,    1.1900,    0.2350,    1.5570,    0.0000,    0.3160,    0.1990,    0.3100,    0.1790,    0.2510,    0.2510,    0.2520}, //10
   {  1.0160,    0.9930,    1.6950,    0.8870,    0.2850,    0.6230,    0.0000,   10.0790,    0.3730,    0.2440,    9.6350,    0.5240,    0.6990,    0.3790}, //11
   {  1.1690,    1.1300,    2.1400,    1.3920,    0.2630,    1.2470,    0.0000,    0.0000,    0.5670,    0.3030,   99.3510,    0.3510,    0.1980,    0.3560}, //12
   {  0.9160,    1.2700,    1.6430,    0.8070,    0.2310,    2.3020,    0.0000,    0.0000,    0.3230,    0.2910,    0.0000,    0.3430,    0.1280,    0.3080}, //13
   {  0.6010,    0.9840,    2.1400,    0.8210,    0.1770,    1.0970,    0.0000,    0.0000,    0.2030,    0.2920,   16.6350,    0.3020,    0.3510,    0.3680}, //14
   {  0.7590,    1.3650,    2.9620,    1.1740,    0.3800,    2.3370,    0.0000,  517.2540,    0.2690,    0.0000,    0.1940,    0.2740,    0.2800,    0.4100}, //15
   {  0.7420,    0.9720,    2.4600,    0.9240,    0.2200,    0.1630,    3.9070,    0.1970,    0.2700,    0.2580,    0.1510,    0.1340,    0.2790,    0.2620}};//16

// crossection and paths for different samples
const double cs[7] = {  // crossection in mb
  7.528,          // pthat = 10 -> 15
  2.237,          // pthat = 15 -> 30
  0.1615,         // pthat = 30 -> 50
  0.02211,        // pthat = 50 -> 80
  78.8,           // minbias
  1.,
  1.
};
const TString infiles[7] = {
  "",
  "../Output_Reco_MkTree_Advanced/Output_Reco_MkTree_QCD_15_30/*.root",
  "",
  "",
  "../Output_Reco_MkTree_Advanced/Output_Reco_MkTree_MinBias/*.root",
  "../Output_Reco_MkTree_Advanced/Output_Reco_MkTree_MB_ak4Jets/*.root",
  "../Output_Reco_MkTree_Advanced/Output_Reco_MkTree_SpecialTest/*.root"
};
const TString outfiles[7] = {
  "HLT_Reco_And_MkTree_QCD_pt10to15.root",
  "HLT_Reco_And_MkTree_QCD_pt15to30.root",
  "HLT_Reco_And_MkTree_QCD_pt30to50.root",
  "HLT_Reco_And_MkTree_QCD_pt50to80.root",
  "HLT_Reco_And_MkTree_MinBias.root",
  "HLT_Reco_And_MkTree_MB_ak4Jets.root",
  "HLT_Reco_And_MkTree_SpecialTest"
};


int main(int argc, char *argv[])
{

  TStopwatch myTimer; myTimer.Start();
  const HelperClass helper;

  //===============================
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // define options
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("selection,s", po::value<int>(), "0-3 for QCD 10,15,30,50; 4 for MinBias; 5 for MinBias with ak4 GenJets; 6 for Special Test Files")
    ("num,N", po::value<int>(), "number of events; not given argument means all events")
  ;
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // readout options
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // define action by option
  if (vm.count("help")) {
    cout << desc << "\n";
    return 1;
  }

  if (!vm.count("selection")) {
    cout << "No sample selected!" << endl;
    return -1;
  }
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //===============================

  cout << "CpuTime after parsinge command line options: " << myTimer.CpuTime() << endl;
  myTimer.Start();

  //=========================
  //!!!!!!!!!!!!!!!!!!!!!!!!!
  const int selection = vm["selection"].as<int>();
  if( selection > 6 ) {
    cout << "Selected sample " << selection << " is out of range [0-6]!" << endl;
    return -1;
  }
  //!!!!!!!!!!!!!!!!!!!!!!!!!
  //=========================

  // Declaration of leaf types
  Int_t           num_pu_vtx;
  TClonesArray    *fspart;
  TClonesArray    *genjet;
  TClonesArray    *casjet;
  TClonesArray    *vertex;
  Int_t           fspart_size;
  Int_t           genjet_size;
  Int_t           casjet_size;
  Int_t           vertex_size;
  Double_t        cas_energy[16][14];
  Int_t           fspart_id[5000];   //[fspart_size]
  Int_t           vtx_ndof[50];   //[vertex_size]
  Int_t           vtx_fake[50];   //[vertex_size]
  Int_t           totem_mpl[2];
  ULong64_t       CastorL1DecisionWord;
  ULong64_t       AlgoJetDecisionWord1;
  ULong64_t       AlgoJetDecisionWord2;
  ULong64_t       HLTDecisionWord;

  // List of branches
  TBranch        *b_num_pu_vtx;   //!
  TBranch        *b_fspart;   //!
  TBranch        *b_genjet;   //!
  TBranch        *b_casjet;   //!
  TBranch        *b_vertex;   //!
  TBranch        *b_fspart_size;   //!
  TBranch        *b_genjet_size;   //!
  TBranch        *b_casjet_size;   //!
  TBranch        *b_vertex_size;   //!
  TBranch        *b_cas_energy;   //!
  TBranch        *b_fspart_id;   //!
  TBranch        *b_vtx_ndof;   //!
  TBranch        *b_vtx_fake;   //!
  TBranch        *b_totem_mpl;   //!
  TBranch        *b_CastorL1DecisionWord;   //!
  TBranch        *b_AlgoJetDecisionWord1;   //!
  TBranch        *b_AlgoJetDecisionWord2;   //!
  TBranch        *b_HLTDecisionWord;   //!

  TChain * chain = new TChain("castorl1test/myTree");

  chain->Add(infiles[selection]);

  // ====================================
  // other constants
  // double lumi_inst = (1./25e-9) * (1./3564) *  1./80;
  // =====================================

  // Set object pointer
  fspart = 0;
  genjet = 0;
  casjet = 0;
  vertex = 0;

  chain->SetBranchAddress("num_pu_vtx", &num_pu_vtx, &b_num_pu_vtx);
  chain->SetBranchAddress("fspart", &fspart, &b_fspart);
  chain->SetBranchAddress("genjet", &genjet, &b_genjet);
  chain->SetBranchAddress("casjet", &casjet, &b_casjet);
  chain->SetBranchAddress("vertex", &vertex, &b_vertex);
  chain->SetBranchAddress("fspart_size", &fspart_size, &b_fspart_size);
  chain->SetBranchAddress("genjet_size", &genjet_size, &b_genjet_size);
  chain->SetBranchAddress("casjet_size", &casjet_size, &b_casjet_size);
  chain->SetBranchAddress("vertex_size", &vertex_size, &b_vertex_size);
  chain->SetBranchAddress("cas_energy", cas_energy, &b_cas_energy);
  chain->SetBranchAddress("fspart_id", fspart_id, &b_fspart_id);
  chain->SetBranchAddress("vtx_ndof", vtx_ndof, &b_vtx_ndof);
  chain->SetBranchAddress("vtx_fake", vtx_fake, &b_vtx_fake);
  chain->SetBranchAddress("totem_mpl", totem_mpl, &b_totem_mpl);
  chain->SetBranchAddress("CastorL1DecisionWord", &CastorL1DecisionWord, &b_CastorL1DecisionWord);
  chain->SetBranchAddress("AlgoJetDecisionWord1", &AlgoJetDecisionWord1, &b_AlgoJetDecisionWord1);
  chain->SetBranchAddress("AlgoJetDecisionWord2", &AlgoJetDecisionWord2, &b_AlgoJetDecisionWord2);
  chain->SetBranchAddress("HLTDecisionWord", &HLTDecisionWord, &b_HLTDecisionWord);

  cout << "CpuTime after setting up chain: " << myTimer.CpuTime() << endl;
  myTimer.Start();

  ///////////////////////////
  // set number of events !!!
  int nEntries = chain->GetEntries();
  if (vm.count("num")) nEntries = vm["num"].as<int>();
  ///////////////////////////

  cout << "CpuTime after reading Entries: " << myTimer.CpuTime() << endl;
  myTimer.Start();

  cout << "Entries in Chain: " << nEntries << endl;

  TFile* file = TFile::Open(outfiles[selection],"RECREATE");

  mhist1D h1;
  mhist2D h2;

  h1["TrigStat"] = new TH1D("TrigStat","TrigStat",20,0,20);
  // h1["hstat"] = new TH1D("hstat","hstat",20,0,20);

  h2["EnergyThreshold_Saturation"] = new TH2D("EnergyThreshold_Saturation","EnergyThreshold Saturation;module;sector",14,0,14,16,0,16);

  // int nbins = 100;
  // double xmin = 0, xmax = 5000;
  int jetptbins = 25;
  double jetptmin = 0, jetptmax = 50;

  h1["CasGenJetPt"]        = new TH1D("CasGenJetPt","CasGenJetPt",jetptbins,jetptmin,jetptmax);
  h1["CasGenJetPt_TTLjet"] = new TH1D("CasGenJetPt_TTLjet","CasGenJetPt_TTLjet",jetptbins,jetptmin,jetptmax);
  h1["CasGenJetPt_TTmuon"] = new TH1D("CasGenJetPt_TTmuon","CasGenJetPt_TTmuon",jetptbins,jetptmin,jetptmax);
  h1["CasGenJetPt_TTgap"]  = new TH1D("CasGenJetPt_TTgap","CasGenJetPt_TTgap",jetptbins,jetptmin,jetptmax);

  // double pi = TMath::Pi();

  int thbins = 100;
  double thmin = 0, thmax = 3000;

  h1["HotCasSecEnergy"] = new TH1D("HotCasSecEnergy","HotCasSecEnergy",thbins,thmin,thmax);
  h1["HotCasSecEnergy_NTTLjet"] = new TH1D("HotCasSecEnergy_NTTLjet","HotCasSecEnergy_NTTLjet",thbins,thmin,thmax);

  h1["NTTjet_Thr"]         = new TH1D("NTTjet_Thr","NTTjet_Thr",thbins,thmin,thmax);
  h1["NTTjet_Thr_DiJet5"]  = new TH1D("NTTjet_Thr_DiJet5","NTTjet_Thr_DiJet5",thbins,thmin,thmax);
  h1["NTTjet_Thr_DiJet10"] = new TH1D("NTTjet_Thr_DiJet10","NTTjet_Thr_DiJet10",thbins,thmin,thmax);
  h1["NTTjet_Thr_DiJet20"] = new TH1D("NTTjet_Thr_DiJet20","NTTjet_Thr_DiJet20",thbins,thmin,thmax);
  h1["NTTjet_Thr_ATjet16"]          = new TH1D("NTTjet_Thr_ATjet16","NTTjet_Thr_ATjet16",thbins,thmin,thmax);
  h1["NTTjet_Thr_ATjet16_DiJet5"]   = new TH1D("NTTjet_Thr_ATjet16_DiJet5","NTTjet_Thr_ATjet16_DiJet5",thbins,thmin,thmax);
  h1["NTTjet_Thr_ATjet16_DiJet10"]  = new TH1D("NTTjet_Thr_ATjet16_DiJet10","NTTjet_Thr_ATjet16_DiJet10",thbins,thmin,thmax);
  h1["NTTjet_Thr_ATjet16_DiJet20"]  = new TH1D("NTTjet_Thr_ATjet16_DiJet20","NTTjet_Thr_ATjet16_DiJet20",thbins,thmin,thmax);
  h1["NTTjet_Thr_HLTjet20"]         = new TH1D("NTTjet_Thr_HLTjet20","NTTjet_Thr_HLTjet20",thbins,thmin,thmax);
  h1["NTTjet_Thr_HLTjet20_DiJet5"]  = new TH1D("NTTjet_Thr_HLTjet20_DiJet5","NTTjet_Thr_HLTjet20_DiJet5",thbins,thmin,thmax);
  h1["NTTjet_Thr_HLTjet20_DiJet10"] = new TH1D("NTTjet_Thr_HLTjet20_DiJet10","NTTjet_Thr_HLTjet20_DiJet10",thbins,thmin,thmax);
  h1["NTTjet_Thr_HLTjet20_DiJet20"] = new TH1D("NTTjet_Thr_HLTjet20_DiJet20","NTTjet_Thr_HLTjet20_DiJet20",thbins,thmin,thmax);

  h1["NTTjet_Thr_CasJet5"]  = new TH1D("NTTjet_Thr_CasJet5","NTTjet_Thr_CasJet5",thbins,thmin,thmax);
  h1["NTTjet_Thr_CasJet10"] = new TH1D("NTTjet_Thr_CasJet10","NTTjet_Thr_CasJet10",thbins,thmin,thmax);
  h1["NTTjet_Thr_CasJet20"] = new TH1D("NTTjet_Thr_CasJet20","NTTjet_Thr_CasJet20",thbins,thmin,thmax);

  int nimbins = 100;
  double immin = 0.5;
  double immax = 200;
  double imbins[nimbins+1];
  helper.GetLogBins(nimbins,immin,immax,imbins);

  int ptbins = 50;
  double ptmin = 0;
  double ptmax = 5;

  h1["MuMu_mass"]           = new TH1D("MuMu_mass","MuMu_mass",nimbins,imbins);
  h1["MuMu_pt"]             = new TH1D("MuMu_pt","MuMu_pt",ptbins,ptmin,ptmax);
  h1["MuMu_ATmu3_mass"]     = new TH1D("MuMu_ATmu3_mass","MuMu_ATmu3_mass",nimbins,imbins);
  h1["MuMu_ATmu3_pt"]       = new TH1D("MuMu_ATmu3_pt","MuMu_ATmu3_pt",ptbins,ptmin,ptmax);
  h1["MuMu_ATmu3_Gap_mass"] = new TH1D("MuMu_ATmu3_Gap_mass","MuMu_ATmu3_Gap_mass",nimbins,imbins);
  h1["MuMu_ATmu3_Gap_pt"]   = new TH1D("MuMu_ATmu3_Gap_pt","MuMu_ATmu3_Gap_pt",ptbins,ptmin,ptmax);
  h1["MuMu_TTjet_mass"]     = new TH1D("MuMu_TTjet_mass","MuMu_TTjet_mass",nimbins,imbins);
  h1["MuMu_TTjet_pt"]       = new TH1D("MuMu_TTjet_pt","MuMu_TTjet_pt",ptbins,ptmin,ptmax);

  h1["MuMu_CasJet_dpt"] = new TH1D("MuMu_CasJet_dpt","MuMu_CasJet_dpt",20,-2,2);

  // loop over all hists in container and set "Sumw2"
  for(mhist1D::iterator it=h1.begin(); it!=h1.end(); it++) it->second->Sumw2();
  for(mhist2D::iterator it=h2.begin(); it!=h2.end(); it++) it->second->Sumw2();


  // double satch[16][14];
  for(int isec=0; isec<16; isec++)
    for(int imod=0; imod<14; imod++) {
      // satch[isec][imod] = 28000*channelGainQE[isec][imod]*absEscaleFactor;
      h2["EnergyThreshold_Saturation"]->Fill(imod+0.5,isec+0.5,28000*channelGainQE[isec][imod]*absEscaleFactor);
    }

  cout << "CpuTime after setting up histogramms: " << myTimer.CpuTime() << endl;
  myTimer.Start();


  progressbar pb("Progress",nEntries);
  for(int iEvent=0; iEvent<nEntries; iEvent++)
  {   
    chain->GetEntry(iEvent);
    pb.printBar(iEvent);
      
    h1["TrigStat"]->Fill("all",1);

    std::bitset<64> CastorL1Bits(CastorL1DecisionWord);
    std::bitset<64> AlgoJetBits1(AlgoJetDecisionWord1);
    std::bitset<64> AlgoJetBits2(AlgoJetDecisionWord2);
    std::bitset<64> HLTBits(HLTDecisionWord);
      
    bool TTgap  = CastorL1Bits[60];
    bool TTjet  = CastorL1Bits[61];
    bool TTLjet = CastorL1Bits[62];
    bool TTmuon = CastorL1Bits[63];

    bool ATjet16 = AlgoJetBits1[15];
    bool ATjet36 = AlgoJetBits1[16];
    bool ATmu3   = AlgoJetBits1[57];
    bool ATmu7   = AlgoJetBits1[59];
    bool ATmuOp  = AlgoJetBits1[55];

    bool ATdimu  = AlgoJetBits2[92-64];

    bool HLTjet   = HLTBits[0];
    bool HLTdijet = HLTBits[1];
    bool HLTjetmu = HLTBits[3];
    bool HLTgapmu = HLTBits[6];

    if( TTgap )    h1["TrigStat"]->Fill("TTgap",1);
    if( TTjet )    h1["TrigStat"]->Fill("TTjet",1);
    if( TTLjet )   h1["TrigStat"]->Fill("TTLjet",1);
    if( TTmuon )   h1["TrigStat"]->Fill("TTmuon",1);
    if( ATjet16 )  h1["TrigStat"]->Fill("ATjet16",1);
    if( ATjet36 )  h1["TrigStat"]->Fill("ATjet36",1);
    if( ATmu3 )    h1["TrigStat"]->Fill("ATmu3",1);
    if( ATmu7 )    h1["TrigStat"]->Fill("ATmu7",1);
    if( ATmuOp )   h1["TrigStat"]->Fill("ATmuOp",1);
    if( HLTjet )   h1["TrigStat"]->Fill("HLTjet",1);
    if( HLTdijet ) h1["TrigStat"]->Fill("HLTdijet",1);
    if( HLTjetmu ) h1["TrigStat"]->Fill("HLTjetmu",1);
    if( HLTgapmu ) h1["TrigStat"]->Fill("HLTgapmu",1);

    if( ATdimu )   h1["TrigStat"]->Fill("ATdimu",1);

    if( TTLjet && ATjet16 ) h1["TrigStat"]->Fill("TTjet_AND_ATjet16",1);
    if( TTLjet && ATjet36 ) h1["TrigStat"]->Fill("TTjet_AND_ATjet36",1);
    if( TTLjet && ATmu3 )   h1["TrigStat"]->Fill("TTjet_AND_ATmu3",1);
    if( TTLjet && ATmu7 )   h1["TrigStat"]->Fill("TTjet_AND_ATmu7",1);
    if( TTgap && ATmu3 )    h1["TrigStat"]->Fill("TTgap_AND_ATmu3",1);
    if( TTgap && ATmu7 )    h1["TrigStat"]->Fill("TTgap_AND_ATmu7",1);


    // Need to copy pointers into vector for sorting
    vector< TLorentzVector* > vfj;
    vector< TLorentzVector* > vcj;
    vector< TLorentzVector* > jrest;
    for(int ijet=0; ijet<genjet_size; ijet++) 
    {
      TLorentzVector* jet = (TLorentzVector*)(*genjet)[ijet];
         
      if( jet->Pt() < 1e-3 ) continue;
         
      if( jet->Eta() > -5 && jet->Eta() < 5 ) {
        vcj.push_back( jet );
      } else if( jet->Eta() > -6.4 && jet->Eta() < -5.4 ) {
        vfj.push_back( jet );
      } else {
        jrest.push_back( jet );
      }
    }

    vector< TLorentzVector* > vCasJet;
    for(int ijet=0; ijet<casjet_size; ijet++)
    {
      TLorentzVector* jet = (TLorentzVector*)(*casjet)[ijet];

      vCasJet.push_back( jet );
    }

    sort(vcj.begin(),vcj.end(),JetPTSort_JetOneBiggerJetTwo());
    sort(vfj.begin(),vfj.end(),JetPTSort_JetOneBiggerJetTwo());
    sort(jrest.begin(),jrest.end(),JetPTSort_JetOneBiggerJetTwo());
    sort(vCasJet.begin(),vCasJet.end(),JetEnergySort_JetOneBiggerJetTwo());

    // For HLT trigger estimations
    bool ATjet12 = vcj.empty() ? false : (vcj[0]->Pt() > 12 ? true : false);
    // HLT without Castor Trigger needs to be add by hand
    bool HLTdijet15 = !ATjet12 ? false : (vcj[0]->Pt() > 15 ? true : false);
    bool HLTdijet20 = ATjet16 && !vcj.empty() ? (vcj[0]->Pt() > 20 ? true : false) : false;
    
    if( ATjet12 )              h1["TrigStat"]->Fill("ATjet12",1);
    if( TTLjet && ATjet12 )    h1["TrigStat"]->Fill("TTjet_AND_ATjet12",1);
    if( TTLjet && HLTdijet15 ) h1["TrigStat"]->Fill("HLTdijet15",1);
    if( TTLjet && HLTdijet20 ) h1["TrigStat"]->Fill("HLTdijet20",1);

    bool dijet5  = helper.IsDiJetEvent(vcj,vfj,5);
    bool dijet10 = helper.IsDiJetEvent(vcj,vfj,10);
    bool dijet20 = helper.IsDiJetEvent(vcj,vfj,20);

    if(!vfj.empty()) {
      h1["CasGenJetPt"]->Fill( vfj[0]->Pt() );
      if( TTLjet ) h1["CasGenJetPt_TTLjet"]->Fill( vfj[0]->Pt() );
      if( TTmuon ) h1["CasGenJetPt_TTmuon"]->Fill( vfj[0]->Pt() );
      if( TTgap )  h1["CasGenJetPt_TTgap"]->Fill( vfj[0]->Pt() );
    }

    double hot_sec_energy = helper.GetMaxSectorEnergy(cas_energy);
    h1["HotCasSecEnergy"]->Fill( hot_sec_energy );
    if( TTLjet ) h1["HotCasSecEnergy_NTTLjet"]->Fill( hot_sec_energy );

    int maxbin = h1["NTTjet_Thr"]->FindBin( hot_sec_energy );
    for(int ibin=1; ibin<=maxbin; ibin++) {
      double binctr = h1["NTTjet_Thr"]->GetBinCenter(ibin);
      h1["NTTjet_Thr"]->Fill(binctr);
      if(dijet5)  h1["NTTjet_Thr_DiJet5"]->Fill(binctr);
      if(dijet10) h1["NTTjet_Thr_DiJet10"]->Fill(binctr);
      if(dijet20) h1["NTTjet_Thr_DiJet20"]->Fill(binctr);
      if(!vfj.empty()) {
        if(vfj[0]->Pt() > 5)  h1["NTTjet_Thr_CasJet5"]->Fill(binctr);
        if(vfj[0]->Pt() > 10) h1["NTTjet_Thr_CasJet10"]->Fill(binctr);
        if(vfj[0]->Pt() > 20) h1["NTTjet_Thr_CasJet20"]->Fill(binctr);
      }
    }
    if(ATjet12) for(int ibin=1; ibin<=maxbin; ibin++) {
      double binctr = h1["NTTjet_Thr_ATjet16"]->GetBinCenter(ibin);
      h1["NTTjet_Thr_ATjet16"]->Fill(binctr);
      if(dijet5)  h1["NTTjet_Thr_ATjet16_DiJet5"]->Fill(binctr);
      if(dijet10) h1["NTTjet_Thr_ATjet16_DiJet10"]->Fill(binctr);
      if(dijet20) h1["NTTjet_Thr_ATjet16_DiJet20"]->Fill(binctr);
    }
    if(HLTdijet15) for(int ibin=1; ibin<=maxbin; ibin++) {
      double binctr = h1["NTTjet_Thr_HLTjet20"]->GetBinCenter(ibin);
      h1["NTTjet_Thr_HLTjet20"]->Fill(binctr);
      if(dijet5)  h1["NTTjet_Thr_HLTjet20_DiJet5"]->Fill(binctr);
      if(dijet10) h1["NTTjet_Thr_HLTjet20_DiJet10"]->Fill(binctr);
      if(dijet20) h1["NTTjet_Thr_HLTjet20_DiJet20"]->Fill(binctr);
    }

    vector< TLorentzVector* > vmupl;
    vector< TLorentzVector* > vmumi;
    for(int ipart=0; ipart<fspart_size; ipart++) 
    {
      TLorentzVector* part = (TLorentzVector*)(*fspart)[ipart];
         
      if( part->Pt() < 1e-3 ) continue;
         
      if( part->Eta() > 2.5 || part->Eta() < -2.5 ) continue;

      if( fspart_id[ipart] == 13 ) vmupl.push_back(part);
      else if( fspart_id[ipart] == -13 ) vmumi.push_back(part);
    }

    double single_mu_ptthr = 1.0;
    vector<TLorentzVector> dimuon;
    helper.GetDiMuon(vmupl, vmumi, dimuon, single_mu_ptthr);

    for(unsigned int i=0; i<dimuon.size(); i++) {
      const TLorentzVector & lvdimu = dimuon[i];

      h1["MuMu_mass"]->Fill( lvdimu.M() );
      h1["MuMu_pt"]->Fill( lvdimu.Pt() );

      if( ATmu3 ) {
        h1["MuMu_ATmu3_mass"]->Fill( lvdimu.M() );
        h1["MuMu_ATmu3_pt"]->Fill( lvdimu.Pt() );
        if( TTgap ) {
          h1["MuMu_ATmu3_Gap_mass"]->Fill( lvdimu.M() );
          h1["MuMu_ATmu3_Gap_pt"]->Fill( lvdimu.Pt() );
        }
      }

      if( TTjet ) {
        h1["MuMu_TTjet_mass"]->Fill( lvdimu.M() );
        h1["MuMu_TTjet_pt"]->Fill( lvdimu.Pt() );
      }
    }


    if( vfj.empty() || dimuon.size() != 1 ) continue;

    TLorentzVector* fj = vfj[0];
    TLorentzVector* cj = &dimuon[0];

    double dphi = fj->DeltaPhi(*cj);
    if( TMath::Abs(dphi) < 2.7 ) continue;

    double avpt = (cj->Pt()+fj->Pt())/2.;
    // double pcut = 0.2 * avpt;

    // if( vcj.size() > 0 ) if( vcj[0]->Pt() > pcut ) continue;
    // if( vfj.size() > 1 ) if( vfj[1]->Pt() > pcut ) continue;

    h1["MuMu_CasJet_dpt"]->Fill( (cj->Pt()-fj->Pt()) / avpt );
  }
  cout << endl;

  cout << "CpuTime after looping over all events: " << myTimer.CpuTime() << endl;
  cout << "CpuTime used per event: " << myTimer.CpuTime()/double(nEntries) << endl;
  myTimer.Start();

  // // this scales hist just to crossection in mb
  // lumi_inst = 1.;

  helper.ScaleHistStringSearch(h1,"NTTjet_Thr",nEntries,cs[selection]);

  file->Write();
  file->Close();

  cout << "CpuTime after writing and closing ROOT file: " << myTimer.CpuTime() << endl;

  return 0;
}

// vectors need to be sorted -> first one must have highest pt
bool HelperClass::IsDiJetEvent(vector< TLorentzVector* >& vcj, vector< TLorentzVector* >& vfj, const double& ptthr) const {
    if( vfj.empty() ) return false;
    if( vcj.empty() ) return false;

    TLorentzVector* cj = vcj[0];
    TLorentzVector* fj = vfj[0];

    if( cj->Pt() < ptthr || fj->Pt() < ptthr ) return false;

    double dphi = fj->DeltaPhi(*cj);
    if( TMath::Abs(dphi) < 2.7 ) return false;

    double pcut = 0.2 * (cj->Pt()+fj->Pt())/2.;

    if( vcj.size() > 1 ) if( vcj[1]->Pt() > pcut ) return false;
    if( vfj.size() > 1 ) if( vfj[1]->Pt() > pcut ) return false;

    return true;
}

void HelperClass::GetDiMuon(vector< TLorentzVector* >& vmupl, vector< TLorentzVector* >& vmumi,
                            vector< TLorentzVector >& dimuon, const double single_mu_ptthr) const
{
  dimuon.clear();

  if( vmupl.empty() ) return;
  if( vmumi.empty() ) return;

  for(unsigned int i=0; i<vmupl.size(); i++) {
    if( vmupl[i]->Pt() < single_mu_ptthr ) continue;
    for(unsigned int j=0; j<vmumi.size(); j++) {
      if( vmumi[j]->Pt() < single_mu_ptthr ) continue;

      TLorentzVector lv_dimuon( vmupl[i]->X() + vmumi[j]->X(),
                                vmupl[i]->Y() + vmumi[j]->Y(),
                                vmupl[i]->Z() + vmumi[j]->Z(),
                                vmupl[i]->E() + vmumi[j]->E() );

      dimuon.push_back(lv_dimuon);
    }
  }
}

double HelperClass::GetMaxSectorEnergy(Double_t energy[16][14], bool bUseChannelQualityMap) const {
  // loop over rechits
  double hot_sec_energy = 0;
  for(int isec=0; isec<16; isec++) 
  {
    double sec_energy = 0;
          
    for(int imod=0; imod<12; imod++)
    {
      if( !bUseChannelQualityMap || channelQuality[isec][imod] ) {
        sec_energy += energy[isec][imod];
      }
    }

    if( sec_energy > hot_sec_energy ) {
      hot_sec_energy = sec_energy;
    }
  }

  return hot_sec_energy;
}

void HelperClass::ScaleHist(const unsigned int& allevt, const double& xs_process, TH1D* h) const {
  h->Scale(xs_process/allevt);
}

void HelperClass::ScaleHistStringSearch(mhist1D& hist, const TString& str_pattern, const unsigned int& allevt, const double& xs_process) const {
  for(mhist1D::iterator it=hist.begin(); it!=hist.end(); it++) {
    if( it->first.Contains( str_pattern ) )
      ScaleHist(allevt,xs_process,it->second);
  }
}

void HelperClass::GetLogBins(const int nbins, const double min, const double max, double* bins) const {
  bins[0] = min; bins[nbins] = max;

  double logmin = log(min);
  double logmax = log(max);

  for(int i=1; i<nbins; i++) {
    double logi = (logmax-logmin)/nbins * i + logmin;
    bins[i] = exp(logi);
  }
}

void HelperClass::printRate(TH1D* h) const {
  int TTjet_bin  = h->GetXaxis()->FindBin("TTjet");
  int TTgap_bin  = h->GetXaxis()->FindBin("TTgap");
  int TTLjet_bin = h->GetXaxis()->FindBin("TTLjet");
  int TTmuon_bin = h->GetXaxis()->FindBin("TTmuon");

  int ATjet16_bin  = h->GetXaxis()->FindBin("ATjet16");
  int ATjet36_bin  = h->GetXaxis()->FindBin("ATjet36");
  int ATmu3_bin    = h->GetXaxis()->FindBin("ATmu3");
  int ATmu7_bin    = h->GetXaxis()->FindBin("ATmu7");
  int HLTjet_bin   = h->GetXaxis()->FindBin("HLTjet");
  int HLTdijet_bin = h->GetXaxis()->FindBin("HLTdijet");
  int HLTjetmu_bin = h->GetXaxis()->FindBin("HLTjetmu");
  int HLTgapmu_bin = h->GetXaxis()->FindBin("HLTgapmu");

  int TTjet_ATjet16_bin = h->GetXaxis()->FindBin("TTjet_AND_ATjet16");
  int TTjet_ATjet36_bin = h->GetXaxis()->FindBin("TTjet_AND_ATjet36");
  int TTjet_ATmu3_bin   = h->GetXaxis()->FindBin("TTjet_AND_ATmu3");
  int TTjet_ATmu7_bin   = h->GetXaxis()->FindBin("TTjet_AND_ATmu7");
  int TTgap_ATmu3_bin   = h->GetXaxis()->FindBin("TTgap_AND_ATmu3");
  int TTgap_ATmu7_bin   = h->GetXaxis()->FindBin("TTgap_AND_ATmu7");

  cout << "======== RATE [Hz] ========" << endl;
  cout << "  TTjet         : " << h->GetBinContent(TTjet_bin) << endl;
  cout << "  TTgap         : " << h->GetBinContent(TTgap_bin) << endl;
  cout << "  TTLjet        : " << h->GetBinContent(TTLjet_bin) << endl;
  cout << "  TTmuon        : " << h->GetBinContent(TTmuon_bin) << endl;
  cout << "---------------------------" << endl;
  cout << "  ATjet16       : " << h->GetBinContent(ATjet16_bin) << endl;
  cout << "  ATjet36       : " << h->GetBinContent(ATjet36_bin) << endl;
  cout << "  ATmu3         : " << h->GetBinContent(ATmu3_bin) << endl;
  cout << "  ATmu7         : " << h->GetBinContent(ATmu7_bin) << endl;
  cout << "---------------------------" << endl;
  cout << "  HLTjet        : " << h->GetBinContent(HLTjet_bin) << endl;
  cout << "  HLTdijet      : " << h->GetBinContent(HLTdijet_bin) << endl;
  cout << "  HLTjetmu      : " << h->GetBinContent(HLTjetmu_bin) << endl;
  cout << "  HLTgapmu      : " << h->GetBinContent(HLTgapmu_bin) << endl;
  cout << "---------------------------" << endl;
  cout << "  TTjet_ATjet16 : " << h->GetBinContent(TTjet_ATjet16_bin) << endl;
  cout << "  TTjet_ATjet36 : " << h->GetBinContent(TTjet_ATjet36_bin) << endl;
  cout << "  TTjet_ATmu3   : " << h->GetBinContent(TTjet_ATmu3_bin) << endl;
  cout << "  TTjet_ATmu7   : " << h->GetBinContent(TTjet_ATmu7_bin) << endl;
  cout << "  TTgap_ATmu3   : " << h->GetBinContent(TTgap_ATmu3_bin) << endl;
  cout << "  TTgap_ATmu7   : " << h->GetBinContent(TTgap_ATmu7_bin) << endl;
  cout << "===========================" << endl;
}