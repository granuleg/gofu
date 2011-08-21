#include "goban.h"

#define G_SQRT2_2 (G_SQRT2/2)
#define G_SQRT3 1.732050808
#define G_SQRT3_2 (G_SQRT3/2)
#define G_SQRT5 2.236067977
#define MAX_MARKER_RADIUS (3.0-G_SQRT5)/2.0

#define compass__E 1 << 0
#define compass_SE 1 << 1
#define compass__S 1 << 2
#define compass_SW 1 << 3
#define compass__W 1 << 4
#define compass_NW 1 << 5
#define compass__N 1 << 6
#define compass_NE 1 << 7

gofu_param_description_t jp_standard = { 19, 19, 140, 150, 7.26, 7.82 };

gofu_param_description_t square = { 1, 1, 23, 23, 23, 23 };

gofu_param_ratio_size_t ratio_size = { G_SQRT2_2, G_SQRT2_2, 1. / 2, 1. / 4 };

gofu_param_ratio_thickness_t ratio_thickness = { 1, 1, 1, 1 };


/*********************************************************************************/
// init
void
gofu_init (gofu_t * gofup)
{
  gofu_init_local (gofup);
  gofu_init_param_parameter (gofup, &jp_standard, &ratio_size,
			     &ratio_thickness);
  gofu_init_param_attribute (gofup);
}

gdouble
box_in_box (gdouble x, gdouble y, gdouble a, gdouble b)
{
  gdouble r, tx, ty;
  if ((a == 0) || (b == 0))
    {
      r = 0;
      tx = 0;
      ty = 0;
    }
  else
    {
      r = MIN (a / x, b / y);
      tx = (a - r * x) / 2;
      ty = (b - r * y) / 2;
    }
  return r;
}

void
gofu_init_param_parameter (gofu_t * gofup, gofu_param_description_t * desc,
			   gofu_param_ratio_size_t * rsize,
			   gofu_param_ratio_thickness_t * rthickness)
{
  gdouble scale;
  gdouble margin_width;
  gdouble margin_length;
  gdouble surface_width;
  gdouble surface_length;
  margin_width =
    (desc->gofu_width -
     (desc->line_spacing_width * (desc->number_line_width - 1))) / 2;
  margin_length =
    (desc->gofu_length -
     (desc->line_spacing_length * (desc->number_line_length - 1))) / 2;
  surface_width =
    (desc->line_spacing_width * (gofup->width - 1)) + (2 * margin_width);
  surface_length =
    (desc->line_spacing_length * (gofup->length - 1)) + (2 * margin_length);
  scale =
    box_in_box (surface_width, surface_length, gofup->param.surface_width,
		gofup->param.surface_length);
  //from description
  gofup->param.grid.liberty.spacing_width = desc->line_spacing_width * scale;
  gofup->param.grid.liberty.spacing_length =
    desc->line_spacing_length * scale;
  gofup->param.grid.liberty.margin_width = margin_width * scale;
  gofup->param.grid.liberty.margin_length = margin_length * scale;
  gofup->param.stone.radius =
    (MIN (desc->line_spacing_width, desc->line_spacing_width) / 2) * scale;
  //from ratio size
  gofup->param.marker.radius =
    gofup->param.stone.radius * rsize->marker_stone;
  gofup->param.grid.starpoint.radius =
    gofup->param.marker.radius * rsize->starpoint_marker;
  gofup->param.grid.liberty.thickness_bound =
    gofup->param.grid.starpoint.radius * rsize->bound_starpoint;
  gofup->param.grid.liberty.thickness =
    gofup->param.grid.liberty.thickness_bound * rsize->unbound_bound;
  //from ratio thickness
  gofup->param.grid.starpoint.thickness =
    gofup->param.grid.liberty.thickness * rthickness->unbound_starpoint;
  gofup->param.marker.thickness =
    gofup->param.grid.liberty.thickness * rthickness->unbound_marker;
  gofup->param.stone.thickness =
    gofup->param.grid.liberty.thickness * rthickness->unbound_stone;
}

void
gofu_init_param_attribute (gofu_t * gofup)
{
  gofu_init_param_grid (gofup);
  gofu_init_param_stone (gofup);
  gofu_init_param_marker (gofup);
  gofu_init_param_label (gofup);
  gofu_init_param_highlight (gofup);
}

void
gofu_init_param_grid (gofu_t * gofup)
{
  gofup->param.grid.style_boundary = 1;
  gofup->param.grid.style_lighten = 1;
  gofu_init_param_grid_background (gofup);
  gofu_init_param_grid_liberty (gofup);
  gofu_init_param_grid_starpoint (gofup);
}

void
gofu_init_param_grid_background (gofu_t * gofup)
{
  gofup->param.grid.background.style = 1;
  gofu_init_param_color (&gofup->param.grid.background.color_fill, 222, 176,
			 109, 255);
  gofup->param.grid.background.image =
    g_string_new
    ("/home/granule/Documents/gofu/trunk/src/resource/resource/wood/test2.png");
}

