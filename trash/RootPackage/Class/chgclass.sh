#!/bin/bash
#
#===============================================================================
#   FILENAME:         makeClass.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年11月25日 00时44分13秒 CST
#   DESCRIPTION: 
#===============================================================================

####################################################NoTICE#######################################################
#There have problems hard to sovle in this script.
#Provided that you have Sigmc.C and Sigmc.h,do not execute ./chgclass.sh with the file having been execute
#./chgclass. it means that the script has better to  execute with the original file from root MakeClass.
#################################################################################################################


#********************************ROOT TYPE to change**************************************************************
#For signal MC
#CLASSHEAD="Sigmc.h"
#For Inclusive MC
CLASSHEAD="Inmc.h"
#For Data
#CLASSHEAD="Data.h"

ROOTTYPE=$(echo ${CLASSHEAD} | cut -f 1 -d ".")
CLASSCXX="${ROOTTYPE}.C"

#*****************************************************************************************************************


#********************************switch varable*******************************************************************
#set 1 to change the *.h file
ADDHEAD=0
#set 1 to change the *.C file
ADDCXX=1

if [ $(grep -c "ClassHelper.h" ${CLASSHEAD}) -lt 1 ];then
	sed -i -e '10a\#include "../Include/ClassHelper.h"' ${CLASSHEAD}
fi

#if [ $(grep -c "TClonesArray.h" ${CLASSCXX}) -lt 1 ];then
#	sed -i -e '10a\#include <TClonesArray.h>' ${CLASSHEAD}
#fi
#********************************cut function*********************************************************************
function cut(){
	echo -e "\t//***************This is a selection for unti-$1******************" >> ${CLASSHEAD}
	echo -ne '\t//' >> ${CLASSHEAD}
	echo -ne "if ($1)  {" >> ${CLASSHEAD}
	echo -e "return -1;}" >> ${CLASSHEAD}

}

#********************************modify header*********************************************************************
if [ ${ADDHEAD} -eq 1 ];then
	TMPHEAD="tmp_headfile"
	#This is to cut the last 3 lines offi
	if [ $(grep -c "#endif // #ifdef" ${CLASSHEAD}) -gt 0 ];then
		touch ${TMPHEAD}
		tac ${CLASSHEAD} > ${TMPHEAD}
		sed -i -e '1,3d' ${TMPHEAD} 
		tac  ${TMPHEAD} > ${CLASSHEAD}
	fi
	rm -rf ${TMPHEAD}
	#end here

	if [ $(grep -c "parameter_1" ${CLASSHEAD}) -lt 1 ];then
		#************************add cut below*********************************************************************
		#if you don't wanto to make cuts in class,you don't need to concern this and it was noted originally.
		cut "parmeter_1<5"
		cut "parmeter_2>2"
		#************************add cut above*********************************************************************
	fi
	
	echo -e "\treturn 1;\n}" >> ${CLASSHEAD}
	sed -e "s/ROOTTYPE/${ROOTTYPE}/g" ../Template/MyClassExternal.C >> ${CLASSHEAD} 
	echo -e '#endif // #ifdef Sigmc_cxx' >> ${CLASSHEAD}
fi


#********************************modify source*********************************************************************

if [ ${ADDCXX} -eq 1 ];then
	if [ $(grep -c "CloneTree(0)" ${CLASSCXX}) -lt 1 ];then
		sed -i -e '/GetEntriesFast/a\	TTree* newTree=(TTree*)fChain->CloneTree(0); ' ${CLASSCXX}
		sed -i -e '/GetEntriesFast/a\	TFile* fout=new TFile("./Dataout.root","RECREATE"); ' ${CLASSCXX}
	fi

	sed -i -e '38,45s/\/\///' ${CLASSCXX}
	if [ $(grep -c "newTree->Fill()" ${CLASSCXX}) -lt 1 ];then
		sed -i -e 's/}//g' ${CLASSCXX}
	fi
	#sed -i -e '//a\ newTree->AutoSave();' ${CLASSCXX}
	if [ $(grep -c "newTree->Fill()" ${CLASSCXX}) -lt 1 ];then
		echo -e "\t\tnewTree->Fill();" >> ${CLASSCXX}
		echo -e "\t}" >> ${CLASSCXX}
		echo -e "\tnewTree->AutoSave();\n\tdelete fout;" >> ${CLASSCXX}
		echo "}" >> ${CLASSCXX}
	fi
fi
