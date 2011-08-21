#include "gofu_popu.h"

void
goban_popu_init (goban_t * gofup)
{
  goban_popu_init_grid (gofup);
  //goban_popu_init_grid_random (gofup);
  goban_popu_init_stone_random (gofup);
  goban_popu_init_marker (gofup);
  //goban_popu_init_marker_random (gofup);
  goban_popu_init_label (gofup);
  //goban_popu_init_label_random (gofup);
  goban_popu_init_highlight (gofup);
  //goban_popu_init_highlight_random (gofup);
}

void
goban_popu_init_grid (goban_t * gofup)
{
  goban_popu_init_grid_liberty (gofup);
  goban_popu_init_grid_starpoint (gofup);
}

void
goban_popu_init_grid_liberty (goban_t * gofup)
{
  guint8 i, j;
  for (i = 1; i <= gofup->width; i++)
    {
      for (j = 1; j <= gofup->length; j++)
	gofup->popu[i][j].grid = GRID_PLAIN;
    }
}

void
goban_popu_init_grid_starpoint (goban_t * gofup)
{
  guint8 delta;
  goban_popu_init_grid_starpoint_tengen (gofup);
  delta = goban_popu_init_grid_starpoint_corner_delta (gofup);
  if (delta != 0)
    {
      goban_popu_init_grid_starpoint_corner (gofup, delta);
      goban_popu_init_grid_starpoint_side (gofup, delta);
    }
}

void
goban_popu_init_grid_starpoint_tengen (goban_t * gofup)
{
  if ((gofup->width % 2 == 1) && (gofup->length % 2 == 1))
    gofup->popu[1 + (gofup->width / 2)][1 + (gofup->length / 2)].grid =
      GRID_STARPOINT;
}

guint8
goban_popu_init_grid_starpoint_corner_delta (goban_t * gofup)
{
  guint8 i, j, delta;
  if ((gofup->width < 7) || (gofup->length < 7))
    delta = 0;
  else
    {
      if (gofup->width < 12)
	i = 2;
      else
	i = 3;
      if (gofup->length < 12)
	j = 2;
      else
	j = 3;
      delta = MIN (i, j);
    }
  return delta;
}

void
goban_popu_init_grid_starpoint_corner (goban_t * gofup, guint8 delta)
{
  gofup->popu[1 + delta][1 + delta].grid = GRID_STARPOINT;
  gofup->popu[gofup->width - delta][1 + delta].grid = GRID_STARPOINT;
  gofup->popu[1 + delta][gofup->length - delta].grid = GRID_STARPOINT;
  gofup->popu[gofup->width - delta][gofup->length - delta].grid = GRID_STARPOINT;
}

void
goban_popu_init_grid_starpoint_side (goban_t * gofup, guint8 delta)
{
  if ((gofup->width % 2 == 1) && (gofup->width - (2 * delta) >= 13))
    {
      gofup->popu[1 + (gofup->width / 2)][1 + delta].grid = GRID_STARPOINT;
      gofup->popu[1 + (gofup->width / 2)][gofup->length - delta].grid =
	GRID_STARPOINT;
    }
  if ((gofup->length % 2 == 1) && ((gofup->length - (2 * delta)) >= 13))
    {
      gofup->popu[1 + delta][1 + (gofup->length / 2)].grid = GRID_STARPOINT;
      gofup->popu[gofup->width - delta][1 + (gofup->length / 2)].grid =
	GRID_STARPOINT;
    }
}

void
goban_popu_init_stone (goban_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  gofup->popu[i][j].stone = STONE_NONE;
	}
    }
}

void
goban_popu_init_marker (goban_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  gofup->popu[i][j].marker = MARKER_NONE;
	}
    }
}

void
goban_popu_init_label (goban_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  gofup->popu[i][j].label = g_string_new ("");
	}
    }
}

void
goban_popu_init_highlight (goban_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  gofup->popu[i][j].highlight = HIGHLIGHT_NONE;
	}
    }
}

void
goban_popu_init_grid_random (goban_t * gofup)
{
  guint8 i, j, temp;
  for (i = 1; i <= gofup->width; i++)
    {
      for (j = 1; j <= gofup->length; j++)
	{
	  temp = g_random_int_range (0, 4);
	  switch (temp)
	    {
	    case 0:
	      gofup->popu[i][j].grid = GRID_NONE;
	      break;
	    case 1:
	      gofup->popu[i][j].grid = GRID_PLAIN;
	      break;
	    case 2:
	      gofup->popu[i][j].grid = GRID_STARPOINT;
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
goban_popu_init_stone_random (goban_t * gofup)
{
  guint8 i, j, temp;
  for (i = 1; i <= gofup->width; i++)
    {
      for (j = 1; j <= gofup->length; j++)
	{
	  temp = g_random_int_range (0, 3);
	  switch (temp)
	    {
	    case 0:
	      gofup->popu[i][j].stone = STONE_NONE;
	      break;
	    case 1:
	      gofup->popu[i][j].stone = STONE_WHITE;
	      break;
	    case 2:
	      gofup->popu[i][j].stone = STONE_BLACK;
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
goban_popu_init_marker_random (goban_t * gofup)
{
  guint8 i, j, temp;
  for (i = 1; i <= gofup->width; i++)
    {
      for (j = 1; j <= gofup->length; j++)
	{
	  temp = g_random_int_range (0, 7);
	  switch (temp)
	    {
	    case 0:
	      gofup->popu[i][j].marker = MARKER_NONE;
	      break;
	    case 1:
	      gofup->popu[i][j].marker = MARKER_CROSS;
	      break;
	    case 2:
	      gofup->popu[i][j].marker = MARKER_TRIANGLE;
	      break;
	    case 3:
	      gofup->popu[i][j].marker = MARKER_DIAMOND;
	      break;
	    case 4:
	      gofup->popu[i][j].marker = MARKER_PENTAGON_STAR;
	      break;
	    case 5:
	      gofup->popu[i][j].marker = MARKER_CIRCLE;
	      break;
	    case 6:
	      gofup->popu[i][j].marker = MARKER_SQUARE;
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
goban_popu_init_label_random (goban_t * gofup)
{
  guint8 i, j, temp;
  char conv[2];
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  temp = g_random_int_range (33, 128);
	  sprintf (conv, "%c", temp);
	  gofup->popu[i][j].label = g_string_new ("");
	  gofup->popu[i][j].label =
	    g_string_assign (gofup->popu[i][j].label, conv);
	}
    }
}

void
goban_popu_init_highlight_random (goban_t * gofup)
{
  guint8 i, j, temp;
  for (i = 1; i <= gofup->width; i++)
    {
      for (j = 1; j <= gofup->length; j++)
	{
	  temp = g_random_int_range (0, 2);
	  switch (temp)
	    {
	    case 0:
	      gofup->popu[i][j].highlight = HIGHLIGHT_NONE;
	      break;
	    case 1:
	      gofup->popu[i][j].highlight = HIGHLIGHT_HL1;
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	}
    }
}
