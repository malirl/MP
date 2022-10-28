#include "main.h" 

void set_line(obj *line, input *input) {
   res res = convert_input(input);
   line_bresenham(&res, &line->points);
   /* line_dda(&res, &line->points); */
}

