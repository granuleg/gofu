#include <config.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include <glib/gprintf.h>
#include <pango/pangocairo.h>
#include <cairo/cairo-pdf.h>
#include <cairo/cairo-svg.h>
#include <cairo/cairo-ps.h>

typedef enum _goban_enum
{
  GRID_NONE,
  GRID_PLAIN,
  GRID_STARPOINT,
  STONE_NONE,
  STONE_BLACK,
  STONE_WHITE,
  MARKER_NONE,
  MARKER_CROSS,
  MARKER_TRIANGLE,
  MARKER_DIAMOND,
  MARKER_PENTAGON_STAR,
  MARKER_CIRCLE,
  MARKER_SQUARE,
  HIGHLIGHT_NONE,
  HIGHLIGHT_HL1
} goban_enum_t;

typedef struct _goban_color_rgba
{
  gdouble red;
  gdouble green;
  gdouble blue;
  gdouble alpha;
} goban_color_rgba_t;

typedef struct _goban_local
{
  guint8 grid;
  guint8 stone;
  guint8 marker;
  guint8 highlight;
  GString *label;
} goban_local_t;

typedef struct _goban_global_grid_background
{
  guint8 style;
  goban_color_rgba_t color_fill;
  GString *image;
} goban_global_grid_background_t;


typedef struct _goban_global_description
{
  guint8 number_line_width;
  guint8 number_line_length;
  gdouble goban_width;
  gdouble goban_length;
  gdouble line_spacing_width;
  gdouble line_spacing_length;
} goban_global_description_t;

typedef struct _goban_global_ratio_size
{
  gdouble marker_stone;
  gdouble starpoint_marker;
  gdouble bound_starpoint;
  gdouble unbound_bound;
} goban_global_ratio_size_t;

typedef struct _goban_global_ratio_thickness
{
  gdouble unbound_bound;
  gdouble unbound_starpoint;
  gdouble unbound_marker;
  gdouble unbound_stone;

} goban_global_ratio_thickness_t;

typedef struct _goban_global_grid_liberty
{
  gdouble thickness;
  gdouble thickness_bound;
  gdouble spacing_width;
  gdouble spacing_length;
  gdouble margin_width;
  gdouble margin_length;
  guint8 style;
  goban_color_rgba_t color_stroke;
} goban_global_grid_liberty_t;

typedef struct _goban_global_grid_starpoint
{
  gdouble thickness;
  gdouble radius;
  guint8 style;
  goban_color_rgba_t color_stroke;
} goban_global_grid_starpoint_t;

typedef struct _goban_global_grid
{
  guint8 style_boundary;
  guint8 style_lighten;
  goban_global_grid_background_t background;
  goban_global_grid_liberty_t liberty;
  goban_global_grid_starpoint_t starpoint;
} goban_global_grid_t;

typedef struct _goban_global_stone
{
  gdouble thickness;
  gdouble radius;
  guint8 style;
  goban_color_rgba_t color_white_stroke;
  goban_color_rgba_t color_white_fill;
  cairo_pattern_t *pattern_white_radial;
  goban_color_rgba_t color_black_stroke;
  goban_color_rgba_t color_black_fill;
  cairo_pattern_t *pattern_black_radial;
} goban_global_stone_t;

typedef struct _goban_global_marker
{
  gdouble thickness;
  gdouble radius;
  guint8 style;
  goban_color_rgba_t color_white_stroke;
  goban_color_rgba_t color_white_fill;
  goban_color_rgba_t color_black_stroke;
  goban_color_rgba_t color_black_fill;
  goban_color_rgba_t color_none_stroke;
} goban_global_marker_t;

typedef struct _goban_global_highlight
{
  goban_color_rgba_t hl1;
} goban_global_highlight_t;

typedef struct _goban_global_label
{
  goban_color_rgba_t color_white_stroke;
  goban_color_rgba_t color_black_stroke;
  goban_color_rgba_t color_none_stroke;
} goban_global_label_t;

typedef struct _goban_global
{
  gdouble surface_width;
  gdouble surface_length;
  goban_global_grid_t grid;
  goban_global_stone_t stone;
  goban_global_marker_t marker;
  goban_global_highlight_t highlight;
  goban_global_label_t label;
} goban_global_t;

typedef struct _goban
{
  guint8 width;
  guint8 length;
  goban_global_t global;
  goban_local_t **local;
} goban_t;


/*handle structure dynamicaly*/
goban_t *goban_alloc (guint8, guint8);
gpointer *goban_alloc_local (gsize, guint8, guint8);
void goban_free (goban_t *);
void goban_free_local_internal (goban_t *);
void goban_free_local (gpointer *, guint8);
void goban_free_global_internal (goban_t *);

