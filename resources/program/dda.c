#include <stdio.h>

int x, y, dx, dy; 
double a, err;

typedef struct point{
   int *x, *y;
}point;


typedef struct res{
   int ax, ay, dx, dy, opt;
   double a;
}res;


point init_dda(res *input, point *point) {
   x = 0;
   y = 0;
   dx = input->dx;
   dy = input->dy;
   a = input->a;
   err = -.5;

   point->x = &x;
   point->y = &y;
}

int next_point() {

   if(x > dx)
      return 0;

   x++;
   err+=a;
   if (err >= 0) {
      y++;
      err-=1;
   }

   return 1;
}

