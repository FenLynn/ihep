#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void lortz(){
	TLorentzVector *a=new TLorentzVector(5,4,3,2);
	TLorentzVector *b=new TLorentzVector(55,44,33,22);
	TLorentzVector *c=new TLorentzVector(555,444,333,222);
	
	TLorentzVector *d=new TLorentzVector();
	*d=*a+*b+*c;
	double invM;
	invM=(*a+*b+*c).M();
	cout<<d->E()<<endl;
	cout<<d->Px()<<endl;
	cout<<d->Py()<<endl;
	cout<<d->Pz()<<endl;
	cout<<invM<<endl;
	
}
