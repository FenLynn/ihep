//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 16 14:10:28 2015 by ROOT version 5.34/01
// from TChain save/
//////////////////////////////////////////////////////////

#ifndef df_h
#define df_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class df {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           indexmc;
   Int_t           pdgid[2613];   //[indexmc]
   Int_t           drank[2613];   //[indexmc]
   Int_t           motheridx[2613];   //[indexmc]
   Int_t           motherpid[2613];   //[indexmc]
   Int_t           runid;
   Int_t           evtid;
   Int_t           nevt;
   Int_t           nNEUTRAL;
   Int_t           nCHARGED;
   Int_t           nTRACKS;
   Int_t           nGamma;
   Double_t        vx[3];
   Double_t        Evx[3];
   Double_t        costheta_chrgd[2];
   Double_t        Rxy[2];
   Double_t        Rz[2];
   Double_t        Rvxy[2];
   Double_t        Rvz[2];
   Double_t        mmiss2;
   Double_t        umiss;
   Double_t        mmiss;
   Double_t        pmiss;
   Double_t        emiss;
   Double_t        ptr;
   Double_t        ptr2;
   Double_t        ptg2;
   Double_t        costhe_ee;
   Double_t        costhe_u;
   Double_t        sinthe_ee;
   Double_t        ee_ivm;
   Double_t        chiDeDx[2][5];
   Double_t        chiTof[2][5];
   Double_t        chiTof1[2][5];
   Double_t        chiTof2[2][5];
   Double_t        chisq_pid[2][5];
   Double_t        prob[2][5];
   Double_t        vtxchisq;
   Int_t           stat1C;
   Double_t        chi1C;
   Double_t        pTrk[2];
   Double_t        deTrk[2];
   Double_t        epTrk[2];
   Int_t           hitsTrk[2];
   Double_t        tof[2];
   Double_t        dtof;
   TClonesArray    *p_all;
   TClonesArray    *p_e1;
   TClonesArray    *p_e2;
   TClonesArray    *p_u;
   TLorentzVector  *xp;
   TLorentzVector  *xm;
   Int_t           numep;
   Int_t           numem;
   Int_t           isSigee;
   Int_t           numgam;
   TClonesArray    *mcgam;

   // List of branches
   TBranch        *b_indexmc;   //!
   TBranch        *b_pdgid;   //!
   TBranch        *b_drank;   //!
   TBranch        *b_motheridx;   //!
   TBranch        *b_motherpid;   //!
   TBranch        *b_runid;   //!
   TBranch        *b_evtid;   //!
   TBranch        *b_nevt;   //!
   TBranch        *b_nNEUTRAL;   //!
   TBranch        *b_nCHARGED;   //!
   TBranch        *b_nTRACKS;   //!
   TBranch        *b_nGamma;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_Evx;   //!
   TBranch        *b_costheta_chrgd;   //!
   TBranch        *b_Rxy;   //!
   TBranch        *b_Rz;   //!
   TBranch        *b_Rvxy;   //!
   TBranch        *b_Rvz;   //!
   TBranch        *b_mmiss2;   //!
   TBranch        *b_umiss;   //!
   TBranch        *b_mmiss;   //!
   TBranch        *b_pmiss;   //!
   TBranch        *b_emiss;   //!
   TBranch        *b_ptr;   //!
   TBranch        *b_ptr2;   //!
   TBranch        *b_ptg2;   //!
   TBranch        *b_costhe_ee;   //!
   TBranch        *b_costhe_u;   //!
   TBranch        *b_sinthe_ee;   //!
   TBranch        *b_ee_ivm;   //!
   TBranch        *b_chiDeDx;   //!
   TBranch        *b_chiTof;   //!
   TBranch        *b_chiTof1;   //!
   TBranch        *b_chiTof2;   //!
   TBranch        *b_chisq_pid;   //!
   TBranch        *b_prob;   //!
   TBranch        *b_vtxchisq;   //!
   TBranch        *b_stat1C;   //!
   TBranch        *b_chi1C;   //!
   TBranch        *b_pTrk;   //!
   TBranch        *b_deTrk;   //!
   TBranch        *b_epTrk;   //!
   TBranch        *b_hitsTrk;   //!
   TBranch        *b_tof;   //!
   TBranch        *b_dtof;   //!
   TBranch        *b_p_all;   //!
   TBranch        *b_p_e1;   //!
   TBranch        *b_p_e2;   //!
   TBranch        *b_p_u;   //!
   TBranch        *b_xp;   //!
   TBranch        *b_xm;   //!
   TBranch        *b_numep;   //!
   TBranch        *b_numem;   //!
   TBranch        *b_isSigee;   //!
   TBranch        *b_numgam;   //!
   TBranch        *b_mcgam;   //!

   df(TTree *tree=0);
   virtual ~df();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef df_cxx
