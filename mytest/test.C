/*
 *======================================================================================
 *       FILENAME: test.C
 *        CREATED: 2014年11月27日 00时38分22秒
 *         AUTHOR: Fengyun Li,lfypku@gmail.com
 *    DESCRIPTION: 
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <TH1F.h>
#include <TCanvas.h>
#include "/workfs/bes/lify/package/include/rootall.h"

using namespace std;

int main()
{
	float a=1.;
	float b=2.;
	float c=3.;
	TH1F *h=new TH1F("h","h",4,0,4);

	for(int i=0;i<10;i++)
	{
		h->Fill(a);
		h->Fill(b);
		h->Fill(c);
		cout<<"a:"<<a<<endl;
		cout<<"b:"<<b<<endl;
		cout<<"c:"<<c<<endl;
	}
	TCanvas *c1=new TCanvas("c1","c2");
	c1->cd(1);
	h->Draw();
	
	cout<<a<<endl;
}

