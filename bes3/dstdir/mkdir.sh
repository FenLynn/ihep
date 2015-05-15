#!/bin/bash
DSTPATH="/besfs/groups/higgs/users/lify/664p01/dst/etapee/gpipi/gametap"
CPWD=$(pwd -P)
OUTFILE=path.txt
cd $DSTPATH

for file in $(ls)
do
	echo $file
	if [ -f $file ];then
		echo $DSTPATH/$file >> $CPWD/$OUTFILE
	fi
done
cd $CPWD
#for dir in $(ls)
#do
#	echo $dir
#	if [ -d $dir ];then
#		cd $dir 
#		for file in $(ls)
#		do
#			echo $DSTPATH/$dir/$file >> $CPWD/pipiee.txt
#		done
#		cd ..
#	fi
#done

