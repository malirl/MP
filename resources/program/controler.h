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
#define STR 2 

#define NONE -1
#define EXAMPLE 0
#define LINE 1
#define CIRCLE 2
#define RING 3
#define POLYGON 4
#define OBJ 5

#define MAX_NUMBER_POLYGON_LINES 100

char* obj_input[][3] = {
	{"example", "\0"},
	{"line", "n:ax n:ay n:bx n:by"},
	{"circle", "n:Sx n:Sy n:r"},
	{"ring", "n:Sx n:Sy n:r"},
	{"polygon","*line:line"}
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

typedef struct{
		int n_lines;
   line lines[MAX_NUMBER_POLYGON_LINES];
}polygon;

point input_point; 
line input_line;
ring input_ring;
circle input_circle;
mirror_to_line input_mirror_to_line;
rot2d input_rot2d;
polygon input_polygon;

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


/* char */
/* 	*args_types_line[] = {"int","int","int","int"}, */
/* 	*args_types_ring[] = {"int","obj"}, */
/* 	*args_types_circle[] = {"int","obj"}; */

/* char** args_objs[]= { */
/* 	&args_types_line, */
/* 	&args_types_ring */
/* }; */



static void init_data() {
	input_ring.S = (point*)malloc(sizeof(point));
	input_circle.S = (point*)malloc(sizeof(point));
	input_rot2d.S = (point*)malloc(sizeof(point));

	input_polygon.n_lines=0;

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

static void make_obj(char name[]){
	last_obj = *get_obj(name);
	set_obj_in_list(last_obj,name);
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
		case STR:
			break;
		/* case OBJ: */
		/* 	if(!get_obj_input(val,input_obj)){ */
		/* 		out(ERR,1,"","%s expected an object!",arg_name); */
		/* 		return false; */
		/* 	} */
			/* break; */
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


bool proc_obj(char *name,char *input, bool cmd);


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

	char* type;
	int type_arg;

	char tmp[20]; //20 delka nazvu jednoho argumentu
	int n_arg = 0;

	bool is_loop; // pro mozny nekonecny vyskyt parametru v zadani 

	int in_text_idx,in_text_len;

	while(1){
		get_from_str(":(\\w+)",args,&pattern,&idx,&len);

		
		if(!pattern)
			return true;


		if(!(is_loop = (args_arr[0]=='*')  ? true : false))
			++n_arg;



		get_from_str(pattern,str_input,&in_text,&idx,&len);

		if(!in_text){
			if(is_loop)
				is_loop=false;
			else if(cmd){
				out(ERR,1,"missing mandatory param: ","%s",pattern);
				return false;
			}
		} else {
			in_text_idx = idx;



			memset(tmp,0,strlen(tmp));
			get_arr(pattern,tmp);


			get_from_str("(\\w+):\\w+",args,&type,&idx,&len);
			in_text_len = strlen(type)+1;



			if(strcmp(type,"n")==0 || strcmp(type,"str")==0)
				replace_str_by(":([^,\\s]*)",tmp,strlen(pattern));	
			else
				replace_str_by(":([^\\s]*)",tmp,strlen(pattern));	


			val = (char*)malloc(sizeof(char));
			get_from_str(tmp,str_input,&val,&idx,&len);

			if(!val){
				out(ERR,1,"missing value for param: ","%s",pattern);
				return false;
			}


			in_text_len += strlen(val);

			
			if(strcmp(type,"n")==0)
				type_arg = INT;
			else if(strcmp(type,"str")==0)
				type_arg = STR;
			else{ // objekt
				type_arg = NONE;

				if(!proc_obj(type,val,true))
					return false;

				switch(obj_id){
					case POLYGON:
						input_polygon.lines[input_polygon.n_lines]=input_line;
						++input_polygon.n_lines;
						break;
				}
			
			}

			if(type_arg != NONE){
				if(set_arg(obj_id,n_arg,val,type_arg,pattern))
					out(SUCCESS,1,"","%s assigned to '%s'",pattern,val);
				else
					return false;
			}
		}

		if(is_loop)
			rm_range(str_input_arr,in_text_idx,in_text_len);
		else{
			get_from_str("\\*?\\w+:\\w+",args,&pattern,&idx,&len);
			rm_range(args_arr,0,len+1);
		}
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


bool set_obj(int id){
	switch(id){
		case EXAMPLE:
			make_obj("example");
			break;
		case LINE:
			make_obj("line");
			break;
		case CIRCLE:
			make_obj("circle");
			break;
	}
	return true;
}



int get_obj_id_by_name(char* name){
	int obj_id;
	if(strcmp(name, "line") == 0)
		obj_id = LINE;
	else if(strcmp(name, "circle") == 0)
		obj_id = CIRCLE;
	else if(strcmp(name, "example") == 0)
		obj_id = EXAMPLE;
	else if(strcmp(name, "polygon") == 0)
		obj_id = POLYGON;

	else{
		out(ERR,1,"unknown obj: ","'%s'",name);
		obj_id = NONE;
	}
	return obj_id;
}


bool proc_obj(char *name,char *input,bool cmd){
	int obj_id = get_obj_id_by_name(name);

	if(obj_id==NONE)
		return false;

	out(INFO,1,"processing sub object: ","%s",name);
	return check_mandatory_args(input,obj_input[obj_id][1],obj_id,cmd);
}

bool proc_obj_cmd(int argc,char *argv[]){
	int obj_id = get_obj_id_by_name(argv[1]);

	if(obj_id==NONE)
		return false;

	out(INFO,0,"processing object: ","%s",argv[1]);
	if(!proc_obj_input_cmd(argv,argc,obj_input[obj_id][1],obj_id))
		return false;
	return set_obj(obj_id);
}


