#!/bes/besd09/zhuk/local/bin/python3.1
#!/usr/bin/python
import os,sys,string, math, time
##
partex={
     "-22"   :  '\gamma_{FSR} ',
      "22"   :  '\gamma       ',
      "11"   :  'e^{+}        ',
     "-11"   :  'e^{-}        ',
      "13"   :  '\mu^{+}      ',
     "-13"   :  '\mu^{-}      ',
      "15"   :  '\\tau^{+}    ',
     "-15"   :  '\\tau^{-}    ',
      "12"   :  '\\nu_{e}           ',
     "-12"   :  '\\bar{\\nu}_{e}    ',
      "14"   :  '\\nu_{\mu}         ',
     "-14"   :  '\\bar{\\nu}_{\mu}  ',
      "16"   :  '\\nu_{\\tau}       ',
     "-16"   :  '\\bar{\\nu}_{\\tau}',
#
      "111"  :  '\pi^{0}        ',
      "211"  :  '\pi^{+}        ',
     "-211"  :  '\pi^{-}        ',
      "113"  :  '\\rho^{0}      ',
      "213"  :  '\\rho^{+}      ',
     "-213"  :  '\\rho^{-}      ',
    "10111"  :  'a_{0}^{0}      ',
    "10211"  :  'a_{0}^{+}      ',
   "-10211"  :  'a_{0}^{-}      ',
   "100111"  :  '\pi(1300)^{0}  ',
   "100211"  :  '\pi(1300)^{+}  ',
  "-100211"  :  '\pi(1300)^{-}  ',
    "20113"  :  'a_{1}^{0}      ',
    "20213"  :  'a_{1}^{+}      ',
   "-20213"  :  'a_{1}^{-}      ',
   "100113"  :  '\\rho^{0}(1450)',
   "100213"  :  '\\rho^{+}(1450)',
  "-100213"  :  '\\rho^{-}(1450)',
  "9000113"  :  '\pi_1(1600)^0  ',
  "9000213"  :  '\pi_1(1600)^+  ',
 "-9000213"  :  '\pi_1(1600)^-  ',
      "115"  :  'a_{2}^{0}      ',
      "215"  :  'a_{2}^{+}      ',
     "-215"  :  'a_{2}^{-}      ',
    "10113"  :  'b_{1}^{0}      ',
    "10213"  :  'b_{1}^{+}      ',
   "-10213"  :  'b_{1}^{-}      ',
#      
      "221"  :  '\\eta          ',
      "331"  :  '\\eta^{\prime} ',
  "9000221"  :  'f_{0}(600)     ',
    "10222"  :  '\\sigma_{0}    ',
  "9010221"  :  'f_{0}(980)     ',
   "100221"  :  '\\eta(1295)    ',
    "10221"  :  'f_{0}(1370)    ',
  "9020221"  :  '\\eta(1405)    ',
   "100331"  :  '\\eta(1475)    ',
    "50221"  :  'f_{0}(1500)    ',
  "9000223"  :  'f_{1}(1510)    ',
    "10331"  :  'f_{0}(1710)    ',
  "9040221"  :  '\\eta(1760)    ',
  "8888888"  :  'f_{0}(1790)    ',
  "9999999"  :  'X(1835)        ',
    "10335"  :  '\\eta_2(1870)  ',
  "9050225"  :  'f_{2}(1950)    ',
  "9050221"  :  'f_{0}(2020)    ',
  "9060221"  :  'f_{0}(2100)    ',
  "9070221"  :  'f_{0}(2200)    ',
  "9080221"  :  '\\eta(2250)    ',
      "223"  :  '\omega         ',
      "333"  :  '\phi           ',
      "335"  :  'f_2^{\'}       ',
    "10223"  :  'h_{1}(1170)    ',
    "20223"  :  'f_{1}(1285)    ',
    "10333"  :  'h_{1}(1380)    ',
    "20333"  :  'f_{1}(1420)    ',
   "100223"  :  '\omega(1420)   ',
      "225"  :  'f_{2}(1270)    ',
      "229"  :  'f_{4}(2050)    ',
      "313"  :  'K^{*0}         ',
    "10221"  :  'f^{\'}_{0}     ',
#
      "311"  :  'K^{0}          ',
     "-311"  :  '\\bar{K}^{0}   ',
      "321"  :  'K^{+}          ',
     "-321"  :  'K^{-}          ',
      "313"  :  'K^{*}          ',
     "-313"  :  '\\bar{K}^{*}   ',
    "10313"  :  'K_1^{0}        ',
   "-10313"  :  '\\bar{K}_1^{0} ',
    "10323"  :  'K_1^{+}        ',
   "-10323"  :  'K_1^{-}        ',
    "10311"  :  'K_0^{0}        ',
   "-10311"  :  '\\bar{K}_0^{*0}',
   "-100313"  :  '\\bar{K}^{\'*0} ',
   "100313"  :  'K^{\'*0}       ',
    "20313"  :  'K_1^{\'0}      ',
   "-20313"  :  '\\bar{K}_1^{\'0}',
    "20323"  :  'K_1^{\'+}      ',
   "-20323"  :  '\\bar{K}_1^{\'-}',
      "310"  :  'K_{S}          ',
      "130"  :  'K_{L}          ',
      "323"  :  'K^{*+}         ',
     "-323"  :  'K^{*-}         ',
      "325"  :  'K_2^{*+}       ',
     "-325"  :  'K_2^{*-}       ',
      "315"  :  'K_2^{*0}       ',
     "-315"  :  'K_2^{*0}       ',
    "10321"  :  'K_{0}^{*+}     ',
   "-10321"  :  'K_{0}^{*-}     ',
   "-10323"  :  'K_{1}^{-}      ',
    "10315"  :  'K_2^0(1770)    ',
   "-10315"  :  '\\bar{K}_2^0(1770)',
    "10325"  :  'K_2^+(1770)    ',
   "-10325"  :  'K_2^-(1770)    ',
    "20315"  :  'K_2^0(1820)    ',
   "-20315"  :  '\\bar{K}_2^0(1820)',
    "20325"  :  'K_2^+(1820)    ',
   "-20325"  :  'K_2^-(1820)    ',
#
      "2212" :  'p                 ',
     "-2212" :  '\\bar{p}          ',
      "2112" :  'n                 ',
     "-2112" :  '\\bar{n}          ',
      "1114" :  '\Delta^-          ',
     "-1114" :  '\\bar{\Delta}^-   ',
      "2114" :  '\Delta^0          ',
     "-2114" :  '\\bar{\Delta}^0   ',
      "2214" :  '\Delta^+          ',
     "-2214" :  '\\bar{\Delta}^+   ',
      "2224" :  '\Delta^{++}       ',
     "-2224" :  '\\bar{\Delta}^{++}',
      "3122" :  '\Lambda           ',
     "-3122" :  '\\bar{\Lambda}    ',
      "3222" :  '\Sigma^+          ',
     "-3222" :  '\\bar{\Sigma}^-   ',
      "3212" :  '\Sigma^0          ',
     "-3212" :  '\\bar{\Sigma}^0   ',
      "3112" :  '\Sigma^-          ',
     "-3112" :  '\\bar{\Sigma}^+   ',
      "3224" :  '\Sigma^{*+}       ',
     "-3224" :  '\\bar{\Sigma}^{*-}',
      "3214" :  '\Sigma^{*0}       ',
     "-3214" :  '\\bar{\Sigma}^{*0}',
      "3114" :  '\Sigma^{*-}       ',
     "-3114" :  '\\bar{\Sigma}^{*+}',
      "3322" :  '\Xi^0             ',
     "-3322" :  '\\bar{\Xi}^0      ',
      "3312" :  '\Xi^-             ',
     "-3312" :  '\\bar{\Xi}^+      ',
      "3324" :  '\Xi^{*0}          ',
     "-3324" :  '\\bar{\Xi}^{*0}   ',
      "3314" :  '\Xi^{*-}          ',
     "-3314" :  '\\bar{\Xi}^{*+}   ',
      "3334" :  '\Omega^-          ',
     "-3334" :  '\\bar{\Omega}^+   ',
#
    "9030443":  '  ',
        "441":  '\eta_{c}    ',
        "443":  'J/\psi      ',
        "411":  'D^{+}       ',
        "-411": 'D^{-}       ',
        "421":  'D_{0}       ',
        "-421": '\\bar{D_{0}}  ',
        "413":  'D^{*+}      ',
        "-413": 'D^{*-}      ',
        "423":  'D^{*0}      ',
        "-423": '\\bar{D^{*0}} ',
        "431":  'D_{s}^{+}    ',
        "-431": 'D_{s}^{-}    ',
        "433":  'D_{s}^{*+}    ',
        "-433": 'D_{s}^{*-}    ',
        "-30213": '\rho(2S)-    ',
        "30213": '\rho(2S)+    ',
        "30113": '\rho(2S)0    ',
      "10441":  '\chi_{c0}   ',
      "20443":  '\chi_{c1}   ',
        "445":  '\chi_{c2}   ',
      "10443":  'h_{c}       ',
      "10441":  '\eta_{c}(2S)',
     "100443":  '\psi^\prime ',
}
##
def process(event):
    global fdict, flist, fnumb, fchan, nevt, itop, itot, lined, ichan,cutnum,cutlines
    number = []
    pdgid  = []
    mother = []
    lined=''
    for ii in event:
        if ii.find("Event listing") != -1:
           continue
        if ii.find("particle/jet")  != -1:
           continue
        parts = ii.split()
        #if parts[2] == '-22' :
        #   continue
        #print ii[:-1]
        number.append(parts[0])
        pdgid .append(parts[2])
        mother.append(parts[3])
    #print len(number),len(pdgid),len(mother)
    #if pdgid.count('10443') != 0 or nevt <=1:
    #   return ''
    i=0
    linel=[]
    while i<100:  
       i+=1
       linel.append([]) 
    i=0
    line0=[]
    while (i<len(number)):
        # skip all FSR photons for sake of simplicity
        if pdgid[i] == '-22' :
           i+=1
           continue
        # recording only final state particles and pi0s 
        if number.count(mother[i]) >= 1 : # be a daugther of anyone
           if (mother.count(number[i])==0 or pdgid[i] == '111'): # has no daugther/final state or is pi0
              if pdgid[int(mother[i])] != '111': # mother is not pi0
                 line0.append(pdgid[i])
        # for whole decay chain except pi0 decay
        if mother.count(number[i]) > 1 :  # has daughers/be a mother
           linel[i].append(pdgid[i])
           j=0
           while (j<len(number)):
              if mother[j] == number[i]:
                 linel[i].append(pdgid[j])
              j+=1
        i+=1
    #print "*"*40
    line0.sort()
    #print line0
    
    i=0
    linep=[]
    while i<100: 
       i+=1
       linep.append('') 
    i=0
    while (i<len(linel)):
         ij=linel[i]
         id=0
         if len(ij)>1 and ij[0] != '111':
            for ii in ij:
               if id==0:
                 linep[i]+= (partex[ii]+" \\rightarrow ")
                 id=1
               else:
                 linep[i]+= (partex[ii])

            linep[i]="%s, "%(linep[i])
            #print linep[i]
            lined+=linep[i]
         i+=1
    #print lined
    local="%3i&$%s$&%5i&%5i\\\\\n"%(ichan,lined[:-2], itop, nevt)
    pline=''
    for ii in line0:
       pline+=partex[ii]
    lined="%3i&$%s$&$%s$&%5i&%5i&%5i\\\\\n"%(ichan,lined[:-2],pline, itop,nevt,itot)
    qline='\psi^\prime\\rightarrow '+pline
    qline="%3i&$%200.200s$ & %5i & %5i & %i\\\\\n"%(ichan, qline, itop, nevt, itot)
    if nevt <= cutnum:
       qline='%'+qline
       lined='%'+lined
       local='%'+local
    #       
    ichan+=1
    if pline in fdict :
       fnumb[pline]=fnumb[pline] + nevt
       fchan[pline]=fchan[pline] + 1 
       if fchan[pline] < cutlines:
          fdict[pline]=fdict[pline]+local
    else:
       #print fdict[pline]
       fdict[pline]=local
       fnumb[pline]=nevt 
       fchan[pline]=1 
    #print qline 
    if nevt <= cutnum:
       return ''
    return qline        
