#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "fstream"
#include "LRoot.h"
using namespace RooFit;
using namespace std;

//====================================================================
//For upper limit culation
const char* outsig_file = "outsig.root";
const char* outsig_tree = "siginfo";
const char* file_mee = "./mee.root";
const int signal_shape_func = 3; // 1 for gauss, 2 for single cball,3 for multi cball

const double global_low = 0.4;
const double global_high = 2.0;
const int global_nsteps = 160;
double global_stepdiv = (global_high - global_low)/global_nsteps;

const int optfit = 1 ;// 1 for multi fit in range,signal shape and bk order; 0 for the normal single fit at every point
const int optrange = 1 ;// 1 for range change
const int optorder = 1 ;// 1 for order change
const int optshape = 1 ;// 1 for shape change

const int Nnum = 150;

ofstream likeli("likeli.txt",ios::app);

//0 for upper number of signal,1 for upper limit
//double up_value[2];

template <class T>
int getMax(T array[],int N)
{
	int maxi=0;
	int temp_maxi=0;
	T temp_max;
	T maxsig=-9999999.;
	for(int i=0;i<N-1;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			temp_max=temp_swap(array[i],array[j]);
			temp_maxi=array[i]>array[j]?i:j;	
			if(temp_max>maxsig) 
			{
				maxsig=temp_max;
				maxi=temp_maxi;
			}
		//	cout<<maxsig<<"     "<<maxi<<endl;
		}
	}
	return maxi;
}

template <class T>
T temp_swap(T a,T b)
{
	if(a>b) return a;
	else return b;
}

//=======================================================================================

