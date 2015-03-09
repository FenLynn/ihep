#!/bin/bash
#
#===============================================================================
#   FILENAME:         clean.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年11月26日 00时03分02秒 CST
#   DESCRIPTION: 
#===============================================================================


#determine whether to clean source files ending with .C and .h,therefor root files
#and scripts keeps not a .C or .h ending. .cc is considered OK.

REMOVE_SOURCE=0

rm -rf *.d
rm -rf *.so

if [ ${REMOVE_SOURCE} -eq 1 ];then
	rm -rf *.C
	rm -rf *.h
fi


