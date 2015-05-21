#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <fstream>

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TVectorF.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TChain.h"
#include "TGraph.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TLine.h"

// Database Values at the moment
#include "DatabaseRecordValues.C"

using namespace std;

#define N_RUN_MAX 10;

struct CASTOR_RECORD {
  int event, bcn, ls, run, time, orbit;
  float recoRHe[14][16];
  float newRHe[14][16];
  int newRHs[14][16];
  float signal[14][16][10];
  int signalADC[14][16][10];
};

struct RATIO_RECORD {
  int run;

  TGraph * grHighEnergyTSRatio[14][16];
  TGraph * grHighEnergyTSRatioADC[14][16];
  vector<double> vHighEnergyRatioTS[14][16];
  vector<double> vHighEnergySumTS[14][16];
  vector<double> vHighEnergyTS4ADC[14][16];
  double meanHighEnergyRatioTS[14][16];
  double rmsHighEnergyRatioTS[14][16];
  double errHighEnergyRatioTS[14][16];

  TH2 * hRatiosMean;
  TH2 * hRatiosRMS;
  TH2 * hRatiosErr;
  TH2 * hRatiosEnt;

  TH1 * hRatiosMeanDist;
  TH1 * hRatiosMeanDistMod[14];

  TGraph * grTSRatio[14][16];
  TGraph * grTSRatioADC[14][16];
  vector<double> vgrTSRatio[14][16];
  vector<double> vgrTSSum[14][16];
  vector<double> vgrTS4ADC[14][16];

  unsigned int NEvents;
  unsigned int NSatEvents;
  unsigned int NShiftedTS;

  // statistic
  TH2 * hTotSatEvt;
  TH2 * hSatEvtRatio;
  
};

class TreeAnalyzer {
public:
  TreeAnalyzer(TChain * chain_, const string & FigureType_);
  void beginAnalyze();
  void endAnalyze();
  void Analyze(int iEvent);

private:
  void calcRatio(int mod, int sec, int runidx);
  void printEventStat();
  void printOutputFile();

  TFile * file;
  TChain * chain;
  CASTOR_RECORD fTreeRecord;

  map<int,int> mRunCnt;

  deque<RATIO_RECORD> RatioRecord;

  string FigureType;
};

void analyze_tree(const string fname = "../out.root", const string figure_type = "jpg", const int MaxNumEvents = -1)
{
 
  //TH1* htest = new TH1F("htest","",100,0,35000);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat("emr");
  gStyle->SetPalette(1);
  
  TChain * chain = new TChain("saturationcorrstudy/CastorRecoSample");
  chain->Add("SaturationCorrStudy.root");

  TreeAnalyzer analyzer(chain,figure_type);

  analyzer.beginAnalyze();
  int Nevents = chain->GetEntries();
  if( MaxNumEvents > 0 ) Nevents = MaxNumEvents;
  cout << "==================================================" << endl;
  cout << "Run over " << Nevents << " Events" << endl;
  cout << "==================================================" << endl;
  for(int i=0; i<Nevents; i++) {
    if( i%(Nevents/50) == (Nevents/50)-1 ) cout << "." << flush;
    analyzer.Analyze(i);
  }
  cout << endl;
  analyzer.endAnalyze();

}

TreeAnalyzer::TreeAnalyzer(TChain * chain_, const string & FigureType_)
  : chain(chain_), FigureType(FigureType_)
{
  file = TFile::Open("AlyCastorRecord.root","RECREATE");

  mRunCnt.clear();
}

void TreeAnalyzer::beginAnalyze()
{
  chain->SetBranchAddress("CastorRecord",&fTreeRecord);
}

