#include "gofu_render_stone.h"

void
gofu_render_stone (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  switch (gp->popu->elem[i][j].stone)
    {
    case STONE_NONE:
      break;
    case STONE_BLACK:
      gofu_render_stone_black (cr, gp, i, j);
      break;
    case STONE_WHITE:
      gofu_render_stone_white (cr, gp, i, j);
      break;
    default:
      break;			// manage error TODO
    }
}

void
gofu_render_stone_black (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
  switch (gp->param->stone.style)
    {
    case STONE_NO:
      break;
    case STONE_PLAIN:
      gofu_render_stone_black_plain (cr, gp);
      break;
    case STONE_RADIAL:
      gofu_render_stone_black_radial (cr, gp);
      break;
    default:
      break;			// manage error TODO
    }
  cairo_restore (cr);
}

void
gofu_render_stone_black_plain (cairo_t * cr, gofu_t * gp)
{
  cairo_scale (cr,
	       gp->param_size->stone.radius - gp->param_size->stone.thickness,
	       gp->param_size->stone.radius -
	       gp->param_size->stone.thickness);
  gofu_render_set_color (cr, gp->param->stone.color_black_fill);
  gofu_render_stone_fill_and_stroke (cr, gp);
}

void
gofu_render_stone_black_radial (cairo_t * cr, gofu_t * gp)
{
  cairo_scale (cr, gp->param_size->stone.radius,
	       gp->param_size->stone.radius);
  /*TODO
     cairo_set_source (cr, gp->param->stone.pattern_black_radial); */
  gofu_render_stone_fill (cr);
}

void
gofu_render_stone_white (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  cairo_save (cr);
  cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
  switch (gp->param->stone.style)
    {
    case STONE_NO:
      break;
    case STONE_PLAIN:
      gofu_render_stone_white_plain (cr, gp);
      break;
    case STONE_RADIAL:
      gofu_render_stone_white_radial (cr, gp);
      break;
    default:
      break;			// manage error TODO
    }
  cairo_restore (cr);
}

void
gofu_render_stone_white_plain (cairo_t * cr, gofu_t * gp)
{
  cairo_scale (cr,
	       gp->param_size->stone.radius - gp->param_size->stone.thickness,
	       gp->param_size->stone.radius -
	       gp->param_size->stone.thickness);
  gofu_render_set_color (cr, gp->param->stone.color_white_fill);
  gofu_render_stone_fill_and_stroke (cr, gp);
}

void
gofu_render_stone_white_radial (cairo_t * cr, gofu_t * gp)
{
  cairo_scale (cr, gp->param_size->stone.radius,
	       gp->param_size->stone.radius);
  /*TODO
     cairo_set_source (cr, stone.pattern_white_radial); */
  gofu_render_stone_fill (cr);

}

void
gofu_render_stone_fill (cairo_t * cr)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill (cr);
}

void
gofu_render_stone_fill_and_stroke (cairo_t * cr, gofu_t * gp)
{
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill_preserve (cr);
  cairo_set_line_width (cr, gp->param_size->stone.thickness);
  gofu_render_set_color (cr, gp->param->stone.color_black_stroke);
  cairo_uniform_stroke (cr);
}
