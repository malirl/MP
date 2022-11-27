#include "main.h"

void set_ring(obj *obj, ring *input) {
   ring_bresenham(input, &obj->points);
}

