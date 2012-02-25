#include "gofu.h"

gofu_t *
gofu_create (guint8 width, guint8 length, gdouble surface_width,
	     gdouble surface_length)
{
  gofu_t *gp;

  if ((gp = (gofu_t *) g_malloc (sizeof (gofu_t))) == NULL)
    return NULL;
  /*alloc */
  gp->popu = gofu_popu_alloc (width, length);
  gp->param = gofu_param_alloc ();
  gp->param_size = gofu_param_size_alloc ();
  /*init */
  gofu_popu_init (gp->popu);
  gofu_param_init (gp->param);
  gofu_param_size_init (gp->param_size, width, length, surface_width,
			surface_length);
  return gp;
}

void
gofu_destroy (gofu_t * gp)
{
  gofu_popu_free (gp->popu);
  gofu_param_free (gp->param);
  gofu_param_size_free (gp->param_size);
  g_free ((gpointer) gp);
}

int
main (void)
{
  cairo_surface_t *surface;
  cairo_t *cr;
  gofu_t *gp;
  //A4=210×297mm^2, inch=25.4mm, @72dpi
  gp = gofu_create (17, 17, 210 * (72 / 25.4), 297 * (72 / 25.4));
  surface =
    cairo_pdf_surface_create ("gofu.pdf", gp->param_size->surface_width,
			      gp->param_size->surface_length);
  cr = cairo_create (surface);
  gofu_render_pangocairo (cr, gp);
  cairo_surface_write_to_png (surface, "gofu.png");
  cairo_destroy (cr);
  cairo_surface_destroy (surface);
  gofu_destroy (gp);
  return 0;
}
