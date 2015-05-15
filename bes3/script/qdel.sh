#!/bin/bash
#
#===============================================================================
#   FILENAME:         qdel.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年09月01日 14时29分33秒 CST
#   DESCRIPTION: 
#===============================================================================

# set as "1" for delete all your job, "0" for the job id you choose
DELALL=1

#set for your job id,begin & end
#if DELALL is 1,no need to set
STARTID=18996374
ENDID=18996378

if [ $DELALL -ne 1 ]; then
	TMPNUM=${STARTID}
	for((i=${STARTID};i<${ENDID}+1;i++))
	do
		qdel ${TMPNUM}
		TMPNUM=$((i+1))
	done
else
	qstat |grep lify | awk '{print "qdel " $1 }' > qdel_myjob_.sh
	source qdel_myjob_.sh
	rm -rf qdel_myjob_.sh
fi

echo 'All done!'

