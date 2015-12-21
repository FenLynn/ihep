#ifndef ROOWEIGHTEDBW1
#define ROOWEIGHTEDBW1

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;

class RooWeightedBW1 : public RooAbsPdf{

  public: 
  RooWeightedBW1(const char *name, const char *title, 
  RooAbsReal& _x, RooAbsReal& _mean,  
  RooAbsReal& _width);

  RooWeightedBW1(const RooWeightedBW1& other, const char* name=0);
  
  virtual TObject* clone(const char* newname) const { 
    return new RooWeightedBW1(*this , newname); 
  }

  protected:
  RooRealProxy x ;
  RooRealProxy mean ;
  RooRealProxy width ; 

  Double_t evaluate() const ; 
  private:
  ClassDef(RooWeightedBW1,0)

};

#endif