##
cutnum   =  0
cutlines = 30
if len(sys.argv)>1:
   cutnum   = int(sys.argv[1])
if len(sys.argv)>2:
   cutlines = int(sys.argv[2])
#print 'number of mode greater than : ', cutnum
#print 'number of line for the table: ', cutlines
##
infile= open('mclist.txt',"r")
list = infile.readlines()
infile.close()
#
infile= open('init/head.tex',"r")
head = infile.readlines()
infile.close()
#
infile= open('init/tail.tex',"r")
tail = infile.readlines()
infile.close()
#
infile= open('init/tab_head.tex',"r")
tab_head = infile.readlines()
infile.close()
#
infile= open('init/sum_head.tex',"r")
sum_head = infile.readlines()
infile.close()
#
infile= open('init/tab_tail.tex',"r")
tab_tail = infile.readlines()
infile.close()
#
#
#
itot =0
fdict={}
flist=[]
fchan={}
fnumb={}
event=[]
lined=''
imode=0
ichan=0
file1='output/mclist_'+"%4.4i"%(imode/cutlines)
f= open(file1+'.tex',"w")
f.writelines(tab_head)
h= open('notice.tex',"w")
h.writelines(head)
h.write("\\tableofcontents\n\\newpage\n")
h.write("\\section{Modes list in decreasing order}\n")
h.write("\n\\subsection{Decay modes }\n")
for ii in list:
    if len(ii)< 5:
       continue
    if ii.find("the topology") != -1:
       continue
    if ii.find("the total topology")  != -1:
       continue
    if ii.find("topology:") != -1:
       if event != []:
          line=process(event)
          if line!='':
             imode+=1
             if lined !='':
                f.write(lined)
          event=[]
       if imode%cutlines==0:
          if imode != 0:
             f.writelines(tab_tail)
             f.close()
             print ('%5i %s'%(imode, file1))
             h.write('\\begin{landscape} '+'\include{'+file1+'} '+'\\end{landscape} \\clearpage \n')
          file1='output/mclist_'+"%4.4i"%(imode/cutlines)
          f= open(file1+'.tex',"w")
          f.writelines(tab_head)
