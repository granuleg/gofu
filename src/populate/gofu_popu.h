typedef enum _gofu_popu_enum
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
} gofu_popu_enum_t;

typedef struct _gofu_popu
{
  guint8 grid;
  guint8 stone;
  guint8 marker;
  guint8 highlight;
  GString *label;
} gofu_popu_t;

void gofu_popu_init (gofu_t *);
void gofu_popu_init_grid (gofu_t *);
void gofu_popu_init_grid_liberty (gofu_t *);
void gofu_popu_init_grid_starpoint (gofu_t *);
void gofu_popu_init_grid_starpoint_tengen (gofu_t *);
guint8 gofu_popu_init_grid_starpoint_corner_delta (gofu_t *);
void gofu_popu_init_grid_starpoint_corner (gofu_t *, guint8);
void gofu_popu_init_grid_starpoint_side (gofu_t *, guint8);
void gofu_popu_init_stone (gofu_t *);
void gofu_popu_init_marker (gofu_t *);
void gofu_popu_init_label (gofu_t *);
void gofu_popu_init_highlight (gofu_t *);
void gofu_popu_init_grid_random (gofu_t *);
void gofu_popu_init_stone_random (gofu_t *);
void gofu_popu_init_marker_random (gofu_t *);
void gofu_popu_init_label_random (gofu_t *);
void gofu_popu_init_highlight_random (gofu_t *);
