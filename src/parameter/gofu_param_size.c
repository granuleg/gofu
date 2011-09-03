#include "gofu_param_size.h"

#define G_SQRT2_2 (G_SQRT2/2)

gofu_param_size_description_t jp_standard = { 19, 19, 140, 150, 7.26, 7.82 };
gofu_param_size_description_t square = { 1, 1, 23, 23, 23, 23 };
gofu_param_size_ratio_size_t ratio_size =
  { G_SQRT2_2, G_SQRT2_2, 1. / 2, 1. / 4 };
gofu_param_size_ratio_thickness_t ratio_thickness = { 1, 1, 1, 1 };


gofu_param_size_t *
gofu_param_size_alloc (void)
{
  gofu_param_size_t *gp;
  if ((gp = (gofu_param_size_t *) g_malloc (sizeof (gofu_param_size_t))) == NULL)
    return NULL;
  return gp;
}

void
gofu_param_size_free (gofu_param_size_t * gp)
{
  g_free ((gpointer) gp);
}

void
gofu_param_size_init (gofu_param_size_t * gp, guint8 width, guint8 length)
{
  gofu_param_size_dimension (gp, width, length, &jp_standard, &ratio_size,
			     &ratio_thickness);
}

gdouble
box_in_box (gdouble x, gdouble y, gdouble a, gdouble b)
{
  gdouble r, tx, ty;
  if ((a == 0) || (b == 0))
    {
      r = 0;
      tx = 0;
      ty = 0;
    }
  else
    {
      r = MIN (a / x, b / y);
      tx = (a - r * x) / 2;
      ty = (b - r * y) / 2;
    }
  return r;
}

void
gofu_param_size_dimension (gofu_param_size_t * gp, guint8 width,
			   guint8 length,
			   gofu_param_size_description_t * desc,
			   gofu_param_size_ratio_size_t * rsize,
			   gofu_param_size_ratio_thickness_t * rthickness)
{
  gdouble scale;
  gdouble margin_width;
  gdouble margin_length;
  gdouble surface_width;
  gdouble surface_length;
  margin_width =
    (desc->gofu_width -
     (desc->line_spacing_width * (desc->number_line_width - 1))) / 2;
  margin_length =
    (desc->gofu_length -
     (desc->line_spacing_length * (desc->number_line_length - 1))) / 2;
  surface_width =
    (desc->line_spacing_width * (width - 1)) + (2 * margin_width);
  surface_length =
    (desc->line_spacing_length * (length - 1)) + (2 * margin_length);
  scale =
    box_in_box (surface_width, surface_length, gp->surface_width,
		gp->surface_length);
  //from description
  gp->grid.liberty.spacing_width = desc->line_spacing_width * scale;
  gp->grid.liberty.spacing_length = desc->line_spacing_length * scale;
  gp->grid.liberty.margin_width = margin_width * scale;
  gp->grid.liberty.margin_length = margin_length * scale;
  gp->stone.radius =
    (MIN (desc->line_spacing_width, desc->line_spacing_width) / 2) * scale;
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
