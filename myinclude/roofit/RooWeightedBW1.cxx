#include <math.h>
#include <iostream>
#include "RooFit.h"
#include "RooWeightedBW1.h"
#include "RooAbsReal.h"

ClassImp(RooWeightedBW1)
RooWeightedBW1::RooWeightedBW1(const char *name, const char *title,
RooAbsReal& _x, RooAbsReal& _mean, RooAbsReal& _width) :
RooAbsPdf(name,title),
x("x","x",this,_x),
mean("mean","mean",this,_mean),
width("width","width",this,_width)
{ }

RooWeightedBW1::RooWeightedBW1(const RooWeightedBW1& other, const char* name) :
RooAbsPdf(other,name), x("x",this,other.x), mean("mean",this,other.mean),
width("width",this,other.width)
{ }

Double_t RooWeightedBW1::evaluate() const { 
    
double pDstar, ppi0, bw;
const  double  mDp=1.86962, mDstm=2.01028, mpi0=0.1349766, mY4260=4.26;
    
double ppi0sqr = (mY4260*mY4260-(x+mpi0)*(x+mpi0))*(mY4260*mY4260-(x-mpi0)*(x-mpi0));
ppi0 = sqrt(ppi0sqr)/(2*mY4260);

if( x*x-(mDp+mDstm)*(mDp+mDstm)>0 ) {
     pDstar = sqrt((x*x-(mDp+mDstm)*(mDp+mDstm))*(x*x-(mDp-mDstm)*(mDp-mDstm)))/(2*x);
 }
    else {
     pDstar = 0;
    }
     //double eff = 1.0;
     double eff1 = 0.2089-0.04268*x;
     double eff2 = 0.2089+(-0.04268+0.3699)*3.91-0.3699*x;
   if(eff1>0&&eff2>0){ 
             bw = 1;
    //bw = ppi0*pDstar/((x*x-mean*mean)*(x*x-mean*mean) + mean*mean*width*width);
    if(x<=3.866)bw = ppi0*pDstar/((x*x-mean*mean)*(x*x-mean*mean) + mean*mean*width*width)*(0.2089-0.04268*3.91);
    if(x>3.866&&x<=3.91)bw = ppi0*pDstar/((x*x-mean*mean)*(x*x-mean*mean) + mean*mean*width*width)*eff1;
    if(x>3.91)bw = ppi0*pDstar/((x*x-mean*mean)*(x*x-mean*mean) + mean*mean*width*width)*eff2;
   
    
       return bw;
    }else{
       return 0;
    }
   }

