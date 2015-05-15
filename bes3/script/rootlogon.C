{
gROOT->SetStyle("Plain"); // remove gray background from plots
//gSystem­>Load("libMinuit.so") ;
//gSystem­>Load("/path/to/this/file/libRooFitCore.so") ;
//gSystem­>Load("/path/to/this/file/libRooFitModels.so") ;
//using namespace RooFit ;
//my own style
//gStyle->SetOptTitle(1);
//gStyle->SetOptStat(1111111);
//gStyle->SetOptFit(1111);
//gStyle->SetHistLineWidth(1);


//..BABAR style from RooLogon.C in workdir
TStyle *babarStyle= new TStyle("BABAR","BaBar approved plots style");

// use plain black on white colors
babarStyle->SetFrameBorderMode(0);
babarStyle->SetCanvasBorderMode(0);
babarStyle->SetPadBorderMode(0);
babarStyle->SetPadColor(0);
babarStyle->SetCanvasColor(0);
babarStyle->SetStatColor(0);
babarStyle->SetFillColor(0);

// set the paper & margin sizes
babarStyle->SetPaperSize(20,26);
babarStyle->SetPadTopMargin(0.05);
babarStyle->SetPadRightMargin(0.05);
babarStyle->SetPadBottomMargin(0.16);
babarStyle->SetPadLeftMargin(0.12);

// use large Times-Roman fonts
babarStyle->SetTextFont(132);
babarStyle->SetTextSize(0.08);
babarStyle->SetLabelFont(132,"x");
babarStyle->SetLabelFont(132,"y");
babarStyle->SetLabelFont(132,"z");
babarStyle->SetLabelSize(0.05,"x");
babarStyle->SetTitleSize(0.06,"x");
babarStyle->SetLabelSize(0.05,"y");
babarStyle->SetTitleSize(0.06,"y");
babarStyle->SetLabelSize(0.05,"z");
babarStyle->SetTitleSize(0.06,"z");

// use bold lines and markers
babarStyle->SetMarkerStyle(21);
babarStyle->SetHistLineWidth(1.85);
babarStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

// get rid of X error bars and y error bar caps
babarStyle->SetErrorX(0.001);

// do not display any of the standard histogram decorations
babarStyle->SetOptTitle(0);
babarStyle->SetOptStat(0);
babarStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
babarStyle->SetPadTickX(1);
babarStyle->SetPadTickY(1);

// BES style changed from BABAR style
TStyle *besStyle= new TStyle("BES","BES approved plots style");

// use plain black on white colors
besStyle->SetCanvasBorderMode(0);
besStyle->SetCanvasColor(0);
besStyle->SetFrameBorderMode(0);
besStyle->SetFrameBorderSize(3);
besStyle->SetFrameLineStyle(1);
besStyle->SetFrameLineWidth(2);
besStyle->SetFrameLineColor(0);
besStyle->SetPadBorderMode(0);
besStyle->SetPadColor(0);

besStyle->SetStatColor(0);
besStyle->SetFillColor(0);

// set the paper & margin sizes
besStyle->SetPaperSize(20,26);
besStyle->SetPadTopMargin(0.05);
besStyle->SetPadRightMargin(0.05);
besStyle->SetPadBottomMargin(0.16);
besStyle->SetPadLeftMargin(0.13);

// use large Times-Roman fonts
besStyle->SetTextFont(132);
besStyle->SetTextSize(0.08);
besStyle->SetLabelFont(132,"x");
besStyle->SetLabelFont(132,"y");
besStyle->SetLabelFont(132,"z");
besStyle->SetLabelSize(0.06,"x");
besStyle->SetTitleSize(0.06,"x");
besStyle->SetLabelSize(0.06,"y");
besStyle->SetTitleSize(0.06,"y");
besStyle->SetLabelSize(0.06,"z");
besStyle->SetTitleSize(0.06,"z");

// use bold lines and markers
besStyle->SetMarkerStyle(21);
besStyle->SetMarkerSize(1.0);
besStyle->SetLineWidth(2);
//besStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

// get rid of X error bars and y error bar caps
besStyle->SetErrorX(0.001);

// do not display any of the standard histogram decorations
besStyle->SetOptTitle(0);
besStyle->SetOptStat(0);
besStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
besStyle->SetPadTickX(1);
besStyle->SetPadTickY(1);

// set histogram line width
//besStyle->SetHistFillColor(0);
//besStyle->SetHistLineStyle(1);
//besStyle->SetHistLineColor(1);
//besStyle->SetHistLineWidth(2);
//  Line attributes are:
//    Line Color (see TAttFill for the list of colors)
//    Line Width expressed in pixel units
//    Line Style 1=solid, 2=dash, 3=dot-dot, 4=dash-dot. Additional line
//               styles can be defined using TStyle::SetLineStyleString.
//               Example:
//besStyle->SetLineStyleString(5,"20 12 4 12");
//besStyle->SetLineStyleString(6,"20 12 4 12 4 12 4 12");
//besStyle->SetLineStyleString(7,"20 20");
//besStyle->SetLineStyleString(8,"20 12 4 12 4 12");
//besStyle->SetLineStyleString(9,"80 20");

//gROOT->ProcessLine(".L /ihepbatch/bes/dusx/root/diffHist.cxx");
//gROOT->ProcessLine(".L /ihepbatch/bes/dusx/root/DrawAllBranches.cxx");
//gROOT->ProcessLine(".L /ihepbatch/bes/dusx/root/AxisSet.cxx");
//gROOT->ProcessLine(".L /ihepbatch/bes/dusx/root/makeClass.cxx");
//gSystem->Load("libRooFit") ;
//using namespace RooFit ;
//gROOT->ProcessLine(".L /ihepbatch/bes/dusx/root/RooBwDGauss.cxx++");
//gROOT->ProcessLine(".L /ihepbatch/bes/dusx/root/RooBwCbPdf.cxx++");
//new TBrowser();

struct measValue
{
  double mean;
  double error;
};

gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/q/qinlq/.root_style.C");

//void 
printf("Welcome to world!\n");

}
void FormatHist(TH * hist){
  hist->SetMarkerStyle(9);
  hist->SetMarkerSize(0.2);
  hist->SetTitleOffset(0.70,"Y");
  hist->SetTitleOffset(0.70,"X");
//  hist->SetFillColor(3);
  hist->SetLineColor(2);
}
void FormatAxis(TAxis * axis){
  axis->SetLabelFont(132);
  axis->SetLabelSize(0.052);
  axis->SetLabelOffset(0.005);
  axis->SetNdivisions(505);
  axis->SetTitleFont(132);
  axis->SetTitleColor(1);
  axis->SetTitleSize(0.070);
  axis->SetTickLength(0.050);
//  axis->SetTitleOffset(1.15);
 // axis->CenterTitle();
}

