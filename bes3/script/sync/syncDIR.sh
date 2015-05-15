#!/bin/bash

SOURCE1=~/mytest/
DST1=/workfs/bes/lify/git/mytest/
#rsync -az --delete $SOURCE1 $DST1
rsync -az  $SOURCE1 $DST1
echo "Sync directory:$SOURCE1 to $DST1    :	 $(date)" >> $DST1/log.sync

SOURCE2=~/script/
DST2=/workfs/bes/lify/git/bes3/script/
rsync -az  $SOURCE2 $DST2
echo "Sync directory:$SOURCE2 to $DST2    :	 $(date)" >> $DST2/log.sync


SOURCE3=/workfs/bes/lify/myinclude/
DST3=/workfs/bes/lify/git/myinclude/
rsync -az  $SOURCE3 $DST3
echo "Sync directory:$SOURCE3 to $DST3    :	 $(date)" >> $DST3/log.sync
