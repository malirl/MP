#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define LINE_CONVERTED_IN 

#include <stdio.h>
#include "../inputs.h"

line_converted convert_input_line(line *input);
void line_dda(line_converted *res, point **point);
void line_bresenham(line_converted *res, point **point);

