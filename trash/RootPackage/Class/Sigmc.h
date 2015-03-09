//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 25 11:41:31 2014 by ROOT version 5.34/07
// from TChain save/
//////////////////////////////////////////////////////////

#ifndef Sigmc_h
#define Sigmc_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Sigmc {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runid;
   Int_t           evtid;
   Int_t           nevt;
   Int_t           nNEUTRAL;
   Int_t           nCHARGED;
   Int_t           nTRACKS;
   Int_t           nGamma;
   Double_t        vx0;
   Double_t        vy0;
   Double_t        vz0;
   Double_t        vr0;
   Double_t        rvxy0;
   Double_t        rvz0;
   Double_t        rvphi0;
   Double_t        rtheta0;
   Double_t        rtheta1;
   Double_t        ppos;
   Double_t        epos;
   Double_t        depos;
   Double_t        EPRatioPlus;
   Double_t        hitspos;
   Double_t        pneg;
   Double_t        eneg;
   Double_t        deneg;
   Double_t        EPRatioMinu;
   Double_t        hitsneg;
   Double_t        TMass;
   Double_t        chi4C;
   Double_t        mmu0;
   Double_t        chi5C;
   Double_t        mmu1;
   Double_t        chiDeDx[4][5];
   Double_t        chiTof1[4][5];
   Double_t        chiTof2[4][5];
   Double_t        chisq_pid[4][5];
   Double_t        prob[4][5];
   Int_t           posmucstat;
   Int_t           negmucstat;
   Double_t        posdepthMuc;
   Double_t        poslayerMuc;
   Double_t        posangMuc;
   Double_t        negdepthMuc;
   Double_t        neglayerMuc;
   Double_t        negangMuc;
   Double_t        poskalrechi2;
   Int_t           poskaldof;
   Double_t        poskaldepth;
   Int_t           poskalbrLastLayer;
   Int_t           poskalecLastLayer;
   Double_t        negkalrechi2;
   Int_t           negkaldof;
   Double_t        negkaldepth;
   Int_t           negkalbrLastLayer;
   Int_t           negkalecLastLayer;

   // List of branches
   TBranch        *b_runid;   //!
   TBranch        *b_evtid;   //!
   TBranch        *b_nevt;   //!
   TBranch        *b_nNEUTRAL;   //!
   TBranch        *b_nCHARGED;   //!
   TBranch        *b_nTRACKS;   //!
   TBranch        *b_nGamma;   //!
   TBranch        *b_vx0;   //!
   TBranch        *b_vy0;   //!
   TBranch        *b_vz0;   //!
   TBranch        *b_vr0;   //!
   TBranch        *b_rvxy0;   //!
   TBranch        *b_rvz0;   //!
   TBranch        *b_rvphi0;   //!
   TBranch        *b_rtheta0;   //!
   TBranch        *b_rtheta1;   //!
   TBranch        *b_ppos;   //!
   TBranch        *b_epos;   //!
   TBranch        *b_depos;   //!
   TBranch        *b_EPRatioPlus;   //!
   TBranch        *b_hitspos;   //!
   TBranch        *b_pneg;   //!
   TBranch        *b_eneg;   //!
   TBranch        *b_deneg;   //!
   TBranch        *b_EPRatioMinu;   //!
   TBranch        *b_hitsneg;   //!
   TBranch        *b_TMass;   //!
   TBranch        *b_chi4C;   //!
   TBranch        *b_mmu0;   //!
   TBranch        *b_chi5C;   //!
   TBranch        *b_mmu1;   //!
   TBranch        *b_chiDeDx;   //!
   TBranch        *b_chiTof1;   //!
   TBranch        *b_chiTof2;   //!
   TBranch        *b_chisq_pid;   //!
   TBranch        *b_prob;   //!
   TBranch        *b_posmucstat;   //!
   TBranch        *b_negmucstat;   //!
   TBranch        *b_posdepthMuc;   //!
   TBranch        *b_poslayerMuc;   //!
   TBranch        *b_posangMuc;   //!
   TBranch        *b_negdepthMuc;   //!
   TBranch        *b_neglayerMuc;   //!
   TBranch        *b_negangMuc;   //!
   TBranch        *b_poskalrechi2;   //!
   TBranch        *b_poskaldof;   //!
   TBranch        *b_poskaldepth;   //!
   TBranch        *b_poskalbrLastLayer;   //!
   TBranch        *b_poskalecLastLayer;   //!
   TBranch        *b_negkalrechi2;   //!
   TBranch        *b_negkaldof;   //!
   TBranch        *b_negkaldepth;   //!
   TBranch        *b_negkalbrLastLayer;   //!
   TBranch        *b_negkalecLastLayer;   //!

   Sigmc(TTree *tree=0);
   virtual ~Sigmc();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Sigmc_cxx
Sigmc::Sigmc(TTree *tree) : fChain(0) 
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
      chain->Add("/home/lify/workarea/root/mycheck/test/test.root/save");
      chain->Add("/home/lify/workarea/root/mycheck/test/test1.root/save");
      chain->Add("/home/lify/workarea/root/mycheck/test/test2.root/save");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Sigmc::~Sigmc()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Sigmc::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Sigmc::LoadTree(Long64_t entry)
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

