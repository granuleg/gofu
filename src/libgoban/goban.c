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

goban_global_description_t jp_standard = { 19, 19, 140, 150, 7.26, 7.82 };

goban_global_description_t square = { 1, 1, 23, 23, 23, 23 };

goban_global_ratio_size_t ratio_size =
  { G_SQRT2_2, G_SQRT2_2, 1. / 2, 1. / 4 };

goban_global_ratio_thickness_t ratio_thickness = { 1, 1, 1, 1 };


/*################################################################################*/
// alloc
goban_t *
goban_alloc (guint8 x, guint8 y)
{
  assert (x >= 2);
  assert (y >= 2);

  goban_t *gb;
  gb = (goban_t *) g_malloc (sizeof (goban_t));
  gb->width = x;
  gb->length = y;
  /*a bounding box is put around */
  gb->local =
    (goban_local_t **) goban_alloc_local (sizeof (goban_local_t),
					  (gb->width) + 2, (gb->length) + 2);
  return gb;
}

gpointer *
goban_alloc_local (gsize size, guint8 x, guint8 y)
{
  guint8 temp;
  gpointer *z;
  z = (gpointer *) g_malloc0 (x * sizeof (gpointer));
  for (temp = 0; temp < x; temp++)
    {
      z[temp] = (gpointer) g_malloc0 (y * size);
    }
  return z;
}

