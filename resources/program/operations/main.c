#include "main.h"

void set_mirror_to_line(obj *obj, input_mirror_to_line *input) {
   mirror_to_line(input,&obj->points);
}

void set_rot2d(obj *obj, input_rot2d *input) {
   rot2d(input,&obj->points); 
}

