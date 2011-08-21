#include "gofu.h"

gofu_t *gofu_alloc (guint8, guint8);
gpointer *gofu_alloc_popu (gsize, guint8, guint8);
void gofu_free (gofu_t *);
void gofu_free_popu_internal (gofu_t *);
void gofu_free_popu (gpointer *, guint8);
void gofu_free_param_internal (gofu_t *);
