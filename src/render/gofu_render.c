#include "gofu_render.h"
#include "gofu_render_external.h"

void
gofu_render_pangocairo (cairo_t * cr, gofu_t * gp)
{
  guint8 i, j;
  gboolean label, marker;
  gofu_render_background (cr, gp);
  gofu_render_grid (cr, gp);
  gofu_render_stone (cr, gp, i, j);
  gofu_render_label (cr, gp, i, j);
  gofu_render_marker (cr, gp, i, j);
}
