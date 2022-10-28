#include <stdio.h>

typedef struct{
 int ax, ay, bx, by;
}input;

/* v poradi: bod a, bod b vuci a, parametr pro zpetny prevod */
typedef struct{
   int ax, ay, dx, dy, opt;
   double a;
}res;

typedef struct point{
   int x, y;
   struct point *next;
}point;

typedef struct{
	point *points;
}obj;


res convert_input(input *input);
void line_dda(res *res, point **point);
void line_bresenham(res *res, point **point);

