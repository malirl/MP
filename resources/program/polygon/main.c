#include "main.h"

bool set_polygon(obj *obj,polygon *input) {

   polygon_converted res = convert_polygon_input(input);

   if(valid_polygon(&res)){
      _set_polygon(&res,obj);
      return true;
   } else
      return false;

}

bool set_polygon_fill(obj *obj,polygon *input) {

   polygon_converted res = convert_polygon_input(input);

   if(valid_polygon(&res)){
      _set_polygon_fill(input,&obj->points);
      return true;
   } else
      return false;
}


void set_polygon_rnd(polygon *output,polygon_rnd *input) {
		_set_polygon_rnd(input, output);
}

/* void (obj *polygon) { */
/*    polygon_generate(polygon,&polygon->points); */
/* } */

