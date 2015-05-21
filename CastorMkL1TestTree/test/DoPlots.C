#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"

#include "DatabaseRecordValues.C"
#include "MeanRatios.cc"

using namespace std;

class DoPlotsHelperClass {
  typedef map< string, map< int, double* > > mratios;
  typedef map< string, map< int, double* > >::iterator itratios;

public:
  DoPlotsHelperClass();

private:
  void CalcNewDbValues();
  void WriteTSRatioOutput();
  void WriteSatCorrDbFile();

  // void FillMapWithTSRatios(mratios & mTSRatios, mratios & mTSErrors);
  void DoPlots();

  DatabaseRecordValues dbV;
  double MeanCastor; int countCastor;
  double MeanMod[14]; int countMod[14];
  double NewDbValOriginal[14][16];
  double NewDbVal[14][16];
};


void DoPlots()
{
 
  DoPlotsHelperClass plots;
 
  plots.CalcNewDbValues();
  plots.WriteTSRatioOutput();
  plots.WriteSatCorrDbFile();
  
  // uses also old data from 2013 and 2011 but this data is not availible in the moment
  // plots.DoPlots();
}

DoPlotsHelperClass::DoPlotsHelperClass() {
  MeanCastor = 0;
  countCastor = 0;
  for(int iMod=0; iMod<14; iMod++) {
    MeanMod[iMod] = 0;
    countMod[iMod] = 0;
    for(int iSec=0; iSec<16; iSec++) {
      NewDbValOriginal[iMod][iSec] = 0;
      NewDbVal[iMod][iSec] = 0;
    }
  }
}


void DoPlotsHelperClass::CalcNewDbValues() {
  for(int iMod=0; iMod<14; iMod++) {
    for(int iSec=0; iSec<16; iSec++) {
      double val1 = -1; // just use one run // CastorTSRatio::MeanRatio_Run_210738_[iMod][iSec];
      double val2 = CastorTSRatio::MeanRatio_Run_245194_[iMod][iSec];
      double valtmp;
      
      valtmp = ( val1 == -1 ? ( val2 == -1 ? -1 : val2 ) : ( val2 == -1 ? val1 : (val1+val2)/2. ) );
      NewDbValOriginal[iMod][iSec] = valtmp;
      MeanMod[iMod] += ( valtmp == -1 ? 0 : valtmp ); countMod[iMod] += ( valtmp != -1 ? 1 : 0);
      MeanCastor += ( valtmp == -1 ? 0 : valtmp ); countCastor += ( valtmp != -1 ? 1 : 0);
    } // loop over Sectors
  } // loop over Modules


  MeanCastor /= ( countCastor != 0 ? countCastor : 1 );
  for(int iMod=0; iMod<14; iMod++) {
    MeanMod[iMod] /= ( countMod[iMod] != 0 ? countMod[iMod] : 1);
    for(int iSec=0; iSec<16; iSec++) {
      NewDbVal[iMod][iSec] = ( NewDbValOriginal[iMod][iSec] == -1 ? ( countMod[iMod] < 4 ? MeanCastor : MeanMod[iMod] ) : NewDbValOriginal[iMod][iSec] );
    } // loop over Sectors
  } // loop over Modules
}


void DoPlotsHelperClass::WriteTSRatioOutput() {
  char buf1[128];

  ofstream out; out.open("NewDbValues.cc");

  out << "namespace CastorTSRatio {" << endl << endl;
  
  out << "  double 2015_DbVal_WithEmptyChannels[14][16] = {" << endl;
  for(int iMod=0; iMod<14; iMod++) {
    out << "    { ";
    for(int iSec=0; iSec<16; iSec++) {
      sprintf(buf1,"% 7.4f",NewDbValOriginal[iMod][iSec]);
      out << buf1 << ( iSec == 16-1 ? " " : ", " );
    }
    out << ( iMod == 14-1 ? " }" : " }," ) << endl;
  }
  out << "  };" << endl << endl;
  
  sprintf(buf1,"% 7.4f",MeanCastor);
  out << "  double 2015_MeanCastor = " << buf1 << ";" << endl << endl;
  out << "  double 2015_MeanMod[14] = { ";
  for(int iMod=0; iMod<14; iMod++) {
    sprintf(buf1,"% 7.4f",MeanMod[iMod]);
    out << buf1 << ( iMod == 14-1 ? " " : ", " );
  }
  out << " };" << endl << endl;


  out << "  double 2015_DbVal[14][16] = {" << endl;
  for(int iMod=0; iMod<14; iMod++) {
    out << "    { ";
    for(int iSec=0; iSec<16; iSec++) {
      sprintf(buf1,"% 7.4f",NewDbVal[iMod][iSec]);
      out << buf1 << ( iSec == 16-1 ? " " : ", " );
    }
    out << ( iMod == 14-1 ? " }" : " }," ) << endl;
  }
  out << "  };" << endl << endl;
  out << "}" << endl;
  out.close();
}

void DoPlotsHelperClass::WriteSatCorrDbFile() {
  char buf[256];

  ofstream out; out.open("CastorCondSaturationCorrs_Run245194.txt");

  out << "#             eta             phi             dep             det    value      DetId" << endl;
  for(int isec=0; isec<16; isec++) {
    for(int imod=0; imod<14; imod++) {
      unsigned int idetid = 1442840576 + (imod+1) + 16*isec;
      if( imod < 2 ) sprintf(buf,"               -1              %2d              %2d       CASTOR_EM   %6.4f   %X", isec+1, imod+1, NewDbVal[imod][isec],idetid);
      else           sprintf(buf,"               -1              %2d              %2d      CASTOR_HAD   %6.4f   %X", isec+1, imod+1, NewDbVal[imod][isec],idetid);
      out << buf << endl;
    }
  }

  out.close();
}


