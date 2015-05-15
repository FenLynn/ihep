#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void vector3(){
	TVector3 v[100];
	double x[100];
	double y[100];
	double z[100];
	for(int i=0;i<100;i++){
		x[i]=i+1;
		y[i]=(i+1)*5;
		z[i]=(i+1)**2;
		v[i].SetXYZ(x[i],y[i],z[i]);
	}
	for(int i=0;i<100;i++)
	{
		TVector3 unit=v[i].Unit();
		TVector3 temp(v[i].X()/v[i].Mag(),v[i].Y()/v[i].Mag(),v[i].Z()/v[i].Mag());
		if (unit.X() != temp.X())
	//	if (unit.X() != temp.X() || unit.Y() != temp.Y() || unit.Z() != temp.Z())
		{	cout<<i<<endl;
			cout<<unit.X()<<endl;
			cout<<temp.X()<<endl;
	//		cout<<i<<":  "<<unit.X()<<"  "<<temp.X()<<" "<< unit.Y()<<" "<<temp.Y()<<" "<<unit.Z()<<" "<<temp.Z()<<endl;

	}

}
}
