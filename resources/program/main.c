#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 1000
#define HEIGHT 1000

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *screen_texture;

unsigned int *pixels;



int render_frame() {
   SDL_UpdateTexture(screen_texture, NULL, pixels, WIDTH * 4);
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
   SDL_RenderPresent(renderer);

   SDL_Event event;
   while (SDL_PollEvent(&event))
   {
      switch (event.type) {
         case SDL_QUIT:
            SDL_DestroyWindow(window);
            SDL_Quit();
            break;
         case SDL_WINDOWEVENT:
            break;
         default: {}
      }
   }
}


void set_pixel(int x, int y) {
   pixels[x + (HEIGHT - y) * WIDTH] = 0xff000000;
}

int init() {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }

   window = SDL_CreateWindow("",
         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         WIDTH, HEIGHT,
         SDL_WINDOW_SHOWN);


   if(window == NULL) {
      fprintf(stderr,"SDL_CreateWindow Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }

   renderer = SDL_CreateRenderer(window, -1,
         SDL_RENDERER_ACCELERATED |
         SDL_RENDERER_PRESENTVSYNC);

   if(renderer == NULL) {
      SDL_DestroyWindow(window);
      fprintf(stderr, "SD1000L_CreateRenderer Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }

   screen_texture = SDL_CreateTexture(renderer,
         SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
         WIDTH, HEIGHT);

   pixels = malloc(WIDTH * HEIGHT * 4);
}

