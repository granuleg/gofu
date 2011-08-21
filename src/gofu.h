#include "gofu_parameter.h"
#include "gofu_populate.h"

typedef struct _gofu
{
  guint8 width;
  guint8 length;
  gofu_param_t param;
  gofu_popu_t **popu;
} gofu_t;


/*handle structure dynamicaly*/
gofu_t *gofu_alloc (guint8, guint8);
gpointer *gofu_alloc_popu (gsize, guint8, guint8);
void gofu_free (gofu_t *);
void gofu_free_popu_internal (gofu_t *);
void gofu_free_popu (gpointer *, guint8);
void gofu_free_param_internal (gofu_t *);

/*init structure*/
void gofu_init (gofu_t *);
gdouble box_in_box (gdouble, gdouble, gdouble, gdouble);
void gofu_init_param_parameter (gofu_t *, gofu_param_description_t *,
				  gofu_param_ratio_size_t *,
				  gofu_param_ratio_thickness_t *);
void gofu_init_param_attribute (gofu_t *);
void gofu_init_param_grid (gofu_t *);
void gofu_init_param_grid_background (gofu_t *);
void gofu_init_param_grid_liberty (gofu_t *);
void gofu_init_param_grid_starpoint (gofu_t *);
void gofu_init_param_stone (gofu_t *);
void gofu_init_param_marker (gofu_t *);
void gofu_init_param_label (gofu_t *);
void gofu_init_param_highlight (gofu_t *);
void gofu_init_popu (gofu_t *);
void gofu_init_popu_grid (gofu_t *);
void gofu_init_popu_grid_liberty (gofu_t *);
void gofu_init_popu_grid_starpoint (gofu_t *);
void gofu_init_popu_grid_starpoint_tengen (gofu_t *);
guint8 gofu_init_popu_grid_starpoint_corner_delta (gofu_t *);
void gofu_init_popu_grid_starpoint_corner (gofu_t *, guint8);
void gofu_init_popu_grid_starpoint_side (gofu_t *, guint8);
void gofu_init_popu_stone (gofu_t *);
void gofu_init_popu_marker (gofu_t *);
void gofu_init_popu_label (gofu_t *);
void gofu_init_popu_highlight (gofu_t *);
void gofu_init_popu_grid_random (gofu_t *);
void gofu_init_popu_stone_random (gofu_t *);
void gofu_init_popu_marker_random (gofu_t *);
void gofu_init_popu_label_random (gofu_t *);
void gofu_init_popu_highlight_random (gofu_t *);

/*graphics stuff*/
void gofu_SL_stdout (gofu_t *);

void cairo_uniform_stroke (cairo_t * cr);
void gofu_init_param_color (gofu_color_rgba_t *, guint8, guint8,
			      guint8, guint8);
void gofu_cairo_set_color (cairo_t *, gofu_color_rgba_t);

gdouble gofu_popuwidth_to_user (gofu_t *, guint8);
gdouble gofu_populength_to_user (gofu_t *, guint8);

void gofu_cairo_grid_background (cairo_t *, gofu_t *);
void gofu_cairo_grid_background_color (cairo_t *, gofu_t *);
void gofu_cairo_grid_background_image (cairo_t *, gofu_t *);
void gofu_cairo_grid_background_imagepattern (cairo_t *, gofu_t *);

guint8 gofu_grid_emptyneighbour (gofu_t *, guint8, guint8);
void gofu_cairo_grid_liberty (cairo_t *, gofu_t *, guint8, guint8);
void gofu_cairo_grid_liberty_E (cairo_t *, gofu_t *);
void gofu_cairo_grid_line_E (cairo_t *);
gboolean gofu_grid_liberty_bound_north (guint8);
gboolean gofu_grid_liberty_bound_south (guint8);
gboolean gofu_grid_liberty_bound_east (guint8);
gboolean gofu_grid_liberty_bound_west (guint8);

void gofu_cairo_grid_starpoint (cairo_t *, gofu_t *, guint8, guint8);
gboolean gofu_grid_starpoint_detect_SE (guint8);
gboolean gofu_grid_starpoint_detect_SW (guint8);
gboolean gofu_grid_starpoint_detect_NW (guint8);
gboolean gofu_grid_starpoint_detect_NE (guint8);
void gofu_cairo_grid_starpoint_SE (cairo_t *, gofu_t *);
void gofu_cairo_grid_starpoint_SE_round (cairo_t *);
void gofu_cairo_grid_starpoint_SE_square (cairo_t *);

void gofu_cairo_stone_fill (cairo_t *);
void gofu_cairo_stone_fill_and_stroke (cairo_t *, gofu_t *);
void gofu_cairo_stone_black (cairo_t *, gofu_t *, guint8, guint8);
void gofu_cairo_stone_black_plain (cairo_t *, gofu_t *);
void gofu_cairo_stone_black_radial (cairo_t *, gofu_t *);
void gofu_cairo_stone_white (cairo_t *, gofu_t *, guint8, guint8);
void gofu_cairo_stone_white_plain (cairo_t *, gofu_t *);
void gofu_cairo_stone_white_radial (cairo_t *, gofu_t *);

void gofu_cairo_marker_context (cairo_t *, gofu_t *, guint8, guint8);
void gofu_cairo_marker_stroke (cairo_t *, gofu_t *, guint8, guint8);
void gofu_cairo_marker_cross (cairo_t *, gofu_t *, guint8, guint8);
void gofu_cairo_marker_triangle (cairo_t *, gofu_t *, guint8, guint8);
void gofu_cairo_marker_diamond (cairo_t *, gofu_t *, guint8, guint8);
void gofu_cairo_marker_pentagon (cairo_t *, gofu_t *, guint8, guint8);

void gofu_pangocairo_label (cairo_t *, gofu_t *, guint8, guint8);

void gofu_cairo (cairo_t *, gofu_t *);
