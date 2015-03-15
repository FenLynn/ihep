#include "TCanvas.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCutG.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TFile.h"
#include "TFrame.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TString.h"

plotKfactor(){

    const int nrebin = 17;

    TFile * fp = new TFile("histograms.root");

    TH1F * hplo = (TH1F *) fp->Get("H_12_LO");
           hplo->Rebin(nrebin);
           //hplo->SetBins(20,30,500);
           hplo->Sumw2();
    TH1F * hpnlo = (TH1F *) fp->Get("H_12_NLO");
           hpnlo->Rebin(nrebin);
           //hpnlo->SetBins(20,30,500);
           hpnlo->Sumw2();

    TH1F * hmlo = (TH1F *) fp->Get("H_13_LO");
           //hmlo->SetBins(20,200,2500);
           hmlo->Rebin(nrebin);
           hmlo->Sumw2();
    TH1F * hmnlo = (TH1F *) fp->Get("H_13_NLO");
           //hmnlo->SetBins(20,200,2500);
           hmnlo->Rebin(nrebin);
           hmnlo->Sumw2();

// ------------------------------------------------

    TFile * fsup = new TFile("scaleup.root");
    TFile * fsdown = new TFile("scaledown.root");

    TH1F * hp_sup = (TH1F *) fsup->Get("H_12_NLO");
           //hp_sup->SetBins(20,30,500);
           hp_sup->Rebin(nrebin);
           hp_sup->Sumw2();
    TH1F * hplo_sup = (TH1F *) fsup->Get("H_12_LO");
           //hp_sup->SetBins(20,30,500);
           hplo_sup->Rebin(nrebin);
           hplo_sup->Sumw2();

    TH1F * hp_sdown = (TH1F *) fsdown->Get("H_12_NLO");
           //hp_sdown->SetBins(20,30,500);
           hp_sdown->Rebin(nrebin);
           hp_sdown->Sumw2();
    TH1F * hplo_sdown = (TH1F *) fsdown->Get("H_12_LO");
           //hp_sdown->SetBins(20,30,500);
           hplo_sdown->Rebin(nrebin);
           hplo_sdown->Sumw2();

    TH1F * hsp = (TH1F*) hp_sup->Clone();
           for(int i=1;i<=hsp->GetNbinsX();i++){
              hsp->SetBinContent(i,fabs(hp_sup->GetBinContent(i)/hplo_sup->GetBinContent(i)-hp_sdown->GetBinContent(i)/hplo_sdown->GetBinContent(i))/(hpnlo->GetBinContent(i)/hplo->GetBinContent(i))); }
              //hsp->SetBinContent(i,fabs(hp_sup->GetBinContent(i)-hp_sdown->GetBinContent(i))/hplo->GetBinContent(i)); }
           //hsp->Add(hp_sdown,-1);
           //hsp->Divide(hplo);

    TH1F * hm_sup = (TH1F *) fsup->Get("H_13_NLO");
           //hm_sup->SetBins(20,200,2500);
           hm_sup->Rebin(nrebin);
           hm_sup->Sumw2();
    TH1F * hmlo_sup = (TH1F *) fsup->Get("H_13_LO");
           //hm_sup->SetBins(20,200,2500);
           hmlo_sup->Rebin(nrebin);
           hmlo_sup->Sumw2();

    TH1F * hm_sdown = (TH1F *) fsdown->Get("H_13_NLO");
           //hm_sdown->SetBins(20,200,2500);
           hm_sdown->Rebin(nrebin);
           hm_sdown->Sumw2();
    TH1F * hmlo_sdown = (TH1F *) fsdown->Get("H_13_LO");
           //hm_sdown->SetBins(20,200,2500);
           hmlo_sdown->Rebin(nrebin);
           hmlo_sdown->Sumw2();

    TH1F * hsm = (TH1F*) hm_sup->Clone();
           for(int i=1;i<=hsm->GetNbinsX();i++){
              hsm->SetBinContent(i,fabs(hm_sup->GetBinContent(i)/hmlo_sup->GetBinContent(i)-hm_sdown->GetBinContent(i)/hmlo_sdown->GetBinContent(i))/(hmnlo->GetBinContent(i)/hmlo->GetBinContent(i))); }
              //hsm->SetBinContent(i,fabs(hm_sup->GetBinContent(i)-hm_sdown->GetBinContent(i))); }
           //hsm->Add(hm_sdown,-1);
           //hsm->Divide(hmlo);


//########## compare the distribution, not gonna save----------------------------

    TCanvas *c1 = new TCanvas("c1","test",1200,600);

    TH1F* hr= (TH1F*) hpnlo->Clone();
    hr->Divide(hplo);
    hr->SetStats(kFALSE);
    hr->SetTitle("VBFNLO, PP>W^{+} #gamma j j, W^{+} > l+ #nu @8TeV LHC");
    hr->GetXaxis()->SetTitle("P_{T}_{#gamma} [GeV/c^2] ");
    hr->GetYaxis()->SetTitle("K factor (NLO/LO)");
    hr->GetXaxis()->CenterTitle();
    hr->GetYaxis()->CenterTitle();

    //c1->cd(1);
    //hr->Draw();

    TH1F* hr2= (TH1F*) hmnlo->Clone();
    hr2->Divide(hmlo);
    hr2->SetStats(kFALSE);
    hr2->SetTitle("VBFNLO, PP>W^{+} #gamma j j, W^{+} > l+ #nu @8TeV LHC");
    hr2->GetXaxis()->SetTitle("M_{j j} [GeV/c^2] ");
    hr2->GetYaxis()->SetTitle("K factor (NLO/LO)");
    hr2->GetXaxis()->CenterTitle();
    hr2->GetYaxis()->CenterTitle();

    c1->cd(2);
    hmlo->SetStats(kFALSE);
    hmlo->Draw();
    //hr2->Draw();

    
//#################################################################################

    TCanvas *cres = new TCanvas("cres","analyse_dataType1",800,800);
    TPad *d1, *d2, *d3;
    cres->Divide(1,3,0,0);
    d1 = (TPad*)cres->GetPad(1);
    d2 = (TPad*)cres->GetPad(2);
    d3 = (TPad*)cres->GetPad(3);
    d1->SetPad(0.01,0.30,0.95,0.99);
    d2->SetPad(0.01,0.025,0.95,0.30);
    d3->SetPad(0.01,0.02,0.95,0.2);

    d1->cd();
    gPad->SetBottomMargin(0.0);
    gPad->SetTopMargin(0.1);
    gPad->SetRightMargin(0.05);
    gPad->SetLeftMargin(0.14);
    hpnlo->SetTitle("VBFNLO, PP>W^{+} #gamma j j, W^{+} > l+ #nu @8TeV LHC");
    //hpnlo->GetXaxis()->SetTitle("PT_{#gamma} [GeV/c^2]");
    hpnlo->GetYaxis()->CenterTitle();
    hpnlo->GetYaxis()->SetTitle("d#sigma/dPT_{#gamma} (fb/GeV)");
    hpnlo->GetYaxis()->SetTitleOffset(1.3) ;
    hpnlo->SetLineColor(kRed);
    hpnlo->SetLineWidth(2);
    hpnlo->SetStats(kFALSE);
    //hpnlo->GetYaxis()->SetRangeUser(1.15,1.75);
    gPad->SetLogy();
    hpnlo->Draw();

    hplo->SetLineColor(kBlue);
    hplo->SetLineStyle(2);
    hplo->SetLineWidth(2);
    hplo->Draw("same");
    
    TLegend *leg = new TLegend(0.66,0.68,0.86,0.82) ;
    leg->SetFillColor(10) ;
    leg->AddEntry(hpnlo,"NLO","L") ;
    leg->AddEntry(hplo,"LO","L") ;
    leg->Draw("same");

    d2->cd();
    gPad->SetLeftMargin(0.14);
    gPad->SetTopMargin(0);
    gPad->SetRightMargin(0.05);
    gPad->SetFrameBorderSize(0);
    gPad->SetBottomMargin(0.633);
    hr->GetYaxis()->SetTitle("K-factor");
    hr->SetTitle("");
    hr->SetStats(kFALSE);
    hr->SetLineWidth(2);
    hr->GetXaxis()->SetTitleSize(0.1);
    hr->GetXaxis()->SetLabelSize(0.1);
    hr->GetYaxis()->SetLabelSize(0.045);
    hr->GetYaxis()->SetTitleSize(0.06);
    hr->GetXaxis()->CenterTitle();
    hr->GetYaxis()->CenterTitle();
    hr->GetYaxis()->SetTitleOffset(0.6) ;
    hr->GetYaxis()->SetRangeUser(0.5,1.5);
    hr->Draw();

    d3->cd();
    gPad->SetLeftMargin(0.14);
    gPad->SetTopMargin(0);
    gPad->SetRightMargin(0.05);
    gPad->SetFrameBorderSize(0);
    gPad->SetBottomMargin(0.4571);
    hsp->GetXaxis()->SetTitle("P_{T}_{#gamma} (GeV)");
    hsp->GetYaxis()->SetTitle("Scale unc.");
    hsp->SetTitle("");
    hsp->SetStats(kFALSE);
    hsp->SetLineWidth(2);
    hsp->GetXaxis()->SetTitleSize(0.14);
    hsp->GetXaxis()->SetLabelSize(0.14);
    hsp->GetYaxis()->SetLabelSize(0.06);
    hsp->GetYaxis()->SetTitleSize(0.1);
    hsp->GetXaxis()->CenterTitle();
    hsp->GetYaxis()->CenterTitle();
    hsp->GetXaxis()->SetTitleOffset(1.35) ;
    hsp->GetYaxis()->SetTitleOffset(0.35) ;
    hsp->GetYaxis()->SetRangeUser(0.,0.5);
    hsp->SetLineColor(kRed);
    hsp->SetLineWidth(2);
    hsp->Draw();
    //d2->Update();
    cres->SaveAs("photonPT_Kfactor.png") ;

//#################################################################################

    TCanvas *cmjj = new TCanvas("cmjj","cmjj",800,800);
    TPad *d1m, *d2m, *d3m;
    cmjj->Divide(1,3,0,0);
    d1m = (TPad*)cmjj->GetPad(1);
    d2m = (TPad*)cmjj->GetPad(2);
    d3m = (TPad*)cmjj->GetPad(3);
    d1m->SetPad(0.01,0.30,0.95,0.99);
    d2m->SetPad(0.01,0.025,0.95,0.30);
    d3m->SetPad(0.01,0.02,0.95,0.2);

    d1m->cd();
    gPad->SetBottomMargin(0.0);
    gPad->SetTopMargin(0.1);
    gPad->SetRightMargin(0.05);
    gPad->SetLeftMargin(0.14);
    hmnlo->SetTitle("VBFNLO, PP>W^{+} #gamma j j, W^{+} > l+ #nu @8TeV LHC");
    //hmnlo->GetXaxis()->SetTitle("PT_{#gamma} [GeV/c^2]");
    hmnlo->GetYaxis()->CenterTitle();
    hmnlo->GetYaxis()->SetTitle("d#sigma/dM_{j j} (fb/GeV)");
    hmnlo->GetYaxis()->SetTitleOffset(1.3) ;
    hmnlo->SetLineColor(kRed);
    hmnlo->SetLineWidth(2);
    hmnlo->SetStats(kFALSE);
    //hmnlo->GetYaxis()->SetRangeUser(1.15,1.75);
    //gPad->SetLogy();
    hmnlo->Draw();

    hmlo->SetLineColor(kBlue);
    hmlo->SetLineStyle(2);
    hmlo->SetLineWidth(2);
    hmlo->Draw("same");
    
    leg->Draw("same");

    d2m->cd();
    gPad->SetLeftMargin(0.14);
    gPad->SetTopMargin(0);
    gPad->SetRightMargin(0.05);
    gPad->SetFrameBorderSize(0);
    gPad->SetBottomMargin(0.633);
    hr2->GetYaxis()->SetTitle("K-factor");
    hr2->SetTitle("");
    hr2->SetStats(kFALSE);
    hr2->SetLineWidth(2);
    hr2->GetXaxis()->SetTitleSize(0.15);
    hr2->GetXaxis()->SetLabelSize(0.1);
    hr2->GetYaxis()->SetLabelSize(0.045);
    hr2->GetYaxis()->SetTitleSize(0.06);
    hr2->GetXaxis()->CenterTitle();
    hr2->GetYaxis()->CenterTitle();
    hr2->GetYaxis()->SetTitleOffset(0.6) ;
    hr2->GetYaxis()->SetRangeUser(0.5,1.5);
    hr2->Draw();

    d3m->cd();
    gPad->SetLeftMargin(0.14);
    gPad->SetTopMargin(0);
    gPad->SetRightMargin(0.05);
    gPad->SetFrameBorderSize(0);
    gPad->SetBottomMargin(0.4571);
    hsm->GetXaxis()->SetTitle("M_{j j} (GeV)");
    hsm->GetYaxis()->SetTitle("Scale unc.");
    hsm->SetTitle("");
    hsm->SetStats(kFALSE);
    hsm->SetLineWidth(2);
    hsm->GetXaxis()->SetTitleSize(0.15);
    hsm->GetXaxis()->SetLabelSize(0.14);
    hsm->GetYaxis()->SetLabelSize(0.06);
    hsm->GetYaxis()->SetTitleSize(0.1);
    hsm->GetXaxis()->CenterTitle();
    hsm->GetYaxis()->CenterTitle();
    hsm->GetXaxis()->SetTitleOffset(1.35) ;
    hsm->GetYaxis()->SetTitleOffset(0.35) ;
    hsm->GetYaxis()->SetRangeUser(0.,0.5);
    hsm->SetLineColor(kRed);
    hsm->SetLineWidth(2);
    hsm->Draw();
    //d2->Update();
    cmjj->SaveAs("mjj_Kfactor.png") ;

}


