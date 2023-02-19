#include <stdio.h>
#include <stdbool.h>

/* #include <stdarg.h> */

#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define POLYGON_IN
#define POLYGON_CONVERTED_IN

#include "../inputs.h"


polygon_converted convert_polygon_input(polygon *input);
bool valid_polygon(polygon_converted *input);
void _set_polygon(polygon_converted *input,obj* obj);
void _set_polygon_fill(polygon *input,point **point);


