#include "/workfs/bes/lify/myinclude/rootult.h"
using namespace RooFit;
using namespace std;

TString LOCALPATH="/besfs/users/lify/Root/Eemiss_v4/fit/normal/h08/";

//====================================================================
//For upper limit culation


//input signal info. 
//const char* insig_file = LOCALPATH+"outsig.root";
TString insig_file(LOCALPATH+"outsig.root");
const char* insig_tree = "siginfo";
//input data invariant mass 
TString file_mee(LOCALPATH+"mee.root");
//output temp plot to check
TString out_ckfit(LOCALPATH+"ckfit.root");
TFile *f_ckfit=new TFile(out_ckfit,"RECREATE");
//output likelihood plot and total upper limit
TString out_final(LOCALPATH+"final.root");
TFile *f_final=new TFile(out_final,"RECREATE");

// 1 for gauss, 2 for single cball,3 for multi cball
const int signal_shape_func = 3; 
//set for opt in range,bkg,sig shape
const int optfit = 1;// 1 for multi fit in range,signal shape and bk order; 0 for the normal single fit at every point
const int optrange = 1 ;// 1 for range change,0 for none
const int optorder = 1 ;// 1 for order change,0 for none
const int optshape = 1 ;// 1 for shape change,0 for none
const int _normal = 1;  //0 for no convolution,1 for convolution

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
ofstream likeli(LOCALPATH+"likelihood.txt",ios::app);
ofstream resultfile(LOCALPATH+"results.txt");

ofstream upsigtxt(LOCALPATH+"upsig.txt");
ofstream uplimittxt(LOCALPATH+"uplimit.txt");

//for debug
const int _debug = 1;
ofstream mydebug(LOCALPATH+"mydebug.txt");


