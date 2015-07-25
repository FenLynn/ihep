#!/bin/bash
#
#===============================================================================
#   FILENAME:         mkdst.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年09月01日 16时48分44秒 CST
#   DESCRIPTION: 
#===============================================================================

#DSTPATH='/bes3fs/offline/data/664p01/psip/mc/09dst/'
FILE="Jpsi_2012"

#sed -i "s%^%${DSTPATH}%g;"  $FILE
sed -i "s%^%\"%g;"  $FILE
sed -i "s%$%\"%g;"  $FILE



