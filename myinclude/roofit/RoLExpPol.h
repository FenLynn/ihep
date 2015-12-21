#ifndef ROLEXPPOL
#define ROLEXPPOL

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;

class RoLExpPol : public RooAbsPdf{

  public: 
  RoLExpPol(const char *name, const char *title, 
  RooAbsReal& _x, RooAbsReal& _exp1,  
  RooAbsReal& _pol0,  RooAbsReal& _pol1, RooAbsReal& _pol2);

  RoLExpPol(const RoLExpPol& other, const char* name=0);
  
  virtual TObject* clone(const char* newname) const { 
    return new RoLExpPol(*this , newname); 
  }

  protected:
  RooRealProxy x ;
  RooRealProxy exp1 ;
  RooRealProxy pol0 ; 
  RooRealProxy pol1 ; 
  RooRealProxy pol2 ; 

  Double_t evaluate() const ; 
  private:
  ClassDef(RoLExpPol,0)

};

#endif
