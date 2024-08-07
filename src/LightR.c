#define WHEREAMI { fprintf(stderr, "Line %3d of File %s \n", __LINE__, __FILE__);  }
#define go_BYE(x) { WHEREAMI; status = x ; goto BYE; }
#define cBYE(x) { if ( (x) < 0 ) { go_BYE((x)) } }
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LightR.h"
#include "jni_init.h"
JNIEXPORT int64_t JNICALL
Java_LightR_init(
    JNIEnv *env, 
    jobject obj, 
    jstring config_dir
    )
{
  int status = 0;
  char *x = NULL;

  const jbyte *str_c = (*env)->GetStringUTFChars(env, model_file, NULL);
  if ( str_c == NULL) { go_BYE(-1); }

  uint64_t address = jni_init(str_c); 

  (*env)->ReleaseStringUTFChars(env, config_dir,    str_c);
BYE:
  if ( status == 0 ) { return address; } else { return 0; }
}
