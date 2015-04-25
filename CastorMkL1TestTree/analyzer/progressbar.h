#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__

#include <iostream>
#include <string>
#include <cstdlib>

class progressbar
{
private:
  std::string title;

  int nEntries;
  int nDots;
  int nPace;
  int nShow;
  

  char buf[128];
public:
  progressbar(const std::string& title_, const int& nEntries_)
    : title(title_), nEntries(nEntries_), nDots(30)
  {
    nPace = std::max(1, nEntries/nDots);
    nShow = nPace == 1 ? nEntries : nEntries-(nEntries%nDots);
  }

  void printBar(const int& iEvent)
  {
    if( iEvent%nPace == 0 && iEvent < nShow ) {
      double pct = (double)iEvent/(double)nEntries*100;

      std::cout << "\r" << title << ": |";
      for(int idot=0; idot<nDots; idot++)
        if( idot<iEvent/nPace ) std::cout << "#";
        else std::cout << " ";
      std::cout << "|";
      
      sprintf(buf,"[% 4.1f%%]",pct);
      std::cout << " " << buf << std::flush;
    } else if( iEvent == nEntries-1 ) {
      std::cout << "\r" << title << ": |";
      for(int idot=0; idot<nDots; idot++)
        std::cout << "#";
      std::cout << "| [100.0%]" << std::flush;
    }
  }
};

#endif