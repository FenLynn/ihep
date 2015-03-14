#include "RooFFTConvPdf.h"
#include <iostream>
#include <iomanip>
using namespace std;
void fitmetap()
{
    //gROOT->Reset();
    //gROOT->SetStyle("Plain");
    gStyle->SetOptFit(111);
    gStyle->SetOptStat(0);
    //gStyle->SetStripDecimals(kFALSE);

    using namespace RooFit;

    TFile *file = new TFile("2pi2mu_final.root");
    TTree *t = (TTree *) file->Get("chi2omg");

    TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,600);
    c1->cd();
    int N=10;
    //int N=60;
    double F[241],S[241],Num[241];
    
    for (int n = 0; n < N; n++  ){
        //RooRealVar _2pi2mu_m2pi2mu("2pi2mu_m2pi2mu", "M(#pi^{+}#pi^{-}#mu^{+}#mu^{-})", 0.90, 1.0, "GeV");
        RooRealVar _2pi2mu_m2pi2mu("2pi2mu_m2pi2mu", "M(#pi^{+}#pi^{-}#mu^{+}#mu^{-})", 0.87, 1.05, "GeV");
        RooRealVar mean("mean", "mean", 0.95778);
        RooRealVar width("width", "width", 0.000194);
        RooBreitWigner breit("breit", "breit", _2pi2mu_m2pi2mu, mean, width);

        RooRealVar gmean1("gmean1", "gmean1", 0);
        RooRealVar gmean2("gmean2", "gmean2", 0);
        RooRealVar sigma1("sigma1", "sigma1", 1.10417e-02);// 0, 0.020
        RooRealVar sigma2("sigma2", "sigma2", 3.23808e-03);//, 0, 0.020);
        
        RooGaussian pdf1("pdf1", "pdf1", _2pi2mu_m2pi2mu, gmean1, sigma1);
        RooGaussian pdf2("pdf2", "pdf2", _2pi2mu_m2pi2mu, gmean2, sigma2);
        
        RooRealVar nsig1("nsig1", "",  1.08548e+04 );//10, 0.00, 100000);//0.
        RooRealVar nsig2("nsig2", "",  2.37713e+04 );//10, 0.00, 100000);//0.
        RooAddPdf res("res", "res:pdf1+ pdf2", RooArgList(pdf1, pdf2), RooArgList(nsig1,nsig2));
        //RooAddPdf res("res", "res:pdf1+ pdf2", RooArgList(pdf1, pdf2), gfrac);

        _2pi2mu_m2pi2mu.setBins(10000, "cache");
        RooFFTConvPdf sig("sig", "sig", _2pi2mu_m2pi2mu, breit, res);

        double a_0 = 1.46599;
        double a_1 = 0.553515;
        double a_2 = 0.0875862;
        RooRealVar a0("a0", "eff0", a_0, -100, 100);
        RooRealVar a1("a1", "eff1", a_1, -100, 100);
        RooRealVar a2("a2", "eff2", a_2, -100, 100);
        RooRealVar a3("a3", "eff3", 0.10, -100, 100);
        RooRealVar a4("a4", "eff4", 0.10, -100, 100);
        RooRealVar a5("a5", "eff5", 0.10, -100, 100);
        RooChebychev bkg("bkg", "chebychev bkg pdf",_2pi2mu_m2pi2mu, RooArgList(a0, a1, a2 ));//, a3));//, a4));//, a5));

        RooRealVar Nsig("Nsig", "num of #pi^{+}#pi^{-}#mu^{+}#mu^{-} ",n*0.2);
        //RooRealVar Nsig("Nsig", "num of #pi^{+}#pi^{-}#mu^{+}#mu^{-} ",n*0.5);
        //Nsig.setConstant(kTRUE);
        RooRealVar Nbkg("Nbkg", "num of bkg",20,0,1000);//the total events in [0.87,1.05] is 107
        RooAddPdf model("model","sig+bkg",RooArgList(sig, bkg),RooArgList(Nsig, Nbkg));
        
        RooDataSet data("data", "data", t, _2pi2mu_m2pi2mu);
        //RooFitResult *fitres = model.fitTo(data, Extended(), Minos(kFALSE), Save(kTRUE));
        RooFitResult *fitres = model.fitTo(data, Save(kTRUE));

        // Plot data and PDF overlaid
        RooPlot *xframe = _2pi2mu_m2pi2mu.frame(50);
        data.plotOn(xframe);	
        model.plotOn(xframe);
        cout<<"chi2/d.o.f="<<(xframe->chiSquare(4))<<endl;
        model.plotOn(xframe, Components(sig), LineStyle(2), LineColor(kBlue));
        model.plotOn(xframe, Components(bkg), LineStyle(1), LineColor(kGreen));
        model.plotOn(xframe, LineColor(kRed));

        //RooArgSet *paramList = model.getParameters(data);
        //model.fitTo(data, "SER");
        fitres->Print("v");

        //paramList->Print("v");
        //c1->cd();
        xframe->Draw();
        c1->Update();

        // P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
        // ----------------------------------------------------------------
        //ofstream likelilog("likepa.dat",ofstream::app);
        double like = fitres->minNll();
        F[n] = -1. *like;
        cout<<"FitEventNumber = "<<0.2*n<<";     n="<<n<<endl;
        //cout<<"FitEventNumber = "<<0.5*n<<";     n="<<n<<endl;
        cout << setiosflags(ios::fixed);
        cout << setprecision(5) << F[n] << endl;
        cout.unsetf(ios::fixed);
    }
    
    
    ofstream outlikelilog;
    outlikelilog.open("test.txt");
    //outlikelilog.open("fitmetap_step_zero_point5.txt");
    for (int i = 0; i < N; i++) {
        
        cout<<"N"<<i<<"	F[N]"<<F[i]<<endl;
        
        S[i] = TMath::Exp(F[i] - F[33]);   // range from 0.87 to 1.05 ,chi2<75
        Num[i] = i*0.2 ;
        //S[i] = TMath::Exp(F[i] - F[10]);
        //Num[i] = i*0.5 ;
        outlikelilog<<Num[i]<<"  ";
        //
        outlikelilog<<setiosflags(ios::fixed);
        outlikelilog<<setprecision(5)<<F[i]<<"  ";
        outlikelilog.unsetf(ios::fixed);
        
        outlikelilog<<i<<"  ";
        outlikelilog<<setiosflags(ios::fixed);
        outlikelilog<<setprecision(5)<<S[i]<<endl;
        outlikelilog.unsetf(ios::fixed);
    }
        outlikelilog.close();
    

    TCanvas *c = new TCanvas("can", "upper limit of etaprime", 200, 10, 800, 600);
    c->cd();
    TGraph *gr = new TGraph(N, Num, S);
    gr->GetXaxis()->SetTitle("Event number");
    gr->GetYaxis()->SetTitle("Likelihood");
    gr->SetMarkerStyle(8);
    gr->SetMarkerColor(kRed);

    //TF1 *f1 = new TF1("f1", "gaus");
    //gr->Fit("f1");
    //f1->SetLineColor(kBlue);

    gr->Draw("ALP");
    //f1->Draw("same");
    TArrow *arrow = new TArrow(12.6, 0.0, 12.6, 0.9, 2.0, ">");// change from 14.6 to 12.6 on 14.02.2012 
    arrow->Draw("same");
    c->Update();
//    c->Print("Likelihood_vs_nEvent_step_zero_point2.eps");
    //c->Print("Likelihood_vs_nEvent_step_zero_point5.eps");
}
