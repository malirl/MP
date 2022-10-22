#include <stdio.h>

int x, y, d, r; 

typedef struct{
   int *x, *y;
}point;


typedef struct{
   int r;
}input;


void init_bresenham(input *input, point *point) {

   r = input->r;

   x = r;
   y = 0;
   d = 0;

   point->x = &x;
   point->y = &y;
}

int next_point() {

   d += 2*y+1;
   y++;

   if(x<y)
     return 0; 

   if(d>0) {
      d += 1-2*x;
      x--;
   }

   return 1;
}
