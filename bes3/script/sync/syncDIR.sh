#!/bin/bash
LOGTXT=~/script/sync/log.sync

echo "Sync time: $(date)" >> $LOGTXT

SOURCE1=~/mytest/
DST1=/workfs/bes/lify/git/mytest/
#rsync -az --delete $SOURCE1 $DST1
rsync -az  $SOURCE1 $DST1
echo "Sync directory: $SOURCE1 to  $DST1 " >> $LOGTXT

SOURCE2=~/script/
DST2=/workfs/bes/lify/git/bes3/script/
rsync -az  $SOURCE2 $DST2
echo "Sync directory: $SOURCE2 to  $DST2 " >> $LOGTXT


SOURCE3=/workfs/bes/lify/myinclude/
DST3=/workfs/bes/lify/git/myinclude/
rsync -az  $SOURCE3 $DST3
echo "Sync directory: $SOURCE3 to  $DST3 " >> $LOGTXT


SOURCE4=~/dstdir/
DST4=/workfs/bes/lify/git/bes3/dstdir/
rsync -az  $SOURCE4 $DST4
echo "Sync directory: $SOURCE4 to  $DST4 " >> $LOGTXT


echo -e "\n" >> $LOGTXT
