#!/bin/bash
CPWD=$(pwd -P)

BAKHOME=/besfs/users/lify/workboss
DSTHOME=/workfs/bes/lify/workboss
foreachd(){
	#	echo $1
	for file in $1/* 
	do
		if [ -d $file ]
		then
			passdir=0
			temp_target=$( echo $file |  cut -d . -f 2)
			for pass in run CVS gcc
			do
				if [ $(echo $temp_target | grep -e ${pass}) ] ;then
					passdir=1
				fi
			done
			if [ $passdir -eq 1 ];then
				continue
			fi
			echo $temp_target
			mkdir -p $DSTDIR$temp_target
			foreachd $file
		elif [ -f $file ]
		then
		
			temp_file=$( echo $file |  cut -d . -f 2-10)
			echo "copying" 
			echo $BAKDIR$temp_file
			echo $DSTDIR$temp_file
			cp $BAKDIR$temp_file  $DSTDIR$temp_file
		fi
	done
}



for Ver in 664p03 664p01
do
	BAKDIR=$BAKHOME/$Ver/Analysis
	DSTDIR=$DSTHOME/$Ver/Analysis
	cd $BAKDIR
	foreachd .
done




cd $CPWD