df::df(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("save",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("save","");
      chain->Add("INPUT/save");
	  tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

df::~df()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t df::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t df::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void df::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   p_all = 0;
   p_e1 = 0;
   p_e2 = 0;
   p_u = 0;
   xp = 0;
   xm = 0;
   mcgam = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("indexmc", &indexmc, &b_indexmc);
   fChain->SetBranchAddress("pdgid", pdgid, &b_pdgid);
   fChain->SetBranchAddress("drank", drank, &b_drank);
   fChain->SetBranchAddress("motheridx", motheridx, &b_motheridx);
   fChain->SetBranchAddress("motherpid", motherpid, &b_motherpid);
   fChain->SetBranchAddress("runid", &runid, &b_runid);
   fChain->SetBranchAddress("evtid", &evtid, &b_evtid);
   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
   fChain->SetBranchAddress("nNEUTRAL", &nNEUTRAL, &b_nNEUTRAL);
   fChain->SetBranchAddress("nCHARGED", &nCHARGED, &b_nCHARGED);
   fChain->SetBranchAddress("nTRACKS", &nTRACKS, &b_nTRACKS);
   fChain->SetBranchAddress("nGamma", &nGamma, &b_nGamma);
   fChain->SetBranchAddress("vx", vx, &b_vx);
   fChain->SetBranchAddress("Evx", Evx, &b_Evx);
   fChain->SetBranchAddress("costheta_chrgd", costheta_chrgd, &b_costheta_chrgd);
   fChain->SetBranchAddress("Rxy", Rxy, &b_Rxy);
   fChain->SetBranchAddress("Rz", Rz, &b_Rz);
   fChain->SetBranchAddress("Rvxy", Rvxy, &b_Rvxy);
   fChain->SetBranchAddress("Rvz", Rvz, &b_Rvz);
   fChain->SetBranchAddress("mmiss2", &mmiss2, &b_mmiss2);
   fChain->SetBranchAddress("umiss", &umiss, &b_umiss);
   fChain->SetBranchAddress("mmiss", &mmiss, &b_mmiss);
   fChain->SetBranchAddress("pmiss", &pmiss, &b_pmiss);
   fChain->SetBranchAddress("emiss", &emiss, &b_emiss);
   fChain->SetBranchAddress("ptr", &ptr, &b_ptr);
   fChain->SetBranchAddress("ptr2", &ptr2, &b_ptr2);
   fChain->SetBranchAddress("ptg2", &ptg2, &b_ptg2);
   fChain->SetBranchAddress("costhe_ee", &costhe_ee, &b_costhe_ee);
   fChain->SetBranchAddress("costhe_u", &costhe_u, &b_costhe_u);
   fChain->SetBranchAddress("sinthe_ee", &sinthe_ee, &b_sinthe_ee);
   fChain->SetBranchAddress("ee_ivm", &ee_ivm, &b_ee_ivm);
   fChain->SetBranchAddress("chiDeDx", chiDeDx, &b_chiDeDx);
   fChain->SetBranchAddress("chiTof", chiTof, &b_chiTof);
   fChain->SetBranchAddress("chiTof1", chiTof1, &b_chiTof1);
   fChain->SetBranchAddress("chiTof2", chiTof2, &b_chiTof2);
   fChain->SetBranchAddress("chisq_pid", chisq_pid, &b_chisq_pid);
   fChain->SetBranchAddress("prob", prob, &b_prob);
   fChain->SetBranchAddress("vtxchisq", &vtxchisq, &b_vtxchisq);
   fChain->SetBranchAddress("stat1C", &stat1C, &b_stat1C);
   fChain->SetBranchAddress("chi1C", &chi1C, &b_chi1C);
   fChain->SetBranchAddress("pTrk", pTrk, &b_pTrk);
   fChain->SetBranchAddress("deTrk", deTrk, &b_deTrk);
   fChain->SetBranchAddress("epTrk", epTrk, &b_epTrk);
   fChain->SetBranchAddress("hitsTrk", hitsTrk, &b_hitsTrk);
   fChain->SetBranchAddress("tof", tof, &b_tof);
   fChain->SetBranchAddress("dtof", &dtof, &b_dtof);
   fChain->SetBranchAddress("p_all", &p_all, &b_p_all);
   fChain->SetBranchAddress("p_e1", &p_e1, &b_p_e1);
   fChain->SetBranchAddress("p_e2", &p_e2, &b_p_e2);
   fChain->SetBranchAddress("p_u", &p_u, &b_p_u);
   fChain->SetBranchAddress("xp", &xp, &b_xp);
   fChain->SetBranchAddress("xm", &xm, &b_xm);
   fChain->SetBranchAddress("numep", &numep, &b_numep);
   fChain->SetBranchAddress("numem", &numem, &b_numem);
   fChain->SetBranchAddress("isSigee", &isSigee, &b_isSigee);
   fChain->SetBranchAddress("numgam", &numgam, &b_numgam);
   fChain->SetBranchAddress("mcgam", &mcgam, &b_mcgam);
   Notify();
}

Bool_t df::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void df::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t df::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef df_cxx
