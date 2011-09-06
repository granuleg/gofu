bin_PROGRAMS = gofu
gofu_SOURCES = ./parameter/gofu_param.c ./parameter/gofu_param_size.c ./populate/gofu_popu.c ./render/gofu_grid.c ./render/gofu_grid.h ./render/gofu_render.c ./render/gofu_render_color.c ./render/gofu_render_color.h ./render/gofu_render_grid_background.c ./render/gofu_render_grid_background.h ./render/gofu_render_grid_liberty.c ./render/gofu_render_grid_liberty.h ./render/gofu_render_grid_starpoint.c ./render/gofu_render_grid_starpoint.h ./render/gofu_render.h ./render/gofu_render_label.c ./render/gofu_render_label.h ./render/gofu_render_marker.c ./render/gofu_render_marker.h ./render/gofu_render_stone.c ./render/gofu_render_stone.h ./render/gofu_render_util.c ./render/gofu_render_util.h ./render/gofu_move.c ./render/gofu_move.h gofu.h gofu.c
AM_CFLAGS = @PANGOCAIRO_CFLAGS@ -Wall
LDADD = @PANGOCAIRO_LIBS@
gofu_SUBDIRS = parameter populate render
