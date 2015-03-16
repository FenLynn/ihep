from ROOT import *
import ROOT
import sys
import os
import string

# CMS Style
if os.path.isfile('tdrstyle.C'):
	gROOT.ProcessLine('.L tdrstyle.C')
	ROOT.setTDRStyle()
	print "Found tdrstyle.C file, using this style."
	HasCMSStyle = True
	if os.path.isfile('CMSTopStyle.cc'):
		gROOT.ProcessLine('.L CMSTopStyle.cc+')
		style = CMSTopStyle()
		style.setupICHEPv1()
		print "Found CMSTopStyle.cc file, use TOP style if requested in xml file."

# for LHEF type
# gSystem.Load("../ExRootAnalysis/lib/libExRootAnalysis.so")
gROOT.ProcessLine('.L ../ExRootAnalysis/lib/libExRootAnalysis.so')

gROOT.SetBatch() # True if session without graphics
#dirname = "ben_small_0414/" 	#	--Jing Li @ 2014-04-14	
dirname = ""
filename = {}
filename["CP=0^{+}"] = dirname + "ben_small_0414/WHiggs0P_M-125p6_8TeV-JHUGenV4-private_0.root" #		--Jing Li @ 2014-04-14	
filename["CP=0^{+}, Higher Order"] = dirname + "ben_small_0414/WHiggs0PH_M-125p6_8TeV-JHUGenV4-private_0.root"
filename["CP=0^{-}"] = dirname + "ben_small_0414/WHiggs0M_M-125p6_8TeV-JHUGenV4-private_0.root"
filename["CP mixed 50-50"] = dirname + "ben_small_0414/WHiggs0Mf05ph0_M-125p6_8TeV-JHUGenV4-private_0.root"

# 		--Jing Li @ 2014-04-15	
filename["MadGraph_ZH_SM"] = dirname + "Mad_SM_test0415/unweighted_events_MadGraph.root"
filename["JHUGenerator_ZH_SM"] = dirname +"test_ZH_20140414/ZHiggs0P_M-125p6_8TeV-JHUGenV4-jing-0414.root"

filename1 = sys.argv[1] # 'tree filename 1'
file1 = TFile(filename[filename1])

filename2 = sys.argv[2] # 'tree filename 2'
file2 = TFile(filename[filename2])

variablename = sys.argv[3]
print variablename
cutname = sys.argv[4]
print cutname
weightname1 = sys.argv[5]
print weightname1
weightname2 = sys.argv[6]
print weightname2

index1 = int(sys.argv[7])
print index1
bin_ = int(sys.argv[8])
print bin_
min_ = float(sys.argv[9])
print min_
max_ = float(sys.argv[10])
print max_

xtitle = sys.argv[11]
print xtitle

additionname = sys.argv[12]
print additionname

#dir = 'Plot_ben_small_2014_04_14/'
#dir = 'Plot_JHU_MadGraph_20140415/' # 		--Jing Li @ 2014-04-15	
dir = 'Plot_JHU_MadGraph_lepton_20140415/'

hcompare = {}

file1.cd()
#obj1 = file1.Get("tree") 	#	--Jing Li @ 2014-04-14	
obj1 = file1.Get("LHEF") 	#	--Jing Li @ 2014-04-15
# ??? weight ???
if weightname2 == "noweight":
	obj1.Draw("%s[%d]>>h1(%d,%f,%f)"%(variablename,index1,bin_,min_,max_),"((%s)*(%s))"%(weightname1,cutname),"goff")
elif weightname2 == "noindex":
   obj1.Draw("%s>>h1(%d,%f,%f)"%(variablename,bin_,min_,max_),"((%s) * (%s))"%(weightname1,cutname),"goff")
else:
   obj1.Draw("%s[%d]>>h1(%d,%f,%f)"%(variablename,index1,bin_,min_,max_),"((%s * %s) * (%s))"%(weightname1,weightname2,cutname),"goff")

hcompare[filename1] = getattr(ROOT,"h1").Clone(filename1)
hcompare[filename1].SetName(filename1)
hcompare[filename1].Sumw2()
hcompare[filename1].SetTitle(filename1)
hcompare[filename1].GetXaxis().SetTitle(xtitle)
hcompare[filename1].GetYaxis().SetTitle("Unit Area")
print hcompare[filename1].GetTitle()
print str(hcompare[filename1].GetNbinsX())
print str(hcompare[filename1].GetEntries())

