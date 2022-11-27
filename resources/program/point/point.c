#define POINT_IN
#define HELPERS

#include <stdio.h>
#include "../inputs.h"


static int x, y; 
static point *current_point; 

static void solve() {
   point_set(x,y,&current_point);
}

void just_point(point *input, point **tracked_point) {
   x = input->x;
   y = input->y;
   current_point = point_new();
   *tracked_point = current_point;
   solve();
}

