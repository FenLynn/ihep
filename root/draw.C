#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include "TFile.h"                                    
#include "TChain.h"
#include "TStyle.h"                                    
#include "TROOT.h"                                    
#include "THStack.h"                                    
#include "TH1F.h"                      
#include "TTree.h" 
#include "TCut.h" 
#include "TLegend.h" 
#include "TCanvas.h"

int DrawAll(int draw_option){
	TFile *f_data  =new TFile("DpD0pi.root","READ");
	TTree *t_data = (TTree*)f_data->Get("save");
	TFile *f_Xc  =new TFile("effixc.root","READ");
	TTree *t_Xc = (TTree*)f_Xc->Get("save");
	TFile *f_mc  =new TFile("phsp.root","READ");
	TTree *t_mc = (TTree*)f_mc->Get("save");

	TFile *f_DD  = new TFile("DD.root","READ");
	TFile *f_DDpi  = new TFile("DDpi.root","READ");
	TFile *f_ISR  = new TFile("ISR.root","READ");
	TFile *f_qqbar  = new TFile("qqbar.root","READ");
	TFile *f_hadrons  = new TFile("hadrons.root","READ");
	TFile *f_gamXYZ  = new TFile("gamXYZ.root","READ");

	TTree *t_DD = (TTree*)f_DD->Get("save");
	TTree *t_DDpi = (TTree*)f_DDpi->Get("save");
	TTree *t_ISR = (TTree*)f_ISR->Get("save");
	TTree *t_qqbar = (TTree*)f_qqbar->Get("save");
	TTree *t_hadrons = (TTree*)f_hadrons->Get("save");
	TTree *t_gamXYZ = (TTree*)f_gamXYZ->Get("save");
	TString draw_var=" ";Double_t xmin = 0.0; Double_t xmax = 0.0;Int_t bins = 10;TString xtitle = " ";

	if(draw_option==1) {draw_var="Mrcpi0";xmin = 3.84; xmax = 4.05;bins = 21;xtitle = "M_{Recoil}(#pi^{0}) (GeV/c^{2})";}
	if(draw_option==2) {draw_var="MrcDppi0";xmin = 1.94; xmax = 2.1;bins = 20;xtitle = "M_{Recoil}(D^{+}#pi^{0}) (GeV/c^{2})";}


	TCut cut_all1 = cut_all&&cut_truthmatch;

	TH1F *th1f_dat = new TH1F("th1f_data","",bins,xmin,xmax);
	TH1F *th1f_mc = new TH1F("th1f_mc","",bins,xmin,xmax);
	TH1F *th1f_Xc = new TH1F("th1f_Xc","",bins,xmin,xmax);
	TH1F *th1f_DD = new TH1F("th1f_DD","",bins,xmin,xmax);
	TH1F *th1f_DDpi = new TH1F("th1f_DDpi","",bins,xmin,xmax);
	TH1F *th1f_ISR = new TH1F("th1f_ISR","",bins,xmin,xmax);
	TH1F *th1f_qqbar = new TH1F("th1f_qqbar","",bins,xmin,xmax);
	TH1F *th1f_hadrons = new TH1F("th1f_hadrons","",bins,xmin,xmax);
	TH1F *th1f_gXYZ = new TH1F("th1f_gXYZ","",bins,xmin,xmax);

	t_data->Project("th1f_data",draw_var,cut_all);
	t_mc->Project("th1f_mc",draw_var,cut_all);
	t_Xc->Project("th1f_Xc",draw_var,cut_all1);
	t_DD->Project("th1f_DD",draw_var,cut_all);
	t_DDpi->Project("th1f_DDpi",draw_var,cut_all);
	t_ISR->Project("th1f_ISR",draw_var,cut_all);
	t_qqbar->Project("th1f_qqbar",draw_var,cut_all);
	t_hadrons->Project("th1f_hadrons",draw_var,cut_all);
	t_gamXYZ->Project("th1f_gXYZ",draw_var,cut_all);




	th1f_dat->SetXTitle(xtitle);
	th1f_dat->SetYTitle(Form("ENTRIES/(%.1lf MeV/c^{2})",ratio));
	th1f_Xc->SetXTitle(xtitle);
	th1f_Xc->SetYTitle(Form("ENTRIES/(%.1lf MeV/c^{2})",ratio));

	th1f_dat->SetLineColor(1);th1f_dat->SetMarkerStyle(8);th1f_dat->SetMarkerSize(0.8);
	th1f_mc->SetFillColor(2);th1f_mc->SetLineColor(2);
	th1f_Xc->SetLineColor(9); th1f_Xc->SetLineWidth(3);
	th1f_DD->SetFillColor(4);th1f_DD->SetLineColor(4);
	th1f_DDpi->SetFillColor(7);th1f_DDpi->SetLineColor(7);
	th1f_ISR->SetFillColor(6);th1f_ISR->SetLineColor(6);
	th1f_qqbar->SetFillColor(5);th1f_qqbar->SetLineColor(5);
	th1f_hadrons->SetFillColor(3);th1f_hadrons->SetLineColor(3);
	th1f_gXYZ->SetFillColor(8);th1f_gXYZ->SetLineColor(8);


	th1f_DD->Scale(0.35);
	th1f_DDpi->Scale(0.04);
	th1f_ISR->Scale(0.15);
	th1f_qqbar->Scale(0.1);
	th1f_hadrons->Scale(0.1);
	th1f_gXYZ->Scale(0.1);
	th1f_Xc->Scale(0.008);
	th1f_mc->Scale(0.025);

	Double_t num_DD=th1f_DD->Integral(); 
	Double_t num_DDpi=th1f_DDpi->Integral(); 
	Double_t num_ISR=th1f_ISR->Integral(); 
	Double_t num_qqbar=th1f_qqbar->Integral(); 
	Double_t num_hadrons=th1f_hadrons->Integral(); 






	Double_t num_gXYZ=th1f_gXYZ->Integral(); 
	Double_t num_mc=th1f_mc->Integral(); 
	Double_t num_Xc=th1f_Xc->Integral(); 

	cout<<"DD num = "<<num_DD<<endl;
	cout<<"DDpi num = "<<num_DDpi<<endl;
	cout<<"ISR num = "<<num_ISR<<endl;
	cout<<"qqbar num = "<<num_qqbar<<endl;
	cout<<"hadrons num = "<<num_hadrons<<endl;
	cout<<"gXYZ num = "<<num_gXYZ<<endl;
	cout<<"PHSP MC num = "<<num_mc<<endl;
	cout<<"Xc num = "<<num_Xc<<endl;


	THStack *hs = new THStack("hs","Stacked histograms");
	//create three 1-d histograms
	hs->Add(th1f_mc);
	hs->Add(th1f_gXYZ);
	hs->Add(th1f_qqbar);
	hs->Add(th1f_hadrons);
	hs->Add(th1f_ISR);
	hs->Add(th1f_DDpi);
	hs->Add(th1f_DD);

	TLegend *legend = new TLegend(.62,.58,.87,.86);
	legend->AddEntry(th1f_dat,"Data","LEP");
	legend->AddEntry(th1f_Xc,"Xc","L");
	legend->AddEntry(th1f_mc,"D^{+}D*^{-}#pi^{0}+c.c 3-body PHSP","F");
	legend->AddEntry(th1f_DD,"DD","F");
	legend->AddEntry(th1f_DDpi,"DD#pi(exclude D^{+}D*^{-}#pi^{0}+c.c)","F");
	legend->AddEntry(th1f_ISR,"ISR","F");
	legend->AddEntry(th1f_qqbar,"q#bar{q}","F");
	legend->AddEntry(th1f_hadrons,"hadrons","F");
	legend->AddEntry(th1f_gXYZ,"#gamma XYZ","F");
	legend->SetFillColor(0);
	legend->SetLineColor(0);
	legend->SetShadowColor(0);

	cout<<"drawing variable: "<<draw_var<<endl;
	//TCanvas *c1=new TCanvas("c1","",0,0,800,600);
	TCanvas *c1 = NULL;
	TCanvas *c8 = NULL;
	if(draw_option==1)c1 = new TCanvas(Form("c%d",draw_option),"",0,0,800,600);


	if(draw_option==1) hs->SetMaximum(25);

	hs->Draw(""); 
	th1f_Xc->Draw("same");
	th1f_dat->Draw("e same");
	legend->Draw("same");
	hs->GetXaxis()->SetTitle(xtitle);
	hs->GetYaxis()->SetTitle(Form("ENTRIES/(%.1lf MeV/c^{2})",ratio));

	gPad->RedrawAxis();

	if(draw_option==1) c1->SaveAs("./plot/rcpi0.eps"); 

	return 0;
}

	void IncAll(){
		DrawAll(1)
	}
