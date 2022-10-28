#include <stdio.h>

typedef struct point{
   int x, y;
   struct point *next;
}point, input;

typedef struct{
	point *points;
	char name[10];
	int color;
}obj;

void just_point(input *input, point **point);

