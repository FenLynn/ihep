#!/bin/bash

#remove the gap directory
for i in $(ls)
do
	if [ -d $i ];then
		cd $i
		mv *.root ../
		cd ..
		rm -r $i
	fi
done

