#include<TH2.h>
#include<TStyle.h>
#include<TCanvas.h>
#include<cmath>
#include <iostream.h>
#include <iomanip.h>
using namespace std;
void fit()
{
    gStyle->SetOptTitle(0);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    
    gStyle->SetOptTitle(0);
    gSystem->Load("libRooFit");
    using namespace RooFit;
    TChain *fChain = new TChain("final");
    fChain->Add("/besfs/users/chenzx/panfs-chenzx/kslambppi/data/JPsi/kslambppifinal.root");
    TH1D *m = new TH1D("m","",30,1.6,1.9);
    fChain->Draw("kslambm>>m");
    m->Draw();
    RooRealVar x("x","M_{p#pi} (GeV/c^{2})",1.6,1.9);
 
//    TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,600);
    c1->cd();
    int N=80;
    //int N=60;
    double F[241],S[241],Num[241];
    
    TChain *f1 = new TChain("final");
    f1->Add("/besfs/users/chenzx/panfs-chenzx/kslambppi/data/JPsi/kslambppipre.root");
    TFile *f2 = new TFile("/besfs/users/chenzx/panfs-chenzx/kslambppi/mc/JPsi/kslambppifinal.root");
    for (int n = 0; n < N; n++  ){
      //if(n<68) continue;
      RooDataHist *data = new RooDataHist("data","dataset with x",x,m);
      RooRealVar b0("b0","coefficient b#0",-0.349265);
      RooRealVar b1("b1","coefficient b#1",0.677919);
      RooRealVar b2("b2","coefficient b#2",-0.242574);
      RooGenericPdf eff("eff","b0+b1*x+b2*x*x",RooArgSet(x,b0,b1,b2));
      
      RooRealVar mass("mass","mass of Breit-Wigner",1.535);
      RooRealVar width("width","width of Breit-Wigner",0.15);
      RooRealVar sigma("sigma","sigma of Breit-Wigner",0.002);
      RooVoigtian bw("bw","Breit-Wigner",x,mass,width,sigma);
      RooProdPdf sig("sig","pdf of signal",RooArgSet(bw));

      //get bkg from etap sideband
      TH1D *bkg_sideband = new TH1D("bkg_sideband","background from sideband",30,1.6,1.9);
      f1->Draw("kslambm>>bkg_sideband","fabs(ksm-0.498)>0.008&&fabs(ksm-0.498)<0.019&&chi2<50&&Lmin>0.0001&&fabs(lambm-1.116)<0.006");
      //
      bkg_sideband->Smooth(1000);
      RooDataHist dh1("dh1","dh1",x,bkg_sideband);
      RooHistPdf bkg1("bkg1","bkg_sideband_pdf",RooArgSet(x),dh1);

      TH1D *bkg_phsp = new TH1D("bkg_phsp","background from phsp",30,1.6,1.9);
      f2->Draw("kslambm>>bkg_phsp");

//      TH1D *bkg_phsp = (TH1D*)f2->Get("hist");
       bkg_phsp->Smooth(1000);
 
      //bkg from phsp

      RooRealVar a1("a1","coefficient a#1",1,-10.,10.);
      RooRealVar a2("a2","coefficient a#2",1,-10.,10.); 
      RooRealVar a3("a3","coefficient a#3",1,-10.,10.);
//      RooChebychev bkg2_p1("bkg2_p1","bkg2_p1",x,RooArgList(a1,a2,a3));
//      RooGenericPdf bkg2_p2("bkg2_p2","",RooArgSet(x));
      RooDataHist dh2("dh2","dh2",x,bkg_phsp);
      RooHistPdf bkg2("bkg2","bkg_phsp",RooArgSet(x),dh2);
 
      RooRealVar nsig("nsig","number of signal events",n);  
      RooRealVar nbkg1("nbkg1","number of background events",41);
      RooRealVar nbkg2("nbkg2","number of background events",100,0,1000);
      RooAddPdf model("model","sig+bkg",RooArgList(sig,bkg1,bkg2),RooArgList(nsig,nbkg1,nbkg2));
      RooPlot* xframe = x.frame(Name("xframe"),Title(" "));
      xframe->GetYaxis()->SetTitle("Events/(0.01GeV/c^{2})");
      RooFitResult *fitres = model.fitTo(*data, Save(kTRUE));

        // Plot data and PDF overlaid
        RooPlot *xframe = x.frame(Name("xframe"),Title(" "));
        data.plotOn(xframe);	
        model.plotOn(xframe);
        cout<<"chi2/d.o.f="<<(xframe->chiSquare(5))<<endl;
        model.plotOn(xframe, Components(sig), LineStyle(2), LineColor(kBlue));
        model.plotOn(xframe, Components(bkg1), LineStyle(1), LineColor(kGreen));
        model.plotOn(xframe, Components(bkg1), LineStyle(1), LineColor(kRed));
//        model.plotOn(xframe, LineColor(kRed));
        fitres->Print("v");
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
        delete data;
        delete bkg_sideband;
        delete bkg_phsp;
    }
    
    
    ofstream outlikelilog;
    outlikelilog.open("test.txt");
    //outlikelilog.open("fitmetap_step_zero_point5.txt");
    for (int i = 0; i < N; i++) {
        
        cout<<"N"<<i<<"	F[N]"<<F[i]<<endl;
        
        S[i] = TMath::Exp(F[i] - F[9]);   // range from 0.87 to 1.05 ,chi2<75
        Num[i] = i ;
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
    

    TCanvas *c = new TCanvas("can", "upper limit of Nbar1535", 200, 10, 800, 600);
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
    c->Print("test.eps");
    //c->Print("Likelihood_vs_nEvent_step_zero_point5.eps");
}