void TreeAnalyzer::Analyze(int iEvent)
{
  chain->GetEntry(iEvent);

  int run = fTreeRecord.run;
  if(mRunCnt.find(run) == mRunCnt.end()) {
    int ms = mRunCnt.size();
    mRunCnt[run] = ms;

    RatioRecord.push_back(RATIO_RECORD());

    RatioRecord.back().run = run;

    RatioRecord.back().NEvents = 0;
    RatioRecord.back().NSatEvents = 0;
    RatioRecord.back().NShiftedTS = 0;

    // statistics
    char buf[128];
    sprintf(buf,"hTotSatEvt_%d",run);   RatioRecord.back().hTotSatEvt = new TH2F(buf,"",14,0,14,16,0,16);
    sprintf(buf,"hSatEvtRatio_%d",run); RatioRecord.back().hSatEvtRatio = new TH2F(buf,"",14,0,14,16,0,16);
  }


  int runidx = mRunCnt.find(run)->second;
  RatioRecord[runidx].NEvents++;

  bool bSatEvent = false;
  bool bShiftedTS = false;

  for(int i=0; i<14; i++)
    for(int j=0; j<16; j++)
      {
	// calculate ratio and sum of the 2 TS for every event and channel
	double ratio = fTreeRecord.signal[i][j][5] / fTreeRecord.signal[i][j][4];
	double sum   = fTreeRecord.signal[i][j][4] + fTreeRecord.signal[i][j][5];

	// commment: often the analysis only use the first five channels
	//           therefor the cut on mod < 5
	// check if saturation bit was set in the new RecHit reco
	if(/*i < 5 && */fTreeRecord.newRHs[i][j] != 0) {
	  bSatEvent = true;
	  RatioRecord[runidx].hTotSatEvt->Fill(i,j);
	  RatioRecord[runidx].hSatEvtRatio->Fill(i,j);
	}
	
	// check if there is a event with shifted TS 
	// but not in the noise region => Cut on ADC > 80
	if(i < 5 && fTreeRecord.signalADC[i][j][5] > 80 && 
	   fTreeRecord.signal[i][j][4] < fTreeRecord.signal[i][j][5])
	  bShiftedTS = true;

	// go to the high energy region and save ratios 
	// but be sure not to save saturated events
	if(fTreeRecord.signalADC[i][j][4] > 110 && fTreeRecord.signalADC[i][j][4] < 127 &&
	   fTreeRecord.signalADC[i][j][5] < fTreeRecord.signalADC[i][j][4])
	  {
	    RatioRecord[runidx].vHighEnergyRatioTS[i][j].push_back(ratio);
	    RatioRecord[runidx].vHighEnergySumTS[i][j].push_back(sum);
	    RatioRecord[runidx].vHighEnergyTS4ADC[i][j].push_back(fTreeRecord.signalADC[i][j][4]);
	    /****DEBUG****
	    if(runidx == 0 && i == 0 && j == 11)
	      cout << "Run: " << run << "\t"
		   << "Mod: " << i << " Sec: " << j << "\t"
		   << "Ratio: " << ratio << " Sum: " << sum << endl;
	    ****DEBUG****/
	  }

	// save ration and sum of all events
	// limit number to 1000 because of memspace
	if(RatioRecord[runidx].vgrTSRatio[i][j].size() < 1000 &&
	   fTreeRecord.signalADC[i][j][4] > 0 && 
	   fTreeRecord.signalADC[i][j][5] > 0 &&
	   ratio > 0 && ratio < 1)
	  {
	    RatioRecord[runidx].vgrTSRatio[i][j].push_back(ratio);
	    RatioRecord[runidx].vgrTSSum[i][j].push_back(sum);
	    RatioRecord[runidx].vgrTS4ADC[i][j].push_back(fTreeRecord.signalADC[i][j][4]);
	  }	
      } // Loop over Module & Sector

  // count number of saturated and shifted events
  if(bSatEvent) RatioRecord[runidx].NSatEvents++;
  if(bShiftedTS) RatioRecord[runidx].NShiftedTS++;
}

