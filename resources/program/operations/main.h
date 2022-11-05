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
}input_mirror_to_line;


typedef struct{
   double alpha;
   point *S;
   obj *obj;
}input_rot2d;



void mirror_to_line(input_mirror_to_line *input, point **point);
void rot2d(input_rot2d *input, point **point);

