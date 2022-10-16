#include <stdio.h>

void init(void);
void set_pixel(int x, int y);
void render_frame(void);


int main() {
   init();

   int ax = 300, ay = 200, bx = 800, by = 400;
   double a = (double)(by-ay)/(bx-ax);
   double err = 0;

   int y = ay;
   for (int x = ax; x <= bx; x++) {
      set_pixel(x,y);
      err+=a;
      if (err >= 0.5) {
         y++;
         err-=1;
      }
   }

   render_frame();
   getchar();
   return 0;
}
