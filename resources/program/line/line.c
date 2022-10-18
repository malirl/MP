#include <stdio.h>

typedef struct input{
 int ax, ay, bx, by;
}input;

/* v poradi: bod A, bod B vuci A, parametr pro zpetny prevod */
typedef struct res{
   int ax, ay, dx, dy, opt;
   double a;
}res;


typedef struct point{
   int *x, *y;
}point;

struct point Point;


res convert_input(input *input);

void init_bresenham(res *res, point *point);
void init_dda(res *res, point *point);
int next_point(void);

void init(void);
void set_pixel(int x, int y);

void render_frame(void);


int main() {
   init();

   input input;
   input.ax = 50;
   input.ay = 50;
   input.bx = 300;
   input.by = 800;

   res res = convert_input(&input);
   init_bresenham(&res, &Point);
   /* init_dda(&res, &Point); */

   switch(res.opt) {
      case 1:
         while(next_point())
            set_pixel(res.ax + *Point.y, res.ay + *Point.x);
         break;
      case 2:
         while(next_point())
            set_pixel(res.ax + *Point.x, res.ay + *Point.y);
         break;
      case 3:
         while(next_point())
            set_pixel(res.ax + *Point.x, res.ay - *Point.y);
         break;
      case 4:
         while(next_point())
            set_pixel(res.ax + *Point.y, res.ay - *Point.x);
         break;
   }

   render_frame();

   getchar();
   return 0;
}