//=======================================================================================
double like(double y1[],TString br_mass,TString br_mass_title)
{
	TCanvas *c1=new TCanvas("c1","c1",1333,500);
	TPad **pad = GenPad();
//	TCanvas *c2=new TCanvas("c2","c2");
	double x[maxfit];
	double y[maxfit];
	double like_sum = 0.;
	double offset = 0.;
//	TH1F* yy=new TH1F("yy","yy",maxfit,0,maxfit*fit_div);
	for(int i=0;i<maxfit;i++){
		x[i]=i*fit_div;
		y[i]=TMath::Exp(-1.*y1[i]+offset);
		like_sum+=fit_div*y[i];
		//mydebug<<"likeli:	"<<x[i]<<" "<<y1[i]<<" "<<y[i]<<endl;
//		yy->SetBinContent(i,y[i]);
	}

	RooRealVar xx("xx","xx",0,maxfit*fit_div);
	//	RooDataHist llhood("llhood","llhood",xx,yy);
	//	RooHistPdf llhoodpdf("llhoddpdf","likelihood pdf",xx,llhood,2);


	/*
	   RooRealVar fitl_sigma("fitl_sigma","fitl_sigma",maxfit*fit_div/2.,0,maxfit*fit_div);
	   RooRealVar fitl_mean("fitl_mean","fitl_mean",maxfit*fit_div/2.,0,maxfit*fit_div);
	   RooGaussian fitl_gauss("fitl_gauss","fitl_gauss",xx,fitl_mean,fitl_sigma);
	   RooFitResult* r_gauss = fitl_gauss.fitTo(llhood,RooFit::Save(kTRUE));
	   */

	//sys_mean.setConstant();
	//	xx.setBins(1000,"cache");

	//	RooAbsReal* llhg_cdf = llhoodpdf.createCdf(xx); 

	TF1 *g1    = new TF1("g1","gaus",0,maxfit*fit_div);
	g1->SetParameters(1.e+22,5.0,2.3);  
	g1->SetLineColor(2);
	TGraph *gr = new TGraph(maxfit,x,y);
	gr->SetLineColor(2);
	gr->SetLineWidth(2);
	gr->SetMarkerColor(4);
	gr->SetMarkerSize(0.7);
	gr->SetMarkerStyle(8);
	gr->SetTitle(" ");
	gr->GetXaxis()->SetTitle("N");
	gr->GetYaxis()->SetTitle("Normalized Likelihood");
	gr->Fit("g1","R");
//	gr->Draw("ap");
	
	double gpar[3];
	gpar[0]=g1->GetParameter(0);
	gpar[1]=g1->GetParameter(1);
	gpar[2]=g1->GetParameter(2);

	RooRealVar like_mean("like_mean","like_mean",gpar[1]);
	RooRealVar like_sigma("like_sigma","like_sigma",gpar[2]);
	RooGaussian like_gauss("like_gauss","like_gauss",xx,like_mean,like_sigma);
	//system unertainity gausssian
	
	double _90upsig=-1.;
	RooFFTConvPdf *llhg;
	RooAbsReal* llhg_cdf; 
	RooAbsReal* like_cdf = like_gauss.createCdf(xx); 
	if(_normal == 0){
		RooRealVar sys_mean("sys_mean","sys_mean",0.);
		RooRealVar sys_sigma("sys_sigma","sys_sigma",par_sys_sigma);
		RooGaussian sys_gauss("sys_gauss","sys_gauss",xx,sys_mean,sys_sigma);
		llhg=new RooFFTConvPdf("llhg","likelihood convoluted gauss",xx,like_gauss,sys_gauss);
		llhg_cdf = llhg->createCdf(xx); 
		_90upsig=llhg_cdf->findRoot(xx,0,maxfit*fit_div,0.90);
	}
	else{
		_90upsig=like_cdf->findRoot(xx,0,maxfit*fit_div,0.90);
	}
	
/*
	double temp_sum = 0.;
	double _90upsig = -1.;
	for(int i=0;i<maxfit;i++)
	{
		temp_sum+=y[i]*fit_div;
		if(temp_sum >= 0.90*like_sum) 
		{
			_90upsig = i;
			break;
		}
	}
*/
	if(out_savellUL == 1){
		TArrow *ar = new TArrow(_90upsig, 1, _90upsig, 0., 0.01,"|>");
		ar->SetLineWidth(3);
		ar->SetFillColor(1);
		TArrow *ar1 = new TArrow(_90upsig, 0.02, _90upsig, 0., 0.01,"|>");
		ar1->SetLineWidth(3);
		ar1->SetFillColor(1);
	
		TLatex ltx(0.5,0.8,Form("N_{signal} = %.2f @90%% C.L.",_90upsig));
		ltx.SetTextFont(62);
		ltx.SetTextColor(2);
		ltx.SetTextSize(0.04);
		ltx.SetNDC();
		TLegend *leg1=ModLeg(0.5,0.6,0.7,0.72);
		TLegend *leg2=ModLeg(0.5,0.6,0.7,0.72);

		RooPlot *xxframe=xx.frame();
		RooPlot *xx1frame=xx.frame();
		c1->SetName(br_mass_title);
		c1->SetTitle(br_mass_title);
		if(_normal==0){
			llhg->plotOn(xxframe,LineStyle(1),LineColor(kRed),RooFit::Name("llhg"));
			llhg_cdf->plotOn(xx1frame,LineStyle(1),LineColor(kRed),RooFit::Name("llhg_cdf"));
			leg1->AddEntry(xxframe->findObject("llhg"),"Likelihood with Convolution");
			leg1->AddEntry(xxframe->findObject("like_gauss"),"Likelihood without Convolution");
			leg2->AddEntry(xx1frame->findObject("llhg_cdf"),"Cdf with Convolution");
			leg2->AddEntry(xx1frame->findObject("like_cdf"),"Cdf without Convolution");
		}
		like_gauss.plotOn(xxframe,LineStyle(kDashed),LineColor(kBlue),RooFit::Name("like_gauss"));
		like_cdf->plotOn(xx1frame,LineStyle(kDashed),LineColor(kBlue),RooFit::Name("like_cdf"));
		pad[0]->cd();	
		pad[0]->SetGrid();
		xxframe->Draw();
		ar1->DrawClone();
		ltx.DrawClone();
//		leg1->DrawClone();
		NameAxis(xxframe,"N_{signal}","Likelihood","Fitting likelihood for "+br_mass);

		pad[1]->cd();
		pad[1]->SetGrid();
		xx1frame->Draw();
		ar->DrawClone();
		ltx.DrawClone();
//		leg2->DrawClone();
		NameAxis(xx1frame,"N_{signal}","Integration","Fitting Cdf for "+br_mass);
		f_final->cd(br_mass);
		c1->Write();
	}
	return _90upsig;
}

