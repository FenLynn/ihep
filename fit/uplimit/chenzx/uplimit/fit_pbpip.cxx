#include<TH2.h>
#include<TStyle.h>
#include<TCanvas.h>
#include<cmath>
#include <iostream.h>
#include <iomanip.h>
void fit_pbpip(){
  gStyle->SetOptTitle(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
    
  gStyle->SetOptTitle(0);
  gSystem->Load("libRooFit") ;
  using namespace RooFit ;
  TChain *fChain = new TChain("final");
  fChain->Add("/panfs/panfs.ihep.ac.cn/home/data/chenzx/work/data/pppipi/JPsi/pppipitest.root");
  TH1D *m = new TH1D("m","",100,1.35,1.75);
  TH1D *n = new TH1D("n","",100,1.35,1.75);
  TH1D *h = new TH1D("h","",100,1.35,1.75);
//  fChain->Draw("m_ggpipi>>m","m_ggpipi>0.92&&m_ggpipi<1.0&&m_pipietap>1.28&&m_pipietap<2.8");
  fChain->Draw("pb_pipm>>m","chi2<40&&fabs(p_pipm-1.21)>0.12&&fabs(pb_pimm-1.21)>0.12&&p_pimm-1.116>0.01&&pb_pipm-1.116>0.01");
  fChain->Draw("p_pimm>>n","chi2<40&&fabs(p_pipm-1.21)>0.12&&fabs(pb_pimm-1.21)>0.12&&p_pimm-1.116>0.01&&pb_pipm-1.116>0.01");
//  fChain->Draw("pb_pipm>>m");
//  fChain->Draw("p_pimm>>n");
  h->Add(m,n);
  h->Draw();
  RooRealVar x("x","M_{#bar{p}#pi^{+}} (GeV/c^{2})",1.35,1.75);
  RooDataHist *data = new RooDataHist("data","dataset with x",x,h);
  //bw1 for etap
  RooRealVar b0("b0","coefficient b#0",-1.79873);
  RooRealVar b1("b1","coefficient b#1",2.67211);
  RooRealVar b2("b2","coefficient b#2",-0.929692);
  RooGenericPdf eff("eff","b0+b1*x+b2*x*x",RooArgSet(x,b0,b1,b2));

  RooRealVar mass1("mass1","mass of Breit-Wigner1",1.5,1.45,1.55);
  RooRealVar width1("width1","width of Breit-Wigner1",0.1,0.05,0.3);
  RooRealVar sigma1("sigma1","sigma of Breit-Wigner1",0.002);
  RooVoigtian bw1("bw1","Breit-Wigner1",x,mass1,width1,sigma1);
  RooProdPdf sig1("sig1","pdf of signal",RooArgSet(bw1,eff));

  RooRealVar mass2("mass2","mass of Breit-Wigner2",1.49,1.47,1.52);
  RooRealVar width2("width2","width of Breit-Wigner2",0.036,0,0.1);
  RooRealVar sigma2("sigma2","sigma of Breit-Wigner2",0.002);
  RooVoigtian bw2("bw2","Breit-Wigner2",x,mass2,width2,sigma2);
  RooProdPdf sig2("sig2","pdf of signal2",RooArgSet(bw2,eff));

  RooRealVar frac("frac","",0.5,0,1);
  RooAddPdf sig("sig","",bw1,bw2,frac);
/*
  RooRealVar mass3("mass3","mass of Breit-Wigner3",1.5,1.1,1.8);
  RooRealVar width3("width3","width of Breit-Wigner3",0.1,0,1);
  RooRealVar sigma3("sigma3","sigma of Breit-Wigner3",0.002);
  RooVoigtian bw3("bw3","Breit-Wigner3",x,mass3,width3,sigma3);
  RooProdPdf sig3("sig3","pdf of signal3",RooArgSet(bw3));
*/

//  RooRealVar a("a","asysmetic",1,0,10);
//  RooRealVar n("n","asysmetic",12.7);
//  RooCBShape sig1("sig1","signal pdf",x,mass1,width1,a,n);
  //bkg from phsp
//  RooRealVar a1("a1","coefficient a#1",-0.8,-10,10);
//  RooRealVar a2("a2","coefficient a#2",-0.05,-10,10);
//  RooRealVar a3("a3","coefficient a#3",-0.032,-10,10);
//  RooRealVar a1("a1","coefficient a#1",-0.856313);
//  RooRealVar a2("a2","coefficient a#2",-0.0976255);
//  RooRealVar a3("a3","coefficient a#3",-0.0791109);
//  RooRealVar a4("a4","coefficient a#4",-0.00640193);

  RooRealVar a1("a1","coefficient a#1",0,-1000000,1000000);
  RooRealVar a2("a2","coefficient a#2",0,-1000000,1000000);
  RooRealVar a3("a3","coefficient a#3",0,-1000000,1000000);
  RooRealVar a4("a4","coefficient a#4",0,-1000000,1000000);
  RooChebychev bkg("bkg","bkg",x,RooArgList(a1,a2,a3,a4));
//  RooGenericPdf bkg("bkg","a1*(1.8-x)+a2*(1.8-x)*(1.8-x)+a3*(1.8-x)*(1.8-x)*(1.8-x)+a4*(1.8-x)*(1.8-x)*(1.8-x)*(1.8-x)",RooArgSet(x,a1,a2,a3,a4));
//  RooGenericPdf bkg("bkg","a1*(1.8-x)+a2*(1.8-x)*(1.8-x)+a3*(1.8-x)*(1.8-x)*(1.8-x)",RooArgSet(x,a1,a2,a3));
//  RooGenericPdf bkg("bkg","a1*(1.8-x)+a2*(1.8-x)*(1.8-x)",RooArgSet(x,a1,a2));

  RooRealVar nsig("nsig","number of signal1 events",4800,0,160000);
  RooRealVar nsig1("nsig1","number of signal1 events",4800,0,160000);
  RooRealVar nsig2("nsig2","number of signal2 events",4800,0,160000);
  RooRealVar nsig3("nsig3","number of signal3 events",4800,0,160000);

  RooRealVar nbkg("nbkg","number of background events",80000,1000,1000000);

  RooAddPdf model("model","sig+bkg",RooArgList(sig1,sig2,bkg),RooArgList(nsig1,nsig2,nbkg));
//  RooAddPdf model("model","sig+bkg",RooArgList(sig,bkg),RooArgList(nsig,nbkg));

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
  xframe->GetYaxis()->SetTitle("Events/(0.004GeV/c^{2})");
  double aaa=model.fitTo(*data,"ER")->minNll();
  cout<<setprecision(8)<<aaa<<endl;
  data->plotOn(xframe);
  model.plotOn(xframe);
  cout<<"chisq of fit:"<<xframe->chiSquare(11)<<endl;
//  cout << "-log(L) at minimum = "<<setprecision(8)<< model.fitTo(*data,"ER")->minNll() << endl ;
  model.plotOn(xframe,Components(bkg),LineStyle(1),LineColor(2));
//  model.plotOn(xframe,Components(sig1),LineStyle(1),LineColor(2));
//  xframe->GetXaxis()->SetTitle("M_{#bar{p}#pi^{+}}(GeV/c^{2})");
   xframe->GetXaxis()->SetTitle("M_{p#pi}(GeV/c^{2})");
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
 
  x.setRange("mwr",1.5+0.1,1.5+0.2);
  RooAbsReal* in_bkg= bkg.createIntegral(x,NormSet(x),Range("mwr")); 
  double f_in_bkg= in_bkg->getVal();
  double n_in_bkg= f_in_bkg*nbkg.getVal();
  cout<<"events of sideband' =   "<<n_in_bkg<<endl;
//  cout << "-log(L) at minimum = "<<setprecision(8)<< model.fitTo(*data,"ER")->minNll() << endl ;

}
