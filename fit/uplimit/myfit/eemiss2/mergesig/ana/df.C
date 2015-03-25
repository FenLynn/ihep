#define df_cxx
#include "df.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "/workfs/bes/lify/myinclude/rootall.h"


void df::Loop()
{
//	 freopen("out.txt","w",stdout);
//   In a ROOT session, you can do:
//      Root > .L df.C
//      Root > df t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	SetMyStyle();
	if (fChain == 0) return;

	TH1F* h_umiss=new TH1F("h_umiss","umiss",100,-0.2,3);
	h_umiss->GetXaxis()->SetTitle("U_{miss}[GeV]");
	h_umiss->GetYaxis()->SetTitle("Events");
	h_umiss->SetTitle("U_{miss}");
	h_umiss->GetXaxis()->CenterTitle();                         
	h_umiss->GetYaxis()->CenterTitle();                         

	TH1F* h_mmiss2=new TH1F("h_mmiss2","mmiss2",100,-0.2,9);
	h_mmiss2->GetXaxis()->SetTitle("M_{miss}^{2} [GeV^{2}]");
	h_mmiss2->GetYaxis()->SetTitle("Events");
	h_mmiss2->SetTitle("M_{miss}^{2}");
	h_mmiss2->GetXaxis()->CenterTitle();                         
	h_mmiss2->GetYaxis()->CenterTitle();                         

	TH1F* h_mmiss=new TH1F("h_mmiss","mmiss",100,-0.1,3);
	h_mmiss->GetXaxis()->SetTitle("M_{miss}[GeV]");
	h_mmiss->GetYaxis()->SetTitle("Events");
	h_mmiss->SetTitle("M_{miss}");
	h_mmiss->GetXaxis()->CenterTitle();                         
	h_mmiss->GetYaxis()->CenterTitle();                         

	TH1F* h_pmiss=new TH1F("h_pmiss","pmiss",100,-0.1,1.5);
	h_pmiss->GetXaxis()->SetTitle("p_{miss} [GeV/c]");
	h_pmiss->GetYaxis()->SetTitle("Events");
	h_pmiss->SetTitle("missing momentum p_{miss}");
	h_pmiss->GetXaxis()->CenterTitle();                         
	h_pmiss->GetYaxis()->CenterTitle();                         

	TH1F* h_emiss=new TH1F("h_emiss","emiss",100,-0.1,1.5);
	h_emiss->GetXaxis()->SetTitle("E_{miss}[GeV]");
	h_emiss->GetYaxis()->SetTitle("Events");
	h_emiss->SetTitle("E_{miss}");
	h_emiss->GetXaxis()->CenterTitle();                         
	h_emiss->GetYaxis()->CenterTitle();                         

	TH1F* h_ee_ivm=new TH1F("h_ee_ivm","ee_ivm",100,-0.1,3.08);
	h_ee_ivm->GetXaxis()->SetTitle("Invariant Mass_{e^{+}e^{-}}[GeV]");
	h_ee_ivm->GetYaxis()->SetTitle("Events");
	h_ee_ivm->SetTitle("Invariant Mass of e^{+}e^{-}");
	h_ee_ivm->GetXaxis()->CenterTitle();                         
	h_ee_ivm->GetYaxis()->CenterTitle();                         

	TH1F* h_vtxchisq=new TH1F("h_vtxchisq","vtxchisq",300,0,10);
	h_vtxchisq->GetXaxis()->SetTitle("#chi_{Vertex}");
	h_vtxchisq->GetYaxis()->SetTitle("Events");
	h_vtxchisq->SetTitle("vertex #chi");
	h_vtxchisq->GetXaxis()->CenterTitle();                         
	h_vtxchisq->GetYaxis()->CenterTitle();                         

	TH1F* h_epTrkp=new TH1F("h_epTrkp","epTrk",100,-1.1,2.2);
	h_epTrkp->GetXaxis()->SetTitle("E/P(e^{+})");
	h_epTrkp->GetYaxis()->SetTitle("Events");
	h_epTrkp->SetTitle("e^{+} E/P");
	h_epTrkp->GetXaxis()->CenterTitle();                         
	h_epTrkp->GetYaxis()->CenterTitle();                         

	TH1F* h_epTrkm=new TH1F("h_epTrkm","epTrk",100,-1.1,2.2);
	h_epTrkm->GetXaxis()->SetTitle("E/P(e^{-})");
	h_epTrkm->GetYaxis()->SetTitle("Events");
	h_epTrkm->SetTitle("e^{-} E/P ");
	h_epTrkm->GetXaxis()->CenterTitle();                         
	h_epTrkm->GetYaxis()->CenterTitle();                         

	TH1F* h_costhep=new TH1F("h_costhep","costhep",100,-1,1);
	h_costhep->GetXaxis()->SetTitle("cos#theta (e^{+})");
	h_costhep->GetYaxis()->SetTitle("Events");
	h_costhep->SetTitle("cos(#theta) e^{+}");
	h_costhep->GetXaxis()->CenterTitle();                         
	h_costhep->GetYaxis()->CenterTitle();                         

	TH1F* h_costhem=new TH1F("h_costhem","costhem",100,-1,1);
	h_costhem->GetXaxis()->SetTitle("cos#theta (e^{-})");
	h_costhem->GetYaxis()->SetTitle("Events");
	h_costhem->SetTitle("cos(#theta) e^{-}");
	h_costhem->GetXaxis()->CenterTitle();                         
	h_costhem->GetYaxis()->CenterTitle();                         

	TH1F* h_p_p=new TH1F("h_p_p","p_p",100,0,1.8);
	h_p_p->GetXaxis()->SetTitle("p(e^{+}) [GeV]");
	h_p_p->GetYaxis()->SetTitle("Events");
	h_p_p->SetTitle("momentum of e^{+}");
	h_p_p->GetXaxis()->CenterTitle();                         
	h_p_p->GetYaxis()->CenterTitle();                         

	TH1F* h_p_m=new TH1F("h_p_m","p_m",100,0,1.8);
	h_p_m->GetXaxis()->SetTitle("p(e^{-}) [GeV]");
	h_p_m->GetYaxis()->SetTitle("Events");
	h_p_m->SetTitle("momentum of e^{-}");
	h_p_m->GetXaxis()->CenterTitle();                         
	h_p_m->GetYaxis()->CenterTitle();                         

	TH1F* h_costhe_ee=new TH1F("h_costhe_ee","costhe_ee",100,-1.1,1.1);
	h_costhe_ee->GetXaxis()->SetTitle("cos#theta");
	h_costhe_ee->GetYaxis()->SetTitle("Events");
	h_costhe_ee->SetTitle("cos#theta of <e^{+},e^{-}> ");
	h_costhe_ee->GetXaxis()->CenterTitle();                         
	h_costhe_ee->GetYaxis()->CenterTitle();                         

	TH1F* h_costhe_u=new TH1F("h_costhe_u","costhe_u",100,-0.81,0.81);
	h_costhe_u->GetXaxis()->SetTitle("cos#theta");
	h_costhe_u->GetYaxis()->SetTitle("Events");
	h_costhe_u->SetTitle("cos#theta of missing  ");
	h_costhe_u->GetXaxis()->CenterTitle();                         
	h_costhe_u->GetYaxis()->CenterTitle();                         

	TH1F* h_ptr2=new TH1F("h_ptr2","ptr2",100,-0.01,0.2);
	h_ptr2->GetXaxis()->SetTitle("p_{tr}^{2} [GeV^{2}]");
	h_ptr2->GetYaxis()->SetTitle("Events");
	h_ptr2->SetTitle("P_{tr}^{2} of e^{+}e^{-}");
	h_ptr2->GetXaxis()->CenterTitle();                         
	h_ptr2->GetYaxis()->CenterTitle();                         

	TH1F* h_chi1C=new TH1F("h_chi1C","chi1C",100,-0.01,200);
	h_chi1C->GetXaxis()->SetTitle("#chi_{1C}^{2}");
	h_chi1C->GetYaxis()->SetTitle("Events");
	h_chi1C->SetTitle("#chi_{1C} of 1C Fit");
	h_chi1C->GetXaxis()->CenterTitle();                         
	h_chi1C->GetYaxis()->CenterTitle();                         
	
	int Npassvtx=0;
	int Npasspid=0;


	///////////////////////////////////////////////////////////////////////////	
	Long64_t nentries = fChain->GetEntries();
	cout<<"Total nentries before selection:		"<<nentries<<endl;
	TFile* fout=new TFile("../OUTPUT","RECREATE"); 
	TTree* newTree=(TTree*)fChain->CloneTree(0); 
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
	//	if (Cut(ientry) < 0) continue;
	//-----------------------------------------------set cut here---------------------------------------------------------------------------------------------------		
	
//		if( chi1C < 5 ) continue;
//		if( epTrk[0] <0.8 || epTrk[1]<0.8 ) continue;
	
		if( vtxchisq > 5 ) continue;
		if(isnan(vtxchisq)) continue;
		
		Npassvtx++;

		if( prob[0][0]<prob[0][2] || prob[0][0]<prob[0][3] || prob[0][0]<prob[0][4] ){
		continue;}
		if( prob[1][0]<prob[1][2] || prob[1][0]<prob[1][3] || prob[1][0]<prob[1][4] ){
		continue;}

		Npasspid++;
	 
		if ( costhe_ee<-0.9 || costhe_ee > 0.99) continue;
		if( ptr2 < 0.05 ) continue;

/*
		if( chiDeDx[0][0]*chiDeDx[0][0]>chiDeDx[0][2]*chiDeDx[0][2] || chiDeDx[0][0]*chiDeDx[0][0]>chiDeDx[0][3]*chiDeDx[0][3] || chiDeDx[0][0]*chiDeDx[0][0]>chiDeDx[0][4]*chiDeDx[0][4] ){
		continue;}
		if( chiDeDx[1][0]*chiDeDx[1][0]>chiDeDx[1][2]*chiDeDx[1][2] || chiDeDx[1][0]*chiDeDx[1][0]>chiDeDx[1][3]*chiDeDx[1][3] || chiDeDx[1][0]*chiDeDx[1][0]>chiDeDx[1][4]*chiDeDx[1][4] ){
		continue;}
*/	
		/*
		if( costhe_ee < -0.77 ) continue;
		if( umiss < 0.08 ) continue;
		if( ptr2 < 0.1 ) continue;
		*/
		//if(mmiss2<0.1) continue;
	//-----------------------------------------------set cut here---------------------------------------------------------------------------------------------------		
		
		h_mmiss2->Fill(mmiss2);
		h_umiss->Fill(umiss);
		h_mmiss->Fill(mmiss);
		h_pmiss->Fill(pmiss);
		h_emiss->Fill(emiss);
		h_vtxchisq->Fill(vtxchisq);
		h_epTrkp->Fill(epTrk[0]);
		h_epTrkm->Fill(epTrk[1]);
		h_costhep->Fill(costheta_chrgd[0]);
		h_costhem->Fill(costheta_chrgd[1]);
		h_p_p->Fill(pTrk[0]);
		h_p_m->Fill(pTrk[1]);
		h_ee_ivm->Fill(ee_ivm);
		h_ptr2->Fill(ptr2);
		h_costhe_ee->Fill(costhe_ee);
		h_costhe_u->Fill(costhe_u);
		h_chi1C->Fill(chi1C);
		newTree->Fill();
	}
	cout<<"pass vtx:	"<<Npassvtx<<endl;
	cout<<"pass pid:	"<<Npasspid<<endl;
	cout<<"Total nentries after selection:		"<<newTree->GetEntries()<<endl;
	fout->cd();

	TCanvas* c_umiss = new TCanvas("c_umiss","_umiss",900,600);
	TPad *p1_umiss=new TPad("p1_umiss","p1_umiss",0.01,0.01,.49,.99,0);
	TPad *p2_umiss=new TPad("p2_umiss","p2_umiss",0.51,0.01,.99,.99,0);
	p1_umiss->Draw();
	p2_umiss->Draw();
	p1_umiss->cd();
	h_umiss->Draw();
	p2_umiss->cd();
	p2_umiss->SetLogy();
	h_umiss->Draw();
	c_umiss->Write();

	TCanvas* c_mmiss2 = new TCanvas("c_mmiss2","_mmiss2",900,600);
	TPad *p1_mmiss2=new TPad("p1_mmiss2","p1_mmiss2",0.01,0.01,.49,.99,0);
	TPad *p2_mmiss2=new TPad("p2_mmiss2","p2_mmiss2",0.51,0.01,.99,.99,0);
	p1_mmiss2->Draw();
	p2_mmiss2->Draw();
	p1_mmiss2->cd();
	h_mmiss2->Draw();
	p2_mmiss2->cd();
	p2_mmiss2->SetLogy();
	h_mmiss2->Draw();
	c_mmiss2->Write();

	TCanvas* c_mmiss = new TCanvas("c_mmiss","_mmiss",900,600);
	TPad *p1_mmiss=new TPad("p1_mmiss","p1_mmiss",0.01,0.01,.49,.99,0);
	TPad *p2_mmiss=new TPad("p2_mmiss","p2_mmiss",0.51,0.01,.99,.99,0);
	p1_mmiss->Draw();
	p2_mmiss->Draw();
	p1_mmiss->cd();
	h_mmiss->Draw();
	p2_mmiss->cd();
	p2_mmiss->SetLogy();
	h_mmiss->Draw();
	c_mmiss->Write();

	TCanvas* c_pmiss = new TCanvas("c_pmiss","_pmiss",900,600);
	TPad *p1_pmiss=new TPad("p1_pmiss","p1_pmiss",0.01,0.01,.49,.99,0);
	TPad *p2_pmiss=new TPad("p2_pmiss","p2_pmiss",0.51,0.01,.99,.99,0);
	p1_pmiss->Draw();
	p2_pmiss->Draw();
	p1_pmiss->cd();
	h_pmiss->Draw();
	p2_pmiss->cd();
	p2_pmiss->SetLogy();
	h_pmiss->Draw();
	c_pmiss->Write();

	TCanvas* c_emiss = new TCanvas("c_emiss","_emiss",900,600);
	TPad *p1_emiss=new TPad("p1_emiss","p1_emiss",0.01,0.01,.49,.99,0);
	TPad *p2_emiss=new TPad("p2_emiss","p2_emiss",0.51,0.01,.99,.99,0);
	p1_emiss->Draw();
	p2_emiss->Draw();
	p1_emiss->cd();
	h_emiss->Draw();
	p2_emiss->cd();
	p2_emiss->SetLogy();
	h_emiss->Draw();
	c_emiss->Write();

	TCanvas* c_ee_ivm = new TCanvas("c_ee_ivm","_ee_ivm",900,600);
	TPad *p1_ee_ivm=new TPad("p1_ee_ivm","p1_ee_ivm",0.01,0.01,.49,.99,0);
	TPad *p2_ee_ivm=new TPad("p2_ee_ivm","p2_ee_ivm",0.51,0.01,.99,.99,0);
	p1_ee_ivm->Draw();
	p2_ee_ivm->Draw();
	p1_ee_ivm->cd();
	h_ee_ivm->Draw();
	p2_ee_ivm->cd();
	p2_ee_ivm->SetLogy();
	h_ee_ivm->Draw();
	c_ee_ivm->Write();

	TCanvas* c_vtxchisq = new TCanvas("c_vtxchisq","_vtxchisq",900,600);
	TPad *p1_vtxchisq=new TPad("p1_vtxchisq","p1_vtxchisq",0.01,0.01,.49,.99,0);
	TPad *p2_vtxchisq=new TPad("p2_vtxchisq","p2_vtxchisq",0.51,0.01,.99,.99,0);
	p1_vtxchisq->Draw();
	p2_vtxchisq->Draw();
	p1_vtxchisq->cd();
	h_vtxchisq->Draw();
	p2_vtxchisq->cd();
	p2_vtxchisq->SetLogy();
	h_vtxchisq->Draw();
	c_vtxchisq->Write();

	TCanvas* c_epTrkp = new TCanvas("c_epTrkp","_epTrkp",900,600);
	TPad *p1_epTrkp=new TPad("p1_epTrkp","p1_epTrkp",0.01,0.01,.49,.99,0);
	TPad *p2_epTrkp=new TPad("p2_epTrkp","p2_epTrkp",0.51,0.01,.99,.99,0);
	p1_epTrkp->Draw();
	p2_epTrkp->Draw();
	p1_epTrkp->cd();
	h_epTrkp->Draw();
	p2_epTrkp->cd();
	p2_epTrkp->SetLogy();
	h_epTrkp->Draw();
	c_epTrkp->Write();

	TCanvas* c_epTrkm = new TCanvas("c_epTrkm","_epTrkm",900,600);
	TPad *p1_epTrkm=new TPad("p1_epTrkm","p1_epTrkm",0.01,0.01,.49,.99,0);
	TPad *p2_epTrkm=new TPad("p2_epTrkm","p2_epTrkm",0.51,0.01,.99,.99,0);
	p1_epTrkm->Draw();
	p2_epTrkm->Draw();
	p1_epTrkm->cd();
	h_epTrkm->Draw();
	p2_epTrkm->cd();
	p2_epTrkm->SetLogy();
	h_epTrkm->Draw();
	c_epTrkm->Write();

	TCanvas* c_costhep = new TCanvas("c_costhep","_costhep",900,600);
	TPad *p1_costhep=new TPad("p1_costhep","p1_costhep",0.01,0.01,.49,.99,0);
	TPad *p2_costhep=new TPad("p2_costhep","p2_costhep",0.51,0.01,.99,.99,0);
	p1_costhep->Draw();
	p2_costhep->Draw();
	p1_costhep->cd();
	h_costhep->Draw();
	p2_costhep->cd();
	p2_costhep->SetLogy();
	h_costhep->Draw();
	c_costhep->Write();

	TCanvas* c_costhem = new TCanvas("c_costhem","_costhem",900,600);
	TPad *p1_costhem=new TPad("p1_costhem","p1_costhem",0.01,0.01,.49,.99,0);
	TPad *p2_costhem=new TPad("p2_costhem","p2_costhem",0.51,0.01,.99,.99,0);
	p1_costhem->Draw();
	p2_costhem->Draw();
	p1_costhem->cd();
	h_costhem->Draw();
	p2_costhem->cd();
	p2_costhem->SetLogy();
	h_costhem->Draw();
	c_costhem->Write();

	TCanvas* c_p_p = new TCanvas("c_p_p","_p_p",900,600);
	TPad *p1_p_p=new TPad("p1_p_p","p1_p_p",0.01,0.01,.49,.99,0);
	TPad *p2_p_p=new TPad("p2_p_p","p2_p_p",0.51,0.01,.99,.99,0);
	p1_p_p->Draw();
	p2_p_p->Draw();
	p1_p_p->cd();
	h_p_p->Draw();
	p2_p_p->cd();
	p2_p_p->SetLogy();
	h_p_p->Draw();
	c_p_p->Write();

	TCanvas* c_p_m = new TCanvas("c_p_m","_p_m",900,600);
	TPad *p1_p_m=new TPad("p1_p_m","p1_p_m",0.01,0.01,.49,.99,0);
	TPad *p2_p_m=new TPad("p2_p_m","p2_p_m",0.51,0.01,.99,.99,0);
	p1_p_m->Draw();
	p2_p_m->Draw();
	p1_p_m->cd();
	h_p_m->Draw();
	p2_p_m->cd();
	p2_p_m->SetLogy();
	h_p_m->Draw();
	c_p_m->Write();

	TCanvas* c_costhe_ee = new TCanvas("c_costhe_ee","_costhe_ee",900,600);
	TPad *p1_costhe_ee=new TPad("p1_costhe_ee","p1_costhe_ee",0.01,0.01,.49,.99,0);
	TPad *p2_costhe_ee=new TPad("p2_costhe_ee","p2_costhe_ee",0.51,0.01,.99,.99,0);
	p1_costhe_ee->Draw();
	p2_costhe_ee->Draw();
	p1_costhe_ee->cd();
	h_costhe_ee->Draw();
	p2_costhe_ee->cd();
	p2_costhe_ee->SetLogy();
	h_costhe_ee->Draw();
	c_costhe_ee->Write();

	TCanvas* c_costhe_u = new TCanvas("c_costhe_u","_costhe_u",900,600);
	TPad *p1_costhe_u=new TPad("p1_costhe_u","p1_costhe_u",0.01,0.01,.49,.99,0);
	TPad *p2_costhe_u=new TPad("p2_costhe_u","p2_costhe_u",0.51,0.01,.99,.99,0);
	p1_costhe_u->Draw();
	p2_costhe_u->Draw();
	p1_costhe_u->cd();
	h_costhe_u->Draw();
	p2_costhe_u->cd();
	p2_costhe_u->SetLogy();
	h_costhe_u->Draw();
	c_costhe_u->Write();

	TCanvas* c_ptr2 = new TCanvas("c_ptr2","_ptr2",900,600);
	TPad *p1_ptr2=new TPad("p1_ptr2","p1_ptr2",0.01,0.01,.49,.99,0);
	TPad *p2_ptr2=new TPad("p2_ptr2","p2_ptr2",0.51,0.01,.99,.99,0);
	p1_ptr2->Draw();
	p2_ptr2->Draw();
	p1_ptr2->cd();
	h_ptr2->Draw();
	p2_ptr2->cd();
	p2_ptr2->SetLogy();
	h_ptr2->Draw();
	c_ptr2->Write();

	TCanvas* c_chi1C = new TCanvas("c_chi1C","_chi1C",900,600);
	TPad *p1_chi1C=new TPad("p1_chi1C","p1_chi1C",0.01,0.01,.49,.99,0);
	TPad *p2_chi1C=new TPad("p2_chi1C","p2_chi1C",0.51,0.01,.99,.99,0);
	p1_chi1C->Draw();
	p2_chi1C->Draw();
	p1_chi1C->cd();
	h_chi1C->Draw();
	p2_chi1C->cd();
	p2_chi1C->SetLogy();
	h_chi1C->Draw();
	c_chi1C->Write();
	
	///////////////////////////////////////////////////////////////////////////	
	

	newTree->AutoSave();
	fout->Close();
	delete fout;
}
