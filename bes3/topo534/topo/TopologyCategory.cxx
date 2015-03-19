#include "TopologyCategory.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopologyCategory::BubbleSort(std::vector<int> &pid,
                                  std::vector<int> &midx)
{
  if ( (int) pid.size() != (int) midx.size() )
  {
    std::cout << "the two vector have different length!" << std::endl;
    std::cout << "the size of pid is " << (int) pid.size() << std::endl;
    std::cout << "the size of midx is " << (int) midx.size() << std::endl;
    std::cout << "Please check your code!" << std::endl; 
    exit(1);
  }

  unsigned int vsize = midx.size();

  // sort max->min 
  int pidtemp;
  int idxtemp;
  for ( unsigned int i=0; i<vsize-1; i++ )
  {
    for ( unsigned int j=i+1; j<vsize; j++ )
    {
      if ( midx[i] < midx[j] )
      {
        pidtemp = pid[i]; idxtemp = midx[i];
        pid[i] = pid[j];  midx[i] = midx[j];
        pid[j] = pidtemp; midx[j] = idxtemp;
      }
    } // for j
  } // for i

}
std::string TopologyCategory::TopoString(std::vector<int> pid, 
                                         std::vector<int> midx)
{
  Vint TopoChain;
  TopoChain.clear();
  Vint iChain;
  iChain.clear();
  Vint vorder1;
  vorder1.clear();
  Vint vorder2;
  vorder2.clear();
  //int NewOrder = -1;
  unsigned int vsize = midx.size();
  begin:
  for ( unsigned int i=0; i<vsize; i++ )
  {
    if (vorder1.empty())
    {
      vorder1.push_back(i);
      TopoChain.push_back(pid[i]);
      continue;
    }
    for (unsigned int j=0; j<vorder1.size(); j++)
    {
      if (midx[i] == vorder1[j]) 
      {
        vorder2.push_back(i);
        iChain.push_back(pid[i]);
	//std::cout << pid[i] << std::endl;
      }
    }
  }
  if (!vorder2.empty())
  {
    std::sort(iChain.begin(), iChain.end());
    for (unsigned int k=0; k<iChain.size(); k++)
    {
      TopoChain.push_back(iChain[k]);
    }
    vorder1.clear();
    vorder1 = vorder2;
    vorder2.clear();
    iChain.clear();
    goto begin;
  }

  std::string tempLine = "";
  //convert int to string
  for (unsigned int i=0; i<TopoChain.size(); i++)
  {
    stringstream s;
    s << TopoChain[i];
    tempLine += s.str();
    tempLine += " ";
  }
  //std::cout << tempLine << std::endl;

  return tempLine;
}


TopologyCategory::TopologyCategory(Vstr avstr)
{

  treeName = avstr[0];
  m_inputFileName.clear();
  for (unsigned int i = 1; i < avstr.size(); i++) 
  {
    m_inputFileName.push_back(avstr[i]);
  }

  Vtopo.clear();
  topoIdx.clear();
  VtopoNpar.clear();
  VtopoStr.clear();
  VcomTPI.clear();
  VsignalTopoStr.clear();
  InclusiveParticleID = 0;
}

TopologyCategory::~TopologyCategory()
{
  delete chain;
}

void TopologyCategory::getSignalTopo(Vstr avstr)
{
  VsignalTopoStr = avstr;
}

void TopologyCategory::getSignalTopo(int pid)
{
  InclusiveParticleID = pid;
}

void TopologyCategory::openRootFile()
{

  chain = new TChain(treeName.c_str());
  for (unsigned int i = 0; i < m_inputFileName.size(); i++)
  {
    chain->Add(m_inputFileName[i].c_str());
  }

  chain->SetBranchAddress("indexmc", &indexmc, &b_indexmc);
  chain->SetBranchAddress("pdgid", pdgid, &b_pdgid);
  chain->SetBranchAddress("motheridx", motheridx, &b_motheridx);
}

