#include <stdbool.h>
#ifndef __CONFIGS_H
#define __CONFIGS_H

typedef struct _config_t { 
  char *cfg_dir;
  int x;
  double y;
  bool z;
} config_t;
#endif
