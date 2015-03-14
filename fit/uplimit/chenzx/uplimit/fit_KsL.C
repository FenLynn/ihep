//#include "RooFFTConvPdf.h"
#include<TH2.h>
#include<TStyle.h>
#include<TCanvas.h>
#include<cmath>
#include <iostream>
#include <iomanip>
using namespace std;
void fit_KsL()
{
    //gROOT->Reset();
    //gROOT->SetStyle("Plain");
    gStyle->SetOptFit(111);
    gStyle->SetOptStat(0);
    //gStyle->SetStripDecimals(kFALSE);
    gSystem->Load("libRooFit") ;
    using namespace RooFit;

    TFile *file = new TFile("Fitnew.root");
    TTree *t = (TTree *) file->Get("t1");

    TChain *fChain_mc = new TChain("initial","");
    fChain_mc->Add("/besfs/users/chenzx/panfs-chenzx/kslambppi/mc/JPsi/kslambppi.root");

    TChain *fChain = new TChain("final","");
   fChain->Add("/besfs/users/chenzx/panfs-chenzx/kslambppi/mc/JPsi/kslambppi.root");
  
    
    TChain *fChain1 = new TChain("final","");
   fChain1->Add("/besfs/users/chenzx/panfs-chenzx/kslambppi/data/JPsi2012/kslambppi.root");
  
    TH1D *m = new TH1D("m","M_KsL",40,0,0.4);
    TH1D *sideband = new TH1D("sideband","M_KsL",40,0,0.4);
 
    fChain->Draw("kslambm-1.116-0.498>>m","chi2<50&&Lmin>0.0001&&fabs(lambm-1.116)<0.006&&fabs(ksm-0.498)<0.006&&pp_pp>0.3&&pp_pm>0.3");
//    fChain->Draw("kslambm-1.116-0.498>>m","chi2<50&&Lmin>0.0001&&fabs(lambm-1.116)<0.006&&fabs(ksm-0.498)<0.006");
    m->Draw();  
    fChain1->Draw("kslambm-1.116-0.498>>sideband","chi2<50&&Lmin>0.0001&&fabs(lambm-1.116)<0.006&&pp_pp>0.3&&pp_pm>0.3&&((ksm<0.490&&ksm>0.479)||(ksm>0.506&&ksm<0.517))");
//    fChain1->Draw("kslambm-1.116-0.498>>sideband","chi2<50&&Lmin>0.0001&&fabs(lambm-1.116)<0.006&&((ksm<0.490&&ksm>0.479)||(ksm>0.506&&ksm<0.517))");

    sideband->Draw();
    
    TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,600);
    c1->cd();
    int N=100;
    //int N=60;
    double F[2000],S[2000],Num[2000];
    
    for (int n = 0; n < N; n++  ){
        //RooRealVar _2pi2mu_m2pi2mu("2pi2mu_m2pi2mu", "M(#pi^{+}#pi^{-}#mu^{+}#mu^{-})", 0.90, 1.0, "GeV");
        RooRealVar M_KsL("M_KsL", "M(#pi^{+}#pi^{-}#mu^{+}#mu^{-})", 0, 0.4, "GeV");
        RooRealVar mean("mean", "mean", -0.079);
        RooRealVar width("width", "width", 0.150);
       
        RooBreitWigner BreitWigner("BreitWigner", "BreitWigner", M_KsL, mean, width); 

      RooRealVar m1("m1","coefficient m#1",1.116+0.498);
      RooRealVar m2("m2","coefficient m#2",1.116-0.498);
//     double m1 = 1.116+0.498;
//     double m2 = 1.116-0.498; 
      RooGenericPdf PHSPfactor("PHSPfactor","sqrt(((M_KsL+m1)*(M_KsL+m1)-m1*m1)*((M_KsL+m1)*(M_KsL+m1)-m2*m2))/(2*(M_KsL+m1))",RooArgSet(M_KsL,m1,m2)); 

       
      RooRealVar p0("p0","coefficient p#0",-42.5338);
      RooRealVar p1("p1","coefficient p#1",-1.40332);
      RooRealVar p2("p2","coefficient p#2",1.89999);
      RooRealVar p3("p3","coefficient p#3",0.0420954);
      RooGenericPdf eff("eff","p3*(1+p2*(M_KsL)+p1*(M_KsL)*(M_KsL)+p0*(M_KsL)*(M_KsL)*(M_KsL))",RooArgSet(M_KsL,p0,p1,p2,p3));

/*
      RooRealVar b0("b0","coefficient b#0",-1.79873);
      RooRealVar b1("b1","coefficient b#1",2.67211);
      RooRealVar b2("b2","coefficient b#2",-0.929692);
      RooGenericPdf eff("eff","b0+b1*x+b2*x*x",RooArgSet(x,b0,b1,b2));
*/


//      RooDataHist dheff("dheff","dheff",M_KsL,meff);
//      RooHistPdf eff("eff","eff",RooArgSet(M_KsL),dheff);
                    
      RooProdPdf sig("sig","sig",RooArgSet(eff,PHSPfactor,BreitWigner));        
        //RooAddPdf res("res", "res:pdf1+ pdf2", RooArgList(pdf1, pdf2), gfrac);

//        RooRealVar a1("a1","coefficient a#1",0.08137);
//        RooRealVar a2("a2","coefficient a#2",-0.6001);
//        RooRealVar a3("a3","coefficient a#3",2.4682);
//        RooRealVar a4("a4", "eff4", 0.10, -100, 100);
//        RooRealVar a5("a5", "eff5", 0.10, -100, 100);
//RooGenericPdf bkg("bkg","a1*sqrt(M_KsL)+a2*sqrt(M_KsL)*sqrt(M_KsL)*sqrt(M_KsL)+a3*sqrt(M_KsL)*sqrt(M_KsL)*sqrt(M_KsL)*sqrt(M_KsL)*sqrt(M_KsL)",RooArgSet(M_KsL,a1,a2,a3));
//       
        RooDataHist dh1("dh1","dh1",M_KsL,m);
        RooDataHist dh_sideband("dh_sideband","dh_sideband",M_KsL,sideband);
        
        RooHistPdf bkg("bkg","PHSP_MC_bg",RooArgSet(M_KsL),dh1);
        RooHistPdf bkg_sideband("bkg_sideband","bkg_sideband",RooArgSet(M_KsL),dh_sideband);

        RooRealVar Nsig("Nsig", "num of #pi^{+}#pi^{-}#mu^{+}#mu^{-} ",n);
//RooRealVar Nsig("Nsig", "num of #pi^{+}#pi^{-}#mu^{+}#mu^{-} ",10,0,150);
//RooRealVar Nsig("Nsig", "num of #pi^{+}#pi^{-}#mu^{+}#mu^{-} ",n*0.5);
        //Nsig.setConstant(kTRUE);
        RooRealVar Nbkg("Nbkg", "num of bkg",50,0,200);//the total events in [0.87,1.05] is 107
        RooRealVar Nbkg_sideband("Nbkg_sideband", "num of bkg_sideband",261);
        RooAddPdf model("model","sig+bkg+bkg_sideband",RooArgList(sig, bkg,bkg_sideband),RooArgList(Nsig, Nbkg,Nbkg_sideband));
        
        RooDataSet data("data", "data", t, M_KsL);

       RooFitResult *fitres = model.fitTo(data, Extended(), Save(kTRUE));
//        RooFitResult *fitres = model.fitTo(data, Save(kTRUE));

        // Plot data and PDF overlaid
        RooPlot *xframe = M_KsL.frame(40);
        xframe->GetYaxis()->SetTitle("Events/(0.01GeV/c^{2})");
        xframe->GetXaxis()->SetTitle("M_{Ks#bar{#Lambda}}-M_{Ks}-M_{#bar{#Lambda}}(GeV/c^{2})");

        data.plotOn(xframe);	
        model.plotOn(xframe);
        cout<<"chi2/d.o.f="<<(xframe->chiSquare(1))<<endl;
        model.plotOn(xframe, Components(sig), LineStyle(2), LineColor(kBlue));
        model.plotOn(xframe, Components(bkg), LineStyle(1), LineColor(kGreen));
        model.plotOn(xframe, Components(bkg_sideband), LineStyle(1), LineColor(kYellow));
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
        cout<<"FitEventNumber = "<<n<<";     n="<<n<<endl;
        //cout<<"FitEventNumber = "<<0.5*n<<";     n="<<n<<endl;
        cout << setiosflags(ios::fixed);
        cout << setprecision(5) << F[n] << endl;
        cout.unsetf(ios::fixed);
    }
    
    
    ofstream outlikelilog;
    outlikelilog.open("FitKs_step_zero_point2.txt");
    //outlikelilog.open("fitmetap_step_zero_point5.txt");
    for (int i = 0; i < N; i++) {
        
        cout<<"N"<<i<<"	F[N]"<<F[i]<<endl;
        
        S[i] = TMath::Exp(F[i] - F[64]);   // range from 0.87 to 1.05 ,chi2<75
        Num[i] = i ;
        //S[i] = TMath::Exp(F[i] - F[10]);
        //Num[i] = i*0.5 ;
        outlikelilog<<Num[i]<<"  ";
        //
        outlikelilog<<setiosflags(ios::fixed);
        outlikelilog<<setprecision(8)<<F[i]<<"  ";
        outlikelilog.unsetf(ios::fixed);
        
        outlikelilog<<i<<"  ";
        outlikelilog<<setiosflags(ios::fixed);
        outlikelilog<<setprecision(8)<<S[i]<<endl;
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
    TArrow *arrow = new TArrow(165, 0.0, 165, 0.9, 1.0, ">");// change from 14.6 to 12.6 on 14.02.2012 
    arrow->Draw("same");
    c->Update();
    c->Print("Likelihood_vs_nEvent_step_zero_point2.eps");
//    c->Close();
    //c->Print("Likelihood_vs_nEvent_step_zero_point5.eps");
}
