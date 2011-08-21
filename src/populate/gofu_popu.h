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
