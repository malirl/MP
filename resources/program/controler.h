#define EVERYTHING_IN

#define INT 1
#define STR 2 

#define NONE -1
#define EXAMPLE 0
#define LINE 1
#define CIRCLE 2
#define RING 3
#define POLYGON 4
#define POINT 5
#define CUBE_EXAMPLE 6
#define POLYGON_FILL 7

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "tiny-regex-c/re.h"
#include "inputs.h"
#include "scene.h"  
#include "strs.h"
#include "log.h"


point* point_new() {
	point *new_point=(point*)malloc(sizeof(point)); 
	new_point->next=NULL;
	return new_point;
}

void point_add(point **prev_point) {
	(*prev_point)->next = (struct point*)point_new(); 
	*prev_point = (point*)(*prev_point)->next;
}

void point_set(int x,int y,point **prev_point) {
	(*prev_point)->x = x;
	(*prev_point)->y = y;
	(*prev_point)->next = NULL;
}

void point3d_set(int x,int y,int z,point **prev_point) {
	(*prev_point)->x = x;
	(*prev_point)->y = y;
	(*prev_point)->z = z;
	(*prev_point)->next = NULL;
}

struct obj* obj_new() {
	obj* to_get=(obj*)malloc(sizeof(struct obj));  
	to_get->sub=to_get->next=NULL;
	to_get->points=NULL;
	return to_get;
}

void obj_next(obj **current,obj *next){
	(*current)->next=next; 
	*current=next;
}

void obj_sub(obj **current,obj *sub){
	(*current)->sub=sub; 
	*current=sub;
}


char* obj_input[][6] = {
	{"example", "\0", "2d"},
	/* {"line", "n:ax n:ay n:bx n:by", "2d"}, */
	{"line", "point:A point:B", "2d"},
	{"circle", "n:Sx n:Sy n:r", "2d"},
	{"ring", "n:Sx n:Sy n:r", "2d"},
	{"polygon","*point:point", "2d"},
	{"point", "n:x n:y", "2d"},
	{"cube-example", "\0", "3d"},
	{"polygon-fill", "*point:point", "2d"}
};


/* //////// */
struct LIST_OBJS{
	obj obj;
	char *type, *name;
	int color;
	struct LIST_OBJS* next;
}*list_objs, *start_obj;
obj last_obj;

point input_point; 
line input_line;
ring input_ring;
circle input_circle;
mirror_to_line input_mirror_to_line;
rot2d input_rot2d;
rot3d input_rot3d;
polygon input_polygon, input_polygon_fill;

void copy_line_input(line *input){
	input_line=*input;
}

/* void create_line_input(int x1,int x2,int y1,int y2){ */
/* 	input_point.x=x1; */
/* 	input_point.y=y1; */
/* 	input_line.A=input_point; */

/* 	input_point.x=x2; */
/* 	input_point.y=y2; */
/* 	input_line.B=input_point; */
/* } */

void copy_point_input(point *input){
	input_point=*input;
}


void set_resolution(int w,int h);
void shift(int x,int y);
int init_render();
int resolve_window_events(void);
bool render(point *points);
void re_render(point *points,bool zoom);

void set_point(obj *obj, point *input);
void set_example(obj *obj);
void set_cube_example(obj *obj);
void set_line(obj *obj, line *input);
void set_ring(obj *obj, ring *input);
void set_circle(obj *obj, circle *input);
void set_mirror_to_line(obj *obj, mirror_to_line *input);
void set_rot2d(obj *obj, rot2d *input);
void set_rot3d(obj *obj, rot3d *input);
bool set_polygon(obj *obj, polygon *input);
bool set_polygon_fill(obj *obj, polygon *input);
/* //////// */

point *point_scene;

static void init_data() {
	input_ring.S = (point*)malloc(sizeof(point));
	input_circle.S = (point*)malloc(sizeof(point));
	input_rot2d.S = (point*)malloc(sizeof(point));
	input_rot3d.O = (point*)malloc(sizeof(point));
	input_polygon.n_points=0;
	input_polygon_fill.n_points=0;
}

