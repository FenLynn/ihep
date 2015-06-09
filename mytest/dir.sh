#!/bin/bash

#remove the gap directory
for i in $(ls)
do
	if [ -d $i ];then
		cd $i
		GAP=1
		for j in `ls`
		do
			if [ -f $j ];then
				GAP=0
			fi
		done
		cd ..
		if [ $GAP -eq 1 ];then
			echo $i
			rm -r $i
		fi
	fi
done

