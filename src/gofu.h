#include "./parameter/gofu_param.h"
#include "./populate/gofu_popu.h"
#include "./render/gofu_render.h"

typedef struct _gofu
{
  guint8 width;
  guint8 length;
  gofu_param_t param;
  gofu_popu_t **popu;
} gofu_t;
