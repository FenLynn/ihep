#include<TTree.h>
#include <TVector3.h>
#include <TRandom3.h>
#include <TMath.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TH1.h>
#include<stdlib.h>
#include<TFile.h>

TVector3 vr(10000,0,0);         //location of the source   
Double_t rPMT=250;				//radius of the detector						
Int_t nPMT=0;
Double_t xl[20000];
Double_t yl[20000];
Double_t zl[20000];
Double_t pi2 = TMath::Pi()*2;
Int_t NP=200000;
Double_t dr=100;


Double_t GetD1(TVector3 v,Int_t IPMT,Double_t dm)
{
  Double_t d,d_1,d_2;
  TVector3 v_i;
  if(dm>rPMT) return -1;
  v_i.SetXYZ(xl[IPMT],yl[IPMT],zl[IPMT]);
  d_1=TMath::Abs((v_i-vr)*v/v.Mag());
  d_2=TMath::Sqrt(rPMT*rPMT-dm*dm);
  d=d_1-d_2;
  return d;
}
Double_t GetDist(TVector3 v,Int_t *IPMT)
{
   Double_t d=1E10,d1=0;
   *IPMT=-1;
   TVector3 v_i;
   for(Int_t i=0;i<nPMT;i++)
     {
        v_i.SetXYZ(xl[i],yl[i],zl[i]);
	d1=((v_i-vr).Cross(v)).Mag()/v.Mag();
	if(d1<d){d=d1;*IPMT=i;} 
     }
   return d;
}

void data_PMT()
{
  TFile *f=new TFile("data.root","RECREATE");
  TTree *dataPMT = new TTree("PMT location","i-xyz");
  Long64_t numPMT = dataPMT->ReadFile("PMTPos_InBallPhoCath.txt","i:x:y:z");
  //read the file into the tree
  nPMT=numPMT;
  Float_t i,x,y,z;
  dataPMT->SetBranchAddress("i",&i);
  dataPMT->SetBranchAddress("x",&x);
  dataPMT->SetBranchAddress("y",&y);
  dataPMT->SetBranchAddress("z",&z);
  
  for(int k=0;k<nPMT;k++)
    {
      dataPMT->GetEntry(k);
      xl[k]=x;
      yl[k]=y;
      zl[k]=z;
      printf("------------------------------\n");
	printf("PMT:%d\n",k);

    }
	//save the dataPMT into the list
  TTree *t = new TTree("t","");
  Double_t xx[20000], yy[20000], zz[20000],dd[20000];
  Int_t N,snPMT[20000];
  t->Branch("N",&N,"N/I");
  t->Branch("xx",xx,"xx[N]/D");
  t->Branch("yy",yy,"yy[N]/D");
  t->Branch("zz",zz,"zz[N]/D");
  t->Branch("dd",dd,"dd[N]/D");
  t->Branch("snPMT",&snPMT,"snPMT[N]/I");
  //be ready for the tree to store the data
 //TH1F *h1 =new TH1F("","",88,6,28);
  TVector3 v0,v1;
  Double_t dnm,dist;
  
  Int_t ipmt;
  Int_t ievt=0;
  //TH1F *h1 =new TH1F("","",88,6,28);
  while(ievt<NP)
    {
      printf("------------------------------\n");
      printf("EVent:%d\n",ievt);
      ievt++;
      N=0;
      Double_t costh=gRandom->Rndm()*2-1;
      Double_t th = TMath::ACos(costh);
      Double_t phi= gRandom->Rndm()*pi2;		//Set the random angle
      v0=vr;
      v1.SetMagThetaPhi(dr,th,phi);
      dnm=GetDist(v1,&ipmt);
      dist=GetD1(v1,ipmt,dnm);
      if(dist<0) continue;
      Double_t Poss=gRandom->Rndm();
      if(Poss>TMath::Exp(-dist/20000)) continue;
      else{
	      xx[N]=xl[ipmt];
	      yy[N]=yl[ipmt];
	      zz[N]=zl[ipmt];
	      dd[N]=dist;
	      snPMT[N]=ipmt;
	      N++;
	      //h1->Fill(dist/1000);
	      t->Fill();
	      continue;
	      }
      
    }
	
	
  TCanvas *c1 =new TCanvas("c1","Events with Didtance");
  t->Draw("dd");
  //c1->GetXAxis()->SetTitle("Distance");
  //TFile out_f("./h1_final.root","RECREATE");
  //h1->Write();
  t->Write();
  f.Close();
  printf("Succeed!");
  //out_f.Close();
  /*
  TCanvas *c2 =new TCanvas();
  TF1 f("","[0]*TMath::Exp(-x/[1])",6,28);
  f.SetParameters(30,20);
  h1->Fit(&f,"","",7.5,27.3);
  h1->Draw();
  Double_t mean,sum,decay;
  mean=h1->GetMean();
  sum=h1->GetEntries();
  decay=mean/(TMath::Log(NP/sum));//!!!!!!!!!!
  printf("=======================================\n");
  printf("the decay Distance is : %f \n",decay);
  */
}