void sfit(double fit_u, double fit_low,double fit_high,int bkg_ord, int sig_side,double up_value[] ){
	//get data mass(ee) spectrum
	TFile *fee = new TFile(file_mee,"READ");
	TTree *tee =(TTree *)fee->Get("data");
	if (!fee) cout<<"Invalid file:	"<<file_mee<<endl;
	if (!tee) cout<<"Invalid tree:	"<<"data"<<endl;
	//signal_shape_func:3 for multi cball
	if(signal_shape_func == 3)
	{
		//get signal shape info from tree
		TFile *fsig=new TFile(outsig_file,"READ");
		TTree *tsig=(TTree*)fsig->Get(outsig_tree);
		if (!fsig) cout<<"Invalid file:	"<<outsig_file<<endl;
		if (!tsig) cout<<"Invalid tree:	"<<outsig_tree<<endl;
		// List of variable
		Double_t        massu;
		Double_t        massh;
		Double_t        cbmean;
		Double_t        ecbmean;
		Double_t        cbsigma;
		Double_t        ecbsigma;
		Double_t        alpha;
		Double_t        ealpha;
		Double_t        n1;
		Double_t        en1;
		Double_t        nfit;
		Double_t        enfit;
		Double_t        nori;
		Double_t        eff;
		// List of branches
		TBranch        *b_massu;   //!
		TBranch        *b_massh;   //!
		TBranch        *b_cbmean;   //!
		TBranch        *b_ecbmean;   //!
		TBranch        *b_cbsigma;   //!
		TBranch        *b_ecbsigma;   //!
		TBranch        *b_alpha;   //!
		TBranch        *b_ealpha;   //!
		TBranch        *b_n1;   //!
		TBranch        *b_en1;   //!
		TBranch        *b_nfit;   //!
		TBranch        *b_enfit;   //!
		TBranch        *b_nori;   //!
		TBranch        *b_eff;   //!
		tsig->SetBranchAddress("massu", &massu, &b_massu);
		tsig->SetBranchAddress("massh", &massh, &b_massh);
		tsig->SetBranchAddress("cbmean", &cbmean, &b_cbmean);
		tsig->SetBranchAddress("ecbmean", &ecbmean, &b_ecbmean);
		tsig->SetBranchAddress("cbsigma", &cbsigma, &b_cbsigma);
		tsig->SetBranchAddress("ecbsigma", &ecbsigma, &b_ecbsigma);
		tsig->SetBranchAddress("alpha", &alpha, &b_alpha);
		tsig->SetBranchAddress("ealpha", &ealpha, &b_ealpha);
		tsig->SetBranchAddress("n1", &n1, &b_n1);
		tsig->SetBranchAddress("en1", &en1, &b_en1);
		tsig->SetBranchAddress("nfit", &nfit, &b_nfit);
		tsig->SetBranchAddress("enfit", &enfit, &b_enfit);
		tsig->SetBranchAddress("nori", &nori, &b_nori);
		tsig->SetBranchAddress("eff", &eff, &b_eff);

		int Nevt = tsig->GetEntries();
		int ishape = -1;
		int nearest_shape = -1;

		for(int i=0;i<Nevt;i++)
		{
			tsig->GetEntry(i);
			if(fit_u <= massu)
			{
				if(i==0) nearest_shape = 0;
				else
				{
					if( fabs(massu-fit_u) < 0.05) nearest_shape = i;
					else nearest_shape = i-1;

					if(nearest_shape < 0) nearest_shape = 0;
				}
			}
			else if(i== Nevt-1)
			{
				nearest_shape = Nevt-1;
			}
			else{continue;}
		}

		ishape = nearest_shape + sig_side;

		if(ishape < 0) ishape = 0;
		if(ishape > Nevt-1) ishape = Nevt-1;
		tsig->GetEntry(ishape);
		double par_sigma = cbsigma;
		double par_n1 = n1;
		double par_alpha = alpha;
		double par_eff = eff;

		//for varible
		//RooRealVar ee_ivm("ee_ivm","ee_ivm",global_low,global_high);
		RooRealVar ee_ivm("ee_ivm","ee_ivm",fit_low,fit_high);
		//for background
		RooRealVar a1("a1","coefficient a#1",0.1,-1.,1.);
		RooRealVar a2("a2","coefficient a#2",0.001,-1.,1.); 
		RooRealVar a3("a3","coefficient a#3",0.004,-1.,1.);
		RooRealVar a4("a4","coefficient a#4",0.004,-1.,1.);

		RooChebychev *bkg;
		if(bkg_ord == 2)  bkg=new RooChebychev("bkg","bkg",ee_ivm,RooArgList(a1,a2));
		else if(bkg_ord == 3) bkg = new RooChebychev("bkg","bkg",ee_ivm,RooArgList(a1,a2,a3));
		else if(bkg_ord == 4) bkg = new RooChebychev("bkg","bkg",ee_ivm,RooArgList(a1,a2,a3,a4));
		else if(bkg_ord == 1) bkg = new RooChebychev("bkg","bkg",ee_ivm,RooArgList(a1));
		else {cout<<"Wrong set for background order!"<<endl;return;}

		//for signal shape
		RooRealVar fit_mean("mean","mean",fit_low,fit_high) ;
		RooRealVar fit_sigma("sigma","sigma",par_sigma) ;
		RooRealVar fit_n1("n1","n1",par_n1);
		RooRealVar fit_alpha("alpha","alpha",par_alpha);
		fit_sigma.setConstant();
		fit_n1.setConstant();
		fit_alpha.setConstant();
		RooCBShape cball("cball","crystal ball",ee_ivm,fit_mean,fit_sigma,fit_alpha,fit_n1);

		RooRealVar nbkg("nbkg","nbkg",100,0,20000);
		RooRealVar nsig("nsig","nsig",0);

		RooDataSet data("data","data with Mee",tee,ee_ivm);
		RooAddPdf model("model","sig+bkg",RooArgList(cball,*bkg),RooArgList(nsig,nbkg));

		double F[Nnum],S[Nnum],Num[Nnum];
		for(int n=0;n<Nnum;n++){
			nsig.setVal(n);
			nsig.setConstant();

			RooFitResult* r = model.fitTo(data,RooFit::Save(kTRUE));
			r->Print("v");
			double like = r->minNll();
			F[n] = -1.*like;
		}

		double offset = 0;
		for(int i=0;i<Nnum;i++){
			S[i] = TMath::Exp(F[i]+offset);
			Num[i] = i;
			likeli<<Num[i]<<" "<<F[i]<<" "<<S[i]<<endl;
		}


		double up_sig = -1.;
		double up_limit = -1.;
		up_value[0] = up_sig;
		up_value[1] = up_limit;
		/*
		   TCanvas *c = new TCanvas("c","upper limit");
		   TGraph *gr = new TGraph(Nnum,Num,S);
		   c->cd();
		   gr->Draw();
		   */
		/*	
			RooPlot* eeframe=ee_ivm.frame();
			data.plotOn(eeframe);
			eeframe->Draw();
			*/
	}
}


