#include <stdio.h>

typedef struct point{
   int x, y;
   struct point *next;
}point;

typedef struct{
	point *points;
}obj;

typedef struct{
	/* /1* int ax, ay, bx, by; *1/ !! */
	int ax;
	int ay;
	int bx;
	int by;
}line;

typedef struct{
   obj *obj;
   line *line;
}input;


void mirror_to_line(input *input, point **point);

