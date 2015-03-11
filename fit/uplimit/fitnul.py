import ROOT
import math
import sys
import json

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

## this time using RooNLLVar
def fitMass(rangem=[0.4,2.0], iflag=1, iopt_bkgshape = 0, CBpar=[0.,0.,0.]):
    global myc, fitres
    m0 = sum(rangem)/2
    #w0=(rangem[1]-rangem[0])/10
    w0 = 0.004
    mass = RooRealVar("ee_ivm", "ee_ivm", rangem[0], rangem[1])
    
    if iflag == 1:
        ###Construct signal pdf with gaus
        mean = RooRealVar("mean", "mean", m0)
        sigma = RooRealVar("sigma", "sigma", w0)
        signal = RooGaussian("signal", "signal", mass, mean, sigma)
    elif iflag == 2 or iflag == 3:
        ## Construct signal pdf with CB function
        ##print "outinfo",x,CBpar[0],CBpar[1],CBpar[2],CBpar[3]
        cbmean = RooRealVar("cbmean", "cbmean" , m0)
        cbsigma = RooRealVar("cbsigma", "cbsigma",CBpar[0])
        n1 = RooRealVar("n1","", CBpar[1])
        alpha = RooRealVar("alpha","",CBpar[2])
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
    a2 = RooRealVar("a2","a2",0.001,-1,1)
    if iopt_bkgshape == 0:
        background = RooChebychev("background","background",mass,RooArgList(a0,a1))
    else:
        background = RooChebychev("background","background",mass,RooArgList(a0,a1,a2))
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
        if optp: print "***** archmin ",themin.Print()
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
            if optp: print "&&& ",i
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



def getShape(m, shape_parlist, i_relative = 0  ):

    """
    get the signal shape used in the present fitting

    pars:
    shape_parlist: is the float list previously defined
    i_relative: indicate which to use
             = 0: the closest shape
             = 1: the next closest shape in high mass direction
             = -1: the next closest shape in low mass direction 

    """

    global sstep
    
    CBpar = [0.0]*5
    if m < shape_parlist[0][0]:
        ipos = i_relative
        if ipos < 0:
            ipos = 0
        CBpar = shape_parlist[ipos][1:]
    elif m > shape_parlist[Nsigsam-1][0]:
        ipos = Nsigsam-1-i_relative
        if ipos > Nsigsam-1:
            ipos = Nsigsam-1
        CBpar = shape_parlist[ipos][1:]
    else:
        nbins=int(round((m-shape_parlist[0][0])/sstep))
        ipos = nbins + i_relative
        if ipos < 0:
            ipos = 0
        elif ipos > Nsigsam-1:
            ipos = Nsigsam-1
        CBpar = shape_parlist[ipos][1:]        
    return CBpar


def multifit(mstart,mend,nstep):
    """"
    do multiple fitting in a specified range
    """

    global halfwidth

    binwidth = (mend-mstart)/(nstep-1)
    all_ul = dict()
    if opt_fit[0] == 1:
        halfwidth = 0.15
    elif opt_fit[0] == -1:
        halfwidth = 0.05

    
    for x in frange(mstart,mend,nstep):
        if optp: 
            print "frange... ", x
            print "frange... ", x-0.5*binwidth,x+0.5*binwidth
        if iflag == 3:
            CBpar = getShape(x, shape_par, opt_fit[1])    
            all_ul[x] = fitMass([x-halfwidth,x+halfwidth], iflag, opt_fit[2] , CBpar)
        else:
            pass
    return all_ul


def getul_br(x, ul_nsig, delta_sys = 0):
    Njpsi = 1086.9e6
    eNjpsi = 6.0e6
    eff = getShape(x, shape_par, 0)[3]        
    ul_br = ul_nsig/(Njpsi*eff*(1-delta_sys))
    return ul_br


#### please put all global var together here
## options for plots and verboses: 0, 1, 2
optp = 0

