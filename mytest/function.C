
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void function()
{
	TF1 *f1=new TF1("f1","TMath::Pi()*sqrt(sin(x)*sin(x)-pow(sin(x),4))/2",0,TMath::Pi());
	TF1 *f2=new TF1("f1","x*sqrt(sin(x)*sin(x)-pow(sin(x),4))",0,TMath::Pi());
	f2->SetLineColor(kBlue);
	f1->SetLineColor(6);
	double sumf1=f1->Integral(0,TMath::Pi());;
	double sumf2=f2->Integral(0,TMath::Pi());;
	
	cout<<sumf1<<endl;
	cout<<sumf2<<endl;
	
	TLegend *leg=ModLeg(0.2,0.82,0.4,0.92);
	leg->AddEntry(f1,"f1(x)=#frac{#pi}{2}#times#sqrt{sin^{2}x-sin^{4}x}","L");
	leg->AddEntry(f2,"f2(x)=x#times#sqrt{sin^{2}x-sin^{4}x}","L");


	NameAxis(f1,"x","f(x)");
	NameAxis(f2,"x","f(x)");
	cdStyle("myStyle");
	TCanvas *c = new TCanvas("c","");
	f2->Draw();
	f1->Draw("same");
	leg->DrawClone();
	TLatex ltx;
	ltx.SetNDC();
	ltx.SetTextSize(0.04);
	ltx.SetTextColor(2);
	ltx.DrawLatex(0.2,0.73,Form("Integral in (0,#pi)  for f1(x):	 %.3f ",sumf1));
	ltx.DrawLatex(0.2,0.67,Form("Integral in (0,#pi)  for f2(x):	 %.3f ",sumf2));

	c->Modified();
	c->SaveAs("func.pdf");
}
