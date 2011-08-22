#include "gofu_popu.h"

void
goban_popu (gofu_popu_t * gp)
{
  goban_popu_grid (gp);
  //goban_popu_grid_random (gp);
  goban_popu_stone_random (gp);
  goban_popu_marker (gp);
  //goban_popu_marker_random (gp);
  goban_popu_label (gp);
  //goban_popu_label_random (gp);
  goban_popu_highlight (gp);
  //goban_popu_highlight_random (gp);
}

void
goban_popu_grid (gofu_popu_t * gp)
{
  goban_popu_grid_liberty (gp);
  goban_popu_grid_starpoint (gp);
}

void
goban_popu_grid_liberty (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 1; i <= gp->width; i++)
    {
      for (j = 1; j <= gp->length; j++)
	gp[i][j].grid = GRID_PLAIN;
    }
}

void
goban_popu_grid_starpoint (gofu_popu_t * gp)
{
  guint8 delta;
  goban_popu_grid_starpoint_tengen (gp);
  delta = goban_popu_grid_starpoint_corner_delta (gp);
  if (delta != 0)
    {
      goban_popu_grid_starpoint_corner (gp, delta);
      goban_popu_grid_starpoint_side (gp, delta);
    }
}

void
goban_popu_grid_starpoint_tengen (gofu_popu_t * gp)
{
  if ((gp->width % 2 == 1) && (gp->length % 2 == 1))
    gp[1 + (gp->width / 2)][1 + (gp->length / 2)].grid = GRID_STARPOINT;
}

guint8
goban_popu_grid_starpoint_corner_delta (gofu_popu_t * gp)
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
goban_popu_grid_starpoint_corner (gofu_popu_t * gp, guint8 delta)
{
  gp[1 + delta][1 + delta].grid = GRID_STARPOINT;
  gp[gp->width - delta][1 + delta].grid = GRID_STARPOINT;
  gp[1 + delta][gp->length - delta].grid = GRID_STARPOINT;
  gp[gp->width - delta][gp->length - delta].grid = GRID_STARPOINT;
}

void
goban_popu_grid_starpoint_side (gofu_popu_t * gp, guint8 delta)
{
  if ((gp->width % 2 == 1) && (gp->width - (2 * delta) >= 13))
    {
      gp[1 + (gp->width / 2)][1 + delta].grid = GRID_STARPOINT;
      gp[1 + (gp->width / 2)][gp->length - delta].grid = GRID_STARPOINT;
    }
  if ((gp->length % 2 == 1) && ((gp->length - (2 * delta)) >= 13))
    {
      gp[1 + delta][1 + (gp->length / 2)].grid = GRID_STARPOINT;
      gp[gp->width - delta][1 + (gp->length / 2)].grid = GRID_STARPOINT;
    }
}

void
goban_popu_stone (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  gp[i][j].stone = STONE_NONE;
	}
    }
}

void
goban_popu_marker (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  gp[i][j].marker = MARKER_NONE;
	}
    }
}

void
goban_popu_label (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  gp[i][j].label = g_string_new ("");
	}
    }
}

void
goban_popu_highlight (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  gp[i][j].highlight = HIGHLIGHT_NONE;
	}
    }
}

void
goban_popu_grid_random (gofu_popu_t * gp)
{
  guint8 i, j, temp;
  for (i = 1; i <= gp->width; i++)
    {
      for (j = 1; j <= gp->length; j++)
	{
	  temp = g_random_int_range (0, 4);
	  switch (temp)
	    {
	    case 0:
	      gp[i][j].grid = GRID_NONE;
	      break;
	    case 1:
	      gp[i][j].grid = GRID_PLAIN;
	      break;
	    case 2:
	      gp[i][j].grid = GRID_STARPOINT;
	      break;
	    case 3:
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
goban_popu_stone_random (gofu_popu_t * gp)
{
  guint8 i, j, temp;
  for (i = 1; i <= gp->width; i++)
    {
      for (j = 1; j <= gp->length; j++)
	{
	  temp = g_random_int_range (0, 3);
	  switch (temp)
	    {
	    case 0:
	      gp[i][j].stone = STONE_NONE;
	      break;
	    case 1:
	      gp[i][j].stone = STONE_WHITE;
	      break;
	    case 2:
	      gp[i][j].stone = STONE_BLACK;
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
goban_popu_marker_random (gofu_popu_t * gp)
{
  guint8 i, j, temp;
  for (i = 1; i <= gp->width; i++)
    {
      for (j = 1; j <= gp->length; j++)
	{
	  temp = g_random_int_range (0, 7);
	  switch (temp)
	    {
	    case 0:
	      gp[i][j].marker = MARKER_NONE;
	      break;
	    case 1:
	      gp[i][j].marker = MARKER_CROSS;
	      break;
	    case 2:
	      gp[i][j].marker = MARKER_TRIANGLE;
	      break;
	    case 3:
	      gp[i][j].marker = MARKER_DIAMOND;
	      break;
	    case 4:
	      gp[i][j].marker = MARKER_PENTAGON_STAR;
	      break;
	    case 5:
	      gp[i][j].marker = MARKER_CIRCLE;
	      break;
	    case 6:
	      gp[i][j].marker = MARKER_SQUARE;
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
goban_popu_label_random (gofu_popu_t * gp)
{
  guint8 i, j, temp;
  char conv[2];
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  temp = g_random_int_range (33, 128);
	  sprintf (conv, "%c", temp);
	  gp[i][j].label = g_string_new ("");
	  gp[i][j].label = g_string_assign (gp[i][j].label, conv);
	}
    }
}

void
goban_popu_highlight_random (gofu_popu_t * gp)
{
  guint8 i, j, temp;
  for (i = 1; i <= gp->width; i++)
    {
      for (j = 1; j <= gp->length; j++)
	{
	  temp = g_random_int_range (0, 2);
	  switch (temp)
	    {
	    case 0:
	      gp[i][j].highlight = HIGHLIGHT_NONE;
	      break;
	    case 1:
	      gp[i][j].highlight = HIGHLIGHT_HL1;
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	}
    }
}
