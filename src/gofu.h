/*cairo backend is temporary placed here*/
#include <cairo/cairo-pdf.h>
#include <cairo/cairo-svg.h>
#include <cairo/cairo-ps.h>

#include "./render/gofu_render.h"

gofu_t *gofu_create (guint8, guint8, gdouble, gdouble);
void gofu_destroy (gofu_t *);
