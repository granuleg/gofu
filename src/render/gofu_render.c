
#define G_SQRT2_2 (G_SQRT2/2)
#define G_SQRT3 1.732050808
#define G_SQRT3_2 (G_SQRT3/2)
#define G_SQRT5 2.236067977
#define MAX_MARKER_RADIUS (3.0-G_SQRT5)/2.0

void
gofu_sensei_library_stdout (gofu_t * gofup)
{
  /*$$ */
  /* X:plain black stone */
  /* O:plain white stone */
  /* 1..9:Black's move 1, White's move 2 */
  /* 0:Black's or White's move 10 */
  /* B:black stone with circle */
  /* W:white stone with circle */
  /* #:black stone with square */
  /* @:white stone with square */
  /* Y:black stone with triangle */
  /* Q:white stone with triangle */
  /* Z:black stone with cross mark (X) */
  /* P:white stone with cross mark (X) */
  /* C:circle on empty intersection */
  /* S:square on empty intersection */
  /* T:triangle on empty intersection */
  /* M:cross mark (X) on empty intersection */
  /* a..z:letter on empty intersection */

  guint8 i, j;
  gchar ascii;
  for (j = 1; j <= gofup->length; j++)
    {
      g_printf ("$$ ");
      for (i = 1; i <= gofup->width; i++)
	{
	  switch (gofup->popu[i][j].grid)
	    {
	    case GRID_NONE:
	      ascii = ' ';
	      break;
	    case GRID_PLAIN:
	      ascii = '.';
	      break;
	    case GRID_STARPOINT:
	      ascii = ',';
	      break;
	    default:
	      ascii = '?';
	      break;
	    }
	  switch (gofup->popu[i][j].stone)
	    {
	    case STONE_NONE:
	      break;
	    case STONE_BLACK:
	      ascii = 'X';
	      break;
	    case STONE_WHITE:
	      ascii = '0';
	      break;
	    default:
	      ascii = '?';
	      break;
	    }
	  switch (gofup->popu[i][j].marker)
	    {
	    case MARKER_NONE:
	      break;
	    case MARKER_CROSS:
	      if (gofup->popu[i][j].stone == STONE_BLACK)
		ascii = 'Z';
	      else if (gofup->popu[i][j].stone == STONE_WHITE)
		ascii = 'P';
	      else
		ascii = 'M';
	      break;
	    case MARKER_TRIANGLE:
	      if (gofup->popu[i][j].stone == STONE_BLACK)
		ascii = 'Y';
	      else if (gofup->popu[i][j].stone == STONE_WHITE)
		ascii = 'Q';
	      else
		ascii = 'T';
	      break;
	    case MARKER_DIAMOND:
	      if (gofup->popu[i][j].stone == STONE_BLACK)
		ascii = 'B';
	      else if (gofup->popu[i][j].stone == STONE_WHITE)
		ascii = 'W';
	      else
		ascii = 'C';
	      break;
	    default:
	      ascii = '?';
	      break;
	    }
	  g_printf ("%c ", ascii);
	}
      g_printf ("\n");
    }
}

void
cairo_uniform_stroke (cairo_t * cr)
{
  cairo_identity_matrix (cr);
  cairo_stroke (cr);
}

void
gofu_cairo_set_color (cairo_t * cr, gofu_color_rgofupa_t color)
{
  cairo_set_source_rgofupa (cr, color.red, color.green, color.blue, color.alpha);
}

gdouble
gofu_popuwidth_to_user (gofu_t * gofup, guint8 i)
{
  assert (i <= gofup->width + 1);
  if (i == 0)
    return 0;
  else if (i == gofup->width + 1)
    return ((2 * gofup->param.grid.liberty.margin_width) +((gofup->width - 1) *
							 gofup->param.
							 grid.liberty.spacing_width));
  else
    return (gofup->param.grid.liberty.margin_width +
	    ((i - 1) * gofup->param.grid.liberty.spacing_width));
}

gdouble
gofu_populength_to_user (gofu_t * gofup, guint8 j)
{
  assert (j <= gofup->length + 1);
  if (j == 0)
    return 0;
  else if (j == gofup->length + 1)
    return ((2 * gofup->param.grid.liberty.margin_length) +
	    ((gofup->length - 1) * gofup->param.grid.liberty.spacing_length));
  else
    return (gofup->param.grid.liberty.margin_length +
	    ((j - 1) * gofup->param.grid.liberty.spacing_length));
}
