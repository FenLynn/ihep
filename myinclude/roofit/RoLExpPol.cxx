#include <math.h>
#include <iostream>
#include "RooFit.h"
#include "RoLExpPol.h"
#include "RooAbsReal.h"

ClassImp(RoLExpPol)
	RoLExpPol::RoLExpPol(const char *name, const char *title,
			RooAbsReal& _x, RooAbsReal& _exp1,RooAbsReal& _pol0, RooAbsReal& _pol1, RooAbsReal& _pol2) :
		RooAbsPdf(name,title),
		x("x","x",this,_x),
		exp1("exp1","exp1",this,_exp1),
		pol0("pol0","pol0",this,_pol0),
		pol1("pol1","pol1",this,_pol1),
		pol2("pol2","pol2",this,_pol2)
{ }

RoLExpPol::RoLExpPol(const RoLExpPol& other, const char* name) :
	RooAbsPdf(other,name), x("x",this,other.x), exp1("exp1",this,other.exp1),
	pol0("pol0",this,other.pol0),pol1("pol1",this,other.pol1),pol2("pol2",this,other.pol2)
{ }

Double_t RoLExpPol::evaluate() const { 

	double p_dalitz;
	double p_pol;
	double total;

	p_dalitz=1./(1-x*x/(exp1*exp1));

	if(x>0.02&&x<0.13){
		p_pol=pol0+pol1*x+pol2*x*x;
	}
	else {
		p_pol=0.;
	}
	total=p_dalitz-p_pol;
	return total;
}
	
	
	




//	double ppi0sqr = (mY4260*mY4260-(x+mpi0)*(x+mpi0))*(mY4260*mY4260-(x-mpi0)*(x-mpi0));
//	ppi0 = sqrt(ppi0sqr)/(2*mY4260);

//	if( x*x-(mDp+mDstm)*(mDp+mDstm)>0 ) {
//		pDstar = sqrt((x*x-(mDp+mDstm)*(mDp+mDstm))*(x*x-(mDp-mDstm)*(mDp-mDstm)))/(2*x);
//	}
//	else {
///		pDstar = 0;
//	}
//	//double eff = 1.0;
//	double eff1 = 0.2089-0.04268*x;
//	double eff2 = 0.2089+(-0.04268+0.3699)*3.91-0.3699*x;
//	if(eff1>0&&eff2>0){ 
//		bw = 1;
//		//bw = ppi0*pDstar/((x*x-mean*mean)*(x*x-mean*mean) + mean*mean*width*width);
//		if(x<=3.866)bw = ppi0*pDstar/((x*x-mean*mean)*(x*x-mean*mean) + mean*mean*width*width)*(0.2089-0.04268*3.91);
//		if(x>3.866&&x<=3.91)bw = ppi0*pDstar/((x*x-mean*mean)*(x*x-mean*mean) + mean*mean*width*width)*eff1;
///		if(x>3.91)bw = ppi0*pDstar/((x*x-mean*mean)*(x*x-mean*mean) + mean*mean*width*width)*eff2;


//		return bw;
//	}else{
//		return 0;
//	}