file2.cd()
#obj2 = file2.Get("tree") # 		--Jing Li @ 2014-04-14	
obj2 = file2.Get("LHEF") # 		--Jing Li @ 2014-04-15	
if weightname2 == "noweight":
   obj2.Draw('%s[%d]>>h2(%d,%f,%f)'%(variablename,index1,bin_,min_,max_),'((%s) * (%s))'%(weightname1,cutname),"goff")
elif weightname2 == "noindex":
   obj2.Draw("%s>>h2(%d,%f,%f)"%(variablename,bin_,min_,max_),"((%s) * (%s))"%(weightname1,cutname),"goff")
else:
   obj2.Draw("%s[%d]>>h2(%d,%f,%f)"%(variablename,index1,bin_,min_,max_),"((%s * %s) * (%s))"%(weightname1,weightname2,cutname),"goff")

hcompare[filename2] = getattr(ROOT,"h2").Clone(filename2)
hcompare[filename2].SetName(filename2)
hcompare[filename2].Sumw2()
hcompare[filename2].SetTitle(filename2)
hcompare[filename2].GetXaxis().SetTitle(xtitle)
hcompare[filename2].GetYaxis().SetTitle("Unit Area")
print hcompare[filename2].GetTitle()
print str(hcompare[filename2].GetEntries())

c1 = TCanvas("cbb","cbb",10,10,1000,700)

hcompare[filename1].SetLineColor(2)
hcompare[filename2].SetLineColor(1)
#hcompare[filename1].SetMarkerColor(2)
#hcompare[filename2].SetMarkerColor(1)
#hcompare[filename1].SetMarkerStyle(2)
#hcompare[filename2].SetMarkerStyle(2)

eventnumber = {}
eventnumber[filename1] = float(hcompare[filename1].Integral(0,hcompare[filename1].GetNbinsX() + 1))
eventnumber[filename2] = float(hcompare[filename2].Integral(0,hcompare[filename2].GetNbinsX() + 1))
hcompare[filename1].Scale(1.0/eventnumber[filename1])
hcompare[filename2].Scale(1.0/eventnumber[filename2])
if hcompare[filename1].GetMaximum() > hcompare[filename2].GetMaximum():
   hcompare[filename1].DrawNormalized("hist")
   hcompare[filename2].DrawNormalized("histsame")
if hcompare[filename1].GetMaximum() < hcompare[filename2].GetMaximum():
   hcompare[filename2].DrawNormalized("hist")
   hcompare[filename1].DrawNormalized("histsame")

aleg = TLegend(0.70,0.77,0.93,0.93)  
SetOwnership( aleg, 0 )
#aleg.SetHeader("#splitline{CMS 2012 Simulation}{"+ filename1 + " " + filename2 +"}")
#aleg.SetHeader("#splitline{" + filename1 + "}{" + filename2 +"}")
#aleg.SetHeader("CMS 2012 Simulation")
#aleg.SetMargin(0.12)
aleg.SetMargin(0.10)
aleg.SetTextSize(0.035)
#aleg.SetTextSize(0.023) # eta
aleg.SetFillColor(0)
aleg.SetFillStyle(0)
aleg.SetBorderSize(0)

aleg.AddEntry(hcompare[filename1],filename1,"L")
aleg.AddEntry(hcompare[filename2],filename2,"L")
aleg.Draw()

# string.replace(s, old, new[, maxreplace])
variablename = string.replace(variablename,">","large")
variablename = string.replace(variablename,"=","euqal")
variablename = string.replace(variablename,"<","small")
variablename = string.replace(variablename,"?","_")
variablename = string.replace(variablename,":","_")
variablename = string.replace(variablename,"(","")
variablename = string.replace(variablename,")","")
variablename = string.replace(variablename,"*","")
variablename = string.replace(variablename,"+","")

cbb.Print(dir + filename1 + "_" + filename2 +"_"+ variablename + "_" + additionname +".png") 
cbb.Print(dir + filename1 + "_" + filename2 +"_"+ variablename + "_" + additionname +".pdf") 
cbb.Print(dir + filename1 + "_" + filename2 +"_"+ variablename + "_" + additionname +".eps")

raw_input ("Enter to quit:")
