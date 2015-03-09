#!/bin/bash
#
#===============================================================================
#   FILENAME:         makeCC.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年11月24日 14时53分08秒 CST
#   DESCRIPTION: 
#===============================================================================


#*********************************Global Variable**********************************************************
#script name to make
SCRIPTNAME="analysis.C"
#Whether Rewrite the script,1 for rewrite,0 will touch another file 
REWRITE=0

#no need to change
CUTSTATUS=0
COUNTERMULTIHIST=0

#**********************************Switch varable**********************************************************
#whether draw the hist plot on 1 canvas for every hist,1 will draw the hist after generate.
DRAWEVERYHIST=1

#********************************The generation script property********************************************
if [ ${REWRITE} -eq 0 ]
then
	for((scriptno=1;scriptno<20;scriptno++))
	do
		tmpscriptname=$(echo ${SCRIPTNAME}|sed "s/\./${scriptno}&/g")
		if [ -f "${tmpscriptname}" ];then
			continue
		else
			touch ${tmpscriptname}
			break
		fi
	done
	SCRIPTNAME=${tmpscriptname}
	echo "The current script file is ${SCRIPTNAME}!"
else
	rm -rf ${SCRIPTNAME}
	touch ${SCRIPTNAME}
fi
#**********************************************************************************************************


#********************************Cut Function**************************************************************
#Cut criteria set
function cut(){
	CUTSTATUS=1
	echo -e "\t\t//**************************This is a selection for $1*******************************************************" >> ${SCRIPTNAME}
	echo -e "\t\tif ( ${ROOTTYPE}->$1 ){" >> ${SCRIPTNAME}
	echo -ne "\t" >> ${SCRIPTNAME}
}
#**********************************************************************************************************

#********************************Single Draw***************************************************************
function singledraw(){
	ROOTTYPE=$2
	INPUTNAME=$1
	TEMP_HIST=${INPUTNAME#*\"}
	TEMP_HIST=${TEMP_HIST%\"*}
	HTEMP_HIST=h${ROOTTYPE}_${TEMP_HIST}
	sed "s/histname/${HTEMP_HIST}/g; s/branchname/${TEMP_HIST}/g; s/histpar/${DRAW[i]}/g; \
		s/rootfrom/${ROOTTYPE}/g" Template/MySingleDraw.C >> ${SCRIPTNAME}
	#*********************************************set cut below******************************************
	#cut "pneg>1.5"
	#*********************************************set cut up*********************************************
	echo -e "\t\t${HTEMP_HIST}->Fill(${ROOTTYPE}->${TEMP_HIST});" >> ${SCRIPTNAME}
	if [ ${CUTSTATUS} -eq 1 ];then
		echo -e "\t\t}" >> ${SCRIPTNAME}
	fi
	echo -e "\t}" >> ${SCRIPTNAME}

	if [ ${DRAWEVERYHIST} -eq 1 ]
	then
		echo -e "\tTCanvas* c${ROOTTYPE}_${TEMP_HIST} = new TCanvas(\"c${ROOTTYPE}_${TEMP_HIST}\",\"${ROOTTYPE}_${TEMP_HIST}\");" >> ${SCRIPTNAME}
		echo -e "\t${HTEMP_HIST}->Draw();" >> ${SCRIPTNAME}
	fi
	echo >> ${SCRIPTNAME}
}
#**********************************************************************************************************

#********************************Draw multiple histogram in one graph Function*****************************
#Draw two plot
function multidraw(){
	echo -e "\t//*****************************This is a comparision for $1 hists*******************************************" >> ${SCRIPTNAME}
	echo -e "\tTCanvas* cc${COUNTERMULTIHIST} = new TCanvas(\"cc${COUNTERMULTIHIST}\",\"cc${COUNTERMULTIHIST}\");" >> ${SCRIPTNAME}
	echo -e "\tTLegend* leg${COUNTERMULTIHIST} = new TLegend(.1,.78,.25,.9);" >> ${SCRIPTNAME}
	echo -e "" >> ${SCRIPTNAME}
	for((histno=2;histno<=(($1+1));histno++))
	do
		eval tmphist=\${$histno}
		eval tmphist_origin=\${$histno}
	
		#find where the histogram comes from
		if [ $(echo $tmphist | grep -c "sig") -ne 0 ];then
			histtype='Signal MC'
		elif [ $(echo $tmphist | grep -c "inm") -ne 0 ];then
			histtype='Inclusive MC'
		elif [ $(echo $tmphist | grep -c "dat") -ne 0 ];then
			histtype='Data'
		else
			histtype=$tmphist
		fi
		
		color_no=$((2*histno-2))
		style_no=$((histno+18))
			
		if [ $histno -eq 2 ];then
			draw_no=""
		else
			draw_no='"same"'
		fi

		
		sed -e "s/histname/${tmphist}/g; s/color_no/$color_no/g; s/draw_no/$draw_no/g; \
			s/legend/leg$COUNTERMULTIHIST/g; s/histtype_no/\"$histtype\"/g ;\
			s/style_no/${style_no}/g" Template/MyMultiDraw.C  >> ${SCRIPTNAME}
	done
	echo -e "\tleg${COUNTERMULTIHIST}->SetFillColor(0);" >> ${SCRIPTNAME}
	echo -e "\tleg${COUNTERMULTIHIST}->SetTextFont(42);" >> ${SCRIPTNAME}
	echo -e "\tleg${COUNTERMULTIHIST}->Draw(\"same\");" >> ${SCRIPTNAME}
}
#**********************************************************************************************************
echo "{" >> ${SCRIPTNAME}

cat Template/MyUpper.C>>${SCRIPTNAME}

#function singledraw format is required.First is your branch name,second is nbins,third is lower limit,
#fourth is higher limit,the last is your root type,optinal choice is sigmc/inmc/data.if you give a branch 
#name "example" from sigmc.then the default hist is "hsig_example",default canvase is "csig_example".

singledraw '"eneg",100,1.48,1.6' sig
singledraw '"pneg",100,1.48,1.6' inm


#first number is your hist number in one graph,then are coming the hist names.
multidraw 2 hinm_pneg hsig_eneg

echo "}" >> ${SCRIPTNAME}


########################################################################################################
#######################################    BACK UP    ##################################################
########################################################################################################

#tmphist=echo ${tmphist_origin} | cut -d - -f 1
#echo -e "\t${tmphist}->GetXaxis()->SetTitle(\"M(e^{-}) [GeV/c^{2}]\");" >> ${SCRIPTNAME}
#echo -e "\t${tmphist}->GetYaxis()->SetTitle(\"Events\");" >> ${SCRIPTNAME}
#echo -e "\t${tmphist}->SetLineColor($tmpcolor);" >> ${SCRIPTNAME}
#echo -e "\tleg${COUNTERMULTIHIST}->AddEntry(${tmphist},\"${histtype}\");" >> ${SCRIPTNAME}
# echo -e "$2->GetYaxis()->SetTitle("Events");" >> ${SCRIPTNAME}
# #echo $tmphist | grep -c "sig"
#for((i=0;i<${DRAWNO};i++))
#do
#done
