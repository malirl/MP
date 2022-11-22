#include <stdio.h>
/* #include <stdarg.h> */

typedef struct point{
   int x, y;
   struct point *next;
}point;


typedef struct obj{
	point *points;
	struct obj *sub,*next;
}obj;



/* void out(int status,int lvl,char* msg,const char* fmt,...); */
void example_(obj* obj,point **point);


