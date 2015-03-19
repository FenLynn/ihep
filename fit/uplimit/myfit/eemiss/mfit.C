#include "/workfs/bes/lify/myinclude/rootult.h"
using namespace RooFit;
using namespace std;

//====================================================================
//For upper limit culation


//input signal info. 
const char* insig_file = "/besfs/users/lify/Root/Eemiss_v4/fit/myfit/include/run1/outsig.root";
const char* insig_tree = "siginfo";
//input data invariant mass 
const char* file_mee = "/besfs/users/lify/Root/Eemiss_v4/fit/myfit/include/run1/mee.root";
//output temp plot to check
const char* out_ckfit="/besfs/users/lify/Root/Eemiss_v4/fit/myfit/include/run1/ckfit.root";
TFile *f_ckfit=new TFile(out_ckfit,"RECREATE");
//output likelihood plot and total upper limit
const char* out_final="/besfs/users/lify/Root/Eemiss_v4/fit/myfit/include/run1/final.root";
TFile *f_final=new TFile(out_final,"RECREATE");


// 1 for gauss, 2 for single cball,3 for multi cball
const int signal_shape_func = 3; 
//set for opt in range,bkg,sig shape
const int optfit = 0 ;// 1 for multi fit in range,signal shape and bk order; 0 for the normal single fit at every point
const int optrange = 1 ;// 1 for range change,0 for none
const int optorder = 1 ;// 1 for order change,0 for none
const int optshape = 1 ;// 1 for shape change,0 for none

//global fit set
const double global_low = 0.4;
const double global_high = 2.0;
const int global_nsteps = 160;
double global_stepdiv = (global_high - global_low)/global_nsteps;

//max number of signal in fit
const int maxfit = 150;
const double fit_div = 1.;
const int out_saveresult = 1;
const int out_savelikelihood = 1;
const int out_savefit = 1;
const int out_savefitopt = 1;
const int out_savellUL = 1;
//input systemactic uncertainity
const double par_sys_sigma = 0.1;

//output likelihood txt info
ofstream likeli("/besfs/users/lify/Root/Eemiss_v4/fit/myfit/include/run1/likelihood.txt",ios::app);
ofstream resultfile("/besfs/users/lify/Root/Eemiss_v4/fit/myfit/include/run1/results.txt");
//ofstream resultfile("results.txt",ofstream::out|ofstream::app);

//for debug
const int _debug = 1;
ofstream mydebug("/besfs/users/lify/Root/Eemiss_v4/fit/myfit/include/run1/mydebug.txt");
//ofstream mydebug("mydebug.txt",ios::app);


//=======================================================================================
double like(double y1[],TString br_mass)
{
	double x[maxfit];
	double y[maxfit];
	double offset = 0.;
	TH1F* yy=new TH1F("yy","yy",maxfit,0,maxfit*fit_div);
	for(int i=0;i<maxfit;i++){
		x[i]=i*fit_div;
		y[i]=TMath::Exp(-1.*y1[i]+offset);
		//mydebug<<"likeli:	"<<x[i]<<" "<<y1[i]<<" "<<y[i]<<endl;
		yy->SetBinContent(i,y[i]);
	}
	//for convolution
	RooRealVar xx("xx","xx",0,maxfit*fit_div);
	RooDataHist llhood("llhood","llhood",xx,yy);
	RooHistPdf llhoodpdf("llhoddpdf","likelihood pdf",xx,llhood,2);
	//system unertainity gausssian
	RooRealVar sys_sigma("sys_sigma","sys_sigma",par_sys_sigma);
	RooRealVar sys_mean("sys_mean","sys_mean",0.);
	//sys_mean.setConstant();
	RooGaussian sys_gauss("sys_gauss","gauss",xx,sys_mean,sys_sigma);
	xx.setBins(1000,"cache");
	RooFFTConvPdf llhg("llhg","likelihood convoluted gauss",xx,llhoodpdf,sys_gauss);
	RooAbsReal* llhg_cdf = llhg.createCdf(xx); 
	double _90upsig=llhg_cdf->findRoot(xx,0,maxfit*fit_div,0.90);
	if(out_savellUL == 1){
		TArrow *ar = new TArrow(_90upsig, 0.02, _90upsig, 0., 0.01,"|>");
		TLatex ltx(_90upsig,0.018,Form("N_{signal} = %.2f @90 C.L.",_90upsig));
		RooPlot *xxframe=xx.frame();
		llhg.plotOn(xxframe,LineStyle(1),LineColor(kRed));
		llhoodpdf.plotOn(xxframe,LineStyle(kDashed),LineColor(kGreen));
		TCanvas *c=new TCanvas("c","c");
		c->SetName(br_mass);
		c->SetTitle(br_mass);
		c->cd();
		xxframe->Draw();
		ar->DrawClone();
		ltx.DrawClone();
		f_final->cd();
		c->Write();
	}
	return _90upsig;
}

