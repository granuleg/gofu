#include "gofu_render.h"
#include "gofu_render_util.h"

void gofu_render_grid (cairo_t *, gofu_t *);
void gofu_render_grid_liberty (cairo_t *, gofu_t *);
void gofu_render_grid_liberty_line (cairo_t *, gofu_t *, gboolean);
void gofu_render_grid_starpoint (cairo_t *, gofu_t *);
void gofu_render_grid_starpoint_style (cairo_t *, gofu_t *);
void gofu_render_grid_starpoint_round (cairo_t *);
void gofu_render_grid_starpoint_square (cairo_t *);
