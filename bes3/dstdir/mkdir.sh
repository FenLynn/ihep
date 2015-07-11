#!/bin/bash
MODIFY=1
#DSTPATH="/scratchfs/bes/lify/664/mc/etapee/gampipi/pipipi/dst"
DSTPATH="/bes3fs/offline/data/664p03/psip/dst"

CPWD=$(pwd -P)
OUTFILE=path.txt
test -f path.txt && rm -rf path.txt
cd $DSTPATH
for dir in $(ls)
do
	echo $dir
	if [ -d $dir ];then
		cd $dir 
		for file in $(ls)
		do
			echo $DSTPATH/$dir/$file >> $CPWD/path.txt
		done
		cd ..
	fi
done
cd $CPWD
if [ $MODIFY -eq 1 ] ;then
	sed -i "s%^%\"%g;"  $OUTFILE
	sed -i "s%$%\"%g;"  $OUTFILE
fi
cd $CPWD
