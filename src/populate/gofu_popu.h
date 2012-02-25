#include <glib.h>
/*why stdio and sdlib are here on a glib dependancy files*/
#include <stdio.h>
#include <stdlib.h>

#ifndef GOFU_POPU_T
#define GOFU_POPU_T

typedef enum _gofu_popu_enum
{
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
} gofu_popu_enum_t;

typedef struct _gofu_popu_elem
{
  guint8 stone;
  guint8 marker;
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
void gofu_popu_init_stone (gofu_popu_t *);
void gofu_popu_init_marker (gofu_popu_t *);
void gofu_popu_init_label (gofu_popu_t *);

void gofu_popu_init_random (gofu_popu_t *);
void gofu_popu_init_stone_random (gofu_popu_t *);
void gofu_popu_init_marker_random (gofu_popu_t *);
void gofu_popu_init_label_random (gofu_popu_t *);
