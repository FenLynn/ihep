#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void single(double mx,double my,double mz){
	TVector3 p0(0.,0.,0.);
	TVector3 pKs(0.,0.,0.02);
	double zz=7;
	TVector3 mphoton(mx,my,mz);
	double xx,yy;
	xx=(zz-pKs.Z())*mphoton.X()/mphoton.Z()+pKs.X();
	yy=(zz-pKs.Z())*mphoton.Y()/mphoton.Z()+pKs.Y();
	TVector3 phit(xx,yy,zz);
	TVector3 punit=mphoton.Unit();
	TVector3 mchg=mphoton.Mag()*punit;
	cout<<"origin:  "<<mphoton.X()<<" "<<mphoton.Y()<<" "<<mphoton.Z()<<endl;
	cout<<"changed: "<<mchg.X()<<" "<<mchg.Y()<<" "<<mchg.Z()<<endl;
}


void hit(){
	for(int i=0;i<100;i++){
		double t=i+1;
		single(-t,t*2,t**2);
	}
}
