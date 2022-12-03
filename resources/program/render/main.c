#define POINT_IN
#define OBJ_IN

#define SCENE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../inputs.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *screen_texture;
SDL_Event event;

unsigned int *pixels;

static scene scene_;

int resolve_window_events() {
   while(1) {
      while(SDL_PollEvent(&event)){
         switch (event.type) {
            case SDL_QUIT:
               SDL_DestroyWindow(window);
               SDL_Quit();
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
               else if(event.wheel.y < 0) 
                  return ACTION_ZOOM_MINUS; 

               break;
            default:
               return STATE_NOTHING;
         }
      }
   }
}

void render_present() {
   SDL_UpdateTexture(screen_texture, NULL, pixels, scene_.width * 4);
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
   SDL_RenderPresent(renderer);
}


/* void render_scene(){ */
/* } */

void copy_scene_render(scene scene_to_set){
   scene_=scene_to_set;
}


void clear_scene(){
   for(int x=0;x<scene_.width;++x){
      for(int y=0;y<scene_.height;++y){
         pixels[x + (scene_.height - y) * scene_.width] = 0x00000000;
      }
   }
}

void render_obj(obj *obj) {
   if(!obj)
      return;

   if(obj->points){
      point *head=(point*)obj->points;
      int x,y;
      do{
         x=head->x+scene_.shiftX;
         y=head->y+scene_.shiftY;
 
         if(x>0 && x<scene_.width && y>0 && y<scene_.height)
            pixels[x + (scene_.height - y) * scene_.width] = 0xff000000;
      }
      while((head=(point*)head->next));
   }

   if(obj->sub)
      render_obj(obj->sub);

   if(obj->next)
      render_obj(obj->next);
}


bool render(obj *obj){

   screen_texture = SDL_CreateTexture(renderer,
         SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
         scene_.width, scene_.height);

   pixels = malloc(scene_.width * scene_.height * 4);

   clear_scene();
   render_obj(obj);
   render_present();
   return true;
}

/* void render_LIST_OBJS() { */
/* } */


void stop_render(){
   /* if(screen_texture) */
   /*    SDL_DestroyTexture(screen_texture); */
   if(window)
      SDL_DestroyWindow(window);
   SDL_Quit();
}

int init_render() {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }

   window = SDL_CreateWindow("MP",
         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         scene_.width, scene_.height,
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
         scene_.width, scene_.height);

   pixels = malloc(scene_.width * scene_.height * 4);

   return EXIT_SUCCESS;
}