void TreeAnalyzer::endAnalyze()
{

  TCanvas * cgr[14][mRunCnt.size()];
  TCanvas * cgrADC[14][mRunCnt.size()];
  TCanvas * cgrerr[14];
  TCanvas * chRatio[mRunCnt.size()];
  TCanvas * chRatioMod[mRunCnt.size()];

  TGraphErrors * grerrHighEnergyTSRatio[14][16];
  TGraph * grDatabaseRecordValue[14][16];
  double MeanHighEnergyTSRatio[14][16][mRunCnt.size()];
  double ErrHighEnergyTSRatio[14][16][mRunCnt.size()];
  double RunNumbers[mRunCnt.size()];

  DatabaseRecordValues DatabaseVal;

  for(unsigned int runidx=0; runidx<mRunCnt.size(); runidx++)
    {
      char buf[128];

      // histos for channelmap with mean ratios for the channels
      sprintf(buf,"hRatiosMean_%d",RatioRecord[runidx].run); RatioRecord[runidx].hRatiosMean = new TH2F(buf,"",14,0,14,16,0,16);
      sprintf(buf,"hRatiosRMS_%d",RatioRecord[runidx].run);  RatioRecord[runidx].hRatiosRMS = new TH2F(buf,"",14,0,14,16,0,16);
      sprintf(buf,"hRatiosErr_%d",RatioRecord[runidx].run);  RatioRecord[runidx].hRatiosErr = new TH2F(buf,"",14,0,14,16,0,16);
      sprintf(buf,"hRatiosEnt_%d",RatioRecord[runidx].run);  RatioRecord[runidx].hRatiosEnt = new TH2F(buf,"",14,0,14,16,0,16);

      // distribution of channel ratios for all channels in castor
      sprintf(buf,"hRatiosMeanDist_%d",RatioRecord[runidx].run); RatioRecord[runidx].hRatiosMeanDist = new TH1F(buf,"",20,0.05,0.25);

      sprintf(buf,"chRatio[%d]",runidx);
      chRatio[runidx] = new TCanvas(buf,"",1200,1200);
      
      sprintf(buf,"chRatioMod[%d]",runidx);
      chRatioMod[runidx] = new TCanvas(buf,"",1200,1200); chRatioMod[runidx]->Divide(4,4);

      RunNumbers[runidx] =  RatioRecord[runidx].run;

      for(int iMod=0; iMod<14; iMod++) {
	sprintf(buf,"cgr[%d][%d]",iMod,runidx);
	cgr[iMod][runidx] = new TCanvas(buf,"",1200,1200); cgr[iMod][runidx]->Divide(4,4);
	sprintf(buf,"cgrADC[%d][%d]",iMod,runidx);
	cgrADC[iMod][runidx] = new TCanvas(buf,"",1200,1200); cgrADC[iMod][runidx]->Divide(4,4);
	
	// distribution of channel ratios for a particular ring respectivaly module
	sprintf(buf,"hRatiosMeanDistMod%d_%d",iMod,RatioRecord[runidx].run);
	RatioRecord[runidx].hRatiosMeanDistMod[iMod] = new TH1F(buf,"",20,0.05,0.25);
	
	for(int iSec=0; iSec<16; iSec++) {
	  // calculate rations for every channel and save it also in the RatioRecord struct
	  calcRatio(iMod,iSec,runidx);

	  MeanHighEnergyTSRatio[iMod][iSec][runidx] = 0;
	  ErrHighEnergyTSRatio[iMod][iSec][runidx] = 0;

	  // fill histograms
	  if(RatioRecord[runidx].meanHighEnergyRatioTS[iMod][iSec] != -1) {
	    RatioRecord[runidx].hRatiosMean->Fill(iMod,iSec,floor(1000*RatioRecord[runidx].meanHighEnergyRatioTS[iMod][iSec])/1000.);
	    RatioRecord[runidx].hRatiosRMS->Fill(iMod,iSec,floor(1000*RatioRecord[runidx].rmsHighEnergyRatioTS[iMod][iSec])/1000.);
      	    RatioRecord[runidx].hRatiosErr->Fill(iMod,iSec,floor(10000*RatioRecord[runidx].errHighEnergyRatioTS[iMod][iSec])/10000.);
	    RatioRecord[runidx].hRatiosEnt->Fill(iMod,iSec,RatioRecord[runidx].vHighEnergyRatioTS[iMod][iSec].size());

	    RatioRecord[runidx].hRatiosMeanDist->Fill(RatioRecord[runidx].meanHighEnergyRatioTS[iMod][iSec]);
	    RatioRecord[runidx].hRatiosMeanDistMod[iMod]->Fill(RatioRecord[runidx].meanHighEnergyRatioTS[iMod][iSec]);

	    MeanHighEnergyTSRatio[iMod][iSec][runidx] = RatioRecord[runidx].meanHighEnergyRatioTS[iMod][iSec];
	    ErrHighEnergyTSRatio[iMod][iSec][runidx] = RatioRecord[runidx].errHighEnergyRatioTS[iMod][iSec];
	  }

	  const int sizeRatio = (int)RatioRecord[runidx].vgrTSRatio[iMod][iSec].size();
	  const int sizeHighEnergyRatio = (int)RatioRecord[runidx].vHighEnergyRatioTS[iMod][iSec].size();
	  if(sizeRatio != 0)
	    {
	      char grTitle[128];
	      sprintf(grTitle,"Run%d_Mod%d_Sec%d",RatioRecord[runidx].run,iMod+1,iSec+1);
	      TMultiGraph * mgrTSRatio = new TMultiGraph("mgrTSRatio",grTitle);

	      sprintf(grTitle,"Run%d_Mod%d_Sec%d",RatioRecord[runidx].run,iMod+1,iSec+1);
	      TMultiGraph * mgrTSRatioADC = new TMultiGraph("mgrTSRatioADC",grTitle);

	      double TSRatio[sizeRatio], TSSum[sizeRatio], TS4ADC[sizeRatio];
	  
	      for(int k=0; k<sizeRatio; k++) {
		TSRatio[k] = RatioRecord[runidx].vgrTSRatio[iMod][iSec][k];
		TSSum[k]   = RatioRecord[runidx].vgrTSSum[iMod][iSec][k];
		TS4ADC[k]   = RatioRecord[runidx].vgrTS4ADC[iMod][iSec][k];
	      }

	      // plot for every event Ratio Vs Sum of the 2 TS
	      RatioRecord[runidx].grTSRatio[iMod][iSec] = new TGraph(sizeRatio,TSSum,TSRatio);
	      RatioRecord[runidx].grTSRatio[iMod][iSec]->SetMinimum(0);
	      RatioRecord[runidx].grTSRatio[iMod][iSec]->SetMaximum(1);
	      RatioRecord[runidx].grTSRatio[iMod][iSec]->SetMarkerStyle(21);
	      RatioRecord[runidx].grTSRatio[iMod][iSec]->SetMarkerSize(0.3);

	      // plot for every event Ratio Vs ADC counts of TS4
	      RatioRecord[runidx].grTSRatioADC[iMod][iSec] = new TGraph(sizeRatio,TS4ADC,TSRatio);
	      RatioRecord[runidx].grTSRatioADC[iMod][iSec]->SetMinimum(0);
	      RatioRecord[runidx].grTSRatioADC[iMod][iSec]->SetMaximum(1);
	      RatioRecord[runidx].grTSRatioADC[iMod][iSec]->SetMarkerStyle(21);
	      RatioRecord[runidx].grTSRatioADC[iMod][iSec]->SetMarkerSize(0.3);

	      /******* Should maybe included ********
	       // Dummy Graph to set x-axis range only for mgrTSRatioADC
	       double xDummy[2] = {0,127}, yDummy[2] = {0,1}; TGraph * grDummy = new TGraph(2,xDummy,yDummy);
	       mgrTSRatioADC->Add(grDummy);
	      **************************************/
	      
	      //cgr[iMod][runidx]->cd(iSec+1);
	      //RatioRecord[runidx].grTSRatio[iMod][iSec]->Draw("AP");
	      mgrTSRatio->Add(RatioRecord[runidx].grTSRatio[iMod][iSec]);
	      mgrTSRatioADC->Add(RatioRecord[runidx].grTSRatioADC[iMod][iSec]);
	      
	      if(sizeHighEnergyRatio != 0)
		{
		  double HighEnergyTSRatio[sizeHighEnergyRatio], HighEnergyTSSum[sizeHighEnergyRatio], HighEnergyTS4ADC[sizeHighEnergyRatio];

		  for(int k=0; k<sizeHighEnergyRatio; k++) {
		    HighEnergyTSRatio[k] = RatioRecord[runidx].vHighEnergyRatioTS[iMod][iSec][k];
		    HighEnergyTSSum[k]   = RatioRecord[runidx].vHighEnergySumTS[iMod][iSec][k];
		    HighEnergyTS4ADC[k]  = RatioRecord[runidx].vHighEnergyTS4ADC[iMod][iSec][k];
		    /****DEBUG****
		    if(runidx == 0 && iMod == 0 && iSec == 11)
		      cout << "Runidx: " << runidx << "\t"
			   << "Mod: " << iMod << " Sec: " << iSec << "\t"
			   << "Ratio: " << RatioRecord[runidx].vHighEnergyRatioTS[iMod][iSec][k]
			   << " Sum: "  << RatioRecord[runidx].vHighEnergySumTS[iMod][iSec][k] << endl;
		    ****DEBUG****/
		  }

		  // plot for event which was used to calculate the overall ratio
		  // in the particular channel the Ratio Vs. Sum of the 2 TS
		  RatioRecord[runidx].grHighEnergyTSRatio[iMod][iSec]
		    = new TGraph(sizeHighEnergyRatio,HighEnergyTSSum,HighEnergyTSRatio);
		  RatioRecord[runidx].grHighEnergyTSRatio[iMod][iSec]->SetMinimum(0);
		  RatioRecord[runidx].grHighEnergyTSRatio[iMod][iSec]->SetMaximum(1);
		  RatioRecord[runidx].grHighEnergyTSRatio[iMod][iSec]->SetMarkerStyle(21);
		  RatioRecord[runidx].grHighEnergyTSRatio[iMod][iSec]->SetMarkerSize(0.4);
		  RatioRecord[runidx].grHighEnergyTSRatio[iMod][iSec]->SetMarkerColor(kRed);

		  // plot for event which was used to calculate the overall ratio
		  // in the particular channel the Ratio Vs. ADC counts of TS4
		  RatioRecord[runidx].grHighEnergyTSRatioADC[iMod][iSec]
		    = new TGraph(sizeHighEnergyRatio,HighEnergyTS4ADC,HighEnergyTSRatio);
		  RatioRecord[runidx].grHighEnergyTSRatioADC[iMod][iSec]->SetMinimum(0);
		  RatioRecord[runidx].grHighEnergyTSRatioADC[iMod][iSec]->SetMaximum(1);
		  RatioRecord[runidx].grHighEnergyTSRatioADC[iMod][iSec]->SetMarkerStyle(21);
		  RatioRecord[runidx].grHighEnergyTSRatioADC[iMod][iSec]->SetMarkerSize(0.4);
		  RatioRecord[runidx].grHighEnergyTSRatioADC[iMod][iSec]->SetMarkerColor(kRed);
		  
		  //RatioRecord[runidx].grHighEnergyTSRatio[iMod][iSec]->Draw("SAME P");
		  mgrTSRatio->Add(RatioRecord[runidx].grHighEnergyTSRatio[iMod][iSec]);
		  mgrTSRatioADC->Add(RatioRecord[runidx].grHighEnergyTSRatioADC[iMod][iSec]);
		}
	      
	      cgr[iMod][runidx]->cd(iSec+1); mgrTSRatio->Draw("AP");
	      cgrADC[iMod][runidx]->cd(iSec+1); mgrTSRatioADC->Draw("AP");
	    }
	} // Loop over Sector

	sprintf(buf,"RatioTS_SumTS_Mod_%d_All_Sec_Run%d.%s",iMod+1,RatioRecord[runidx].run,FigureType.c_str());
	cgr[iMod][runidx]->Print(buf);
	sprintf(buf,"RatioTS_TS4ADC_Mod_%d_All_Sec_Run%d.%s",iMod+1,RatioRecord[runidx].run,FigureType.c_str());
	cgrADC[iMod][runidx]->Print(buf);
	 
	chRatioMod[runidx]->cd(iMod+1);
	RatioRecord[runidx].hRatiosMeanDistMod[iMod]->Draw();
      } // Loop over Module

      RatioRecord[runidx].hSatEvtRatio->Scale(1./RatioRecord[runidx].NEvents);
      char tmpTitle[128]; sprintf(tmpTitle,"Number of Total Events: %d",RatioRecord[runidx].NEvents);
      RatioRecord[runidx].hSatEvtRatio->SetTitle(tmpTitle);
      TCanvas * tmp = new TCanvas("tmp");
      tmp->Divide(2,1);
      tmp->cd(1); RatioRecord[runidx].hSatEvtRatio->Draw("colZ text");
      tmp->cd(2); RatioRecord[runidx].hTotSatEvt->Draw("colZ text");
      tmp->Print("SaturatedEventsStat.jpg");
      tmp->Print("SaturatedEventsStat.eps");

       
      chRatio[runidx]->cd();
      RatioRecord[runidx].hRatiosMeanDist->Draw();
      sprintf(buf,"RatioTS_Distribution_Run%d.%s",RatioRecord[runidx].run,FigureType.c_str());
      chRatio[runidx]->Print(buf);

      sprintf(buf,"RatioTS_Distribution_All_Mod_Run%d.%s",RatioRecord[runidx].run,FigureType.c_str());
      chRatioMod[runidx]->Print(buf);
    } // Loop over Runs


  for(int iMod=0; iMod<14; iMod++) {
    char buf[128]; sprintf(buf,"cgrerr[%d]",iMod);
    cgrerr[iMod] = new TCanvas(buf,"",1200,1200); cgrerr[iMod]->Divide(4,4);

    for(int iSec=0; iSec<16; iSec++) {
      // plot for every channel the distribution of ratios over time respectively runnumber
      grerrHighEnergyTSRatio[iMod][iSec]
	= new TGraphErrors(mRunCnt.size(),RunNumbers,MeanHighEnergyTSRatio[iMod][iSec],
			   0,ErrHighEnergyTSRatio[iMod][iSec]);
      //grerrHighEnergyTSRatio[iMod][iSec]->SetMinimum(0.05);
      //grerrHighEnergyTSRatio[iMod][iSec]->SetMaximum(0.25);
      grerrHighEnergyTSRatio[iMod][iSec]->SetMarkerStyle(21);
      grerrHighEnergyTSRatio[iMod][iSec]->SetMarkerSize(0.2);
      grerrHighEnergyTSRatio[iMod][iSec]->SetMarkerColor(kRed);

      // Mutligraph to trick root! TLine was not working!
      sprintf(buf,"RatioTS_Mod_%d_Sec_%d",iMod+1,iSec+1);
      TMultiGraph * mgrHighEnergyTSRatio = new TMultiGraph(buf,buf);
      //grerrHighEnergyTSRatio[iMod][iSec]->SetTitle(buf);

      for(unsigned int iPoint=mRunCnt.size(); iPoint>0; iPoint--) {
	double x,y;
	grerrHighEnergyTSRatio[iMod][iSec]->GetPoint(iPoint-1,x,y);
	if(y == 0.0) {
	  grerrHighEnergyTSRatio[iMod][iSec]->RemovePoint(iPoint-1);
	  /****DEBUG****
	  cout << "For Mod:" << iMod+1 << "; Sec:" << iSec+1 
	       << " => Remove Point:" << iPoint << " = [" << x << "," << y << "]" << endl;
	  ****DEBUG****/
	}
      }
      grerrHighEnergyTSRatio[iMod][iSec]->Sort();

      double RecordVal = DatabaseVal.getVal(iMod,iSec);
      // I trick root here! TLine was not working!
      double RecordValues[mRunCnt.size()]; for(unsigned int i=0; i<mRunCnt.size(); i++) RecordValues[i]=RecordVal;
      grDatabaseRecordValue[iMod][iSec] = new TGraph(mRunCnt.size(),RunNumbers,RecordValues);
      //grDatabaseRecordValue[iMod][iSec]->SetMarkerStyle(21);
      grDatabaseRecordValue[iMod][iSec]->SetMarkerColor(kRed);
      grDatabaseRecordValue[iMod][iSec]->SetLineColor(kRed);

      mgrHighEnergyTSRatio->Add(grDatabaseRecordValue[iMod][iSec]);
      if( grerrHighEnergyTSRatio[iMod][iSec]->GetN() != 0 ) mgrHighEnergyTSRatio->Add(grerrHighEnergyTSRatio[iMod][iSec]);

      cgrerr[iMod]->cd(iSec+1);
      mgrHighEnergyTSRatio->Draw("ALP");
      //grerrHighEnergyTSRatio[iMod][iSec]->Draw("ALP");
    } // Loop over Sector

    sprintf(buf,"Mean_RatioTS_Mod_%d_All_Sec.%s",iMod+1,FigureType.c_str());
    cgrerr[iMod]->Print(buf);
  } // Loop over Module

  gStyle->SetOptStat("e");
  for(map<int,int>::iterator it = mRunCnt.begin(); it != mRunCnt.end(); it++)
    {
      int runidx = it->second;
      char buf[128];

      sprintf(buf,"TS_Ratios_mean_Run%d.%s",it->first,FigureType.c_str());
      TCanvas * cMeanRatioTS = new TCanvas("cMeanRatioTS","",700,800); cMeanRatioTS->cd()->Update();
      RatioRecord[runidx].hRatiosMean->Draw("colZText"); cMeanRatioTS->Print(buf);

      sprintf(buf,"TS_Ratios_RMS_Run%d.%s",it->first,FigureType.c_str());
      TCanvas * cRMSRatioTS = new TCanvas("cRMSRatioTS","",700,800); cRMSRatioTS->cd()->Update();
      RatioRecord[runidx].hRatiosRMS->Draw("colZText"); cRMSRatioTS->Print(buf);

      sprintf(buf,"TS_Ratios_Err_Run%d.%s",it->first,FigureType.c_str());
      TCanvas * cErrRatioTS = new TCanvas("cErrRatioTS","",700,800); cErrRatioTS->cd()->Update();
      RatioRecord[runidx].hRatiosErr->Draw("colZText"); cErrRatioTS->Print(buf);

      sprintf(buf,"TS_Ratios_Entries_Run%d.%s",it->first,FigureType.c_str());
      TCanvas * cMErrRatioTS = new TCanvas("cMErrRatioTS","",700,800); cMErrRatioTS->cd()->Update();
      RatioRecord[runidx].hRatiosEnt->Draw("colZText"); cMErrRatioTS->Print(buf);
    }
  
  printEventStat();
  printOutputFile();

  file->Write();
}


