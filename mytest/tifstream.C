#include "/workfs/bes/lify/myinclude/rootall.h"

ifstream inp("data.txt");
void tifstream(){
	int m,n;
	int i=0;
	int x[10];
	int y[10];
	for(int k=0;k<10;k++)
	{
		x[k]=-1;
		y[k]=-1;
	}
	while(inp >> x[i] >> y[i]) 
	{
		cout<<i<<" "<<x[i]<<" "<<y[i]<<endl;
		i++;
	}
	inp.close();

}

