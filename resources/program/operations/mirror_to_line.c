#include <stdio.h>
#include "../helpers.h"

typedef struct{
	point *points;
}obj;

typedef struct{
	/* /1* int ax, ay, bx, by; *1/ !! */
	int ax;
	int ay;
	int bx;
	int by;
}line;

typedef struct{
   obj *obj;
   line *line;
}input;


static point *head, *current_point;
static int px, py, bx, by, x, y, res_x, res_y;
static double k;

static void solve() {
   while(1) {
      bx = head->x;
      by = head->y;
      k = (double)(x*(bx-px)+y*(by-py))/(x*x+y*y);
      res_x = (int)2*(k*x+px)-bx+.5;
      res_y = (int)2*(k*y+py)-by+.5;

      set_point(res_x, res_y, &current_point);
      
      head = (point*)head->next;

      if(!head)
         return;

      add_point(&current_point);
  }
}


void mirror_to_line(input *input, point **tracked_point) {
   head = (point*)input->obj->points;

   px = input->line->ax;
   py = input->line->ay;
   x = input->line->bx-input->line->ax;
   y = input->line->by-input->line->ay;

   current_point = new_point();
   *tracked_point = current_point;
   solve();
}

