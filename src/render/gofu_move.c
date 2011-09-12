#include "gofu_move.h"

inline gdouble
gofu_move_width (gofu_t * gp, guint8 i)
{
  return (gp->param_size->grid.background.margin_width +
	  ((i - 1) * gp->param_size->grid.liberty.spacing_width));
}

inline gdouble
gofu_move_length (gofu_t * gp, guint8 j)
{
  return (gp->param_size->grid.background.margin_length +
	  ((j - 1) * gp->param_size->grid.liberty.spacing_length));
}
