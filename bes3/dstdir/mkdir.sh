#!/bin/bash
DSTPATH="/bes3fs/offline/data/664-1/psip/dst"
CPWD=$(pwd -P)
cd $DSTPATH
for dir in $(ls)
do
	echo $dir
	if [ -d $dir ];then
		cd $dir 
		for file in $(ls)
		do
			echo $DSTPATH/$dir/$file >> $CPWD/data09.txt
		done
		cd ..
	fi
done
cd $CPWD

