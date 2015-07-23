#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"


void cal_norm()
{
double 	Ngen=11600000;
double	Nsur=1194;
double	NexptX=1964130;
double	ENexptX=70517;

double Nob=(NexptX*Nsur)/Ngen;
double ENob=(ENexptX*Nsur)/Ngen;

cout<<Nob<<" +- "<<ENob<<endl;
}




