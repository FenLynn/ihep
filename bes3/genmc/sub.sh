#!/bin/bash
#while read MY_LINE
#do

DECAYNAME=""
MAKECLEAN=1
CLEANNAME="clean.sh"

TMP_MYNUM=100
MYNUM=100

if [ ${MAKECLEAN} -eq 1 ]
then	
	if [ -f ${CLEANNAME} ]
	then
		rm ${CLEANNAME}
	fi

	touch ${CLEANNAME}
	echo "#!/bin/bash" > ${CLEANNAME}
	echo "rm -rf fort.*" >> ${CLEANNAME}
	echo "rm -rf sim${DECAYNAME}_*.txt" >> ${CLEANNAME}
	echo "rm -rf rec${DECAYNAME}_*.txt" >> ${CLEANNAME}
	echo "rm -rf sub_*.txt" >> ${CLEANNAME}
	echo "rm -rf sub_*.txt.*" >> ${CLEANNAME}
	chmod 755 ${CLEANNAME}
fi

#for((i=0;i<1;i++))
for((i=0;i<200;i++))
do
	TMP_MYNUM=$((i+10001))
	MYNUM=`echo $TMP_MYNUM|cut -c 3-6`
	echo $MYNUM
	echo "#!/bin/bash" > sub_$MYNUM.txt
	echo "source ~/set664p01.sh" >> sub_$MYNUM.txt
	echo -e "\ncd $(pwd -P)\n" >> sub_$MYNUM.txt
	sed "s/NUM/$MYNUM/g;" jobOptions_sim.txt > sim${DECAYNAME}_$MYNUM.txt
	sed "s/NUM/$MYNUM/g;" jobOptions_rec.txt > rec${DECAYNAME}_$MYNUM.txt
	sed "s/NUM/$MYNUM/g;" qsub_Temp.sh >> sub_$MYNUM.txt
	qsub -q besq sub_$MYNUM.txt
done
#done < ModeFile
