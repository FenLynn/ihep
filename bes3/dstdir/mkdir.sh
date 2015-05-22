#!/bin/bash
MODIFY=1
DSTPATH="/besfs/groups/higgs/users/lify/664p01/dst/etapee/gpipi/pipipi"
CPWD=$(pwd -P)
OUTFILE=path.txt
test -f path.txt && rm -rf path.txt
cd $DSTPATH
for file in $(ls)
do
	echo $file
	if [ -f $file ];then
		echo $DSTPATH/$file >> $CPWD/$OUTFILE
	fi
done
cd $CPWD
if [ $MODIFY -eq 1 ] ;then
	sed -i "s%^%\"%g;"  $OUTFILE
	sed -i "s%$%\"%g;"  $OUTFILE
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