/*init structure*/
void goban_init (goban_t *);
gdouble box_in_box (gdouble, gdouble, gdouble, gdouble);
void goban_init_global_parameter (goban_t *, goban_global_description_t *,
				  goban_global_ratio_size_t *,
				  goban_global_ratio_thickness_t *);
void goban_init_global_attribute (goban_t *);
void goban_init_global_grid (goban_t *);
void goban_init_global_grid_background (goban_t *);
void goban_init_global_grid_liberty (goban_t *);
void goban_init_global_grid_starpoint (goban_t *);
void goban_init_global_stone (goban_t *);
void goban_init_global_marker (goban_t *);
void goban_init_global_label (goban_t *);
void goban_init_global_highlight (goban_t *);
void goban_init_local (goban_t *);
void goban_init_local_grid (goban_t *);
void goban_init_local_grid_liberty (goban_t *);
void goban_init_local_grid_starpoint (goban_t *);
void goban_init_local_grid_starpoint_tengen (goban_t *);
guint8 goban_init_local_grid_starpoint_corner_delta (goban_t *);
void goban_init_local_grid_starpoint_corner (goban_t *, guint8);
void goban_init_local_grid_starpoint_side (goban_t *, guint8);
void goban_init_local_stone (goban_t *);
void goban_init_local_marker (goban_t *);
void goban_init_local_label (goban_t *);
void goban_init_local_highlight (goban_t *);
void goban_init_local_grid_random (goban_t *);
void goban_init_local_stone_random (goban_t *);
void goban_init_local_marker_random (goban_t *);
void goban_init_local_label_random (goban_t *);
void goban_init_local_highlight_random (goban_t *);

/*graphics stuff*/
void goban_SL_stdout (goban_t *);

void cairo_uniform_stroke (cairo_t * cr);
void goban_init_global_color (goban_color_rgba_t *, guint8, guint8,
			      guint8, guint8);
void goban_cairo_set_color (cairo_t *, goban_color_rgba_t);

gdouble goban_localwidth_to_user (goban_t *, guint8);
gdouble goban_locallength_to_user (goban_t *, guint8);

void goban_cairo_grid_background (cairo_t *, goban_t *);
void goban_cairo_grid_background_color (cairo_t *, goban_t *);
void goban_cairo_grid_background_image (cairo_t *, goban_t *);
void goban_cairo_grid_background_imagepattern (cairo_t *, goban_t *);

guint8 goban_grid_emptyneighbour (goban_t *, guint8, guint8);
void goban_cairo_grid_liberty (cairo_t *, goban_t *, guint8, guint8);
void goban_cairo_grid_liberty_E (cairo_t *, goban_t *);
void goban_cairo_grid_line_E (cairo_t *);
gboolean goban_grid_liberty_bound_north (guint8);
gboolean goban_grid_liberty_bound_south (guint8);
gboolean goban_grid_liberty_bound_east (guint8);
gboolean goban_grid_liberty_bound_west (guint8);

void goban_cairo_grid_starpoint (cairo_t *, goban_t *, guint8, guint8);
gboolean goban_grid_starpoint_detect_SE (guint8);
gboolean goban_grid_starpoint_detect_SW (guint8);
gboolean goban_grid_starpoint_detect_NW (guint8);
gboolean goban_grid_starpoint_detect_NE (guint8);
void goban_cairo_grid_starpoint_SE (cairo_t *, goban_t *);
void goban_cairo_grid_starpoint_SE_round (cairo_t *);
void goban_cairo_grid_starpoint_SE_square (cairo_t *);

void goban_cairo_stone_fill (cairo_t *);
void goban_cairo_stone_fill_and_stroke (cairo_t *, goban_t *);
void goban_cairo_stone_black (cairo_t *, goban_t *, guint8, guint8);
void goban_cairo_stone_black_plain (cairo_t *, goban_t *);
void goban_cairo_stone_black_radial (cairo_t *, goban_t *);
void goban_cairo_stone_white (cairo_t *, goban_t *, guint8, guint8);
void goban_cairo_stone_white_plain (cairo_t *, goban_t *);
void goban_cairo_stone_white_radial (cairo_t *, goban_t *);

void goban_cairo_marker_context (cairo_t *, goban_t *, guint8, guint8);
void goban_cairo_marker_stroke (cairo_t *, goban_t *, guint8, guint8);
void goban_cairo_marker_cross (cairo_t *, goban_t *, guint8, guint8);
void goban_cairo_marker_triangle (cairo_t *, goban_t *, guint8, guint8);
void goban_cairo_marker_diamond (cairo_t *, goban_t *, guint8, guint8);
void goban_cairo_marker_pentagon (cairo_t *, goban_t *, guint8, guint8);

void goban_pangocairo_label (cairo_t *, goban_t *, guint8, guint8);

void goban_cairo (cairo_t *, goban_t *);
