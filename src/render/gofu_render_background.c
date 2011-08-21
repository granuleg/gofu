void
gofu_render_grid_background (cairo_t * cr, gofu_t * gofup)
{
  switch (gofup->param.grid.background.style)
    {
    case 0:
      break;
    case 1:
      gofu_render_grid_background_color (cr, gofup);
      break;
    case 2:
      gofu_render_grid_background_image (cr, gofup);
      break;
    case 3:
      gofu_render_grid_background_imagepattern (cr, gofup);
      break;
    default:
      g_printf ("%d\n", __LINE__);
      exit (EXIT_FAILURE);
      break;
    }
}

void
gofu_render_grid_background_color (cairo_t * cr, gofu_t * gofup)
{
  double max_x, max_y, min_x, min_y;
  cairo_save (cr);
  min_x = gofu_popuwidth_to_user (gofup, 0);
  min_y = gofu_populength_to_user (gofup, 0);
  max_x = gofu_popuwidth_to_user (gofup, gofup->width + 1);
  max_y = gofu_populength_to_user (gofup, gofup->length + 1);
  gofu_render_set_color (cr, gofup->param.grid.background.color_fill);
  cairo_rectangle (cr, min_x, min_y, max_x, max_y);
  cairo_fill (cr);
  cairo_restore (cr);
}

void
gofu_render_grid_background_image (cairo_t * cr, gofu_t * gofup)
{
  double max_x, max_y, min_x, min_y;
  double w, h;
  cairo_surface_t *image;
  cairo_save (cr);
  min_x = gofu_popuwidth_to_user (gofup, 0);
  min_y = gofu_populength_to_user (gofup, 0);
  max_x = gofu_popuwidth_to_user (gofup, gofup->width + 1);
  max_y = gofu_populength_to_user (gofup, gofup->length + 1);
  image =
    cairo_image_surface_create_from_png
    ((gofup->param.grid.background.image)->str);
  w = cairo_image_surface_get_width (image);
  h = cairo_image_surface_get_height (image);
  cairo_scale (cr, max_x / w, max_y / h);
  cairo_set_source_surface (cr, image, 0, 0);
  cairo_rectangle (cr, min_x * (max_x / w), min_y * (max_y / h), w, h);
  cairo_fill (cr);
  cairo_surface_destroy (image);
  cairo_restore (cr);
}

void
gofu_render_grid_background_imagepattern (cairo_t * cr, gofu_t * gofup)
{
  double max_x, max_y, min_x, min_y;
  cairo_surface_t *image;
  cairo_pattern_t *pattern;
  cairo_matrix_t matrix;
  cairo_save (cr);
  min_x = gofu_popuwidth_to_user (gofup, 0);
  min_y = gofu_populength_to_user (gofup, 0);
  max_x = gofu_popuwidth_to_user (gofup, gofup->width + 1);
  max_y = gofu_populength_to_user (gofup, gofup->length + 1);
  image =
    cairo_image_surface_create_from_png
    ((gofup->param.grid.background.image)->str);
  pattern = cairo_pattern_create_for_surface (image);
  cairo_translate (cr, min_x, min_y);
  cairo_pattern_set_extend (pattern, CAIRO_EXTEND_REFLECT);
  cairo_matrix_init_scale (&matrix, 1.0, 1.0);
  cairo_pattern_set_matrix (pattern, &matrix);
  cairo_set_source (cr, pattern);
  cairo_rectangle (cr, min_x, min_y, max_x, max_y);
  cairo_fill (cr);
  cairo_pattern_destroy (pattern);
  cairo_surface_destroy (image);
  cairo_restore (cr);
}
