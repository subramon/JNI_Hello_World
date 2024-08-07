#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "jni_close.h"

JNIEXPORT int64_t JNICALL
Java_LightR_close(
    JNIEnv *env, 
    jobject obj, 
    uint64_t address
    )
{
  return jni_close(address);
}
