

void cdmystyle(){
	TStyle *myStyle= new TStyle("myStyle","Customed personal Tstyle");
	myStyle->SetCanvasBorderMode(0);
	myStyle->SetCanvasColor(0);
	myStyle->SetFrameBorderMode(0);
	myStyle->SetFrameBorderSize(3);
	myStyle->SetFrameLineStyle(1);
	myStyle->SetFrameLineWidth(2);
	myStyle->SetFrameLineColor(0);

	myStyle->SetPadBorderMode(0);
	myStyle->SetPadColor(0);
	myStyle->SetPadTickX(1);
	myStyle->SetPadTickY(1);

	myStyle->SetCanvasDefH(600);
	myStyle->SetCanvasDefW(800);
	myStyle->SetCanvasDefX(0);
	myStyle->SetCanvasDefY(0);
	//	myStyle->SetFillColor(0);

	myStyle->SetPalette(1);

	myStyle->SetStatColor(0);
	//	myStyle->SetStatFont(42);
	//	myStyle->SetStatFont(22);
	myStyle->SetStatBorderSize(1);
	myStyle->SetOptStat(0);
	myStyle->SetStatFontSize(.03);
	myStyle->SetStatX(0.90);
	myStyle->SetStatY(0.90);

	myStyle->SetNdivisions(510,"x");
	myStyle->SetNdivisions(510,"y");
	myStyle->SetTickLength(.03,"xyz");

	// set the paper & margin sizes
	myStyle->SetPaperSize(20,26);
	myStyle->SetPadTopMargin(0.04);
	myStyle->SetPadRightMargin(0.04);
	myStyle->SetPadBottomMargin(0.11);
	myStyle->SetPadLeftMargin(0.13);

	// use large Times-Roman fonts
	myStyle->SetTextFont(132);
	myStyle->SetTextSize(0.08);

	// use bold lines and markers
	myStyle->SetMarkerStyle(20);
	myStyle->SetMarkerSize(1.0);
	myStyle->SetLineWidth(2);
	//		myStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
	myStyle->SetLabelSize(0.04,"xyz");
	myStyle->SetTitleSize(0.06,"xyz");
	myStyle->SetLabelOffset(0.005);
	myStyle->SetTitleOffset(0.7,"x");
	myStyle->SetTitleOffset(0.9,"y");
	myStyle->SetTitleFont(22);
	myStyle->SetLabelFont(22);

	// get rid of X error bars and y error bar caps
	myStyle->SetErrorX(0.5);
	myStyle->SetOptFit(0);

	// do not display any of the standard histogram decorations
	myStyle->SetHistLineColor(1);
	myStyle->SetHistFillStyle(1001);
	myStyle->SetHistLineWidth(2);
	myStyle->SetMarkerStyle(20);


	myStyle->SetLegendBorderSize(0);
	myStyle->SetLegendFillColor(0);
	myStyle->SetLegendFont(42);
	myStyle->SetOptTitle(0);

	myStyle->cd();

}
// put tick marks on top and RHS of plots

//..BABAR style from RooLogon.C in workdir
void cdbabarstyle(){
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
	babarStyle->SetHistLineWidth(2);
//	babarStyle->SetHistLineWidth(1.85);
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
	babarStyle->cd();
}

// BES style changed from BABAR style
void cdbesstyle(){
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

	besStyle->cd();
}

void cdStyle(TString style_c){
	if(style_c=="myStyle") cdmystyle();
	else if(style_c=="babarStyle") cdbabarstyle();
	else if(style_c=="besStyle") cdbesstyle();
	else cout<<"No Matched Style!"<<endl;
}
