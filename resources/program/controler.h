#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   int x, y;
	 struct point *next;
}point;

typedef struct obj{
	point *points;
	char name[10];
	int color;
}obj;


/* typedef struct{ */
/* 	obj* obj; */
/* 	struct scene* next; */
/* }scene; */

/* scene scene; */


/* inputy */

typedef struct{
	/* /1* int ax, ay, bx, by; *1/ !! */
	int ax;
	int ay;
	int bx;
	int by;
}line;

typedef struct{
	/* /1* int r, sx, sy; *1/ !! */
	int r;
	int sx;
	int sy;
}circle;

typedef struct{
	obj* obj;	
	int ax;
	int ay;
	int bx;
	int by;
}mirror_to_line;

point input_point; 
line input_line;
circle input_circle;
mirror_to_line input_mirror_to_line;


/* //////// */

int init_render(void);
int resolve_window_events(void);
int render_obj(obj *obj);


void set_point(obj *obj, point *input);
void set_line(obj *obj, line *input);
void set_circle(obj *obj, circle *input);
void set_mirror_to_line(obj *obj, mirror_to_line *input);

