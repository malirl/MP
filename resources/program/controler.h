#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "tiny-regex-c/re.h"

#include "strs.h"
#include "log.h"

#define INT 1
#define TXT 2 

#define LINE 1
#define RING 2
#define CIRCLE 3 
#define EXAMPLE 4


char* obj_input[][2] = {
	{"line", "ax ay bx by"},
	{"circle", "Sx Sy r"},
	{"ring", "Sx Sy"},
	{"example", "\0"},
	{NULL, ""}
};


typedef struct{
   int x, y;
	 struct point *next;
}point;


typedef struct obj{
	point *points;
	struct obj *sub;
  struct obj *next;
}obj;


obj last_obj;

struct LIST_OBJS{
	obj obj;
	char *type, *name;
	int color;
	struct LIST_OBJS* next;
}*list_objs, *start_obj;

/* typedef char* args; */
/* args mandatory[], opt[]; */
/* struct input_args{ */
/* 	int a; */
/* 	args* man; */
/* }OBJ_ARGS; */



/* const int num_of_avaible_cmds = 6; */
/* char* available_cmds[6] = { */
/* 	"point","line","ring","circle","mirror_to_line","rot2d" */
/* }; */


/* inputy */
/* #define _input input; */ 


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
}ring, circle;

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
circle input_circle;
mirror_to_line input_mirror_to_line;
rot2d input_rot2d;

/* //////// */


int init_render(void);
int resolve_window_events(void);
bool render(obj *obj);


void set_point(obj *obj, point *input);
void set_example(obj *obj);
void set_line(obj *obj, line *input);
void set_ring(obj *obj, ring *input);
void set_circle(obj *obj, ring *input);
void set_mirror_to_line(obj *obj, mirror_to_line *input);
void set_rot2d(obj *obj, rot2d *input);


/* //////// */


char
	*args_types_line[] = {"int","int","int","int"},
	*args_types_ring[] = {"int","obj"},
	*args_types_circle[] = {"int","obj"};

/* char** args_objs[]= { */
/* 	&args_types_line, */
/* 	&args_types_ring */
/* }; */



static void init_data() {
	input_ring.S = (point*)malloc(sizeof(point));
	input_circle.S = (point*)malloc(sizeof(point));
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
	obj_to_set->sub=obj_to_set->next=NULL;
	obj_to_set->points=NULL;

	if(strcmp(name, "example") == 0)
		set_example(obj_to_set);
	else if(strcmp(name, "line") == 0)
		set_line(obj_to_set, &input_line);
	else if(strcmp(name, "ring") == 0)
		set_ring(obj_to_set, &input_ring);
	else if(strcmp(name, "circle") == 0)
		set_circle(obj_to_set, &input_circle);
	else if(strcmp(name, "mirror_to_line") == 0)
		set_mirror_to_line(obj_to_set, &input_mirror_to_line);
	else if(strcmp(name, "rot2d") == 0)
		set_rot2d(obj_to_set, &input_rot2d);
	else if(strcmp(name, "point") == 0)
		set_point(obj_to_set, &input_point);

	return obj_to_set;
}

static void make_obj(char name[],bool is_anonym){
	last_obj = *get_obj(name);
	set_obj_in_list(last_obj,name);
	if(!is_anonym)
		add_obj_to_list();
}

/* //////// */

bool get_int(char* num, int* res){
	*res=0;

	if(!num)
		return false;

	int digit;
	int len = strlen(num); 
	for(int i=0;i<len;++i){
		digit=*(num+i)-'0';
		if(digit>=0 && digit<=10)
			*res+=((pow(10,strlen(num)-i-1)))*digit;
		else
			return false;
	}
	return true;	
}


void set_args(int obj_id,int nums[],char* strs[]){
	/* !! */
	switch(obj_id){
		case LINE:
				input_line.ax=nums[0];
				input_line.ay=nums[1];
				input_line.bx=nums[2];
				input_line.by=nums[3];
			break;
		case CIRCLE:
			break;
		case RING:
			break;
	}
}



bool set_arg(int obj,int arg,char* val,int type,char* arg_name){
	int Z;

	/* validace čísla, textu... */
	switch(type){
		case INT:
			if(!get_int(val,&Z)){
				out(ERR,1,"","%s expected an integer!",arg_name);
				return false;
			}
			break;
		case TXT:
			break;
	}

	/* !vlastní validace (omezený zadání) */	

	switch(obj){
		case LINE:
			switch(arg){
				case 1:
					input_line.ax=Z;
					break;
				case 2:
					input_line.ay=Z;
					break;
				case 3:
					input_line.bx=Z;
					break;
				case 4:
					input_line.by=Z;
					break;
			}
			break;
		case CIRCLE:
			switch(arg){
				case 1:
				   input_circle.S->x=Z;
					break;
				case 2:
				   input_circle.S->y=Z;
					break;
				case 3:
					input_circle.r=Z;
					break;
			}
			break;
	}

	return true;
}

