#include <cairo.h>

#define mm_per_pt (25.4/72)
#define pt_per_mm (72/25.4)

int
main (int argc, char *argv[])
{
  cairo_surface_t *surface = cairo_pdf_surface_create ("size.pdf", 200.*pt_per_mm, 200.*pt_per_mm);
        cairo_t *cr = cairo_create (surface);
	cairo_set_source_rgb (cr, 0., 0., 0.);
	cairo_set_line_width (cr, 2.0);
	cairo_rectangle (cr, 0., 0., 200, 100.);
	cairo_stroke(cr);
        //cairo_surface_write_to_png (surface, "size.png");
        cairo_destroy (cr);
        cairo_surface_destroy (surface);
        return 0;
}
