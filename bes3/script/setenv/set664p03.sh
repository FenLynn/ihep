#!/bin/bash


CPWD=$(pwd -P)

#set path
cd /afs/ihep.ac.cn/users/l/lify/cmthome/cmthome-6.6.4.p03
#set enviroment


source setupCVS.sh
. setupCMT.sh
cmt config
. setup.sh

source /besfs/users/lify/workboss/664p03/TestRelease/TestRelease-00-00-80/cmt/setup.sh

#cd /besfs/users/lify/
cd $CPWD
#enter the work dir
#cd ~/besfs	
