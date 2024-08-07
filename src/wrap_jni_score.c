#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "jni_score.h"

JNIEXPORT int64_t JNICALL
Java_LightR_score(
    JNIEnv *env, 
    jobject obj, 
    uint64_t address,
    jstring j_arg1,
    jstring j_arg2
    )
{
  int status = 0;
  const jbyte *c_arg1 = (*env)->GetStringUTFChars(env, j_arg1, NULL);
  const jbyte *c_arg2 = (*env)->GetStringUTFChars(env, j_arg2, NULL);

  status = jni_score(address, c_arg1, c_arg2); 

  (*env)->ReleaseStringUTFChars(env, j_arg1,  c_arg1);
  (*env)->ReleaseStringUTFChars(env, j_arg2,  c_arg2);
BYE:
  return status; 
}
