//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 26 00:07:33 2014 by ROOT version 5.34/07
// from TChain save/
//////////////////////////////////////////////////////////

#ifndef Data_h
#define Data_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Data {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           indexmc;
   Int_t           pdgid[1];   //[indexmc]
   Int_t           drank[1];   //[indexmc]
   Int_t           motheridx[1];   //[indexmc]
   Int_t           motherpid[1];   //[indexmc]
   Double_t        ppos;
   Double_t        epos;
   Double_t        depos;
   Double_t        epp;
   Int_t           hitspos;
   Double_t        pneg;
   Double_t        eneg;
   Double_t        deneg;
   Double_t        epn;
   Int_t           hitsneg;
   Double_t        tmass;
   Int_t           posmucstat;
   Int_t           negmucstat;
   Double_t        posdepthMuc;
   Double_t        negdepthMuc;
   Int_t           poslayerMuc;
   Int_t           neglayerMuc;
   Double_t        posangMuc;
   Double_t        negangMuc;
   Double_t        poskalrechi2;
   Double_t        negkalrechi2;
   Int_t           poskalecLastLayer;
   Int_t           negkalecLastLayer;
   Int_t           poskalbrLastLayer;
   Int_t           negkalbrLastLayer;
   Double_t        poskaldepth;
   Double_t        negkaldepth;
   Int_t           poskaldof;
   Int_t           negkaldof;
   Double_t        chisq_pi0;
   Double_t        chisq_4c;
   Int_t           len;
   Double_t        lvtrpi0[4];   //[len]
   Double_t        lvtrpip[4];   //[len]
   Double_t        lvtrpim[4];   //[len]
   Double_t        lvtrpi0unfit[4];   //[len]
   Double_t        lvtrpipunfit[4];   //[len]
   Double_t        lvtrpimunfit[4];   //[len]

   // List of branches
   TBranch        *b_indexmc;   //!
   TBranch        *b_pdgid;   //!
   TBranch        *b_drank;   //!
   TBranch        *b_motheridx;   //!
   TBranch        *b_motherpid;   //!
   TBranch        *b_ppos;   //!
   TBranch        *b_epos;   //!
   TBranch        *b_depos;   //!
   TBranch        *b_epp;   //!
   TBranch        *b_hitspos;   //!
   TBranch        *b_pneg;   //!
   TBranch        *b_eneg;   //!
   TBranch        *b_deneg;   //!
   TBranch        *b_epn;   //!
   TBranch        *b_hitsneg;   //!
   TBranch        *b_tmass;   //!
   TBranch        *b_posmucstat;   //!
   TBranch        *b_negmucstat;   //!
   TBranch        *b_posdepthMuc;   //!
   TBranch        *b_negdepthMuc;   //!
   TBranch        *b_poslayerMuc;   //!
   TBranch        *b_neglayerMuc;   //!
   TBranch        *b_posangMuc;   //!
   TBranch        *b_negangMuc;   //!
   TBranch        *b_poskalrechi2;   //!
   TBranch        *b_negkalrechi2;   //!
   TBranch        *b_poskalecLastLayer;   //!
   TBranch        *b_negkalecLastLayer;   //!
   TBranch        *b_poskalbrLastLayer;   //!
   TBranch        *b_negkalbrLastLayer;   //!
   TBranch        *b_poskaldepth;   //!
   TBranch        *b_negkaldepth;   //!
   TBranch        *b_poskaldof;   //!
   TBranch        *b_negkaldof;   //!
   TBranch        *b_chisq_pi0;   //!
   TBranch        *b_chisq_4c;   //!
   TBranch        *b_len;   //!
   TBranch        *b_lvtrpi0;   //!
   TBranch        *b_lvtrpip;   //!
   TBranch        *b_lvtrpim;   //!
   TBranch        *b_lvtrpi0unfit;   //!
   TBranch        *b_lvtrpipunfit;   //!
   TBranch        *b_lvtrpimunfit;   //!

   Data(TTree *tree=0);
   virtual ~Data();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Data_cxx
Data::Data(TTree *tree) : fChain(0) 
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
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi001.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi002.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi003.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi004.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi005.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi006.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi007.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi008.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi009.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi010.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi011.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi012.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi013.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi014.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi015.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi016.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi017.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi018.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi019.root/save");
      chain->Add("/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi020.root/save");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Data::~Data()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Data::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Data::LoadTree(Long64_t entry)
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

