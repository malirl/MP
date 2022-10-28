#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   int x, y;
	 struct point *next;
}point;

typedef struct obj{
	point *points;
	/* obj *next */
}obj;

obj current_obj;

struct LIST_OBJS{
	obj obj;
	int color;
	char name[100];
	struct LIST_OBJS* next;
}*list_objs;


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


/* //////// */

static struct LIST_OBJS* new_obj(){
  return (struct LIST_OBJS*)malloc(sizeof(struct LIST_OBJS)); 
}

static void add_obj_to_list(){
   list_objs->next = new_obj(); 
   list_objs = list_objs->next;
   list_objs->next = NULL;
}

static void set_obj(obj obj){
	list_objs->obj = obj; 
}

static void add_obj(char name[]){
	obj *obj_to_set = (struct obj*)malloc(sizeof(obj));

	if(strcmp(name, "line") == 0)
		set_line(obj_to_set, &input_line);
	else if(strcmp(name, "circle") == 0)
		set_circle(obj_to_set, &input_circle);
	else if(strcmp(name, "mirror_to_line") == 0)
		set_mirror_to_line(obj_to_set, &input_mirror_to_line);
	else if(strcmp(name, "point") == 0)
		set_point(obj_to_set, &input_point);

	current_obj = *obj_to_set;
	set_obj(current_obj);
	add_obj_to_list();
}

/* get obj */