## please put CB parameters here in the format
## cbsigma, n1, alpha
CBpar=[0.00626, 1.178, 1.260,1.0]

## flag to indicate signal pdf used
## 1: gauss 2: single CB  3: step-wise CB
iflag = 3
halfwidth = 0.1
mstart = 0.4
mend = 2.0
nstep = 3

#	
binwidth = (mend-mstart)/(nstep-1)
hUL = TH1F("hUL","hUL", nstep, mstart-0.5*binwidth, mend+0.5*binwidth)
hUL_BR = TH1F("hUL_BR","hUL_BR", nstep, mstart-0.5*binwidth, mend+0.5*binwidth)
hUL.SetTitle(";mee(GeV); nsignal UL(90%CL)")
hUL_BR.SetTitle(";mee(GeV); BR UL(90%CL)")

if iflag == 3:
    sig_par = ROOT.TChain("siginfo")
    #	sig_par.Add("outsig.root")
    Nsigsam=14
    sstep = 0.1
    sig_array = [0]*Nsigsam
    cbsiginfo = open("cbinfo.txt","r")
    temp_sigsam = 0
    for read_line in cbsiginfo.readlines():
        sig_array[temp_sigsam] =read_line.split(" ")
        temp_sigsam=temp_sigsam+1
    cbsiginfo.close()
else:
    pass


shape_par = [map(float, sig_array[i]) for i in xrange(Nsigsam)]




# ## now do the different fitting optionsn  
# ## opt_fit_in = "abc": a,b,c are all signed digits. default is "+0+0+0""
# a: fiting range,  = 1 (+-150MeV) -1 (+-50MeV)
# b: signal shape, = 1 (next closest shape higher) -1(next closest shape lower)
# c: bkg shape, = 1 (+1 order polynomial)
## should use like ""000 001 010 100", note it has to be string

## flag to control automatic fitting with all options, 0: manual
auto = 1 

## switch to control whether N_UL and BR_UL calculated together
## 1: N 2: BR 3: N+BR 
calc_switch = 3 

if calc_switch & 1:
    if auto == 0:
    ## this part is for manual operation
        opt_fit_in = "+0+0+0"
        opt_fit = [int(opt_fit_in[j:j+2]) for j in range(0,len(opt_fit_in),2)]
        ul_sig = multifit(mstart, mend, nstep)
    else:
    ## this part is for automatic 
        allopt = ["+0+0+0","+0+0+1","+0+1+0","+0-1+0","+1+0+0","-1+0+0" ]
        grandall_ul = dict()
        for this_fit in allopt:
            opt_fit = [int(this_fit[j:j+2]) for j in range(0,len(this_fit),2)]
            vdict = multifit(mstart, mend, nstep)
            vkeys = vdict.keys()
            vkeys.sort()
            grandall_ul[this_fit] = map(vdict.get, vkeys)
        vmap = zip(*grandall_ul.values())
        ul_sig = dict(zip(vkeys, map(max, vmap)))
        if optp: print grandall_ul



if optp: print ul_sig
json.dump(ul_sig, open("ulnsig.dict","w"))

if calc_switch == 2: 
    ul_sig  = json.load(open("ulnsig.dict"))

ibin=1
delta_sys= 0.1
for x in frange(mstart,mend,nstep):
    if calc_switch & 1:
        hUL.SetBinContent(ibin, ul_sig[x])
    if calc_switch & 2: 
        this_br = getul_br(x, ul_sig[x],delta_sys)
        hUL_BR.SetBinContent(ibin, this_br)
    ibin += 1

if calc_switch & 1:
    hUL.Draw()
    myc.Print("hul_nsig.png")
    hUL.SaveAs("hul_nsig.root")
    raw_input()

if calc_switch & 2:
    hUL_BR.Draw()
    myc.Print("hul_br.png")
    hUL_BR.SaveAs("hul_br.root")
    raw_input()


