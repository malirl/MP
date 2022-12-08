#include "main.h"

void set_example(obj *example) {
   example_(example,&example->points);
}

void set_cube_example(obj *cube) {
   cube_example(&cube->points,cube);
}

