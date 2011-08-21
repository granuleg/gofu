#include "gofu_cairo_color.h"

void
gofu_render_color_hl1 (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  cairo_scale (cr, gofup->param.grid.liberty.spacing_width,
	       gofup->param.grid.liberty.spacing_length);
  cairo_set_line_width (cr, gofup->param.marker.thickness);
  cairo_rectangle (cr, -0.5, -0.5, 1., 1.);
  cairo_close_path (cr);
  gofu_render_set_color (cr, gofup->param.highlight.hl1);
  cairo_fill (cr);
  cairo_restore (cr);
}
