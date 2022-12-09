#include "main.h"

bool set_polygon(obj *obj,polygon *input) {
   polygon_converted res = convert_polygon_input(input);
   if(valid_polygon(&res)){
      _set_polygon(&res,obj);
      return true;
   } else
      return false;

}

/* void (obj *polygon) { */
/*    polygon_generate(polygon,&polygon->points); */
/* } */

