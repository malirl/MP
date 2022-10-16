#include <stdio.h>

void init(void);
void set_pixel(int x, int y);
void render_frame(void);

int main() {
   init();

   int ax = 300, ay = 200, bx = 800, by = 400;
   int dy = by - ay;
   int dx = bx - ax;
   int err = -2*dx;

   int y = ay;
   for (int x = ax; x <= bx; x++) {
      set_pixel(x,y);
      err+=2*dy;
      if (err >= 0) {
         y++;
         err-=2*dx;
      }
   }

   render_frame();
   getchar();
   return 0;
}
