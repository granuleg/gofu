guint8 gofu_grid_emptyneighbour (gofu_t *, guint8, guint8);
gboolean gofu_grid_liberty_bound_east (guint8);
gboolean gofu_grid_liberty_bound_south (guint8);
gboolean gofu_grid_liberty_bound_west (guint8);
gboolean gofu_grid_liberty_bound_north (guint8);
gboolean gofu_grid_starpoint_detect_SE (guint8);
gboolean gofu_grid_starpoint_detect_SW (guint8);
gboolean gofu_grid_starpoint_detect_NW (guint8);
gboolean gofu_grid_starpoint_detect_NE (guint8);
gdouble gofu_popuwidth_to_user (gofu_t *, guint8);
gdouble gofu_populength_to_user (gofu_t *, guint8);
