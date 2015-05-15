#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void tdir()
{
	TFile *f=new TFile("afile.root","RECREATE");
	f->mkdir("a");
	f->mkdir("b");
	f->mkdir("c");

	TH1F *h1=new TH1F("h1","h1",100,0,100);
	TH1F *h2=new TH1F("h2","h2",100,0,100);
	TH1F *h3=new TH1F("h3","h3",100,0,100);
	TH1F *h4=new TH1F("h4","h4",100,0,100);

	for(int i=0;i<200;i++)
	{
		h1->Fill(i);
		h2->Fill(0.1*i);
		h3->Fill(0.2*i);
		h4->Fill(0.3*i);
	}
	f->cd("a");
	h1->Write();
	f->cd("b");
	h2->Write();
	f->cd("c");
	h3->Write();
	h4->Write();
	
	f->Close();
	
}


