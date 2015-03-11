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
#include "TString.h"
#include "RooCBShape.h"
#include "RooExtendPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "TFile.h"
#include "TTree.h"
#include "iostream"
#include "fstream"
using namespace RooFit ;


double* cball(TFile *fout,char* treename,double low,double high,double massu,double massh)
{
	//double reset[11];
	double reset[12];
	const char* filename="sigtree.root";
	

	RooRealVar ee("ee_ivm","ee_ivm",low,high) ;
	RooRealVar cbmean("cbmean","cbmean",low+0.07,low,high) ;
	RooRealVar cbsigma("cbsigma","cbsigma",0.005,0.001,0.01) ;
	RooRealVar n1("n1","n1",1.0,0.,10.);
	RooRealVar alpha("alpha","alpha",1.0,0.,10.);
	RooCBShape cball("cball","crystal ball",ee,cbmean,cbsigma,alpha,n1);

//	cout<<"filename:	"<<filename<<endl;
//	cout<<"treename:	"<<treename<<endl;
	
	TString br_tree=treename;
//	cout<<br_tree<<endl;

	TFile *file1 = new TFile(filename,"READ");
	TTree *tree1 =(TTree *)file1->Get(br_tree);

	if (!file1) cout<<"invalid file"<<endl;
	if (!tree1) cout<<"invalid tree"<<endl;
	
	//cout<<tree1->GetEntries()<<endl;	


	TString ncut="";
	ncut+="ee_ivm<";
	ncut+=high;
	ncut+="&&ee_ivm>";
	ncut+=low;
	
	//cout<<ncut<<endl;
	
	//int Nsignal=tree->GetEntries(ncut);
	
	int nentries=0;
	nentries=tree1->GetEntries(ncut);

	RooRealVar nsig("nsig","nsig",nentries,0,50000);
	RooExtendPdf model("model","esig",cball,nsig);

	RooDataSet signal("signal","signal",RooArgSet(ee),Import(*tree1));
	signal.Print();
	

	//nsig.setConstant(kTRUE);

	cout<<"Preparing ..."<<endl;
	model.fitTo(signal);
	cout<<"completed ..."<<endl;
	

	cout<<cbmean.getVal()<<endl;;
	//reset[0]=cbmean.getVal();
	

	reset[0]=cbmean.getVal();
	//cout<<reset[0]<<endl;
	reset[2]=cbsigma.getVal();
	reset[4]=alpha.getVal();
	reset[6]=n1.getVal();
	reset[8]=nsig.getVal();
	
	reset[1]=cbmean.getError();
	reset[3]=cbsigma.getError();
	reset[5]=alpha.getError();
	reset[7]=n1.getError();
	reset[9]=nsig.getError();
	
	reset[10]=double(nentries);
	reset[11]=cbmean.getVal();

	cout<<"reset complete"<<endl;

	RooPlot* xframe = ee.frame();
	xframe->SetName(treename);
	signal.plotOn(xframe);
	model.plotOn(xframe);
	model.paramOn(xframe);
	xframe->Draw();
	
//	fout->cd();
//	xframe->Write();

	return reset;
	
}


void mul_cball()
{
	cout<<"mul_cball  start"<<endl;
	double massu;
	double massh;
	
	TFile *fout=new TFile("outsig.root","RECREATE");
	TTree *tout=new TTree("siginfo","siginfo");
	
//	double reset[11];
	double *reset;
	double cbmean;
	double ecbmean;
	double cbsigma;
	double ecbsigma;
	double alpha;
	double ealpha;
	double n1;
	double en1;
	double nfit;
	double enfit;
	double nori;
	double eff;

	
	tout->Branch("massu",&massu,"massu/D");
	tout->Branch("massh",&massh,"massh/D");
//	tout->Branch("reset",reset,"reset/D");	
	
	tout->Branch("cbmean",&cbmean,"cbmean/D");
	tout->Branch("ecbmean",&ecbmean,"ecbmean/D");
	tout->Branch("cbsigma",&cbsigma,"cbsigma/D");
	tout->Branch("ecbsigma",&ecbsigma,"ecbsigma/D");
	tout->Branch("alpha",&alpha,"alpha/D");
	tout->Branch("ealpha",&ealpha,"ealpha/D");
	tout->Branch("n1",&n1,"n1/D");
	tout->Branch("en1",&en1,"en1/D");
	tout->Branch("nfit",&nfit,"nfit/D");
	tout->Branch("enfit",&enfit,"enfit/D");
	tout->Branch("nori",&nori,"nori/D");
	tout->Branch("eff",&eff,"eff/D");

	char* tree_file="tree.txt";
//	char* filename="sigtree.root";
	//char* filename="mee.root";
	
	double low=-1;
	double high=5;
	
	char* treename="";
	TString treetitle="";
	//cout<<"3"<<endl;

	ifstream inp;
	int t=0;
	inp.open(tree_file);
	while (inp>>massu>>massh>>treetitle>>treename)
	{
//		cout<<treetitle<<endl;
//		cout<<treename<<endl;
		if(t>12) break;

		low=massu-0.07;
		high=massu+0.03;
		cout<<massu<<"	"<<treename<<endl;
		reset=cball(fout,treename,low,high,massu,massh);
		
//		cout<<reset[0]<<endl<<reset[1]<<endl<<reset[2]<<endl;

		cbmean=reset[11];
		ecbmean=reset[1];
		cbsigma=reset[2];
		ecbsigma=reset[3];
		alpha=reset[4];
		ealpha=reset[5];
		n1=reset[6];
		en1=reset[7];
		nfit=reset[8];
		enfit=reset[9];
		nori=reset[10];

		eff=nfit*1.0/50000;

		tout->Fill();
		t++;
	}
	tout->AutoSave();
//	fout->Close();
}

