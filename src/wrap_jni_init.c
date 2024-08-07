#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "macros.h"
#include "jni_init.h"
JNIEXPORT int64_t JNICALL
Java_LightR_init(
    JNIEnv *env, 
    jobject obj, 
    jstring config_dir
    )
{
  int status = 0;
  const jbyte *str_c = (*env)->GetStringUTFChars(env, config_dir, NULL);
  if ( str_c == NULL) { go_BYE(-1); }

  int64_t address = jni_init(str_c); 
  (*env)->ReleaseStringUTFChars(env, config_dir, str_c);
BYE:
  if ( status == 0 ) { return address; } else { return 0; }
}
