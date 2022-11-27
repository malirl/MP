#define POINT_IN
#define LINE_CONVERTED_IN 
#define HELPERS

#include <stdio.h>
#include "../inputs.h"

static int x, y, dx, dy, ax, ay, err, opt; 

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
      err+=2*dy;
      if (err >= 0) {
         y++;
         err-=2*dx;
      }

      point_add(&current_point);
      point_set(ax + *res_x, ay + mark_y * *res_y, &current_point);
   }

}


void line_bresenham(line_converted *input, point **tracked_point) {
   dx = input->dx;
   dy = input->dy;
   ax = input->ax;
   ay = input->ay;
   opt = input->opt;

   x = 0;
   y = 0;
   err = -dx;

   current_point = point_new(); 
   *tracked_point = current_point; 
   solve();
}

