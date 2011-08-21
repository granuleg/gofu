#include "gofu.h"

gofu_t *
gofu_alloc (guint8 x, guint8 y)
{
  gofu_t *gofup;
  guint8 bounding_box = 2;

  if ((x < 2) || (y < 2))
    return NULL;
  if ((gofup = (gofu_t *) g_malloc (sizeof (gofu_t))) == NULL)
    return NULL;
  gofup->width = x;
  gofup->length = y;
  if ((gofup->popu =
       (gofu_popu_t **) gofu_alloc_popu (sizeof (gofu_popu_t),
					 (gofup->width) + bounding_box,
					 (gofup->length) + bounding_box)) ==
      NULL)
    return NULL;
  return gofup;
}

void
gofu_free (gofu_t * gofup)
{
  gofu_free_param_internal (gofup);
  gofu_free_popu_internal (gofup);
  gofu_free_popu ((gpointer *) gofup->popu, (gofup->width) + 2);
  g_free ((gpointer) gofup);
}

gpointer *
gofu_alloc_popu (gsize size, guint8 x, guint8 y)
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
gofu_free_param_internal (gofu_t * gofup)
{
  cairo_pattern_destroy (gofup->param.stone.pattern_black_radial);
  cairo_pattern_destroy (gofup->param.stone.pattern_white_radial);
  g_string_free (gofup->param.grid.background.image, TRUE);
}

void
gofu_free_popu_internal (gofu_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  g_string_free (gofup->popu[i][j].label, TRUE);
	}
    }
}

void
gofu_free_popu (gpointer * z, guint8 x)
{
  guint8 temp;
  for (temp = 0; temp < x; temp++)
    {
      g_free (z[temp]);
    }
  g_free (z);
}
