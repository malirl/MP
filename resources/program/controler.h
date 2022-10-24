#include <stdio.h>
#include <stdlib.h>

typedef struct{
   int x, y;
	 struct point *next;
}point;

typedef struct{
	point *points;
	char name[10];
	int color;
}obj;


struct{
	obj objs[10];
}scene;


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



int init_render(void);
int resolve_window_events(void);
int render_obj(obj *obj);



void set_line(obj *obj, line *input);
void mirror_to_line(obj *obj, line *input);
void set_circle(obj *obj, circle *input);

