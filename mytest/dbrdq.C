#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void dbrdq(){
	double ml=0.000511;
	double alpha=1./137;
	double x;
	double mPsip = 3.68609;
	double mpsi = 3.097;
	double mP=0.958;
	TF1 *f2 =new TF1("f2","( 1/(1.0-x/([0]*[0])) ) * ( 1/(1.0-x/([0]*[0])))",0,3);
	f2->SetParameter(0,mPsip);	
//	y=(1./3)*(alpha*alpha/(24*TMath::Pi()*pow(mpsi,3)))*(f2/x)*sqrt(1-4*ml*ml/x)*(1+2*ml*ml/x)*pow(pow((mpsi*mpsi-mP*mP+x),2)-4*mpsi*mpsi*x,3/2);
	TF1 *yy=new TF1("yy","(1./3)*([0]*[0]/(24*TMath::Pi()*pow([1],3)))*(f2/x)*sqrt(1-4*[2]*[2]/x)*(1+2*[2]*[2]/x)*pow(pow(([1]*[1]-[3]*[3]+x),2)-4*[1]*[1]*x,3/2)",0,3);
	yy->SetParameters(alpha,mpsi,ml,mP);
	TF1 *logyy=new TF1("logyy","log(yy)",0,3);

	logyy->Draw();
}
