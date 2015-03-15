#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TSystem.h"
#include "TH2F.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"
#include <cmath>
#include "function.h"
#include "TString.h"
#include "TCut.h"
#include "THStack.h"
#include "TSystem.h"
#include "TLegend.h"


using namespace std;
void comp()
{


    gStyle->SetFrameBorderMode(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetTitleColor(1);
    gStyle->SetStatColor(0);
    gStyle->SetTitleFillColor(0);
    gStyle->SetHistFillColor(0);

    // set the paper & margin sizes
    //gStyle->SetPaperSize(20,26);
    //gStyle->SetPadTopMargin(0.01);
    //gStyle->SetPadRightMargin(0.04);
    //gStyle->SetPadBottomMargin(0.14);
    //gStyle->SetPadLeftMargin(0.10);

    // use large Times-Roman fonts
    gStyle->SetTitleFont(132,"xyz");  // set the all 3 axes title font
    gStyle->SetTitleFont(132," ");    // set the pad title font
    gStyle->SetTitleSize(0.06,"xyz"); // set the 3 axes title size
    gStyle->SetTitleSize(0.06," ");   // set the pad title size
    gStyle->SetLabelFont(132,"xyz");
    gStyle->SetLabelSize(0.05,"xyz");
    gStyle->SetTextFont(132);
    gStyle->SetTextSize(0.08);
    gStyle->SetStatFont(132);
    // use bold lines and markers
    gStyle->SetMarkerStyle(1);
    gStyle->SetHistLineWidth(1);
    gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
    // Get rid of X error bars
    gStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);

    // put tick marks on top and RHS of plots
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);


    TFile *file1 = new TFile("./rootsample/datasample.root","READ");
    TFile *file2 = new TFile("./rootsample/PHSPsample.root","READ");
    TFile *file3 = new TFile("./rootsample/DDsample.root","READ");

    TFile *file4 = new TFile("./rootsample/ISRsample.root","READ");
    TFile *file5 = new TFile("./rootsample/qqbarsample.root","READ");
    TFile *file6 = new TFile("./rootsample/DD2sample.root","READ");
    TFile *file7 = new TFile("./rootsample/normalsample.root","READ");

    TTree *t1 = (TTree*)file1->Get("save");
    TTree *t2 = (TTree*)file2->Get("save");
    TTree *t3 = (TTree*)file3->Get("save");
    TTree *t4 = (TTree*)file4->Get("save");
    TTree *t5 = (TTree*)file5->Get("save");
    TTree *t6 = (TTree*)file6->Get("save");
    TTree *t7 = (TTree*)file7->Get("save");




    TCut cut;
    TCut cut_rmD0pi0="(rmD0pi0-2.157)*(rmD0pi0-2.157)*(6608.7)+(rmD0pi0-2.157)*(rmantiD0pi0-2.157)*(-4521.74)+(rmantiD0pi0-2.157)* (rmantiD0pi0-2.157)*(6608.7)<1";
    TCut cut_mD0pi0 = "mD0pi0>2.02";
    TCut cut_mantiD0pi0 = "mantiD0pi0>2.02";
    cut=cut_rmD0pi0&&cut_mD0pi0&&cut_mantiD0pi0;
    bool D0,D0pi0,antiD0pi0,antiD0,bpi0,rD0,rD0pi0,rantiD0pi0,rantiD0,rpi0;
    D0=0;
    antiD0=0;
    bpi0=0;
    rD0=0;
    rD0pi0=0;
    rantiD0pi0=0;
    rantiD0=0;
    rpi0=1;
    D0pi0=0;
    antiD0pi0=0;
    if(D0pi0){TString draw_var="mD0pi0";Int_t xbins=30;Double_t xmin=2;Double_t xmax=2.15;}
    if(antiD0pi0){TString draw_var="mantiD0pi0";Int_t xbins=30;Double_t xmin=2;Double_t xmax=2.15;}
    if(D0){TString draw_var="mD0_raw";Int_t xbins=20;Double_t xmin=2.2;Double_t xmax=2.4;}
    if(antiD0){TString draw_var="mantiD0_raw";Int_t xbins=70;Double_t xmin=1.8;Double_t xmax=1.94;}
    if(bpi0){TString draw_var="mpi0";Int_t xbins=50;Double_t xmin=0.12;Double_t xmax=0.145;}
    if(rD0){TString draw_var="rmD0_raw";Int_t xbins=55;Double_t xmin=1.8;Double_t xmax=2.35;}
    if(rD0pi0){TString draw_var="rmD0pi0";Int_t xbins=80;Double_t xmin=1.5;Double_t xmax=2.3;}
    if(rantiD0pi0){TString draw_var="rmantiD0pi0";Int_t xbins=80;Double_t xmin=1.5;Double_t xmax=2.3;}
    if(rantiD0){TString draw_var="rmantiD0_raw";Int_t xbins=60;Double_t xmin=1.8;Double_t xmax=2.4;}
    if(rpi0){TString draw_var="rmpi0_";Int_t xbins=20;Double_t xmin=4.01;Double_t xmax=4.09;}
    //************************************************************8	



    TH1F *th1f_data=new TH1F("t_data","", xbins, xmin, xmax); //th1f_data->SetMinimum(0);
    TH1F *th1f_PHSP=new TH1F("t_PHSP","", xbins, xmin, xmax);  
    TH1F *th1f_DD=new TH1F("t_DD","", xbins, xmin, xmax);
    TH1F *th1f_DD2=new TH1F("t_DD2","", xbins, xmin, xmax);
    TH1F *th1f_ISR=new TH1F("t_ISR","", xbins, xmin, xmax);
    TH1F *th1f_qqbar=new TH1F("t_qqbar","", xbins, xmin, xmax);
    TH1F *th1f_signal=new TH1F("t_signal","", xbins, xmin, xmax);



    t1->Project("t_data", draw_var, cut);
    t2->Project("t_PHSP", draw_var, cut);
    t3->Project("t_DD", draw_var, cut);
    t4->Project("t_ISR", draw_var, cut);
    t5->Project("t_qqbar", draw_var, cut);
    t6->Project("t_DD2", draw_var, cut);
    t7->Project("t_signal", draw_var, cut);

    th1f_ISR->Scale(1.04);
    th1f_DD->Scale(0.1107);
    //th1f_DD2->Scale(1.23);
    th1f_qqbar->Scale(0.5655);
    th1f_DD2->Scale(0.2236);
    th1f_PHSP->Scale(0.004);
    //th1f_signal->Scale(0.007);



    th1f_PHSP->SetLineColor(kBlue);// th1f_PHSP->SetLineStyle(1);
    th1f_PHSP->SetLineWidth(2); //th1f_PHSP->SetFillStyle(3010);
    th1f_signal->SetLineColor(kRed); //th1f_PHSP->SetFillStyle(3010);
    th1f_signal->SetLineWidth(2); //th1f_PHSP->SetFillStyle(3010);
    //	th1f_PHSP->SetLineColor(kBlue); //th1f_PHSP->SetFillStyle(3010);
    //	th1f_bhabha->SetFillColor(kBlack); //th1f_bhabha->SetFillStyle(3011);
    th1f_DD->SetFillColor(kCyan); //th1f_DD->SetFillStyle(3013);
    //	th1f_digamma->SetFillColor(kBlack);// th1f_digamma->SetFillStyle(3014);
    //	th1f_dimu->SetFillColor(kBlack); //th1f_dimu->SetFillStyle(3015);
    //	th1f_ditau->SetFillColor(kCyan); //th1f_ditau->SetFillStyle(3016);
    //	th1f_gXYZ->SetFillColor(0); //th1f_gXYZ->SetFillStyle(3017);
    th1f_DD2->SetFillColor(kYellow); //th1f_DD2s->SetFillStyle(3018);
    th1f_ISR->SetFillColor(kMagenta); //th1f_ISR->SetFillStyle(3019);
    th1f_qqbar->SetFillColor(kGreen); //th1f_qqbar->SetFillStyle(3020);
    //	 th1f_twogamma->SetFillColor(kBlack); th1f_twogamma->SetFillStyle(3022);
    char num_PHSP[20],num_sum[20],num_signal[20],num_DDpi[20],num_DD[20],num_DD2[20],num_ISR[20],num_qqbar[20],num_data[20];
    Double_t I_DD=th1f_DD->Integral();
    Double_t I_DD2=th1f_DD2->Integral();
    Double_t I_ISR=th1f_ISR->Integral();
    Double_t I_qqbar=th1f_qqbar->Integral();
    Double_t I_data=th1f_data->Integral();
    Double_t I_PHSP=th1f_PHSP->Integral();
    Double_t I_signal=th1f_signal->Integral();

    sprintf(num_DD, "(%.3f)",I_DD );
    sprintf(num_DD2, "(%.3f)",I_DD2 );
    sprintf(num_ISR, "(%.3f)",I_ISR );
    sprintf(num_qqbar, "(%.3f)",I_qqbar );
    sprintf(num_data, "(%.3f)",I_data );
    sprintf(num_PHSP, "(%f)",I_PHSP );
    sprintf(num_signal, "(%f)",I_signal );

    TString name_DD("DD");
    TString name_DD2("DD2");
    TString name_ISR("ISR");
    TString name_qqbar("qqbar");
    TString name_data("data");  
    TString name_PHSP("PHSP");
    TString name_signal("signal");
    //cout<<th1f_signal->Integral()<<endl;
    //cout<<th1f_signal->GetEntries()<<endl;


    THStack *hs = new THStack("hs","rmpi0_");
    //	hs->Add(th1f_PHSP);
    //	hs->Add(th1f_signal);
    hs->Add(th1f_DD);
    //hs->Add(th1f_DDpi);
    hs->Add(th1f_ISR);
    hs->Add(th1f_qqbar);
    hs->Add(th1f_DD2);
    //	hs->Add(th1f_ditau);
    //	hs->Add(th1f_gXYZ);
    //	hs->Add(th1f_bhabha);
    //hs->Add(th1f_data);
    //hs->Add(th1f_signal);
    //	hs->Add(th1f_digamma);
    //	hs->Add(th1f_dimu);
    //	hs->Add(th1f_twogamma);
    TLegend *legend1 = new TLegend(.65,.6,.85,.8);
    //TLegend *legend1 = new TLegend(.6,.55,.85,.8);
    ////num_signallegend1->AddEntry(th1f_bhabha,"bhabha","F");
    //legend1->AddEntry(th1f_DDpi,name_DDpi+num_DDpi,"F");
    legend1->AddEntry(th1f_DD,name_DD+num_DD,"F");
    ////num_DDlegend1->AddEntry(th1f_digamma,"#gamma#gamma","F");
    ////gammalegend1->AddEntry(th1f_dimu,"#dimu#dimu","F");
    ////dimulegend1->AddEntry(th1f_ditau,"#tau#tau","F");
    ////taulegend1->AddEntry(th1f_gXYZ,"#gamma XYZ","F");
    legend1->AddEntry(th1f_DD2,name_DD2+num_DD2,"F");
    legend1->AddEntry(th1f_ISR,name_ISR+num_ISR,"F");
    legend1->AddEntry(th1f_qqbar,name_qqbar+num_qqbar,"F");
    legend1->AddEntry(th1f_data,name_data+num_data,"PL");
    legend1->AddEntry(th1f_PHSP,"PHSP");
    //legend1->AddEntry(th1f_signal,"SIGNAL");
    legend1->SetFillColor(0);

    TLegend *legend2 = new TLegend(.2,.75,.2,.75);
    legend2->SetHeader("  4230 ");
    legend2->SetTextSize(0.05);
    legend2->SetTextColor(2);
    legend2->SetFillColor(2);

    gStyle->SetOptStat(0);
    TCanvas *c1=new TCanvas("c1","",0,0,800,600);
    c1->cd();
    hs->SetMaximum(20);
    hs->SetTitle("");
    hs->Draw();
    hs->GetYaxis()->SetTitle(Form("Events/(%.3f)",(xmax-xmin)/xbins));
    //hs->GetXaxis()->SetTitle("RM(D#pi^{0}) Gev/c^{2}");
    hs->GetXaxis()->SetTitle("RM(#pi^{0}) Gev/c^{2}");
    //	th1f_PHSP->SetMaximum(20);
    //    th1f_PHSP->Draw("same");
    th1f_data->SetMarkerStyle(20);
    th1f_data->SetMarkerSize(0.7);
    th1f_data->Draw("pesame");
    //	th1f_PHSP->SetMarkerStyle(4);
    //	th1f_PHSP->SetMarkerSize(0.8);
    th1f_PHSP->Draw("same");
 //   th1f_signal->Draw("same");
    legend1->Draw();
    legend2->Draw();
    c1->SaveAs("plots/rmpi04230.eps");
    //   th1f_data->Draw();

}

