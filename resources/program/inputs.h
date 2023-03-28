#ifdef EVERYTHING_IN
#define POINT_IN
#define OBJ_IN
#define SCENE_IN
#define LINE_IN
#define RING_IN
#define CIRCLE_IN
#define MIRROR_TO_LINE_IN
#define ROT2D_IN
#define ROT3D_IN 
#define POLYGON_IN 
#endif


#ifdef POINT_IN
typedef struct{
   double x, y, z;
	 struct point *next;
}point;
#endif

#ifdef OBJ_IN
typedef struct obj{
	point *points;
	int n_edges,edges[100];
	struct obj *next, *sub;
	/* bool fill; */
}obj;
#endif

#ifdef SCENE_IN 
typedef struct{
	int width, height;
	int shiftX, shiftY;
	int space;	
	double alpha,sigma,distance;
	point P,Pabs,focus,X,Y,Z;
	point *points;
}scene;
void init_scene(scene*);
#define SCENE_STATES
#endif

#ifdef SCENE_STATES
#define STATE_QUIT -1
#define STATE_NOTHING 0

#define ACTION_RIGHT 1
#define ACTION_LEFT 2
#define ACTION_UP 3
#define ACTION_DOWN 4
#define ACTION_ZOOM_MINUS 5
#define ACTION_ZOOM_PLUS 6

#define _2D 1
#define _3D 2
#endif


#ifdef LINE_IN
typedef struct{
	point A, B;
}line;
#endif

#ifdef RING_IN
typedef struct{
	int r;
	point S;
}ring;
#endif

#ifdef CIRCLE_IN 
typedef struct{
	int r;
	point S;
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

#ifdef ROT3D_IN
typedef struct{
   double alpha;
	int x,y,z;
   point *O; // osa O jako vektor velikosti 1
}rot3d;
#endif


#ifdef POLYGON_IN
#define POLYGON_MAX_NUMBER_POINTS 1000

typedef struct{
	int n_points;
	point points[POLYGON_MAX_NUMBER_POINTS];
}polygon;
typedef struct{
	int n_points;
}polygon_rnd;
#endif



#ifdef LINE_CONVERTED_IN
typedef struct{
	int ax, ay, dx, dy, opt;
	double a;
}line_converted;
#endif

#ifdef POLYGON_CONVERTED_IN 
#define POLYGON_MAX_NUMBER_LINES 1000
typedef struct{
	int n_lines;
	line lines[POLYGON_MAX_NUMBER_LINES];
}polygon_converted;
#endif


#ifdef LINE_COPY_IN 
static line input_line;
void copy_line_input(line *input);
/* void create_line_input(int x1,int x2,int y1,int y2); */
#endif


#ifdef POINT_COPY_IN 
static point input_point;
void copy_point_input(point *input);
#endif



#ifdef POINT_D
typedef struct{
   double x, y, z;
}point_d;
#endif


#ifdef HELPERS_3D 
#define POINT_NEW
#define POINT_ADD
#define POINT3D_SET

static point *current_point;
#endif


#ifdef HELPERS
#define POINT_NEW
#define POINT_ADD
#define POINT_SET

static point *current_point;
#endif

#ifdef POINT_NEW 
point* point_new();
#endif

#ifdef POINT_SET
void point_set(int x,int y, point **prev_point);
#endif

#ifdef POINT3D_SET
void point3d_set(int x,int y,int z, point **prev_point);
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

#define OBJ_ADD_EDGE

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

#ifdef OBJ_ADD_EDGE
void obj_add_edge(obj *obj,int p1,int p2);
#endif

