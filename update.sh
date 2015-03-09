#!/bin/bash
#
#===============================================================================
#   FILENAME:         update.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年11月30日 11时00分46秒 CST
#   DESCRIPTION: 
#===============================================================================

cd /afs/ihep.ac.cn/users/l/lify/git/BESIII

git add .
git commit -m "$(date)"
git push origin master


cd /afs/ihep.ac.cn/users/l/lify/git/ROOT

git add .
git commit -m "$(date)"
git push origin master

cd /afs/ihep.ac.cn/users/l/lify/git/
echo "Both Done!"
