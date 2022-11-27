#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define MIRROR_TO_LINE_IN 
#define HELPERS

#include <stdio.h>
#include "../inputs.h"

static point *head;
static int px, py, bx, by, x, y, res_x, res_y;
static double k;

static void solve() {
   while(1) {
      bx = head->x;
      by = head->y;
      k = (double)(x*(bx-px)+y*(by-py))/(x*x+y*y);
      res_x = (int)2*(k*x+px)-bx+.5;
      res_y = (int)2*(k*y+py)-by+.5;

      point_set(res_x, res_y, &current_point);
      
      head = (point*)head->next;

      if(!head)
         return;

      point_add(&current_point);
  }
}

void _mirror_to_line(mirror_to_line *input, point **tracked_point) {
   head = (point*)input->obj->points;

   px = input->line->ax;
   py = input->line->ay;
   x = input->line->bx-input->line->ax;
   y = input->line->by-input->line->ay;

   current_point = point_new();
   *tracked_point = current_point;
   solve();
}

