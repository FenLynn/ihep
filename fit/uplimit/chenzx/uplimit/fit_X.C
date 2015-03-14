#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <cmath>

fit_X(){
  gStyle->SetOptTitle(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);

  gStyle->SetOptTitle(0);
  gSystem->Load("libRooFit") ;
  using namespace RooFit ;
  
  //get spetrum of X
  TChain *fChain = new TChain("t1");
  fChain->Add("./tree.root");
  TH1D *m = new TH1D("m","#pi#pi#etap invarient mass spectrum ",70,1.4,2.8);
  fChain->Draw("m_pipietap>>m","signal&&m_eta2pi0>1&&chi5C<60");
  //get bkg from etap sideband
  TChain *f3 = new TChain("t1");
  f3->Add("./tree.root");
  TH1D *bkg_sideband = new TH1D("bkg_sideband","background from sideband",70,1.4,2.8);
  f3->Draw("m_pipietap>>bkg_sideband","sideband&&m_eta2pi0>1&&chi5C<60");
  //
  TFile *f4 = new TFile("/panfs/panfs.ihep.ac.cn/home/data/mintj/651p02/workarea/Analysis/Physics/gpi0pi0etap1Alg/gpi0pi0etap1Alg-00-00-01/run/excl/phsp/ana/phsp.root");
  TH1D *bkg_phsp = (TH1D*)f4->Get("hist");
  bkg_phsp->Smooth(1000);
  //start fitting
  RooAbsData* data = 0;
  RooRealVar x("x","M_{#pi^{-}#pi^{+}#eta'} GeV",1.4,2.8);
  RooRealVar res("res","resolution",0.0136405);
  //mass dependence efficiency curve
  RooRealVar coeff1("coeff1","coefficient of x0",0);
  RooRealVar coeff2("coeff2","coefficient of x1",0);
  RooRealVar coeff3("coeff3","coefficient of x2",0);
  RooRealVar coeff4("coeff4","coefficient of x3",0);
  RooGenericPdf eff("eff","1",RooArgSet(x));
  //RooGenericPdf eff("eff","coeff1+coeff2*x+coeff3*x*x+coeff4*x*x*x",RooArgSet(x,coeff1,coeff2,coeff3,coeff4));
  //bw1 for 1500
  RooRealVar mass1("mass1","mass of Breit-Wigner1",1.525,1.500,1.600);
  RooRealVar width1("width1","width of Breit-Wigner1",0.048,0.01,0.1);
  RooBreitWigner bw1("bw1","Breit-Wigner1",x,mass1,width1);
  //RooVoigtian bw1("bw1","Breit-Wigner1",x,mass1,width1,res);
  RooProdPdf sig1("sig1","pdf of signal1, with eff. correction",RooArgSet(eff,bw1));
  //bw2 for 1835
  RooRealVar mass2("mass2","mass of Breit-Wigner2",1.85,1.8,1.9);
  RooRealVar width2("width2","width of Breit-Wigner2",0.18,0.05,0.25);
  RooBreitWigner bw2("bw2","Breit-Wigner2",x,mass2,width2);
  //RooVoigtian bw2("bw2","Breit-Wigner2",x,mass2,width2,res);
  RooProdPdf sig2("sig2","pdf of signal2, with eff. correction",RooArgSet(eff,bw2));
  //bw3 for 2120
  RooRealVar mass3("mass3","mass of Breit-Wigner3",2.122,2.080,2.250);
  RooRealVar width3("width3","width of Breit-Wigner3",0.083);//,0.07,0.3);
  RooBreitWigner bw3("bw3","Breit-Wigner3",x,mass3,width3);
  //RooVoigtian bw3("bw3","Breit-Wigner3",x,mass3,width3,res);
  RooProdPdf sig3("sig3","pdf of signal3, with eff. correction",RooArgSet(eff,bw3));
  //bw4 for 2370
  RooRealVar mass4("mass4","mass of Breit-Wigner4",2.376,2.350,2.450);
  RooRealVar width4("width4","width of Breit-Wigner4",0.083);//,0.02,0.12);
  RooBreitWigner bw4("bw4","Breit-Wigner4",x,mass4,width4);
  //RooVoigtian bw4("bw4","Breit-Wigner4",x,mass4,width4,res);
  RooProdPdf sig4("sig4","pdf of signal4, with eff. correction",RooArgSet(eff,bw4));
  //bkg with cbp shape
  RooRealVar c0("c0","coefficient c#0",0.1,-10.,10.);
  RooRealVar c1("c1","coefficient c#1",0.1,-10.,10.);
  RooRealVar c2("c2","coefficient c#2",0.1,-10.,10.);
  RooChebychev bkg("bkg","background p.d.f",x,RooArgList(c0,c1,c2));
  //bkg from etap sideband
  bkg_sideband->Smooth(1000);
  RooDataHist dh2("dh2","dh2",x,bkg_sideband);
  RooHistPdf bkg2("bkg2","bkg_sideband_pdf",RooArgSet(x),dh2);
  //bkg from phsp
  RooRealVar a1("a1","coefficient a#1",1,-10.,10.);
  RooRealVar a2("a2","coefficient a#2",1,-10.,10.);
  //RooGenericPdf bkg3("bkg3","pow(x-1.2368,0.5)+a1*pow(x-1.2368,1.5)+a2*pow(x-1.2368,2.5)",RooArgSet(x,a1,a2));
  RooChebychev bkg3_p1("bkg3_p1","bkg3_p1",x,RooArgList(a1,a2));
  RooGenericPdf bkg3_p2("bkg3_p2","pow(x-1.2368,0.5)",RooArgSet(x));
  //RooProdPdf bkg3("bkg3","bkg_phsp",RooArgSet(bkg3_p1,bkg3_p2));
  //RooChebychev bkg3("bkg3","bkg_phsp",x,RooArgList(a1,a2));
  RooDataHist dh3("dh3","dh3",x,bkg_phsp);
  RooHistPdf bkg3("bkg3","bkg_phsp",RooArgSet(x),dh3);
  //events
  RooRealVar nsig1("nsig1","number of signal1 events",100,10,500.);
  RooRealVar nsig2("nsig2","number of signal2 events",1000,100,2000.);
  RooRealVar nsig3("nsig3","number of signal3 events",300,10,500.);
  RooRealVar nsig4("nsig4","number of signal4 events",300,10,500.);
  RooRealVar nbkg2("nbkg2","number of background2 events",608.221);  
  RooRealVar nbkg3("nbkg3","number of background3 events",1000,0,3000);
  //RooAddPdf sum("sum","sig+bkg",RooArgList(sig2,bkg2,bkg3),RooArgList(nsig2,nbkg2,nbkg3));
  //RooAddPdf sum("sum","sig+bkg",RooArgList(bkg2,bkg3),RooArgList(nbkg2,nbkg3));
  //RooAddPdf sum("sum","sig+bkg",RooArgList(sig2,sig3,sig4,bkg2,bkg3),RooArgList(nsig2,nsig3,nsig4,nbkg2,nbkg3));
  //RooAddPdf sum("sum","sig+bkg",RooArgList(sig1,sig3,sig4,bkg2,bkg3),RooArgList(nsig1,nsig3,nsig4,nbkg2,nbkg3));
  //RooAddPdf sum("sum","sig+bkg",RooArgList(sig1,sig2,sig4,bkg2,bkg3),RooArgList(nsig1,nsig2,nsig4,nbkg2,nbkg3));
  RooAddPdf sum("sum","sig+bkg",RooArgList(sig1,sig2,sig3,bkg2,bkg3),RooArgList(nsig1,nsig2,nsig3,nbkg2,nbkg3));
  //RooAddPdf sum("sum","sig+bkg",RooArgList(sig1,sig2,sig3,sig4,bkg2,bkg3),RooArgList(nsig1,nsig2,nsig3,nsig4,nbkg2,nbkg3));
  
  data = new RooDataHist("data","dataset with x",x,m);
  TCanvas *myCanvas = new TCanvas();
  myCanvas->Divide(1,1);
  myCanvas->SetFrameLineWidth(3);
  myCanvas->SetFillColor(10);
  myCanvas->cd(1);
  gPad->SetTopMargin(0.004);
  gPad->SetRightMargin(0.05);
  gPad->SetLeftMargin(0.18);
  gPad->SetBottomMargin(0.18);
  gPad->SetFrameLineWidth(2);
  gPad->SetFillColor(0);
  gPad->SetFrameFillColor(0);
  
  RooPlot* xframe = x.frame(Name("xframe"),Title(" "));
  xframe->GetYaxis()->SetTitle("Events/(0.02GeV/c^{2})");
  sum.fitTo(*data,"ER");
  data->plotOn(xframe);
  sum.plotOn(xframe);
  sum.plotOn(xframe,Components(bkg2),LineStyle(2),LineColor(3));
  sum.plotOn(xframe,Components("bkg2"),LineStyle(3),LineColor(4));
  sum.plotOn(xframe,Components("bkg3"),LineStyle(3),LineColor(2));
  sum.plotOn(xframe,Components("bkg2,bkg3"),LineStyle(5),LineColor(6));
  //sum.plotOn(xframe,Components(sig),LineStyle(1),LineColor(1)) ;
  //sum.paramOn(xframe,Parameters(RooArgSet(mass,width,nsig)), Format("NELU",AutoPrecision(1)), Layout(0.6,0.9,0.9));
  xframe->GetXaxis()->SetTitle("M_{#eta'#pi^{+}#pi^{-}}(GeV/c^{2})");

  xframe->SetLineWidth(2.);
  xframe->SetLineColor(1);
  xframe->GetYaxis()->SetLabelOffset(0.012);
  xframe->GetYaxis()->SetTitleOffset(1.);
  xframe->GetXaxis()->SetLabelOffset(0.012);
  xframe->GetXaxis()->SetTitleOffset(0.95);
  xframe->GetXaxis()->SetTitleSize(0.08);
  xframe->GetXaxis()->SetLabelSize(0.06);
  xframe->GetYaxis()->SetTitleSize(0.08);
  xframe->GetYaxis()->SetLabelSize(0.06);

  xframe->SetMarkerSize(1.5);
  xframe->Draw();
}
