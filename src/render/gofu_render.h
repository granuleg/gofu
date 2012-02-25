#include <cairo.h>
#include <glib.h>

#include "../populate/gofu_popu.h"
#include "../parameter/gofu_param.h"
#include "../parameter/gofu_param_size.h"


#ifndef GOFU_T
#define GOFU_T

typedef struct _gofu
{
  gofu_popu_t *popu;
  gofu_param_t *param;
  gofu_param_size_t *param_size;
} gofu_t;

#endif // GOFU_T

void gofu_render_pangocairo (cairo_t *, gofu_t *);
