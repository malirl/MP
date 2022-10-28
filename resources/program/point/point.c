#include <stdio.h>
#include "../helpers.h"

typedef point input;

static int x, y; 
static point *current_point; 

static void solve() {
   set_point(x,y,&current_point);
}

void just_point(input *input, point **tracked_point) {
   x = input->x;
   y = input->y;
   current_point = new_point();
   *tracked_point = current_point;
   solve();
}

