#include <cairo.h>
#include <glib.h>

#include "../parameter/gofu_param.h"
#include "../parameter/gofu_param_size.h"
#include "../populate/gofu_popu.h"

typedef struct _gofu
{
  gofu_popu_t *popu;
  gofu_param_t *param;
  gofu_param_size_t *param_size;
} gofu_t;

void gofu_render_senseilibrary (gofu_t *);
void gofu_render_pangocairo (cairo_t *, gofu_t *);