static struct LIST_OBJS* new_obj(){
	return (struct LIST_OBJS*)malloc(sizeof(struct LIST_OBJS)); 
}

static void add_obj_to_list(){
	list_objs->next=new_obj(); 
	list_objs=list_objs->next;
	list_objs->next=NULL;
}

static void set_obj_in_list(obj obj, char *name){
	list_objs->obj=obj; 
	list_objs->name=name;
}

obj *get_obj(char name[]) {
	obj *obj_to_set = (struct obj*)malloc(sizeof(obj));
	obj_to_set->sub=obj_to_set->next=NULL;
	obj_to_set->points=NULL;
	bool is_set_success=true;

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
	else if(strcmp(name, "rot3d") == 0)
		set_rot3d(obj_to_set, &input_rot3d);
	else if(strcmp(name, "point") == 0)
		set_point(obj_to_set, &input_point);
	else if(strcmp(name, "polygon") == 0)
		is_set_success=set_polygon(obj_to_set, &input_polygon);
	else if(strcmp(name, "polygon-fill") == 0)
		is_set_success=set_polygon_fill(obj_to_set, &input_polygon);
	else if(strcmp(name, "cube-example") == 0)
		set_cube_example(obj_to_set);



	if(!is_set_success){
		out(ERR,0,"validation failed","");
		return NULL;
	}
	return obj_to_set;
}

int round_double(double num){
	if(num<0)
		return (int)num-.5;
	return (int)num+.5;
}

struct{
	point *tmp, *buff_points_for3d;
	line *lines;
}tmp;

void points_3d_to_2d(obj *obj){
	double x,y,z,k;
	point *head=(point*)obj->points;
	point *converted_point=tmp.tmp=point_new();
	point v,B;

	while(1){
		x=head->x;
		y=head->y;
		z=head->z;

		v.x=x-scene_.Pabs.x;
		v.y=y-scene_.Pabs.y;
		v.z=z-scene_.Pabs.z;

		/* v preved do S, vysledkem je bod B vuci S*/ 
		B.x=scene_.X.x*v.x+scene_.X.y*v.y+scene_.X.z*v.z;
		B.y=scene_.Y.x*v.x+scene_.Y.y*v.y+scene_.Y.z*v.z;
		B.z=scene_.Z.x*v.x+scene_.Z.y*v.y+scene_.Z.z*v.z;

		/* urci vysledny souradnice x a y na "plose" */
		x=B.x-scene_.focus.x;
		y=B.y-scene_.focus.y;
		z=B.z-scene_.focus.z;
		k=(1-B.z)/z;

		/* urci v=P-B */
		/* printf("\n%f\n",x+x*k+WIDTH/2); */
		point_set(round_double(B.x+x*k+WIDTH/2),round_double(B.y+y*k+WIDTH/2),&converted_point);
		if(!(head=(point*)head->next))
			return;
		point_add(&converted_point);
	}
}


void rot_in_polar(double a,double b,point* to_rot){
	double x=to_rot->x,y=to_rot->y,z=to_rot->z;
	to_rot->x=x*cos(b)+z*sin(b);
	to_rot->y=-x*sin(a)*sin(b)+z*sin(a)*cos(b)+y*cos(a);
	to_rot->z=-x*cos(a)*sin(b)+z*cos(a)*cos(b)-y*sin(a);
	/* https://www.wolframalpha.com/input?i2d=true&i=%7B%7B1%2C0%2C0%7D%2C%7B0%2Ccos%5C%2840%29a%5C%2841%29%2Csin%5C%2840%29a%5C%2841%29%7D%2C%7B0%2C-sin%5C%2840%29a%5C%2841%29%2Ccos%5C%2840%29a%5C%2841%29%7D%7D%7B%7Bcos%5C%2840%29b%5C%2841%29%2C0%2Csin%5C%2840%29b%5C%2841%29%7D%2C%7B0%2C1%2C0%7D%2C%7B-sin%5C%2840%29b%5C%2841%29%2C0%2Ccos%5C%2840%29b%5C%2841%29%7D%7D%7B%7Bx%7D%2C%7By%7D%2C%7Bz%7D%7D */	
}


