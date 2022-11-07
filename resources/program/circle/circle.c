#include <stdio.h>
#include "../helpers.h"

typedef struct{
   int r;
   point *S;
}input;

static int sx, sy, r;
static point *current_point; 


static void solve() {
   int x = 0, y = 0;

   set_point(sx, sy, &current_point);

   for(x = -r;x <= r;x++) {
      for(y = -r;y <= r;y++) {
         if(x*x+y*y<=r*r) {
            add_point(&current_point);
            set_point(sx + x, sy + y, &current_point);
         }
      }
   }


}


void circle_(input *input, point **tracked_point) {
   r = input->r;

   sx = input->S->x;
   sy = input->S->y;

   current_point = new_point();
   *tracked_point = current_point;
   solve();
}

