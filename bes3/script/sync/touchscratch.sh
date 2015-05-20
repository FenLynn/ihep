#!/bin/bash
LOGTXT=~/script/sync/log.sync
find  /scratchfs/bes/lify  -type d -print |

sed 's;$;\/*;'|

sed 's/^/touch -c  /'|

sh  

find /scratchfs/bes/wangq -type d -print |

sed 's;$;\/*;'|
sed 's/^/touch -c /'|

sh


echo "Update scratchfs time: $(date)" >> $LOGTXT
echo -e "\n" >> $LOGTXT

exit 0

