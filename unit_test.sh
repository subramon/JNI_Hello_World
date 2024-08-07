#!/bin/bash
set -e 
INCS="-I. "
INCS="${INCS} -I../../utils/inc/ "
INCS="${INCS} -I../../inc/ "
INCS="${INCS} -I/usr/lib/jvm/java-11-openjdk-amd64/include/ "
INCS="${INCS} -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux/ "
export CLASSPATH=$PWD/
if [ "$LIGHTR_ROOT" == "" ]; then echo "Set LIGHTR_ROOT"; exit 1; fi
test -d "$LIGHTR_ROOT" 

export LD_LIBRARY_PATH=$LIGHTR_ROOT/src/:$PWD
echo "LD_LIBRARY_PATH set to $LD_LIBRARY_PATH"
javac  LightR.java
gcc -g -fPIC -shared ${INCS} \
  wrap_jni_init.c \
  wrap_jni_score.c \
  wrap_jni_close.c \
  -o ../../src/libLightR.so    \
  ../../src/libjni.so \
   /usr/local/lib/libluajit-5.1.so 

echo "Compiled libLightR.so"
java LightR 
