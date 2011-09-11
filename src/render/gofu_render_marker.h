#include <math.h>

#include "gofu_render.h"
#include "gofu_move.h"
#include "gofu_render_util.h"

void gofu_render_marker (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_marker_cross (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_marker_triangle (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_marker_diamond (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_marker_pentagon_star (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_marker_circle (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_marker_square (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_marker_context (cairo_t *, gofu_t *, guint8, guint8);
void gofu_render_marker_stroke (cairo_t *, gofu_t *, guint8, guint8);
