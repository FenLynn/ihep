#!/bin/bash

CPWD=$(pwd -P)
ROOTPATH="/scratchfs/bes/lify/664p01/root/Eemiss/signal"

for nh in h02 h04 h08
do
	mkdir -p $nh/temp
	if [ $nh = "h02" ];then
		mh="h0.2"
	elif [ $nh = "h04" ];then
		mh="h0.4"
	elif [ $nh = "h08" ];then
		mh="h0.8"
	else
		echo "Match failed!"
	fi
	echo $mh
	sed -e "s%WRAPFILE%mee$nh%g;" ana/wrap_up.C > $nh/wrap.C
	for tname in $(ls $ROOTPATH/*$mh*)
	do
		echo "=================================================================================="
		name=u$(echo $tname|cut -d u -f 2)
		brname=$(echo $name| cut -d . -f 1)$(echo $name| cut -d . -f 2)$(echo $name| cut -d . -f 3)
	#	mergename=$(echo $name| cut -d _ -f 2 |cut -d . -f 1)$(echo $name| cut -d . -f 3)
	#	echo $name $brname $mergename $tname
		cd $nh/temp
	#	sed -e "s%INPUT%$tname%g;" ../../ana/df.h > ./df.h
	#	sed -e "s%OUTPUT%$name%g;" ../../ana/df.C > ./df.C
	#	cp ../../ana/run.C ./
		sed -e "s%MYNAME%$brname%g; s%FILENAME%$name%g" ../../ana/wrap_mid.C >> ../wrap.C
	#	root -q -b run.C
		cd ../../
	done
	cat ana/wrap_low.C >> $nh/wrap.C
	cd $nh
	root -q -b wrap.C
	cd ../
done