void TopologyCategory::TopoRead()
{

  //Create a new tree
  //write the clone of old tree and the new tree into one new file
  TFile *newfile = new TFile("topo.root","recreate");
  TTree *newtree = chain->CloneTree(0);
  TTree *newtree2 = new TTree("topo", "new tree");

  Int_t n_signal;
  Int_t n_itopo;
  newtree2->Branch("signal", &n_signal,  "n_signal/I");
  newtree2->Branch("itopo",  &n_itopo,   "n_itopo/I");

  int totalEvent = 0;
  int totalTopo = 0;
  Long64_t nevent = chain->GetEntries();
  for (Long64_t i=0; i<nevent; i++ ) 
  {
    chain->GetEntry(i);

    totalEvent++;
    n_signal = 0;
    Vint parid;
    Vint midx;
    parid.clear();
    midx.clear();
    for (int j=0; j<indexmc; j++)
    {
      midx.push_back(motheridx[j]);
      parid.push_back(pdgid[j]);
      if (pdgid[j] == InclusiveParticleID) { n_signal = 1; }
    }
    std::string tempLine = TopoString(parid, midx);
    //std::cout << tempLine << std::endl;

    if (!VsignalTopoStr.empty())//exclusive signal
    {
      for (unsigned int k=0; k < VsignalTopoStr.size(); k++)
      {
        //std::cout << VsignalTopoStr[k] << std::endl;
        if (tempLine == VsignalTopoStr[k]) { n_signal = 1; break; }
      }
    }
    Bool_t newType = true;
    if (totalTopo != 0)
    {
      int xtopo = 0;
      for (unsigned int istr = 0; istr < VtopoStr.size(); istr++)
      {
        if (tempLine == VtopoStr[istr]) 
        {
          newType = false;
          n_itopo = xtopo;
          Vtopo[xtopo]++;
          break; 
        }
        xtopo++;
      }// end of while      
    }// if the first topology type

    if (newType)
    {
      Vtopo.push_back(1);
      VtopoNpar.push_back(indexmc);
      VtopoStr.push_back(tempLine);
      n_itopo = totalTopo;
      for (int k=0; k<indexmc; k++)
      {
        acomTPI.Topo = totalTopo;
        acomTPI.PID = pdgid[k];
        acomTPI.Idx = motheridx[k];
        VcomTPI.push_back(acomTPI);
      }//end loop particle in one new type
      totalTopo++;
    }//end of new type
    newtree->Fill();
    newtree2->Fill();
  }// loop for all entries

  newtree->Write();
  newtree2->Write();
  newfile->Close();
}

void TopologyCategory::TopoLog()
{
  std::ofstream m_outputFile;
  m_outputFile.open("log.txt", ios_base::out);

  Vint Vtopoback = Vtopo;
  int totalTopo = Vtopo.size();
  for (int i = 0; i < totalTopo; i++)
  {
    topoIdx.push_back(i);
  }
  BubbleSort(topoIdx, Vtopo);
  BubbleSort(VtopoNpar, Vtopoback);

  std::cout << "the total topology number is: " << totalTopo << std::endl;
  m_outputFile << "the topology category statisticcal information" 
               << std::endl;
  m_outputFile << "the total topology number is: " << totalTopo << std::endl;
  m_outputFile << "type      " << "Event Number" << std::endl;
  for (int i=0; i<totalTopo; i++)
  {
    m_outputFile.flags(ios::left | ios::fixed);
    m_outputFile << setw(10) << topoIdx[i] 
                 << setw(10) << Vtopo[i] << std::endl;
  }
  m_outputFile.close();

}

void TopologyCategory::TopoWrite()
{

  //open the file to write
  ofstream m_outputFile;
  if (m_outputFileName.empty()) { m_outputFileName = "mclist.txt"; }
  m_outputFile.open(m_outputFileName.c_str(), ios_base::out); 
  if (!m_outputFile)
  {
    std::cout << "can't open the file: mclist.txt " << std::endl;
    exit(-1);
  }

  int totalTopo = Vtopo.size();

  m_outputFile << "the topology category statisticcal information" 
               << std::endl;
  m_outputFile << "the total topology number is: " << totalTopo << std::endl;

  for (int i=0; i<totalTopo; i++)
  {
    m_outputFile.flags(ios::left | ios::fixed);
    m_outputFile << "\ntopology: " << setw(10) << topoIdx[i]
                 << " Events: "    << setw(10) << Vtopo[i] 
                 << std::endl << std::endl;
    m_outputFile.flags(ios::right | ios::fixed);
    m_outputFile << std::setw(30) <<"Event listing (summary)" << endl;
    m_outputFile.flags(ios::left | ios::fixed);
    m_outputFile << std::setw(10) << "I";
    m_outputFile << std::setw(15) << "particle/jet";
    m_outputFile.flags(ios::right | ios::fixed);
    m_outputFile << std::setw(8) << "KF";
    m_outputFile << std::setw(8) << "orig" << endl;
    //m_outputFile << endl << endl;

    int index = 0;
    for (unsigned int j=0; j<VcomTPI.size(); j++)
    {
      if (index == VtopoNpar[i]) break;
      if (topoIdx[i] == VcomTPI[j].Topo)
      {
        std::string mcname = aParticleObject.GetParName(VcomTPI[j].PID);
        m_outputFile.flags(ios::left | ios::fixed);
        m_outputFile << setw(10) << index; 
        m_outputFile << setw(15) << mcname;
        m_outputFile.flags(ios::right | ios::fixed);
        m_outputFile << setw(8) << setprecision(0) << VcomTPI[j].PID;
        m_outputFile << setw(8) << setprecision(0) << VcomTPI[j].Idx;
        m_outputFile.flags(ios::right | ios::showpoint | ios::fixed);
        m_outputFile << endl;
        index++;
      }
    }
  }
  m_outputFile.close();
}