void NameAxes(TH1 * datahist, char * xname, char * yname){
  if(xname)
    datahist->GetXaxis()->SetTitle(xname);
  if(yname)
    datahist->GetYaxis()->SetTitle(yname);
}


// Format for second MC or background
// (Blue shaded area)
void FormatMC2(TH1 * mc2hist){
  mc2hist->SetLineColor(4);
  mc2hist->SetFillColor(4);
  mc2hist->SetLineWidth(2);
  mc2hist->SetFillStyle(3001);
}

// Graph Format for second MC or background
// (Blue line)
void FormatMC2(TGraph * mc2hist){
  mc2hist->SetLineColor(4);
  mc2hist->SetLineWidth(2);
}

// Graph Format for third MC or background
// (Blue line)
void FormatMC3(TGraph * mc3hist){
  mc3hist->SetLineColor(6);
  mc3hist->SetLineWidth(2);
}


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
  leg->SetTextFont(42);
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

void setStyle()
{
gStyle->SetFrameBorderMode(0);
gStyle->SetCanvasBorderMode(0);
gStyle->SetPadBorderMode(0);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);
//gStyle->SetTitleColor(0);
gStyle->SetStatColor(0);
gStyle->SetTitleFillColor(0);
gStyle->SetHistFillColor(0);
// set the paper & margin sizes
gStyle->SetPaperSize(20,26);
gStyle->SetPadTopMargin(0.05);
gStyle->SetPadRightMargin(0.05);
gStyle->SetPadBottomMargin(0.185);
gStyle->SetPadLeftMargin(0.12);

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
 gStyle->SetMarkerStyle(8);
 gStyle->SetHistLineWidth(1.85);
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

}

void setSave(TCanvas * c1, TString *filename){
  c1->cd();     //  fname.Replace(fname.Sizeof()-6,5,"_root_figs",10);
  c1->Print(filename+".eps");
//  c1->Print(filename+".png");
//  c1->Clear();
}