bool check_mandatory_args(char* str_input,char* args,int obj_id,bool cmd){
	/* vyhledej v args, arg, ktery jednotlive pouzijes a odstranujes dokud neni match=-1 */
	/* 	kdyz to pritom nenajdes, dej chybu */

	if(strcmp(args,"")==0) //!!
		return true;

	char *pattern, *in_text, *val;
	char args_arr[strlen(args)+1], str_input_arr[strlen(str_input)+1];
	int idx,len;
	get_arr(args,args_arr);
	args=(char*)args_arr;
	get_arr(str_input,str_input_arr);
	str_input=(char*)str_input_arr;

	char tmp[20]; //20 delka nazvu jednoho argumentu
	int n_arg = 0;

	while(1){
		get_from_str("\\w+",args,&pattern,&idx,&len);

		if(!pattern)
			return true;

		++n_arg;
		get_from_str(pattern,str_input,&in_text,&idx,&len);

		if(!in_text){
			if(cmd){
				out(ERR,1,"missing mandatory param: ","%s",pattern);
				return false;
			}
		} else {
			memset(tmp,0,strlen(tmp));
			get_arr(pattern,tmp);
			replace_str_by(":(\\d+)",tmp,strlen(pattern));	

			val = (char*)malloc(sizeof(char));

			get_from_str(tmp,str_input,&val,&idx,&len);

			if(set_arg(obj_id,n_arg,val,INT,pattern))
				out(SUCCESS,1,"","%s assigned to '%s'",pattern,val);
			else
				return false;

		}
		rm_range(args_arr,0,strlen(pattern)+1);
	}
}


bool proc_obj_input_cmd(char *argv[],int argc,char* args,int obj_id) {
	char str_input[100];
	size_t n_ch = -1;
	for(int arg=2;arg<argc;++arg){
		for(size_t i=0;i<strlen(argv[arg]);++i) {
			str_input[++n_ch] = *(argv[arg]+i);
			str_input[n_ch+1] = '\0';
		}
		str_input[++n_ch] = ' ';
		str_input[n_ch+1] = '\0';
	}
	return check_mandatory_args(str_input,args,obj_id,true);
}


bool set_obj(int id,bool is_anonym){
	switch(id){
		case EXAMPLE:
			make_obj("example",is_anonym);
			break;
		case LINE:
			make_obj("line",is_anonym);
			break;
		case CIRCLE:
			make_obj("circle",is_anonym);
			break;
	}
	return true;
}


void proc_obj(char *name,char *input){
	/* single object set */
	char* selected;
	int	i=-1, obj_id;

	while(1){
		if(!(selected=obj_input[++i][0]))//takovy nazev pro obj se nenaseL
		{
			out(ERR,1,"unknown obj: ","'%s'",name);
			return;
		}

		if(compare_strs(selected, name)){
			out(INFO,1,"processing sub object: ","%s",name);

			if(strcmp(name, "line") == 0)
				obj_id = LINE;
			else if(strcmp(name, "circle") == 0)
				obj_id = CIRCLE;
			else if(strcmp(name, "example") == 0)
				obj_id = EXAMPLE;

			if(check_mandatory_args(input,obj_input[i][1],obj_id,false))
				set_obj(obj_id,true);

			return;
		}
	}
}






bool proc_obj_cmd(int argc,char *argv[]){
	/* single object set */
	char* selected, *main_arg = argv[1];
	int	i=-1, obj_id;

	while(1){
		if(!(selected=obj_input[++i][0]))//takovy nazev pro obj se nenaseL
		{
			out(ERR,0,"unknown obj: ","'%s'",main_arg);
			return false;
		}

		if(compare_strs(selected, main_arg)){
			out(INFO,0,"processing object: ","%s",main_arg);

			if(strcmp(main_arg, "line") == 0)
				obj_id = LINE;
			else if(strcmp(main_arg, "circle") == 0)
				obj_id = CIRCLE;
			else if(strcmp(main_arg, "example") == 0)
				obj_id = EXAMPLE;

			if(!proc_obj_input_cmd(argv,argc,obj_input[i][1],obj_id))
				return false;
			break;
		}
	}
	return set_obj(obj_id,false);
}


