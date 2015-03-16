{
	//+++++Do not set relative path like "./../a.root",it must from root directory 
	//+++++like "/home/user/root/test*.root" 
	//char *rootfile_path="/home/lify/workarea/2muon/dmu11/rhopi/sigmc/Rhopi0*";
	//char *rootfile_path="/home/lify/workarea/2muon/dmu11/rhopi/inmc/Rhopi0*";
	char *rootfile_path="/scratchfs/bes/lify/664p01/root/Eemiss/data12/Eemiss_*.root";
//	char *rootfile_path1="/scratchfs/bes/lify/664p01/root/Eemiss/data12/Eemiss_01*.root";
//	char *rootfile_path2="/scratchfs/bes/lify/664p01/root/Eemiss/data12/Eemiss_02*.root";
//	char *rootfile_path3="/scratchfs/bes/lify/664p01/root/Eemiss/data12/Eemiss_03*.root";
//	char *rootfile_path="/scratchfs/bes/lify/664p01/root/Eemiss/QED/baba/Eemiss*.root";
//	char *rootfile_path="/besfs/users/lify/Root/Eemiss_v4/sysun/efferr/u0.8_h0.6/normal/*.root";
	//+++++Select which type your root file come from,and of course you can customize,
	//+++++to avoid other errors,it's better just change like below
	
//	char *roottype="Sigmc";
	char *roottype="df";
//	char *nbi="nb"
//	char *roottype="Data";
	
	//+++++Select the tree
	TChain *chain=new TChain("save","");
//	TChain *c1=new TChain("nbinfo","");

	chain->Add(rootfile_path);
//	chain->Add(rootfile_path1);
//	chain->Add(rootfile_path2);
//	chain->Add(rootfile_path3);
	chain->MakeClass(roottype);
	
//	c1->Add(rootfile_path);
//	c1->MakeClass(nbi);
}
