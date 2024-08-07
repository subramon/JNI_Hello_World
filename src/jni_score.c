#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "macros.h"
#include "jni_struct.h"
#include "jni_score.h"

int
jni_score(
    uint64_t address,
    const char * const c_arg1,
    const char * const c_arg2
    )
{
  int status = 0;
  int chk; 
  if ( address == 0 )  { go_BYE(-1); }
  if ( ( c_arg1 == NULL  ) || ( *c_arg1 == '\0' ) ) { go_BYE(-1); }
  if ( ( c_arg2 == NULL  ) || ( *c_arg2 == '\0' ) ) { go_BYE(-1); }

  jni_ctx_t *J = (jni_ctx_t *)address;
  lua_State *L = J->L;
  if ( L == NULL ) { go_BYE(-1); }

  // Load function to be used 
  status = luaL_dostring(L, "foobar = G.foobar"); 
  if ( status != 0 ) { 
    fprintf(stderr, "Error luaL_string=%s\n", lua_tostring(L,-1));
  }
  cBYE(status); 
  // Put lua function on stack 
  chk = lua_gettop(L); if ( chk != 0 ) { go_BYE(-1); }
  lua_getglobal(L, "foobar");
  chk = lua_gettop(L); if ( chk != 1 ) { go_BYE(-1); }
  if ( !lua_isfunction(L, -1)) {
    fprintf(stderr, "Lua Function foobar undefined\n");
    lua_pop(L, 1);
    go_BYE(-1);
  }
  // push remaining args on stack
  lua_pushstring(L, c_arg1); 
  chk = lua_gettop(L); if ( chk != 2 ) { go_BYE(-1); }

  lua_pushnumber(L, strlen(c_arg2)); 
  chk = lua_gettop(L); if ( chk != 3 ) { go_BYE(-1); }
  //-----------------------------------------
  // call lua function and check status 
  status = lua_pcall(L, 2, 1, 0);
  if ( status != 0 ) {
    fprintf(stderr, "fn pass2_fn failed: %s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    return status;
  }
  if ( !lua_isstring(L, 1) ) { go_BYE(-1); }
  char *cptr = lua_tostring(L, 1); 
  printf("Lua returned [%s]\n", cptr); 
  // clean up lua stack 
  lua_pop(L, 1);
  //----------------------------
BYE:
  chk = lua_gettop(L); if ( chk != 0 ) { WHEREAMI; return -1; }
  return status;
}

