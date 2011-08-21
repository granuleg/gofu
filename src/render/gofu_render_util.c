#define "gofu_render_util.h"

void
cairo_uniform_stroke (cairo_t * cr)
{
  cairo_identity_matrix (cr);
  cairo_stroke (cr);
}

void
gofu_render_set_color (cairo_t * cr, gofu_color_rgba_t color)
{
  cairo_set_source_rgba (cr, color.red, color.green, color.blue, color.alpha);
}