void
gofu_init_param_grid_liberty (gofu_t * gofup)
{
  gofup->param.grid.liberty.style = 0;
  gofu_init_param_color (&gofup->param.grid.liberty.color_stroke, 0, 0, 0,
			 255);
}

void
gofu_init_param_grid_starpoint (gofu_t * gofup)
{
  gofup->param.grid.starpoint.style = 0;
  gofu_init_param_color (&gofup->param.grid.starpoint.color_stroke, 0, 0, 0,
			 255);
}

void
gofu_init_param_stone (gofu_t * gofup)
{
  gofup->param.stone.style = 1;
  gofu_init_param_color (&gofup->param.stone.color_black_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.stone.color_black_fill, 0, 0, 0, 255);
  gofu_init_param_color (&gofup->param.stone.color_white_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.stone.color_white_fill, 255, 255, 255,
			 255);
  gofup->param.stone.pattern_black_radial =
    cairo_pattern_create_radial (-0.2, -0.2, 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgofupa (gofup->param.stone.
					pattern_black_radial, 0., 1., 1., 1.,
					1.);
  cairo_pattern_add_color_stop_rgofupa (gofup->param.stone.
					pattern_black_radial, 1., 0., 0., 0.,
					1.);
  gofup->param.stone.pattern_white_radial =
    cairo_pattern_create_radial (-0.2, -0.2, 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgofupa (gofup->param.stone.
					pattern_white_radial, 0., 0., 0., 0.,
					1.);
  cairo_pattern_add_color_stop_rgofupa (gofup->param.stone.
					pattern_white_radial, 1., 1., 1., 1.,
					1.);
}

void
gofu_init_param_marker (gofu_t * gofup)
{
  gofup->param.marker.style = 0;
  gofu_init_param_color (&gofup->param.marker.color_black_stroke, 255, 255,
			 255, 255);
  gofu_init_param_color (&gofup->param.marker.color_black_fill, 255, 255, 255,
			 255);
  gofu_init_param_color (&gofup->param.marker.color_white_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.marker.color_white_fill, 255, 255, 255,
			 255);
  gofu_init_param_color (&gofup->param.marker.color_none_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.label.color_white_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.label.color_black_stroke, 255, 255,
			 255, 255);
}

void
gofu_init_param_label (gofu_t * gofup)
{
  gofu_init_param_color (&gofup->param.label.color_none_stroke, 0, 0, 0, 255);
}

void
gofu_init_param_highlight (gofu_t * gofup)
{
  gofu_init_param_color (&gofup->param.highlight.hl1, 10, 100, 100, 128);
}

void
gofu_init_local (gofu_t * gofup)
{
  gofu_init_local_grid (gofup);
  //gofu_init_local_grid_random (gofup);
  gofu_init_local_stone_random (gofup);
  gofu_init_local_marker (gofup);
  //gofu_init_local_marker_random (gofup);
  gofu_init_local_label (gofup);
  //gofu_init_local_label_random (gofup);
  gofu_init_local_highlight (gofup);
  //gofu_init_local_highlight_random (gofup);
}

void
gofu_init_local_grid (gofu_t * gofup)
{
  gofu_init_local_grid_liberty (gofup);
  gofu_init_local_grid_starpoint (gofup);
}

void
gofu_init_local_grid_liberty (gofu_t * gofup)
{
  guint8 i, j;
  for (i = 1; i <= gofup->width; i++)
    {
      for (j = 1; j <= gofup->length; j++)
	gofup->local[i][j].grid = GRID_PLAIN;
    }
}

void
gofu_init_local_grid_starpoint (gofu_t * gofup)
{
  guint8 delta;
  gofu_init_local_grid_starpoint_tengen (gofup);
  delta = gofu_init_local_grid_starpoint_corner_delta (gofup);
  if (delta != 0)
    {
      gofu_init_local_grid_starpoint_corner (gofup, delta);
      gofu_init_local_grid_starpoint_side (gofup, delta);
    }
}

void
gofu_init_local_grid_starpoint_tengen (gofu_t * gofup)
{
  if ((gofup->width % 2 == 1) && (gofup->length % 2 == 1))
    gofup->local[1 + (gofup->width / 2)][1 + (gofup->length / 2)].grid =
      GRID_STARPOINT;
}

guint8
gofu_init_local_grid_starpoint_corner_delta (gofu_t * gofup)
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
gofu_init_local_grid_starpoint_corner (gofu_t * gofup, guint8 delta)
{
  gofup->local[1 + delta][1 + delta].grid = GRID_STARPOINT;
  gofup->local[gofup->width - delta][1 + delta].grid = GRID_STARPOINT;
  gofup->local[1 + delta][gofup->length - delta].grid = GRID_STARPOINT;
  gofup->local[gofup->width - delta][gofup->length - delta].grid =
    GRID_STARPOINT;
}

void
gofu_init_local_grid_starpoint_side (gofu_t * gofup, guint8 delta)
{
  if ((gofup->width % 2 == 1) && (gofup->width - (2 * delta) >= 13))
    {
      gofup->local[1 + (gofup->width / 2)][1 + delta].grid = GRID_STARPOINT;
      gofup->local[1 + (gofup->width / 2)][gofup->length - delta].grid =
	GRID_STARPOINT;
    }
  if ((gofup->length % 2 == 1) && ((gofup->length - (2 * delta)) >= 13))
    {
      gofup->local[1 + delta][1 + (gofup->length / 2)].grid = GRID_STARPOINT;
      gofup->local[gofup->width - delta][1 + (gofup->length / 2)].grid =
	GRID_STARPOINT;
    }
}

void
gofu_init_local_stone (gofu_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  gofup->local[i][j].stone = STONE_NONE;
	}
    }
}

