#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooFFTConvPdf.h"
#include "RooCBShape.h"
#include "RooVoigtian.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TTree.h"
using namespace RooFit;

void UpLimit()
{

Double_t low(0.88), high(1.02);

RooRealVar Inv_U("Inv_U","Inv_U",low,high);

//Get the MC shape
TFile *file1=new TFile("./result.root");
TTree* tree1 =(TTree*) file1-> Get("sig");
// read the tree into histogram
RooDataSet sigmc("sigmc", "", tree1, RooArgSet(Inv_U));
RooKeysPdf sig_shape("sig_shape", "", Inv_U, sigmc);


RooRealVar nsig("nsig","nsig",0);
RooExtendPdf esig("esig","esig",sig_shape,nsig);

RooRealVar p11("p11", "p11", 0, -1, 1);
RooRealVar p12("p12", "p12", 0, -1, 1);
RooChebychev bkg("bkg", "bkg", Inv_U, RooArgList(p11,p12));
RooRealVar nbkg("nbkg","nbkg",30,10,80);
RooExtendPdf ebkg("ebkg","ebkg",bkg,nbkg);

RooAddPdf model("model","",RooArgList(esig,ebkg),RooArgList(nsig,nbkg));

TFile *file=new TFile("./result.root");
TTree* tree =(TTree*) file-> Get("data");
// read the tree into histogram
RooDataSet data("data","dataset with Inv_U",tree,Inv_U);

// fit model to data

bool offset=false;
double offsetValue=0.;
ofstream outfile("likelihood.txt");

 for (int i=0;i<150;i++){
        double nsignal = i*0.1;
	nsig.setVal(nsignal);
        nsig.setConstant();

	nbkg.setVal(30);
	p11.setVal(0);

        RooFitResult* r = model.fitTo(data,RooFit::Save(kTRUE));
        r->Print("v");
        ofstream resultfile("results.txt",ofstream::out|ofstream::app);
        r->printStream(resultfile, r->defaultPrintContents(0), r->defaultPrintStyle(0));
        if(!offset) {
          offsetValue = r->minNll();
          outfile<<"#"<<"\t" << offsetValue << std::endl;
          offset = true;
        }
        double likelihood = r->minNll()-offsetValue;
        outfile<<i<<"\t" << likelihood << std::endl;
        }
 
}
