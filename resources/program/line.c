#include <stdio.h>

typedef struct input{
 int ax, ay, bx, by;
}input;

/* v poradi: bod A, bod B vuci A, parametr pro zpetny prevod */
typedef struct res{
   int ax, ay, dx, dy, opt;
}res;


typedef struct point{
   int *x, *y;
}point;


res convert_input(input *input);

point init_bresenham(res *res);
int next_point(void);

void init(void);
void set_pixel(int x, int y);

void render_frame(void);


int main() {
   init();

   input input;
   input.ax = 200;
   input.ay = 700;
   input.bx = 300;
   input.by = 600;

   res res = convert_input(&input);
   point point = init_bresenham(&res);

   switch(res.opt) {
      case 1:
         while(next_point())
            set_pixel(res.ax + *point.y, res.ay + *point.x);
         break;
      case 2:
         while(next_point())
            set_pixel(res.ax + *point.x, res.ay + *point.y);
         break;
      case 3:
         while(next_point())
            set_pixel(res.ax + *point.x, res.ay - *point.y);
         break;
      case 4:
         while(next_point())
            set_pixel(res.ax + *point.y, res.ay - *point.x);
         break;
   }

   render_frame();

   getchar();
   return 0;
}

