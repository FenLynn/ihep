#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include "TFile.h"                                    
#include "TChain.h"
#include "TStyle.h"                                    
#include "TROOT.h"                                    
#include "TH1F.h"                      
#include "TTree.h" 
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TClonesArray.h" 
#include "TLatex.h" 

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooDataHist.h"
#include "RooRealVar.h"
#include "TMath.h"
#include "RooStats/RooStatsUtils.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "RooCBShape.h"
#include "RooPolynomial.h"
#include "RooChebychev.h"
#include "RooGaussian.h"
#include "RooFitResult.h"
#include "RooFFTConvPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"

using namespace RooFit;

void Fitrcpi_bkg() { 
gROOT->Reset();  
gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadBottomMargin(0.15);
gStyle->SetTitleSize(0.05,"xyz");
gStyle->SetLabelSize(0.05,"xyz");
gROOT->ProcessLine(".L RooWeightedBW.cxx++");

TFile *f1  =new TFile("FitDDpi0.root","READ");
TTree *chain  = (TTree*)f1->Get("save");

gStyle->SetOptStat(1001111);
Double_t xmin = 3.83;
//Double_t xmin = 3.85;
//Double_t xmax = 4.01;
Double_t xmax = 4.06;
Int_t bin = int((xmax-xmin)*1000/10+0.5);
cout<<"bin = "<<bin<<endl;

RooRealVar recoilpi0("Mrcpi0", "Recoil mass of #pi_{0} (GeV/c^{2})", xmin, xmax);

RooDataSet data("recoilpi0", "recoil mass of pi0", RooArgSet(recoilpi0));

Double_t nentries = chain->GetEntries();
Double_t mass_recoilpi0;
chain->SetBranchAddress("recoilpi0",&mass_recoilpi0);
for(int i=0; i<nentries; i++){
  chain->GetEntry(i);
  if(mass_recoilpi0>recoilpi0.getMin()&&mass_recoilpi0<recoilpi0.getMax()){
  recoilpi0.setVal(mass_recoilpi0);
  data.add(RooArgSet(recoilpi0));
 } 
}

Double_t tot = data.sumEntries();
//BW PDF
//RooRealVar mean("mean","Bw mass",3.900);//,3.88,3.91) ;
RooRealVar mean("mean","Bw mass",3.896,3.88,3.91) ;
RooRealVar width("width","BW width",0.011,0.0,0.1);
RooWeightedBW bw("bwFactor", "", recoilpi0, mean, width); 

//CB Function
RooRealVar mean1("mean1","mass mean",0.00233) ;
RooRealVar sigma("sigma","sigma of gauss",0.0098);
RooRealVar alpha("alpha","alpha",-0.666);
RooRealVar n("n","n",6.4);
RooCBShape cb("cb","crystal ball",recoilpi0,mean1,sigma,alpha,n);


//RooFFTConvPdf
RooFFTConvPdf bwxcb("bwxcb","bw convoluted cb",recoilpi0,bw,cb);


TFile *file  = new TFile("keyspdf.root");
RooKeysPdf *pdf_DD =(RooKeysPdf*)file->Get("pdf_DD");
RooKeysPdf *pdf_DDpi =(RooKeysPdf*)file->Get("pdf_DDpi");
RooKeysPdf *pdf_ISR =(RooKeysPdf*)file->Get("pdf_ISR");
RooKeysPdf *pdf_qqbar =(RooKeysPdf*)file->Get("pdf_qqbar");
//RooKeysPdf *pdf_hadron =(RooKeysPdf*)file->Get("pdf_hadron");
RooKeysPdf *pdf_PHSP =(RooKeysPdf*)file->Get("pdf_PHSP");

//RooRealVar nbkg("nbkg","num of bkg",0.3*tot,0,tot+100);
RooRealVar nbkg("nbkg","num of bkg",6,0,tot+100);
RooRealVar nDD("nDD","nDD",1./24*nbkg.getVal()) ;
RooRealVar nDDpi("nDDpi","nDDpi",16./24*nbkg.getVal()) ;
RooRealVar nISR("nISR","nISR",4./24*nbkg.getVal()) ;
RooRealVar nqqbar("nqqbar","nqqbar",3./24*nbkg.getVal()) ;
//RooRealVar nhadron("nhadron","nhadron",8./4080*nbkg.getVal()) ;

RooAddPdf bkgpdf("bkgpdf","bkgpdf",RooArgList(*pdf_DD,*pdf_DDpi,*pdf_ISR,*pdf_qqbar),RooArgList(nDD,nDDpi,nISR,nqqbar)) ;
//RooAddPdf bkgpdf("bkgpdf","bkgpdf",RooArgList(*pdf_DD,*pdf_DDpi),RooArgList(nDD,nDDpi)) ;



//Add PHSP PDF
RooRealVar Rcpi("Mrcpi0", "Recoil mass of #pi_{0}", xmin, xmax);

RooPlot* frame2 = Rcpi.frame(Bins(bin),Title("Recoil mass distribution of #pi_{0}"));
//RooKeysPdf 
//pdf_DD->plotOn(frame2);
pdf_ISR->plotOn(frame2);
new TCanvas("c1", "rcpiInvmass", 200, 10, 700, 500);

frame2->Draw();

new TCanvas("c2", "psipInvmass", 200, 10, 700, 500);

//Add the component
//RooRealVar nbwxcb("nsig","num of bw&cb",0.3*tot,0,tot+100);
RooRealVar nbwxcb("nsig","num of bw&cb",43,0,tot+100);
RooExtendPdf ebwxcb("ebwxcb","extended bwxcb pdf",bwxcb,nbwxcb);

//RooRealVar nphsp("nphsp","num of phsp",0.35*tot,0,tot+100);
RooRealVar nphsp("nphsp","num of phsp",53,0,tot+100);
RooExtendPdf ephsp("ephsp","extended phsp pdf",*pdf_PHSP,nphsp);

RooExtendPdf ebkg("ebkg","extended phsp pdf",bkgpdf,nbkg);
RooAddPdf sum("sum","bkg+bw",RooArgList(ebwxcb,ephsp,ebkg),RooArgList(nbwxcb,nphsp,nbkg));
//RooAddPdf sum("sum","bkg+bw",RooArgList(ephsp,ebkg),RooArgList(nphsp,nbkg));
//RooAddPdf sum("sum","bkg+bw",RooArgList(ephsp),RooArgList(nphsp));

sum.fitTo(data,Extended(kTRUE));

RooPlot* xframe = recoilpi0.frame(Bins(bin),Title("Recoil mass distribution of #pi_{0}"));
data.plotOn(xframe);
sum.plotOn(xframe,Components(bwxcb),LineStyle(kDashed),LineColor(kRed));
sum.plotOn(xframe,Components(*pdf_PHSP),LineStyle(kDashDotted),LineColor(9));
sum.plotOn(xframe,Components(bkgpdf),LineStyle(kDotted),LineColor(3));
//bw.plotOn(xframe);
//bw.paramOn(xframe,Layout(0.549, 0.90,0.72));
sum.plotOn(xframe);
sum.paramOn(xframe,Layout(0.549, 0.90,0.9));
//data.statOn(xframe,What("NMR"),Layout(0.549,0.90,0.36));
gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.3) ; xframe->Draw() ;
}
