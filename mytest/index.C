#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"

void index(){
	TString a("hello,world,lifengyun,nihao,u1.6_h0.2");
	{
		int m=3;
		int n=4;
		int p=m+n;
	}
	cout<<p<<endl;	
	cout<<a.Index("_h0.2")<<endl;
}
