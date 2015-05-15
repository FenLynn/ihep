#include "TString.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <time.h>
#include <stdio.h>
using namespace std;

TString LMtime(int start[],int end[]){
//    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//   time_t timep;
 //   struct tm *p;
//    time(&timep);
//    p = localtime(&timep); //取得当地时间
//    char tmp[64]={0};
//	int *t_time[6];
//	sprintf(tmp,"%d\/%d\/%d  %d:%d:%d",(1900+p->tm_year), (1+p->tm_mon), p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
		
//	TString cur_time(Form("%d %d %d  %d:%d:%d",(1900+p->tm_year), (1+p->tm_mon), p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec));
//	ofstream fout("shijian.txt",ios::app); 
//	fout<<tmp;
	TString minus_time;
	int minus[6];
	for(int i=0;i<6;i++){
		minus[i]=0;
	}
	if(end[5]>=start[5]) minus[5]=end[5]-start[5];
	else
	{
		minus[5]=end[5]+60-start[5];
		end[4]--;
	}
	if(end[4]>=start[4]) minus[4]=end[4]-start[4];
	else
	{
		minus[4]=end[4]+60-start[4];
		end[3]--;
	}
	if(end[3]>=start[3]) minus[3]=end[3]-start[3];
	else
	{
		minus[3]=end[3]+24-start[3];
		end[2]--;
	}
	if(end[2]>=start[2]) minus[2]=end[2]-start[2];
	else
	{
		minus[2]=end[2]+30-start[2];
		end[1]--;
	}
	if(end[1]>=start[1]) minus[1]=end[1]-start[1];
	else
	{
		minus[1]=end[1]+12-start[1];
		end[0]--;
	}
	minus[0]=end[0]-start[0];
	minus_time=Form("%d/%d/%d %d:%d:%d",minus[0],minus[1],minus[2],minus[3],minus[4],minus[5]);
	return minus_time;
//	cout<<tmp<<endl;  
}
