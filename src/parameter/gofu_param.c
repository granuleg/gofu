#include "gofu_param.h"

#define G_SQRT2_2 (G_SQRT2/2)

gofu_param_description_t jp_standard = { 19, 19, 140, 150, 7.26, 7.82 };
gofu_param_description_t square = { 1, 1, 23, 23, 23, 23 };
gofu_param_ratio_size_t ratio_size = { G_SQRT2_2, G_SQRT2_2, 1. / 2, 1. / 4 };
gofu_param_ratio_thickness_t ratio_thickness = { 1, 1, 1, 1 };

void
gofu_param (gofu_param_t * gp, guint8 width, guint8 length)
{
  gofu_param_dimension (gp, &jp_standard, width, length, &ratio_size,
			&ratio_thickness);
  gofu_param_attribute (gp);
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
gofu_param_dimension (gofu_param_t * gp, guint8 width, guint8 length,
		      gofu_param_description_t * desc,
		      gofu_param_ratio_size_t * rsize,
		      gofu_param_ratio_thickness_t * rthickness)
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

void
gofu_param_attribute (gofu_param_t * gp)
{
  gofu_param_grid (gofup);
  gofu_param_stone (gofup);
  gofu_param_marker (gofup);
  gofu_param_label (gofup);
  gofu_param_highlight (gofup);
}

void
gofu_param_grid (gofu_param_t * gp)
{
  gp->grid.style_boundary = 1;
  gp->grid.style_lighten = 1;
  gofu_param_grid_background (gofup);
  gofu_param_grid_liberty (gofup);
  gofu_param_grid_starpoint (gofup);
}

void
gofu_param_grid_background (gofu_param_t * gp)
{
  gp->grid.background.style = 1;
  gofu_param_color (&gp->grid.background.color_fill, 222, 176, 109, 255);
  gp->grid.background.image =
    g_string_new
    ("/home/granule/Documents/gofu/trunk/src/resource/resource/wood/test2.png");
}

void
gofu_param_grid_liberty (gofu_param_t * gp)
{
  gp->grid.liberty.style = 0;
  gofu_param_color (&gp->grid.liberty.color_stroke, 0, 0, 0, 255);
}

void
gofu_param_grid_starpoint (gofu_param_t * gp)
{
  gp->grid.starpoint.style = 0;
  gofu_param_color (&gp->grid.starpoint.color_stroke, 0, 0, 0, 255);
}

void
gofu_param_stone (gofu_param_t * gp)
{
  gp->stone.style = 1;
  gofu_param_color (&gp->stone.color_black_stroke, 0, 0, 0, 255);
  gofu_param_color (&gp->stone.color_black_fill, 0, 0, 0, 255);
  gofu_param_color (&gp->stone.color_white_stroke, 0, 0, 0, 255);
  gofu_param_color (&gp->stone.color_white_fill, 255, 255, 255, 255);
  gp->stone.pattern_black_radial =
    cairo_pattern_create_radial (-0.2, -0.2, 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gp->stone.pattern_black_radial,
				     0., 1., 1., 1., 1.);
  cairo_pattern_add_color_stop_rgba (gp->stone.pattern_black_radial,
				     1., 0., 0., 0., 1.);
  gp->stone.pattern_white_radial =
    cairo_pattern_create_radial (-0.2, -0.2, 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gp->stone.pattern_white_radial,
				     0., 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gp->stone.pattern_white_radial,
				     1., 1., 1., 1., 1.);
}

void
gofu_param_marker (gofu_param_t * gp)
{
  gp->marker.style = 0;
  gofu_param_color (&gp->marker.color_black_stroke, 255, 255, 255, 255);
  gofu_param_color (&gp->marker.color_black_fill, 255, 255, 255, 255);
  gofu_param_color (&gp->marker.color_white_stroke, 0, 0, 0, 255);
  gofu_param_color (&gp->marker.color_white_fill, 255, 255, 255, 255);
  gofu_param_color (&gp->marker.color_none_stroke, 0, 0, 0, 255);
  gofu_param_color (&gp->label.color_white_stroke, 0, 0, 0, 255);
  gofu_param_color (&gp->label.color_black_stroke, 255, 255, 255, 255);
}

void
gofu_param_label (gofu_param_t * gp)
{
  gofu_param_color (&gp->label.color_none_stroke, 0, 0, 0, 255);
}

void
gofu_param_highlight (gofu_param_t * gp)
{
  gofu_param_color (&gp->highlight.hl1, 10, 100, 100, 128);
}

void
gofu_param_color (gofu_color_rgba_t * rgba, guint8 red, guint8 green,
		  guint8 blue, guint8 alpha)
{
  rgba->red = (gdouble) red / (gdouble) G_MAXUINT8;
  rgba->green = (gdouble) green / (gdouble) G_MAXUINT8;
  rgba->blue = (gdouble) blue / (gdouble) G_MAXUINT8;
  rgba->alpha = (gdouble) alpha / (gdouble) G_MAXUINT8;
}
