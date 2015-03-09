	
	//***********************************This ia a single Canvas***********************************************
	TH1F* histname=new TH1F("histname",histpar);
	histname->GetXaxis()->SetTitle("M(e^{-}) [GeV/c^{2}]");
	histname->GetYaxis()->SetTitle("Events");
	histname->SetLineColor(kRed);
	histname->SetStats(0);
	for(Long64_t i=0;i<rootfrom->fChain->GetEntriesFast();i++)
	{
		rootfrom->fChain->GetEntry(i);
		//if(i%10000==1) cout<<"entry:"<<i<<endl;