void Sigmc::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runid", &runid, &b_runid);
   fChain->SetBranchAddress("evtid", &evtid, &b_evtid);
   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
   fChain->SetBranchAddress("nNEUTRAL", &nNEUTRAL, &b_nNEUTRAL);
   fChain->SetBranchAddress("nCHARGED", &nCHARGED, &b_nCHARGED);
   fChain->SetBranchAddress("nTRACKS", &nTRACKS, &b_nTRACKS);
   fChain->SetBranchAddress("nGamma", &nGamma, &b_nGamma);
   fChain->SetBranchAddress("vx0", &vx0, &b_vx0);
   fChain->SetBranchAddress("vy0", &vy0, &b_vy0);
   fChain->SetBranchAddress("vz0", &vz0, &b_vz0);
   fChain->SetBranchAddress("vr0", &vr0, &b_vr0);
   fChain->SetBranchAddress("rvxy0", &rvxy0, &b_rvxy0);
   fChain->SetBranchAddress("rvz0", &rvz0, &b_rvz0);
   fChain->SetBranchAddress("rvphi0", &rvphi0, &b_rvphi0);
   fChain->SetBranchAddress("rtheta0", &rtheta0, &b_rtheta0);
   fChain->SetBranchAddress("rtheta1", &rtheta1, &b_rtheta1);
   fChain->SetBranchAddress("ppos", &ppos, &b_ppos);
   fChain->SetBranchAddress("epos", &epos, &b_epos);
   fChain->SetBranchAddress("depos", &depos, &b_depos);
   fChain->SetBranchAddress("EPRatioPlus", &EPRatioPlus, &b_EPRatioPlus);
   fChain->SetBranchAddress("hitspos", &hitspos, &b_hitspos);
   fChain->SetBranchAddress("pneg", &pneg, &b_pneg);
   fChain->SetBranchAddress("eneg", &eneg, &b_eneg);
   fChain->SetBranchAddress("deneg", &deneg, &b_deneg);
   fChain->SetBranchAddress("EPRatioMinu", &EPRatioMinu, &b_EPRatioMinu);
   fChain->SetBranchAddress("hitsneg", &hitsneg, &b_hitsneg);
   fChain->SetBranchAddress("TMass", &TMass, &b_TMass);
   fChain->SetBranchAddress("chi4C", &chi4C, &b_chi4C);
   fChain->SetBranchAddress("mmu0", &mmu0, &b_mmu0);
   fChain->SetBranchAddress("chi5C", &chi5C, &b_chi5C);
   fChain->SetBranchAddress("mmu1", &mmu1, &b_mmu1);
   fChain->SetBranchAddress("chiDeDx", chiDeDx, &b_chiDeDx);
   fChain->SetBranchAddress("chiTof1", chiTof1, &b_chiTof1);
   fChain->SetBranchAddress("chiTof2", chiTof2, &b_chiTof2);
   fChain->SetBranchAddress("chisq_pid", chisq_pid, &b_chisq_pid);
   fChain->SetBranchAddress("prob", prob, &b_prob);
   fChain->SetBranchAddress("posmucstat", &posmucstat, &b_posmucstat);
   fChain->SetBranchAddress("negmucstat", &negmucstat, &b_negmucstat);
   fChain->SetBranchAddress("posdepthMuc", &posdepthMuc, &b_posdepthMuc);
   fChain->SetBranchAddress("poslayerMuc", &poslayerMuc, &b_poslayerMuc);
   fChain->SetBranchAddress("posangMuc", &posangMuc, &b_posangMuc);
   fChain->SetBranchAddress("negdepthMuc", &negdepthMuc, &b_negdepthMuc);
   fChain->SetBranchAddress("neglayerMuc", &neglayerMuc, &b_neglayerMuc);
   fChain->SetBranchAddress("negangMuc", &negangMuc, &b_negangMuc);
   fChain->SetBranchAddress("poskalrechi2", &poskalrechi2, &b_poskalrechi2);
   fChain->SetBranchAddress("poskaldof", &poskaldof, &b_poskaldof);
   fChain->SetBranchAddress("poskaldepth", &poskaldepth, &b_poskaldepth);
   fChain->SetBranchAddress("poskalbrLastLayer", &poskalbrLastLayer, &b_poskalbrLastLayer);
   fChain->SetBranchAddress("poskalecLastLayer", &poskalecLastLayer, &b_poskalecLastLayer);
   fChain->SetBranchAddress("negkalrechi2", &negkalrechi2, &b_negkalrechi2);
   fChain->SetBranchAddress("negkaldof", &negkaldof, &b_negkaldof);
   fChain->SetBranchAddress("negkaldepth", &negkaldepth, &b_negkaldepth);
   fChain->SetBranchAddress("negkalbrLastLayer", &negkalbrLastLayer, &b_negkalbrLastLayer);
   fChain->SetBranchAddress("negkalecLastLayer", &negkalecLastLayer, &b_negkalecLastLayer);
   Notify();
}

Bool_t Sigmc::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Sigmc::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Sigmc::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
	//***************This is a selection for unti-parmeter_1<5******************
	//if (parmeter_1<5)  {return -1;}
	//***************This is a selection for unti-parmeter_2>2******************
	//if (parmeter_2>2)  {return -1;}
	return 1;
}
/*
//This is an external function belonging to your class Sigmc/Inmc/Data
void Sigmc::FUNC(Int_t par)
{
	if (!fChain) return;
	//you can add anything here to extract the class
}
*/
//do not delete this line
//do not delete this line
#endif // #ifdef Sigmc_cxx
