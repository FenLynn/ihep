	TChain *fMYNAME = new TChain("save","");
	fMYNAME->Add("./FILENAME");
	fMYNAME->SetBranchStatus("*",kFALSE);
	fMYNAME->SetBranchStatus("ee_ivm",kTRUE);
	TTree *o_MYNAME = (TTree*)fMYNAME->CloneTree();
	o_MYNAME->SetName("MYNAME");
	out->cd();
	o_MYNAME->AutoSave();

