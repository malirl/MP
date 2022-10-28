#include <stdio.h>

typedef struct point{
   int x, y;
   struct point *next;
}point;

typedef struct{
	point *points;
	char name[10];
	int color;
}obj;

typedef struct{
   obj *obj;
   int ax;
   int ay;
   int bx;
   int by;
}input;


void mirror_to_line(input *input, point **point);

