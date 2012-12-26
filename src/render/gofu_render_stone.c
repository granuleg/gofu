#include "gofu_render_stone.h"

void
gofu_render_stone (cairo_t * cr, gofu_t * gp)
{
  switch (gp->param->stone.style)
    {
    case STONE_NO:
      break;
    case STONE_PLAIN:
      gofu_render_stones_plain (cr, gp);
      break;
    case STONE_IMAGE:
      gofu_render_stones_image (cr, gp);
      break;
    default:
      break;			// manage error TODO
    }
}

void
gofu_render_stones_plain (cairo_t * cr, gofu_t * gp)
{
  guint8 i, j;
  for (i = 1; i <= gp->popu->width; i++)
    {
      for (j = 1; j <= gp->popu->length; j++)
	{
	  switch (gp->popu->elem[i][j].stone)
	    {
	    case STONE_NONE:
	      break;
	    case STONE_BLACK:
	      cairo_save (cr);
	      cairo_translate (cr, gofu_move_width (gp, i),
			       gofu_move_length (gp, j));
	      gofu_render_stone_black_plain (cr, gp);
	      cairo_restore (cr);
	      break;
	    case STONE_WHITE:
	      cairo_save (cr);
	      cairo_translate (cr, gofu_move_width (gp, i),
			       gofu_move_length (gp, j));
	      gofu_render_stone_white_plain (cr, gp);
	      cairo_restore (cr);
	      break;
	    default:
	      break;		// manage error TODO
	    }
	}
    }
}

void
gofu_render_stones_image (cairo_t * cr, gofu_t * gp)
{
  guint8 i, j;
  for (i = 1; i <= gp->popu->width; i++)
    {
      for (j = 1; j <= gp->popu->length; j++)
	{
	  switch (gp->popu->elem[i][j].stone)
	    {
	    case STONE_NONE:
	      break;
	    case STONE_BLACK:
	      cairo_save (cr);
	      cairo_translate (cr, gofu_move_width (gp, i),
			       gofu_move_length (gp, j));
	      gofu_render_stone_black_image (cr, gp);
	      cairo_restore (cr);
	      break;
	    case STONE_WHITE:
	      cairo_save (cr);
	      cairo_translate (cr, gofu_move_width (gp, i),
			       gofu_move_length (gp, j));
	      gofu_render_stone_white_image (cr, gp);
	      cairo_restore (cr);
	      break;
	    default:
	      break;		// manage error TODO
	    }
	}
    }
}

void
gofu_render_stone_black_plain (cairo_t * cr, gofu_t * gp)
{
  gdouble s;
  s = gp->param_size->stone.radius - gp->param_size->stone.thickness;
  cairo_scale (cr, s, s);
  gofu_cairo_set_color (cr, gp->param->stone.color_black_fill);
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill_preserve (cr);
  cairo_set_line_width (cr, gp->param_size->stone.thickness);
  gofu_cairo_set_color (cr, gp->param->stone.color_black_stroke);
  gofu_cairo_uniform_stroke (cr);
}

void
gofu_render_stone_white_plain (cairo_t * cr, gofu_t * gp)
{
  gdouble s;
  s = gp->param_size->stone.radius - gp->param_size->stone.thickness;
  cairo_scale (cr, s, s);
  gofu_cairo_set_color (cr, gp->param->stone.color_white_fill);
  cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
  cairo_fill_preserve (cr);
  cairo_set_line_width (cr, gp->param_size->stone.thickness);
  gofu_cairo_set_color (cr, gp->param->stone.color_white_stroke);
  gofu_cairo_uniform_stroke (cr);
}

void
gofu_render_stone_image (cairo_t * cr, gofu_t * gp, const char *image)
{
  int w, h;
  cairo_surface_t *cs;

  cs = cairo_image_surface_create_from_png (image);
  w = cairo_image_surface_get_width (cs);
  h = cairo_image_surface_get_height (cs);
  cairo_scale (cr, 2 * gp->param_size->stone.radius / w,
	       2 * gp->param_size->stone.radius / h);
  cairo_arc (cr, 0., 0., w / 2.0, 0., 2 * M_PI);
  cairo_clip (cr);
  cairo_set_source_surface (cr, cs, -w / 2.0, -h / 2.0);
  cairo_paint (cr);
  cairo_surface_destroy (cs);
}

void
gofu_render_stone_black_image (cairo_t * cr, gofu_t * gp)
{
  gofu_render_stone_image (cr, gp,
			   "./black.png");
}

void
gofu_render_stone_white_image (cairo_t * cr, gofu_t * gp)
{
  gofu_render_stone_image (cr, gp,
			   "./white.png");
}