void TreeAnalyzer::calcRatio(int mod, int sec, int runidx)
{
  double mean = 0;
  double rms = 0;
  double error = 0;
  
  unsigned int size = RatioRecord[runidx].vHighEnergyRatioTS[mod][sec].size();
  if(size < 5) {
    RatioRecord[runidx].meanHighEnergyRatioTS[mod][sec] = -1;
    RatioRecord[runidx].rmsHighEnergyRatioTS[mod][sec] = -1;
    RatioRecord[runidx].errHighEnergyRatioTS[mod][sec] = -1;
    //cout << "No Ratio calculated for Mod,Sec = " <<mod+1<<","<<sec+1<< endl;
    return;
  }
  
  for(unsigned int k=0; k<size; k++)
    mean += RatioRecord[runidx].vHighEnergyRatioTS[mod][sec][k]/size;

  for(unsigned int k=0; k<size; k++)
    rms += (RatioRecord[runidx].vHighEnergyRatioTS[mod][sec][k]-mean) * (RatioRecord[runidx].vHighEnergyRatioTS[mod][sec][k]-mean) / size;
  rms = sqrt(rms);
  error = rms/sqrt(size-1);
  
  RatioRecord[runidx].meanHighEnergyRatioTS[mod][sec]=mean;
  RatioRecord[runidx].rmsHighEnergyRatioTS[mod][sec]=rms;
  RatioRecord[runidx].errHighEnergyRatioTS[mod][sec]=error;
  //cout << "Ratior for Mod,Sec = " <<mod+1<<","<<sec+1<< " is : " << RatioRecord[runidx].meanHighEnergyRatioTS[mod][sec]
  //<< " RMS = " << RatioRecord[runidx].rmsHighEnergyRatioTS[mod][sec] << endl;
}

