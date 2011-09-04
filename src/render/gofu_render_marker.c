#include "gofu_render_marker.h"

#define G_SQRT2_2 (G_SQRT2/2)
#define G_SQRT3 1.732050808
#define G_SQRT3_2 (G_SQRT3/2)
#define G_SQRT5 2.236067977
#define MAX_MARKER_RADIUS (3.0-G_SQRT5)/2.0

void
gofu_render_marker_context (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_translate (cr, gofu_popuwidth_to_user (gp, i),
		   gofu_populength_to_user (gp, j));
  cairo_scale (cr, gp->param_size->marker.radius,
	       gp->param_size->marker.radius);
}

void
gofu_render_marker_stroke (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_set_line_width (cr, gp->param_size->marker.thickness);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
  cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
  switch (gp->popu->elem[i][j].stone)
    {
    case STONE_BLACK:
      gofu_render_set_color (cr, gp->param->marker.color_black_fill);
      cairo_fill_preserve (cr);
      gofu_render_set_color (cr, gp->param->marker.color_black_stroke);
      cairo_uniform_stroke (cr);
      break;
    case STONE_NONE:
      gofu_render_set_color (cr, gp->param->marker.color_none_stroke);
      cairo_uniform_stroke (cr);
      break;
    case STONE_WHITE:
      gofu_render_set_color (cr, gp->param->marker.color_white_fill);
      cairo_fill_preserve (cr);
      gofu_render_set_color (cr, gp->param->marker.color_white_stroke);
      cairo_uniform_stroke (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_marker_cross (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gp, i, j);
  cairo_move_to (cr, -G_SQRT2_2, -G_SQRT2_2);
  cairo_line_to (cr, +G_SQRT2_2, +G_SQRT2_2);
  cairo_move_to (cr, -G_SQRT2_2, +G_SQRT2_2);
  cairo_line_to (cr, +G_SQRT2_2, -G_SQRT2_2);
  gofu_render_marker_stroke (cr, gp, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_triangle (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gp, i, j);
  cairo_move_to (cr, 0., -1.);
  cairo_line_to (cr, G_SQRT3_2, 0.5);
  cairo_line_to (cr, -G_SQRT3_2, 0.5);
  cairo_line_to (cr, 0., -1.);
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gp, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_diamond (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gp, i, j);
  cairo_move_to (cr, 0., -1.);
  cairo_line_to (cr, 1., 0.);
  cairo_line_to (cr, 0., 1.);
  cairo_line_to (cr, -1., 0.);
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gp, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_pentagon_star (cairo_t * cr, gofu_t * gp, guint8 i,
				  guint8 j)
{
  guint8 z;
  cairo_save (cr);
  gofu_render_marker_context (cr, gp, i, j);
  cairo_move_to (cr, cos (0 * (2 * G_PI / 10.0) + (G_PI_2)),
		 -sin (0 * (2 * G_PI / 10.0) + (G_PI_2)));
  cairo_line_to (cr,
		 ((3 - G_SQRT5) / 2.0) * cos ((2 * G_PI / 10.0) + (G_PI_2)),
		 -((3 - G_SQRT5) / 2.0) * sin ((2 * G_PI / 10.0) + (G_PI_2)));
  for (z = 2; z <= 10; z += 2)
    {
      cairo_line_to (cr, cos (z * (2 * G_PI / 10.0) + (G_PI_2)),
		     -sin (z * (2 * G_PI / 10.0) + (G_PI_2)));
      cairo_line_to (cr,
		     ((3 - G_SQRT5) / 2.0) * cos ((z +
						   1) * (2 * G_PI / 10.0) +
						  (G_PI_2)),
		     -((3 - G_SQRT5) / 2.0) * sin ((z +
						    1) * (2 * G_PI / 10.0) +
						   (G_PI_2)));
    }
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gp, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_circle (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gp, i, j);
  cairo_arc (cr, 0., 0., MAX_MARKER_RADIUS, 0., 2 * G_PI);
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gp, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_square (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gp, i, j);
  cairo_rectangle (cr, -MAX_MARKER_RADIUS, -MAX_MARKER_RADIUS,
		   2 * MAX_MARKER_RADIUS, 2 * MAX_MARKER_RADIUS);
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gp, i, j);
  cairo_restore (cr);
}
