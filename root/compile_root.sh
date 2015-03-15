#!/bin/bash
#!/bin/bash
export CFLAGS=`root-config --cflags`
export LDFLAGS=`root-config --ldflags --glibs`
g++ ${CFLAGS} -c ${1}.cxx
g++ -o ${1} ${1}.o ${LDFLAGS}
rm ${1}.o

