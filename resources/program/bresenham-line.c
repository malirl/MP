#include <stdio.h>

int x, y, dx, dy, err; 

typedef struct point{
   int *x, *y;
}point;


typedef struct res{
   int ax, ay, dx, dy, opt;
}res;


point init_bresenham(res *input) {
   x = 0;
   y = 0;
   dx = input->dx;
   dy = input->dy;
   err = -2*dx;

   point point;
   point.x = &x;
   point.y = &y;
   return point; 
}

int next_point() {

   if(x > dx)
      return 0;

   x++;

   if (err >= 0) {
      y++;
      err-=2*dx;
   }
   err+=2*dy;

   return 1;
}

