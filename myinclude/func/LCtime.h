#include "TString.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <time.h>
#include <stdio.h>
using namespace std;

int* LCtime(){
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep); //取得当地时间
//    char tmp[64]={0};
	int *t_time=new double[6];
//	sprintf(tmp,"%d\/%d\/%d  %d:%d:%d",(1900+p->tm_year), (1+p->tm_mon), p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	t_time[0]=1900+p->tm_year;
	t_time[1]=1+p->tm_mon;
	t_time[2]=p->tm_mday;
	t_time[3]=p->tm_hour;
	t_time[4]=p->tm_min;
	t_time[5]=p->tm_sec;
//	TString cur_time(Form("%d %d %d  %d:%d:%d",(1900+p->tm_year), (1+p->tm_mon), p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec));
//	ofstream fout("shijian.txt",ios::app); 
//	fout<<tmp;
	return t_time;
//	cout<<tmp<<endl;  
}
