//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr 20 11:55:15 2015 by ROOT version 5.34/01
// from TChain nbinfo/
//////////////////////////////////////////////////////////

#ifndef num_h
#define num_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class num {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Ncut0;
   Int_t           Ncut1;
   Int_t           Ncut2;
   Int_t           Ncut3;
   Int_t           Ncut4;
   Int_t           Ncut5;
   Int_t           Ncut6;
   Int_t           Ncut7;
   Int_t           Ncut8;
   Int_t           Ncut9;
   Int_t           Ncut10;

   // List of branches
   TBranch        *b_Ncut0;   //!
   TBranch        *b_Ncut1;   //!
   TBranch        *b_Ncut2;   //!
   TBranch        *b_Ncut3;   //!
   TBranch        *b_Ncut4;   //!
   TBranch        *b_Ncut5;   //!
   TBranch        *b_Ncut6;   //!
   TBranch        *b_Ncut7;   //!
   TBranch        *b_Ncut8;   //!
   TBranch        *b_Ncut9;   //!
   TBranch        *b_Ncut10;   //!

   num(TTree *tree=0);
   virtual ~num();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef num_cxx
num::num(TTree *tree) : fChain(0) 
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
      f->GetObject("nbinfo",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("nbinfo","");
      chain->Add("../Pipieeh_001.root/nbinfo");
      chain->Add("../Pipieeh_002.root/nbinfo");
      chain->Add("../Pipieeh_003.root/nbinfo");
      chain->Add("../Pipieeh_004.root/nbinfo");
      chain->Add("../Pipieeh_005.root/nbinfo");
      chain->Add("../Pipieeh_006.root/nbinfo");
      chain->Add("../Pipieeh_007.root/nbinfo");
      chain->Add("../Pipieeh_008.root/nbinfo");
      chain->Add("../Pipieeh_009.root/nbinfo");
      chain->Add("../Pipieeh_010.root/nbinfo");
      chain->Add("../Pipieeh_011.root/nbinfo");
      chain->Add("../Pipieeh_012.root/nbinfo");
      chain->Add("../Pipieeh_013.root/nbinfo");
      chain->Add("../Pipieeh_014.root/nbinfo");
      chain->Add("../Pipieeh_015.root/nbinfo");
      chain->Add("../Pipieeh_016.root/nbinfo");
      chain->Add("../Pipieeh_017.root/nbinfo");
      chain->Add("../Pipieeh_018.root/nbinfo");
      chain->Add("../Pipieeh_019.root/nbinfo");
      chain->Add("../Pipieeh_020.root/nbinfo");
      chain->Add("../Pipieeh_021.root/nbinfo");
      chain->Add("../Pipieeh_022.root/nbinfo");
      chain->Add("../Pipieeh_023.root/nbinfo");
      chain->Add("../Pipieeh_024.root/nbinfo");
      chain->Add("../Pipieeh_025.root/nbinfo");
      chain->Add("../Pipieeh_026.root/nbinfo");
      chain->Add("../Pipieeh_027.root/nbinfo");
      chain->Add("../Pipieeh_028.root/nbinfo");
      chain->Add("../Pipieeh_029.root/nbinfo");
      chain->Add("../Pipieeh_030.root/nbinfo");
      chain->Add("../Pipieeh_031.root/nbinfo");
      chain->Add("../Pipieeh_032.root/nbinfo");
      chain->Add("../Pipieeh_033.root/nbinfo");
      chain->Add("../Pipieeh_034.root/nbinfo");
      chain->Add("../Pipieeh_035.root/nbinfo");
      chain->Add("../Pipieeh_036.root/nbinfo");
      chain->Add("../Pipieeh_037.root/nbinfo");
      chain->Add("../Pipieeh_038.root/nbinfo");
      chain->Add("../Pipieeh_039.root/nbinfo");
      chain->Add("../Pipieeh_040.root/nbinfo");
      chain->Add("../Pipieeh_041.root/nbinfo");
      chain->Add("../Pipieeh_042.root/nbinfo");
      chain->Add("../Pipieeh_043.root/nbinfo");
      chain->Add("../Pipieeh_044.root/nbinfo");
      chain->Add("../Pipieeh_045.root/nbinfo");
      chain->Add("../Pipieeh_046.root/nbinfo");
      chain->Add("../Pipieeh_047.root/nbinfo");
      chain->Add("../Pipieeh_048.root/nbinfo");
      chain->Add("../Pipieeh_049.root/nbinfo");
      chain->Add("../Pipieeh_050.root/nbinfo");
      chain->Add("../Pipieeh_051.root/nbinfo");
      chain->Add("../Pipieeh_052.root/nbinfo");
      chain->Add("../Pipieeh_053.root/nbinfo");
      chain->Add("../Pipieeh_054.root/nbinfo");
      chain->Add("../Pipieeh_055.root/nbinfo");
      chain->Add("../Pipieeh_056.root/nbinfo");
      chain->Add("../Pipieeh_057.root/nbinfo");
      chain->Add("../Pipieeh_058.root/nbinfo");
      chain->Add("../Pipieeh_059.root/nbinfo");
      chain->Add("../Pipieeh_060.root/nbinfo");
      chain->Add("../Pipieeh_061.root/nbinfo");
      chain->Add("../Pipieeh_062.root/nbinfo");
      chain->Add("../Pipieeh_063.root/nbinfo");
      chain->Add("../Pipieeh_064.root/nbinfo");
      chain->Add("../Pipieeh_065.root/nbinfo");
      chain->Add("../Pipieeh_066.root/nbinfo");
      chain->Add("../Pipieeh_067.root/nbinfo");
      chain->Add("../Pipieeh_068.root/nbinfo");
      chain->Add("../Pipieeh_069.root/nbinfo");
      chain->Add("../Pipieeh_070.root/nbinfo");
      chain->Add("../Pipieeh_071.root/nbinfo");
      chain->Add("../Pipieeh_072.root/nbinfo");
      chain->Add("../Pipieeh_073.root/nbinfo");
      chain->Add("../Pipieeh_074.root/nbinfo");
      chain->Add("../Pipieeh_075.root/nbinfo");
      chain->Add("../Pipieeh_076.root/nbinfo");
      chain->Add("../Pipieeh_077.root/nbinfo");
      chain->Add("../Pipieeh_078.root/nbinfo");
      chain->Add("../Pipieeh_079.root/nbinfo");
      chain->Add("../Pipieeh_080.root/nbinfo");
      chain->Add("../Pipieeh_081.root/nbinfo");
      chain->Add("../Pipieeh_082.root/nbinfo");
      chain->Add("../Pipieeh_083.root/nbinfo");
      chain->Add("../Pipieeh_084.root/nbinfo");
      chain->Add("../Pipieeh_085.root/nbinfo");
      chain->Add("../Pipieeh_086.root/nbinfo");
      chain->Add("../Pipieeh_087.root/nbinfo");
      chain->Add("../Pipieeh_088.root/nbinfo");
      chain->Add("../Pipieeh_089.root/nbinfo");
      chain->Add("../Pipieeh_090.root/nbinfo");
      chain->Add("../Pipieeh_091.root/nbinfo");
      chain->Add("../Pipieeh_092.root/nbinfo");
      chain->Add("../Pipieeh_093.root/nbinfo");
      chain->Add("../Pipieeh_094.root/nbinfo");
      chain->Add("../Pipieeh_095.root/nbinfo");
      chain->Add("../Pipieeh_096.root/nbinfo");
      chain->Add("../Pipieeh_097.root/nbinfo");
      chain->Add("../Pipieeh_098.root/nbinfo");
      chain->Add("../Pipieeh_099.root/nbinfo");
      chain->Add("../Pipieeh_100.root/nbinfo");
      chain->Add("../Pipieeh_101.root/nbinfo");
      chain->Add("../Pipieeh_102.root/nbinfo");
      chain->Add("../Pipieeh_103.root/nbinfo");
      chain->Add("../Pipieeh_104.root/nbinfo");
      chain->Add("../Pipieeh_105.root/nbinfo");
      chain->Add("../Pipieeh_106.root/nbinfo");
      chain->Add("../Pipieeh_107.root/nbinfo");
      chain->Add("../Pipieeh_108.root/nbinfo");
      chain->Add("../Pipieeh_109.root/nbinfo");
      chain->Add("../Pipieeh_110.root/nbinfo");
      chain->Add("../Pipieeh_111.root/nbinfo");
      chain->Add("../Pipieeh_112.root/nbinfo");
      chain->Add("../Pipieeh_113.root/nbinfo");
      chain->Add("../Pipieeh_114.root/nbinfo");
      chain->Add("../Pipieeh_115.root/nbinfo");
      chain->Add("../Pipieeh_116.root/nbinfo");
      chain->Add("../Pipieeh_117.root/nbinfo");
      chain->Add("../Pipieeh_118.root/nbinfo");
      chain->Add("../Pipieeh_119.root/nbinfo");
      chain->Add("../Pipieeh_120.root/nbinfo");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

num::~num()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t num::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t num::LoadTree(Long64_t entry)
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

void num::Init(TTree *tree)
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

   fChain->SetBranchAddress("Ncut0", &Ncut0, &b_Ncut0);
   fChain->SetBranchAddress("Ncut1", &Ncut1, &b_Ncut1);
   fChain->SetBranchAddress("Ncut2", &Ncut2, &b_Ncut2);
   fChain->SetBranchAddress("Ncut3", &Ncut3, &b_Ncut3);
   fChain->SetBranchAddress("Ncut4", &Ncut4, &b_Ncut4);
   fChain->SetBranchAddress("Ncut5", &Ncut5, &b_Ncut5);
   fChain->SetBranchAddress("Ncut6", &Ncut6, &b_Ncut6);
   fChain->SetBranchAddress("Ncut7", &Ncut7, &b_Ncut7);
   fChain->SetBranchAddress("Ncut8", &Ncut8, &b_Ncut8);
   fChain->SetBranchAddress("Ncut9", &Ncut9, &b_Ncut9);
   fChain->SetBranchAddress("Ncut10", &Ncut10, &b_Ncut10);
   Notify();
}

Bool_t num::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void num::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t num::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef num_cxx
