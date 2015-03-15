#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

template <class T>
T temp_coompare(T a,T b){
	if(a>b) return a;
	else return b;
}

template <class T>
T getMax(T array[],int N){
	T temp_max;
	T maxsig=-9999999.;
	for(int i=0;i<N-1;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			temp_max=temp_coompare(array[i],array[j]);
			if(temp_max>maxsig) maxsig=temp_max;
		}
	}
	return maxsig;
}

template <class T>
int getMaxIndex(T array[],int N){
	int maxi=0;
	int temp_maxi=0;
	T temp_max;
	T maxsig=-9999999.;
	for(int i=0;i<N-1;i++){
		for(int j=i+1;j<N;j++){
			temp_max=temp_coompare(array[i],array[j]);
			temp_maxi=array[i]>array[j]?i:j;	
			if(temp_max>maxsig) {
				maxsig=temp_max;
				maxi=temp_maxi;
			}//	cout<<maxsig<<"     "<<maxi<<endl;
		}
	}
	return maxi; 
}





