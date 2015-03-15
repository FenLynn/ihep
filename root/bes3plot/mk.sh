#!/bin/bash

#export 1=test

export CFLAGS=`root-config --cflags`
export LDFLAGS=`root-config --ldflags --glibs`
#export MYHEAD=$(pwd)/include

OBJ=$(echo ${1} | cut -f 1 -d ".")

#echo ${OBJ}
#echo "g++ ${CFLAGS} -c ${1}"
g++ -fPIC ${CFLAGS} -c ${1}
g++ -shared -o lib${OBJ}.so ${OBJ}.o
#g++ -o ${OBJ} ${OBJ}.o ${LDFLAGS} ${MYLIB}
#rm ${OBJ}.o


#echo "g++ ${CFLAGS} -c ${1}.C"
#g++ ${CFLAGS} -c ${1}.C
#g++ -o ${1} ${1}.o ${LDFLAGS}
#rm ${1}.o

