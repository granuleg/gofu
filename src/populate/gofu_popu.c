#include "gofu_popu.h"

static guint8 bounding_box = 2;

gofu_popu_t *
gofu_popu_alloc (guint8 width, guint8 length)
{
  gofu_popu_t *gp;

  if ((gp = (gofu_popu_t *) g_malloc (sizeof (gofu_popu_t))) == NULL)
    return NULL;
  gp->width = width;
  gp->length = length;
  if ((gp->elem =
       (gofu_popu_elem_t **) gofu_popu_alloc_elem (sizeof (gofu_popu_elem_t),
						   (gp->width) + bounding_box,
						   (gp->length) +
						   bounding_box)) == NULL)
    return NULL;
  return gp;
}

gpointer *
gofu_popu_alloc_elem (gsize elem_size, guint8 width, guint8 length)
{
  gpointer *elem;
  guint8 temp;

  if ((elem = (gpointer *) g_malloc0 (width * sizeof (gpointer))) == NULL)
    return NULL;
  for (temp = 0; temp < width; temp++)
    {
      if ((elem[temp] = (gpointer) g_malloc0 (length * elem_size)) == NULL)
	return NULL;
    }
  return elem;
}

void
gofu_popu_free (gofu_popu_t * gp)
{
  gofu_popu_free_string (gp);
  gofu_popu_free_elem ((gpointer *) gp->elem, (gp->width) + bounding_box);
  g_free ((gpointer) gp);
}

void
gofu_popu_free_string (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  g_string_free (gp->elem[i][j].label, TRUE);
	}
    }
}

void
gofu_popu_free_elem (gpointer * elem, guint8 width)
{
  guint8 temp;
  for (temp = 0; temp < width; temp++)
    {
      g_free (elem[temp]);
    }
  g_free (elem);
}

void
gofu_popu_init (gofu_popu_t * gp)
{
  gofu_popu_init_grid (gp);
  //gofu_popu_init_grid_random (gp);
  gofu_popu_init_stone_random (gp);
  gofu_popu_init_marker (gp);
  //gofu_popu_init_marker_random (gp);
  gofu_popu_init_label (gp);
  //gofu_popu_init_label_random (gp);
  gofu_popu_init_highlight (gp);
  //gofu_popu_init_highlight_random (gp);
}

void
gofu_popu_init_grid (gofu_popu_t * gp)
{
  gofu_popu_init_grid_liberty (gp);
  gofu_popu_init_grid_starpoint (gp);
}

void
gofu_popu_init_grid_liberty (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 1; i <= gp->width; i++)
    {
      for (j = 1; j <= gp->length; j++)
	gp->elem[i][j].grid = GRID_PLAIN;
    }
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

void
gofu_popu_init_stone (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  gp->elem[i][j].stone = STONE_NONE;
	}
    }
}

void
gofu_popu_init_marker (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  gp->elem[i][j].marker = MARKER_NONE;
	}
    }
}

void
gofu_popu_init_label (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  gp->elem[i][j].label = g_string_new ("");
	}
    }
}

void
gofu_popu_init_highlight (gofu_popu_t * gp)
{
  guint8 i, j;
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  gp->elem[i][j].highlight = HIGHLIGHT_NONE;
	}
    }
}

void
gofu_popu_init_grid_random (gofu_popu_t * gp)
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
	      gp->elem[i][j].grid = GRID_NONE;
	      break;
	    case 1:
	      gp->elem[i][j].grid = GRID_PLAIN;
	      break;
	    case 2:
	      gp->elem[i][j].grid = GRID_STARPOINT;
	      break;
	    case 3:
	      break;
	    default:
	      g_print ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	}
    }
}

void
gofu_popu_init_stone_random (gofu_popu_t * gp)
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
	      gp->elem[i][j].stone = STONE_NONE;
	      break;
	    case 1:
	      gp->elem[i][j].stone = STONE_WHITE;
	      break;
	    case 2:
	      gp->elem[i][j].stone = STONE_BLACK;
	      break;
	    default:
	      g_print ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	}
    }
}

void
gofu_popu_init_marker_random (gofu_popu_t * gp)
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
	      gp->elem[i][j].marker = MARKER_NONE;
	      break;
	    case 1:
	      gp->elem[i][j].marker = MARKER_CROSS;
	      break;
	    case 2:
	      gp->elem[i][j].marker = MARKER_TRIANGLE;
	      break;
	    case 3:
	      gp->elem[i][j].marker = MARKER_DIAMOND;
	      break;
	    case 4:
	      gp->elem[i][j].marker = MARKER_PENTAGON_STAR;
	      break;
	    case 5:
	      gp->elem[i][j].marker = MARKER_CIRCLE;
	      break;
	    case 6:
	      gp->elem[i][j].marker = MARKER_SQUARE;
	      break;
	    default:
	      g_print ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	}
    }
}

void
gofu_popu_init_label_random (gofu_popu_t * gp)
{
  guint8 i, j, temp;
  char conv[2];
  for (i = 0; i <= gp->width + 1; i++)
    {
      for (j = 0; j <= gp->length + 1; j++)
	{
	  temp = g_random_int_range (33, 128);
	  sprintf (conv, "%c", temp);
	  gp->elem[i][j].label = g_string_new ("");
	  gp->elem[i][j].label = g_string_assign (gp->elem[i][j].label, conv);
	}
    }
}

void
gofu_popu_init_highlight_random (gofu_popu_t * gp)
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
	      gp->elem[i][j].highlight = HIGHLIGHT_NONE;
	      break;
	    case 1:
	      gp->elem[i][j].highlight = HIGHLIGHT_HL1;
	      break;
	    default:
	      g_print ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	}
    }
}
