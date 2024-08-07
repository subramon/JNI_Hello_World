#!/bin/bash
set -e 
ROOT=$PWD
# Copy .so file for LuaJIT 
cp /usr/local/lib/libluajit-5.1.so $ROOT/so_dir/
# Build a C library that will be invoked by Lua
pushd .
mkdir -p so_dir/
cd lua_dir/src/
gcc -fPIC -std=gnu99 -shared cprint.c -o ../../so_dir/libutils.so
# Quick test that the library works 
cd ../lua/
luajit test_cprint.lua
popd
#----------------------
INCS="-I./inc/ "
INCS="${INCS} -I/usr/lib/jvm/java-11-openjdk-amd64/include/ "
INCS="${INCS} -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux/ "
# Make libjni.so 
gcc -g -fPIC -shared ${INCS} \
  ./src/jni_init.c \
  ./src/jni_score.c \
  ./src/jni_close.c \
  -o ${ROOT}/so_dir/libjni.so 
test -f $ROOT/so_dir/libjni.so
#----------------------
gcc -g -fPIC -shared ${INCS} \
  ./src/wrap_jni_init.c \
  ./src/wrap_jni_score.c \
  ./src/wrap_jni_close.c \
  -o ${ROOT}/so_dir/libLightR.so \
  ${ROOT}/so_dir/libjni.so \
   /usr/local/lib/libluajit-5.1.so 
test -f $ROOT/so_dir/libLightR.so
#----------------------
echo "Libraries ready"
pushd . 
cd java/
javac LightR.java
java LightR
popd
