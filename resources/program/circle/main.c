#include <stdio.h>

typedef struct{
 int r, sx, sy;
}input;


typedef struct{
   int *x, *y;
}point;

point Point;
input Input;



void init_bresenham(input *res, point *point);
int next_point(void);

void init(void);
void set_pixel(int x, int y);

void render_frame(void);
int check_events_forever(void);


int main() {
   init();

   Input.r = 200;
   Input.sx = 300;
   Input.sy = 500;


   init_bresenham(&Input, &Point);

   do{ 
      set_pixel(Input.sx + *Point.x, Input.sy + *Point.y);
      set_pixel(Input.sx + *Point.y, Input.sy + *Point.x);
      set_pixel(Input.sx - *Point.y, Input.sy + *Point.x);
      set_pixel(Input.sx - *Point.x, Input.sy + *Point.y);
      set_pixel(Input.sx - *Point.x, Input.sy - *Point.y);
      set_pixel(Input.sx + *Point.x, Input.sy - *Point.y);
      set_pixel(Input.sx + *Point.y, Input.sy - *Point.x);
      set_pixel(Input.sx - *Point.y, Input.sy - *Point.x);
      /* set_pixel(Input.sx + *Point.x, Input.sy + *Point.y); */
   }while(next_point());




   render_frame();
   check_events_forever();

   getchar();
   return 0;
}

