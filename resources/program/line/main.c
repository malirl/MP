#include "main.h" 

void set_line(obj *obj,line *input) {
   line_converted res = convert_input_line(input);
   line_bresenham(&res, &obj->points);
   /* line_dda(&res, &obj->points); */
}

