#define POINT_IN
#define LINE_CONVERTED_IN 
#define HELPERS

#include <stdio.h>
#include "../inputs.h"

static int x, y, dx, dy, ax, ay, opt; 
static double a, err;

static void solve() {
   int *res_x, *res_y, mark_y = 1;

   switch(opt)
   {
      case 1:
         res_x = &y; 
         res_y = &x;
         break;
      case 2:
         res_x = &x;
         res_y = &y;
         break;
      case 3:
         res_x = &x;
         res_y = &y;
         mark_y = -1;
         break;
      case 4:
         res_x = &y;
         res_y = &x;
         mark_y = -1;
         break;
   }

   point_set(ax + *res_x, ay + mark_y * *res_y, &current_point);

   while(x < dx) {
      x++;
      err+=a;
      if (err >= 0) {
         y++;
         err-=1;
      }

      point_add(&current_point);
      point_set(ax + *res_x, ay + mark_y * *res_y, &current_point);
   }
}

void line_dda(line_converted *input, point **tracked_point) {
   dx = input->dx;
   dy = input->dy;
   ax = input->ax;
   ay = input->ay;
   a = input->a;
   opt = input->opt;

   x = 0;
   y = 0;
   err = -.5;

   current_point = point_new(); 
   *tracked_point = current_point; 

   solve();
}