point get_point_at_idx(int i,point *head){
	int c=0;
	while((++c)<i){head=(point*)head->next;}
	return *head;
}

point* get_last_point_address(point *head){
	point *last_point=head;
	while((head=(point*)head->next)){last_point=head;}
	return last_point;
}

void add_obj_points_scene(obj *obj,bool space);


void fill(obj *obj){
	/* jen pridava hrany zatim */

	/* metoda pozaduje */  
	/* metoda zatim nevyplnuje,pouze tvary se uvazuji objekty slozene z primek, bez krivek atd. */
	int i=0;	
	tmp.buff_points_for3d=point_new();
	while(i+1<obj->n_edges){
		input_line.A=get_point_at_idx(obj->edges[i],tmp.tmp);
		input_line.B=get_point_at_idx(obj->edges[i+1],tmp.tmp);
		get_last_point_address(tmp.buff_points_for3d)->next=(struct point*)get_obj("line")->points;
		i+=2;	
	}
}


double distance(point *point){
	double x=point->x,y=point->y,z=point->z;
	return sqrt(x*x+y*y+z*z);
}


void change_O_pos(double alpha, double sigma){
	/* zmen souradnice vektoru vyjadrujici soustavu S */ 
	rot_in_polar(alpha,sigma,&scene_.X); 
	rot_in_polar(alpha,sigma,&scene_.Y); 
	rot_in_polar(alpha,sigma,&scene_.Z); 

	/* urci pozici pozorovatele nanesenim bodu na S */ 
	double x,y,z;
	x=scene_.X.x*scene_.P.x+scene_.Y.x*scene_.P.y+scene_.Z.x*scene_.P.z; 
	y=scene_.X.y*scene_.P.x+scene_.Y.y*scene_.P.y+scene_.Z.y*scene_.P.z; 
	z=scene_.X.z*scene_.P.x+scene_.Y.z*scene_.P.y+scene_.Z.z*scene_.P.z; 
	scene_.Pabs.x=x;
	scene_.Pabs.y=y;
	scene_.Pabs.z=z;

	struct LIST_OBJS *head=start_obj;
	while(head){
		/* predpoklada se, ze vsechny objekty jsou 3d */
		if(head->obj.points){
			points_3d_to_2d(&head->obj);
			fill(&head->obj);
			scene_.points=point_scene=point_new();
			add_obj_points_scene(&head->obj,true);
		}
		head=head->next;
	}
}

void add_obj_points_scene(obj *obj,bool space){
	if(!obj)
		return;

	point *head=(space) ? tmp.buff_points_for3d : (point*)obj->points;
	if(head){
		double x,y;
		point_add(&point_scene);

		do{
			x=head->x;
			y=head->y;

			point_set((int)x,(int)y,&point_scene);

			if((head=(point*)head->next))	
				point_add(&point_scene);
			else break;

		}while(1);
	}

	if(obj->sub)
		add_obj_points_scene(obj->sub,space);

	if(obj->next)
		add_obj_points_scene(obj->next,space);
}