void
gofu_init_local_marker (gofu_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  gofup->local[i][j].marker = MARKER_NONE;
	}
    }
}

void
gofu_init_local_label (gofu_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  gofup->local[i][j].label = g_string_new ("");
	}
    }
}

void
gofu_init_local_highlight (gofu_t * gofup)
{
  guint8 i, j;
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  gofup->local[i][j].highlight = HIGHLIGHT_NONE;
	}
    }
}

void
gofu_init_local_grid_random (gofu_t * gofup)
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
	      gofup->local[i][j].grid = GRID_NONE;
	      break;
	    case 1:
	      gofup->local[i][j].grid = GRID_PLAIN;
	      break;
	    case 2:
	      gofup->local[i][j].grid = GRID_STARPOINT;
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
gofu_init_local_stone_random (gofu_t * gofup)
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
	      gofup->local[i][j].stone = STONE_NONE;
	      break;
	    case 1:
	      gofup->local[i][j].stone = STONE_WHITE;
	      break;
	    case 2:
	      gofup->local[i][j].stone = STONE_BLACK;
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
gofu_init_local_marker_random (gofu_t * gofup)
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
	      gofup->local[i][j].marker = MARKER_NONE;
	      break;
	    case 1:
	      gofup->local[i][j].marker = MARKER_CROSS;
	      break;
	    case 2:
	      gofup->local[i][j].marker = MARKER_TRIANGLE;
	      break;
	    case 3:
	      gofup->local[i][j].marker = MARKER_DIAMOND;
	      break;
	    case 4:
	      gofup->local[i][j].marker = MARKER_PENTAGON_STAR;
	      break;
	    case 5:
	      gofup->local[i][j].marker = MARKER_CIRCLE;
	      break;
	    case 6:
	      gofup->local[i][j].marker = MARKER_SQUARE;
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
gofu_init_local_label_random (gofu_t * gofup)
{
  guint8 i, j, temp;
  char conv[2];
  for (i = 0; i <= gofup->width + 1; i++)
    {
      for (j = 0; j <= gofup->length + 1; j++)
	{
	  temp = g_random_int_range (33, 128);
	  sprintf (conv, "%c", temp);
	  gofup->local[i][j].label = g_string_new ("");
	  gofup->local[i][j].label =
	    g_string_assign (gofup->local[i][j].label, conv);
	}
    }
}

void
gofu_init_local_highlight_random (gofu_t * gofup)
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
	      gofup->local[i][j].highlight = HIGHLIGHT_NONE;
	      break;
	    case 1:
	      gofup->local[i][j].highlight = HIGHLIGHT_HL1;
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	}
    }
}

