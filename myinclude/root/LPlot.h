/**********************************************************
 *                                                        *
 *         BES III Plotstyle: format functions            *
 *                                                        *
 *         August 2009, Niklaus Berger                    *
 *         nberger@ihep.ac.cn                             *
 *                                                        *
 *********************************************************/

//#include "bes3plotstyle.h"

#include <TH1.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLatex.h>
#include <TList.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TGraph.h>

#include <iostream>

// Format for data points
template <class Type>
void FormatData(Type* datahist){
	datahist->SetMarkerStyle(20);
	datahist->SetMarkerColor(1);
	datahist->SetMarkerSize(0.7);
	datahist->SetLineWidth(2);
	datahist->SetLineColor(1);
	FormatAxis(datahist->GetXaxis());
	FormatAxis(datahist->GetYaxis());
}

//
// Format for MC line

template <class Type>
//void ModLine(Type* mchist , Color_t icolor=2 , Style_t istyle=1 , Width_t iwidth=2 ){
void ModLine(Type* mchist , Int_t icolor = 2 , Int_t istyle = 1 , Double_t iwidth = 2. ){
	mchist->SetLineColor(icolor);
	mchist->SetLineWidth(iwidth);
	mchist->SetLineStyle(istyle);
}

template <class Type>
void ModFill(Type* mchist,int icolor=4,int istyle=1001){
	mchist->SetFillColor(icolor);
	mchist->SetLineColor(icolor);
	mchist->SetLineWidth(0);
	mchist->SetFillStyle(istyle);
}

template <class Type>
void ModData(Type* mchist,int mstyle=20, int mcolor=1, double msize=0.3, double lcolor=1,int lwidth=2){
	mchist->SetMarkerStyle(mstyle);
	mchist->SetMarkerColor(mcolor);
	mchist->SetMarkerSize(msize);
	mchist->SetLineColor(lcolor);
	mchist->SetLineWidth(lwidth);
}



template <class Type>
void FormatMC(Type* mc1hist){
	mc1hist->SetLineColor(kAzure+7);
	mc1hist->SetLineWidth(0);
	mc1hist->SetFillColor(kAzure+7);
	mc1hist->SetFillStyle(3001);
//	NameAxis(mc1hist);
}


// Format for MC 0 (black line)
template <class Type>
void FormatMC0(Type* mc1hist){
	mc1hist->SetLineColor(1);
	mc1hist->SetLineWidth(2);
//	NameAxis(mc1hist);
}
// Format for MC 1 (red line)
template <class Type>
void FormatMC1(Type* mc1hist){
	mc1hist->SetLineColor(2);
	mc1hist->SetLineWidth(2);
//	NameAxis(mc1hist);
}

// Format for MC 2 (green line)
template <class Type>
void FormatMC2(Type* mc1hist){
	mc1hist->SetLineColor(3);
	mc1hist->SetLineWidth(2);
//	NameAxis(mc1hist);
}

// Format for MC 3 (blue line)
template <class Type>
void FormatMC3(Type* mc1hist){
	mc1hist->SetLineColor(4);
	mc1hist->SetLineWidth(2);
//	mc1hist->SetLineStyle(2);
//	NameAxis(mc1hist);
}


// Format for MC 4 (pink line)
template <class Type>
void FormatMC4(Type* mc1hist){
	mc1hist->SetLineColor(6);
	mc1hist->SetLineWidth(2);
//	NameAxis(mc1hist);
}

// Format for MC ( line)
template <class Type>
void FormatMC(Type* mc1hist,int color){
	mc1hist->SetLineColor(color);
	mc1hist->SetLineWidth(2);
//	NameAxis(mc1hist);
}

//
//format one Axis
void FormatAxis(TAxis * axis){
//	axis->SetLabelFont(42);
//	axis->SetTitleFont(22);
///	axis->SetTitleOffset(.62);
//	axis->SetLabelSize(0.04);
//	axis->SetTitleSize(0.06);
//	axis->SetLabelOffset(0.005);
//	axis->SetNdivisions(505);
//	axis->SetTitleFont(22);
//	axis->SetLabelFont(22);
//	axis->SetTitleColor(1);
	axis->CenterTitle();
}


