#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#ifndef __JNI_INIT_H
#define __JNI_INIT_H
extern int64_t 
jni_init(
    const char * const config_dir
    );
extern lua_State *
mk_lua_state(
    void
    );
extern int
load_configs(
    lua_State *L,
    const char * const cfg_dir
    );
#endif // __JNI_INIT_H
