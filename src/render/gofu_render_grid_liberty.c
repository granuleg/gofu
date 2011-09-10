#include "gofu_render_grid_liberty.h"

void
gofu_render_grid_liberty (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  guint8 grid, gridE, gridS, gridW, gridN;
  guint8 stone, stoneE, stoneS, stoneW, stoneN;
  guint8 detect, detectE, detectS, detectW, detectN;
  cairo_save (cr);
  cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
  cairo_scale (cr, gp->param_size->grid.liberty.spacing_width / 2.0,
	       gp->param_size->grid.liberty.spacing_length / 2.0);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
  gofu_render_set_color (cr, gp->param->grid.liberty.color);
  grid = gp->popu->elem[i][j].grid;
  stone = gp->popu->elem[i][j].stone;
  gridE = gp->popu->elem[i + 1][j].grid;
  gridS = gp->popu->elem[i][j + 1].grid;
  gridW = gp->popu->elem[i - 1][j].grid;
  gridN = gp->popu->elem[i][j - 1].grid;
  cairo_move_to (cr, 0., 0.);
  if (stone == STONE_NONE || gp->param->grid.style_lighten == FALSE)
    {
      if (gp->param->grid.style_boundary == FALSE)
	{
	  cairo_set_line_width (cr, gp->param_size->grid.liberty.thickness);
	  if (gridE != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	}
      else
	{
	  detect = gofu_grid_emptyneighbour (gp, i, j);
	  detectE = gofu_grid_liberty_bound_east (detect);
	  detectS = gofu_grid_liberty_bound_south (detect);
	  detectW = gofu_grid_liberty_bound_west (detect);
	  detectN = gofu_grid_liberty_bound_north (detect);
	  cairo_set_line_width (cr, gp->param_size->grid.liberty.thickness);
	  if (gridE != GRID_NONE && !(detectE))
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && !(detectS))
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && !(detectW))
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && !(detectN))
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  cairo_set_line_width (cr,
				gp->param_size->grid.liberty.thickness_bound);
	  if (gridE != GRID_NONE && detectE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && detectS)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && detectW)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && detectN)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	}
    }
  else				/*else if (stone != STONE_NONE && gp->param->grid.style_lighten == TRUE) */
    {
      stoneE = gp->popu->elem[i + 1][j].stone;
      stoneS = gp->popu->elem[i][j + 1].stone;
      stoneW = gp->popu->elem[i - 1][j].stone;
      stoneN = gp->popu->elem[i][j - 1].stone;
      if (gp->param->grid.style_boundary == FALSE)
	{
	  cairo_set_line_width (cr, gp->param_size->grid.liberty.thickness);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	}
      else
	{
	  detect = gofu_grid_emptyneighbour (gp, i, j);
	  detectE = gofu_grid_liberty_bound_east (detect);
	  detectS = gofu_grid_liberty_bound_south (detect);
	  detectW = gofu_grid_liberty_bound_west (detect);
	  detectN = gofu_grid_liberty_bound_north (detect);
	  cairo_set_line_width (cr, gp->param_size->grid.liberty.thickness);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE && !(detectE))
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE && !(detectS))
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE && !(detectW))
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE && !(detectN))
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  cairo_set_line_width (cr,
				gp->param_size->grid.liberty.thickness_bound);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE && detectE)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE && detectS)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE && detectW)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE && detectN)
	    gofu_render_grid_liberty_E (cr, gp);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	}
    }
  cairo_restore (cr);
}

void
gofu_render_grid_liberty_E (cairo_t * cr, gofu_t * gp)
{
  switch (gp->param->grid.liberty.style)
    {
    case GRID_LIBERTY_NO:
      break;
    case GRID_LIBERTY_LINE:
      gofu_render_grid_line_E (cr);
      break;
    default:
      g_print ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_grid_line_E (cairo_t * cr)
{
  cairo_line_to (cr, 1., 0.);
  cairo_line_to (cr, 0., 0.);
}
