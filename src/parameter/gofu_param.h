#include <glib.h>

typedef struct _gofu_color_rgba
{
  gdouble red;
  gdouble green;
  gdouble blue;
  gdouble alpha;
} gofu_color_rgba_t;

typedef struct _gofu_param_grid_background
{
  guint8 style;
  gofu_color_rgba_t color_fill;
  GString *image;
} gofu_param_grid_background_t;

typedef struct _gofu_param_description
{
  guint8 number_line_width;
  guint8 number_line_length;
  gdouble gofu_width;
  gdouble gofu_length;
  gdouble line_spacing_width;
  gdouble line_spacing_length;
} gofu_param_description_t;

typedef struct _gofu_param_ratio_size
{
  gdouble marker_stone;
  gdouble starpoint_marker;
  gdouble bound_starpoint;
  gdouble unbound_bound;
} gofu_param_ratio_size_t;

typedef struct _gofu_param_ratio_thickness
{
  gdouble unbound_bound;
  gdouble unbound_starpoint;
  gdouble unbound_marker;
  gdouble unbound_stone;

} gofu_param_ratio_thickness_t;

typedef struct _gofu_param_grid_liberty
{
  gdouble thickness;
  gdouble thickness_bound;
  gdouble spacing_width;
  gdouble spacing_length;
  gdouble margin_width;
  gdouble margin_length;
  guint8 style;
  gofu_color_rgba_t color_stroke;
} gofu_param_grid_liberty_t;

typedef struct _gofu_param_grid_starpoint
{
  gdouble thickness;
  gdouble radius;
  guint8 style;
  gofu_color_rgba_t color_stroke;
} gofu_param_grid_starpoint_t;

typedef struct _gofu_param_grid
{
  guint8 style_boundary;
  guint8 style_lighten;
  gofu_param_grid_background_t background;
  gofu_param_grid_liberty_t liberty;
  gofu_param_grid_starpoint_t starpoint;
} gofu_param_grid_t;

typedef struct _gofu_param_stone
{
  gdouble thickness;
  gdouble radius;
  guint8 style;
  gofu_color_rgba_t color_white_stroke;
  gofu_color_rgba_t color_white_fill;
  gofu_color_rgba_t color_black_stroke;
  gofu_color_rgba_t color_black_fill;
} gofu_param_stone_t;

typedef struct _gofu_param_marker
{
  gdouble thickness;
  gdouble radius;
  guint8 style;
  gofu_color_rgba_t color_white_stroke;
  gofu_color_rgba_t color_white_fill;
  gofu_color_rgba_t color_black_stroke;
  gofu_color_rgba_t color_black_fill;
  gofu_color_rgba_t color_none_stroke;
} gofu_param_marker_t;

typedef struct _gofu_param_highlight
{
  gofu_color_rgba_t hl1;
} gofu_param_highlight_t;

typedef struct _gofu_param_label
{
  gofu_color_rgba_t color_white_stroke;
  gofu_color_rgba_t color_black_stroke;
  gofu_color_rgba_t color_none_stroke;
} gofu_param_label_t;

typedef struct _gofu_param
{
  gdouble surface_width;
  gdouble surface_length;
  gofu_param_grid_t grid;
  gofu_param_stone_t stone;
  gofu_param_marker_t marker;
  gofu_param_highlight_t highlight;
  gofu_param_label_t label;
} gofu_param_t;

void gofu_param (gofu_param_t *);
gdouble box_in_box (gdouble, gdouble, gdouble, gdouble);
void gofu_param_dimension (gofu_param_t *, gofu_param_description_t *,
			   gofu_param_ratio_size_t *,
			   gofu_param_ratio_thickness_t *);
void gofu_param_attribute (gofu_param_t *);
void gofu_param_grid (gofu_param_t *);
void gofu_param_grid_background (gofu_param_t *);
void gofu_param_grid_liberty (gofu_param_t *);
void gofu_param_grid_starpoint (gofu_param_t *);
void gofu_param_stone (gofu_param_t *);
void gofu_param_marker (gofu_param_t *);
void gofu_param_label (gofu_param_t *);
void gofu_param_highlight (gofu_param_t *);
void gofu_param_color (gofu_color_rgba_t *, guint8, guint8, guint8, guint8);
