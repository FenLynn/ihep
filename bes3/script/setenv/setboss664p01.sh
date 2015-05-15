#!/bin/bash

#set path
cd ~/cmthome/cmthome-6.6.4.p01/

#set enviroment


source setupCVS.sh
. setupCMT.sh
cmt config
. setup.sh

source /besfs/users/lify/TestRelease/TestRelease-00-00-80/cmt/setup.sh

#cd /besfs/users/lify/
cd ~
#enter the work dir
#cd ~/besfs	
