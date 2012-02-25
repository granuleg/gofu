#include "gofu_render_grid_starpoint.h"

void
gofu_render_grid_starpoint (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  switch (gp->popu->elem[i][j].grid)
    {
    case GRID_NONE:
      break;
    case GRID_PLAIN:
      break;
    case GRID_STARPOINT:
      gofu_render_grid_starpoint_all (cr, gp, i, j);
      break;
    default:
      break;			// manage error TODO
    }
}

void
gofu_render_grid_starpoint_all (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  guint8 detect;
  if (gp->popu->elem[i][j].stone != STONE_NONE)
    return;
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
      break;			// manage error TODO
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

void
gofu_popu_init_grid_starpoint (gofu_popu_t * gp)
{
  guint8 delta;
  gofu_popu_init_grid_starpoint_tengen (gp);
  delta = gofu_popu_init_grid_starpoint_corner_delta (gp);
  if (delta != 0)
    {
      gofu_popu_init_grid_starpoint_corner (gp, delta);
      gofu_popu_init_grid_starpoint_side (gp, delta);
    }
}

void
gofu_popu_init_grid_starpoint_tengen (gofu_popu_t * gp)
{
  if ((gp->width % 2 == 1) && (gp->length % 2 == 1))
    gp->elem[1 + (gp->width / 2)][1 + (gp->length / 2)].grid = GRID_STARPOINT;
}

guint8
gofu_popu_init_grid_starpoint_corner_delta (gofu_popu_t * gp)
{
  guint8 i, j, delta;
  if ((gp->width < 7) || (gp->length < 7))
    delta = 0;
  else
    {
      if (gp->width < 12)
	i = 2;
      else
	i = 3;
      if (gp->length < 12)
	j = 2;
      else
	j = 3;
      delta = MIN (i, j);
    }
  return delta;
}

void
gofu_popu_init_grid_starpoint_corner (gofu_popu_t * gp, guint8 delta)
{
  gp->elem[1 + delta][1 + delta].grid = GRID_STARPOINT;
  gp->elem[gp->width - delta][1 + delta].grid = GRID_STARPOINT;
  gp->elem[1 + delta][gp->length - delta].grid = GRID_STARPOINT;
  gp->elem[gp->width - delta][gp->length - delta].grid = GRID_STARPOINT;
}

void
gofu_popu_init_grid_starpoint_side (gofu_popu_t * gp, guint8 delta)
{
  if ((gp->width % 2 == 1) && (gp->width - (2 * delta) >= 13))
    {
      gp->elem[1 + (gp->width / 2)][1 + delta].grid = GRID_STARPOINT;
      gp->elem[1 + (gp->width / 2)][gp->length - delta].grid = GRID_STARPOINT;
    }
  if ((gp->length % 2 == 1) && ((gp->length - (2 * delta)) >= 13))
    {
      gp->elem[1 + delta][1 + (gp->length / 2)].grid = GRID_STARPOINT;
      gp->elem[gp->width - delta][1 + (gp->length / 2)].grid = GRID_STARPOINT;
    }
}
