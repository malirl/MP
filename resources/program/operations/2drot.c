#define POINT_IN
#define OBJ_IN
#define ROT2D_IN
#define HELPERS

#include <stdio.h>
#include <math.h>
#include "../inputs.h"

static point *head;
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
      point_set((int)Sx + x*x1 + y*x2+.5, (int)Sy + x*y1 + y*y2+.5, &current_point);
      
      head = (point*)head->next;
      if(!head)
         return;

      point_add(&current_point);
   }
}

void _rot2d(rot2d *input, point **tracked_point) {
   Sx = input->S->x;
   Sy = input->S->y;
   alpha = input->alpha; 
   head = (point*)input->obj->points;

   current_point = point_new();
   *tracked_point = current_point;
   solve();
}

