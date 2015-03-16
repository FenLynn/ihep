#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include "TFile.h"                                    
#include "TChain.h"
#include "TStyle.h"                                    
#include "TROOT.h"                                    
#include "THStack.h"                                    
#include <TCut.h>
#include <TLegend.h>
#include <TArrow.h>
#include <TLatex.h>

using namespace std;

void mkroot()
{
	//get existed tree
	double ee_ivm_1,ee_ivm_2,ee_ivm_3,ee_ivm_4;
	
//	TFile *f1=new TFile("/besfs/users/lify/Root/Eemiss_v4/ana/09data/r1_2/out.root","READ");
//	TFile *f2=new TFile("/besfs/users/lify/Root/Eemiss_v4/ana/09mc/r1_2/out.root","READ");
//	TFile *f3=new TFile("/besfs/users/lify/Root/Eemiss_v4/ana/sigmc/ux/u1.6_h0.6/r1_2/out.root","READ");
//	TFile *f4=new TFile("/besfs/users/lify/Root/Eemiss_v4/ana/con/r1_2/out.root","READ");
	TFile *f1=new TFile("/besfs/users/lify/Root/Eemiss_v4/ana/12data/r1_7/out.root","READ");
	TFile *f2=new TFile("/besfs/users/lify/Root/Eemiss_v4/ana/12mc/r1_7/out.root","READ");
	TFile *f3=new TFile("/besfs/users/lify/Root/Eemiss_v4/ana/sigmc/ux/u1.6_h0.6/r2/out.root","READ");
	TFile *f4=new TFile("/besfs/users/lify/Root/Eemiss_v4/ana/con/r1_7/out.root","READ");

	TTree *t1=(TTree*)f1->Get("save");
	TTree *t2=(TTree*)f2->Get("save");
	TTree *t3=(TTree*)f3->Get("save");
	TTree *t4=(TTree*)f4->Get("save");

	t1->SetBranchAddress("ee_ivm", &ee_ivm_1);
	t2->SetBranchAddress("ee_ivm", &ee_ivm_2);
	t3->SetBranchAddress("ee_ivm", &ee_ivm_3);
	t4->SetBranchAddress("ee_ivm", &ee_ivm_4);

	//make new tree
	TFile *fout=new TFile("./mee.root","RECREATE");
	
	TTree *n1=new TTree("data","data");
	TTree *n2=new TTree("inmc","inclusive");
	TTree *n3=new TTree("sig","signal");
	TTree *n4=new TTree("con","continuum");
	
	n1->Branch("ee_ivm",&ee_ivm_1,"ee_ivm/D");
	n2->Branch("ee_ivm",&ee_ivm_2,"ee_ivm/D");
	n3->Branch("ee_ivm",&ee_ivm_3,"ee_ivm/D");
	n4->Branch("ee_ivm",&ee_ivm_4,"ee_ivm/D");

	fout->cd();
	for(Long64_t i=0;i<t1->GetEntries();i++)
	{
		t1->GetEntry(i);
		n1->Fill();
	}
	n1->AutoSave();
	for(Long64_t i=0;i<t2->GetEntries();i++)
	{
		t2->GetEntry(i);
		n2->Fill();
	}
	n2->AutoSave();
	for(Long64_t i=0;i<t3->GetEntries();i++)
	{
		t3->GetEntry(i);
		n3->Fill();
	}
	n3->AutoSave();
	
	for(Long64_t i=0;i<t4->GetEntries();i++)
	{
		t4->GetEntry(i);
		n4->Fill();
	}
	n4->AutoSave();

	fout->Close();
	delete fout;
}	
