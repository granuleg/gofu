#include "gofu_render_label.h"

void
gofu_render_label (cairo_t * cr, gofu_t * gp, guint8 i, guint8 j)
{
  PangoLayout *layout;
  PangoFontDescription *font_description;
  PangoRectangle ink_rect;
  PangoRectangle logical_rect;
  int size_x, size_y, pyta, delta_x, delta_y;
  cairo_save (cr);
  font_description = pango_font_description_new ();
  layout = pango_cairo_create_layout (cr);
  /*sans serif (roman) for stone number */
  /*serif (roman) for stone letter */
  pango_font_description_set_family (font_description, "Junicode");
  /* pango_font_description_set_style (font_description, PANGO_STYLE_NORMAL); */
  /* pango_font_description_set_weight (font_description, PANGO_WEIGHT_BOOK); */
  /* pango_font_description_set_variant(font_description,PANGO_VARIANT_NORMAL); */
  /* pango_font_description_set_stretch(font_description, PANGO_STRETCH_ULTRA_EXPANDED); */
  pango_font_description_set_absolute_size (font_description,
					    100 * PANGO_SCALE);
  pango_layout_set_font_description (layout, font_description);
  pango_layout_set_text (layout, (gp->popu->elem[i][j].label)->str, -1);
  pango_layout_get_extents (layout, &ink_rect, &logical_rect);
  size_x = ink_rect.width;
  size_y = ink_rect.height;
  delta_x = logical_rect.x - ink_rect.x;
  delta_y = logical_rect.y - ink_rect.y;
  pyta =
    sqrt (pow (0.5 * size_x / PANGO_SCALE, 2) +
	  pow (0.5 * size_y / PANGO_SCALE, 2));
  cairo_translate (cr, gofu_move_width (gp, i), gofu_move_length (gp, j));
  cairo_scale (cr,
	       gp->param_size->marker.radius / pyta,
	       gp->param_size->marker.radius / pyta);
  switch (gp->popu->elem[i][j].stone)
    {
    case STONE_BLACK:
      gofu_render_set_color (cr, gp->param->label.color_black_stroke);
      break;
    case STONE_WHITE:
      gofu_render_set_color (cr, gp->param->label.color_white_stroke);
      break;
    case STONE_NONE:
      gofu_render_set_color (cr, gp->param->label.color_none_stroke);
      break;
    default:
      g_print ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
  pango_cairo_update_layout (cr, layout);
  cairo_move_to (cr, (-0.5 * size_x + delta_x) / PANGO_SCALE,
		 (-0.5 * size_y + delta_y) / PANGO_SCALE);
  pango_cairo_show_layout (cr, layout);
  cairo_new_path (cr);
  g_object_unref (layout);
  pango_font_description_free (font_description);
  cairo_restore (cr);
}
