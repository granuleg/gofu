#include "gofu_param.h"

#define G_SQRT2_2 (G_SQRT2/2)

gofu_param_description_t jp_standard = { 19, 19, 140, 150, 7.26, 7.82 };

gofu_param_description_t square = { 1, 1, 23, 23, 23, 23 };

gofu_param_ratio_size_t ratio_size = { G_SQRT2_2, G_SQRT2_2, 1. / 2, 1. / 4 };

gofu_param_ratio_thickness_t ratio_thickness = { 1, 1, 1, 1 };

void
gofu_param_init (gofu_t * gofup)
{
  gofu_param_init (gofup, &jp_standard, &ratio_size, &ratio_thickness);
  gofu_param_init_attribute (gofup);
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
gofu_param_init (gofu_t * gofup, gofu_param_description_t * desc,
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
    (desc->line_spacing_width * (gofup->width - 1)) + (2 * margin_width);
  surface_length =
    (desc->line_spacing_length * (gofup->length - 1)) + (2 * margin_length);
  scale =
    box_in_box (surface_width, surface_length, gofup->param.surface_width,
		gofup->param.surface_length);
  //from description
  gofup->param.grid.liberty.spacing_width = desc->line_spacing_width * scale;
  gofup->param.grid.liberty.spacing_length =
    desc->line_spacing_length * scale;
  gofup->param.grid.liberty.margin_width = margin_width * scale;
  gofup->param.grid.liberty.margin_length = margin_length * scale;
  gofup->param.stone.radius =
    (MIN (desc->line_spacing_width, desc->line_spacing_width) / 2) * scale;
  //from ratio size
  gofup->param.marker.radius =
    gofup->param.stone.radius * rsize->marker_stone;
  gofup->param.grid.starpoint.radius =
    gofup->param.marker.radius * rsize->starpoint_marker;
  gofup->param.grid.liberty.thickness_bound =
    gofup->param.grid.starpoint.radius * rsize->bound_starpoint;
  gofup->param.grid.liberty.thickness =
    gofup->param.grid.liberty.thickness_bound * rsize->unbound_bound;
  //from ratio thickness
  gofup->param.grid.starpoint.thickness =
    gofup->param.grid.liberty.thickness * rthickness->unbound_starpoint;
  gofup->param.marker.thickness =
    gofup->param.grid.liberty.thickness * rthickness->unbound_marker;
  gofup->param.stone.thickness =
    gofup->param.grid.liberty.thickness * rthickness->unbound_stone;
}

void
gofu_init_param_attribute (gofu_t * gofup)
{
  gofu_init_param_grid (gofup);
  gofu_init_param_stone (gofup);
  gofu_init_param_marker (gofup);
  gofu_init_param_label (gofup);
  gofu_init_param_highlight (gofup);
}

void
gofu_init_param_grid (gofu_t * gofup)
{
  gofup->param.grid.style_boundary = 1;
  gofup->param.grid.style_lighten = 1;
  gofu_init_param_grid_background (gofup);
  gofu_init_param_grid_liberty (gofup);
  gofu_init_param_grid_starpoint (gofup);
}

void
gofu_init_param_grid_background (gofu_t * gofup)
{
  gofup->param.grid.background.style = 1;
  gofu_init_param_color (&gofup->param.grid.background.color_fill, 222, 176,
			 109, 255);
  gofup->param.grid.background.image =
    g_string_new
    ("/home/granule/Documents/gofu/trunk/src/resource/resource/wood/test2.png");
}

void
gofu_init_param_grid_liberty (gofu_t * gofup)
{
  gofup->param.grid.liberty.style = 0;
  gofu_init_param_color (&gofup->param.grid.liberty.color_stroke, 0, 0, 0,
			 255);
}

void
gofu_init_param_grid_starpoint (gofu_t * gofup)
{
  gofup->param.grid.starpoint.style = 0;
  gofu_init_param_color (&gofup->param.grid.starpoint.color_stroke, 0, 0, 0,
			 255);
}

void
gofu_init_param_stone (gofu_t * gofup)
{
  gofup->param.stone.style = 1;
  gofu_init_param_color (&gofup->param.stone.color_black_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.stone.color_black_fill, 0, 0, 0, 255);
  gofu_init_param_color (&gofup->param.stone.color_white_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.stone.color_white_fill, 255, 255, 255,
			 255);
  gofup->param.stone.pattern_black_radial =
    cairo_pattern_create_radial (-0.2, -0.2, 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gofup->param.stone.pattern_black_radial,
				     0., 1., 1., 1., 1.);
  cairo_pattern_add_color_stop_rgba (gofup->param.stone.pattern_black_radial,
				     1., 0., 0., 0., 1.);
  gofup->param.stone.pattern_white_radial =
    cairo_pattern_create_radial (-0.2, -0.2, 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gofup->param.stone.pattern_white_radial,
				     0., 0., 0., 0., 1.);
  cairo_pattern_add_color_stop_rgba (gofup->param.stone.pattern_white_radial,
				     1., 1., 1., 1., 1.);
}

void
gofu_init_param_marker (gofu_t * gofup)
{
  gofup->param.marker.style = 0;
  gofu_init_param_color (&gofup->param.marker.color_black_stroke, 255, 255,
			 255, 255);
  gofu_init_param_color (&gofup->param.marker.color_black_fill, 255, 255, 255,
			 255);
  gofu_init_param_color (&gofup->param.marker.color_white_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.marker.color_white_fill, 255, 255, 255,
			 255);
  gofu_init_param_color (&gofup->param.marker.color_none_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.label.color_white_stroke, 0, 0, 0,
			 255);
  gofu_init_param_color (&gofup->param.label.color_black_stroke, 255, 255,
			 255, 255);
}

void
gofu_init_param_label (gofu_t * gofup)
{
  gofu_init_param_color (&gofup->param.label.color_none_stroke, 0, 0, 0, 255);
}

void
gofu_init_param_highlight (gofu_t * gofup)
{
  gofu_init_param_color (&gofup->param.highlight.hl1, 10, 100, 100, 128);
}

void
gofu_init_param_color (gofu_color_rgba_t * rgba, guint8 red, guint8 green,
		       guint8 blue, guint8 alpha)
{
  rgba->red = (gdouble) red / (gdouble) G_MAXUINT8;
  rgba->green = (gdouble) green / (gdouble) G_MAXUINT8;
  rgba->blue = (gdouble) blue / (gdouble) G_MAXUINT8;
  rgba->alpha = (gdouble) alpha / (gdouble) G_MAXUINT8;
}
