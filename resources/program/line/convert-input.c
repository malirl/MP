#include <stdio.h>


#define LINE_IN
#define LINE_CONVERTED_IN 

#include "../inputs.h"


void swap(int *a, int *b) {
   int c = *a;
   *a = *b; 
   *b = c;
}


line_converted convert_input_line(line *input) {

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

   line_converted res;
   res.ax = ax;
   res.ay = ay;
   res.dx = dx;
   res.dy = dy;
   res.a = (double)dy/dx;
   res.opt = opt;

   return res;
}

