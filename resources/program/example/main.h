#include <stdio.h>
#include <stdarg.h>

typedef struct point{
   int x, y;
   struct point *next;
}point;

typedef struct{
	point *points;
	int color;
}obj;

void example_(point **point);
void out(int status,int lvl,char* msg,const char* fmt,...);


