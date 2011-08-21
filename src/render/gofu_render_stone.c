#include "gofu_render_stone.h"

void
gofu_render_stone_fill (cairo_t * cr)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill (cr);
}

void
gofu_render_stone_fill_and_stroke (cairo_t * cr, gofu_t * gofup)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill_preserve (cr);
  cairo_set_line_width (cr, gofup->param.stone.thickness);
  gofu_render_set_color (cr, gofup->param.stone.color_black_stroke);
  cairo_uniform_stroke (cr);
}

void
gofu_render_stone_black (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  switch (gofup->param.stone.style)
    {
    case 0:
      gofu_render_stone_black_plain (cr, gofup);
      break;
    case 1:
      gofu_render_stone_black_radial (cr, gofup);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
  cairo_restore (cr);
}

void
gofu_render_stone_black_plain (cairo_t * cr, gofu_t * gofup)
{
  cairo_scale (cr, gofup->param.stone.radius - gofup->param.stone.thickness,
	       gofup->param.stone.radius - gofup->param.stone.thickness);
  gofu_render_set_color (cr, gofup->param.stone.color_black_fill);
  gofu_render_stone_fill_and_stroke (cr, gofup);
}

void
gofu_render_stone_black_radial (cairo_t * cr, gofu_t * gofup)
{
  cairo_scale (cr, gofup->param.stone.radius, gofup->param.stone.radius);
  cairo_set_source (cr, gofup->param.stone.pattern_black_radial);
  gofu_render_stone_fill (cr);
}

void
gofu_render_stone_white (cairo_t * cr, gofu_t * gofup, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_localwidth_to_user (gofup, i),
		   gofu_locallength_to_user (gofup, j));
  switch (gofup->param.stone.style)
    {
    case 0:
      gofu_render_stone_white_plain (cr, gofup);
      break;
    case 1:
      gofu_render_stone_white_radial (cr, gofup);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
  cairo_restore (cr);
}

void
gofu_render_stone_white_plain (cairo_t * cr, gofu_t * gofup)
{
  cairo_scale (cr, gofup->param.stone.radius - gofup->param.stone.thickness,
	       gofup->param.stone.radius - gofup->param.stone.thickness);
  gofu_render_set_color (cr, gofup->param.stone.color_white_fill);
  gofu_render_stone_fill_and_stroke (cr, gofup);
}

void
gofu_render_stone_white_radial (cairo_t * cr, gofu_t * gofup)
{
  cairo_scale (cr, gofup->param.stone.radius, gofup->param.stone.radius);
  cairo_set_source (cr, gofup->param.stone.pattern_white_radial);
  gofu_render_stone_fill (cr);

}
