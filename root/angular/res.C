#include "/workfs/bes/lify/package/include/rootall.h"
void res()
{
	double pi=TMath::Pi();
	SetMyStyle();
	TFile *fout=new TFile("outpic.root","RECREATE");
///////////////////////////////////////////////////////////////
	TF1 *resf=new TF1("resf","1+x^2",-1,1);
	resf->SetTitle("Resonance cross-section for J/#psi -> e^{+}e^{-}");
	NameAxis(resf,"cos#theta_{e^{+}}","d#sigma/d#Omega");
	TPaveText *p11=new TPaveText(.4,.75,.8,.9,"NDC");
	p11->AddText("#frac{d#sigma_{res}}{d#Omega}~1+cos^{2}#theta_{e^{+}}");	
	TF1 *resfthe=new TF1("resf","1+pow(TMath::Cos(x),2)",0,pi);
	resfthe->SetTitle("Resonance cross-section for J/#psi -> e^{+}e^{-}");
	TPaveText *p12=new TPaveText(.4,.75,.8,.9,"NDC");
	p12->AddText("#frac{d#sigma_{res}}{d#Omega}~1+cos^{2}#theta_{e^{+}}");	
	NameAxis(resfthe,"#theta_{e^{+}} [rad]","d#sigma/d#Omega");
///////////////////////////////////////////////////////////////
	TF1 *qedf=new TF1("qedf","pow((3+x^2)/(1-x),2)",-0.999,0.999);
	qedf->SetTitle("qed cross-section for e^{+}e^{-}->e^{+}e^{-}");
	NameAxis(qedf,"cos#theta_{e^{+}}","d#sigma/d#Omega");
	TPaveText *p21=new TPaveText(.4,.75,.8,.9,"NDC");
	p21->AddText("#frac{d#sigma_{qed}}{d#Omega}~(#frac{3+cos^{2}#theta_{e^{+}}}{1-cos#theta_{e^{+}}})^{2}");	
	TF1 *qedfthe=new TF1("qedfthe","pow((3+TMath::Cos(x)^2)/(1-TMath::Cos(x)),2)",0.001,pi-0.001);
	qedfthe->SetTitle("qed cross-section for e^{+}e^{-}->e^{+}e^{-}");
	NameAxis(qedfthe,"cos#theta_{e^{+}}","d#sigma/d#Omega");
	TPaveText *p22=new TPaveText(.4,.75,.8,.9,"NDC");
	p22->AddText("#frac{d#sigma_{qed}}{d#Omega}~(#frac{3+cos^{2}#theta_{e^{+}}}{1-cos#theta_{e^{+}}})^{2}");	
///////////////////////////////////////////////////////////////
	TF1 *intf=new TF1("intf","-(1+x^2)+(1+x)^2/(1-x)",-0.999,0.999);
	intf->SetTitle("interference cross-section for e^{+}e^{-}->e^{+}e^{-}");
	NameAxis(intf,"cos#theta_{e^{+}}","d#sigma/d#Omega");
	TPaveText *p31=new TPaveText(.4,.75,.8,.9,"NDC");
	p31->AddText("#frac{d#sigma_{int}}{d#Omega}~(#frac{3+cos^{2}#theta_{e^{+}}}{1-cos#theta_{e^{+}}})^{2}");	
	TF1 *intfthe=new TF1("qedfthe","-(1+TMath::Cos(x)^2)+(1+TMath::Cos(x))^2/(1-TMath::Cos(x))",0.001,pi-0.001);
	intfthe->SetTitle("interference cross-section for e^{+}e^{-}->e^{+}e^{-}");
	NameAxis(intfthe,"cos#theta_{e^{+}}","d#sigma/d#Omega");
	TPaveText *p32=new TPaveText(.4,.75,.8,.9,"NDC");
	p32->AddText("#frac{d#sigma_{qed}}{d#Omega}~(#frac{3+cos^{2}#theta_{e^{+}}}{1-cos#theta_{e^{+}}})^{2}");	
///////////////////////////////////////////////////////////////
	fout->cd();
	TCanvas **c=GenCanvas(1,"c",600,800);
	c[0]->cd();
	TPad **p1=GenPad(6,"L");	

	p1[0]->cd();
	resf->Draw();
	p11->Draw();

	p1[1]->cd();
	resfthe->Draw();
	p12->Draw();

	p1[2]->cd();
	qedf->Draw();
	p21->Draw();

	p1[3]->cd();
	qedfthe->Draw();
	p22->Draw();
	p1[2]->SetLogy();
	p1[3]->SetLogy();

	p1[4]->cd();
	intf->Draw();
	p31->Draw();

	p1[5]->cd();
	intfthe->Draw();
	p32->Draw();
	p1[4]->SetLogy();
	p1[5]->SetLogy();
	c[0]->Write();
	fout->Close();
}