void mfit(){
	//sfit(0.8,0.7,0.9);
	int iee=0;
	double mass=0.;
	double up_value[2];

	const double mf_len[3]={0.05,0.1,0.15};
	const int mf_shape[3]={-1,0,1};
	const int mf_bkg[4]={1,2,3,4};
	double tupsig[global_nsteps],tuplimit[global_nsteps];
	double q_upsig[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	double q_uplimit[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	double temp_low,temp_high;
	int temp_shape,temp_bkg;

	for(iee=0;iee<global_nsteps;iee++){
		mass=iee*global_stepdiv;
		if(optfit == 0)
		{
			temp_low=mass-mf_len[1];
			temp_high=mass+mf_len[1];
			temp_bkg=mf_bkg[1];
			temp_shape=mf_shape[1];
			sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
			tupsig[iee]=up_value[0];
			tuplimit[iee]=up_value[1];
		}
		else
		{
			if(optrange == 1)
			{
				//for normale range
				temp_low=mass-mf_len[1];
				temp_high=mass+mf_len[1];
				temp_bkg=mf_bkg[1];
				temp_shape=mf_shape[1];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
				q_upsig[0]=up_value[0];
				q_uplimit[0]=up_value[1];
				//for large range
				temp_low=mass-mf_len[2];
				temp_high=mass+mf_len[2];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
				q_upsig[1]=up_value[0];
				q_uplimit[1]=up_value[1];
				//for small range
				temp_low=mass-mf_len[0];
				temp_high=mass+mf_len[0];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
				q_upsig[2]=up_value[0];
				q_uplimit[2]=up_value[1];
			}
			if(optshape == 1)
			{
				//for normale range
				if(q_upsig[0] == -1)
				{
					temp_low=mass-mf_len[1];
					temp_high=mass+mf_len[1];
					temp_bkg=mf_bkg[1];
					temp_shape=mf_shape[1];
					sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
					q_upsig[0]=up_value[0];
					q_uplimit[0]=up_value[1];
				}
				temp_low=mass-mf_len[1];
				temp_high=mass+mf_len[1];
				temp_bkg=mf_bkg[1];

				temp_shape=mf_shape[0];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
				q_upsig[3]=up_value[0];
				q_uplimit[3]=up_value[1];
				
				temp_shape=mf_shape[2];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
				q_upsig[4]=up_value[0];
				q_uplimit[4]=up_value[1];
			}
			if(optorder == 1)
			{
				//for normal order 2
				if(q_upsig[0] == -1)
				{
					temp_low=mass-mf_len[1];
					temp_high=mass+mf_len[1];
					temp_bkg=mf_bkg[1];
					temp_shape=mf_shape[1];
					sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
					q_upsig[0]=up_value[0];
					q_uplimit[0]=up_value[1];
				}
				temp_low=mass-mf_len[1];
				temp_high=mass+mf_len[1];
				temp_shape=mf_shape[1];
				//for normal order 3
				temp_bkg=mf_bkg[2];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value);
				q_upsig[5]=up_value[0];
				q_uplimit[4]=up_value[1];
			}
		}
		int maxi = getMax(q_upsig,10);
		tupsig[iee] = q_upsig[maxi];
		tuplimit[iee] = q_uplimit[maxi];

	}
}


