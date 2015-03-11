//////////////////////////////////////////////////////////////////////////
//
// 'BASIC FUNCTIONALITY' RooFit tutorial macro #101
// 
// Fitting, plotting, toy data generation on one-dimensional p.d.f
//
// pdf = gauss(x,m,s) 
//
//
// 07/2008 - Wouter Verkerke 
// 
/////////////////////////////////////////////////////////////////////////

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "RooKeysPdf.h"
using namespace RooFit ;


void cball()
{
//	TFile *f=new TFile("out.root","RECREATE");

	TFile *file = new TFile("sigtree.root","READ");
	TTree *tree =(TTree *)file->Get("u07_h06");
	//RooRealVar ee("ee_ivm","ee_ivm",1.4,1.65) ;
	
	RooRealVar ee("ee_ivm","ee_ivm",0.60,0.72) ;
/*	
	RooRealVar cbmean("cbmean","cbmean",0.7,0.55,0.75) ;
	RooRealVar cbsigma("cbsigma","cbsigma",0.005,0.001,0.01) ;
	RooRealVar n1("n1","n1",1.0,0.,10.);
	RooRealVar alpha("alpha","alpha",1.0,0.,10.);
	
	RooCBShape cball("cball","crystal ball",ee,cbmean,cbsigma,alpha,n1);
*/
//	RooRealVar nsig("nsig","nsig",2935,0,5000);
	RooDataSet signal("signal","signal",RooArgSet(ee),Import(*tree));
	
//	RooKeysPdf kpdf("kpdf","kpdf",RooArgSet(ee),signal, RooKeysPdf::NoMirror,2.4);
	RooKeysPdf kpdf("kpdf","kpdf",ee,signal);

//	RooExtendPdf model("model","esig",cball,nsig);

	signal.Print();
	


	//nsig.setConstant(kTRUE);

	kpdf.fitTo(signal);
/*	
	cout<<cbmean.getVal()<<endl;;
	cout<<cbsigma.getVal()<<endl;;
	cout<<alpha.getVal()<<endl;;
	cout<<n1.getVal()<<endl;;
	cout<<nsig.getVal()<<endl;;
	cout<<cbmean.getError()<<endl;;
	cout<<cbsigma.getError()<<endl;;
	cout<<alpha.getError()<<endl;;
	cout<<n1.getError()<<endl;;
	cout<<nsig.getError()<<endl;;
*/	
//	TCanvas *c=new TCanvas("c","c");
//	c->cd();
	kpdf.SaveAs("a.root");
	RooPlot* xframe = ee.frame();
	xframe->SetName("test signal");
	signal.plotOn(xframe);
	kpdf.plotOn(xframe);
	//.paramOn(xframe);
	xframe->Draw();

//	f->cd();
//	xframe->Write();
//	f->Close();
}
