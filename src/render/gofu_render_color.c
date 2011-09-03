#include "gofu_render_color.h"

void
gofu_render_color_hl1 (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gp, i),
		   gofu_locallength_to_user (gp, j));
  cairo_scale (cr, gp->param_size->grid.liberty.spacing_width,
	       gp->param_size->grid.liberty.spacing_length);
  cairo_set_line_width (cr, gp->param_size->marker.thickness);
  cairo_rectangle (cr, -0.5, -0.5, 1., 1.);
  cairo_close_path (cr);
  gofu_render_set_color (cr, gp->param->highlight.hl1);
  cairo_fill (cr);
  cairo_restore (cr);
}
