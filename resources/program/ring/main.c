#include "main.h"

void set_ring(obj *ring, input *input) {
   ring_bresenham(input, &ring->points);
}

