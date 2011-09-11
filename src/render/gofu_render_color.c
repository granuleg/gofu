#include "gofu_render_color.h"

void
gofu_render_color (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  switch (gp->popu->elem[i][j].highlight)
    {
    case HIGHLIGHT_NONE:
      break;
    case HIGHLIGHT_HL1:
      gofu_render_color_hl1 (cr, gp, i, j);
      break;
    default:
      g_print ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_color_hl1 (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
  cairo_scale (cr, gp->param_size->grid.liberty.spacing_width,
	       gp->param_size->grid.liberty.spacing_length);
  cairo_set_line_width (cr, gp->param_size->marker.thickness);
  cairo_rectangle (cr, -0.5, -0.5, 1., 1.);
  cairo_close_path (cr);
  gofu_render_set_color (cr, gp->param->highlight.hl1);
  cairo_fill (cr);
  cairo_restore (cr);
}
