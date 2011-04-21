#define min(a,b) (((a)<(b))?(a):(b))

#include <stdio.h>

void
main (void)
{
  int x, y;
  int a, b;
  float r,tx,ty;

  x = 2;
  y = 3;

  a = 1;
  b = 1;


  if ((a == 0) || (b == 0))
    {
      r = 0;
      tx=0;
      ty=0;
    }
  else
    {
      r = min ((float) (a) / x, (float) (b) / y);
      tx= ((float)a-r*(float)(x))/2;
      ty= ((float)b-r*(float)(y))/2;
    }

  printf ("(r)=%f\n", r);
  printf ("(rx,ry)=%f,%f\n", r * x, r * y);
  printf ("(tx,ty)=%f,%f\n", tx, ty);
  printf ("(a,b)=%d,%d\n", a, b);
}
