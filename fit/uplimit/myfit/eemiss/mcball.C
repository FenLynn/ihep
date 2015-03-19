#include "/workfs/bes/lify/myinclude/rootult.h"
using namespace RooFit;
using namespace std;

//====================================================================
//For crystal signal fit to get shape
const char* tree_file = "tree.txt";
const char* filename="sigtree.root";
const int NofSignal=50000;

const int input_tree_name = 1;
const double left_range = 0.07;
const double right_range = 0.03;

ofstream outfile("cbinfo.txt");
const char* outsig_file = "outsig.root";
const char* outsig_tree = "siginfo";
TFile *fout=new TFile(outsig_file,"RECREATE");
TTree *tout=new TTree(outsig_tree,outsig_tree);


double* cball(TString treename,double low,double high,double reset[])
{
	RooRealVar ee("ee_ivm","ee_ivm",low,high) ;
	RooRealVar cbmean("cbmean","cbmean",low+left_range,low,high) ;
	RooRealVar cbsigma("cbsigma","cbsigma",0.005,0.001,0.01) ;
	RooRealVar n1("n1","n1",1.0,0.,10.);
	RooRealVar alpha("alpha","alpha",1.0,0.,10.);
	RooCBShape cball("cball","crystal ball",ee,cbmean,cbsigma,alpha,n1);

	TString br_tree=treename;
	TFile *file1 = new TFile(filename,"READ");
	TTree *tree1 =(TTree *)file1->Get(br_tree);
	if (!file1) cout<<"Invalid file:	"<<filename<<endl;
	if (!tree1) cout<<"Invalid tree:	"<<br_tree<<endl;

	TString ncut="";
	ncut+="ee_ivm<";
	ncut+=high;
	ncut+="&&ee_ivm>";
	ncut+=low;

	int nentries=0;
	nentries=tree1->GetEntries(ncut);

	RooRealVar nsig("nsig","nsig",nentries,0,50000);
	RooExtendPdf model("model","esig",cball,nsig);
	RooDataSet signal("signal","signal",RooArgSet(ee),Import(*tree1));
	signal.Print();

	model.fitTo(signal);

	reset[0]=cbmean.getVal();
	reset[2]=cbsigma.getVal();
	reset[4]=alpha.getVal();
	reset[6]=n1.getVal();
	reset[8]=nsig.getVal();
	reset[1]=cbmean.getError();
	reset[3]=cbsigma.getError();
	reset[5]=alpha.getError();
	reset[7]=n1.getError();
	reset[9]=nsig.getError();
	reset[10]=double(nentries);
	reset[11]=-99;

	RooPlot* xframe = ee.frame();
	xframe->SetName(treename);
	signal.plotOn(xframe);
	model.plotOn(xframe);
	model.paramOn(xframe);
	//	xframe->Draw();

	fout->cd();
	xframe->Write();

	return reset;
}


void mcball()
{
	int Nsigsam = 4;
	double *reset;
	double reset_1[12]={-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99};

	cout<<"1. Multiple Crystal Ball fit start..."<<endl;
	double massu[500];
	double massh[500];
	double tree_massu;
	double tree_massh;
	TString treetitle[500];
	//TString treename[500]={"u07_h06","u08_h06","u09_h06","u10_h06"};
	TString treename[500];

	double cbmean;
	double ecbmean;
	double cbsigma;
	double ecbsigma;
	double alpha;
	double ealpha;
	double n1;
	double en1;
	double nfit;
	double enfit;
	double nori;
	double eff;
	double low=0.;
	double high=3.2;

	tout->Branch("massu",&tree_massu,"massu/D");
	tout->Branch("massh",&tree_massh,"massh/D");

	tout->Branch("cbmean",&cbmean,"cbmean/D");
	tout->Branch("ecbmean",&ecbmean,"ecbmean/D");
	tout->Branch("cbsigma",&cbsigma,"cbsigma/D");
	tout->Branch("ecbsigma",&ecbsigma,"ecbsigma/D");
	tout->Branch("alpha",&alpha,"alpha/D");
	tout->Branch("ealpha",&ealpha,"ealpha/D");
	tout->Branch("n1",&n1,"n1/D");
	tout->Branch("en1",&en1,"en1/D");
	tout->Branch("nfit",&nfit,"nfit/D");
	tout->Branch("enfit",&enfit,"enfit/D");
	tout->Branch("nori",&nori,"nori/D");
	tout->Branch("eff",&eff,"eff/D");

	if(input_tree_name == 1 )
	{
		cout<<"2. Input tree info!"<<endl;
		double t_massu;
		double t_massh;
		TString t_treename;
		TString t_treetitle;
		ifstream inp;
		inp.open(tree_file);
		int t=0;
		while(inp>>t_massu>>t_massh>>t_treetitle>>t_treename)
		{
			if( t>1000 ) break;
			//cout<<t_massu<<endl;
			massu[t]=t_massu;
			massh[t]=t_massh;
			treetitle[t]=t_treetitle;
			treename[t]=t_treename;
			t++;
		}
		Nsigsam=t;
	}
	else if(input_tree_name == 0 )
	{
		cout<<"2. Modify tree info!"<<endl;
		/*
		   TString ts_massu="";
		   TString ts_massh="";
		   TString mod_str="";
		   for(int i=0;i<Nsigsam;i++)
		   {
		   char *temp_str = treename[i];
		   mod_str=temp_str[1];
		   mod_str+=".";
		   mod_str+=temp_str[2];
		   cout<<mod_str<<endl;
		   }
		   */
	}
	else
	{
		cout<<"input_tree_name set  wrong.Pleaase set 1 or 0"<<endl;
		return;
	}

	for(int i=0;i<Nsigsam;i++)
		//for(int i=0;i<1;i++)
	{
		low = massu[i]-left_range;
		high = massu[i] +right_range;

		reset=cball(treename[i],low,high,reset_1);

		tree_massu=massu[i];
		tree_massh=massh[i];
		cbmean=reset[0];
		ecbmean=reset[1];
		cbsigma=reset[2];
		ecbsigma=reset[3];
		alpha=reset[4];
		ealpha=reset[5];
		n1=reset[6];
		en1=reset[7];
		nfit=reset[8];
		enfit=reset[9];
		nori=reset[10];

		eff=nfit*1.0/NofSignal;
		tout->Fill();
		//outfile<<massu[i]<<" "<<massh[i]<<" "<<cbmean<<" "<<cbsigma<<" "<<n1<<" "<<alpha<<" "<<endl<<endl;
		outfile<<massu[i]<<" "<<cbsigma<<" "<<n1<<" "<<alpha<<" "<<eff<<endl;
	}
	tout->AutoSave();
	fout->Close();
}

