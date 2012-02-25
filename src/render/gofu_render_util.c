#include "gofu_render_util.h"

inline gdouble
gofu_move_width (gofu_t * gp, guint8 i)
{
  return (gp->param_size->pos.tx +
	  gp->param_size->grid.margin.width +
	  ((i - 1) * 2.0 * gp->param_size->grid.liberty.spacing_width_2));
}

inline gdouble
gofu_move_length (gofu_t * gp, guint8 j)
{
  return (gp->param_size->pos.ty +
	  gp->param_size->grid.margin.length +
	  ((j - 1) * 2.0 * gp->param_size->grid.liberty.spacing_length_2));
}

void
gofu_cairo_set_color (cairo_t * cr, gofu_color_t color)
{
  cairo_set_source_rgb (cr, color.red, color.green, color.blue);
}

void
gofu_cairo_uniform_stroke (cairo_t * cr)
{
  cairo_identity_matrix (cr);
  cairo_stroke (cr);
}
