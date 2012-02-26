#include "gofu_param_size.h"

#define G_SQRT2_2 (G_SQRT2/2)
#define G_SQRT5 2.236067977
#define MAX_MARKER_RADIUS (3.0-G_SQRT5)/2.0

gofu_param_size_description_t jp_standard = { 19, 19, 140, 150, 7.26, 7.82 };
gofu_param_size_description_t square = { 1, 1, 23, 23, 23, 23 };
gofu_param_size_ratio_size_t ratio_size =
  { G_SQRT2_2, MAX_MARKER_RADIUS / 2., 1. / 2, 1. / 2 };
gofu_param_size_ratio_thickness_t ratio_thickness = { 1, 1, 1, 1 };


gofu_param_size_t *
gofu_param_size_alloc (void)
{
  gofu_param_size_t *gp;
  if ((gp =
       (gofu_param_size_t *) g_malloc (sizeof (gofu_param_size_t))) == NULL)
    return NULL;
  return gp;
}

void
gofu_param_size_free (gofu_param_size_t * gp)
{
  GSList *list = gp->grid.starpoint.list;
  for (list; list; list = g_slist_next (list))
    g_free (list->data);
  g_slist_free (gp->grid.starpoint.list);
  g_free ((gpointer) gp);
}

void
gofu_param_size_init (gofu_param_size_t * gp, guint8 width, guint8 length,
		      gdouble surface_width, gdouble surface_length)
{
  gofu_param_size_starpoint (gp, width, length);
  gofu_param_size_dimension (gp, width, length, surface_width, surface_length,
			     &jp_standard, &ratio_size, &ratio_thickness);
  gp->surface_width = surface_width;
  gp->surface_length = surface_length;
}

void
box_in_box (gofu_pos_t * gofu_pos, gdouble x, gdouble y, gdouble a, gdouble b)
{
  gdouble s, tx, ty;
  if ((a == 0) || (b == 0))
    {
      s = 0;
      tx = 0;
      ty = 0;
    }
  else
    {
      s = MIN (a / x, b / y);
      tx = (a - s * x) / 2.0;
      ty = (b - s * y) / 2.0;
    }
  gofu_pos->s = s;
  gofu_pos->tx = tx;
  gofu_pos->ty = ty;
  return;
}

void
gofu_param_size_dimension (gofu_param_size_t * gp,
			   guint8 width, guint8 length,
			   gdouble surface_width, gdouble surface_length,
			   gofu_param_size_description_t * desc,
			   gofu_param_size_ratio_size_t * rsize,
			   gofu_param_size_ratio_thickness_t * rthickness)
{
  gdouble desc_margin_width;
  gdouble desc_margin_length;
  gdouble virtual_surface_width;
  gdouble virtual_surface_length;
  //calculate virtual surface from description
  desc_margin_width =
    (desc->surface_width -
     (desc->line_spacing_width * (desc->number_line_width - 1))) / 2.0;
  desc_margin_length =
    (desc->surface_length -
     (desc->line_spacing_length * (desc->number_line_length - 1))) / 2.0;
  virtual_surface_width =
    (desc->line_spacing_width * (width - 1)) + (2 * desc_margin_width);
  virtual_surface_length =
    (desc->line_spacing_length * (length - 1)) + (2 * desc_margin_length);
  //calculate surface translation and scale
  box_in_box (&(gp->pos), virtual_surface_width, virtual_surface_length,
	      surface_width, surface_length);
  //from description
  gp->grid.liberty.spacing_width_2 =
    (desc->line_spacing_width / 2.0) * gp->pos.s;
  gp->grid.liberty.spacing_length_2 =
    (desc->line_spacing_length / 2.0) * gp->pos.s;
  gp->grid.margin.width = desc_margin_width * gp->pos.s;
  gp->grid.margin.length = desc_margin_length * gp->pos.s;
  gp->stone.radius =
    (MIN (desc->line_spacing_width, desc->line_spacing_width) / 2.0) *
    gp->pos.s;
  //from ratio size
  gp->marker.radius = gp->stone.radius * rsize->marker_stone;
  gp->grid.starpoint.radius = gp->marker.radius * rsize->starpoint_marker;
  gp->grid.liberty.thickness_bound =
    gp->grid.starpoint.radius * rsize->bound_starpoint;
  gp->grid.liberty.thickness =
    gp->grid.liberty.thickness_bound * rsize->unbound_bound;
  //from ratio thickness
  gp->grid.starpoint.thickness =
    gp->grid.liberty.thickness * rthickness->unbound_starpoint;
  gp->marker.thickness =
    gp->grid.liberty.thickness * rthickness->unbound_marker;
  gp->stone.thickness =
    gp->grid.liberty.thickness * rthickness->unbound_stone;
}

void
gofu_param_size_starpoint (gofu_param_size_t * gp, guint8 width,
			   guint8 length)
{
  guint8 delta;
  GSList *list = NULL;
  guint8 i, j;
  list = gofu_grid_starpoint_tengen (list, width, length);
  delta = gofu_grid_starpoint_corner_delta (width, length);
  if (delta != 0)
    {
      list = gofu_grid_starpoint_corner (list, width, length, delta);
      list = gofu_grid_starpoint_side (list, width, length, delta);
    }
  gp->grid.starpoint.list = list;
}

GSList *
gofu_grid_starpoint_tengen (GSList * list, guint8 width, guint8 length)
{
  if ((width % 2 == 1) && (length % 2 == 1))
    list = gofu_list_prepend_xy (list, 1 + (width / 2), 1 + (length / 2));
  return list;
}

guint8
gofu_grid_starpoint_corner_delta (guint8 width, guint8 length)
{
  guint8 i, j, delta;
  if ((width < 7) || (length < 7))
    delta = 0;
  else
    {
      if (width < 12)
	i = 2;
      else
	i = 3;
      if (length < 12)
	j = 2;
      else
	j = 3;
      delta = MIN (i, j);
    }
  return delta;
}

GSList *
gofu_grid_starpoint_corner (GSList * list, guint8 width, guint8 length,
			    guint8 delta)
{
  list = gofu_list_prepend_xy (list, 1 + delta, 1 + delta);
  list = gofu_list_prepend_xy (list, width - delta, 1 + delta);
  list = gofu_list_prepend_xy (list, 1 + delta, length - delta);
  list = gofu_list_prepend_xy (list, width - delta, length - delta);
  return list;
}

GSList *
gofu_grid_starpoint_side (GSList * list, guint8 width, guint8 length,
			  guint8 delta)
{
  if ((width % 2 == 1) && (width - (2 * delta) >= 13))
    {
      list = gofu_list_prepend_xy (list, 1 + (width / 2), 1 + delta);
      list = gofu_list_prepend_xy (list, 1 + (width / 2), length - delta);
    }
  if ((length % 2 == 1) && ((length - (2 * delta)) >= 13))
    {
      list = gofu_list_prepend_xy (list, 1 + delta, 1 + (length / 2));
      list = gofu_list_prepend_xy (list, width - delta, 1 + (length / 2));
    }
  return list;
}

GSList *
gofu_list_prepend_xy (GSList * list, guint8 x, guint8 y)
{
  gdouble *loc;
  if ((loc = (gdouble *) g_malloc (2 * sizeof (gdouble))) == NULL)
    return NULL;		//TODO manage error
  loc[0] = x;
  loc[1] = y;
  list = g_slist_prepend (list, loc);
  return list;
}
