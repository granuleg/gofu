#include "gofu_grid.h"

#define compass__E 1 << 0
#define compass_SE 1 << 1
#define compass__S 1 << 2
#define compass_SW 1 << 3
#define compass__W 1 << 4
#define compass_NW 1 << 5
#define compass__N 1 << 6
#define compass_NE 1 << 7

guint8
gofu_grid_emptyneighbour (gofu_t * gp, guint8 i, guint8 j)
{
  guint8 gridN, gridS, gridW, gridE, gridNW, gridNE, gridSW, gridSE;
  guint8 neighbour = 0;
  gridN = gp->popu->elem[i][j - 1].grid;
  gridS = gp->popu->elem[i][j + 1].grid;
  gridW = gp->popu->elem[i - 1][j].grid;
  gridE = gp->popu->elem[i + 1][j].grid;
  gridNW = gp->popu->elem[i - 1][j - 1].grid;
  gridNE = gp->popu->elem[i + 1][j - 1].grid;
  gridSW = gp->popu->elem[i - 1][j + 1].grid;
  gridSE = gp->popu->elem[i + 1][j + 1].grid;
  if (gridN == GRID_NONE)
    neighbour |= compass__N;
  if (gridS == GRID_NONE)
    neighbour |= compass__S;
  if (gridW == GRID_NONE)
    neighbour |= compass__W;
  if (gridE == GRID_NONE)
    neighbour |= compass__E;
  if (gridNW == GRID_NONE)
    neighbour |= compass_NW;
  if (gridNE == GRID_NONE)
    neighbour |= compass_NE;
  if (gridSW == GRID_NONE)
    neighbour |= compass_SW;
  if (gridSE == GRID_NONE)
    neighbour |= compass_SE;
  return neighbour;
}

gboolean
gofu_grid_liberty_bound_detect_E (guint8 neighbour)
{
  if ((neighbour & compass__N) || (neighbour & compass__S)
      || (neighbour & compass_NE) || (neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_liberty_bound_detect_S (guint8 neighbour)
{
  if ((neighbour & compass__W) || (neighbour & compass__E)
      || (neighbour & compass_SW) || (neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_liberty_bound_detect_W (guint8 neighbour)
{
  if ((neighbour & compass__N) || (neighbour & compass__S)
      || (neighbour & compass_NW) || (neighbour & compass_SW))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_liberty_bound_detect_N (guint8 neighbour)
{
  if ((neighbour & compass__W) || (neighbour & compass__E)
      || (neighbour & compass_NW) || (neighbour & compass_NE))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_starpoint_detect_SE (guint8 neighbour)
{
  if (!(neighbour & compass__S) &&
      !(neighbour & compass__E) && !(neighbour & compass_SE))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_starpoint_detect_SW (guint8 neighbour)
{
  if (!(neighbour & compass__S) &&
      !(neighbour & compass__W) && !(neighbour & compass_SW))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_starpoint_detect_NW (guint8 neighbour)
{
  if (!(neighbour & compass__N) &&
      !(neighbour & compass__W) && !(neighbour & compass_NW))
    return TRUE;
  else
    return FALSE;
}

gboolean
gofu_grid_starpoint_detect_NE (guint8 neighbour)
{
  if (!(neighbour & compass__N) &&
      !(neighbour & compass__E) && !(neighbour & compass_NE))
    return TRUE;
  else
    return FALSE;
}
