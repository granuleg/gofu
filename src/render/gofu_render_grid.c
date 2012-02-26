#include "gofu_render_grid.h"

void
gofu_render_grid (cairo_t * cr, gofu_t * gp)
{
  gofu_render_grid_liberty (cr, gp);
  gofu_render_grid_starpoint (cr, gp);
}

void
gofu_render_grid_liberty (cairo_t * cr, gofu_t * gp)
{
  switch (gp->param->grid.liberty.style)
    {
    case GRID_LIBERTY_NO:
      break;
    case GRID_LIBERTY_LINE:
      gofu_render_grid_liberty_line (cr, gp, FALSE);
      break;
    case GRID_LIBERTY_BOUND:
      gofu_render_grid_liberty_line (cr, gp, TRUE);
      break;
    default:
      break;			// manage error TODO
    }
}

void
gofu_render_grid_liberty_line (cairo_t * cr, gofu_t * gp, gboolean bound)
{
  guint8 i;
  gdouble c, min_width, max_width, min_length, max_length;
  cairo_save (cr);
  gofu_cairo_set_color (cr, gp->param->grid.liberty.color);
  cairo_set_line_width (cr, gp->param_size->grid.liberty.thickness);
  min_length = gofu_move_length (gp, 1);
  max_length = gofu_move_length (gp, gp->popu->length);
  min_width = gofu_move_width (gp, 1);
  max_width = gofu_move_width (gp, gp->popu->width);
  /*draw vertical line without border */
  for (i = 2; i <= gp->popu->width - 1; i++)
    {
      c = gofu_move_width (gp, i);
      cairo_move_to (cr, c, min_length);
      cairo_line_to (cr, c, max_length);
      cairo_stroke (cr);
    }
  /*draw horizontal line without border */
  for (i = 2; i <= gp->popu->length - 1; i++)
    {
      c = gofu_move_length (gp, i);
      cairo_move_to (cr, min_width, c);
      cairo_line_to (cr, max_width, c);
      cairo_stroke (cr);
    }
  /*draw border */
  if (bound == TRUE)
    cairo_set_line_width (cr, gp->param_size->grid.liberty.thickness_bound);
  cairo_rectangle (cr, min_width, min_length, max_width - min_width,
		   max_length - min_length);
  cairo_stroke (cr);
  cairo_restore (cr);
}

void
gofu_render_grid_starpoint (cairo_t * cr, gofu_t * gp)
{
  switch (gp->param->grid.starpoint.style)
    {
    case GRID_STARPOINT_NO:
      break;
    case GRID_STARPOINT_ROUND:
      gofu_render_grid_starpoint_elem (cr, gp,
				       &gofu_render_grid_starpoint_round);
      break;
    case GRID_STARPOINT_SQUARE:
      gofu_render_grid_starpoint_elem (cr, gp,
				       &gofu_render_grid_starpoint_square);
      break;
    default:
      break;			// manage error TODO
    }
}

void
gofu_render_grid_starpoint_elem (cairo_t * cr, gofu_t * gp,
				 void (*f) (cairo_t * cr))
{
  guint8 i, j;
  GSList *temp;
  for (temp = gp->param_size->grid.starpoint.list; temp;
       temp = g_slist_next (temp))
    {
      i = ((gdouble *) (temp->data))[0];
      j = ((gdouble *) (temp->data))[1];
      cairo_save (cr);
      cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
      cairo_scale (cr, gp->param_size->grid.starpoint.radius,
		   gp->param_size->grid.starpoint.radius);
      gofu_cairo_set_color (cr, gp->param->grid.starpoint.color);
      cairo_set_line_width (cr, gp->param_size->grid.starpoint.thickness);
      cairo_move_to (cr, 0., 0.);
      (*f) (cr);
      cairo_rotate (cr, G_PI_2);
      cairo_fill_preserve (cr);
      gofu_cairo_uniform_stroke (cr);
      cairo_restore (cr);
    }
}

void
gofu_render_grid_starpoint_round (cairo_t * cr)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * G_PI);
  cairo_close_path (cr);
}

void
gofu_render_grid_starpoint_square (cairo_t * cr)
{
  cairo_rectangle (cr, -1.0, -1.0, 2.0, 2.0);
}
