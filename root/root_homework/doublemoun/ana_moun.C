#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <TH1F.h>
using namespace std;

void ana_moun()
{
	double m_ene1,m_ene2,add_mass;
	TH1F *h=new TH1F("deposit energy in EMC","deposit energy in EMC",100,0.0,0.8);
	TFile *f=new TFile("test.root","read");
	TTree *T=f->Get("inv_ene");
	T->SetBranchAddress("ene1",&m_ene1);
	T->SetBranchAddress("ene2",&m_ene2);
	//T->Draw("ene1");
	int total_entries=T->GetEntries();
	int nbytes;
	std::cout<<"Total Entries:   "<<total_entries<<std::endl;
	for(int i=0;i<total_entries;i++)
	{
		nbytes+=T->GetEntry(i);
		add_mass=m_ene1+m_ene2;
		//cout<<"energy1: "<<m_ene1<<"  energy2: "<<m_ene2<<"  Total mass: "<<add_mass<<endl;
		h->Fill(add_mass);
	}
	h->Draw();
		
}
	
