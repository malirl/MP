#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define LINE_COPY_IN 
#define POINT_COPY_IN
#define POLYGON_IN
#define POLYGON_CONVERTED_IN
#define POINT_NEW
#define POINT_SET
#define HELPERS_OBJ

#include <stdbool.h>
#include "../inputs.h"

static int n_lines;
static line *lines;

static void solve() {

    for(int i=0;i<n_lines;++i){
        input_line=lines[i];
        copy_line_input(&input_line); 
        obj_sub(&current_obj,get_obj("line"));
    }

    /* copy_line_input(&lines[i]); */ 
    /* obj_sub(&current_obj,get_obj("line")); */
    /* point_set(,,&intersect); */
}



void _set_polygon(polygon_converted *input,obj *obj) {
    lines=input->lines;
    n_lines=input->n_lines;

    current_obj=obj;
    solve();
}