double cal_ul(double upsig,double eff){
	const double Njpsi= 1086.9e6;
	//	const double eNjpsi = 6.0e6;
	const double delta_sys = 0.1;
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
		//fixed signal shape
		fit_sigma.setConstant();
		fit_n1.setConstant();
		fit_alpha.setConstant();
		//fixed fit mean
		fit_mean.setVal(fit_u);
		fit_mean.setConstant();

		RooCBShape cball("cball","crystal ball",ee_ivm,fit_mean,fit_sigma,fit_alpha,fit_n1);
		RooRealVar nsig("nsig","nsig",0,200);
		RooExtendPdf ecball("ecball","ecball",cball,nsig);

		RooDataSet data("data","data with Mee",tee,ee_ivm);
		RooAddPdf model("model","sig+bkg",RooArgList(ecball,ebkg),RooArgList(nsig,nbkg));

		TString br_mass_title="";
		br_mass_title+=br_mass;
		br_mass_title+="_";
		br_mass_title+=Form("%.2f",fit_high-fit_low);
		br_mass_title+="_";
		br_mass_title+=bkg_ord;
		br_mass_title+="_";
		br_mass_title+=sig_side;
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
				TString eeframe_title="";
				eeframe_title+=br_mass_title;
				eeframe_title+=Form("_%.2f",nsignal);
				eeframe->SetName(eeframe_title);
				eeframe->Write();
			}

		}
		double up_sig = -1.;
		double up_limit = -1.;
		

		up_sig=like(like_array,br_mass,br_mass_title);
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
	SetMyStyle();
	int iee=0;
	double mass=0.;
	double up_value[2];

	const double mf_len[3]={0.05,0.1,0.15};
	const int mf_shape[3]={-1,0,1};
	const int mf_bkg[4]={1,2,3,4};
	double mass_array[global_nsteps],tupsig[global_nsteps],tuplimit[global_nsteps];
	for(int i=0;i<global_nsteps;i++){
		mass_array[i]=-1.;
		tupsig[i]=-1.;
		tuplimit[i]=-1.;
	}

	double q_upsig[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	double q_uplimit[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	double temp_low,temp_high;
	int temp_shape,temp_bkg;

	for(iee=0;iee<global_nsteps;iee++){
//		if(iee > 50 || (iee%10!=0) ) continue;
//		if(iee!=40  &&  iee!=120  ) continue;
//		if(iee!=40 ) continue;
		mass=global_low+iee*global_stepdiv;
		mass_array[iee]=mass;
		TString br_mass="";
		br_mass+="mee";
		br_mass+=Form("%.2f",mass);
		f_ckfit->mkdir(br_mass);
		f_final->mkdir(br_mass);
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
	
	for(int i=0;i<global_nsteps;i++){
		upsigtxt<<mass_array[i]<<" "<<tupsig[i]<<endl;
		uplimittxt<<mass_array[i]<<" "<<tuplimit[i]<<endl;
	}

	TGraph *g_upsig = new TGraph(global_nsteps,mass_array,tupsig);
	TGraph *g_uplimit = new TGraph(global_nsteps,mass_array,tuplimit);
	
	NameAxis(g_upsig,"M(e^{+}e^{-}) (GeV/c^{2})","N_{signal}","Fitted upper N_{signal} @90% C.L.");
	NameAxis(g_uplimit,"M(e^{+}e^{-}) (GeV/c^{2})","BR(J/#psi->Uh)#timesBR(U->e^{+}e^{-})","Fitted upper limit @90% C.L.");
	g_upsig->SetName("upper_signal");
	g_uplimit->SetName("upper_limit");
//	TCanvas *cc = new TCanvas("cc","cc");
//	cc->cd();
//	g_upsig->Draw("ap");
	f_final->cd();
//	cc->Write();
	g_upsig->Write();
	g_uplimit->Write();

	f_ckfit->Close();
	f_final->Close();

}