//
//format and name Axis
template <class Type>
void NameAxis(Type* datahist, TString xname="", TString yname="",TString title=""){
	if(xname)
	{
		datahist->GetXaxis()->SetTitle(xname);
		FormatAxis(datahist->GetXaxis());
	}
	if(yname)
	{
		datahist->GetYaxis()->SetTitle(yname);
		FormatAxis(datahist->GetYaxis());
	}
	if(title)
	{
		datahist->SetTitle(title);
	}
}

template <class Type>
void NameAxis(Type* datahist, char * xname=NULL, char * yname=NULL,char *title=NULL){
	if(xname)
	{
		datahist->GetXaxis()->SetTitle(xname);
		FormatAxis(datahist->GetXaxis());
	}
	if(yname)
	{
		datahist->GetYaxis()->SetTitle(yname);
		FormatAxis(datahist->GetYaxis());
	}
	if(title)
	{
		datahist->SetTitle(title);
	}
}
//
//format line  graph
template <class Type>
void FormatLine(Type* hist,int color=2,double width=2)
{
	hist->SetLineColor(color);
	hist->SetLineWidth(width);
	NameAxis(hist);
}

//
//format filled  graph
template <class Type>
void FormatFill(Type* hist,int color=9,int style=3001)
{
	hist->SetFillColor(color);
	hist->SetLineWidth(0);
	hist->SetLineColor(color);
	hist->SetFillStyle(style);
}

//
// Write "BESIII" in the upper right corner
void WriteBes3(){
	TLatex *bes3=new TLatex(.11,.89,"#color[4]{B}#color[2]{E}#color[3]{S}#color[1]{III}");
	bes3->SetNDC();
	bes3->SetTextFont(132);
	bes3->SetTextSize(0.04);
	bes3->SetTextAlign(13);
	bes3->Draw();
}

// Write "Preliminary" below BESIII -
void WritePreliminary(){
	TLatex * prelim = new TLatex(0.5,0.5, "Preliminary");
	prelim->SetNDC();
	prelim->SetTextFont(32);
	prelim->SetTextSize(0.14);
	prelim->SetTextAlign(22);
	prelim->SetTextColor(kGreen);
	prelim->SetTextAngle(30);
	prelim->Draw();
}


