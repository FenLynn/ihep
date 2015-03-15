//chenqy
//draw noOsc/Oscnospread/Oscwithspread together
//as TH1D form
#include "TH2D.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TMath.h"
#include "TLegend.h"
#include "TMarker.h"
#include "TLatex.h"
#include "TObjArray.h"
#include "TMultiGraph.h"
#include "TH1.h"
#include "TH1F.h"
#include "TF1.h"
#include "TPad.h"
#include "TFile.h"
#include "TLine.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

//--------------------------------------------------
void eraselabel(TPad *p,Double_t h)
{
  p->cd();
  TPad *pe = new TPad("pe","pe",0,0,p->GetLeftMargin(),h);
  pe->Draw();
  pe->SetFillColor(p->GetFillColor());
  pe->SetBorderMode(0);
}
//=================================================================
void draw_3spec_newStyle()
{
  gStyle->SetOptStat(kFALSE);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetLegendBorderSize(0);
  
  //TFile *file = new TFile("compareFunc_50.000000m.root");
  //TFile *file = new TFile("compareFunc_44.400000m.root");
  TFile *file = new TFile("compareFunc_20.000000m.root");
  file->ls();
  
  TF1 *func_noOsc = (TF1*)file->Get("func_noOsc");
  TF1 *func_Osc_nospread = (TF1*)file->Get("func_Osc_nospread");
  TF1 *func_Osc_spread = (TF1*)file->Get("func_Osc_spread");
  TF1 *func_Osc_spread_analytical = (TF1*)file->Get("func_Osc_spread_analytical");

  TCanvas *cfuncs = new TCanvas("cfuncs","cfuncs",800, 600);
  func_noOsc->Draw();
  func_Osc_nospread->Draw("same");
  func_Osc_spread->Draw("same");
  func_Osc_spread_analytical->Draw("same");
  cfuncs->Update();
 
  Int_t NBINS = 32;
  //Int_t NBINS = 40;
  //Int_t NBINS = 100;
  Double_t enumin = 2.0;
  Double_t enumax = 10.0;
  
  cout<<"---------------------------------------------"<<endl;
  Double_t nwant_noOsc = func_noOsc->Integral(enumin, enumax);
  Double_t nwant_Osc_nospread = func_Osc_nospread->Integral(enumin, enumax);
  Double_t nwant_Osc_spread = func_Osc_spread->Integral(enumin, enumax);
  Double_t nwant_Osc_spread_analytical = func_Osc_spread_analytical->Integral(enumin, enumax);
  cout<<"func_noOsc->Integral(2.0, 10.0) = "<<nwant_noOsc<<endl;
  cout<<"func_Osc_nospread->Integral(2.0, 10.0) = "<<nwant_Osc_nospread<<endl;
  cout<<"func_Osc_spread->Integral(2.0, 10.0) = "<<nwant_Osc_spread<<endl;
  cout<<"func_Osc_spread_analytical->Integral(2.0, 10.0) = "<<nwant_Osc_spread_analytical<<endl;
  cout<<"---------------------------------------------"<<endl;
 
  TH1D* h_noOsc = new TH1D("h_noOsc", "h_noOsc", NBINS, enumin, enumax);
  TH1D* h_Osc_nospread = new TH1D("h_Osc_nospread", "h_Osc_nospread", NBINS, enumin, enumax);
  TH1D* h_Osc_spread = new TH1D("h_Osc_spread", "h_Osc_spread", NBINS, enumin, enumax);
  TH1D* h_Osc_spread_analytical = new TH1D("h_Osc_spread_analytical", "h_Osc_spread_analytical", NBINS, enumin, enumax);

  h_noOsc->SetStats(0);
  h_Osc_nospread->SetStats(0);
  h_Osc_spread->SetStats(0);
  h_Osc_spread_analytical->SetStats(0);

  h_noOsc->SetLineColor(1);
  h_Osc_nospread->SetLineColor(2);
  h_Osc_spread->SetLineColor(3);
  h_Osc_spread_analytical->SetLineColor(7);

  h_noOsc->SetMarkerColor(1);
  h_Osc_nospread->SetMarkerColor(2);
  h_Osc_spread->SetMarkerColor(3);
  h_Osc_spread_analytical->SetMarkerColor(7);
  
  for(Int_t i=1; i<=NBINS; i++)
  {
    Double_t enu = h_noOsc->GetBinCenter(i);
    Double_t value_noOsc = func_noOsc->Eval(enu);
    Double_t value_Osc_nospread = func_Osc_nospread->Eval(enu);
    Double_t value_Osc_spread = func_Osc_spread->Eval(enu);
    Double_t value_Osc_spread_analytical = func_Osc_spread_analytical->Eval(enu);
    h_noOsc->SetBinContent(i, value_noOsc);
    h_Osc_nospread->SetBinContent(i, value_Osc_nospread);
    h_Osc_spread->SetBinContent(i, value_Osc_spread);
    h_Osc_spread_analytical->SetBinContent(i, value_Osc_spread_analytical);
  }//end of for loop
  //h_noOsc->Sumw2();  
  //h_Osc_nospread->Sumw2();  
  //h_Osc_spread->Sumw2();  
  //h_Osc_spread_analytical->Sumw2();  
  
  cout<<"--------------------------------"<<endl;
  cout<<"h_noOsc->Integral() = "<<h_noOsc->Integral()<<endl;
  cout<<"h_Osc_nospread->Integral() = "<<h_Osc_nospread->Integral()<<endl;
  cout<<"h_Osc_spread->Integral() = "<<h_Osc_spread->Integral()<<endl;
  cout<<"h_Osc_spread_analytical->Integral() = "<<h_Osc_spread_analytical->Integral()<<endl;
  h_noOsc->Scale(nwant_noOsc/h_noOsc->Integral());
  h_Osc_nospread->Scale(nwant_Osc_nospread/h_Osc_nospread->Integral());
  h_Osc_spread->Scale(nwant_Osc_spread/h_Osc_spread->Integral());
  h_Osc_spread_analytical->Scale(nwant_Osc_spread_analytical/h_Osc_spread_analytical->Integral());
  cout<<"after scale h_noOsc->Integral() = "<<h_noOsc->Integral()<<endl;
  cout<<"after scale h_Osc_nospread->Integral() = "<<h_Osc_nospread->Integral()<<endl;
  cout<<"after scale h_Osc_spread->Integral() = "<<h_Osc_spread->Integral()<<endl;
  cout<<"after scale h_Osc_spread_analytical->Integral() = "<<h_Osc_spread_analytical->Integral()<<endl;
  cout<<"--------------------------------"<<endl;

  TCanvas *c = new TCanvas("c","c",800,600);
  TPad* p1 = new TPad("p1","p1",0.01,0.5,0.99,0.99,0); p1->Draw();
  TPad* p2 = new TPad("p1","p1",0.01,0.01,0.99,0.5,0); p2->Draw();
  p1->SetBottomMargin(0);
  p2->SetTopMargin(0);

  p1->SetLeftMargin(0.15);
  p2->SetLeftMargin(0.15);
  p2->SetBottomMargin(0.18);

  h_noOsc->GetYaxis()->SetLabelSize(0.08); 
  h_noOsc->GetYaxis()->SetLabelFont(22); 
  h_noOsc->GetYaxis()->SetTitle("Number of events"); 
  h_noOsc->GetYaxis()->SetTitleSize(0.08); 
  h_noOsc->GetYaxis()->SetTitleFont(22); 
  h_noOsc->GetYaxis()->SetTitleOffset(0.8); 
  h_noOsc->GetYaxis()->CenterTitle(); 
  p1->cd(); 
  h_noOsc->Draw("e"); 
  h_Osc_nospread->Draw("esame");
  h_Osc_spread->Draw("esame");
  h_Osc_spread_analytical->Draw("esame");
  h_Osc_nospread->Draw("esame");
  //h_noOsc->Draw("e"); 
  //h_Osc_nospread->Draw("esame");
  //h_Osc_spread->Draw("esame");
   
  TLegend* leg = new TLegend(0.45, 0.55, 0.85, 0.85);
  leg->SetTextSize(0.08);
  leg->SetTextFont(22);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h_noOsc, "no osc", "lp");
  leg->AddEntry(h_Osc_nospread, "osc, no smear", "lp");
  leg->AddEntry(h_Osc_spread, "osc, smear (MC)", "lp");
  leg->AddEntry(h_Osc_spread_analytical, "osc, smear (analytical)", "lp");
  leg->Draw();

  //h_noOsc->Sumw2();  
  //h_Osc_nospread->Sumw2();  
  //h_Osc_spread->Sumw2();  
  
  h_noOsc->Sumw2();  
  h_Osc_nospread->Sumw2();  
  h_Osc_spread->Sumw2();  
  h_Osc_spread_analytical->Sumw2();  
  TH1D *hdeno = new TH1D(*h_Osc_nospread);
  TH1D *hdeno2 = new TH1D(*h_Osc_nospread);
  hdeno->Sumw2();
  hdeno2->Sumw2();
  TH1D *h_divide = new TH1D(*h_Osc_spread);
  h_divide->Divide(h_Osc_spread, hdeno);
  h_divide->SetLineColor(4);
  h_divide->SetMarkerColor(4);
  h_divide->GetXaxis()->SetTitleSize(0.08); 
  h_divide->GetYaxis()->SetTitleSize(0.08); 
  h_divide->GetXaxis()->SetLabelSize(0.08); 
  h_divide->GetYaxis()->SetLabelSize(0.08); 
  h_divide->GetXaxis()->SetLabelFont(22);
  h_divide->GetYaxis()->SetLabelFont(22);
  h_divide->GetYaxis()->SetRangeUser(0.95, 1.05);
  h_divide->GetXaxis()->SetTitle("Energy (MeV)"); 
  h_divide->GetYaxis()->SetTitle("Ratio"); 
  h_divide->GetXaxis()->SetTitleFont(22);
  h_divide->GetYaxis()->SetTitleFont(22);
  h_divide->GetYaxis()->SetTitleOffset(0.8);
  h_divide->GetXaxis()->CenterTitle();
  h_divide->GetYaxis()->CenterTitle();
  TH1D *h_divide_analytical = new TH1D(*h_Osc_spread_analytical);
  h_divide_analytical->Divide(h_Osc_spread_analytical, hdeno2);
  h_divide_analytical->SetLineColor(6);
  h_divide_analytical->SetMarkerColor(6);
  
  p2->cd();
  //h_divide->Draw("e");
  h_divide->Draw();
  h_divide_analytical->Draw("same");
  TLine *line1 = new TLine(enumin, 1.0, enumax, 1.0);
  line1->SetLineStyle(2);
  //line1->SetLineWidth(3);
  line1->Draw();
  
  TLatex *tex = new TLatex(4, 1.01, "Ratio = #frac{osc, smear (MC))}{osc, no smear}");
  tex->SetTextColor(4);
  tex->SetTextSize(0.08);
  tex->SetTextFont(22);
  tex->Draw(); 
  TLatex *texAna = new TLatex(4, 0.98, "Ratio = #frac{osc, smear (analytical)}{osc, no smear}");
  texAna->SetTextColor(6);
  texAna->SetTextSize(0.08);
  texAna->SetTextFont(22);
  texAna->Draw(); 

  eraselabel(p1,h_noOsc->GetXaxis()->GetLabelSize());
  c->cd();
}

