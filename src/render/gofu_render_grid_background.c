#include "gofu_render_grid_background.h"

void
gofu_render_grid_background (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  switch (gp->param->grid.background.style)
    {
    case GRID_BACKGROUND_NO:
      break;
    case GRID_BACKGROUND_COLOR:
      gofu_render_grid_background_color (cr, gp, i, j);
      break;
    case GRID_BACKGROUND_IMAGE:
      gofu_render_grid_background_image (cr, gp, i, j);
      break;
    default:
      break;			// manage error TODO
    }
}

void
gofu_render_grid_background_overlap (cairo_t * cr, gofu_t * gp, guint8 i,
				     guint8 j)
{
  switch (gp->param->grid.background.style)
    {
    case GRID_BACKGROUND_NO:
      break;
    case GRID_BACKGROUND_COLOR:
      gofu_render_grid_background_color_overlap (cr, gp, i, j);
      break;
    case GRID_BACKGROUND_IMAGE:
      gofu_render_grid_background_image_overlap (cr, gp, i, j);
      break;
    default:
      break;			// manage error TODO
    }
}

void
gofu_render_grid_background_color_overlap (cairo_t * cr, gofu_t * gp,
					   guint8 i, guint8 j)
{
  double max_width, min_width, max_length, min_length;
  double x, y, width, length;
  guint8 gridE, gridS, gridW, gridN;
  cairo_save (cr);
  cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
  gridE = gp->popu->elem[i + 1][j].grid;
  gridS = gp->popu->elem[i][j + 1].grid;
  gridW = gp->popu->elem[i - 1][j].grid;
  gridN = gp->popu->elem[i][j - 1].grid;
  max_width = gp->param_size->grid.background.margin_width;
  min_width = gp->param_size->grid.liberty.spacing_width / 2.0;
  max_length = gp->param_size->grid.background.margin_length;
  min_length = gp->param_size->grid.liberty.spacing_length / 2.0;
  if (gridW == GRID_NONE)
    x = max_width;
  else
    x = min_width;
  if (gridE == GRID_NONE)
    width = x + max_width;
  else
    width = x + min_width;
  if (gridN == GRID_NONE)
    y = max_length;
  else
    y = min_length;
  if (gridS == GRID_NONE)
    length = y + max_length;
  else
    length = y + min_length;
  gofu_render_set_color (cr, gp->param->grid.background.color);
  cairo_rectangle (cr, -x, -y, width, length);
  cairo_fill (cr);
  cairo_restore (cr);
}

void
gofu_render_grid_background_color (cairo_t * cr, gofu_t * gp, guint8 i,
				   guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
  cairo_scale (cr, gp->param_size->grid.liberty.spacing_width,
	       gp->param_size->grid.liberty.spacing_length);
  gofu_render_set_color (cr, gp->param->grid.background.color);
  cairo_rectangle (cr, -0.5, -0.5, 1., 1.);
  cairo_fill (cr);
  cairo_restore (cr);
}

void
gofu_render_grid_background_image (cairo_t * cr, gofu_t * gp, guint8 i,
				   guint8 j)
{
  double max_x, max_y, min_x, min_y;
  double w, h;
  cairo_surface_t *image;
  cairo_save (cr);
  min_x = gofu_move_width (gp, 0);
  min_y = gofu_move_length (gp, 0);
  max_x = gofu_move_width (gp, gp->popu->width + 1);
  max_y = gofu_move_length (gp, gp->popu->length + 1);
  image =
    cairo_image_surface_create_from_png
    ((gp->param->grid.background.image)->str);
  w = cairo_image_surface_get_width (image);
  h = cairo_image_surface_get_height (image);
  cairo_scale (cr, max_x / w, max_y / h);
  cairo_set_source_surface (cr, image, 0, 0);
  cairo_rectangle (cr, min_x * (max_x / w), min_y * (max_y / h), w, h);
  cairo_fill (cr);
  cairo_surface_destroy (image);
  cairo_restore (cr);
}

void
gofu_render_grid_background_image_overlap (cairo_t * cr, gofu_t * gp,
					   guint8 i, guint8 j)
{
  return;
}