/*********************************************************************************/
// Sensei library
void
gofu_SL_stdout (gofu_t * gofup)
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
	  switch (gofup->local[i][j].grid)
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
	  switch (gofup->local[i][j].stone)
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
	  switch (gofup->local[i][j].marker)
	    {
	    case MARKER_NONE:
	      break;
	    case MARKER_CROSS:
	      if (gofup->local[i][j].stone == STONE_BLACK)
		ascii = 'Z';
	      else if (gofup->local[i][j].stone == STONE_WHITE)
		ascii = 'P';
	      else
		ascii = 'M';
	      break;
	    case MARKER_TRIANGLE:
	      if (gofup->local[i][j].stone == STONE_BLACK)
		ascii = 'Y';
	      else if (gofup->local[i][j].stone == STONE_WHITE)
		ascii = 'Q';
	      else
		ascii = 'T';
	      break;
	    case MARKER_DIAMOND:
	      if (gofup->local[i][j].stone == STONE_BLACK)
		ascii = 'B';
	      else if (gofup->local[i][j].stone == STONE_WHITE)
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

/*********************************************************************************/
// goban util
void
cairo_uniform_stroke (cairo_t * cr)
{
  cairo_identity_matrix (cr);
  cairo_stroke (cr);
}

void
gofu_init_param_color (gofu_color_rgofupa_t * rgofupa, guint8 red,
		       guint8 green, guint8 blue, guint8 alpha)
{
  rgofupa->red = (gdouble) red / (gdouble) G_MAXUINT8;
  rgofupa->green = (gdouble) green / (gdouble) G_MAXUINT8;
  rgofupa->blue = (gdouble) blue / (gdouble) G_MAXUINT8;
  rgofupa->alpha = (gdouble) alpha / (gdouble) G_MAXUINT8;
}

void
gofu_render_set_color (cairo_t * cr, gofu_color_rgofupa_t color)
{
  cairo_set_source_rgofupa (cr, color.red, color.green, color.blue,
			    color.alpha);
}

gdouble
gofu_localwidth_to_user (gofu_t * gofup, guint8 i)
{
  assert (i <= gofup->width + 1);
  if (i == 0)
    return 0;
  else if (i == gofup->width + 1)
    return ((2 * gofup->param.grid.liberty.margin_width) +
	    ((gofup->width - 1) * gofup->param.grid.liberty.spacing_width));
  else
    return (gofup->param.grid.liberty.margin_width +
	    ((i - 1) * gofup->param.grid.liberty.spacing_width));
}

gdouble
gofu_locallength_to_user (gofu_t * gofup, guint8 j)
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

/********************************************************************************/
// background

void
gofu_render_grid_background (cairo_t * cr, gofu_t * gofup)
{
  switch (gofup->param.grid.background.style)
    {
    case 0:
      break;
    case 1:
      gofu_render_grid_background_color (cr, gofup);
      break;
    case 2:
      gofu_render_grid_background_image (cr, gofup);
      break;
    case 3:
      gofu_render_grid_background_imagepattern (cr, gofup);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_grid_background_color (cairo_t * cr, gofu_t * gofup)
{
  double max_x, max_y, min_x, min_y;
  cairo_save (cr);
  min_x = gofu_localwidth_to_user (gofup, 0);
  min_y = gofu_locallength_to_user (gofup, 0);
  max_x = gofu_localwidth_to_user (gofup, gofup->width + 1);
  max_y = gofu_locallength_to_user (gofup, gofup->length + 1);
  gofu_render_set_color (cr, gofup->param.grid.background.color_fill);
  cairo_rectangle (cr, min_x, min_y, max_x, max_y);
  cairo_fill (cr);
  cairo_restore (cr);
}

void
gofu_render_grid_background_image (cairo_t * cr, gofu_t * gofup)
{
  double max_x, max_y, min_x, min_y;
  double w, h;
  cairo_surface_t *image;
  cairo_save (cr);
  min_x = gofu_localwidth_to_user (gofup, 0);
  min_y = gofu_locallength_to_user (gofup, 0);
  max_x = gofu_localwidth_to_user (gofup, gofup->width + 1);
  max_y = gofu_locallength_to_user (gofup, gofup->length + 1);
  image =
    cairo_image_surface_create_from_png
    ((gofup->param.grid.background.image)->str);
  w = cairo_image_surface_get_width (image);
  h = cairo_image_surface_get_height (image);
  cairo_scale (cr, max_x / w, max_y / h);
  cairo_set_source_surface (cr, image, 0, 0);
  cairo_rectangle (cr, min_x * (max_x / w), min_y * (max_y / h), w, h);
  cairo_fill (cr);
  cairo_surface_destroy (image);
  cairo_restore (cr);
}

void
gofu_render_grid_background_imagepattern (cairo_t * cr, gofu_t * gofup)
{
  double max_x, max_y, min_x, min_y;
  cairo_surface_t *image;
  cairo_pattern_t *pattern;
  cairo_matrix_t matrix;
  cairo_save (cr);
  min_x = gofu_localwidth_to_user (gofup, 0);
  min_y = gofu_locallength_to_user (gofup, 0);
  max_x = gofu_localwidth_to_user (gofup, gofup->width + 1);
  max_y = gofu_locallength_to_user (gofup, gofup->length + 1);
  image =
    cairo_image_surface_create_from_png
    ((gofup->param.grid.background.image)->str);
  pattern = cairo_pattern_create_for_surface (image);
  cairo_translate (cr, min_x, min_y);
  cairo_pattern_set_extend (pattern, CAIRO_EXTEND_REFLECT);
  cairo_matrix_init_scale (&matrix, 1.0, 1.0);
  cairo_pattern_set_matrix (pattern, &matrix);
  cairo_set_source (cr, pattern);
  cairo_rectangle (cr, min_x, min_y, max_x, max_y);
  cairo_fill (cr);
  cairo_pattern_destroy (pattern);
  cairo_surface_destroy (image);
  cairo_restore (cr);
}

/********************************************************************************/
// grid = liberty & starpoint

guint8
gofu_grid_emptyneighbour (gofu_t * gofup, guint8 i, guint8 j)
{
  guint8 gridN, gridS, gridW, gridE, gridNW, gridNE, gridSW, gridSE;
  guint8 neighbour = 0;
  gridN = gofup->local[i][j - 1].grid;
  gridS = gofup->local[i][j + 1].grid;
  gridW = gofup->local[i - 1][j].grid;
  gridE = gofup->local[i + 1][j].grid;
  gridNW = gofup->local[i - 1][j - 1].grid;
  gridNE = gofup->local[i + 1][j - 1].grid;
  gridSW = gofup->local[i - 1][j + 1].grid;
  gridSE = gofup->local[i + 1][j + 1].grid;
  if (gridN == GRID_NONE)
    neighbour |= compass__N;
  if (gridS == GRID_NONE)
    neighbour |= compass__S;
  if (gridW == GRID_NONE)
    neighbour |= compass__W;
  if (gridE == GRID_NONE)
    neighbour |= compass__E;
  if (gridNW == GRID_NONE)
    neighbour |= compass_NW;
  if (gridNE == GRID_NONE)
    neighbour |= compass_NE;
  if (gridSW == GRID_NONE)
    neighbour |= compass_SW;
  if (gridSE == GRID_NONE)
    neighbour |= compass_SE;
  return neighbour;
}

/********************************************************************************/
// liberty

void
gofu_render_grid_liberty (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  guint8 grid, gridE, gridS, gridW, gridN;
  guint8 stone, stoneE, stoneS, stoneW, stoneN;
  guint8 detect, detectE, detectS, detectW, detectN;
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  cairo_scale (cr, gofup->param.grid.liberty.spacing_width / 2.0,
	       gofup->param.grid.liberty.spacing_length / 2.0);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
  gofu_render_set_color (cr, gofup->param.grid.liberty.color_stroke);
  grid = gofup->local[i][j].grid;
  stone = gofup->local[i][j].stone;
  gridE = gofup->local[i + 1][j].grid;
  gridS = gofup->local[i][j + 1].grid;
  gridW = gofup->local[i - 1][j].grid;
  gridN = gofup->local[i][j - 1].grid;
  cairo_move_to (cr, 0., 0.);
  if (stone == STONE_NONE || gofup->param.grid.style_lighten == 0)
    {
      switch (gofup->param.grid.style_boundary)
	{
	case 0:
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness);
	  if (gridE != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	case 1:
	  detect = gofu_grid_emptyneighbour (gofup, i, j);
	  detectE = gofu_grid_liberty_bound_east (detect);
	  detectS = gofu_grid_liberty_bound_south (detect);
	  detectW = gofu_grid_liberty_bound_west (detect);
	  detectN = gofu_grid_liberty_bound_north (detect);
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness);
	  if (gridE != GRID_NONE && !(detectE))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && !(detectS))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && !(detectW))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && !(detectN))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  cairo_set_line_width (cr,
				gofup->param.grid.liberty.thickness_bound);
	  if (gridE != GRID_NONE && detectE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && detectS)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && detectW)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && detectN)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	default:
	  g_printf ("%d\n", __LINE__);
	  exit (EXIT_FAILURE);
	  break;
	}
    }
  else				/*else if (stone != STONE_NONE && gofup->param.grid.style_lighten == 1) */
    {
      stoneE = gofup->local[i + 1][j].stone;
      stoneS = gofup->local[i][j + 1].stone;
      stoneW = gofup->local[i - 1][j].stone;
      stoneN = gofup->local[i][j - 1].stone;
      switch (gofup->param.grid.style_boundary)
	{
	case 0:
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	case 1:
	  detect = gofu_grid_emptyneighbour (gofup, i, j);
	  detectE = gofu_grid_liberty_bound_east (detect);
	  detectS = gofu_grid_liberty_bound_south (detect);
	  detectW = gofu_grid_liberty_bound_west (detect);
	  detectN = gofu_grid_liberty_bound_north (detect);
	  cairo_set_line_width (cr, gofup->param.grid.liberty.thickness);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE && !(detectE))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE && !(detectS))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE && !(detectW))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE && !(detectN))
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  cairo_set_line_width (cr,
				gofup->param.grid.liberty.thickness_bound);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE && detectE)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE && detectS)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE && detectW)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE && detectN)
	    gofu_render_grid_liberty_E (cr, gofup);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	default:
	  g_printf ("%d\n", __LINE__);
	  exit (EXIT_FAILURE);
	  break;
	}
    }
  cairo_restore (cr);
}

