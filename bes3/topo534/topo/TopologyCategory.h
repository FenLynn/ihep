/* @(#)TopologyCategory.h
 */

#ifndef _TOPOLOGYCATEGORY_H
#define _TOPOLOGYCATEGORY_H 1

#include "ParticleObject.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iomanip> //for setw
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <TROOT.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

typedef std::vector<int> Vint;
typedef std::vector<std::string> Vstr;

class TopologyCategory 
{
public:
  TopologyCategory(std::vector<std::string>);
  ~TopologyCategory();

  void getSignalTopo(std::vector<std::string>);
  void getSignalTopo(int);
  void openRootFile();
  void TopoRead();
  void TopoWrite();
  void TopoLog();

  void BubbleSort(std::vector<int> &, std::vector<int> &);
  std::string TopoString(std::vector<int>, std::vector<int>);

private:

  std::vector<std::string> VsignalTopoStr;

  std::string treeName;
  Vstr m_inputFileName;
  //std::string  m_inputFileName;

  std::ofstream m_outputFile;
  std::string m_outputFileName;

  TChain *chain;
  // Declaration of leave types
  Int_t           indexmc;
  Int_t           pdgid[100];   //[indexmc]
  Int_t           motheridx[100];   //[indexmc]

  // List of branches
  TBranch        *b_indexmc;   //!
  TBranch        *b_pdgid;   //!
  TBranch        *b_motheridx;   //!

  ParticleObject aParticleObject;
  // counter the number of topology category 
  // and the number of events in this topology
  Vint Vtopo; 
  Vint topoIdx;
  Vstr VtopoStr;
  int InclusiveParticleID;
  // counter the number of particles in this topology
  Vint VtopoNpar;

  struct comTopoPIDIdx
  {
    int Topo;
    int PID;
    int Idx;
  };
  comTopoPIDIdx acomTPI;
  std::vector<comTopoPIDIdx> VcomTPI;
};

#endif /* _TOPOLOGYCATEGORY_H */

