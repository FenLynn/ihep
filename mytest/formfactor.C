#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

std::vector<double> sum[100];

void formfactor(){


	mytime->Print();
	for(int i=0;i<100;i++)
	{
		sum[i].clear();
	}
	
	TFile *fout=new TFile("./out.root","RECREATE");
	TTree *tree=new TTree("F","F");
//	TH2F *formf=new TH2F("formf","formf",100,0,3.2,,0,10000);
	TH1F *formf=new TH1F("formf","formf",100,0,0.1);
	double T2,f2,qq;
	int Nsuccess=0;
	tree->Branch("T2",&T2,"T2/D");
	tree->Branch("f2",&f2,"f2/D");
	tree->Branch("qq",&qq,"qq/D");
	double Ecms=3.097;
	double me=0.000511;
	double metap=0.958;
	double mPsip = 3.68609;
	TLorentzVector jpsi,e1,e2,vp,P;
	jpsi.SetPxPyPzE(0.,0.,0.,Ecms);
	for(int i=0;i<1000000;i++){
		double Ppx,Ppy,Ppz,PE;
		Ppx=gRandom->Uniform(-2.1,2.1);
		Ppy=gRandom->Uniform(-2.1,2.1);
		Ppz=gRandom->Uniform(-2.1,2.1);
		PE=sqrt(metap*metap+Ppx*Ppx+Ppy*Ppy+Ppz*Ppz);
		if(PE>Ecms) continue;
		P.SetPxPyPzE(Ppx,Ppy,Ppz,PE);
		vp=jpsi-P;
		double e2x,e2y,e2z,e2E;
		double e1x,e1y,e1z,e1E;
		//e1E=vp.E()/2;
		e1E=gRandom->Uniform(0,vp.E());
		e2E=vp.E()-e1E;
		e1x=gRandom->Uniform(0,e1E);
		e2x=vp.Px()-e1x;
		if(fabs(e1E)<fabs(e1x) || fabs(e2E)<fabs(e2x)) continue;
		double ra2=e1E*e1E-me*me-e1x*e1x;
		double rb2=e2E*e2E-me*me-e2x*e2x;
		if(ra2<0 || rb2<0 ) continue;
		double ra=sqrt(ra2);
		double rb=sqrt(rb2);
		double tanthe=vp.Pz()/vp.Py();
		double sinthe=tanthe/(sqrt(1+tanthe*tanthe));
		double costhe=sqrt(1-sinthe*sinthe);
		e1y=ra*costhe;
		e1z=ra*sinthe;
		e2y=rb*costhe;
		e2z=rb*sinthe;
		e1.SetPxPyPzE(e1x,e1y,e1z,e1E);
		e2.SetPxPyPzE(e2x,e2y,e2z,e2E);
//		cout<<"e1:	"<<e1.Px()<<" "<<e1.Py()<<" "<<e1.Pz()<<" "<<e1.E()<<" "<<e1.M()<<endl;
//		cout<<"e2:	"<<e2.Px()<<" "<<e2.Py()<<" "<<e2.Pz()<<" "<<e2.E()<<" "<<e2.M()<<endl;
//		cout<<"P:	"<<P.Px()<<" "<<P.Py()<<" "<<P.Pz()<<" "<<P.E()<<" "<<P.M()<<endl;
		
		double pq=P.E()*vp.E()-P.Px()*vp.Px()-P.Py()*vp.Py()-P.Pz()*vp.Pz();
		qq=vp.M2();
		double pp=P.M2();
		double k1p=P.E()*e1.E()-P.Px()*e1.Px()-P.Py()*e1.Py()-P.Pz()*e1.Pz();
		double k2p=P.E()*e2.E()-P.Px()*e2.Px()-P.Py()*e2.Py()-P.Pz()*e2.Pz();
		double mlep2=me*me;
		
//		cout<<qq<<endl;
		
		f2 = ( 1/(1.0-qq/(mPsip*mPsip)) ) * ( 1/(1.0-qq/(mPsip*mPsip)) );
		T2 = f2*(8*pq*pq*mlep2 - 8*pp*qq*mlep2 - 2*pp*qq*qq - 8*k1p*k2p*qq + 4*pq*pq*qq)/(qq*qq);
		tree->Fill();
		if(qq>0){
			double binw=0.1/100;
			int m=(int)(qq/binw);
			if( m<100 ) sum[m].push_back(T2);
		}
		Nsuccess++;
	}
	for(int i=0;i<3;i++){
		double sum_temp=0.;
		int N=sum[i].size();
		cout<<"i= "<<i<<" N= "<<N<<endl;
		for(int j=0;j<N;j++){
			sum_temp+=sum[i][j];
			cout<<sum_temp<<endl;
		}
		double mean=sum_temp/(N*1.);
		cout<<i<<" "<<mean<<endl;
		formf->SetBinContent(i,mean);
	}
	formf->Write();
	tree->AutoSave();
	cout<<"success:      "<<Nsuccess<<endl;
	formf->Draw();

	mytime->Print();
}

