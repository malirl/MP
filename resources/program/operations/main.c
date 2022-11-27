#include "main.h"

void set_mirror_to_line(obj *obj, mirror_to_line *input) {
   _mirror_to_line(input,&obj->points);
}

void set_rot2d(obj *obj, rot2d *input) {
   _rot2d(input,&obj->points); 
}

