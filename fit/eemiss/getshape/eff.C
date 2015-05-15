#include "/workfs/bes/lify/myinclude/rootall.h"

using namespace std;

void eff()
{
	SetMyStyle();
	TFile *fin=new TFile("outsig.root","READ");
	TTree *tin=(TTree*)fin->Get("siginfo");
	

	double massu[100];
	double eff[100];
	double e_eff[100];

	double temp_massu;
	double temp_eff;
	tin->SetBranchAddress("massu",&temp_massu);
	tin->SetBranchAddress("eff",&temp_eff);

	int N=tin->GetEntries();
	
	int Ntotal = 50000;
//	cout<<N<<endl;

	for(int i=0;i<tin->GetEntries();i++){
	
//		cout<<i<<endl;
		tin->GetEntry(i);
		massu[i]=temp_massu;
		eff[i]=temp_eff;
		e_eff[i]=sqrt(eff[i]*(1-eff[i])/Ntotal);
		cout<<"i="<<i<<" "<<eff[i]<<" "<<e_eff[i]<<endl;
		//e_eff[i]=0.1;
	}
//	cout<<"t get"<<endl;
	TGraphErrors *graph=new TGraphErrors(N,massu,eff,0,e_eff);
	double xmin=massu[0];
	double xmax=massu[N-1];
	TF1 *f1=new TF1("f1","pol2",xmin,xmax);
	TCanvas *c=new TCanvas("eff","eff",800,600);
	NameAxis(graph,"mass_{U} (GeV/c^{2}) ","efficiency");
	graph->SetMarkerStyle(20);
	graph->SetMarkerColor(4);
	graph->SetMarkerSize(1.5);
	graph->SetTitle("efficiency curve");

	graph->Draw("AP");
	graph->Fit(f1,"R");
	cout<<f1->GetParameter(0);
	cout<<f1->GetParameter(1);
	cout<<f1->GetParameter(2);
//	TLatex ltx(0.5,0.8,Form("#splitline{#splitline{p0=%.3f}{p1=%.3f}}{p2=%.3f}",f1->GetParameter(0),f1->GetParameter(1),f1->GetParameter(2)));
	TLatex ltx(0.5,0.85,Form("y= %.3f x^{2}+ %.3f x+ %.3f ",f1->GetParameter(2),f1->GetParameter(1),f1->GetParameter(0)));
	ltx.SetTextFont(62);
	ltx.SetTextColor(2);
	ltx.SetTextSize(0.04);
	ltx.SetNDC();
	ltx.DrawClone();
	c->SaveAs("eff.root");
}

