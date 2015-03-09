#define num_cxx
#include "num.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

void num::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L nb.C
//      Root > nb t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	int kLIST = 0;
	freopen("../number.txt","w",stdout);	
	cout<<"This is number info for files" <<endl;
	cout<<system("pwd -P")<<endl;

   if (fChain == 0) return;
	
   Long64_t           Tcut0=0;
   Long64_t           Tcut1=0;
   Long64_t           Tcut2=0;
   Long64_t           Tcut3=0;
   Long64_t           Tcut4=0;
   Long64_t           Tcut5=0;
   Long64_t           Tcut6=0;
   Long64_t           Tcut7=0;
   Long64_t           Tcut8=0;
   Long64_t           Tcut9=0;
   Long64_t           Tcut10=0;
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	 Tcut0+=Ncut0;
	 if( kLIST == 1)  cout<<"N:"<<Tcut0<<"	iN:"<<Ncut0<<endl;
	 Tcut1+=Ncut1;
	 Tcut2+=Ncut2;
	 Tcut3+=Ncut3;
	 Tcut4+=Ncut4;
	 Tcut5+=Ncut5;
	 Tcut6+=Ncut6;
	 Tcut7+=Ncut7;
	 Tcut8+=Ncut8;
	 Tcut9+=Ncut9;
	 Tcut10+=Ncut10;
      // if (Cut(ientry) < 0) continue;
   }
   cout<<"Tcut0 "<<			  Tcut0<<endl;
   cout<<"Tcut1 "<<           Tcut1<<endl;
   cout<<"Tcut2 "<<           Tcut2<<endl;
   cout<<"Tcut3 "<<           Tcut3<<endl;
   cout<<"Tcut4 "<<           Tcut4<<endl;
   cout<<"Tcut5 "<<           Tcut5<<endl;
   cout<<"Tcut6 "<<           Tcut6<<endl;
   cout<<"Tcut7 "<<           Tcut7<<endl;
   cout<<"Tcut8 "<<           Tcut8<<endl;
   cout<<"Tcut9 "<<           Tcut9<<endl;
   cout<<"Tcut10 "<<           Tcut10<<endl;
}