static bool make_obj(char name[]){
	obj *obj = get_obj(name);
	if(!obj)
		return false;
	last_obj = *obj;
	set_obj_in_list(last_obj,name);
	add_obj_to_list();
	return true;
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
			input_line.A.x=nums[0];
			input_line.A.y=nums[1];
			input_line.B.x=nums[2];
			input_line.B.y=nums[3];
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
				out(ERR,1,"","%s expected an integer! obtained value: '%s'",arg_name,val);
				return false;
			}
			break;
		case STR:
			break;
	}


	switch(obj){
		case POINT:
			switch(arg){
				case 1:
					input_point.x=Z;
					break;
				case 2:
					input_point.y=Z;
					break;
			}
			break;
		case LINE:
			switch(arg){
				case 1:
					input_line.A.x=Z;
					break;
				case 2:
					input_line.A.y=Z;
					break;
				case 3:
					input_line.B.x=Z;
					break;
				case 4:
					input_line.B.y=Z;
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
		case RING:
			switch(arg){
				case 1:
					input_ring.S->x=Z;
					break;
				case 2:
					input_ring.S->y=Z;
					break;
				case 3:
					input_ring.r=Z;
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


			get_from_str("(\\w+):",args,&type,&idx,&len);
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
					case POLYGON_FILL:
						input_polygon.points[input_polygon.n_points]=input_point;
						++input_polygon.n_points;
						break;
					case LINE:
						if(n_arg==1)
							input_line.B=input_point;
						else
							input_line.A=input_point;
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
	char str_input[1000];
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
	char* obj_name;
	switch(id){
		case EXAMPLE:
			obj_name="example";
			break;
		case LINE:
			obj_name="line";
			break;
		case CIRCLE:
			obj_name="circle";
			break;
		case RING:
			obj_name="ring";
			break;
		case POLYGON:
			obj_name="polygon";
			break;
		case POLYGON_FILL:
			obj_name="polygon-fill";
			break;
		case POINT:
			obj_name="point";
			break;
		case CUBE_EXAMPLE:
			obj_name="cube-example";
	}

	out(INFO,0,"processing obj: ","%s",obj_name);
	return make_obj(obj_name);
}



int get_obj_id_by_name(char* name){
	int obj_id;


	if(strcmp(name, "line") == 0)
		obj_id = LINE;
	else if(strcmp(name, "ring") == 0)
		obj_id = RING;
	else if(strcmp(name, "circle") == 0)
		obj_id = CIRCLE;
	else if(strcmp(name, "example") == 0)
		obj_id = EXAMPLE;
	else if(strcmp(name, "polygon") == 0)
		obj_id = POLYGON;
	else if(strcmp(name, "point") == 0)
		obj_id = POINT;
	else if(strcmp(name, "cube-example") == 0)
		obj_id = CUBE_EXAMPLE;
	else if(strcmp(name, "polygon-fill") == 0)
		obj_id = POLYGON_FILL;


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

	out(INFO,1,"processing input: ","%s",name);
	return check_mandatory_args(input,obj_input[obj_id][1],obj_id,cmd);
}

bool proc_obj_cmd(int argc,char *argv[]){
	int obj_id = get_obj_id_by_name(argv[1]);

	if(obj_id==NONE)
		return false;

	if(strcmp(obj_input[obj_id][2],"3d")==0)
		scene_.space=_3D;	
	else
		scene_.space=_2D;


	out(INFO,0,"processing input: ","%s",argv[1]);
	if(!proc_obj_input_cmd(argv,argc,obj_input[obj_id][1],obj_id))
		return false;
	if(!set_obj(obj_id))
		return false;

	/* objekt se naplni convertovanymi body, pokud je 3D */ 
	if(scene_.space==_3D){
		/* !! */
		scene_.Pabs.x=scene_.P.x;
		scene_.Pabs.y=scene_.P.y;
		scene_.Pabs.z=scene_.P.z;
		/* !! */
		points_3d_to_2d(&last_obj);
		fill(&last_obj);
	}	
	scene_.points=point_scene=point_new();
	add_obj_points_scene(&last_obj,(scene_.space==_3D));

	return true;	
}

void obj_add_edge(obj *obj,int p1,int p2){
	obj->edges[obj->n_edges]=p1;
	obj->edges[obj->n_edges+1]=p2;
	obj->n_edges+=2;
}

