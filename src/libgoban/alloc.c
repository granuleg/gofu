#include "goban.h"

goban_t *
goban_alloc (guint8 x, guint8 y)
{
  goban_t *gb;
  guint8 bounding_box = 2;

  if ((x < 2) || (y < 2))
    return NULL;
  if ((gb = (goban_t *) g_malloc (sizeof (goban_t))) == NULL)
    return NULL;
  gb->width = x;
  gb->length = y;
  if ((gb->local =
       (goban_local_t **) goban_alloc_local (sizeof (goban_local_t),
					     (gb->width) + bounding_box,
					     (gb->length) + bounding_box)) ==
      NULL)
    return NULL;
  return gb;
}

void
goban_free (goban_t * gb)
{
  goban_free_global_internal (gb);
  goban_free_local_internal (gb);
  goban_free_local ((gpointer *) gb->local, (gb->width) + 2);
  g_free ((gpointer) gb);
}

gpointer *
goban_alloc_local (gsize size, guint8 x, guint8 y)
{
  gpointer *z;
  guint8 temp;

  if ((z = (gpointer *) g_malloc0 (x * sizeof (gpointer))) == NULL)
    return NULL;
  for (temp = 0; temp < x; temp++)
    {
      if ((z[temp] = (gpointer) g_malloc0 (y * size)) == NULL)
	return NULL;
    }
  return z;
}

void
goban_free_global_internal (goban_t * gb)
{
  cairo_pattern_destroy (gb->global.stone.pattern_black_radial);
  cairo_pattern_destroy (gb->global.stone.pattern_white_radial);
  g_string_free (gb->global.grid.background.image, TRUE);
}

void
goban_free_local_internal (goban_t * gb)
{
  guint8 i, j;
  for (i = 0; i <= gb->width + 1; i++)
    {
      for (j = 0; j <= gb->length + 1; j++)
	{
	  g_string_free (gb->local[i][j].label, TRUE);
	}
    }
}

void
goban_free_local (gpointer * z, guint8 x)
{
  guint8 temp;
  for (temp = 0; temp < x; temp++)
    {
      g_free (z[temp]);
    }
  g_free (z);
}
