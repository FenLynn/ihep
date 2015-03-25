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

