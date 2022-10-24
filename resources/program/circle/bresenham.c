#include <stdio.h>
#include "../helpers.h"

typedef struct{
   int r, sx, sy;
}input;

static int sx, sy, r, x, y, d; 
static point *current_point; 


static void solve() {

   set_point(sx + x, sy + y, &current_point);

   while(x>=y) {
      
      add_point(&current_point);
      set_point(sx + x, sy + y, &current_point);

      add_point(&current_point);
      set_point(sx + y, sy + x, &current_point);

      add_point(&current_point);
      set_point(sx - y, sy + x, &current_point);

      add_point(&current_point);
      set_point(sx - x, sy + y, &current_point);

      add_point(&current_point);
      set_point(sx - x, sy - y, &current_point);

      add_point(&current_point);
      set_point(sx + x, sy - y, &current_point);

      add_point(&current_point);
      set_point(sx + y, sy - x, &current_point);

      add_point(&current_point);
      set_point(sx - y, sy - x, &current_point);

      d += 2*y+1;
      y++;

      if(d>0) {
         d += 1-2*x;
         x--;
      }
   }
}


void circle_bresenham(input *input, point **tracked_point) {

   r = input->r;
   sx = input->sx;
   sy = input->sy;

   x = r;
   y = 0;
   d = 0;

   current_point = new_point();
   *tracked_point = current_point;

   solve();
}

