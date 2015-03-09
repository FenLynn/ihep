{
	//+++++Do not set relative path like "./../a.root",it must from root directory 
	//+++++like "/home/user/root/test*.root" 
	//char *rootfile_path="/home/lify/workarea/2muon/dmu11/rhopi/sigmc/Rhopi0*";
	//char *rootfile_path="/home/lify/workarea/2muon/dmu11/rhopi/inmc/Rhopi0*";
	char *rootfile_path="/home/lify/workarea/2muon/dmu11/rhopi/data/Rhopi0*";
	
	//+++++Select which type your root file come from,and of course you can customize,
	//+++++to avoid other errors,it's better just change like below
	
//	char *roottype="Sigmc";
	//char *roottype="Inmc";
	char *roottype="Data";

	//+++++Select the tree
	TChain *chain=new TChain("save","");

	chain->Add(rootfile_path);

	chain->MakeClass(roottype);
	
}
