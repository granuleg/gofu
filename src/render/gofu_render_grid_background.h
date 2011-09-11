#include "gofu_render.h"
#include "gofu_move.h"
#include "gofu_render_util.h"

void gofu_render_grid_background (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_grid_background_color (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_grid_background_image (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_grid_background_imagepattern (cairo_t *, gofu_t *, guint8,
					       guint8);
