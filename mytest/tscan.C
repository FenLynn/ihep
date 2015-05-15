#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "/workfs/bes/lify/myinclude/rootall.h"
#include "TTree.h"

void tscan(){
	TFile *f=new TFile("meeh02.root","READ");
	TIter nextkey(f->GetListOfKeys());
	TKey *key;
	while (key = (TKey*)nextkey()){
		TTree *tree = (TTree *)key->ReadObj();
		cout<<tree->GetName()<<endl;
	}
}

