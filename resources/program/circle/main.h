#include <stdio.h>

typedef struct{
   int r, sx, sy;
}input;

typedef struct point{
   int x, y;
   struct point *next;
}point;

typedef struct{
	point *points;
	int color;
}obj;


void circle_bresenham(input *input, point **point);