// void DoPlotsHelperClass::FillMapWithTSRatios(mratios & mTSRatios, mratios & mTSErrors) {
//   for(int iMod=0; iMod<14; iMod++) {
//     mTSRatios["136066"][iMod] = CastorTSRatio::MeanRatio_Run_136066_[iMod];
//     mTSRatios["136082"][iMod] = CastorTSRatio::MeanRatio_Run_136082_[iMod];
//     mTSRatios["142928"][iMod] = CastorTSRatio::MeanRatio_Run_142928_[iMod];
//     mTSRatios["144089"][iMod] = CastorTSRatio::MeanRatio_Run_144089_[iMod];
//     mTSRatios["146437"][iMod] = CastorTSRatio::MeanRatio_Run_146437_[iMod];
//     mTSRatios["148822"][iMod] = CastorTSRatio::MeanRatio_Run_148822_[iMod];
//     mTSRatios["160957"][iMod] = CastorTSRatio::MeanRatio_Run_160957_[iMod];
//     mTSRatios["163765"][iMod] = CastorTSRatio::MeanRatio_Run_163765_[iMod];
//     //mTSRatios["178866"][iMod] = CastorTSRatio::MeanRatio_Run_178866_[iMod];
//     mTSRatios["210738"][iMod] = CastorTSRatio::MeanRatio_Run_210738_[iMod];
//     mTSRatios["211390"][iMod] = CastorTSRatio::MeanRatio_Run_211390_[iMod];

//     mTSErrors["136066"][iMod] = CastorTSRatio::MeanRatio_Err_Run_136066_[iMod];
//     mTSErrors["136082"][iMod] = CastorTSRatio::MeanRatio_Err_Run_136082_[iMod];
//     mTSErrors["142928"][iMod] = CastorTSRatio::MeanRatio_Err_Run_142928_[iMod];
//     mTSErrors["144089"][iMod] = CastorTSRatio::MeanRatio_Err_Run_144089_[iMod];
//     mTSErrors["146437"][iMod] = CastorTSRatio::MeanRatio_Err_Run_146437_[iMod];
//     mTSErrors["148822"][iMod] = CastorTSRatio::MeanRatio_Err_Run_148822_[iMod];
//     mTSErrors["160957"][iMod] = CastorTSRatio::MeanRatio_Err_Run_160957_[iMod];
//     mTSErrors["163765"][iMod] = CastorTSRatio::MeanRatio_Err_Run_163765_[iMod];
//     //mTSErrors["178866"][iMod] = CastorTSRatio::MeanRatio_Err_Run_178866_[iMod];
//     mTSErrors["210738"][iMod] = CastorTSRatio::MeanRatio_Err_Run_210738_[iMod];
//     mTSErrors["211390"][iMod] = CastorTSRatio::MeanRatio_Err_Run_211390_[iMod];
//   }

// }

void DoPlotsHelperClass::DoPlots() {
  mratios mTSRatios;
  mratios mTSErrors;

  // FillMapWithTSRatios(mTSRatios,mTSErrors);

  TCanvas * c[14];
  TH1 * hRatios[14][16];
  TH2 * hNewDBVal = new TH2F("hNewDBVal","TS-Ratios for 2015;Mod;Sec",14,0,14,16,0,16);

  char buf1[128], buf2[128];
  for(int iMod=0; iMod<14; iMod++)
    {
      sprintf(buf1,"%d",iMod);
      c[iMod] = new TCanvas(buf1,buf1,1000,1000);
      c[iMod]->Divide(4,4);

      for(int iSec=0; iSec<16; iSec++)
	{
	  sprintf(buf1,"hRatios_%d_%d",iMod,iSec); sprintf(buf2,"Mod %d / Sec %d",iMod,iSec);
	  hRatios[iMod][iSec] = new TH1F(buf1,buf2,mTSRatios.size(),0,mTSRatios.size());
	  hRatios[iMod][iSec]->SetMinimum(-0.5);
	  hRatios[iMod][iSec]->SetMaximum( 0.5);

	  hNewDBVal->Fill( iMod, iSec, double(int(1000*NewDbVal[iMod][iSec]))/1000. );

	  itratios itVal = mTSRatios.begin();
	  itratios itErr = mTSErrors.begin();
	  for(unsigned int iRun=0; iRun<mTSRatios.size(); iRun++)
	    {     
	      double val = itVal->second[iMod][iSec];
	      double err = itErr->second[iMod][iSec];

	      if( val != -1 ) {
		val = val - dbV.getVal(iMod,iSec); val /= dbV.getVal(iMod,iSec);
		hRatios[iMod][iSec]->Fill(itVal->first.c_str(),val);

		err /= dbV.getVal(iMod,iSec);
		hRatios[iMod][iSec]->SetBinError( hRatios[iMod][iSec]->GetXaxis()->FindBin(itVal->first.c_str()) , err );
	      }
	      else {
		hRatios[iMod][iSec]->Fill(itVal->first.c_str(),0);
	      }

	      itVal++;
	      itErr++;
	    } // loop over runs

	  c[iMod]->cd(iSec+1);
	  hRatios[iMod][iSec]->Draw("E");

	} // loop over sectors

      sprintf(buf1,"RelativeDiff_TSRatiosToDBValues_Mod%d.pdf",iMod);
      c[iMod]->Print(buf1);
    } // loop over modules

  gStyle->SetOptStat("");

  TCanvas * cNewDBVal = new TCanvas("cNewDBVal","",2000,1500); cNewDBVal->cd();
  hNewDBVal->Draw("COLZ TEXT");
  cNewDBVal->Print("NewDBVal_2015.pdf");

}
