#include "gofu_render.h"

void
gofu_render_pangocairo (cairo_t * cr, gofu_t * gp)
{
  guint8 i, j;
  gofu_render_grid_background (cr, gp);
  for (i = 1; i <= gp->popu->width; i++)
    {
      for (j = 1; j <= gp->popu->length; j++)
	{
	  switch (gp->popu->elem[i][j].grid)
	    {
	    case GRID_NONE:
	      break;
	    case GRID_PLAIN:
	      gofu_render_grid_liberty (cr, gp, i, j);
	      break;
	    case GRID_STARPOINT:
	      gofu_render_grid_liberty (cr, gp, i, j);
	      gofu_render_grid_starpoint (cr, gp, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  switch (gp->popu->elem[i][j].stone)
	    {
	    case STONE_NONE:
	      break;
	    case STONE_BLACK:
	      gofu_render_stone_black (cr, gp, i, j);
	      break;
	    case STONE_WHITE:
	      gofu_render_stone_white (cr, gp, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  switch (gp->popu->elem[i][j].marker)
	    {
	    case MARKER_NONE:
	      break;
	    case MARKER_TRIANGLE:
	      gofu_render_marker_triangle (cr, gp, i, j);
	      break;
	    case MARKER_DIAMOND:
	      gofu_render_marker_diamond (cr, gp, i, j);
	      break;
	    case MARKER_CROSS:
	      gofu_render_marker_cross (cr, gp, i, j);
	      break;
	    case MARKER_PENTAGON_STAR:
	      gofu_render_marker_pentagon_star (cr, gp, i, j);
	      break;
	    case MARKER_CIRCLE:
	      gofu_render_marker_circle (cr, gp, i, j);
	      break;
	    case MARKER_SQUARE:
	      gofu_render_marker_square (cr, gp, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  if ((g_strcmp0 ((gp->popu->elem[i][j].label)->str, "") != 0)
	      && (gp->popu->elem[i][j].marker == MARKER_NONE))
	    gofu_render_label (cr, gp, i, j);
	  switch (gp->popu->elem[i][j].highlight)
	    {
	    case HIGHLIGHT_NONE:
	      break;
	    case HIGHLIGHT_HL1:
	      gofu_render_color_hl1 (cr, gp, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	}
    }
}

void
gofu_render_senseilibrary (gofu_t * gp)
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
  for (j = 1; j <= gp->popu->length; j++)
    {
      g_printf ("$$ ");
      for (i = 1; i <= gp->popu->width; i++)
	{
	  switch (gp->popu->elem[i][j].grid)
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
	  switch (gp->popu->elem[i][j].stone)
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
	  switch (gp->popu->elem[i][j].marker)
	    {
	    case MARKER_NONE:
	      break;
	    case MARKER_CROSS:
	      if (gp->popu->elem[i][j].stone == STONE_BLACK)
		ascii = 'Z';
	      else if (gp->popu->elem[i][j].stone == STONE_WHITE)
		ascii = 'P';
	      else
		ascii = 'M';
	      break;
	    case MARKER_TRIANGLE:
	      if (gp->popu->elem[i][j].stone == STONE_BLACK)
		ascii = 'Y';
	      else if (gp->popu->elem[i][j].stone == STONE_WHITE)
		ascii = 'Q';
	      else
		ascii = 'T';
	      break;
	    case MARKER_DIAMOND:
	      if (gp->popu->elem[i][j].stone == STONE_BLACK)
		ascii = 'B';
	      else if (gp->popu->elem[i][j].stone == STONE_WHITE)
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
