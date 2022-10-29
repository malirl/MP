#include <stdio.h>

typedef struct point{
   int x, y;
   struct point *next;
}point;

typedef struct{
	point *points;
	int color;
}obj;

typedef struct{
   int r;
   point *S;
}input;



void circle_bresenham(input *input, point **point);