void TreeAnalyzer::printEventStat()
{
  cout << "===============================================================================" << endl;
  cout << "================================= Statistics ==================================" << endl;
  cout << "===============================================================================" << endl;
  cout << endl;
  for(map<int,int>::iterator it = mRunCnt.begin(); it != mRunCnt.end(); it++)
    {
      int run = it->first;
      int runidx = it->second;
      cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      cout << "Stats for Run " << run << " : " <<  endl;
      cout << "Number of Events : " << RatioRecord[runidx].NEvents << endl;
      cout << "Number of Saturated Events : " << RatioRecord[runidx].NSatEvents << endl;
      cout << "Number of Events with shifted TS : " << RatioRecord[runidx].NShiftedTS << endl;
      cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      cout << endl;
    }
}

void TreeAnalyzer::printOutputFile()
{
  // File to write the TS MeanRatios down
  ofstream ofMeanRatios; ofMeanRatios.open("MeanRatios.cc");

  ofMeanRatios << "namespace CastorTSRatio {" << endl << endl;

  for(unsigned int runidx=0; runidx<mRunCnt.size(); runidx++)
    {
      char buf[128];

      string prec = "% 8.5f";

      // for every run start to write a new array
      sprintf(buf,"  double MeanRatio_Run_%d_[14][16] = {",RatioRecord[runidx].run);
      ofMeanRatios << buf << endl;

      for(int iMod=0; iMod<14; iMod++) {
	ofMeanRatios << "    { "; // new line with sector numbers
	for(int iSec=0; iSec<16; iSec++) {
	  // write mean high energy ratios in the .cc outputfile
	  sprintf(buf,prec.c_str(),RatioRecord[runidx].meanHighEnergyRatioTS[iMod][iSec]);
	  ofMeanRatios << " " << buf << (iSec < 16-1 ? "," : "");
	}
	ofMeanRatios << " }" << (iMod < 14-1 ? "," : "" ) << endl; // end of sector line in .cc output file
      }
      ofMeanRatios << "};" << endl << endl;

      // same again for errors on the mean
      sprintf(buf,"  double MeanRatio_Err_Run_%d_[14][16] = {",RatioRecord[runidx].run);
      ofMeanRatios << buf << endl;
      for(int iMod=0; iMod<14; iMod++) {
	ofMeanRatios << "   { "; // new line with sector numbers
	for(int iSec=0; iSec<16; iSec++) {
	  // write mean high energy ratios in the .cc outputfile
	  sprintf(buf,prec.c_str(),RatioRecord[runidx].errHighEnergyRatioTS[iMod][iSec]);
	  ofMeanRatios << " " << buf << (iSec < 16-1 ? "," : "");
	}
	ofMeanRatios << " }" << (iMod < 14-1 ? "," : "" ) << endl; // end of sector line in .cc output file
      }
      ofMeanRatios << "};" << endl << endl << endl;

    }
  ofMeanRatios << "}" << endl;
  // close output .cc file
  ofMeanRatios.close();
}