void
goban_free (goban_t * gb)
{
  goban_free_global_internal (gb);
  goban_free_local_internal (gb);
  goban_free_local ((gpointer *) gb->local, (gb->width) + 2);
  g_free ((gpointer) gb);
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

/*********************************************************************************/
// init
void
goban_init (goban_t * gb)
{
  goban_init_local (gb);
  goban_init_global_parameter (gb, &jp_standard, &ratio_size,
			       &ratio_thickness);
  goban_init_global_attribute (gb);
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
goban_init_global_parameter (goban_t * gb, goban_global_description_t * desc,
			     goban_global_ratio_size_t * rsize,
			     goban_global_ratio_thickness_t * rthickness)
{
  gdouble scale;
  gdouble margin_width;
  gdouble margin_length;
  gdouble surface_width;
  gdouble surface_length;
  margin_width =
    (desc->goban_width -
     (desc->line_spacing_width * (desc->number_line_width - 1))) / 2;
  margin_length =
    (desc->goban_length -
     (desc->line_spacing_length * (desc->number_line_length - 1))) / 2;
  surface_width =
    (desc->line_spacing_width * (gb->width - 1)) + (2 * margin_width);
  surface_length =
    (desc->line_spacing_length * (gb->length - 1)) + (2 * margin_length);
  scale =
    box_in_box (surface_width, surface_length, gb->global.surface_width,
		gb->global.surface_length);
  //from description
  gb->global.grid.liberty.spacing_width = desc->line_spacing_width * scale;
  gb->global.grid.liberty.spacing_length = desc->line_spacing_length * scale;
  gb->global.grid.liberty.margin_width = margin_width * scale;
  gb->global.grid.liberty.margin_length = margin_length * scale;
  gb->global.stone.radius =
    (MIN (desc->line_spacing_width, desc->line_spacing_width) / 2) * scale;
  //from ratio size
  gb->global.marker.radius = gb->global.stone.radius * rsize->marker_stone;
  gb->global.grid.starpoint.radius =
    gb->global.marker.radius * rsize->starpoint_marker;
  gb->global.grid.liberty.thickness_bound =
    gb->global.grid.starpoint.radius * rsize->bound_starpoint;
  gb->global.grid.liberty.thickness =
    gb->global.grid.liberty.thickness_bound * rsize->unbound_bound;
  //from ratio thickness
  gb->global.grid.starpoint.thickness =
    gb->global.grid.liberty.thickness * rthickness->unbound_starpoint;
  gb->global.marker.thickness =
    gb->global.grid.liberty.thickness * rthickness->unbound_marker;
  gb->global.stone.thickness =
    gb->global.grid.liberty.thickness * rthickness->unbound_stone;
}

void
goban_init_global_attribute (goban_t * gb)
{
  goban_init_global_grid (gb);
  goban_init_global_stone (gb);
  goban_init_global_marker (gb);
  goban_init_global_label (gb);
  goban_init_global_highlight (gb);
}

void
goban_init_global_grid (goban_t * gb)
{
  gb->global.grid.style_boundary = 1;
  gb->global.grid.style_lighten = 1;
  goban_init_global_grid_background (gb);
  goban_init_global_grid_liberty (gb);
  goban_init_global_grid_starpoint (gb);
}

void
goban_init_global_grid_background (goban_t * gb)
{
  gb->global.grid.background.style = 1;
  goban_init_global_color (&gb->global.grid.background.color_fill, 222, 176,
			   109, 255);
  gb->global.grid.background.image =
    g_string_new
    ("/home/granule/Documents/gofu/trunk/src/resource/resource/wood/test2.png");
}

void
goban_init_global_grid_liberty (goban_t * gb)
{
  gb->global.grid.liberty.style = 0;
  goban_init_global_color (&gb->global.grid.liberty.color_stroke, 0, 0, 0,
			   255);
}

void
goban_init_global_grid_starpoint (goban_t * gb)
{
  gb->global.grid.starpoint.style = 0;
  goban_init_global_color (&gb->global.grid.starpoint.color_stroke, 0, 0, 0,
			   255);
}

void
goban_init_global_stone (goban_t * gb)
{
  gb->global.stone.style = 1;
  goban_init_global_color (&gb->global.stone.color_black_stroke, 0, 0, 0,
			   255);
  goban_init_global_color (&gb->global.stone.color_black_fill, 0, 0, 0, 255);
  goban_init_global_color (&gb->global.stone.color_white_stroke, 0, 0, 0,
			   255);
  goban_init_global_color (&gb->global.stone.color_white_fill, 255, 255, 255,
			   255);
  gb->global.stone.pattern_black_radial =
    cairo_pattern_create_radial (-0.2, -0.2, 0.,
				 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gb->global.stone.pattern_black_radial,
				     0., 1., 1., 1., 1.);
  cairo_pattern_add_color_stop_rgba (gb->global.stone.pattern_black_radial,
				     1., 0., 0., 0., 1.);
  gb->global.stone.pattern_white_radial =
    cairo_pattern_create_radial (-0.2, -0.2, 0.,
				 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gb->global.stone.pattern_white_radial,
				     0., 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gb->global.stone.pattern_white_radial,
				     1., 1., 1., 1., 1.);
}

void
goban_init_global_marker (goban_t * gb)
{
  gb->global.marker.style = 0;
  goban_init_global_color (&gb->global.marker.color_black_stroke, 255, 255,
			   255, 255);
  goban_init_global_color (&gb->global.marker.color_black_fill, 255, 255, 255,
			   255);
  goban_init_global_color (&gb->global.marker.color_white_stroke, 0, 0, 0,
			   255);
  goban_init_global_color (&gb->global.marker.color_white_fill, 255, 255, 255,
			   255);
  goban_init_global_color (&gb->global.marker.color_none_stroke, 0, 0, 0,
			   255);
  goban_init_global_color (&gb->global.label.color_white_stroke, 0, 0, 0,
			   255);
  goban_init_global_color (&gb->global.label.color_black_stroke, 255, 255,
			   255, 255);
}

void
goban_init_global_label (goban_t * gb)
{
  goban_init_global_color (&gb->global.label.color_none_stroke, 0, 0, 0, 255);
}

void
goban_init_global_highlight (goban_t * gb)
{
  goban_init_global_color (&gb->global.highlight.hl1, 10, 100, 100, 128);
}

void
goban_init_local (goban_t * gb)
{
  goban_init_local_grid (gb);
  //goban_init_local_grid_random (gb);
  goban_init_local_stone_random (gb);
  goban_init_local_marker (gb);
  //goban_init_local_marker_random (gb);
  goban_init_local_label (gb);
  //goban_init_local_label_random (gb);
  goban_init_local_highlight (gb);
  //goban_init_local_highlight_random (gb);
}

void
goban_init_local_grid (goban_t * gb)
{
  goban_init_local_grid_liberty (gb);
  goban_init_local_grid_starpoint (gb);
}

void
goban_init_local_grid_liberty (goban_t * gb)
{
  guint8 i, j;
  for (i = 1; i <= gb->width; i++)
    {
      for (j = 1; j <= gb->length; j++)
	gb->local[i][j].grid = GRID_PLAIN;
    }
}

void
goban_init_local_grid_starpoint (goban_t * gb)
{
  guint8 delta;
  goban_init_local_grid_starpoint_tengen (gb);
  delta = goban_init_local_grid_starpoint_corner_delta (gb);
  if (delta != 0)
    {
      goban_init_local_grid_starpoint_corner (gb, delta);
      goban_init_local_grid_starpoint_side (gb, delta);
    }
}

void
goban_init_local_grid_starpoint_tengen (goban_t * gb)
{
  if ((gb->width % 2 == 1) && (gb->length % 2 == 1))
    gb->local[1 + (gb->width / 2)][1 + (gb->length / 2)].grid =
      GRID_STARPOINT;
}

guint8
goban_init_local_grid_starpoint_corner_delta (goban_t * gb)
{
  guint8 i, j, delta;
  if ((gb->width < 7) || (gb->length < 7))
    delta = 0;
  else
    {
      if (gb->width < 12)
	i = 2;
      else
	i = 3;
      if (gb->length < 12)
	j = 2;
      else
	j = 3;
      delta = MIN (i, j);
    }
  return delta;
}

void
goban_init_local_grid_starpoint_corner (goban_t * gb, guint8 delta)
{
  gb->local[1 + delta][1 + delta].grid = GRID_STARPOINT;
  gb->local[gb->width - delta][1 + delta].grid = GRID_STARPOINT;
  gb->local[1 + delta][gb->length - delta].grid = GRID_STARPOINT;
  gb->local[gb->width - delta][gb->length - delta].grid = GRID_STARPOINT;
}

void
goban_init_local_grid_starpoint_side (goban_t * gb, guint8 delta)
{
  if ((gb->width % 2 == 1) && (gb->width - (2 * delta) >= 13))
    {
      gb->local[1 + (gb->width / 2)][1 + delta].grid = GRID_STARPOINT;
      gb->local[1 + (gb->width / 2)][gb->length - delta].grid =
	GRID_STARPOINT;
    }
  if ((gb->length % 2 == 1) && ((gb->length - (2 * delta)) >= 13))
    {
      gb->local[1 + delta][1 + (gb->length / 2)].grid = GRID_STARPOINT;
      gb->local[gb->width - delta][1 + (gb->length / 2)].grid =
	GRID_STARPOINT;
    }
}

void
goban_init_local_stone (goban_t * gb)
{
  guint8 i, j;
  for (i = 0; i <= gb->width + 1; i++)
    {
      for (j = 0; j <= gb->length + 1; j++)
	{
	  gb->local[i][j].stone = STONE_NONE;
	}
    }
}

void
goban_init_local_marker (goban_t * gb)
{
  guint8 i, j;
  for (i = 0; i <= gb->width + 1; i++)
    {
      for (j = 0; j <= gb->length + 1; j++)
	{
	  gb->local[i][j].marker = MARKER_NONE;
	}
    }
}

void
goban_init_local_label (goban_t * gb)
{
  guint8 i, j;
  for (i = 0; i <= gb->width + 1; i++)
    {
      for (j = 0; j <= gb->length + 1; j++)
	{
	  gb->local[i][j].label = g_string_new ("");
	}
    }
}

void
goban_init_local_highlight (goban_t * gb)
{
  guint8 i, j;
  for (i = 0; i <= gb->width + 1; i++)
    {
      for (j = 0; j <= gb->length + 1; j++)
	{
	  gb->local[i][j].highlight = HIGHLIGHT_NONE;
	}
    }
}

void
goban_init_local_grid_random (goban_t * gb)
{
  guint8 i, j, temp;
  for (i = 1; i <= gb->width; i++)
    {
      for (j = 1; j <= gb->length; j++)
	{
	  temp = g_random_int_range (0, 4);
	  switch (temp)
	    {
	    case 0:
	      gb->local[i][j].grid = GRID_NONE;
	      break;
	    case 1:
	      gb->local[i][j].grid = GRID_PLAIN;
	      break;
	    case 2:
	      gb->local[i][j].grid = GRID_STARPOINT;
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
goban_init_local_stone_random (goban_t * gb)
{
  guint8 i, j, temp;
  for (i = 1; i <= gb->width; i++)
    {
      for (j = 1; j <= gb->length; j++)
	{
	  temp = g_random_int_range (0, 3);
	  switch (temp)
	    {
	    case 0:
	      gb->local[i][j].stone = STONE_NONE;
	      break;
	    case 1:
	      gb->local[i][j].stone = STONE_WHITE;
	      break;
	    case 2:
	      gb->local[i][j].stone = STONE_BLACK;
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
goban_init_local_marker_random (goban_t * gb)
{
  guint8 i, j, temp;
  for (i = 1; i <= gb->width; i++)
    {
      for (j = 1; j <= gb->length; j++)
	{
	  temp = g_random_int_range (0, 7);
	  switch (temp)
	    {
	    case 0:
	      gb->local[i][j].marker = MARKER_NONE;
	      break;
	    case 1:
	      gb->local[i][j].marker = MARKER_CROSS;
	      break;
	    case 2:
	      gb->local[i][j].marker = MARKER_TRIANGLE;
	      break;
	    case 3:
	      gb->local[i][j].marker = MARKER_DIAMOND;
	      break;
	    case 4:
	      gb->local[i][j].marker = MARKER_PENTAGON_STAR;
	      break;
	    case 5:
	      gb->local[i][j].marker = MARKER_CIRCLE;
	      break;
	    case 6:
	      gb->local[i][j].marker = MARKER_SQUARE;
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
goban_init_local_label_random (goban_t * gb)
{
  guint8 i, j, temp;
  char conv[2];
  for (i = 0; i <= gb->width + 1; i++)
    {
      for (j = 0; j <= gb->length + 1; j++)
	{
	  temp = g_random_int_range (33, 128);
	  sprintf (conv, "%c", temp);
	  gb->local[i][j].label = g_string_new ("");
	  gb->local[i][j].label =
	    g_string_assign (gb->local[i][j].label, conv);
	}
    }
}

void
goban_init_local_highlight_random (goban_t * gb)
{
  guint8 i, j, temp;
  for (i = 1; i <= gb->width; i++)
    {
      for (j = 1; j <= gb->length; j++)
	{
	  temp = g_random_int_range (0, 2);
	  switch (temp)
	    {
	    case 0:
	      gb->local[i][j].highlight = HIGHLIGHT_NONE;
	      break;
	    case 1:
	      gb->local[i][j].highlight = HIGHLIGHT_HL1;
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
goban_SL_stdout (goban_t * gb)
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
  for (j = 1; j <= gb->length; j++)
    {
      g_printf ("$$ ");
      for (i = 1; i <= gb->width; i++)
	{
	  switch (gb->local[i][j].grid)
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
	  switch (gb->local[i][j].stone)
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
	  switch (gb->local[i][j].marker)
	    {
	    case MARKER_NONE:
	      break;
	    case MARKER_CROSS:
	      if (gb->local[i][j].stone == STONE_BLACK)
		ascii = 'Z';
	      else if (gb->local[i][j].stone == STONE_WHITE)
		ascii = 'P';
	      else
		ascii = 'M';
	      break;
	    case MARKER_TRIANGLE:
	      if (gb->local[i][j].stone == STONE_BLACK)
		ascii = 'Y';
	      else if (gb->local[i][j].stone == STONE_WHITE)
		ascii = 'Q';
	      else
		ascii = 'T';
	      break;
	    case MARKER_DIAMOND:
	      if (gb->local[i][j].stone == STONE_BLACK)
		ascii = 'B';
	      else if (gb->local[i][j].stone == STONE_WHITE)
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
goban_init_global_color (goban_color_rgba_t * rgba, guint8 red, guint8 green,
			 guint8 blue, guint8 alpha)
{
  rgba->red = (gdouble) red / (gdouble) G_MAXUINT8;
  rgba->green = (gdouble) green / (gdouble) G_MAXUINT8;
  rgba->blue = (gdouble) blue / (gdouble) G_MAXUINT8;
  rgba->alpha = (gdouble) alpha / (gdouble) G_MAXUINT8;
}

void
goban_cairo_set_color (cairo_t * cr, goban_color_rgba_t color)
{
  cairo_set_source_rgba (cr, color.red, color.green, color.blue, color.alpha);
}

gdouble
goban_localwidth_to_user (goban_t * gb, guint8 i)
{
  assert (i <= gb->width + 1);
  if (i == 0)
    return 0;
  else if (i == gb->width + 1)
    return ((2 * gb->global.grid.liberty.margin_width) +((gb->width - 1) *
							 gb->global.
							 grid.liberty.spacing_width));
  else
    return (gb->global.grid.liberty.margin_width +
	    ((i - 1) * gb->global.grid.liberty.spacing_width));
}

gdouble
goban_locallength_to_user (goban_t * gb, guint8 j)
{
  assert (j <= gb->length + 1);
  if (j == 0)
    return 0;
  else if (j == gb->length + 1)
    return ((2 * gb->global.grid.liberty.margin_length) +
	    ((gb->length - 1) * gb->global.grid.liberty.spacing_length));
  else
    return (gb->global.grid.liberty.margin_length +
	    ((j - 1) * gb->global.grid.liberty.spacing_length));
}

/********************************************************************************/
// background

void
goban_cairo_grid_background (cairo_t * cr, goban_t * gb)
{
  switch (gb->global.grid.background.style)
    {
    case 0:
      break;
    case 1:
      goban_cairo_grid_background_color (cr, gb);
      break;
    case 2:
      goban_cairo_grid_background_image (cr, gb);
      break;
    case 3:
      goban_cairo_grid_background_imagepattern (cr, gb);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
goban_cairo_grid_background_color (cairo_t * cr, goban_t * gb)
{
  double max_x, max_y, min_x, min_y;
  cairo_save (cr);
  min_x = goban_localwidth_to_user (gb, 0);
  min_y = goban_locallength_to_user (gb, 0);
  max_x = goban_localwidth_to_user (gb, gb->width + 1);
  max_y = goban_locallength_to_user (gb, gb->length + 1);
  goban_cairo_set_color (cr, gb->global.grid.background.color_fill);
  cairo_rectangle (cr, min_x, min_y, max_x, max_y);
  cairo_fill (cr);
  cairo_restore (cr);
}

void
goban_cairo_grid_background_image (cairo_t * cr, goban_t * gb)
{
  double max_x, max_y, min_x, min_y;
  double w, h;
  cairo_surface_t *image;
  cairo_save (cr);
  min_x = goban_localwidth_to_user (gb, 0);
  min_y = goban_locallength_to_user (gb, 0);
  max_x = goban_localwidth_to_user (gb, gb->width + 1);
  max_y = goban_locallength_to_user (gb, gb->length + 1);
  image =
    cairo_image_surface_create_from_png
    ((gb->global.grid.background.image)->str);
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
goban_cairo_grid_background_imagepattern (cairo_t * cr, goban_t * gb)
{
  double max_x, max_y, min_x, min_y;
  cairo_surface_t *image;
  cairo_pattern_t *pattern;
  cairo_matrix_t matrix;
  cairo_save (cr);
  min_x = goban_localwidth_to_user (gb, 0);
  min_y = goban_locallength_to_user (gb, 0);
  max_x = goban_localwidth_to_user (gb, gb->width + 1);
  max_y = goban_locallength_to_user (gb, gb->length + 1);
  image =
    cairo_image_surface_create_from_png
    ((gb->global.grid.background.image)->str);
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
goban_grid_emptyneighbour (goban_t * gb, guint8 i, guint8 j)
{
  guint8 gridN, gridS, gridW, gridE, gridNW, gridNE, gridSW, gridSE;
  guint8 neighbour = 0;
  gridN = gb->local[i][j - 1].grid;
  gridS = gb->local[i][j + 1].grid;
  gridW = gb->local[i - 1][j].grid;
  gridE = gb->local[i + 1][j].grid;
  gridNW = gb->local[i - 1][j - 1].grid;
  gridNE = gb->local[i + 1][j - 1].grid;
  gridSW = gb->local[i - 1][j + 1].grid;
  gridSE = gb->local[i + 1][j + 1].grid;
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
goban_cairo_grid_liberty (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  guint8 grid, gridE, gridS, gridW, gridN;
  guint8 stone, stoneE, stoneS, stoneW, stoneN;
  guint8 detect, detectE, detectS, detectW, detectN;
  cairo_save (cr);
  cairo_translate (cr, goban_localwidth_to_user (gb, i),
		   goban_locallength_to_user (gb, j));
  cairo_scale (cr, gb->global.grid.liberty.spacing_width / 2.0,
	       gb->global.grid.liberty.spacing_length / 2.0);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
  goban_cairo_set_color (cr, gb->global.grid.liberty.color_stroke);
  grid = gb->local[i][j].grid;
  stone = gb->local[i][j].stone;
  gridE = gb->local[i + 1][j].grid;
  gridS = gb->local[i][j + 1].grid;
  gridW = gb->local[i - 1][j].grid;
  gridN = gb->local[i][j - 1].grid;
  cairo_move_to (cr, 0., 0.);
  if (stone == STONE_NONE || gb->global.grid.style_lighten == 0)
    {
      switch (gb->global.grid.style_boundary)
	{
	case 0:
	  cairo_set_line_width (cr, gb->global.grid.liberty.thickness);
	  if (gridE != GRID_NONE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	case 1:
	  detect = goban_grid_emptyneighbour (gb, i, j);
	  detectE = goban_grid_liberty_bound_east (detect);
	  detectS = goban_grid_liberty_bound_south (detect);
	  detectW = goban_grid_liberty_bound_west (detect);
	  detectN = goban_grid_liberty_bound_north (detect);
	  cairo_set_line_width (cr, gb->global.grid.liberty.thickness);
	  if (gridE != GRID_NONE && !(detectE))
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && !(detectS))
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && !(detectW))
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && !(detectN))
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  cairo_set_line_width (cr, gb->global.grid.liberty.thickness_bound);
	  if (gridE != GRID_NONE && detectE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && detectS)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && detectW)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && detectN)
	    goban_cairo_grid_liberty_E (cr, gb);
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
  else				/*else if (stone != STONE_NONE && gb->global.grid.style_lighten == 1) */
    {
      stoneE = gb->local[i + 1][j].stone;
      stoneS = gb->local[i][j + 1].stone;
      stoneW = gb->local[i - 1][j].stone;
      stoneN = gb->local[i][j - 1].stone;
      switch (gb->global.grid.style_boundary)
	{
	case 0:
	  cairo_set_line_width (cr, gb->global.grid.liberty.thickness);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  break;
	case 1:
	  detect = goban_grid_emptyneighbour (gb, i, j);
	  detectE = goban_grid_liberty_bound_east (detect);
	  detectS = goban_grid_liberty_bound_south (detect);
	  detectW = goban_grid_liberty_bound_west (detect);
	  detectN = goban_grid_liberty_bound_north (detect);
	  cairo_set_line_width (cr, gb->global.grid.liberty.thickness);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE && !(detectE))
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE && !(detectS))
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE && !(detectW))
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE && !(detectN))
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  cairo_close_path (cr);
	  cairo_save (cr);
	  cairo_uniform_stroke (cr);
	  cairo_restore (cr);
	  cairo_set_line_width (cr, gb->global.grid.liberty.thickness_bound);
	  if (gridE != GRID_NONE && stoneE == STONE_NONE && detectE)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridS != GRID_NONE && stoneS == STONE_NONE && detectS)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridW != GRID_NONE && stoneW == STONE_NONE && detectW)
	    goban_cairo_grid_liberty_E (cr, gb);
	  cairo_rotate (cr, G_PI_2);
	  if (gridN != GRID_NONE && stoneN == STONE_NONE && detectN)
	    goban_cairo_grid_liberty_E (cr, gb);
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
goban_cairo_grid_liberty_E (cairo_t * cr, goban_t * gb)
{
  switch (gb->global.grid.liberty.style)
    {
    case 0:
      goban_cairo_grid_line_E (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
goban_cairo_grid_line_E (cairo_t * cr)
{
  cairo_line_to (cr, 1., 0.);
  cairo_line_to (cr, 0., 0.);
}

gboolean
goban_grid_liberty_bound_east (guint8 neighbour)
{
  if ((neighbour & compass__N) || (neighbour & compass__S)
      || (neighbour & compass_NE) || (neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
goban_grid_liberty_bound_south (guint8 neighbour)
{
  if ((neighbour & compass__W) || (neighbour & compass__E)
      || (neighbour & compass_SW) || (neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
goban_grid_liberty_bound_west (guint8 neighbour)
{
  if ((neighbour & compass__N) || (neighbour & compass__S)
      || (neighbour & compass_NW) || (neighbour & compass_SW))
    return TRUE;
  else
    return FALSE;
}

gboolean
goban_grid_liberty_bound_north (guint8 neighbour)
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
goban_cairo_grid_starpoint (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  guint8 detect;
  cairo_save (cr);
  cairo_translate (cr, goban_localwidth_to_user (gb, i),
		   goban_locallength_to_user (gb, j));
  cairo_scale (cr, gb->global.grid.starpoint.radius,
	       gb->global.grid.starpoint.radius);
  goban_cairo_set_color (cr, gb->global.grid.starpoint.color_stroke);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
  cairo_set_line_width (cr, gb->global.grid.starpoint.thickness);
  cairo_move_to (cr, 0., 0.);
  detect = goban_grid_emptyneighbour (gb, i, j);
  if (goban_grid_starpoint_detect_SE (detect))
    goban_cairo_grid_starpoint_SE (cr, gb);
  cairo_rotate (cr, G_PI_2);
  if (goban_grid_starpoint_detect_SW (detect))
    goban_cairo_grid_starpoint_SE (cr, gb);
  cairo_rotate (cr, G_PI_2);
  if (goban_grid_starpoint_detect_NW (detect))
    goban_cairo_grid_starpoint_SE (cr, gb);
  cairo_rotate (cr, G_PI_2);
  if (goban_grid_starpoint_detect_NE (detect))
    goban_cairo_grid_starpoint_SE (cr, gb);
  cairo_rotate (cr, G_PI_2);
  cairo_fill_preserve (cr);
  cairo_uniform_stroke (cr);
  cairo_restore (cr);
}

gboolean
goban_grid_starpoint_detect_SE (guint8 neighbour)
{
  if (!(neighbour & compass__S) &&
      !(neighbour & compass__E) && !(neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
goban_grid_starpoint_detect_SW (guint8 neighbour)
{
  if (!(neighbour & compass__S) &&
      !(neighbour & compass__W) && !(neighbour & compass_SW))
    return TRUE;
  else
    return FALSE;
}

gboolean
goban_grid_starpoint_detect_NW (guint8 neighbour)
{
  if (!(neighbour & compass__N) &&
      !(neighbour & compass__W) && !(neighbour & compass_NW))
    return TRUE;
  else
    return FALSE;
}

gboolean
goban_grid_starpoint_detect_NE (guint8 neighbour)
{
  if (!(neighbour & compass__N) &&
      !(neighbour & compass__E) && !(neighbour & compass_NE))
    return TRUE;
  else
    return FALSE;
}

void
goban_cairo_grid_starpoint_SE (cairo_t * cr, goban_t * gb)
{
  switch (gb->global.grid.starpoint.style)
    {
    case 0:
      goban_cairo_grid_starpoint_SE_round (cr);
      break;
    case 1:
      goban_cairo_grid_starpoint_SE_square (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
goban_cairo_grid_starpoint_SE_round (cairo_t * cr)
{
  cairo_arc (cr, 0., 0., 1., 0., G_PI_2);
  cairo_close_path (cr);
}

void
goban_cairo_grid_starpoint_SE_square (cairo_t * cr)
{
  cairo_rectangle (cr, 0.0, 0.0, 1.0, 1.0);
}


/********************************************************************************/
// stone

void
goban_cairo_stone_fill (cairo_t * cr)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill (cr);
}

void
goban_cairo_stone_fill_and_stroke (cairo_t * cr, goban_t * gb)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill_preserve (cr);
  cairo_set_line_width (cr, gb->global.stone.thickness);
  goban_cairo_set_color (cr, gb->global.stone.color_black_stroke);
  cairo_uniform_stroke (cr);
}

void
goban_cairo_stone_black (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, goban_localwidth_to_user (gb, i),
		   goban_locallength_to_user (gb, j));
  switch (gb->global.stone.style)
    {
    case 0:
      goban_cairo_stone_black_plain (cr, gb);
      break;
    case 1:
      goban_cairo_stone_black_radial (cr, gb);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
  cairo_restore (cr);
}

void
goban_cairo_stone_black_plain (cairo_t * cr, goban_t * gb)
{
  cairo_scale (cr, gb->global.stone.radius - gb->global.stone.thickness,
	       gb->global.stone.radius - gb->global.stone.thickness);
  goban_cairo_set_color (cr, gb->global.stone.color_black_fill);
  goban_cairo_stone_fill_and_stroke (cr, gb);
}

void
goban_cairo_stone_black_radial (cairo_t * cr, goban_t * gb)
{
  cairo_scale (cr, gb->global.stone.radius, gb->global.stone.radius);
  cairo_set_source (cr, gb->global.stone.pattern_black_radial);
  goban_cairo_stone_fill (cr);
}


void
goban_cairo_stone_white (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, goban_localwidth_to_user (gb, i),
		   goban_locallength_to_user (gb, j));
  switch (gb->global.stone.style)
    {
    case 0:
      goban_cairo_stone_white_plain (cr, gb);
      break;
    case 1:
      goban_cairo_stone_white_radial (cr, gb);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
  cairo_restore (cr);
}

void
goban_cairo_stone_white_plain (cairo_t * cr, goban_t * gb)
{
  cairo_scale (cr, gb->global.stone.radius - gb->global.stone.thickness,
	       gb->global.stone.radius - gb->global.stone.thickness);
  goban_cairo_set_color (cr, gb->global.stone.color_white_fill);
  goban_cairo_stone_fill_and_stroke (cr, gb);
}

void
goban_cairo_stone_white_radial (cairo_t * cr, goban_t * gb)
{
  cairo_scale (cr, gb->global.stone.radius, gb->global.stone.radius);
  cairo_set_source (cr, gb->global.stone.pattern_white_radial);
  goban_cairo_stone_fill (cr);

}

/********************************************************************************/
// marker

void
goban_cairo_marker_context (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_translate (cr, goban_localwidth_to_user (gb, i),
		   goban_locallength_to_user (gb, j));
  cairo_scale (cr, gb->global.marker.radius, gb->global.marker.radius);
}

void
goban_cairo_marker_stroke (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_set_line_width (cr, gb->global.marker.thickness);
  cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
  cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
  switch (gb->local[i][j].stone)
    {
    case STONE_BLACK:
      goban_cairo_set_color (cr, gb->global.marker.color_black_fill);
      cairo_fill_preserve (cr);
      goban_cairo_set_color (cr, gb->global.marker.color_black_stroke);
      cairo_uniform_stroke (cr);
      break;
    case STONE_NONE:
      goban_cairo_set_color (cr, gb->global.marker.color_none_stroke);
      cairo_uniform_stroke (cr);
      break;
    case STONE_WHITE:
      goban_cairo_set_color (cr, gb->global.marker.color_white_fill);
      cairo_fill_preserve (cr);
      goban_cairo_set_color (cr, gb->global.marker.color_white_stroke);
      cairo_uniform_stroke (cr);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
goban_cairo_marker_cross (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_save (cr);
  goban_cairo_marker_context (cr, gb, i, j);
  cairo_move_to (cr, -G_SQRT2_2, -G_SQRT2_2);
  cairo_line_to (cr, +G_SQRT2_2, +G_SQRT2_2);
  cairo_move_to (cr, -G_SQRT2_2, +G_SQRT2_2);
  cairo_line_to (cr, +G_SQRT2_2, -G_SQRT2_2);
  goban_cairo_marker_stroke (cr, gb, i, j);
  cairo_restore (cr);
}

void
goban_cairo_marker_triangle (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_save (cr);
  goban_cairo_marker_context (cr, gb, i, j);
  cairo_move_to (cr, 0., -1.);
  cairo_line_to (cr, G_SQRT3_2, 0.5);
  cairo_line_to (cr, -G_SQRT3_2, 0.5);
  cairo_line_to (cr, 0., -1.);
  cairo_close_path (cr);
  goban_cairo_marker_stroke (cr, gb, i, j);
  cairo_restore (cr);
}

void
goban_cairo_marker_diamond (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_save (cr);
  goban_cairo_marker_context (cr, gb, i, j);
  cairo_move_to (cr, 0., -1.);
  cairo_line_to (cr, 1., 0.);
  cairo_line_to (cr, 0., 1.);
  cairo_line_to (cr, -1., 0.);
  cairo_close_path (cr);
  goban_cairo_marker_stroke (cr, gb, i, j);
  cairo_restore (cr);
}

void
goban_cairo_marker_pentagon_star (cairo_t * cr, goban_t * gb, guint8 i,
				  guint8 j)
{
  guint8 z;
  cairo_save (cr);
  goban_cairo_marker_context (cr, gb, i, j);
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
  goban_cairo_marker_stroke (cr, gb, i, j);
  cairo_restore (cr);
}

void
goban_cairo_marker_circle (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_save (cr);
  goban_cairo_marker_context (cr, gb, i, j);
  cairo_arc (cr, 0., 0., MAX_MARKER_RADIUS, 0., 2 * G_PI);
  cairo_close_path (cr);
  goban_cairo_marker_stroke (cr, gb, i, j);
  cairo_restore (cr);
}

void
goban_cairo_marker_square (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_save (cr);
  goban_cairo_marker_context (cr, gb, i, j);
  cairo_rectangle (cr, -MAX_MARKER_RADIUS, -MAX_MARKER_RADIUS,
		   2 * MAX_MARKER_RADIUS, 2 * MAX_MARKER_RADIUS);
  cairo_close_path (cr);
  goban_cairo_marker_stroke (cr, gb, i, j);
  cairo_restore (cr);
}


/********************************************************************************/
// color

void
goban_cairo_color_hl1 (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, goban_localwidth_to_user (gb, i),
		   goban_locallength_to_user (gb, j));
  cairo_scale (cr, gb->global.grid.liberty.spacing_width,
	       gb->global.grid.liberty.spacing_length);
  cairo_set_line_width (cr, gb->global.marker.thickness);
  cairo_rectangle (cr, -0.5, -0.5, 1., 1.);
  cairo_close_path (cr);
  goban_cairo_set_color (cr, gb->global.highlight.hl1);
  cairo_fill (cr);
  cairo_restore (cr);
}

/********************************************************************************/
// label

void
goban_pangocairo_label (cairo_t * cr, goban_t * gb, guint8 i, guint8 j)
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
  pango_layout_set_text (layout, (gb->local[i][j].label)->str, -1);
  pango_layout_get_extents (layout, &ink_rect, &logical_rect);
  size_x = ink_rect.width;
  size_y = ink_rect.height;
  delta_x = logical_rect.x - ink_rect.x;
  delta_y = logical_rect.y - ink_rect.y;
  pyta =
    sqrt (pow (0.5 * size_x / PANGO_SCALE, 2) +
	  pow (0.5 * size_y / PANGO_SCALE, 2));
  cairo_translate (cr, goban_localwidth_to_user (gb, i),
		   goban_locallength_to_user (gb, j));
  cairo_scale (cr,
	       gb->global.marker.radius / pyta,
	       gb->global.marker.radius / pyta);
  switch (gb->local[i][j].stone)
    {
    case STONE_BLACK:
      goban_cairo_set_color (cr, gb->global.label.color_black_stroke);
      break;
    case STONE_WHITE:
      goban_cairo_set_color (cr, gb->global.label.color_white_stroke);
      break;
    case STONE_NONE:
      goban_cairo_set_color (cr, gb->global.label.color_none_stroke);
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
// goban_cairo entry point

void
goban_cairo (cairo_t * cr, goban_t * gb)
{
  guint8 i, j;
  goban_cairo_grid_background (cr, gb);
  for (i = 1; i <= gb->width; i++)
    {
      for (j = 1; j <= gb->length; j++)
	{
	  switch (gb->local[i][j].grid)
	    {
	    case GRID_NONE:
	      break;
	    case GRID_PLAIN:
	      goban_cairo_grid_liberty (cr, gb, i, j);
	      break;
	    case GRID_STARPOINT:
	      goban_cairo_grid_liberty (cr, gb, i, j);
	      goban_cairo_grid_starpoint (cr, gb, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  switch (gb->local[i][j].stone)
	    {
	    case STONE_NONE:
	      break;
	    case STONE_BLACK:
	      goban_cairo_stone_black (cr, gb, i, j);
	      break;
	    case STONE_WHITE:
	      goban_cairo_stone_white (cr, gb, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  switch (gb->local[i][j].marker)
	    {
	    case MARKER_NONE:
	      break;
	    case MARKER_TRIANGLE:
	      goban_cairo_marker_triangle (cr, gb, i, j);
	      break;
	    case MARKER_DIAMOND:
	      goban_cairo_marker_diamond (cr, gb, i, j);
	      break;
	    case MARKER_CROSS:
	      goban_cairo_marker_cross (cr, gb, i, j);
	      break;
	    case MARKER_PENTAGON_STAR:
	      goban_cairo_marker_pentagon_star (cr, gb, i, j);
	      break;
	    case MARKER_CIRCLE:
	      goban_cairo_marker_circle (cr, gb, i, j);
	      break;
	    case MARKER_SQUARE:
	      goban_cairo_marker_square (cr, gb, i, j);
	      break;
	    default:
	      g_printf ("%d\n", __LINE__);
	      exit (EXIT_FAILURE);
	      break;
	    }
	  if ((g_strcmp0 ((gb->local[i][j].label)->str, "") != 0)
	      && (gb->local[i][j].marker == MARKER_NONE))
	    goban_pangocairo_label (cr, gb, i, j);
	  switch (gb->local[i][j].highlight)
	    {
	    case HIGHLIGHT_NONE:
	      break;
	    case HIGHLIGHT_HL1:
	      goban_cairo_color_hl1 (cr, gb, i, j);
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
  goban_t *gb;
  gb = goban_alloc (17, 17);
  gb->global.surface_width = 210 * (72 / 25.4);
  gb->global.surface_length = 297 * (72 / 25.4);
  goban_init (gb);
  surface =
    cairo_pdf_surface_create ("goban.pdf", gb->global.surface_width,
			      gb->global.surface_length);
  cr = cairo_create (surface);
  goban_cairo (cr, gb);
  cairo_surface_write_to_png (surface, "goban.png");
  cairo_destroy (cr);
  cairo_surface_destroy (surface);
  goban_free (gb);
  return 0;
}
