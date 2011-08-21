#include "gofu.h"

int
main (void)
{
  cairo_surface_t *surface;
  cairo_t *cr;
  gofu_t *gofup;
  gofup = gofu_alloc (17, 17);
  gofup->param.surface_width = 210 * (72 / 25.4);
  gofup->param.surface_length = 297 * (72 / 25.4);
  gofu_init (gofup);
  surface =
    cairo_pdf_surface_create ("goban.pdf", gofup->param.surface_width,
			      gofup->param.surface_length);
  cr = cairo_create (surface);
  gofu_render (cr, gofup);
  cairo_surface_write_to_png (surface, "goban.png");
  cairo_destroy (cr);
  cairo_surface_destroy (surface);
  gofu_free (gofup);
  return 0;
}
