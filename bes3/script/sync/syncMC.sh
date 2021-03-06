#!/bin/bash
CPWD=$(pwd -P)
LOGTXT=~/script/sync/log.sync
BAKHOME=/besfs/groups/higgs/users/lify/genmc
DSTHOME=/workfs/bes/lify/genmc
foreachd(){
	#	echo $1
	for file in $1/* 
	do
		if [ -d $file ]
		then
			passdir=0
			bfile=$file
			temp_target=$( echo $file |  cut -d . -f 2-100)
			temp_target1=`basename $bfile`
			for pass in run CVS gcc
			do
				if [ $(echo $temp_target1 | grep -e ${pass}) ] ;then
					passdir=1
				fi
			done
			if [ $passdir -eq 1 ];then
				continue
			fi
			echo $temp_target1
			echo $temp_target
			mkdir -p $DSTDIR$temp_target
			foreachd $file
		elif [ -f $file ]
		then
			bfile=$file
			bbfile=`basename $bfile`
#			echo $bbfile
			passfile=0
#			for passf in sim_[0-9]\{1,3\}\.txt rec_[0-9]\{1,3\}\.txt sub_[0-9]\{1,3\}\.txt sub_[0-9]\{1,3\}\.txt\.[e,o]  fort\.
			for passf in sim sub rec
			do
				if [ $(echo $bbfile | grep  "${passf}_[0-9]\{1,3\}\.txt") ];then
					passfile=1
				fi
				if [ $(echo $bbfile | grep  "${passf}[u,h].*\.txt") ];then
					passfile=1
				fi
			done
			if [ $(echo $bbfile | grep  "fort\.[0-9]\{1,2\}$") ];then
				passfile=1
			fi
			if [ $(echo $bbfile | grep  "log\.sub") ];then
				passfile=1
			fi
			
			if [ $(echo $bbfile | grep  "sub_[u,h].*\.txt") ];then
				passfile=1
			fi
			
		
			if [ $passfile -eq 1 ];then
				continue;
			fi

#			echo $file
			temp_file=$( echo $file |  cut -d . -f 2-10)
#			echo $temp_file
		#	echo -n "copying " 
		#	echo -n "$BAKDIR$temp_file  "
		#	echo $DSTDIR$temp_file
			cp $BAKDIR$temp_file  $DSTDIR$temp_file
		fi
	done
}



for Ver in 664 664p01
do
	BAKDIR=$BAKHOME/$Ver
	DSTDIR=$DSTHOME/$Ver
	cd $BAKDIR
	foreachd .
done

#echo "Sync Analysis Package time: $(date)" >> $LOGTXT
#echo -e "\n" >> $LOGTXT

cd $CPWD



