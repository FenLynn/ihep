#include<TCanvas.h>
#include<TProfile.h>
#include<TF1.h>
#include <TMath.h>

Double_t x1[20000];
Double_t y1[20000];
Double_t z1[20000];
Double_t max=0,min=28;

void Fit_exp()
{
  TTree *dataPMT = new TTree("PMT location","i-x-y-z");
  Long64_t numPMT = dataPMT->ReadFile("PMTPos_InBallPhoCath.txt","i:x:y:z");
  Float_t i,x,y,z;
  dataPMT->SetBranchAddress("i",&i);
  dataPMT->SetBranchAddress("x",&x);
  dataPMT->SetBranchAddress("y",&y);
  dataPMT->SetBranchAddress("z",&z);  
  for(int k=0;k<numPMT;k++)
    {
      dataPMT->GetEntry(k);
      x1[k]=x;
      y1[k]=y;
      z1[k]=z;
      printf("PMT %d is import\n ",k);
      printf("-------------------\n");
    }
   printf("PMT is over \n");
  //above is get the PMT number &location

  TFile *f=TFile::Open("data.root");
  TTree *record=(TTree*)f->Get("t");  
  TProfile *profile = new TProfile("profile","profile",100,6,28,0,10000);  
  TH1F *hist = new TH1F("hist","hist",numPMT,0,numPMT);
  //get created data from root
  
  Double_t d,xx,yy,zz;
  TVector3 v0,v1;
  Int_t N,total_number,snPMT,nb;
  v0.SetXYZ(10000,0,0); 
  total_number=record->GetEntries();
  
  record->SetBranchAddress("xx",&xx);
  record->SetBranchAddress("yy",&yy);
  record->SetBranchAddress("zz",&zz);
  record->SetBranchAddress("snPMT",&snPMT);
  record->SetBranchAddress("N",&N);
  
  for(k=0;k<total_number;k++)
  {
	record->GetEntry(k);
	hist->Fill(snPMT);
	v1.SetXYZ(xx,yy,zz);
	d=(v1-v0).Mag();
	}
	
  for(k=0;k<numPMT;k++)
	{
	v1.SetXYZ(x1[k],y1[k],z1[k]);
	d=(v1-v0).Mag()/1000;
	nb=hist->GetBinContent(k);
	profile->Fill(d,nb);
	if(d>max) max=d;
	if(d<min) min=d;
	}
   TCanvas *c1 =new TCanvas("c1");
   //hist->Draw();
   profile->Draw();
   TF1 *f1 = new TF1("f1","[0]/x/x*TMath::Exp(-x/[1])",8,28);
   f1.SetParameters(30,20);
   profile->Fit(f1,"","",8,28);
   profile->Draw();
   printf("Succeed!");
  
 
}
