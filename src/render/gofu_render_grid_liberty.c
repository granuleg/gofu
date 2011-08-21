
void
gofu_render_grid_liberty (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  guint8 grid, gridE, gridS, gridW, gridN;
  guint8 stone, stoneE, stoneS, stoneW, stoneN;
  guint8 detect, detectE, detectS, detectW, detectN;
  cairo_save (cr);
  cairo_translate (cr, gofu_popuwidth_to_user (gofup, i),
		   gofu_populength_to_user (gofup, j));
  cairo_scale (cr, gofup->param.grid.liberty.spacing_width / 2.0,
	       gofup->param.grid.liberty.spacing_length / 2.0);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
  gofu_render_set_color (cr, gofup->param.grid.liberty.color_stroke);
  grid = gofup->popu[i][j].grid;
  stone = gofup->popu[i][j].stone;
  gridE = gofup->popu[i + 1][j].grid;
  gridS = gofup->popu[i][j + 1].grid;
  gridW = gofup->popu[i - 1][j].grid;
  gridN = gofup->popu[i][j - 1].grid;
  cairo_move_to (cr, 0., 0.);
  if (stone == STONE_NONE || gofup->param.grid.style_lighten == 0)
    {
      switch (gofup->param.grid.style_boundary)
	{
	case 0:
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness);
	  if (gridE != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	case 1:
	  detect = gofu_grid_emptyneighbour (gofup, i, j);
	  detectE = gofu_grid_liberty_bound_east (detect);
	  detectS = gofu_grid_liberty_bound_south (detect);
	  detectW = gofu_grid_liberty_bound_west (detect);
	  detectN = gofu_grid_liberty_bound_north (detect);
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness);
	  if (gridE != GRID_NONE && !(detectE))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && !(detectS))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && !(detectW))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && !(detectN))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness_bound);
	  if (gridE != GRID_NONE && detectE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && detectS)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && detectW)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && detectN)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	default:
	  g_printf ("%d\n", __LINE__);
	  exit (EXIT_FAILURE);
	  break;
	}
    }
  else				/*else if (stone != STONE_NONE && gofup->param.grid.style_lighten == 1) */
    {
      stoneE = gofup->popu[i + 1][j].stone;
      stoneS = gofup->popu[i][j + 1].stone;
      stoneW = gofup->popu[i - 1][j].stone;
      stoneN = gofup->popu[i][j - 1].stone;
      switch (gofup->param.grid.style_boundary)
	{
	case 0:
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	case 1:
	  detect = gofu_grid_emptyneighbour (gofup, i, j);
	  detectE = gofu_grid_liberty_bound_east (detect);
	  detectS = gofu_grid_liberty_bound_south (detect);
	  detectW = gofu_grid_liberty_bound_west (detect);
	  detectN = gofu_grid_liberty_bound_north (detect);
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE && !(detectE))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE && !(detectS))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE && !(detectW))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE && !(detectN))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness_bound);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE && detectE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE && detectS)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE && detectW)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE && detectN)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	default:
	  g_printf ("%d\n", __LINE__);
	  exit (EXIT_FAILURE);
	  break;
	}
    }
  cairo_restore (cr);
}

void
gofu_render_grid_liberty_E (cairo_t * cr, gofu_t * gofup)
{
  switch (gofup->param.grid.liberty.style)
    {
    case 0:
      gofu_render_grid_line_E (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
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
