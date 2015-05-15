#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void angle(){
	TLorentzVector v1(0,1,0,9);
	TLorentzVector v2(0,0,1,8);

	double angle = v1.Angle(v2.Vect());
	double cosangle = cos(angle);

	cout<<angle<<endl<<cosangle<<endl;

}
