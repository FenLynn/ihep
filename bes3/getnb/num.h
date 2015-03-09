//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar  9 11:00:33 2015 by ROOT version 5.34/01
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
      chain->Add("../Eemiss001.root/nbinfo");
      chain->Add("../Eemiss002.root/nbinfo");
      chain->Add("../Eemiss003.root/nbinfo");
      chain->Add("../Eemiss004.root/nbinfo");
      chain->Add("../Eemiss005.root/nbinfo");
      chain->Add("../Eemiss006.root/nbinfo");
      chain->Add("../Eemiss007.root/nbinfo");
      chain->Add("../Eemiss008.root/nbinfo");
      chain->Add("../Eemiss009.root/nbinfo");
      chain->Add("../Eemiss010.root/nbinfo");
      chain->Add("../Eemiss011.root/nbinfo");
      chain->Add("../Eemiss012.root/nbinfo");
      chain->Add("../Eemiss013.root/nbinfo");
      chain->Add("../Eemiss014.root/nbinfo");
      chain->Add("../Eemiss015.root/nbinfo");
      chain->Add("../Eemiss016.root/nbinfo");
      chain->Add("../Eemiss017.root/nbinfo");
      chain->Add("../Eemiss018.root/nbinfo");
      chain->Add("../Eemiss019.root/nbinfo");
      chain->Add("../Eemiss020.root/nbinfo");
      chain->Add("../Eemiss021.root/nbinfo");
      chain->Add("../Eemiss022.root/nbinfo");
      chain->Add("../Eemiss023.root/nbinfo");
      chain->Add("../Eemiss024.root/nbinfo");
      chain->Add("../Eemiss025.root/nbinfo");
      chain->Add("../Eemiss026.root/nbinfo");
      chain->Add("../Eemiss027.root/nbinfo");
      chain->Add("../Eemiss028.root/nbinfo");
      chain->Add("../Eemiss029.root/nbinfo");
      chain->Add("../Eemiss030.root/nbinfo");
      chain->Add("../Eemiss031.root/nbinfo");
      chain->Add("../Eemiss032.root/nbinfo");
      chain->Add("../Eemiss033.root/nbinfo");
      chain->Add("../Eemiss034.root/nbinfo");
      chain->Add("../Eemiss035.root/nbinfo");
      chain->Add("../Eemiss036.root/nbinfo");
      chain->Add("../Eemiss037.root/nbinfo");
      chain->Add("../Eemiss038.root/nbinfo");
      chain->Add("../Eemiss039.root/nbinfo");
      chain->Add("../Eemiss040.root/nbinfo");
      chain->Add("../Eemiss041.root/nbinfo");
      chain->Add("../Eemiss042.root/nbinfo");
      chain->Add("../Eemiss043.root/nbinfo");
      chain->Add("../Eemiss044.root/nbinfo");
      chain->Add("../Eemiss045.root/nbinfo");
      chain->Add("../Eemiss046.root/nbinfo");
      chain->Add("../Eemiss047.root/nbinfo");
      chain->Add("../Eemiss048.root/nbinfo");
      chain->Add("../Eemiss049.root/nbinfo");
      chain->Add("../Eemiss050.root/nbinfo");
      chain->Add("../Eemiss051.root/nbinfo");
      chain->Add("../Eemiss052.root/nbinfo");
      chain->Add("../Eemiss053.root/nbinfo");
      chain->Add("../Eemiss054.root/nbinfo");
      chain->Add("../Eemiss055.root/nbinfo");
      chain->Add("../Eemiss056.root/nbinfo");
      chain->Add("../Eemiss057.root/nbinfo");
      chain->Add("../Eemiss058.root/nbinfo");
      chain->Add("../Eemiss059.root/nbinfo");
      chain->Add("../Eemiss060.root/nbinfo");
      chain->Add("../Eemiss061.root/nbinfo");
      chain->Add("../Eemiss062.root/nbinfo");
      chain->Add("../Eemiss063.root/nbinfo");
      chain->Add("../Eemiss064.root/nbinfo");
      chain->Add("../Eemiss065.root/nbinfo");
      chain->Add("../Eemiss066.root/nbinfo");
      chain->Add("../Eemiss067.root/nbinfo");
      chain->Add("../Eemiss068.root/nbinfo");
      chain->Add("../Eemiss069.root/nbinfo");
      chain->Add("../Eemiss070.root/nbinfo");
      chain->Add("../Eemiss071.root/nbinfo");
      chain->Add("../Eemiss072.root/nbinfo");
      chain->Add("../Eemiss073.root/nbinfo");
      chain->Add("../Eemiss074.root/nbinfo");
      chain->Add("../Eemiss075.root/nbinfo");
      chain->Add("../Eemiss076.root/nbinfo");
      chain->Add("../Eemiss077.root/nbinfo");
      chain->Add("../Eemiss078.root/nbinfo");
      chain->Add("../Eemiss079.root/nbinfo");
      chain->Add("../Eemiss080.root/nbinfo");
      chain->Add("../Eemiss081.root/nbinfo");
      chain->Add("../Eemiss082.root/nbinfo");
      chain->Add("../Eemiss083.root/nbinfo");
      chain->Add("../Eemiss084.root/nbinfo");
      chain->Add("../Eemiss085.root/nbinfo");
      chain->Add("../Eemiss086.root/nbinfo");
      chain->Add("../Eemiss087.root/nbinfo");
      chain->Add("../Eemiss088.root/nbinfo");
      chain->Add("../Eemiss089.root/nbinfo");
      chain->Add("../Eemiss090.root/nbinfo");
      chain->Add("../Eemiss091.root/nbinfo");
      chain->Add("../Eemiss092.root/nbinfo");
      chain->Add("../Eemiss093.root/nbinfo");
      chain->Add("../Eemiss094.root/nbinfo");
      chain->Add("../Eemiss095.root/nbinfo");
      chain->Add("../Eemiss096.root/nbinfo");
      chain->Add("../Eemiss097.root/nbinfo");
      chain->Add("../Eemiss098.root/nbinfo");
      chain->Add("../Eemiss099.root/nbinfo");
      chain->Add("../Eemiss100.root/nbinfo");
      chain->Add("../Eemiss101.root/nbinfo");
      chain->Add("../Eemiss102.root/nbinfo");
      chain->Add("../Eemiss103.root/nbinfo");
      chain->Add("../Eemiss104.root/nbinfo");
      chain->Add("../Eemiss105.root/nbinfo");
      chain->Add("../Eemiss106.root/nbinfo");
      chain->Add("../Eemiss107.root/nbinfo");
      chain->Add("../Eemiss108.root/nbinfo");
      chain->Add("../Eemiss109.root/nbinfo");
      chain->Add("../Eemiss110.root/nbinfo");
      chain->Add("../Eemiss111.root/nbinfo");
      chain->Add("../Eemiss112.root/nbinfo");
      chain->Add("../Eemiss113.root/nbinfo");
      chain->Add("../Eemiss114.root/nbinfo");
      chain->Add("../Eemiss115.root/nbinfo");
      chain->Add("../Eemiss116.root/nbinfo");
      chain->Add("../Eemiss117.root/nbinfo");
      chain->Add("../Eemiss118.root/nbinfo");
      chain->Add("../Eemiss119.root/nbinfo");
      chain->Add("../Eemiss120.root/nbinfo");
      chain->Add("../Eemiss121.root/nbinfo");
      chain->Add("../Eemiss122.root/nbinfo");
      chain->Add("../Eemiss123.root/nbinfo");
      chain->Add("../Eemiss124.root/nbinfo");
      chain->Add("../Eemiss125.root/nbinfo");
      chain->Add("../Eemiss126.root/nbinfo");
      chain->Add("../Eemiss127.root/nbinfo");
      chain->Add("../Eemiss128.root/nbinfo");
      chain->Add("../Eemiss129.root/nbinfo");
      chain->Add("../Eemiss130.root/nbinfo");
      chain->Add("../Eemiss131.root/nbinfo");
      chain->Add("../Eemiss132.root/nbinfo");
      chain->Add("../Eemiss133.root/nbinfo");
      chain->Add("../Eemiss134.root/nbinfo");
      chain->Add("../Eemiss135.root/nbinfo");
      chain->Add("../Eemiss136.root/nbinfo");
      chain->Add("../Eemiss137.root/nbinfo");
      chain->Add("../Eemiss138.root/nbinfo");
      chain->Add("../Eemiss139.root/nbinfo");
      chain->Add("../Eemiss140.root/nbinfo");
      chain->Add("../Eemiss141.root/nbinfo");
      chain->Add("../Eemiss142.root/nbinfo");
      chain->Add("../Eemiss143.root/nbinfo");
      chain->Add("../Eemiss144.root/nbinfo");
      chain->Add("../Eemiss145.root/nbinfo");
      chain->Add("../Eemiss146.root/nbinfo");
      chain->Add("../Eemiss147.root/nbinfo");
      chain->Add("../Eemiss148.root/nbinfo");
      chain->Add("../Eemiss149.root/nbinfo");
      chain->Add("../Eemiss150.root/nbinfo");
      chain->Add("../Eemiss151.root/nbinfo");
      chain->Add("../Eemiss152.root/nbinfo");
      chain->Add("../Eemiss153.root/nbinfo");
      chain->Add("../Eemiss154.root/nbinfo");
      chain->Add("../Eemiss155.root/nbinfo");
      chain->Add("../Eemiss156.root/nbinfo");
      chain->Add("../Eemiss157.root/nbinfo");
      chain->Add("../Eemiss158.root/nbinfo");
      chain->Add("../Eemiss159.root/nbinfo");
      chain->Add("../Eemiss160.root/nbinfo");
      chain->Add("../Eemiss161.root/nbinfo");
      chain->Add("../Eemiss162.root/nbinfo");
      chain->Add("../Eemiss163.root/nbinfo");
      chain->Add("../Eemiss164.root/nbinfo");
      chain->Add("../Eemiss165.root/nbinfo");
      chain->Add("../Eemiss166.root/nbinfo");
      chain->Add("../Eemiss167.root/nbinfo");
      chain->Add("../Eemiss168.root/nbinfo");
      chain->Add("../Eemiss169.root/nbinfo");
      chain->Add("../Eemiss170.root/nbinfo");
      chain->Add("../Eemiss171.root/nbinfo");
      chain->Add("../Eemiss172.root/nbinfo");
      chain->Add("../Eemiss173.root/nbinfo");
      chain->Add("../Eemiss174.root/nbinfo");
      chain->Add("../Eemiss175.root/nbinfo");
      chain->Add("../Eemiss176.root/nbinfo");
      chain->Add("../Eemiss177.root/nbinfo");
      chain->Add("../Eemiss178.root/nbinfo");
      chain->Add("../Eemiss179.root/nbinfo");
      chain->Add("../Eemiss180.root/nbinfo");
      chain->Add("../Eemiss181.root/nbinfo");
      chain->Add("../Eemiss182.root/nbinfo");
      chain->Add("../Eemiss183.root/nbinfo");
      chain->Add("../Eemiss184.root/nbinfo");
      chain->Add("../Eemiss185.root/nbinfo");
      chain->Add("../Eemiss186.root/nbinfo");
      chain->Add("../Eemiss187.root/nbinfo");
      chain->Add("../Eemiss188.root/nbinfo");
      chain->Add("../Eemiss189.root/nbinfo");
      chain->Add("../Eemiss190.root/nbinfo");
      chain->Add("../Eemiss191.root/nbinfo");
      chain->Add("../Eemiss192.root/nbinfo");
      chain->Add("../Eemiss193.root/nbinfo");
      chain->Add("../Eemiss194.root/nbinfo");
      chain->Add("../Eemiss195.root/nbinfo");
      chain->Add("../Eemiss196.root/nbinfo");
      chain->Add("../Eemiss197.root/nbinfo");
      chain->Add("../Eemiss198.root/nbinfo");
      chain->Add("../Eemiss199.root/nbinfo");
      chain->Add("../Eemiss200.root/nbinfo");
      chain->Add("../Eemiss201.root/nbinfo");
      chain->Add("../Eemiss202.root/nbinfo");
      chain->Add("../Eemiss203.root/nbinfo");
      chain->Add("../Eemiss204.root/nbinfo");
      chain->Add("../Eemiss205.root/nbinfo");
      chain->Add("../Eemiss206.root/nbinfo");
      chain->Add("../Eemiss207.root/nbinfo");
      chain->Add("../Eemiss208.root/nbinfo");
      chain->Add("../Eemiss209.root/nbinfo");
      chain->Add("../Eemiss210.root/nbinfo");
      chain->Add("../Eemiss211.root/nbinfo");
      chain->Add("../Eemiss212.root/nbinfo");
      chain->Add("../Eemiss213.root/nbinfo");
      chain->Add("../Eemiss214.root/nbinfo");
      chain->Add("../Eemiss215.root/nbinfo");
      chain->Add("../Eemiss216.root/nbinfo");
      chain->Add("../Eemiss217.root/nbinfo");
      chain->Add("../Eemiss218.root/nbinfo");
      chain->Add("../Eemiss219.root/nbinfo");
      chain->Add("../Eemiss220.root/nbinfo");
      chain->Add("../Eemiss221.root/nbinfo");
      chain->Add("../Eemiss222.root/nbinfo");
      chain->Add("../Eemiss223.root/nbinfo");
      chain->Add("../Eemiss224.root/nbinfo");
      chain->Add("../Eemiss225.root/nbinfo");
      chain->Add("../Eemiss226.root/nbinfo");
      chain->Add("../Eemiss227.root/nbinfo");
      chain->Add("../Eemiss228.root/nbinfo");
      chain->Add("../Eemiss229.root/nbinfo");
      chain->Add("../Eemiss230.root/nbinfo");
      chain->Add("../Eemiss231.root/nbinfo");
      chain->Add("../Eemiss232.root/nbinfo");
      chain->Add("../Eemiss233.root/nbinfo");
      chain->Add("../Eemiss234.root/nbinfo");
      chain->Add("../Eemiss235.root/nbinfo");
      chain->Add("../Eemiss236.root/nbinfo");
      chain->Add("../Eemiss237.root/nbinfo");
      chain->Add("../Eemiss238.root/nbinfo");
      chain->Add("../Eemiss239.root/nbinfo");
      chain->Add("../Eemiss240.root/nbinfo");
      chain->Add("../Eemiss241.root/nbinfo");
      chain->Add("../Eemiss242.root/nbinfo");
      chain->Add("../Eemiss243.root/nbinfo");
      chain->Add("../Eemiss244.root/nbinfo");
      chain->Add("../Eemiss245.root/nbinfo");
      chain->Add("../Eemiss246.root/nbinfo");
      chain->Add("../Eemiss247.root/nbinfo");
      chain->Add("../Eemiss248.root/nbinfo");
      chain->Add("../Eemiss249.root/nbinfo");
      chain->Add("../Eemiss250.root/nbinfo");
      chain->Add("../Eemiss251.root/nbinfo");
      chain->Add("../Eemiss252.root/nbinfo");
      chain->Add("../Eemiss253.root/nbinfo");
      chain->Add("../Eemiss254.root/nbinfo");
      chain->Add("../Eemiss255.root/nbinfo");
      chain->Add("../Eemiss256.root/nbinfo");
      chain->Add("../Eemiss257.root/nbinfo");
      chain->Add("../Eemiss258.root/nbinfo");
      chain->Add("../Eemiss259.root/nbinfo");
      chain->Add("../Eemiss260.root/nbinfo");
      chain->Add("../Eemiss261.root/nbinfo");
      chain->Add("../Eemiss262.root/nbinfo");
      chain->Add("../Eemiss263.root/nbinfo");
      chain->Add("../Eemiss264.root/nbinfo");
      chain->Add("../Eemiss265.root/nbinfo");
      chain->Add("../Eemiss266.root/nbinfo");
      chain->Add("../Eemiss267.root/nbinfo");
      chain->Add("../Eemiss268.root/nbinfo");
      chain->Add("../Eemiss269.root/nbinfo");
      chain->Add("../Eemiss270.root/nbinfo");
      chain->Add("../Eemiss271.root/nbinfo");
      chain->Add("../Eemiss272.root/nbinfo");
      chain->Add("../Eemiss273.root/nbinfo");
      chain->Add("../Eemiss274.root/nbinfo");
      chain->Add("../Eemiss275.root/nbinfo");
      chain->Add("../Eemiss276.root/nbinfo");
      chain->Add("../Eemiss277.root/nbinfo");
      chain->Add("../Eemiss278.root/nbinfo");
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
