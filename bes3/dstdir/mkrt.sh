#!/bin/bash
MODIFY=0
DSTPATH="/scratchfs/bes/lify/664/root/gamgamkkpipi/mc09"

CPWD=$(pwd -P)
OUTFILE=list
test -f $OUTFILE && rm -rf $OUTFILE
cd $DSTPATH
for file in $(ls *.root)
do
#	echo $file
	if [ -f $file ];then
		echo $DSTPATH/$file >> $CPWD/$OUTFILE
	fi
done
cd $CPWD
if [ $MODIFY -eq 1 ] ;then
	sed -i "s%^%chain->Add(\"%g;"  $OUTFILE
	sed -i "s%$%/save\");%g;"  $OUTFILE
fi
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

