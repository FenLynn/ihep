import ROOT
import math

from ROOT import (gROOT, gSystem, TCanvas, TF1, TFile, TTree, gRandom, TH1F, TChain, \
                  RooFit,RooRealVar, RooFormulaVar, RooGaussian, RooChebychev, RooArgList, \
                  RooArgSet, RooAddPdf, RooDataSet, RooCategory, RooSimultaneous, RooNLLVar, \
                  RooBreitWigner, RooCBShape, RooFFTConvPdf, RooGlobalFunc, RooMinuit, \
                  RooConstVar, RooProfileLL)

gROOT.Reset()
gSystem.Load( "libRooFit" )
data = ROOT.TChain("data")
data.Add("result.root")
myc = TCanvas("myc","My Canvas", 1400, 400)
myc.Divide(3)

optp = 0

## this time using RooNLLVar
def fitMass(rangem=[0.2,3.0]):
    global myc, fitres
    m0=sum(rangem)/2
    #w0=(rangem[1]-rangem[0])/10
    w0=0.004
    mass = RooRealVar("ee_ivm", "ee_ivm", rangem[0], rangem[1])
    # Construct signal pdf
    mean = RooRealVar("mean", "mean", m0)
    sigma = RooRealVar("sigma", "sigma", w0)
    signal = RooGaussian("signal", "signal", mass, mean, sigma)
    # Construct background pdf
    a0 = RooRealVar("a0","a0",0.1,-1,1)
    a1 = RooRealVar("a1","a1",0.004,-1,1)
    background = RooChebychev("background","background",mass,RooArgList(a0,a1))
    # Construct composite pdf
    nsig = RooRealVar("nsig", "nsig", 2, 0, 40)
    nbkg = RooRealVar("nbkg", "nbkg", 80, 0, 500)
    #frac = RooRealVar("frac", "frac", 0.001, 0.0001, 0.1)
    model = RooAddPdf("model", "model", RooArgList(signal, background), RooArgList(nsig, nbkg))
    #model = RooAddPdf("model", "model", RooArgList(signal, background), RooArgList(frac))
    mcdata = RooDataSet("ds","ds",RooArgSet(mass),RooFit.Import(data), RooFit.Cut("ee_ivm<"+str(rangem[1])+"&&ee_ivm>"+str(rangem[0])))
    if optp:
        ipr = 1
        verbose = 1
    else:
        ipr = -1
        verbose = 0
    
    fitres=model.fitTo(mcdata,RooFit.Save(),RooFit.Minos(1), RooFit.Strategy(2),\
                       RooFit.PrintLevel(ipr), RooFit.Verbose(verbose))
    nll=RooNLLVar("nll","nll",model,mcdata,RooFit.Range(rangem[0], rangem[1]))    
    pll=nll.createProfile(RooArgSet(nsig))
    Profile = RooProfileLL("Profile", "Profile", nll, RooArgSet(nsig))
    llhoodP = RooFormulaVar("llhoodP","exp(-0.5*Profile)",RooArgList(Profile))
    xframe2 = nsig.frame(RooFit.Title("number of signal"))    
    nllplot = nll.plotOn(xframe2,RooFit.ShiftToZero())    
    themin = RooConstVar("themin","themin",nllplot.GetMinimum())

    llhood = RooFormulaVar("nll2","exp(-0.5*(nll-themin*0.95))", RooArgList(nll,themin))
    
    if optp:
        xframe = mass.frame(RooFit.Title("mass of ee pair"))
        
        xframe3 = nsig.frame(RooFit.Title("number of signal"))

        mcdata.plotOn(xframe)      
        model.plotOn(xframe,RooFit.Components(RooArgSet(background)),RooFit.LineStyle(ROOT.kDashed),RooFit.LineColor(ROOT.kRed))
        model.plotOn(xframe,RooFit.Components(RooArgSet(signal)),RooFit.LineStyle(ROOT.kDashed),RooFit.LineColor(ROOT.kGreen))
        model.plotOn(xframe)
        myc.cd(1)
        xframe.Draw()
     
        pll.plotOn(xframe2,RooFit.LineColor(ROOT.kRed))    
        print "***** archmin ",themin
        #nll.plotOn(xframe2)    
        llhoodP.plotOn(xframe3, RooFit.LineColor(ROOT.kRed))
        
        llhood.plotOn(xframe3)
        myc.cd(2)
    
        xframe2.SetMinimum(0)
        xframe2.Draw()
        myc.cd(3)  
        xframe3.Draw()
        myc.Update()
        raw_input()

    nsig.setRange("IntRange1",0,1000.)
    Int1 = llhood.createIntegral(RooArgSet(nsig), ROOT.RooFit.Range('IntRange1'))
    Int1Val = Int1.getVal()
    i = 0
    hit = False
    while not(hit):
        i=i+1
        nsig.setRange("IntRange2",0,float(i))
        Int2 = llhood.createIntegral(RooArgSet(nsig), ROOT.RooFit.Range('IntRange2'))
        if Int2.getVal() >= Int1Val*0.9:
            print "&&& ",i
            hit=True
            return i
    
def frange(start,stop,steps):
    ''' Computes a range of floating value.
        
        Input:
            start (float)  : Start value.
            end   (float)  : End value
            steps (integer): Number of values
        
        Output:
            A list of floats
        
        Example:
            >>> print floatrange(0.25, 1.3, 5)
            [0.25, 0.51249999999999996, 0.77500000000000002, 1.0375000000000001, 1.3]
    '''
    return [start+float(i)*(stop-start)/(float(steps)-1) for i in xrange(steps)]


mstep = 100
halfwidth = 0.1
mstart = 0.4
mend = 2.0
binwidth = (mend-mstart)/(mstep-1)
hUL = TH1F("hUL","hUL", mstep, mstart-0.5*binwidth, mend+0.5*binwidth)
hUL.SetTitle(";mee(GeV); UL(90%CL)")
ibin=1
for x in frange(mstart,mend,mstep):
    if optp: print "frange... ", x
    print "frange... ", x-0.5*binwidth,x+0.5*binwidth
    ul = fitMass([x-halfwidth,x+halfwidth])
    hUL.SetBinContent(ibin, ul)
    ibin += 1

hUL.Draw()
raw_input()
