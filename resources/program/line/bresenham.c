#include <stdio.h>
#include "../helpers.h"


typedef struct{
   int ax, ay, dx, dy, opt;
   double a;
}input;


static int x, y, dx, dy, ax, ay, err, opt; 
static point *current_point; 


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
   

   set_point(ax + *res_x, ay + mark_y * *res_y, &current_point);

   while(x < dx) {

      x++;
      err+=2*dy;
      if (err >= 0) {
         y++;
         err-=2*dx;
      }

      add_point(&current_point);
      set_point(ax + *res_x, ay + mark_y * *res_y, &current_point);
   }

}


void line_bresenham(input *input, point **tracked_point) {
   dx = input->dx;
   dy = input->dy;
   ax = input->ax;
   ay = input->ay;
   opt = input->opt;

   x = 0;
   y = 0;
   err = -dx;

   current_point = new_point(); 
   *tracked_point = current_point; 
   solve();
}

