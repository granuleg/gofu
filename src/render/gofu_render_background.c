#include "gofu_render_background.h"

void
gofu_render_background (cairo_t * cr, gofu_t * gp)
{
  switch (gp->param->background.style)
    {
    case GRID_BACKGROUND_NO:
      break;
    case GRID_BACKGROUND_COLOR:
      gofu_render_background_color (cr, gp);
      break;
    case GRID_BACKGROUND_IMAGE:
      gofu_render_background_image (cr, gp);
      break;
    default:
      break;			// manage error TODO
    }
}

void
gofu_render_background_color (cairo_t * cr, gofu_t * gp)
{
  double x, y, width, length;
  cairo_save (cr);
  gofu_cairo_set_color (cr, gp->param->background.color);
  x = gp->param_size->pos.tx;
  y = gp->param_size->pos.ty;
  width =
    gofu_move_width (gp,
		     gp->popu->width) + gp->param_size->grid.margin.width - x;
  length =
    gofu_move_length (gp,
		      gp->popu->length) + gp->param_size->grid.margin.length -
    y;
  cairo_rectangle (cr, x, y, width, length);
  cairo_fill (cr);
  cairo_restore (cr);
}

void
gofu_render_background_image (cairo_t * cr, gofu_t * gp)
{
   /*TODO*/
    /* double max_x, max_y, min_x, min_y; */
    /* double w, h; */
    /* cairo_surface_t *image; */
    /* cairo_save (cr); */
    /* min_x =  */
    /* min_y =  */
    /* max_x =  */
    /* max_y =  */
    /* image = */
    /*   cairo_image_surface_create_from_png */
    /*   ((gp->param->background.image)->str); */
    /* w = cairo_image_surface_get_width (image); */
    /* h = cairo_image_surface_get_height (image); */
    /* cairo_scale (cr, max_x / w, max_y / h); */
    /* cairo_set_source_surface (cr, image, 0, 0); */
    /* cairo_rectangle (cr, min_x * (max_x / w), min_y * (max_y / h), w, h); */
    /* cairo_fill (cr); */
    /* cairo_surface_destroy (image); */
    /* cairo_restore (cr); */
}
