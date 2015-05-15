#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void boost(){
	TLorentzVector a;
	a.SetPxPyPzE(3,3,5,8);
	TVector3 a1(a.Px(),a.Py(),a.Pz());
	TVector3 a2=a.BoostVector();
	cout<<a1.Px()<<endl<<a1.Py()<<endl<<a1.Pz()<<endl;
	cout<<a2.Px()<<endl<<a2.Py()<<endl<<a2.Pz()<<endl;

}
