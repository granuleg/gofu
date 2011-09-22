#include <math.h>

#include "gofu_render.h"
#include "gofu_move.h"
#include "gofu_render_util.h"

void gofu_render_stone (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_stone_black (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_stone_black_plain (cairo_t *, gofu_t *);
void gofu_render_stone_black_image (cairo_t *, gofu_t *);
void gofu_render_stone_white (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_stone_white_plain (cairo_t *, gofu_t *);
void gofu_render_stone_white_image (cairo_t *, gofu_t *);
void gofu_render_stone_paint (cairo_t *, gofu_t *, const char *);
void gofu_render_stone_fill_and_stroke (cairo_t *, gofu_t *);
