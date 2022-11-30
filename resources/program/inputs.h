#ifdef EVERYTHING_IN
#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define RING_IN
#define CIRCLE_IN
#define MIRROR_TO_LINE_IN
#define ROT2D_IN
#define POLYGON_IN 
#endif


#ifdef POINT_IN
typedef struct{
   int x, y;
	 struct point *next;
}point;
#endif


#ifdef OBJ_IN
typedef struct obj{
	point *points;
	struct obj *sub;
  struct obj *next;
}obj;
#endif





#ifdef LINE_IN
typedef struct{
	int ax;
	int ay;
	int bx;
	int by;
}line;
#endif

#ifdef RING_IN
typedef struct{
	int r;
	point *S;
}ring;
#endif

#ifdef CIRCLE_IN 
typedef struct{
	int r;
	point *S;
}circle;
#endif

#ifdef MIRROR_TO_LINE_IN
typedef struct{
	obj* obj;	
	line* line;
}mirror_to_line;
#endif

#ifdef ROT2D_IN
typedef struct{
   double alpha;
   point *S;
   obj *obj;
}rot2d;
#endif

#ifdef POLYGON_IN
#define POLYGON_MAX_NUMBER_POINTS 100
typedef struct{
	int n_points;
	point points[POLYGON_MAX_NUMBER_POINTS];
}polygon;
#endif



#ifdef LINE_CONVERTED_IN
typedef struct{
	int ax, ay, dx, dy, opt;
	double a;
}line_converted;
#endif



#ifdef LINE_COPY_IN 
static line input_line;
void copy_line_input(line *input);
#endif


#ifdef POINT_COPY_IN 
static point input_point;
void copy_point_input(point *input);
#endif


#ifdef HELPERS
#define POINT_NEW
#define POINT_SET
#define POINT_ADD

static point *current_point;
#endif

#ifdef POINT_NEW 
point* point_new();
#endif

#ifdef POINT_SET
void point_set(int res_x, int res_y, point **prev_point);
#endif

#ifdef POINT_ADD
void point_add(point **prev_point);
#endif


#ifdef HELPERS_OBJ
#define LINE 1
#define RING 2
#define CIRCLE 3 
#define EXAMPLE 4

#define OBJ_GET 
#define OBJ_NEW
#define OBJ_NEXT 
#define OBJ_SUB 

#define PROC_OBJ
#define SET_ARG

static obj *current_obj;
#endif


#ifdef OBJ_GET
obj* get_obj(char name[]);
#endif

#ifdef PROC_OBJ 
bool proc_obj(char *name,char* input,bool check);
#endif

#ifdef SET_ARG 
obj* set_args(int name,int nums[],char* strs[]); 
#endif

#ifdef OBJ_NEW 
struct obj* obj_new();
#endif

#ifdef OBJ_NEXT 
void obj_next(obj **current,obj *next);
#endif

#ifdef OBJ_SUB 
void obj_sub(obj **current,obj *sub);
#endif