void Data::Init(TTree *tree)
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

   fChain->SetBranchAddress("indexmc", &indexmc, &b_indexmc);
   fChain->SetBranchAddress("pdgid", &pdgid, &b_pdgid);
   fChain->SetBranchAddress("drank", &drank, &b_drank);
   fChain->SetBranchAddress("motheridx", &motheridx, &b_motheridx);
   fChain->SetBranchAddress("motherpid", &motherpid, &b_motherpid);
   fChain->SetBranchAddress("ppos", &ppos, &b_ppos);
   fChain->SetBranchAddress("epos", &epos, &b_epos);
   fChain->SetBranchAddress("depos", &depos, &b_depos);
   fChain->SetBranchAddress("epp", &epp, &b_epp);
   fChain->SetBranchAddress("hitspos", &hitspos, &b_hitspos);
   fChain->SetBranchAddress("pneg", &pneg, &b_pneg);
   fChain->SetBranchAddress("eneg", &eneg, &b_eneg);
   fChain->SetBranchAddress("deneg", &deneg, &b_deneg);
   fChain->SetBranchAddress("epn", &epn, &b_epn);
   fChain->SetBranchAddress("hitsneg", &hitsneg, &b_hitsneg);
   fChain->SetBranchAddress("tmass", &tmass, &b_tmass);
   fChain->SetBranchAddress("posmucstat", &posmucstat, &b_posmucstat);
   fChain->SetBranchAddress("negmucstat", &negmucstat, &b_negmucstat);
   fChain->SetBranchAddress("posdepthMuc", &posdepthMuc, &b_posdepthMuc);
   fChain->SetBranchAddress("negdepthMuc", &negdepthMuc, &b_negdepthMuc);
   fChain->SetBranchAddress("poslayerMuc", &poslayerMuc, &b_poslayerMuc);
   fChain->SetBranchAddress("neglayerMuc", &neglayerMuc, &b_neglayerMuc);
   fChain->SetBranchAddress("posangMuc", &posangMuc, &b_posangMuc);
   fChain->SetBranchAddress("negangMuc", &negangMuc, &b_negangMuc);
   fChain->SetBranchAddress("poskalrechi2", &poskalrechi2, &b_poskalrechi2);
   fChain->SetBranchAddress("negkalrechi2", &negkalrechi2, &b_negkalrechi2);
   fChain->SetBranchAddress("poskalecLastLayer", &poskalecLastLayer, &b_poskalecLastLayer);
   fChain->SetBranchAddress("negkalecLastLayer", &negkalecLastLayer, &b_negkalecLastLayer);
   fChain->SetBranchAddress("poskalbrLastLayer", &poskalbrLastLayer, &b_poskalbrLastLayer);
   fChain->SetBranchAddress("negkalbrLastLayer", &negkalbrLastLayer, &b_negkalbrLastLayer);
   fChain->SetBranchAddress("poskaldepth", &poskaldepth, &b_poskaldepth);
   fChain->SetBranchAddress("negkaldepth", &negkaldepth, &b_negkaldepth);
   fChain->SetBranchAddress("poskaldof", &poskaldof, &b_poskaldof);
   fChain->SetBranchAddress("negkaldof", &negkaldof, &b_negkaldof);
   fChain->SetBranchAddress("chisq_pi0", &chisq_pi0, &b_chisq_pi0);
   fChain->SetBranchAddress("chisq_4c", &chisq_4c, &b_chisq_4c);
   fChain->SetBranchAddress("len", &len, &b_len);
   fChain->SetBranchAddress("lvtrpi0", lvtrpi0, &b_lvtrpi0);
   fChain->SetBranchAddress("lvtrpip", lvtrpip, &b_lvtrpip);
   fChain->SetBranchAddress("lvtrpim", lvtrpim, &b_lvtrpim);
   fChain->SetBranchAddress("lvtrpi0unfit", lvtrpi0unfit, &b_lvtrpi0unfit);
   fChain->SetBranchAddress("lvtrpipunfit", lvtrpipunfit, &b_lvtrpipunfit);
   fChain->SetBranchAddress("lvtrpimunfit", lvtrpimunfit, &b_lvtrpimunfit);
   Notify();
}

Bool_t Data::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Data::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Data::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Data_cxx
