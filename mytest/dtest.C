#include "/workfs/bes/lify/package/include/rootall.h"

void dtest()
{

	SetMyStyle();
	//SetStyle();
	TFile* f=new TFile("./out.root","READ");
	TFile* fout=new TFile("./f.root","RECREATE");
	TTree* t=(TTree*)f->Get("save");
	double umiss,mmiss2;
	t->SetBranchAddress("umiss",&umiss);
	t->SetBranchAddress("mmiss2",&mmiss2);
	TH1F* h_umiss=new TH1F("h_umiss","umiss",100,-0.2,3);
	TH1F* h_mmiss=new TH1F("h_mmiss","mmiss",100,-0.2,3);
//	h_umiss->GetXaxis()->SetTitle("U_{miss}[GeV]");
//	h_umiss->GetYaxis()->SetTitle("Events");
//	h_umiss->SetTitle("U_{miss}");
//	h_umiss->GetXaxis()->CenterTitle();                         
//	h_umiss->GetYaxis()->CenterTitle();                         
	TH1F** hh=GenTH1F("ha",4,0,3);
	for(int i=0;i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		h_umiss->Fill(umiss);
		h_mmiss->Fill(mmiss2);
		hh[0]->Fill(umiss);
	}
//	FormatData(h_umiss);
//	FormatMC2(h_mmiss);
	
//	x->SetBinLabel(10,"aaa");
	char *a="aaaa";
	TString *ss=new TString();
	*ss=a;
	*ss+="bbb";
//	TString s=a;
//	s+="bbbb";
	cout<<*ss<<endl;
	
//	fout->cd();
//	TCanvas* c_umiss = new TCanvas("c_umiss","_umiss",800,600);
	
//	h_mmiss->GetXaxis()->SetTitle("a");
//	h_mmiss->GetYaxis()->SetTitle("a");

//	h_mmiss->SetLineColor(kBlue);
	TCanvas** cs=GenCanvas(1,"c");	
	cs[0]->SetName("hmiss");
	cs[0]->SetTitle("miss energy");
	cs[0]->cd();
	TPad** c=GenPad(1);
	c[0]->cd();
//	FormatFill(h_umiss);
//	FormatMC4(h_umiss);
	FormatData(h_umiss);
	FormatFill(h_mmiss,6);
	h_umiss->SetTitle("aaa");
	NameAxis(h_umiss,"mya","myb","myc");
	drawData(h_umiss,h_mmiss);
//	h_umiss->Draw();
//	TLatex *l1=new TLatex(.09,.92,"#color[4]{B}#color[2]{E}#color[3]{S}#color[1]{III}");
//	l1->SetNDC();
//	l1->SetTextFont(12);
//	l1->SetTextFont(22);
//	l1->SetTextFont(32);
//	l1->SetTextFont(42);
//	l1->SetTextFont(62);
//	l1->SetTextFont(72);
//	l1->SetTextFont(82);
//	l1->SetTextFont(92);
//	l1->SetTextFont(102);
//	l1->SetTextFont(112);
//	l1->SetTextFont(122);
//	l1->SetTextFont(132);
//	l1->SetTextSize(0.06);
//	l1->SetTextFont(142);
//	l1->SetTextFont(162);
//	l1->DrawClone();
//	cs[0]->Write();
	WriteBes3();
	WritePreliminary();

//	c[1]->cd();
//	hh[0]->Draw();
//	WriteBes3();
//	WritePreliminary();

//	NameAxis(h_umiss,"a","b");
//	FormatLine(h_umiss,3);
	TLegend *leg1=ModLeg(0.5,.74,.7,.9);
	leg1->AddEntry(hh[0],"J/#psi->e^{+}e^{-}","LEP");
	leg1->AddEntry(h_mmiss,"aa","L");
	leg1->AddEntry(hh[0],"aa","F");
//	leg1->AddEntry(hh[0],"aa","F");
//	leg1->AddEntry(hh[0],"aa","F");
//	leg1->AddEntry(hh[0],"aa","F");
//	leg1->AddEntry(hh[0],"aa","F");
	leg1->DrawClone();
//	MakeLegend(h_mmiss,"umiss",h_mmiss,"mmiss2",h_mmiss,"ccad");
/*
	cs[1]->cd();
//	c[0]->Draw();	
	h_umiss->Draw();
	h_mmiss->Draw("same");
	WriteBes3();
	
	WritePreliminary();
//	cs[1]->Write();
//	fout->Close();
//	c_umiss->SetLogx();
//	PlotScatter("aa",h_umiss,1);
*/
}