#
       ipos = ii.find("topology:")
       itop = int(ii[ipos+9 :ipos+20])
       ipos = ii.find("Events:")
       nevt = int(ii[ipos+8:])
       itot+=nevt 
       #print ii[:-1], itop, nevt
    else:
       event.append(ii)
line=process(event)
if line!='':
   if lined !='':
      f.write(lined)
f.writelines(tab_tail)
print ("%5i %s"%(imode, file1))
h.write('\\begin{landscape} '+'\include{'+file1+'} '+'\\end{landscape} \\clearpage  \n')
f.close()
h.write("\n\\subsection{Total number of events is "+str(itot)+"}\n")
#
h.write("\n\\setcounter{table}{0}\n")
h.write("\n\\section{Modes rearanged by types of final states}\n")
h.write("\n\\subsection{ Types of final states }\n")
fnumb=sorted(fnumb.items(), key = lambda fnumb:fnumb[1], reverse=True)
f = open('output/summary.tex',"w")
for k in fnumb:
    if k[0] in fdict :
       f.writelines(sum_head)
       f.write( '\multicolumn{3}{c}{$' + k[0] + '$}\\\\\\hline \n')
       f.write( fdict[k[0]] )
       f.write( '\\hline\multicolumn{3}{c}{' + str(k[1])+' evts (' + str(fchan[k[0]]) +' modes )' + '}\\\\\\hline ')
       f.writelines(tab_tail)
       f.write('\\clearpage\n')
h.write('\\begin{landscape} '+'\include{output/summary} '+'\\end{landscape} \\clearpage\n')
h.write("\n\\subsection{ Total number of types of final states "+str(len(fnumb))+"}\n")
#
h.writelines(tail)
h.close()
