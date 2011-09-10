#include "gofu_render_grid_starpoint.h"

void
gofu_render_grid_starpoint (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  guint8 detect;
  cairo_save (cr);
  cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
  cairo_scale (cr, gp->param_size->grid.starpoint.radius,
	       gp->param_size->grid.starpoint.radius);
  gofu_render_set_color (cr, gp->param->grid.starpoint.color);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
  cairo_set_line_width (cr, gp->param_size->grid.starpoint.thickness);
  cairo_move_to (cr, 0., 0.);
  detect = gofu_grid_emptyneighbour (gp, i, j);
  if (gofu_grid_starpoint_detect_SE (detect))
    gofu_render_grid_starpoint_SE (cr, gp);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_SW (detect))
    gofu_render_grid_starpoint_SE (cr, gp);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_NW (detect))
    gofu_render_grid_starpoint_SE (cr, gp);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_NE (detect))
    gofu_render_grid_starpoint_SE (cr, gp);
  cairo_rotate (cr, G_PI_2);
  cairo_fill_preserve (cr);
  cairo_uniform_stroke (cr);
  cairo_restore (cr);
}


void
gofu_render_grid_starpoint_SE (cairo_t * cr, gofu_t * gp)
{
  switch (gp->param->grid.starpoint.style)
    {
    case GRID_STARPOINT_NO:
      break;
    case GRID_STARPOINT_ROUND:
      gofu_render_grid_starpoint_SE_round (cr);
      break;
    case GRID_STARPOINT_SQUARE:
      gofu_render_grid_starpoint_SE_square (cr);
      break;
    default:
      g_print ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_grid_starpoint_SE_round (cairo_t * cr)
{
  cairo_arc (cr, 0., 0., 1., 0., G_PI_2);
  cairo_close_path (cr);
}

void
gofu_render_grid_starpoint_SE_square (cairo_t * cr)
{
  cairo_rectangle (cr, 0.0, 0.0, 1.0, 1.0);
}
