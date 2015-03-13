#!/bin/bash
#
#===============================================================================
#   FILENAME:         make.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年09月02日 12时07分41秒 CST
#   DESCRIPTION: 
#===============================================================================

cpwd=$(pwd -P)

cd ~
source set664p01.sh
cd ${cpwd}

cd cmt
cmt br cmt config
cmt br make clean
cmt br make
source setup.sh

cd ${cpwd}
