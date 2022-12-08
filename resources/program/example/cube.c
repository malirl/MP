#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define HELPERS_OBJ
#define HELPERS_3D

#include <stdio.h>
#include <stdbool.h>
#include "../inputs.h"


static void solve() {

   current_obj->n_edges=0;
   int a=50;

   obj_add_edge(current_obj,1,2);
   obj_add_edge(current_obj,2,3);
   obj_add_edge(current_obj,3,4);
   obj_add_edge(current_obj,1,4);

   obj_add_edge(current_obj,5,6);
   obj_add_edge(current_obj,6,7);
   obj_add_edge(current_obj,7,8);
   obj_add_edge(current_obj,5,8);

   obj_add_edge(current_obj,1,5);
   obj_add_edge(current_obj,2,6);
   obj_add_edge(current_obj,3,7);
   obj_add_edge(current_obj,4,8);


   /* current_obj->edges[0]=1; */
   /* current_obj->edges[1]=2; */

   /* current_obj->edges[0]=1; */
   /* current_obj->edges[1]=2; */


   point3d_set(-a,a,-a,&current_point);

   point_add(&current_point);
   point3d_set(a,a,-a,&current_point);

   point_add(&current_point);
   point3d_set(a,a,a,&current_point);

   point_add(&current_point);
   point3d_set(-a,a,a,&current_point);

   point_add(&current_point);
   point3d_set(-a,-a,-a,&current_point);

   point_add(&current_point);
   point3d_set(a,-a,-a,&current_point);

   point_add(&current_point);
   point3d_set(a,-a,a,&current_point);

   point_add(&current_point);
   point3d_set(-a,-a,a,&current_point);


}

void cube_example(point **tracked_point,obj *obj){
   *tracked_point = current_point = point_new();
   current_obj=obj;
   solve();
}

