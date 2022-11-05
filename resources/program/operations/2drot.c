#include <stdio.h>
#include <math.h>
#include "../helpers.h"

typedef struct{
	point *points;
}obj;

typedef struct{
   double alpha;
   point *S;
   obj *obj;
}input;


static point *head, *current_point;
static double alpha, x1, y1, x2, y2;
static int Sx, Sy, x, y; 


static void solve() {
   /* nove souradnice os */
   x1 = cos(alpha);
   x2 = sin(alpha);
   y1 = -x2;
   y2 = x1;

   while(1) {
      x = head->x-Sx;
      y = head->y-Sy;

      /* "naneseni" bodu na souradnice os po rotaci */
      set_point((int)Sx + x*x1 + y*x2+.5, (int)Sy + x*y1 + y*y2+.5, &current_point);
      
      head = (point*)head->next;
      if(!head)
         return;

      add_point(&current_point);
   }
}


void rot2d(input *input, point **tracked_point) {
   head = (point*)input->obj->points;

   alpha = input->alpha; 

   Sx = input->S->x;
   Sy = input->S->y;

   current_point = new_point();
   *tracked_point = current_point;
   solve();
}

