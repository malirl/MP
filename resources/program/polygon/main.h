#include <stdio.h>
/* #include <stdarg.h> */

typedef struct point{
   int x, y;
   struct point *next;
}point;


#define MAX_NUMBER_POLYGON_LINES 100

typedef struct{
	int ax;
	int ay;
	int bx;
	int by;
}line;

typedef struct{
		int n_lines;
   line lines[MAX_NUMBER_POLYGON_LINES];
}input;


typedef struct obj{
	point *points;
	struct obj *sub,*next;
}obj;



/* void out(int status,int lvl,char* msg,const char* fmt,...); */
void _set_polygon(input *input,obj* obj);

