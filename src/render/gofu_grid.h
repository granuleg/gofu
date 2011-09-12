#include "gofu_render.h"

guint8 gofu_grid_emptyneighbour (gofu_t *, guint8, guint8);
gboolean gofu_grid_liberty_bound_detect_E (guint8);
gboolean gofu_grid_liberty_bound_detect_S (guint8);
gboolean gofu_grid_liberty_bound_detect_W (guint8);
gboolean gofu_grid_liberty_bound_detect_N (guint8);
gboolean gofu_grid_starpoint_detect_SE (guint8);
gboolean gofu_grid_starpoint_detect_SW (guint8);
gboolean gofu_grid_starpoint_detect_NW (guint8);
gboolean gofu_grid_starpoint_detect_NE (guint8);
