#include "main.h" 

void mirror_to_line(obj *obj, input *line) {
   int px, py, bx, by, x, y, res_x, res_y;
   double k;

   px = line->ax;
   py = line->ay;
   x = line->bx-line->ax;
   y = line->by-line->ay; 

   point *head = (point*)obj->points;
   while(head) {

      bx = head->x;
      by = head->y;
      k = (double)(x*(bx-px)+y*(by-py))/(x*x+y*y);
      res_x = (int)2*(k*x+px)-bx+.5;
      res_y = (int)2*(k*y+py)-by+.5;

      head->x = res_x;
      head->y = res_y;

      head = (point*)head->next;
   }
}



void set_line(obj *line, input *input) {
   res res = convert_input(input);
   line_bresenham(&res, &line->points);
   /* line_dda(&res, &line->points); */

}

