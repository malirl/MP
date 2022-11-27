#define POINT_IN
#define CIRCLE_IN
#define HELPERS

#include <stdio.h>
#include "../inputs.h"

static int sx, sy, r;

static void solve() {
   int x = 0, y = 0;

   point_set(sx, sy, &current_point);

   for(x = -r;x <= r;x++) {
      for(y = -r;y <= r;y++) {
         if(x*x+y*y<=r*r) {
            point_add(&current_point);
            point_set(sx + x, sy + y, &current_point);
         }
      }
   }
}

void circle_(circle *input, point **tracked_point) {
   r = input->r;

   sx = input->S->x;
   sy = input->S->y;

   current_point = point_new();
   *tracked_point = current_point;
   solve();
}

