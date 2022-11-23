#define LINE 1
#define RING 2
#define CIRCLE 3 
#define EXAMPLE 4

typedef struct obj{
	point *points;
	struct obj *sub;
  struct obj *next;
}obj;

/* static void make_obj_uniform(){} */

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

