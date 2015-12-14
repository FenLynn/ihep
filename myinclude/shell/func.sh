#!/bin/bash
function mcd(){
mkdir -p "$1"
cd "$1"
}

function cll(){
cd "$1"
ll
}

function bakup(){
for((i=1;i<20;i++))
do
	if [ -f $1.bak$i -o -d $1.bak$i ];then
		continue
	else
		cp $1 $1.bak$i -r
		break
	fi
done
}


function extract(){
if [ -f $1 ];then
	case $1 in
		*.tar.bz2) tar -xvjf $1 ;;
		*.tar.gz) tar -xvzf $1 ;;
		*.bz2) bunzip2 $1 ;;
		*.rar) unrar -e $1 ;;
		*.gz) gunzip $1 ;;
		*.tar) tar -xvf $1 ;;
		*.tbz2) tar -xjfv $1 ;;
		*.tgz) tar -xvzf $1 ;;
		*.zip) unzip $1 ;;
		*.X) uncompress $1 ;;
		*.7z) 7z -x $1 ;;
		*) echo " $1 cannot be extracted via extract()" ;;
	esac
else
	echo ""$1" is not a valid file"
fi
}

function farmscp(){
if [ -f $1 ];then
	scp $1 lify@hepfarm02.phy.pku.edu.cn:~/save
else
	echo "Not found target!"
fi
}

function farmrscp(){
if [ -d $1 ];then
	scp -r $1 lify@hepfarm02.phy.pku.edu.cn:~/save
else
	echo "Not found target!"
fi
}

function compress(){
if [ -d $1 ];then
	tar -cvzf ${1}.tar.gz $1
else
	echo "Target is not a directory!"
fi
}


#function foreachd(){
##	echo $1
#	for file in $1/* 
#	do
# 如果是目录就打印处理，然后继续遍历，递归调用
#		if [ -d $file ]
#		then
#			echo "$file is directory!"
#			foreachd $file
#elif [ -f $file ]
#then
#		fi
#	done
#}
#CURRENTPATH=${PWD}
#echo $CURRENTPATH
#foreachd $1


function ckqstat()
{
	MYUSER=${USER}
	echo "User:		${USER}"
	qstat -u $MYUSER | awk '{print $1}' | grep \.pbssrv\. | wc -l | awk '{print "Total jobs:	"$1}'
	qstat -u $MYUSER | awk '{print $10}' | grep R | wc -l | awk '{print "Running jobs:	"$1}'
	qstat -u $MYUSER | awk '{print $10}' | grep Q | wc -l | awk '{print "Queueed jobs:	"$1}'
}
