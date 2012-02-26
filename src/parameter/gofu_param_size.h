#include <glib.h>

#ifndef GOFU_PARAM_SIZE_T
#define GOFU_PARAM_SIZE_T

typedef struct _gofu_param_size_description
{
  guint8 number_line_width;
  guint8 number_line_length;
  gdouble surface_width;
  gdouble surface_length;
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


typedef struct _gofu_param_size_grid_margin
{
  gdouble width;
  gdouble length;
} gofu_param_size_grid_margin_t;

typedef struct _gofu_param_size_grid_liberty
{
  gdouble thickness;
  gdouble thickness_bound;
  gdouble spacing_width_2;
  gdouble spacing_length_2;
} gofu_param_size_grid_liberty_t;

typedef struct _gofu_param_size_grid_starpoint
{
  gdouble thickness;
  gdouble radius;
  GSList *list;
} gofu_param_size_grid_starpoint_t;

typedef struct _gofu_pos
{
  gdouble s;
  gdouble tx;
  gdouble ty;
} gofu_pos_t;

typedef struct _gofu_param_size_grid
{
  gofu_param_size_grid_margin_t margin;
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
  gofu_pos_t pos;
  gofu_param_size_grid_t grid;
  gofu_param_size_stone_t stone;
  gofu_param_size_marker_t marker;
} gofu_param_size_t;

#endif // GOFU_PARAM_SIZE_T

gofu_param_size_t *gofu_param_size_alloc (void);
void gofu_param_size_free (gofu_param_size_t * gp);
void gofu_param_size_init (gofu_param_size_t *, guint8, guint8, gdouble,
			   gdouble);
void box_in_box (gofu_pos_t *, gdouble, gdouble, gdouble, gdouble);
void gofu_param_size_dimension (gofu_param_size_t *,
				guint8, guint8,
				gdouble, gdouble,
				gofu_param_size_description_t *,
				gofu_param_size_ratio_size_t *,
				gofu_param_size_ratio_thickness_t *);
void gofu_param_size_starpoint (gofu_param_size_t *, guint8, guint8);
GSList *gofu_grid_starpoint_tengen (GSList *, guint8, guint8);
guint8 gofu_grid_starpoint_corner_delta (guint8, guint8);
GSList *gofu_grid_starpoint_corner (GSList *, guint8, guint8, guint8);
GSList *gofu_grid_starpoint_side (GSList *, guint8, guint8, guint8);
GSList *gofu_list_prepend_xy (GSList *, guint8, guint8);
