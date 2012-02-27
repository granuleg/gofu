#include "gofu_param.h"

gofu_param_t *
gofu_param_alloc (void)
{
  gofu_param_t *gp;
  if ((gp = (gofu_param_t *) g_malloc (sizeof (gofu_param_t))) == NULL)
    return NULL;
  return gp;
}

void
gofu_param_free (gofu_param_t * gp)
{
  gofu_param_free_string (gp);
  g_free ((gpointer) gp);
}

void
gofu_param_free_string (gofu_param_t * gp)
{
  g_string_free (gp->background.image, TRUE);
  g_string_free (gp->stone.image_black, TRUE);
  g_string_free (gp->stone.image_white, TRUE);
}

void
gofu_param_init (gofu_param_t * gp)
{
  gofu_param_init_background (gp);
  gofu_param_init_grid (gp);
  gofu_param_init_stone (gp);
  gofu_param_init_marker (gp);
  gofu_param_init_label (gp);
}

void
gofu_param_init_background (gofu_param_t * gp)
{
  gp->background.style = GRID_BACKGROUND_COLOR;
  gofu_param_set_color (&gp->background.color, 222, 176, 109);
  gp->background.image = g_string_new ("background.png");
}

void
gofu_param_init_grid (gofu_param_t * gp)
{
  gofu_param_init_grid_liberty (gp);
  gofu_param_init_grid_starpoint (gp);
}

void
gofu_param_init_grid_liberty (gofu_param_t * gp)
{
  gp->grid.liberty.style = GRID_LIBERTY_BOUND;
  gofu_param_set_color_black (&gp->grid.liberty.color);
}

void
gofu_param_init_grid_starpoint (gofu_param_t * gp)
{
  gp->grid.starpoint.style = GRID_STARPOINT_ROUND;
  gofu_param_set_color_black (&gp->grid.starpoint.color);
}

void
gofu_param_init_stone (gofu_param_t * gp)
{
  gp->stone.style = STONE_PLAIN;
  /*color stone */
  gofu_param_set_color_black (&gp->stone.color_black_stroke);
  gofu_param_set_color_black (&gp->stone.color_black_fill);
  gofu_param_set_color_black (&gp->stone.color_white_stroke);
  gofu_param_set_color_white (&gp->stone.color_white_fill);
  /* image stone */
  gp->stone.image_black = g_string_new ("stone_black.png");
  gp->stone.image_white = g_string_new ("stone_white.png");
  /*multiple image should be computed from stone image name */
}

void
gofu_param_init_marker (gofu_param_t * gp)
{
  gp->marker.style = MARKER_PLAIN;
  gofu_param_set_color_white (&gp->marker.color_black_fill);
  gofu_param_set_color_white (&gp->marker.color_black_stroke);
  gofu_param_set_color_black (&gp->marker.color_none_stroke);
  gofu_param_set_color_white (&gp->marker.color_white_fill);
  gofu_param_set_color_black (&gp->marker.color_white_stroke);
}

void
gofu_param_init_label (gofu_param_t * gp)
{
  gp->label.style = LABEL_PLAIN;
  /*font description */
  gofu_param_set_color_white (&gp->label.color_black_stroke);
  gofu_param_set_color_black (&gp->label.color_none_stroke);
  gofu_param_set_color_black (&gp->label.color_white_stroke);
}

void
gofu_param_set_color (gofu_color_t * rgb, guint8 red, guint8 green,
		      guint8 blue)
{
  rgb->red = (gdouble) red / (gdouble) G_MAXUINT8;
  rgb->green = (gdouble) green / (gdouble) G_MAXUINT8;
  rgb->blue = (gdouble) blue / (gdouble) G_MAXUINT8;
}

void
gofu_param_set_color_white (gofu_color_t * rgb)
{
  rgb->red = 1.0;
  rgb->green = 1.0;
  rgb->blue = 1.0;
}

void
gofu_param_set_color_black (gofu_color_t * rgb)
{
  rgb->red = 0.0;
  rgb->green = 0.0;
  rgb->blue = 0.0;
}
