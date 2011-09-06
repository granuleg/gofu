#include "gofu_move.h"

gdouble
gofu_move_width (gofu_t * gp, guint8 i)
{
  if (i == 0)
    return 0;
  else if (i == gp->popu->width + 1)
    return ((2 * gp->param_size->grid.liberty.margin_width) +
	    ((gp->popu->width -
	      1) * gp->param_size->grid.liberty.spacing_width));
  else
    return (gp->param_size->grid.liberty.margin_width +
	    ((i - 1) * gp->param_size->grid.liberty.spacing_width));
}

gdouble
gofu_move_length (gofu_t * gp, guint8 j)
{
  if (j == 0)
    return 0;
  else if (j == gp->popu->length + 1)
    return ((2 * gp->param_size->grid.liberty.margin_length) +
	    ((gp->popu->length -
	      1) * gp->param_size->grid.liberty.spacing_length));
  else
    return (gp->param_size->grid.liberty.margin_length +
	    ((j - 1) * gp->param_size->grid.liberty.spacing_length));
}
