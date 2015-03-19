#!/bin/bash
#
#===============================================================================
#   FILENAME:         topo.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年09月24日 15时45分24秒 CST
#   DESCRIPTION: 
#===============================================================================

#cp out.root InclusiveTopo-07
cd topo
./topology
sleep 2

cp mclist.txt ../mclist
cd ../mclist

./top.py
make

dvipdf notice.dvi
#gv notice.ps&

