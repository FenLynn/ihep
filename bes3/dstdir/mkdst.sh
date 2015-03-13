#!/bin/bash
#
#===============================================================================
#   FILENAME:         mkdst.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年09月01日 16时48分44秒 CST
#   DESCRIPTION: 
#===============================================================================

DSTPATH=/besfs/groups/dqa/users/vindy/diebhiwide_dst

sed "s/a/${DSTPATH}/g;" qedpath > a.txt



