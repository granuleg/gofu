#include "gofu_render.h"
#include "gofu_move.h"
#include "gofu_grid.h"
#include "gofu_render_util.h"

void gofu_render_grid_starpoint (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_grid_starpoint_all (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_grid_starpoint_SE (cairo_t *, gofu_t *);
void gofu_render_grid_starpoint_SE_round (cairo_t *);
void gofu_render_grid_starpoint_SE_square (cairo_t * cr);