//########################################################################################
//Add myself,		--Fengyun LI @ 2015-01-08
void SetMyStyle()
{
	//for canvas
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasBorderSize(0);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetCanvasDefH(600);
	gStyle->SetCanvasDefW(800);
	gStyle->SetCanvasDefX(0);
	gStyle->SetCanvasDefY(0);
	
	gStyle->SetPalette(1);
	gStyle->SetOptStat(1);
	gStyle->SetStatX(0.9);
	gStyle->SetStatY(0.9);
	gStyle->SetStatFont(42);
//	gStyle->SetStatFormat("6.4g");
	gStyle->SetStatBorderSize(1);
	gStyle->SetStatFontSize(.03);
	gStyle->SetTickLength(.02,"xyz");
	gStyle->SetStatStyle(0);
	
	// Format for axes
	gStyle->SetLabelFont(42,"xyz");
	gStyle->SetLabelSize(0.025,"xyz");
	gStyle->SetLabelOffset(0.005,"xyz");
	gStyle->SetNdivisions(510,"xyz");
	gStyle->SetTitleFont(62,"xyz");
	gStyle->SetTitleColor(1,"xyz");
	gStyle->SetTitleSize(0.06,"xyz");
	gStyle->SetTitleOffset(.62,"xyz");
	gStyle->SetTitleAlign(23);

	// No pad borders
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadBorderSize(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(2);
	//	gStyle->SetPadGridX(1);
	//	gStyle->SetPadGridY(1);

	//	gStyle->SetTitleFont(62);
	//	gStyle->SetTitleSize(0.045,"xyz");
	//	gStyle->SetFrameLineStyle(1);
	//	gStyle->SetFrameLineColor(1);
	//	gStyle->SetFrameLineWidth(2);
	gStyle->SetTitleX(0.5);
	gStyle->SetTitleY(0.97);
	// No error bars in x direction
	gStyle->SetErrorX(0);
	gStyle->SetLegendBorderSize(1);
	gStyle->SetHistLineColor(kRed);
	gStyle->SetHistLineWidth(2);
	gStyle->SetMarkerStyle(20);
}

//Be careful that you must creat a canvas
//befor using GenPad to draw
TPad **GenPad(int n=2,char *s=NULL)
{
	TPad** p=new TPad*[10];
	if(n==1)
	{
		p[0]=new TPad("","",0.,0.,1.,1.);
	}
	else if(n==2)
	{
		p[0]=new TPad("","",0.,0.,.5,1.);
		p[1]=new TPad("","",.5,0.,1.,1.);
	}
	else if(n==4)
	{
		p[0]=new TPad("","",0.,.5,.5,1.);
		p[1]=new TPad("","",.5,.5,1.,1.);
		p[2]=new TPad("","",0.,0.,.5,.5);
		p[3]=new TPad("","",.5,0.,1.,.5);
	}
	else if(n==6)
	{
		if(!s)
		{
			p[0]=new TPad("","",0.,.5,.33,1.);
			p[1]=new TPad("","",.33,.5,.66,1.);
			p[2]=new TPad("","",0.66,.5,.99,1.);
			p[3]=new TPad("","",0.,0,.33,.5);
			p[4]=new TPad("","",.33,0,.66,.5);
			p[5]=new TPad("","",0.66,0,.99,.5);
		}
		else
		{
			p[0]=new TPad("","",0.,.66,.5,1.);
			p[1]=new TPad("","",.5,.66,1.,1.);
			p[2]=new TPad("","",0.,.33,.5,.66);
			p[3]=new TPad("","",.5,.33,1.,.66);
			p[4]=new TPad("","",0.,0.,.5,.33);
			p[5]=new TPad("","",.5,0.,1.,.33);
		}
	}
	else cout<<"Invalid Input!"<<endl;
	for(int i=0;i<n;i++)
	{
		p[i]->SetFrameLineWidth(2);
		p[i]->Draw();
	}
	return p;
}

 

TH1F **GenTH1F(char *histname,int n=1,int nbins=100,double xlow=0.,double xhigh=1.)
{
	TString *head=new TString();
	*head=histname;
	*head+="_h";
	TString *tmp_head=new TString();
	TH1F **p=new TH1F*[10];

	for(Long_t i=0;i<n;i++)
	{	
		*tmp_head=*head+i;
		cout<<*tmp_head<<endl;
		p[i]=new TH1F(*tmp_head,*tmp_head,nbins,xlow,xhigh);	
		FormatAxis(p[i]->GetXaxis());
		FormatAxis(p[i]->GetYaxis());
	}
	
	return p;	
}

TH1F **GenTH1F(char *histname,int n=1,double xlow=0.,double xhigh=1.)
{
	TString *head=new TString();
	*head=histname;
	*head+="_h";
	TString *tmp_head=new TString();
	TH1F **p=new TH1F*[10];
	int nbins=100;

	for(Long_t i=0;i<n;i++)
	{	
		*tmp_head=*head+i;
		cout<<*tmp_head<<endl;
		p[i]=new TH1F(*tmp_head,*tmp_head,nbins,xlow,xhigh);	
		FormatAxis(p[i]->GetXaxis());
		FormatAxis(p[i]->GetYaxis());
	}
	
	return p;	
}

TCanvas **GenCanvas(int n=1, char *histname="c",int width=1200,int height=900)
{
	TString *head=new TString();
	*head+=histname;
	TString *tmp=new TString();
	TCanvas **p=new TCanvas*[40];
	for(Long_t i=0;i<n;i++)
	{
		*tmp=*head+i;
		p[i]=new TCanvas(*tmp,*tmp,width,height);	
	}
	return p;	
}

TLegend* ModLeg(double x1=0.5,double y1=.74,double x2=.7,double y2=.87)
{
	TLegend* leg=new TLegend(x1,y1,x2,y2);
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->SetTextAlign(12);
//	leg->SetTextSizePixels(100);
//	leg->Draw();
	return leg;
}


//
//draw line hist as order
/*
template <class Type>
void drawLine(Type* a,Type* b,Type *c=NULL,Type *d=NULL,Type *e=NULL)
{
	int maxhist=0;
	if(c==NULL)
	{
		if((a->GetMaximum()())>=(b->GetMaximum()()))
		{
			a->Draw();
			b->Draw("same");
		}
		else
		{
			b->Draw();
			a->Draw("same");
		}		
	}
	else if(d==NULL)
	{
		maxhist=findmax(3,a->GetMaximum(),b->GetMaximum(),c->GetMaximum());
		if(maxhist==0) {a->Draw();b->Draw("same");c->Draw("same");}
		if(maxhist==1) {b->Draw();a->Draw("same");c->Draw("same");}
		if(maxhist==2) {c->Draw();a->Draw("same");b->Draw("same");}
	}
	else if(e==NULL)
	{
		maxhist=findmax(4,a->GetMaximum(),b->GetMaximum(),c->GetMaximum(),d->GetMaximum());
		if(maxhist==0) {a->Draw();b->Draw("same");c->Draw("same");d->Draw("same");}
		if(maxhist==1) {b->Draw();a->Draw("same");c->Draw("same");d->Draw("same");}
		if(maxhist==2) {c->Draw();b->Draw("same");a->Draw("same");d->Draw("same");}
		if(maxhist==3) {d->Draw();b->Draw("same");c->Draw("same");a->Draw("same");}
	}
	else
	{
		maxhist=findmax(5,a->GetMaximum(),b->GetMaximum(),c->GetMaximum(),d->GetMaximum(),e->GetMaximum());
		if(maxhist==0) {a->Draw();b->Draw("same");c->Draw("same");d->Draw("same");e->Draw("same");}
		if(maxhist==1) {b->Draw();a->Draw("same");c->Draw("same");d->Draw("same");e->Draw("same");}
		if(maxhist==2) {c->Draw();b->Draw("same");a->Draw("same");d->Draw("same");e->Draw("same");}
		if(maxhist==3) {d->Draw();b->Draw("same");c->Draw("same");a->Draw("same");e->Draw("same");}
		if(maxhist==4) {e->Draw();b->Draw("same");c->Draw("same");d->Draw("same");a->Draw("same");}
	}
}
*/

//
//draw data and line hist as order
template <class Type>
void drawData(Type* a,Type* b)
{
	if((a->GetMaximum())>=(b->GetMaximum()))
	{
		a->Draw("e");
		b->Draw("same");
	}
	else
	{
		b->Draw();
		a->Draw("esame");
	}		
}

//draw mc and line hist as order
template <class Type>
void drawMC(Type* a,Type* b)
{
	if((a->GetMaximum())>=(b->GetMaximum()))
	{
		a->Draw("");
		b->Draw("same");
	}
	else
	{
		b->Draw();
		a->Draw("same");
	}		
}
/*
	else if(d==NULL)
	{
		Double_t aa[3]=a->GetMaximum(),b->GetMaximum(),c->GetMaximum()};
		maxno=aa[0];
		for(int i=1;i<3;i++)
		{
			if(maxno>aa[i])
			{
				maxno=aa[i];
				maxhist=i;
			}
		}
		if(maxhist==0) {a->Draw("e");b->Draw("same");c->Draw("same");}
		if(maxhist==1) {b->Draw();a->Draw("esame");c->Draw("same");}
		if(maxhist==2) {c->Draw();a->Draw("esame");b->Draw("same");}
	}
	else if(e==NULL)
	{
		Double_t aa[4]={a->GetMaximum(),b->GetMaximum(),c->GetMaximum(),d->GetMaximum()};
		maxno=aa[0];
		for(int i=1;i<4;i++)
		{
			if(maxno>aa[i])
			{
				maxno=aa[i];
				maxhist=i;
			}
		}
		if(maxhist==0) {a->Draw("e");b->Draw("same");c->Draw("same");d->Draw("same");}
		if(maxhist==1) {b->Draw();a->Draw("esame");c->Draw("same");d->Draw("same");}
		if(maxhist==2) {c->Draw();b->Draw("same");a->Draw("esame");d->Draw("same");}
		if(maxhist==3) {d->Draw();b->Draw("same");c->Draw("same");a->Draw("esame");}
	}
	else
	{
		Double_t aa[5]={a->GetMaximum(),b->GetMaximum(),c->GetMaximum(),d->GetMaximum(),e->GetMaximum()};
		maxno=aa[0];
		for(int i=1;i<5;i++)
		{
			if(maxno>aa[i])
			{
				maxno=aa[i];
				maxhist=i;
			}
		}
		if(maxhist==0) {a->Draw("e");b->Draw("same");c->Draw("same");d->Draw("same");e->Draw("same");}
		if(maxhist==1) {b->Draw();a->Draw("esame");c->Draw("same");d->Draw("same");e->Draw("same");}
		if(maxhist==2) {c->Draw();b->Draw("same");a->Draw("esame");d->Draw("same");e->Draw("same");}
		if(maxhist==3) {d->Draw();b->Draw("same");c->Draw("same");a->Draw("esame");e->Draw("same");}
		if(maxhist==4) {e->Draw();b->Draw("same");c->Draw("same");d->Draw("same");a->Draw("esame");}
	}
}
*/
/*
int findmax(int n,Double_t *a)
{
	Double_t max_a=a[0];
	int max_no=0;
	for(int i=1;i<n;i++)
	{
		if(max_a<a[i]) max_a=a[i];
		max_no=i;
	}
	return max_no;
}
*/



/* 
// Make a legend; 
// position will have to change depending on the data shape
void MakeLegend(TH1 * datahist,   // Histogram with data
		char * dataname,  // Description of data
		TH1 * mc1hist, // Histogram with first MC
		char * mc1name, // Description of first MC
		TH1 * mc2hist, // Histogram with 2nd MC/BG
		char * mc2name, // Description of second MC/BG
		double xlow,      // Left edge of legend 
		//(fraction of canavas width)
		double ylow,       // Bottom edge of legend
		//(fraction of canavas height)
		double xhi,       // Right edge of legend 
		//(fraction of canavas width)
		double yhi){       // Top edge of legend
	//(fraction of canavas height)

	TLegend * leg = new TLegend(xlow, ylow, xhi, yhi);
	if(datahist && dataname)
		leg->AddEntry(datahist, dataname, "LEP");
	if(mc1hist && mc1name)
		leg->AddEntry(mc1hist, mc1name, "L");
	if(mc2hist && mc2name)
		leg->AddEntry(mc2hist, mc2name, "LF");

	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->Draw();

}


// Make a legend; 
// position will have to change depending on the data shape
void MakeLegend(TGraph * datahist,   // Graph with data
		char * dataname,  // Description of data
		TGraph * mc1hist, // Graph with first MC
		char * mc1name, // Description of first MC
		TGraph * mc2hist, // Graph with 2nd MC/BG
		char * mc2name, // Description of second MC/BG
		TGraph * mc3hist, // Graph with 3rd MC/BG
		char * mc3name, // Description of third MC/BG

		double xlow,      // Left edge of legend 
		//(fraction of canavas width)
		double ylow,       // Bottom edge of legend
		//(fraction of canavas height)
		double xhi,       // Right edge of legend 
		//(fraction of canavas width)
		double yhi){       // Top edge of legend
	//(fraction of canavas height)

	TLegend * leg = new TLegend(xlow, ylow, xhi, yhi);
	if(datahist && dataname)
		leg->AddEntry(datahist, dataname, "LEP");
	if(mc1hist && mc1name)
		leg->AddEntry(mc1hist, mc1name, "L");
	if(mc2hist && mc2name)
		leg->AddEntry(mc2hist, mc2name, "L");
	if(mc3hist && mc3name)
		leg->AddEntry(mc3hist, mc3name, "L");

	leg->SetFillColor(0);
//	leg->SetTextFont(42);
	leg->SetTextFont(32);
	leg->Draw();

}



// Make a legend (version for fit functions
// position will have to change depending on the data shape
void MakeLegend(TH1 * datahist,   // Histogram with data
		char * dataname,  // Description of data
		char ** functionnames, // list of function names
		double xlow,      // Left edge of legend 
		//(fraction of canavas width)
		double ylow,       // Bottom edge of legend
		//(fraction of canavas height)
		double xhi,       // Right edge of legend 
		//(fraction of canavas width)
		double yhi){       // Top edge of legend
	//(fraction of canavas height)

	TLegend * leg = new TLegend(xlow, ylow, xhi, yhi);
	if(datahist && dataname)
		leg->AddEntry(datahist, dataname, "LEP");

	TList* list = datahist->GetListOfFunctions();
	unsigned int nfun = list->GetEntries();

	for(unsigned int i =0;  i < nfun; i++){
		TF1* f1 = (TF1*)(list->At(i));
		leg->AddEntry(f1, functionnames[i], "L");
	}
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->Draw();

}





// Set the general style options
void SetStyle(){
	// No Canvas Border
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasBorderSize(0);
	// White BG
	gStyle->SetCanvasColor(10);
	// Format for axes
	gStyle->SetLabelFont(42,"xyz");
	gStyle->SetLabelSize(0.06,"xyz");
	gStyle->SetLabelOffset(0.01,"xyz");
	gStyle->SetNdivisions(510,"xyz");
	gStyle->SetTitleFont(42,"xyz");
	gStyle->SetTitleColor(1,"xyz");
	gStyle->SetTitleSize(0.07,"xyz");
	gStyle->SetTitleOffset(1.15,"xyz");
	// No pad borders
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadBorderSize(0);
	// White BG
	gStyle->SetPadColor(10);
	// Margins for labels etc.
	gStyle->SetPadLeftMargin(0.17);
	gStyle->SetPadBottomMargin(0.17);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadTopMargin(0.05);
	// No error bars in x direction
	gStyle->SetErrorX(0);
	// Format legend
	gStyle->SetLegendBorderSize(0);
}

// Style options for "final" plots
// (no stat/fit box)
void SetPrelimStyle(){
	gStyle->SetOptDate(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	gStyle->SetOptTitle(0);
}

// Style options for internal meetings
// (stat/fit box)
void SetMeetingStyle(){
	gStyle->SetOptDate(0);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(1111);
	gStyle->SetStatBorderSize(1);
	gStyle->SetStatColor(10);
	gStyle->SetStatFont(42);
	gStyle->SetStatFontSize(0.03);
	gStyle->SetOptFit(1111);
}


// Plot a data MC plot
void PlotDataMC(char * filename,  // Name for the output files, 
		// without extension 
		TH1 * datahist,   // Histogram with data
		char * dataname,  // Description of data
		TH1 * mc1hist, // Histogram with first MC
		char * mc1name, // Description of first MC
		TH1 * mc2hist, // Histogram with 2nd MC/BG
		char * mc2name, // Description of second MC/BG
		int prelim,    // Use 1 for Preliminary plot
		// 2 for a publication plot
		// and 0 for a meeting plot with 
		// stat and fit box
		double xlow, // Left edge of legend 
		//(fraction of canavas width)
		double ylow,  // Bottom edge of legend
		//(fraction of canavas height)
		double xhi,  // Right edge of legend 
		//(fraction of canavas width)
		double yhi){  // Top edge of legend
	//(fraction of canavas height)

	SetStyle();
	if(prelim)
		SetPrelimStyle();
	else
		SetMeetingStyle();

	TCanvas * c1 = new TCanvas("bes3plots","BESIII Plots", 800,600);

	FormatData(datahist);
	if(mc1hist)
		FormatMC1(mc1hist);
	if(mc2hist)
		FormatMC2(mc2hist);


	datahist->Draw("axis");
	if(mc2hist)
		mc2hist->Draw("same");
	if(mc1hist)
		mc1hist->Draw("same");
	datahist->Draw("Esame");
	datahist->Draw("axissame");
	if(prelim){
		WriteBes3();
		if(prelim == 1)
			WritePreliminary();
	}
	MakeLegend(datahist, dataname,
			mc1hist,  mc1name,
			mc2hist,  mc2name);


	char filenameall[256];
	sprintf(filenameall,"%s.eps", filename);
	c1->SaveAs(filenameall);
	sprintf(filenameall,"%s.png", filename);
	c1->SaveAs(filenameall);
}


// Plot data with one or more (fit) functions
// Functions should be part of the data histograms list of functions
// (i.e. perform fits with the "+" option or add other functions via
// datahist->GetListOfFunctions->Add(TF1 * function))
// functionnames should have at least as many elements as the function
// list
void PlotDataFit(char * filename,  // Name for the output files, 
		// without extension 
		TH1F * datahist,   // Histogram with data
		char * dataname,  // Description of data
		char ** functionnames,// Names of associated functions
		int prelim,    // Use 1 for Preliminary plot
		// 2 for a publication plot
		// and 0 for a meeting plot with 
		// stat and fit box
		double xlow, // Left edge of legend 
		//(fraction of canavas width)
		double ylow,  // Bottom edge of legend
		//(fraction of canavas height)
		double xhi,  // Right edge of legend 
		//(fraction of canavas width)
		double yhi){  // Top edge of legend
	//(fraction of canavas height)


	SetStyle();
	if(prelim)
		SetPrelimStyle();
	else
		SetMeetingStyle();

	TCanvas * c1 = new TCanvas("bes3plots","BESIII Plots", 800,600);

	FormatData(datahist);

	int linestyles[] = {1,2,3,7,9,10};
	//int linecolors[]   = {2,4,kGreen+2,kOrange+7,kMagenta,2};
	int linecolors[]   = {2,4,6, 9,8,2};

	TList* list = datahist->GetListOfFunctions();
	TH1F * datacopy = new TH1F(*datahist); 
	datacopy->Draw("axis");


	unsigned int nfun = list->GetEntries();

	if(nfun > 6){
		std::cout << "ERROR: More than six associated functions not forseen" << std::endl;
		return;
	}


	for(unsigned int i =0;  i < nfun; i++){
		TF1* f1 = (TF1*)(list->At(i));
		f1->SetLineColor(linecolors[i]);
		f1->SetLineStyle(linestyles[i]);
		f1->Draw("same");
	}

	MakeLegend(datahist, dataname, functionnames,xlow, ylow, xhi, yhi);

	datacopy->Draw("Esame");
	datacopy->Draw("axissame");

	if(prelim){
		WriteBes3();
		if(prelim==1)
			WritePreliminary();
	}

	char filenameall[256];
	sprintf(filenameall,"%s.eps", filename);
	c1->SaveAs(filenameall);
	sprintf(filenameall,"%s.png", filename);
	c1->SaveAs(filenameall);


}


// Scatter plot
void PlotScatter(char * filename,  // Name for the output files, 
		// without extension 
		TH1 * datahist,   // Histogram with data
		int prelim       // preliminary plot
		){


	SetStyle();
	if(prelim)
		SetPrelimStyle();
	else
		SetMeetingStyle();

	TCanvas * c1 = new TCanvas("bes3plots","BESIII Plots", 800,600);

	FormatData(datahist);

	if(datahist->Integral() > 5000)
		datahist->SetMarkerStyle(1);
	else if(datahist->Integral() > 500)
		datahist->SetMarkerSize(0.5);


	datahist->Draw("");

	if(prelim){
		WriteBes3();
		if(prelim==1)
			WritePreliminary();
	}


	char filenameall[256];
	sprintf(filenameall,"%s.eps", filename);
	c1->SaveAs(filenameall);
	sprintf(filenameall,"%s.png", filename);
	c1->SaveAs(filenameall);
}
*/
