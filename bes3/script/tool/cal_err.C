#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"


void cal_err3()
{
double	Njpsi=1310.6e6;
double	ENjpsi=7.0e6;
double	Brjpsi=1.05e-4;
double 	EBrjpsi=0.18e-4;
double	Bretap=0.291;
double 	EBretap=0.005;
double	BrX=1.;
double	EBrX=0.;
	
double	Nob=Njpsi*Brjpsi*Bretap*BrX;
double	ENob=Nob*sqrt((ENjpsi/Njpsi)**2+(EBrjpsi/Brjpsi)**2+(EBretap/Bretap)**2+(EBrX/BrX)**2);
cout<<Nob<<" +- "<<ENob<<endl;
}


void cal_err()
{
double	Njpsi=1310.6e6;
double	ENjpsi=7.0e6;
double	Brjpsi=5.15e-3;
double 	EBrjpsi=0.16e-3;
double	BrX=0.291;
double	EBrX=0.005;
	
double	Nob=Njpsi*Brjpsi*BrX;
double	ENob=Nob*sqrt((ENjpsi/Njpsi)**2+(EBrjpsi/Brjpsi)**2+(EBrX/BrX)**2);
cout<<Nob<<" +- "<<ENob<<endl;
}






