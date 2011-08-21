#include "gofu_render_grid_starpoint.h"

void
gofu_render_grid_starpoint (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  guint8 detect;
  cairo_save (cr);
  cairo_translate (cr, gofu_popuwidth_to_user (gofup, i),
		   gofu_populength_to_user (gofup, j));
  cairo_scale (cr, gofup->param.grid.starpoint.radius,
	       gofup->param.grid.starpoint.radius);
  gofu_render_set_color (cr, gofup->param.grid.starpoint.color_stroke);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
  cairo_set_line_width (cr, gofup->param.grid.starpoint.thickness);
  cairo_move_to (cr, 0., 0.);
  detect = gofu_grid_emptyneighbour (gofup, i, j);
  if (gofu_grid_starpoint_detect_SE (detect))
    gofu_render_grid_starpoint_SE (cr, gofup);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_SW (detect))
    gofu_render_grid_starpoint_SE (cr, gofup);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_NW (detect))
    gofu_render_grid_starpoint_SE (cr, gofup);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_NE (detect))
    gofu_render_grid_starpoint_SE (cr, gofup);
  cairo_rotate (cr, G_PI_2);
  cairo_fill_preserve (cr);
  cairo_uniform_stroke (cr);
  cairo_restore (cr);
}


void
gofu_render_grid_starpoint_SE (cairo_t * cr, gofu_t * gofup)
{
  switch (gofup->param.grid.starpoint.style)
    {
    case 0:
      gofu_cairo_grid_starpoint_SE_round (cr);
      break;
    case 1:
      gofu_cairo_grid_starpoint_SE_square (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
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
