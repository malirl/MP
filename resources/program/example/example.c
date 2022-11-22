#include <stdio.h>
#include "../helpers.h"


#define LINE 1
#define RING 2
#define CIRCLE 3 
#define EXAMPLE 4

typedef struct obj{
	point *points;
	struct obj *sub;
  struct obj *next;
}obj;

/* /1* static void make_obj_uniform(){ *1/ */

/* /1* } *1/ */

obj* get_obj(char name[]);
obj* proc_obj(char *name,char* input);
obj* set_args(int name,int nums[],char* strs[]); 

static point *current_point; 
static obj *current_obj;

static struct obj* new_obj() {
  obj* to_get=(obj*)malloc(sizeof(struct obj));  
	to_get->sub=to_get->next=NULL;
	to_get->points=NULL;
  return to_get;
}

static void next(obj *to_set,obj *next){
  to_set->next=current_obj=next; 
}
static void sub(obj *to_set,obj *sub){
  to_set->sub=current_obj=sub;
}


static int num_args[10];
static char* str_args[10]; 

static void solve() {

   set_point(0, 0, &current_point);
   /* add_point(&current_point); */

  /* 1. varianta pridavani podobjekty */ 
   /* proc_obj("line","ay:200 by:34 ax:100 bx:100"); */
   /* sub(current_obj,get_obj("line")); */
   proc_obj("line","by:600 ax:200 bx:600"); // neuplny zadani povoleno 
   sub(current_obj,get_obj("line"));
   proc_obj("circle","Sx:500 Sy:500 r:60");
   sub(current_obj,get_obj("circle"));
   proc_obj("line","by:700 ax:700 bx:800"); 
   sub(current_obj,get_obj("line"));

  /* 2. varianta pro predem neznamy hodnoty parametru*/ 
   num_args[0]=200;
   num_args[1]=34;
   num_args[2]=100;
   num_args[3]=100;
   set_args(LINE,num_args,str_args);
   sub(current_obj,get_obj("line"));





}

/* obj *obj, */
void example_(obj* obj,point **tracked_point) {
    *tracked_point = current_point = new_point();
    current_obj=obj;
   solve();
}

