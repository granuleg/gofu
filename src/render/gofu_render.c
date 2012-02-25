#include "gofu_render.h"
#include "gofu_render_external.h"

void
gofu_render_pangocairo (cairo_t * cr, gofu_t * gp)
{
  guint8 i, j;
  gboolean label, marker;
  gofu_render_background (cr, gp);
  gofu_render_grid (cr, gp);
  /* for (i = 1; i <= gp->popu->width; i++) */
  /*   { */
  /*     for (j = 1; j <= gp->popu->length; j++) */
  /*    { */
  /*      if (gp->popu->elem[i][j].grid != GRID_NONE) */
  /*        { */
  /*          if (g_strcmp0 ((gp->popu->elem[i][j].label)->str, "") != 0) */
  /*            label = TRUE; */
  /*          else */
  /*            label = FALSE; */
  /*          if (gp->popu->elem[i][j].marker == MARKER_NONE) */
  /*            marker = FALSE; */
  /*          else */
  /*            marker = TRUE; */
  /*          gofu_render_grid_background_overlap (cr, gp, i, j); */
  /*          if (label == FALSE) */
  /*            { */
  /*              gofu_render_grid_liberty (cr, gp, i, j); */
  /*              gofu_render_grid_starpoint (cr, gp, i, j); */
  /*            } */
  /*          gofu_render_stone (cr, gp, i, j); */
  /*          if (label == TRUE) */
  /*            gofu_render_label (cr, gp, i, j); */
  /*          else */
  /*            gofu_render_marker (cr, gp, i, j); */
  /*        } */
  /*    } */
  /*   } */
}
