#include <math.h>
#include <fstream>
#include <iostream>
using namespace std;
void like() 
{
  //Author: Rene Brun
  //   #include <math.h>
//  gROOT->LoadMacro("AtlasStyle.C");
//      gROOT->LoadMacro("AtlasUtils.C");
//            SetAtlasStyle();
  TCanvas *c1 = new TCanvas("c1"," ",200,10,800,600);

  c1->SetFillColor(kWhite);
  c1->SetGrid();

  ifstream input("likelihood.txt");

  const Int_t n =150; 
  const Double_t Div = 0.1;
  int temp;
//  const Int_t n = 10;
//  const Double_t Div = 1;
  long double Sum_90(0), Pos_90(-1);
  long double y[n] = 0; 
  Double_t y1[n] = 0;
  string tmpStr;
  //input>>tmpStr;
  for(int i=0; i<n; i++) {
    input>>temp>>y[i];
//    cout<<"y[" << i << "]: "<<y[i]<<endl;
  }
  Double_t x[n];
  for(Int_t i =0;i<n;i++) {
    x[i]=i*Div;
  }

  //cout<<"111111"<<endl;
  double FCN_Sum(0);
  double offset = 0.;
//  double offset1 = y[200]-y[199];
  for(Int_t j =0;j<n;j++)
  {
//	if (j>=200) {
//	y[j] = y[j]-offset1;
//	}
    y1[j]=TMath::Exp(-1.*y[j] + offset);

    FCN_Sum += y1[j]*Div;
    //cout<<" y1 "<<y1[j]<<" div "<<Div<<" * "<<y1[j]*Div<<endl;
    //cout<<"Pos: "<<j*Div<<" j: "<<j<<" y1[j]: "<<(y1[j]+offset)<<endl;
  //  cout<<" FCN_Sum "<<FCN_Sum<<endl;

  }

  //cout<<"222222"<<endl;
  for(int i=0; i<n; i++) {
    ////cout<<y1[i]<<endl;

    if(Sum_90 < FCN_Sum*0.9) {
      Sum_90 += y1[i]*Div;
      Pos_90 = i*Div;
    }

  }
  cout << y[0] << " "  << y[1] << endl;
  cout << x[0] << " "  << y1[0] << endl;
  cout << x[1] << " "  << y1[1] << endl;
  cout<<" 90\% C.L "<<Pos_90<<" FCN sum "<<Sum_90<<" Tot. FCN "<<FCN_Sum<<endl;

  TF1 *g1    = new TF1("g1","gaus",0,70);
   g1->SetParameters(1.e+22,5.0,2.3);  
  g1->SetLineColor(2);
  gr = new TGraph(n,x,y1);
  gr->SetLineColor(2);
 // gr->SetLineWidth(2);
  gr->SetMarkerColor(4);
  gr->SetMarkerSize(0.7);
  gr->SetMarkerStyle(8);
  gr->SetTitle(" ");
  gr->GetXaxis()->SetTitle("N");
  gr->GetYaxis()->SetTitle("Normalized Likelihood");
  //gr->Fit("g1","R");
  gr->Draw("ap");

  double signal_lo(0.51),  signal_up(0.57);
  double side_lo_lo(0.42), side_lo_up(0.48);
  double side_up_lo(0.60), side_up_up(0.68);

  TArrow *ar = new TArrow(Pos_90, y1[0]*0.8, Pos_90, y1[0]*0.4, 0.02,"|>");
  ar->SetLineStyle(1);
  ar->SetLineColor(1);
  ar->SetFillColor(1);
  ar->SetLineWidth(3);
  ar->Draw();

  // TCanvas::Update() draws the frame, after which one can change it
  c1->Update();
  c1->GetFrame()->SetFillColor(kWhite);
  c1->GetFrame()->SetBorderSize(1);
  c1->Modified();
  c1->SaveAs("uplimit.eps");
}
