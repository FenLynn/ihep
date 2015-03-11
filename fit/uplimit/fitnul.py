import ROOT
import math
import sys

from ROOT import (gROOT, gSystem, TCanvas, TF1, TFile, TTree, gRandom, TH1F, TChain, \
                  RooFit,RooRealVar, RooFormulaVar, RooGaussian, RooChebychev, RooArgList, \
                  RooArgSet, RooAddPdf, RooDataSet, RooCategory, RooSimultaneous, RooNLLVar, \
                  RooBreitWigner, RooCBShape, RooFFTConvPdf, RooGlobalFunc, RooMinuit, \
                  RooConstVar, RooProfileLL)

gROOT.Reset()
gSystem.Load( "libRooFit" )
data = ROOT.TChain("data")
data.Add("mee.root")
myc = TCanvas("myc","My Canvas", 1400, 400)
myc.Divide(3)

## options for plots and verboses: 0, 1, 2
optp = 1

## this time using RooNLLVar
def fitMass(rangem=[0.4,2.0], iflag=1, CBpar=[0.,0.,0.]):
    global myc, fitres
    m0=sum(rangem)/2
    #w0=(rangem[1]-rangem[0])/10
    w0=0.004
    mass = RooRealVar("ee_ivm", "ee_ivm", rangem[0], rangem[1])
    
    if iflag == 1:
        ###Construct signal pdf with gaus
        mean = RooRealVar("mean", "mean", m0)
        sigma = RooRealVar("selfigma", "sigma", w0)
        signal = RooGaussian("signal", "signal", mass, mean, sigma)
    elif iflag == 2 or iflag == 3:
        ## Construct signal pdf with CB function
		print CBpar[0],CBpar[1],CBpar[2]
		cbmean = RooRealVar("cbmean", "cbmean" , m0)
		cbsigma = RooRealVar("cbsigma", "cbsigma",CBpar[0])
		n1= RooRealVar("n1","", CBpar[1])
		alpha= RooRealVar("alpha","",CBpar[2])
		cbsigma.setConstant(ROOT.kTRUE)
		n1.setConstant(ROOT.kTRUE)
		alpha.setConstant(ROOT.kTRUE)
		signal = RooCBShape("cball", "crystal ball1", mass, cbmean, cbsigma, alpha, n1)
#    elif iflag ==3:
#        pass
    else:
        print "ERROR, please specify signal shape for fitting!!"
        sys.exit()

    # Construct background pdf
    a0 = RooRealVar("a0","a0",0.1,-1,1)
    a1 = RooRealVar("a1","a1",0.004,-1,1)
    background = RooChebychev("background","background",mass,RooArgList(a0,a1))
    # Construct composite pdf
    if iflag ==1:
        up_nsig = 40
    else:
        up_nsig = 60
    nsig = RooRealVar("nsig", "nsig", 5, 0.0, up_nsig)
    nbkg = RooRealVar("nbkg", "nbkg", 800, 0, 3000)
    
    #frac = RooRealVar("frac", "frac", 0.001, 0.0001, 0.1)
    model = RooAddPdf("model", "model", RooArgList(signal, background), RooArgList(nsig, nbkg))
    #model = RooAddPdf("model", "model", RooArgList(signal, background), RooArgList(frac))
    mcdata = RooDataSet("ds","ds",RooArgSet(mass),RooFit.Import(data), RooFit.Cut("ee_ivm<"+str(rangem[1])+"&&ee_ivm>"+str(rangem[0])))
    if optp == 1:
        ipr = 1
        verbose = 0
    elif optp == 2:
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

    llhood = RooFormulaVar("llhood","exp(-0.5*(nll-themin*0.95))", RooArgList(nll,themin))
    
    if optp:
        xframe = mass.frame(RooFit.Title("mass of ee pair"))
        
        xframe3 = nsig.frame(RooFit.Title("number of signal"))
        xframe3.SetYTitle("Likelihood")

        mcdata.plotOn(xframe)      
        model.plotOn(xframe)
        model.plotOn(xframe,RooFit.Components("background"),RooFit.LineStyle(ROOT.kDashed),RooFit.LineColor(ROOT.kRed))
        model.plotOn(xframe,RooFit.Components("cball"),RooFit.LineStyle(ROOT.kDashed),RooFit.LineColor(ROOT.kGreen))


        myc.cd(1)
        xframe.Draw()
     
        #pll.plotOn(xframe2,RooFit.LineColor(ROOT.kRed))    
        print "***** archmin ",themin.Print()
        #llhoodP.plotOn(xframe3, RooFit.LineColor(ROOT.kRed))
        
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


def nsig2eps(ul_nsig):
    ul_eps = -1.0


    return ul_eps

## please put CB parameters here in the format
## cbsigma, n1, alpha
CBpar=[0.00626, 1.178, 1.260,1.0]

## flag to indicate signal pdf used
## 1: gauss 2: single CB  3: step-wise CB
iflag=3
mstep = 25
halfwidth = 0.1
mstart = 0.8
mend = 1.2
binwidth = (mend-mstart)/(mstep-1)
hUL = TH1F("hUL","hUL", mstep, mstart-0.5*binwidth, mend+0.5*binwidth)
hUL.SetTitle(";mee(GeV); nsignal UL(90%CL)")
if iflag==3:
	sstep = 0.1
	hsstep = sstep/2
#	sig_par = ROOT.TChain("siginfo")
#	sig_par.Add("outsig.root")
	Nsigsam=14
	sig_array = [0]*Nsigsam
	cbsiginfo = open("cbinfo.txt","r")
	temp_sigsam = 0
	for read_line in cbsiginfo.readlines():
		sig_array[temp_sigsam] =read_line.split(" ")
		temp_sigsam=temp_sigsam+1
	cbsiginfo.close()
else:
	pass

ibin=1
for x in frange(mstart,mend,mstep):
	if optp: print "frange... ", x
	print "frange... ", x-0.5*binwidth,x+0.5*binwidth
	if iflag == 3:
		if x<=float(sig_array[0][0]) :
			CBpar[float(sig_array[0][1]),float(sig_array[0][2]),float(sig_array[0][3]),float(sig_array[0][4])]
		elif x>=float(sig_array[Nsigsam-1][0]):
			CBpar[float(sig_array[Nsigsam-1][1]),float(sig_array[Nsigsam-1][2]),float(sig_array[Nsigsam-1][3]),float(sig_array[Nsigsam-1][4])]
		else:
			nbins=int(round((x-float(sig_array[0][0]))/sstep))
			#CBpar[float(sig_array[int(nbins)][1]),float(sig_array[int(nbins)][2]),float(sig_array[int(nbins)][3])]
			#CBpar[float(sig_array[1][1]),float(sig_array[1][2]),float(sig_array[1][3])]
			#CBpar=[0.00626, 1.178, 1.260]
			CBpar=[float(sig_array[nbins][1]), float(sig_array[nbins][2]), float(sig_array[nbins][3]),float(sig_array[nbins][4])]
	else:
		pass
	ul_nsig = fitMass([x-halfwidth,x+halfwidth], iflag, CBpar)
	hUL.SetBinContent(ibin, ul_nsig)
	ibin += 1

hUL.Draw()
raw_input()
