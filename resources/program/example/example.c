#include <stdio.h>
#include "../helpers.h"

static point *current_point; 

void set_obj(int id);

#define LINE 1
#define RING 2
#define CIRCLE 3 
#define EXAMPLE 4

static void add_obj_to_points(){

}

static void add_sub_obj(){
}



static void solve() {
   /* slouzi k ukazkam prace s objekty v samotnych objektech */
   /* napriklad pridani bodů jinyho objektu do bodů objektu example */
   /* nebo vytvoreni anonymniho (neukladaneho) objektu pro vstup do jinyho */
   /* nebo pridani objektu do podobjektu */

   /* !! */


   /* set_point(sx, sy, &current_point); */
   /* add_point(&current_point); */

   set_obj(LINE);


}


void example_(point **tracked_point) {
   current_point = new_point();
   *tracked_point = current_point;
   solve();
}

