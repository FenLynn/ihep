#!/bin/bash
#
#===============================================================================
#   FILENAME:         update.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年11月30日 11时00分46秒 CST
#   DESCRIPTION: 
#===============================================================================

cpwd=$(pwd -P)

git add .
git commit -m "$(date)"
git push origin master


cd $cpwd
echo "Sync Completed!"
