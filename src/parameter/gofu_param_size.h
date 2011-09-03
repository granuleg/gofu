#include <glib.h>

typedef struct _gofu_param_size_description
{
  guint8 number_line_width;
  guint8 number_line_length;
  gdouble gofu_width;
  gdouble gofu_length;
  gdouble line_spacing_width;
  gdouble line_spacing_length;
} gofu_param_size_description_t;

typedef struct _gofu_param_size_ratio_size
{
  gdouble marker_stone;
  gdouble starpoint_marker;
  gdouble bound_starpoint;
  gdouble unbound_bound;
} gofu_param_size_ratio_size_t;

typedef struct _gofu_param_size_ratio_thickness
{
  gdouble unbound_bound;
  gdouble unbound_starpoint;
  gdouble unbound_marker;
  gdouble unbound_stone;
} gofu_param_size_ratio_thickness_t;

typedef struct _gofu_param_size_grid_liberty
{
  gdouble thickness;
  gdouble thickness_bound;
  gdouble spacing_width;
  gdouble spacing_length;
  gdouble margin_width;
  gdouble margin_length;
} gofu_param_size_grid_liberty_t;

typedef struct _gofu_param_size_grid_starpoint
{
  gdouble thickness;
  gdouble radius;
} gofu_param_size_grid_starpoint_t;

typedef struct _gofu_param_size_grid
{
  gofu_param_size_grid_liberty_t liberty;
  gofu_param_size_grid_starpoint_t starpoint;
} gofu_param_size_grid_t;

typedef struct _gofu_param_size_stone
{
  gdouble thickness;
  gdouble radius;
} gofu_param_size_stone_t;

typedef struct _gofu_param_size_marker
{
  gdouble thickness;
  gdouble radius;
} gofu_param_size_marker_t;

typedef struct _gofu_param_size
{
  gdouble surface_width;
  gdouble surface_length;
  gofu_param_size_grid_t grid;
  gofu_param_size_stone_t stone;
  gofu_param_size_marker_t marker;
} gofu_param_size_t;


gofu_param_size_t *gofu_param_size_alloc (void);
void gofu_param_size_free (gofu_param_size_t * gp);
void gofu_param_size_init (gofu_param_size_t *, guint8, guint8);
gdouble box_in_box (gdouble, gdouble, gdouble, gdouble);
void gofu_param_size_dimension (gofu_param_size_t *, guint8, guint8,
				gofu_param_size_description_t *,
				gofu_param_size_ratio_size_t *,
				gofu_param_size_ratio_thickness_t *);
