#ifndef __JNI_STRUCT_H
#include "configs.h"
#include <lua.h>
#define __JNI_STRUCT_H
// following is JNI context 
typedef struct jni_ctx_t {
  char *config_dir; 
  config_t   C; 
  lua_State *L;
} jni_ctx_t; 

#endif // __JNI_STRUCT_H
