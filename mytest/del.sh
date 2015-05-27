#!/bin/bash

TEST_STR="/besfs/users/lify/workboss/sub_012.txt.o12324238"

BSTR=`basename $TEST_STR`
#echo ${TEST_STR%//}

SW=$(echo $BSTR | grep  "sub_.*\.txt\.o.*$")

echo $SW
