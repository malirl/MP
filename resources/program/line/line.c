#include <stdio.h>

typedef struct{
 int ax, ay, bx, by;
}input;

/* v poradi: bod A, bod B vuci A, parametr pro zpetny prevod */
typedef struct{
   int ax, ay, dx, dy, opt;
   double a;
}res;

typedef struct{
   int *x, *y;
}point;

typedef struct{
   point mirror;
   int bx, by;
}pointToMirror;

point Point;
input Input;

res convert_input(input *input);

void init_bresenham(res *res, point *point);
void init_dda(res *res, point *point);
int next_point(void);

void init(void);
void set_pixel(int x, int y);

void render_frame(void);


void mirror(pointToMirror *B) {
   int px = Input.ax, py = Input.ay, bx = B->bx, by = B->by;
   int x = Input.bx-Input.ax, y = Input.by-Input.ay; 

   double k = (double)(x*(bx-px)+y*(by-py))/(x*x+y*y);

   int res_x = (int)2*(k*x+px)-bx+.5, res_y = (int)2*(k*y+py)-by+.5;

   B->mirror.x = &res_x;
   B->mirror.y = &res_y;
}



int main() {
   init();

   Input.ax = 100;
   Input.ay = 300;
   Input.bx = 400;
   Input.by = 850;

   res res = convert_input(&Input);
   init_bresenham(&res, &Point);
   /* init_dda(&res, &Point); */


   /* zrcadleni */
   pointToMirror B;
   B.bx = 410;
   B.by = 400;

   set_pixel(B.bx,B.by);
   mirror(&B);
   set_pixel(*B.mirror.x,*B.mirror.y);
   printf("%f",*B.mirror.x);



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