double cal_ul(double upsig,double eff){
	const double Njpsi= 1086.9e6;
//	const double eNjpsi = 6.0e6;
	const double delta_sys = 0.;
	const int _normal = 0;
	double ul_br = -1.;
	if(_normal == 1){
		ul_br=upsig/(Njpsi*eff*(1-delta_sys));
	}
	else
	{
		ul_br=upsig/(Njpsi*eff);
	}
	return ul_br;
}

void sfit(double fit_u, double fit_low,double fit_high,int bkg_ord, int sig_side,double up_value[],TString br_mass ){

	double like_array[maxfit];

	TFile *fee = new TFile(file_mee,"READ");
	TTree *tee =(TTree *)fee->Get("data");

	if (!fee) cout<<"Invalid file:	"<<file_mee<<endl;
	if (!tee) cout<<"Invalid tree:	"<<"data"<<endl;

	if(signal_shape_func == 3)
	{
		TFile *fsig=new TFile(insig_file,"READ");
		TTree *tsig=(TTree*)fsig->Get(insig_tree);
		if (!fsig) cout<<"Invalid file:	"<<insig_file<<endl;
		if (!tsig) cout<<"Invalid tree:	"<<insig_tree<<endl;
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
		RooRealVar nbkg("nbkg","nbkg",100,0,20000);
		RooExtendPdf ebkg("ebkg","ebkg",*bkg,nbkg);

		//for signal shape
		RooRealVar fit_mean("mean","mean",fit_low,fit_high) ;
		RooRealVar fit_sigma("sigma","sigma",par_sigma) ;
		RooRealVar fit_n1("n1","n1",par_n1);
		RooRealVar fit_alpha("alpha","alpha",par_alpha);
		fit_sigma.setConstant();
		fit_n1.setConstant();
		fit_alpha.setConstant();
		RooCBShape cball("cball","crystal ball",ee_ivm,fit_mean,fit_sigma,fit_alpha,fit_n1);
		RooRealVar nsig("nsig","nsig",0,200);
		RooExtendPdf ecball("ecball","ecball",cball,nsig);

		RooDataSet data("data","data with Mee",tee,ee_ivm);
		RooAddPdf model("model","sig+bkg",RooArgList(ecball,ebkg),RooArgList(nsig,nbkg));

		//fit beginc----------------------------------------------------------------------------------------		
		bool offset=false;
		double offsetValue=0.;
		for (int i=0;i<maxfit;i++){
			double nsignal = i*fit_div;
			nsig.setVal(nsignal);
			nsig.setConstant();
			RooFitResult* r = model.fitTo(data,RooFit::Save(kTRUE));
			r->Print("v");
			if( out_saveresult == 1){	
				r->printStream(resultfile, r->defaultPrintContents(0), r->defaultPrintStyle(0));
			}
			if(!offset) {
				offsetValue = r->minNll();
				//outfile<<"#"<<"\t" << offsetValue << std::endl;
				offset = true;
			}
			double likelihood = r->minNll()-offsetValue;
			like_array[i]=likelihood;

			if( out_savelikelihood == 1){
				likeli<<i<<"\t" << likelihood << std::endl;
			}
			if( out_savefit == 1){
				//if( out_savefitopt == 1){
				//	if(!(((fit_high - fit_low) == 0.2) &&  bkg_ord ==2 && sig_side == 0)) continue ;
				//}
				RooPlot* eeframe=ee_ivm.frame();
				data.plotOn(eeframe);
				model.plotOn(eeframe,Components(ecball),LineStyle(kDashed),LineColor(kGreen));
				model.plotOn(eeframe,Components(ebkg),LineStyle(kDot),LineColor(kBlue));
				model.plotOn(eeframe,LineColor(kRed));
				model.paramOn(eeframe);
				f_ckfit->cd(br_mass);
				eeframe->Write();
			}
			
		}
		double up_sig = -1.;
		double up_limit = -1.;
		up_sig=like(like_array,br_mass);
		up_limit=cal_ul(up_sig,par_eff);
		mydebug<<"original:	"<<up_sig<<" "<<up_limit<<endl;
		up_value[0] = up_sig;
		up_value[1] = up_limit;
		/*
		if(_debug == 1){
			mydebug<<endl;
			mydebug<<up_sig<<endl;
			mydebug<<up_limit<<endl;
		}
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
	double mass_array[global_nsteps],tupsig[global_nsteps],tuplimit[global_nsteps];
	double q_upsig[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	double q_uplimit[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	double temp_low,temp_high;
	int temp_shape,temp_bkg;

	for(iee=0;iee<global_nsteps;iee++){
		//if(iee > 50 || (iee%10!=0) ) continue;
		//if(iee!=120 ) continue;
		mass=global_low+iee*global_stepdiv;
		TString br_mass="";
		br_mass+="mee";
		br_mass+=Form("%.2f",mass);
		f_ckfit->mkdir(br_mass);
		if(optfit == 0)
		{
			temp_low=mass-mf_len[1];
			temp_high=mass+mf_len[1];
			temp_bkg=mf_bkg[1];
			temp_shape=mf_shape[1];
			sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
			tupsig[iee]=up_value[0];
			tuplimit[iee]=up_value[1];
			if(_debug == 1){
				mydebug<<mass<<endl;
				mydebug<<temp_low<<endl;
				mydebug<<temp_high<<endl;
				mydebug<<temp_bkg<<endl;
				mydebug<<temp_shape<<endl;
				mydebug<<br_mass<<endl;
				mydebug<<tupsig[iee]<<endl;
				mydebug<<tuplimit[iee]<<endl<<endl;
			}
		}
		else
		{
			int maxi = -1;
			if(optrange == 1)
			{
				//for normale range
				temp_low=mass-mf_len[1];
				temp_high=mass+mf_len[1];
				temp_bkg=mf_bkg[1];
				temp_shape=mf_shape[1];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
				q_upsig[0]=up_value[0];
				q_uplimit[0]=up_value[1];
				//for large range
				temp_low=mass-mf_len[2];
				temp_high=mass+mf_len[2];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
				q_upsig[1]=up_value[0];
				q_uplimit[1]=up_value[1];
				//for small range
				temp_low=mass-mf_len[0];
				temp_high=mass+mf_len[0];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
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
					sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
					q_upsig[0]=up_value[0];
					q_uplimit[0]=up_value[1];
				}
				temp_low=mass-mf_len[1];
				temp_high=mass+mf_len[1];
				temp_bkg=mf_bkg[1];

				temp_shape=mf_shape[0];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
				q_upsig[3]=up_value[0];
				q_uplimit[3]=up_value[1];

				temp_shape=mf_shape[2];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
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
					sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
					q_upsig[0]=up_value[0];
					q_uplimit[0]=up_value[1];
				}
				temp_low=mass-mf_len[1];
				temp_high=mass+mf_len[1];
				temp_shape=mf_shape[1];
				//for normal order 3
				temp_bkg=mf_bkg[2];
				sfit(mass,temp_low,temp_high,temp_bkg,temp_shape,up_value,br_mass);
				q_upsig[5]=up_value[0];
				q_uplimit[4]=up_value[1];
			}
			maxi = getMaxIndex(q_upsig,10);
			tupsig[iee] = q_upsig[maxi];
			tuplimit[iee] = q_uplimit[maxi];
		}

	}
	TGraph *g_upsig = new TGraph(global_nsteps,mass_array,tupsig);
	TGraph *g_uplimit = new TGraph(global_nsteps,mass_array,tuplimit);

	f_final->cd();
	g_upsig->Write();
	g_uplimit->Write();
	
	f_ckfit->Close();
	f_final->Close();

}


