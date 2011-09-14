#include "gofu.h"

gofu_t *
gofu_create (guint8 width, guint8 length)
{
  gofu_t *gp;

  if ((gp = (gofu_t *) g_malloc (sizeof (gofu_t))) == NULL)
    return NULL;
  gp->popu = gofu_popu_alloc (width, length);
  gp->param = gofu_param_alloc ();
  gp->param_size = gofu_param_size_alloc ();
  //gofu_popu_init (gp->popu);
  gofu_popu_init_random (gp->popu);
  gofu_param_init (gp->param);
  gp->param_size->surface_width = 210 * (72 / 25.4);
  gp->param_size->surface_length = 297 * (72 / 25.4);
  gofu_param_size_init (gp->param_size, width, length);
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
  //gp = gofu_create (G_MAXUINT8 - 2, G_MAXUINT8 - 2);
  gp = gofu_create (17, 17);
  surface =
    cairo_pdf_surface_create ("gofu.pdf", gp->param_size->surface_width,
			      gp->param_size->surface_length);
  cr = cairo_create (surface);
  gofu_render_pangocairo (cr, gp);
  cairo_surface_write_to_png (surface, "gofu.png");
  cairo_destroy (cr);
  cairo_surface_destroy (surface);
  gofu_render_senseilibrary (gp);
  gofu_destroy (gp);
  return 0;
}
