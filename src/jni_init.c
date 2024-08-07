#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "macros.h"
#include "jni_struct.h"
#include "jni_init.h"

int64_t 
jni_init(
    const char * const config_dir
    )
{
  int status = 0;
  char *env_str = NULL;
  const char * const fmt = 
  "%s/lua/?.lua;%s/setup/?.lua;%s/setup/?/init.lua;;";

  if ( ( config_dir == NULL  ) || ( *config_dir == '\0' ) ) { go_BYE(-1); }
  jni_ctx_t *J = NULL;
  J = malloc(1 * sizeof(jni_ctx_t));
  return_if_malloc_failed(J);
  memset(J, 0,  (1 * sizeof(jni_ctx_t)));

  int len_str = strlen(fmt) + (3 * strlen(config_dir)) + 64; 
  // printf("len_str   = %d \n", len_str);
  // printf("config_dir = %s \n", config_dir);
  env_str = malloc(len_str); memset(env_str, 0,  len_str); 
  sprintf(env_str, fmt, config_dir, config_dir, config_dir);
  // printf("env_str   = %s \n", env_str);
  setenv("LUA_PATH", env_str, 1);
  // printf("LUA_PATH  = %s \n", getenv("LUA_PATH"));

  J->L = mk_lua_state(); if ( J->L == NULL ) { go_BYE(-1); }
  J->config_dir = strdup(config_dir); 
  status = load_configs(J->L, "mgcv"); // TODO P0 FIX 

BYE:
  free_if_non_null(env_str);
  if ( status != 0 ) { return 0; } else { return (uint64_t)J; }
}

lua_State *
mk_lua_state(
    void
    )
{
  int status = 0;
  lua_State *L = NULL;

  L = luaL_newstate();
  if ( L == NULL ) { go_BYE(-1); }
  luaL_openlibs(L);
BYE:
  if ( status < 0 ) { return NULL; } else { return L; } 
}

int
load_configs(
    lua_State *L,
    const char * const cfg_dir
    )
{
  int status = 0;
  char *cmd = NULL;

  if ( cfg_dir == NULL ) { go_BYE(-1); }
  if ( L == NULL ) { go_BYE(-1); }

  int len = strlen(cfg_dir) + strlen("G = require ''") + 16;
  cmd = malloc(len); 
  return_if_malloc_failed(cmd);
  memset(cmd, 0, len); 
  // Load the configs into G. IMPORTANT: This is a global 
  snprintf(cmd, len-1, "G = require '%s'", cfg_dir); 
  status = luaL_dostring(L, cmd);
  if ( status != 0 ) { 
    fprintf(stderr, "Error luaL_string=%s\n", lua_tostring(L,-1));
    go_BYE(-1);
  }
  // quick check 
  status = luaL_dostring(L, "assert(type(G) == 'table')");
  if ( status != 0 ) { 
    fprintf(stderr, "Error luaL_string=%s\n", lua_tostring(L,-1));
  }
  cBYE(status); 
  status = luaL_dostring(L, "assert(type(G.foo) == 'function')");
  if ( status != 0 ) { 
    fprintf(stderr, "Error luaL_string=%s\n", lua_tostring(L,-1));
  }
  cBYE(status); 
BYE:
  free_if_non_null(cmd);
  return status;
}
