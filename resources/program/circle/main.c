#include "main.h"

void set_circle(obj *circle, input *input) {
   circle_bresenham(input, &circle->points);
}

