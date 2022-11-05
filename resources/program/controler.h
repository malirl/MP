#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   int x, y;
	 struct point *next;
}point;

typedef struct obj{
	point *points;
	struct obj *next;
}obj;

obj last_obj;

struct LIST_OBJS{
	obj obj;
	char *type, *name;
	int color;
	struct LIST_OBJS* next;
}*list_objs, *start_obj;


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
	point *S;
}ring;

typedef struct{
	obj* obj;	
	line* line;
}mirror_to_line;

typedef struct{
   double alpha;
   point *S;
   obj *obj;
}rot2d;

point input_point; 
line input_line;
ring input_ring;
mirror_to_line input_mirror_to_line;
rot2d input_rot2d;

/* //////// */

int init_render(void);
int resolve_window_events(void);
int render_obj(obj *obj);


void set_point(obj *obj, point *input);
void set_line(obj *obj, line *input);
void set_ring(obj *obj, ring *input);
void set_mirror_to_line(obj *obj, mirror_to_line *input);
void set_rot2d(obj *obj, rot2d *input);

/* //////// */

static void init_data() {
	input_ring.S = (point*)malloc(sizeof(point));
	input_rot2d.S = (point*)malloc(sizeof(point));
}

static struct LIST_OBJS* new_obj(){
  return (struct LIST_OBJS*)malloc(sizeof(struct LIST_OBJS)); 
}

static void add_obj_to_list(){
   list_objs->next = new_obj(); 
   list_objs = list_objs->next;
   list_objs->next = NULL;
}

static void set_obj_in_list(obj obj, char name[]){
	list_objs->obj = obj; 
	list_objs->name = name;
}

obj *get_obj(char name[]) {
	obj *obj_to_set = (struct obj*)malloc(sizeof(obj));

	if(strcmp(name, "line") == 0)
		set_line(obj_to_set, &input_line);
	else if(strcmp(name, "ring") == 0)
		set_ring(obj_to_set, &input_ring);
	else if(strcmp(name, "mirror_to_line") == 0)
		set_mirror_to_line(obj_to_set, &input_mirror_to_line);
	else if(strcmp(name, "rot2d") == 0)
		set_rot2d(obj_to_set, &input_rot2d);
	else if(strcmp(name, "point") == 0)
		set_point(obj_to_set, &input_point);
	return obj_to_set;
}

static void make_obj(char name[]){
	last_obj = *get_obj(name);
	set_obj_in_list(last_obj,name);
	add_obj_to_list();
}

