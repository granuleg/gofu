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
  gofu_popu_init_stone (gp);
  gofu_popu_init_marker (gp);
  gofu_popu_init_label (gp);
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
gofu_popu_init_random (gofu_popu_t * gp)
{
  gofu_popu_init_stone_random (gp);
  gofu_popu_init_marker_random (gp);
  gofu_popu_init_label_random (gp);
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
	      break;		// manage error TODO
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
	      break;		// manage error TODO
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
