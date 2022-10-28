#include <stdio.h>

typedef struct point{
   int x, y;
   struct point *next;
}point, input;

typedef struct{
	point *points;
}obj;

void just_point(input *input, point **point);

