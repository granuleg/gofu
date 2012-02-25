#include <glib.h>

#ifndef GOFU_PARAM_T
#define GOFU_PARAM_T

typedef enum _gofu_param_enum
{
  GRID_BACKGROUND_NO,
  GRID_BACKGROUND_COLOR,
  GRID_BACKGROUND_IMAGE,
  GRID_LIBERTY_NO,
  GRID_LIBERTY_LINE,
  GRID_LIBERTY_BOUND,
  GRID_STARPOINT_NO,
  GRID_STARPOINT_ROUND,
  GRID_STARPOINT_SQUARE,
  STONE_NO,
  STONE_PLAIN,
  STONE_IMAGE,
  MARKER_NO,
  MARKER_PLAIN,
  LABEL_NO,
  LABEL_PLAIN
} gofu_param_enum_t;

typedef struct _gofu_color
{
  gdouble red;
  gdouble green;
  gdouble blue;
} gofu_color_t;

typedef struct _gofu_param_background
{
  gofu_param_enum_t style;
  gofu_color_t color;
  GString *image;
} gofu_param_background_t;

typedef struct _gofu_param_grid_liberty
{
  gofu_param_enum_t style;
  gofu_color_t color;
} gofu_param_grid_liberty_t;

typedef struct _gofu_param_grid_starpoint
{
  gofu_param_enum_t style;
  gofu_color_t color;
} gofu_param_grid_starpoint_t;

typedef struct _gofu_param_grid
{
  gboolean boundary;
  gofu_param_grid_liberty_t liberty;
  gofu_param_grid_starpoint_t starpoint;
} gofu_param_grid_t;

typedef struct _gofu_param_stone
{
  gofu_param_enum_t style;
  gofu_color_t color_black_fill;
  gofu_color_t color_black_stroke;
  gofu_color_t color_white_fill;
  gofu_color_t color_white_stroke;
  GString *image_black;
  GString *image_white;
} gofu_param_stone_t;

typedef struct _gofu_param_marker
{
  gofu_param_enum_t style;
  gofu_color_t color_black_fill;
  gofu_color_t color_black_stroke;
  gofu_color_t color_none_stroke;
  gofu_color_t color_white_fill;
  gofu_color_t color_white_stroke;
} gofu_param_marker_t;

typedef struct _gofu_param_label
{
  gofu_param_enum_t style;
  /*font description */
  gofu_color_t color_black_stroke;
  gofu_color_t color_none_stroke;
  gofu_color_t color_white_stroke;
} gofu_param_label_t;

typedef struct _gofu_param
{
  gofu_param_background_t background;
  gofu_param_grid_t grid;
  gofu_param_stone_t stone;
  gofu_param_marker_t marker;
  gofu_param_label_t label;
} gofu_param_t;

#endif // GOFU_PARAM_T

gofu_param_t *gofu_param_alloc ();
void gofu_param_free (gofu_param_t *);
void gofu_param_free_string (gofu_param_t *);
void gofu_param_init (gofu_param_t *);
void gofu_param_init_background (gofu_param_t *);
void gofu_param_init_grid (gofu_param_t *);
void gofu_param_init_grid_liberty (gofu_param_t *);
void gofu_param_init_grid_starpoint (gofu_param_t *);
void gofu_param_init_stone (gofu_param_t *);
void gofu_param_init_marker (gofu_param_t *);
void gofu_param_init_label (gofu_param_t *);
void gofu_param_set_color (gofu_color_t *, guint8, guint8, guint8);
void gofu_param_set_color_white (gofu_color_t *);
void gofu_param_set_color_black (gofu_color_t *);
