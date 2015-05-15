#include "TString.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <time.h>
#include <stdio.h>
using namespace std;

TString LTime(){
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep); //取得当地时间
    char tmp[64]={0};
//	sprintf(tmp,"%d\/%d\/%d  %d:%d:%d",(1900+p->tm_year), (1+p->tm_mon), p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	TString cur_time(Form("%d %d %d  %d:%d:%d",(1900+p->tm_year), (1+p->tm_mon), p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec));
//	ofstream fout("shijian.txt",ios::app); 
//	fout<<tmp;
	return cur_time;
//	cout<<tmp<<endl;  
}
