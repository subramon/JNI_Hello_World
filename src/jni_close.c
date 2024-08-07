#include "macros.h"
#include <stdint.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "jni_struct.h"
#include "jni_close.h"

int 
jni_close(
  uint64_t address
    )
{
  int status = 0;
  if ( address == 0 )  { go_BYE(-1); }

  jni_ctx_t *J = (jni_ctx_t *)address;
  printf("Freeing C/Lua data structures\n");
  // TODO SOMETHING LIKE THIS free_configs(&(J->C));
  free_if_non_null(J->config_dir); 
  if ( J->L != NULL ) { lua_close(J->L); }
  free(J);
BYE:
  return status;
}
