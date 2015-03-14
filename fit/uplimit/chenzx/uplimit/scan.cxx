#include <iostream>
#include <fstream>

void scan()
{
Double_t chi2,Lmin,lambm,ksm,kslambm,pp_pp,pp_pm;
Double_t M_KsL;
//open your root file

    TChain * chain = new TChain("final");
    chain->Add("/besfs/users/chenzx/panfs-chenzx/kslambppi/data/JPsi2012/kslambppi.root");
//    char filename[97];
//    TChain * chain = new TChain("final");
//    for (int ifile=1;ifile<=97;ifile++) {
//       sprintf(filename,"../pppipiIn_%d.root",ifile);
//       chain->Add(filename);
//      }
    chain->SetBranchAddress("chi2", &chi2);
    chain->SetBranchAddress("ksm", &ksm);
    chain->SetBranchAddress("lambm", &lambm);
    chain->SetBranchAddress("Lmin", &Lmin);
    chain->SetBranchAddress("pp_pp", &pp_pp);
    chain->SetBranchAddress("pp_pm", &pp_pm);
    chain->SetBranchAddress("kslambm", &kslambm);
//    chain->SetBranchAddress("Pykaon", &pykaon);
//    chain->SetBranchAddress("Pzkaon", &pzkaon);
//    chain->SetBranchAddress("Ekaon", &Ekaon);
//    chain->SetBranchAddress("Pxlambda", &pxlambda);
//    chain->SetBranchAddress("Pylambda", &pylambda);
//    chain->SetBranchAddress("Pzlambda", &pzlambda);
//    chain->SetBranchAddress("Elambda", &Elambda);
//    chain->SetBranchAddress("m_PP", &m_PP);                                                                                
											      
  TFile *newfile = new TFile("Fitnew.root","recreate");
// TH1F *h1 =new  TH1F ("M_KsL","",50,0,0.1);
  //  TTree *newtree = chain->CloneTree(0);
TTree *newtree =new TTree("t1","recoil");
 t1->Branch("M_KsL", &M_KsL,"M_KsL/D"); 

  Long64_t nevent = chain->GetEntries();
  for(Long64_t j=0; j<nevent; j++ ) 
  {
    chain->GetEntry(j);
   //your cut condition
    
   if(!(chi2<50&&Lmin>0.0001&&fabs(lambm-1.116)<0.006&&fabs(ksm-0.498)<0.006&&pp_pp>0.3&&pp_pm>0.3)) continue; 
//if(chi2<40&&fabs(m_PpPIm_4c-1.116)>0.01&&fabs(m_PmPIp_4c-1.116)>0.01)
//if(chi2<40&&fabs(m_PpPIp_4c-1.21)>0.09&&fabs(m_PmPIm_4c-1.21)>0.09)
//cout<<"======"<<(m_KsL_4c-1.116-0.498)<<endl; 
   M_KsL =  kslambm-1.116-0.498;

//  h1->Fill(M_KsL);

   newtree->Fill();
  }
//  newfile->Write();
     newtree->Write();
   newfile->Close();

  //h100->DrawCopy();
  //delete h100;
}
