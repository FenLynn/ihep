{
	TDatime *mytime1 = new TDatime();
	for(int i=0;i<10000000;i++){;}
	TDatime *mytime2 = new TDatime();
	cout<<mytime1->Convert(1)<<endl;
	cout<<mytime2->Convert()<<endl;
	cout<<mytime1->Get()<<endl;
//	cout<<(mytime2->Convert()-mytime1->Convert)
	mytime->Print();
}

