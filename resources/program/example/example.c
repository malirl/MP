#include <stdio.h>
#include "../helpers.h"
#include "../obj_helpers.h"


static void solve() {

   set_point(0, 0, &current_point);
   /* add_point(&current_point); */

  /* 1. varianta pridavani podobjekty */ 
   proc_obj("line","ay:200 by:34 ax:100 bx:100",false);
   sub(current_obj,get_obj("line"));
   proc_obj("line","by:600 ax:200 bx:600",false); // neuplny zadani povoleno 
   sub(current_obj,get_obj("line"));
   proc_obj("circle","Sx:500 Sy:500 r:60",false);
   next(current_obj,get_obj("circle"));
   
   proc_obj("line","by:700 ax:700 bx:800",false); 
   sub(current_obj,get_obj("line"));

   /* 2. varianta pro predem neznamy hodnoty parametru*/ 
   num_args[0]=200;
   num_args[1]=34;
   num_args[2]=100;
   num_args[3]=100;
   set_args(LINE,num_args,str_args);
   sub(current_obj,get_obj("line"));





}

void example_(obj* obj,point **tracked_point) {
    *tracked_point = current_point = new_point();
    current_obj=obj;
   solve();
}

