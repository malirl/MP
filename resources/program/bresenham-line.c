#include <stdio.h>

int x, y, dx, dy, err; 

typedef struct point{
   int *x, *y;
}point;


typedef struct res{
   int ax, ay, dx, dy, opt;
   double a;
}res;


void init_bresenham(res *input, point *point) {
   x = 0;
   y = 0;
   dx = input->dx;
   dy = input->dy;
   err = -dx;

   point->x = &x;
   point->y = &y;
}

int next_point() {

   if(x > dx)
      return 0;

   x++;
   err+=2*dy;
   if (err >= 0) {
      y++;
      err-=2*dx;
   }

   return 1;
}

