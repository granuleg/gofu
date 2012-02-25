# ./render/gofu_render_stone.c \
# ./render/gofu_render_stone.h \
# ./render/gofu_render_marker.c \
# ./render/gofu_render_marker.h \
# ./render/gofu_render_label.c \
# ./render/gofu_render_label.h 
bin_PROGRAMS = gofu
gofu_SOURCES = \
./parameter/gofu_param.c \
./parameter/gofu_param_size.c \
./populate/gofu_popu.c \
./render/gofu_render.c \
./render/gofu_render.h \
./render/gofu_render_util.c \
./render/gofu_render_util.h \
./render/gofu_render_grid.c \
./render/gofu_render_grid.h \
./render/gofu_render_background.c \
./render/gofu_render_background.h \
gofu.c \
gofu.h

AM_CFLAGS = @PANGOCAIRO_CFLAGS@
LDADD = @PANGOCAIRO_LIBS@
gofu_SUBDIRS = parameter populate render
