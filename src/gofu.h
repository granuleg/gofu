#include "./parameter/gofu_param.h"
#include "./populate/gofu_popu.h"


typedef struct _gofu
{
  guint8 width;
  guint8 length;
  gofu_param_t param;
  gofu_popu_t **popu;
} gofu_t;



/*graphics stuff*/
void gofu_SL_stdout (gofu_t *);

void cairo_uniform_stroke (cairo_t * cr);

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