void
gofu_render_grid_liberty_E (cairo_t * cr, gofu_t * gofup)
{
  switch (gofup->param.grid.liberty.style)
    {
    case 0:
      gofu_render_grid_line_E (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_grid_line_E (cairo_t * cr)
{
  cairo_line_to (cr, 1., 0.);
  cairo_line_to (cr, 0., 0.);
}

gboolean
gofu_grid_liberty_bound_east (guint8 neighbour)
{
  if ((neighbour & compass__N) || (neighbour & compass__S)
      || (neighbour & compass_NE) || (neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_liberty_bound_south (guint8 neighbour)
{
  if ((neighbour & compass__W) || (neighbour & compass__E)
      || (neighbour & compass_SW) || (neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_liberty_bound_west (guint8 neighbour)
{
  if ((neighbour & compass__N) || (neighbour & compass__S)
      || (neighbour & compass_NW) || (neighbour & compass_SW))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_liberty_bound_north (guint8 neighbour)
{
  if ((neighbour & compass__W) || (neighbour & compass__E)
      || (neighbour & compass_NW) || (neighbour & compass_NE))
    return TRUE;
  else
    return FALSE;
}

/********************************************************************************/
// starpoint

void
gofu_render_grid_starpoint (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  guint8 detect;
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  cairo_scale (cr, gofup->param.grid.starpoint.radius,
	       gofup->param.grid.starpoint.radius);
  gofu_render_set_color (cr, gofup->param.grid.starpoint.color_stroke);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
  cairo_set_line_width (cr, gofup->param.grid.starpoint.thickness);
  cairo_move_to (cr, 0., 0.);
  detect = gofu_grid_emptyneighbour (gofup, i, j);
  if (gofu_grid_starpoint_detect_SE (detect))
    gofu_render_grid_starpoint_SE (cr, gofup);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_SW (detect))
    gofu_render_grid_starpoint_SE (cr, gofup);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_NW (detect))
    gofu_render_grid_starpoint_SE (cr, gofup);
  cairo_rotate (cr, G_PI_2);
  if (gofu_grid_starpoint_detect_NE (detect))
    gofu_render_grid_starpoint_SE (cr, gofup);
  cairo_rotate (cr, G_PI_2);
  cairo_fill_preserve (cr);
  cairo_uniform_stroke (cr);
  cairo_restore (cr);
}

gboolean
gofu_grid_starpoint_detect_SE (guint8 neighbour)
{
  if (!(neighbour & compass__S) &&
      !(neighbour & compass__E) && !(neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_starpoint_detect_SW (guint8 neighbour)
{
  if (!(neighbour & compass__S) &&
      !(neighbour & compass__W) && !(neighbour & compass_SW))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_starpoint_detect_NW (guint8 neighbour)
{
  if (!(neighbour & compass__N) &&
      !(neighbour & compass__W) && !(neighbour & compass_NW))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_starpoint_detect_NE (guint8 neighbour)
{
  if (!(neighbour & compass__N) &&
      !(neighbour & compass__E) && !(neighbour & compass_NE))
    return TRUE;
  else
    return FALSE;
}

void
gofu_render_grid_starpoint_SE (cairo_t * cr, gofu_t * gofup)
{
  switch (gofup->param.grid.starpoint.style)
    {
    case 0:
      gofu_render_grid_starpoint_SE_round (cr);
      break;
    case 1:
      gofu_render_grid_starpoint_SE_square (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_grid_starpoint_SE_round (cairo_t * cr)
{
  cairo_arc (cr, 0., 0., 1., 0., G_PI_2);
  cairo_close_path (cr);
}

void
gofu_render_grid_starpoint_SE_square (cairo_t * cr)
{
  cairo_rectangle (cr, 0.0, 0.0, 1.0, 1.0);
}


/********************************************************************************/
// stone

void
gofu_render_stone_fill (cairo_t * cr)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill (cr);
}

void
gofu_render_stone_fill_and_stroke (cairo_t * cr, gofu_t * gofup)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill_preserve (cr);
  cairo_set_line_width (cr, gofup->param.stone.thickness);
  gofu_render_set_color (cr, gofup->param.stone.color_black_stroke);
  cairo_uniform_stroke (cr);
}

void
gofu_render_stone_black (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  switch (gofup->param.stone.style)
    {
    case 0:
      gofu_render_stone_black_plain (cr, gofup);
      break;
    case 1:
      gofu_render_stone_black_radial (cr, gofup);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
  cairo_restore (cr);
}

void
gofu_render_stone_black_plain (cairo_t * cr, gofu_t * gofup)
{
  cairo_scale (cr, gofup->param.stone.radius - gofup->param.stone.thickness,
	       gofup->param.stone.radius - gofup->param.stone.thickness);
  gofu_render_set_color (cr, gofup->param.stone.color_black_fill);
  gofu_render_stone_fill_and_stroke (cr, gofup);
}

void
gofu_render_stone_black_radial (cairo_t * cr, gofu_t * gofup)
{
  cairo_scale (cr, gofup->param.stone.radius, gofup->param.stone.radius);
  cairo_set_source (cr, gofup->param.stone.pattern_black_radial);
  gofu_render_stone_fill (cr);
}


void
gofu_render_stone_white (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  switch (gofup->param.stone.style)
    {
    case 0:
      gofu_render_stone_white_plain (cr, gofup);
      break;
    case 1:
      gofu_render_stone_white_radial (cr, gofup);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
  cairo_restore (cr);
}

void
gofu_render_stone_white_plain (cairo_t * cr, gofu_t * gofup)
{
  cairo_scale (cr, gofup->param.stone.radius - gofup->param.stone.thickness,
	       gofup->param.stone.radius - gofup->param.stone.thickness);
  gofu_render_set_color (cr, gofup->param.stone.color_white_fill);
  gofu_render_stone_fill_and_stroke (cr, gofup);
}

void
gofu_render_stone_white_radial (cairo_t * cr, gofu_t * gofup)
{
  cairo_scale (cr, gofup->param.stone.radius, gofup->param.stone.radius);
  cairo_set_source (cr, gofup->param.stone.pattern_white_radial);
  gofu_render_stone_fill (cr);

}

/********************************************************************************/
// marker

void
gofu_render_marker_context (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  cairo_scale (cr, gofup->param.marker.radius, gofup->param.marker.radius);
}

void
gofu_render_marker_stroke (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_set_line_width (cr, gofup->param.marker.thickness);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
  cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
  switch (gofup->local[i][j].stone)
    {
    case STONE_BLACK:
      gofu_render_set_color (cr, gofup->param.marker.color_black_fill);
      cairo_fill_preserve (cr);
      gofu_render_set_color (cr, gofup->param.marker.color_black_stroke);
      cairo_uniform_stroke (cr);
      break;
    case STONE_NONE:
      gofu_render_set_color (cr, gofup->param.marker.color_none_stroke);
      cairo_uniform_stroke (cr);
      break;
    case STONE_WHITE:
      gofu_render_set_color (cr, gofup->param.marker.color_white_fill);
      cairo_fill_preserve (cr);
      gofu_render_set_color (cr, gofup->param.marker.color_white_stroke);
      cairo_uniform_stroke (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_marker_cross (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gofup, i, j);
  cairo_move_to (cr, -G_SQRT2_2, -G_SQRT2_2);
  cairo_line_to (cr, +G_SQRT2_2, +G_SQRT2_2);
  cairo_move_to (cr, -G_SQRT2_2, +G_SQRT2_2);
  cairo_line_to (cr, +G_SQRT2_2, -G_SQRT2_2);
  gofu_render_marker_stroke (cr, gofup, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_triangle (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gofup, i, j);
  cairo_move_to (cr, 0., -1.);
  cairo_line_to (cr, G_SQRT3_2, 0.5);
  cairo_line_to (cr, -G_SQRT3_2, 0.5);
  cairo_line_to (cr, 0., -1.);
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gofup, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_diamond (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gofup, i, j);
  cairo_move_to (cr, 0., -1.);
  cairo_line_to (cr, 1., 0.);
  cairo_line_to (cr, 0., 1.);
  cairo_line_to (cr, -1., 0.);
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gofup, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_pentagon_star (cairo_t * cr, gofu_t * gofup, guint8 i,
				 guint8 j)
{
  guint8 z;
  cairo_save (cr);
  gofu_render_marker_context (cr, gofup, i, j);
  cairo_move_to (cr, cos (0 * (2 * G_PI / 10.0) + (G_PI_2)),
		 -sin (0 * (2 * G_PI / 10.0) + (G_PI_2)));
  cairo_line_to (cr,
		 ((3 - G_SQRT5) / 2.0) * cos ((2 * G_PI / 10.0) + (G_PI_2)),
		 -((3 - G_SQRT5) / 2.0) * sin ((2 * G_PI / 10.0) + (G_PI_2)));
  for (z = 2; z <= 10; z += 2)
    {
      cairo_line_to (cr, cos (z * (2 * G_PI / 10.0) + (G_PI_2)),
		     -sin (z * (2 * G_PI / 10.0) + (G_PI_2)));
      cairo_line_to (cr,
		     ((3 - G_SQRT5) / 2.0) * cos ((z +
						   1) * (2 * G_PI / 10.0) +
						  (G_PI_2)),
		     -((3 - G_SQRT5) / 2.0) * sin ((z +
						    1) * (2 * G_PI / 10.0) +
						   (G_PI_2)));
    }
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gofup, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_circle (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gofup, i, j);
  cairo_arc (cr, 0., 0., MAX_MARKER_RADIUS, 0., 2 * G_PI);
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gofup, i, j);
  cairo_restore (cr);
}

void
gofu_render_marker_square (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  gofu_render_marker_context (cr, gofup, i, j);
  cairo_rectangle (cr, -MAX_MARKER_RADIUS, -MAX_MARKER_RADIUS,
		   2 * MAX_MARKER_RADIUS, 2 * MAX_MARKER_RADIUS);
  cairo_close_path (cr);
  gofu_render_marker_stroke (cr, gofup, i, j);
  cairo_restore (cr);
}


/********************************************************************************/
// color

void
gofu_render_color_hl1 (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  cairo_scale (cr, gofup->param.grid.liberty.spacing_width,
	       gofup->param.grid.liberty.spacing_length);
  cairo_set_line_width (cr, gofup->param.marker.thickness);
  cairo_rectangle (cr, -0.5, -0.5, 1., 1.);
  cairo_close_path (cr);
  gofu_render_set_color (cr, gofup->param.highlight.hl1);
  cairo_fill (cr);
  cairo_restore (cr);
}

/********************************************************************************/
// label

void
gofu_pangocairo_label (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  PangoLayout *layout;
  PangoFontDescription *font_description;
  PangoRectangle ink_rect;
  PangoRectangle logical_rect;
  int size_x, size_y, pyta, delta_x, delta_y;
  cairo_save (cr);
  font_description = pango_font_description_new ();
  layout = pango_cairo_create_layout (cr);
  /*sans serif (roman) for stone number */
  /*serif (roman) for stone letter */
  pango_font_description_set_family (font_description, "Junicode");
  /* pango_font_description_set_style (font_description, PANGO_STYLE_NORMAL); */
  /* pango_font_description_set_weight (font_description, PANGO_WEIGHT_BOOK); */
  /* pango_font_description_set_variant(font_description,PANGO_VARIANT_NORMAL); */
  /* pango_font_description_set_stretch(font_description, PANGO_STRETCH_ULTRA_EXPANDED); */
  pango_font_description_set_absolute_size (font_description,
					    100 * PANGO_SCALE);
  pango_layout_set_font_description (layout, font_description);
  pango_layout_set_text (layout, (gofup->local[i][j].label)->str, -1);
  pango_layout_get_extents (layout, &ink_rect, &logical_rect);
  size_x = ink_rect.width;
  size_y = ink_rect.height;
  delta_x = logical_rect.x - ink_rect.x;
  delta_y = logical_rect.y - ink_rect.y;
  pyta =
    sqrt (pow (0.5 * size_x / PANGO_SCALE, 2) +
	  pow (0.5 * size_y / PANGO_SCALE, 2));
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  cairo_scale (cr,
	       gofup->param.marker.radius / pyta,
	       gofup->param.marker.radius / pyta);
  switch (gofup->local[i][j].stone)
    {
    case STONE_BLACK:
      gofu_render_set_color (cr, gofup->param.label.color_black_stroke);
      break;
    case STONE_WHITE:
      gofu_render_set_color (cr, gofup->param.label.color_white_stroke);
      break;
    case STONE_NONE:
      gofu_render_set_color (cr, gofup->param.label.color_none_stroke);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
  pango_cairo_update_layout (cr, layout);
  cairo_move_to (cr, (-0.5 * size_x + delta_x) / PANGO_SCALE,
		 (-0.5 * size_y + delta_y) / PANGO_SCALE);
  pango_cairo_show_layout (cr, layout);
  g_object_unref (layout);
  pango_font_description_free (font_description);
  cairo_restore (cr);
}


/********************************************************************************/
// gofu_render entry point

void
gofu_render (cairo_t * cr, gofu_t * gofup)
{
  guint8 i, j;
  gofu_render_grid_background (cr, gofup);
  for (i = 1; i <= gofup->width; i++)
    {
      for (j = 1; j <= gofup->length; j++)
	{
	  switch (gofup->local[i][j].grid)
	    {
	    case GRID_NONE:
	      break;
	    case GRID_PLAIN:
	      gofu_render_grid_liberty (cr, gofup, i, j);
	      break;
	    case GRID_STARPOINT:
	      gofu_render_grid_liberty (cr, gofup, i, j);
	      gofu_render_grid_starpoint (cr, gofup, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  switch (gofup->local[i][j].stone)
	    {
	    case STONE_NONE:
	      break;
	    case STONE_BLACK:
	      gofu_render_stone_black (cr, gofup, i, j);
	      break;
	    case STONE_WHITE:
	      gofu_render_stone_white (cr, gofup, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  switch (gofup->local[i][j].marker)
	    {
	    case MARKER_NONE:
	      break;
	    case MARKER_TRIANGLE:
	      gofu_render_marker_triangle (cr, gofup, i, j);
	      break;
	    case MARKER_DIAMOND:
	      gofu_render_marker_diamond (cr, gofup, i, j);
	      break;
	    case MARKER_CROSS:
	      gofu_render_marker_cross (cr, gofup, i, j);
	      break;
	    case MARKER_PENTAGON_STAR:
	      gofu_render_marker_pentagon_star (cr, gofup, i, j);
	      break;
	    case MARKER_CIRCLE:
	      gofu_render_marker_circle (cr, gofup, i, j);
	      break;
	    case MARKER_SQUARE:
	      gofu_render_marker_square (cr, gofup, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  if ((g_strcmp0 ((gofup->local[i][j].label)->str, "") != 0)
	      && (gofup->local[i][j].marker == MARKER_NONE))
	    gofu_pangocairo_label (cr, gofup, i, j);
	  switch (gofup->local[i][j].highlight)
	    {
	    case HIGHLIGHT_NONE:
	      break;
	    case HIGHLIGHT_HL1:
	      gofu_render_color_hl1 (cr, gofup, i, j);
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
display_device (cairo_surface_t * surface)
{
  double x_offset, y_offset;
  double x_pixels_per_inch, y_pixels_per_inch;
  cairo_surface_get_device_offset (surface, &x_offset, &y_offset);
  cairo_surface_get_fallback_resolution (surface, &x_pixels_per_inch,
					 &y_pixels_per_inch);
}

int
main (void)
{
  cairo_surface_t *surface;
  cairo_t *cr;
  gofu_t *gofup;
  gofup = gofu_alloc (17, 17);
  gofup->param.surface_width = 210 * (72 / 25.4);
  gofup->param.surface_length = 297 * (72 / 25.4);
  gofu_init (gofup);
  surface =
    cairo_pdf_surface_create ("goban.pdf", gofup->param.surface_width,
			      gofup->param.surface_length);
  cr = cairo_create (surface);
  gofu_render (cr, gofup);
  cairo_surface_write_to_png (surface, "goban.png");
  cairo_destroy (cr);
  cairo_surface_destroy (surface);
  gofu_free (gofup);
  return 0;
}
