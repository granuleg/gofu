#include <glib.h>

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

typedef struct _gofu_popu_elem
{
  guint8 grid;
  guint8 stone;
  guint8 marker;
  guint8 highlight;
  GString *label;
} gofu_popu_elem_t;

typedef struct _gofu_popu
{
  guint8 width;
  guint8 length;
  gofu_popu_elem_t **gp;
} gofu_popu_t;

void gofu_popu (gofu_popu_t *);
void gofu_popu_grid (gofu_popu_t *);
void gofu_popu_grid_liberty (gofu_popu_t *);
void gofu_popu_grid_starpoint (gofu_popu_t *);
void gofu_popu_grid_starpoint_tengen (gofu_popu_t *);
guint8 gofu_popu_grid_starpoint_corner_delta (gofu_popu_t *);
void gofu_popu_grid_starpoint_corner (gofu_popu_t *, guint8);
void gofu_popu_grid_starpoint_side (gofu_popu_t *, guint8);
void gofu_popu_stone (gofu_popu_t *);
void gofu_popu_marker (gofu_popu_t *);
void gofu_popu_label (gofu_popu_t *);
void gofu_popu_highlight (gofu_popu_t *);
void gofu_popu_grid_random (gofu_popu_t *);
void gofu_popu_stone_random (gofu_popu_t *);
void gofu_popu_marker_random (gofu_popu_t *);
void gofu_popu_label_random (gofu_popu_t *);
void gofu_popu_highlight_random (gofu_popu_t *);
