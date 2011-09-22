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
  g_string_free (gp->grid.background.image, TRUE);
  g_string_free (gp->stone.image_black, TRUE);
  g_string_free (gp->stone.image_white, TRUE);
}

void
gofu_param_init (gofu_param_t * gp)
{
  gofu_param_init_grid (gp);
  gofu_param_init_stone (gp);
  gofu_param_init_marker (gp);
  gofu_param_init_highlight (gp);
  gofu_param_init_label (gp);
}

void
gofu_param_init_grid (gofu_param_t * gp)
{
  gp->grid.boundary = TRUE;
  gp->grid.lighten = FALSE;
  gofu_param_init_grid_background (gp);
  gofu_param_init_grid_liberty (gp);
  gofu_param_init_grid_starpoint (gp);
}

void
gofu_param_init_grid_background (gofu_param_t * gp)
{
  gp->grid.background.style = GRID_BACKGROUND_COLOR;
  gofu_param_set_color (&gp->grid.background.color, 222, 176, 109, 255);
  gp->grid.background.image = g_string_new ("background.png");
}

void
gofu_param_init_grid_liberty (gofu_param_t * gp)
{
  gp->grid.liberty.style = GRID_LIBERTY_LINE;
  gofu_param_set_color (&gp->grid.liberty.color, 0, 0, 0, 255);
}

void
gofu_param_init_grid_starpoint (gofu_param_t * gp)
{
  gp->grid.starpoint.style = GRID_STARPOINT_ROUND;
  gofu_param_set_color (&gp->grid.starpoint.color, 0, 0, 0, 255);
}

void
gofu_param_init_stone (gofu_param_t * gp)
{
  gp->stone.style = STONE_IMAGE;
  /*color stone */
  gofu_param_set_color (&gp->stone.color_black_stroke, 0, 0, 0, 255);
  gofu_param_set_color (&gp->stone.color_black_fill, 0, 0, 0, 255);
  gofu_param_set_color (&gp->stone.color_white_stroke, 0, 0, 0, 255);
  gofu_param_set_color (&gp->stone.color_white_fill, 255, 255, 255, 255);
  /* image stone */
  gp->stone.image_black = g_string_new ("stone_black.png");
  gp->stone.image_white = g_string_new ("stone_white.png");
  /*multiple image should be computed from stone image name */
}

void
gofu_param_init_marker (gofu_param_t * gp)
{
  gp->marker.style = MARKER_PLAIN;
  gofu_param_set_color (&gp->marker.color_black_fill, 255, 255, 255, 255);
  gofu_param_set_color (&gp->marker.color_black_stroke, 255, 255, 255, 255);
  gofu_param_set_color (&gp->marker.color_none_stroke, 0, 0, 0, 255);
  gofu_param_set_color (&gp->marker.color_white_fill, 255, 255, 255, 255);
  gofu_param_set_color (&gp->marker.color_white_stroke, 0, 0, 0, 255);
}

void
gofu_param_init_highlight (gofu_param_t * gp)
{
  gp->highlight.style = HIGHLIGHT_COLOR;
  gofu_param_set_color (&gp->highlight.hl1, 10, 100, 100, 128);
}

void
gofu_param_init_label (gofu_param_t * gp)
{
  gp->label.style = LABEL_PLAIN;
  /*font description */
  gofu_param_set_color (&gp->label.color_black_stroke, 255, 255, 255, 255);
  gofu_param_set_color (&gp->label.color_none_stroke, 0, 0, 0, 255);
  gofu_param_set_color (&gp->label.color_white_stroke, 0, 0, 0, 255);
}

void
gofu_param_set_color (gofu_color_rgba_t * rgba, guint8 red, guint8 green,
		      guint8 blue, guint8 alpha)
{
  rgba->red = (gdouble) red / (gdouble) G_MAXUINT8;
  rgba->green = (gdouble) green / (gdouble) G_MAXUINT8;
  rgba->blue = (gdouble) blue / (gdouble) G_MAXUINT8;
  rgba->alpha = (gdouble) alpha / (gdouble) G_MAXUINT8;
}

gofu_color_rgba_t *
gofu_param_invert_color (gofu_color_rgba_t * rgba)
{
  rgba->red = (gdouble) 1.0 - rgba->red;
  rgba->green = (gdouble) 1.0 - rgba->green;
  rgba->blue = (gdouble) 1.0 - rgba->blue;
}
