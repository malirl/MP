#define POINT_IN
#define OBJ_IN
#define SCENE_STATES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../inputs.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *screen_texture;
SDL_Event event;

SDL_Rect src_rect;
SDL_Rect dst_rect;

unsigned int *pixels;

int width, height, shiftX=0, shiftY=0;

void stop_render(){
   SDL_DestroyTexture(screen_texture);
   screen_texture = NULL;
   SDL_DestroyRenderer(renderer);
   renderer = NULL;
   SDL_DestroyWindow(window);
   window = NULL;
   SDL_Quit();
   free(pixels);
}

int resolve_window_events() {
      /* SDL_Delay(1000/60); */
      while(SDL_PollEvent(&event)){
         switch (event.type) {
            case SDL_QUIT:
               return STATE_QUIT;
               break;
            case SDL_WINDOWEVENT:
               break;
            case SDL_KEYDOWN:
               switch(event.key.keysym.sym){
                  case SDLK_q:
                     return STATE_QUIT;
                  case SDLK_RIGHT:
                     return ACTION_RIGHT;
                  case SDLK_LEFT:
                     return ACTION_LEFT;
                  case SDLK_UP:
                     return ACTION_UP;
                  case SDLK_DOWN:
                     return ACTION_DOWN;
               }
               break;
            case SDL_MOUSEWHEEL:
               if(event.wheel.y > 0)
                  return ACTION_ZOOM_PLUS; 
               return ACTION_ZOOM_MINUS; 
               break;
            default:
               return STATE_NOTHING;
         }
      }
      return STATE_NOTHING;
}

void render_present() {
   SDL_UpdateTexture(screen_texture, NULL, pixels, width * 4);
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
   SDL_RenderPresent(renderer);
}

void refresh(){
   render_present();
}

/* void render_scene(){ */
/* } */

void set_resolution(int width_,int height_){
   width=width_;
   height=height_;
}

void shift(int x, int y){
   shiftX=x;
   shiftY=y;
}

void clear_scene(){
   for(int x=0;x<width;++x){
      for(int y=0;y<=height;++y){
         pixels[x + (height - y) * width] = 0x00000000;
      }
   }
}

void render_scene(point *head) {
   int x,y;
   do{
      x=head->x+shiftX;
      y=head->y+shiftY;
      if(x>=0 && x<width && y>=0 && y<=height)
         pixels[x + (height - y) * width] = 0xff000000;
   }while((head=(point*)head->next));
}

bool render(point *points){
   if(points){
      clear_scene();
      render_scene(points);
      render_present();
      return true;
   }
   return false;
}

void re_render(point *points,bool zoom){
   if(zoom){
      /* src_rect.x = 0; */
      /* src_rect.y = 0; */
      /* src_rect.w = width; */
      /* src_rect.h = height; */
      /* dst_rect.x = 0; */
      /* dst_rect.y = 0; */
      /* dst_rect.w = width; */
      /* dst_rect.h = height; */

      /* SDL_DestroyTexture(screen_texture); */
      screen_texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
            width, height);
   }
   render(points);
}

/* void render_LIST_OBJS() { */
/* } */


int init_render(){
   if(getenv("XDG_RUNTIME_DIR") == NULL){
      SDL_setenv("XDG_RUNTIME_DIR", "/run/user/$(id -u)", 1);
      /* system("sudo systemctl restart display-manager"); */
   }

   if(SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }

   window = SDL_CreateWindow("MP",
         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         width, height,
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
         width, height);
   if(screen_texture==NULL) {
      /* SDL_DestroyWindow(window); */
      fprintf(stderr, "SDLCreateStructure Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }

   SDL_RenderSetLogicalSize(renderer, width, height);
   pixels = malloc(width*height*4*sizeof(unsigned int));

   return (SDL_GetError() == NULL);
}

