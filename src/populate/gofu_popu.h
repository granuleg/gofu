#include <glib.h>
/*why stdio and sdlib are here on a glib dependancy files*/
#include <stdio.h>
#include <stdlib.h>

#ifndef GOFU_POPU_T
#define GOFU_POPU_T

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
  gofu_popu_elem_t **elem;
} gofu_popu_t;

#endif // GOFU_POPU_T

gofu_popu_t *gofu_popu_alloc (guint8, guint8);
gpointer *gofu_popu_alloc_elem (gsize, guint8, guint8);

void gofu_popu_free (gofu_popu_t *);
void gofu_popu_free_string (gofu_popu_t *);
void gofu_popu_free_elem (gpointer *, guint8);

void gofu_popu_init (gofu_popu_t *);
void gofu_popu_init_grid (gofu_popu_t *);
void gofu_popu_init_grid_liberty (gofu_popu_t *);
void gofu_popu_init_grid_starpoint (gofu_popu_t *);
void gofu_popu_init_grid_starpoint_tengen (gofu_popu_t *);
guint8 gofu_popu_init_grid_starpoint_corner_delta (gofu_popu_t *);
void gofu_popu_init_grid_starpoint_corner (gofu_popu_t *, guint8);
void gofu_popu_init_grid_starpoint_side (gofu_popu_t *, guint8);
void gofu_popu_init_stone (gofu_popu_t *);
void gofu_popu_init_marker (gofu_popu_t *);
void gofu_popu_init_label (gofu_popu_t *);
void gofu_popu_init_highlight (gofu_popu_t *);
void gofu_popu_init_grid_random (gofu_popu_t *);
void gofu_popu_init_stone_random (gofu_popu_t *);
void gofu_popu_init_marker_random (gofu_popu_t *);
void gofu_popu_init_label_random (gofu_popu_t *);
void gofu_popu_init_highlight_random (gofu_popu_t *);
