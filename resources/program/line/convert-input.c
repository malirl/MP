#include <stdio.h>

typedef struct input{
 int ax, ay, bx, by;
}input;


/* v poradi: bod A, bod B vuci A, parametr pro zpetny prevod */
typedef struct res{
   int ax, ay, dx, dy, opt;
   double a;
}res;


void swap(int *a, int *b) {
   int c = *a;
   *a = *b; 
   *b = c;
}


res convert_input(input *input) {

   int ax = input->ax, ay = input->ay, bx = input->bx, by = input->by; 

   if(ax>bx) {
      swap(&ax, &bx);
      swap(&ay, &by);
   }

   int dx = bx - ax, dy = by - ay;
   double a = (double)dy/dx;
   
   int opt = 2;

   if(a>1 || a<-1 || dx==0) {
      swap(&dx, &dy);
      opt = 1;

      if(a<-1) {
         dx *= -1;
         opt = 4;
      }
   } else if(a<0) {
      dy *= -1;
      opt = 3;
   }

   res res;
   res.ax = ax;
   res.ay = ay;
   res.dx = dx;
   res.dy = dy;
   res.a = (double)dy/dx;
   res.opt = opt;

   return res;
}

