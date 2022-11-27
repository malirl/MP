#define POINT_IN
#define RING_IN 
#define HELPERS

#include <stdio.h>
#include "../inputs.h"

static int sx, sy, r, x, y, d; 

static void solve() {
   point_set(sx + x, sy + y, &current_point);

   while(x>=y) {
      
      point_add(&current_point);
      point_set(sx + x, sy + y, &current_point);

      point_add(&current_point);
      point_set(sx + y, sy + x, &current_point);

      point_add(&current_point);
      point_set(sx - y, sy + x, &current_point);

      point_add(&current_point);
      point_set(sx - x, sy + y, &current_point);

      point_add(&current_point);
      point_set(sx - x, sy - y, &current_point);

      point_add(&current_point);
      point_set(sx + x, sy - y, &current_point);

      point_add(&current_point);
      point_set(sx + y, sy - x, &current_point);

      point_add(&current_point);
      point_set(sx - y, sy - x, &current_point);

      d += 2*y+1;
      y++;

      if(d>0) {
         d += 1-2*x;
         x--;
      }
   }
}

void ring_bresenham(ring *input, point **tracked_point) {
   r = input->r;
   sx = input->S->x;
   sy = input->S->y;

   x = r;
   y = 0;
   d = 0;

   current_point = point_new();
   *tracked_point = current_point;
   solve();
}

