#!/bin/bash

find  /scratchfs/bes/lify  -type d -print |

sed 's;$;\/*;'|

sed 's/^/touch -c  /'|

sh  

find /scratchfs/bes/wangq -type d -print |

sed 's;$;\/*;'|
sed 's/^/touch -c /'|

sh


exit 0

