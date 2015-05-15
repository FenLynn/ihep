#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "TMath.h"
#include "TAxis.h"
#include "TCut.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TFrame.h"
#include "TNtuple.h"
#include "TPostScript.h"
#include "RooFit.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooNovosibirsk.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooBreitWigner.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooArgusBG.h"
#include "RooArgList.h"
#include "RooAddPdf.h"
#include "RooAbsPdf.h"
#include "RooKeysPdf.h"
#include "RooPlot.h"

using namespace RooFit ;

void uplimit()
{
// --- Global Settings ---
  gROOT->SetStyle("Plain");

// ==================== / Input & Output / ==================== //
// --- Definition ---
	TCut cut_deltaE = "deltaE>-0.060&&deltaE<0.030";
	TCut cut_mH2 = "mH2>0.110&&mH2<0.155";
	TCut cut_mL1L2_s = "(mL1L2<0.935)||(mL1L2>1.053)";
	TCut cut_mL1L2_l = "mL1L2>0.935&&mL1L2<1.053";
	TCut cut_eop="eopL1>0.8&&eopL2>0.8&&eopL1<1.2&&eopL2<1.2";
	TCut cut_GC="mL1L2>0.2";
	TCut cut_s=cut_deltaE&&cut_mH2&&cut_mL1L2_s&&cut_GC&&cut_eop;
	TCut cut_l=cut_deltaE&&cut_mH2&&cut_mL1L2_l&&cut_GC&&cut_eop;

// --- Input ---
	TString FILENAME_I_1 = "/scratchfs/bes/xiaod/STDptoPiPi0EEAlg/root/inclusive/scale/inclusive.root";
  TFile *FILE_I_1 = new TFile(FILENAME_I_1);
	
	TString FILENAME_I_2 = "/scratchfs/bes/xiaod/STDptoPiPi0EEAlg/root/exclusive/pdf/exclusive.mBC.s.pdf.root";
  TFile *FILE_I_2 = new TFile(FILENAME_I_2);
	cout << " Run Here 1..." << endl;

// --- Output ---
	TString FILENAME_O_1 = "/scratchfs/bes/xiaod/STDptoPiPi0EEAlg/root/inclusive/ana/inclusive.uplimit.s.root";
	TFile *FILE_O = new TFile(FILENAME_O_1, "recreate");

	cout << " Run Here 2..." << endl;

	TString TREENAME_I = "st";
	TTree *TREE_I = FILE_I_1->Get(TREENAME_I);
	TTree *tree = TREE_I->CopyTree(cut_s);

	cout << " Run Here 3..." << endl;

	Int_t nentries = (Int_t)tree->GetEntries();

// --- Retrieve Data ---
	RooRealVar mBC("mBC", "mBC", 1.8400, 1.8865);
	RooDataSet *data = new RooDataSet("data", "data", tree, RooArgSet(mBC));
	RooRealVar m0("m0", "m0", 1.8865, 1.8865, 1.8865);
	RooRealVar c("c", "c", -13, -100, 100);

// ==================== / PDF Definition / ==================== //
// --- Truth Pdf ---
	RooKeysPdf *sigPDF = (RooKeysPdf*)(FILE_I_2->Get("sigPDF"));	

// --- Argus Background Pdf ---
	RooAbsPdf *bkgPDF = new RooArgusBG("bkgPDF", "bkgPDF", mBC, m0, c); 

// ==================== / Fit and Draw / ==================== //
	const int stepNum = 100;
	Double_t stepLength = (Double_t)(0.06/stepNum);
	Double_t loglikelihood = 0;
	Double_t offset = 0;
	Double_t sum_total = 0;
	Double_t sum_uplimit = 0;
	Double_t uplimit = 0;
	Double_t sigNum[stepNum];
	Double_t likelihood[stepNum];

	for(Int_t i=0; i<stepNum; i++){
// --- Signal + Background Pdf ---
		sigNum[i] = i*stepLength*nentries;	
		RooRealVar nsig("nsig", "#sig events", sigNum[i], sigNum[i], sigNum[i]);
		RooRealVar nbkg("nbkg", "#bkg events", 0.70*nentries, -1.0*nentries, 1.0*nentries);
		RooAddPdf sum("sum", "sum", RooArgList(*sigPDF, *bkgPDF), RooArgList(nsig, nbkg));

// --- Fit ---
		RooFitResult* r = sum.fitTo(*data, Extended(kTRUE),RooFit::Save(kTRUE));

// --- Calculate ---
		loglikelihood = r->minNll();
		if(i==0) offset = loglikelihood;
		loglikelihood -= offset; 
		likelihood[i] = exp(-loglikelihood);
		sum_total += likelihood[i];
	}

	Int_t j=0;
	while(sum_uplimit<0.9*sum_total){
		sum_uplimit += likelihood[j];
		j++;
	}
	uplimit = (sigNum[j-1] + sigNum[j])/2.0;

	cout << " The uplimit is " << uplimit << endl;	

//	--- Draw ---
	TGraph *gr1 = new TGraph(stepNum, sigNum, likelihood);
	
	TCanvas *c1 = new TCanvas("c1","c1",900,640);
	gPad->SetRightMargin(0.05);
	gr1->SetTitle("Uplimit of Signal Number");
	gr1->GetXaxis()->SetTitle("Signal Number");
	gr1->GetYaxis()->SetTitle("Normalized Likelihood");
	gr1->GetYaxis()->SetTitleOffset(1.2);
	gr1->Draw("AC*");
	
	TArrow *ar1 = new TArrow(uplimit, likelihood[j]+0.3, uplimit, likelihood[j]+0.1, 0.02, ">");
  ar1->SetFillColor(4);
  ar1->SetFillStyle(1001);
  ar1->SetLineColor(4);
  ar1->SetLineWidth(2);
  ar1->SetAngle(40);
	ar1->Draw();
	
	c1->Modified();	
	c1->Update();
   
	TString s1("N_obs < ");
	s1 += uplimit;
	s1 += " (90% CL)";
	TPaveText *pt1 = new TPaveText(0.6, 0.8, 0.95, 0.9, "brNDC");
  pt1->SetFillColor(10);
	pt1->AddText(s1);
  pt1->Draw();
  
	c1->Modified();
	c1->Update();

// --- Output Pdf ---
	TString FILENAME_O_2 = "/scratchfs/bes/xiaod/STDptoPiPi0EEAlg/root/inclusive/ana/inclusive.uplimit.s.pdf";
	c1->Print(FILENAME_O_2);
	tree->Write();
	c1->Write();

  return;
}
