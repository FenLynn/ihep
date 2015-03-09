/*
 *======================================================================================
 *       FILENAME: MyHead.h
 *        CREATED: 2014年11月23日 23时14分19秒
 *         AUTHOR: Fengyun Li,lfypku@gmail.com
 *    DESCRIPTION: 
 * =====================================================================================
 */
#ifndef MYHEAD_H
#define MYHEAD_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TVector3.h>
#include <TH1F.h>
using namespace std;


#endif
/*
#ifndef MYSIGMC_EXTERNAL
#define MYSIGMC_EXTERNAL

TH1* Sigmc::GetBranchHist(char *branchName)
{
 
	char *branchType=typeid(branchName);
	if(branchName !="double" && branchName!="int" && branchName!="Double_t" && branchName!="Int_t")
	{
		cout<<"This branch is not a simple branch!"<<endl;
		return 0;
	}
	
	TH1 *branchHist;
	return branchHist;

}

 
#define MYSIGMC_EXTERNAL
*/
