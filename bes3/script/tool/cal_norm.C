#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"


void cal_norm()
{
double 	Ngen=1.16e6;
double	Nsur=106;
double	NexptX=23266.1;
double	ENexptX=4010.2;

double Nob=(NexptX*Nsur)/Ngen;
double ENob=(ENexptX*Nsur)/Ngen;

cout<<Nob<<" +- "<<ENob<<endl;
}




