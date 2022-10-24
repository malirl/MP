#include <stdlib.h>

typedef struct point{
   int x, y;
   struct point *next;
}point;

static struct point* new_point() {
  return (struct point*)malloc(sizeof(point));  
}

static void add_point(point **prev_point) {
   (*prev_point)->next = new_point(); 
   *prev_point = (point*)(*prev_point)->next;
   (*prev_point)->next = NULL;
}

static void set_point(int res_x, int res_y, point **prev_point) {
   (*prev_point)->x = res_x;
   (*prev_point)->y = res_y;
}

