#!/bin/bash
#code by Hao Xiqing, method from Zhang Lei
#mail haoxq@ihep.ac.cn
###################
#Chang Log
#creat in 2009-09-08 by Hao Xiqing
#test-version
####################
#

#some bariable to make scripts
MAKECLEANSCRIPT=1
CLEANSCRIPTNAME="clean.sh"

if [ ${MAKECLEANSCRIPT} -eq 1 ];then
	if [ -e $CLEANSCRIPTNAME ];then
		rm $CLEANSCRIPTNAME
	fi
	touch ${CLEANSCRIPTNAME}
	echo "#!/bin/bash">>${CLEANSCRIPTNAME}
	chmod 755 ${CLEANSCRIPTNAME}
fi



#variable only for script itself
MY_LINE_NO=0
MY_FILEE=100000
#MY_FILEE=101000

###variable user difine####################
#The number of data files you want to sub in one job.My_NUM cant't be 1.
MY_NUM=40
#The name of table of path of data file
DST_TABLE=gpipiee.txt
#The end line of the path table you want to stop. Zero means for all
#END=4
END=20

PROJECTNAME="GPiPiEE"

SUBWORKNAME="sub${PROJECTNAME}.txt"
OUTPATH="/besfs/groups/higgs/users/lify/664p01/root/etapee/gpipi/sig"

CPWD=$(pwd -P)

if [ ! -e $OUTPATH ];then
	echo "Outpath isn't exist!"
	mkdir -p ${OUTPATH}
fi


TOTAL=`cat $DST_TABLE|wc -l`
if [ $TOTAL -le $END ];then
    END=$TOTAL
fi
if [ $END == 0 ];then
    END=$TOTAL
fi

while read MY_LINE
do
#    MY_FILE=$((MY_FILE+1))
    MY_LINE_NO=$((MY_LINE_NO+1)) 

#for where to begin and end
    if [ $MY_LINE_NO -le $END ]; then

	if expr $MY_LINE_NO % $MY_NUM == 1 >/dev/null;then  
	    MY_FILEE=$((MY_FILEE+1))
	   # MY_FILE=`echo $MY_FILEE |cut -c 4-6`
	    MY_FILE=`echo $MY_FILEE |cut -c 4-6`
	    cat upper.txt>job_$MY_FILE.txt
	fi
	echo $MY_LINE>>job_$MY_FILE.txt
	if expr $MY_LINE_NO % $MY_NUM == 0 >/dev/null;then
	    echo $MY_LINE_NO
	elif [ $MY_LINE_NO -ne $END ];then
	    echo ",">>job_$MY_FILE.txt;
	fi
	if expr $MY_LINE_NO % $MY_NUM == 0 >/dev/null || expr $MY_LINE_NO == $END >/dev/null;then  
	    cat lower.txt>>job_$MY_FILE.txt
		sed "s/NUM/$MY_FILE/g" job_$MY_FILE.txt -i
#	    echo NTupleSvc.Output={\"FILE1 DATAFILE=\'${OUTPATH}\/tuple\/${PROJECTNAME}tuple${MY_FILE}.root\' OPT=\'NEW\' TYP=\'ROOT\'\"}\;>>job_$MY_FILE.txt;
	    echo ${PROJECTNAME}.OutputFileName=\"${OUTPATH}\/${PROJECTNAME}_${MY_FILE}.root\"\;>>job_$MY_FILE.txt;
		echo "job_$MY_FILE.txt done"
		
		#This to make subjob scripts
		####start from here
		if [ -e sub_$MY_FILE.txt ];then
			rm sub_$MY_FILE.txt
		fi
		touch "sub_$MY_FILE.txt"
		echo "#!/bin/bash">>sub_$MY_FILE.txt
		echo "source ~/set664p01.sh">>sub_$MY_FILE.txt
		echo "cd $CPWD" >> sub_$MY_FILE.txt
#		echo "boss.exe $(pwd -P)/job_$MY_FILE.txt">>sub_$MY_FILE.txt
		echo "boss.exe job_$MY_FILE.txt">>sub_$MY_FILE.txt
#		qsub -q higgsq sub_$MY_FILE.txt
#		qsub -q besq sub_$MY_FILE.txt
		####end of here
		if [ $MAKECLEANSCRIPT -a -e $CLEANSCRIPTNAME ];then
			echo "rm job_$MY_FILE.txt">>$CLEANSCRIPTNAME
			echo "rm sub_$MY_FILE.txt">>$CLEANSCRIPTNAME
			echo "rm -f sub_$MY_FILE.txt.o*">>$CLEANSCRIPTNAME
			echo "rm -f sub_$MY_FILE.txt.e*">>$CLEANSCRIPTNAME
		fi


#	sed "s/NUM/$MY_FILE/g;" qsub_Temp.sh > sub_$MY_FILE.txt
#	qsub -q publicq sub_$MY_FILE.txt
#	    bossslow -q job_$MY_FILE.txt
#		 boss -q job_$MY_FILE.txt
#    boss.exe job_$MY_FILE.txt &
	fi
    fi
done < $DST_TABLE
