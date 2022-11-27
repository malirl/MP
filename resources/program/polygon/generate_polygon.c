#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define COPY_LINE_IN
#define POLYGON_IN
#define HELPERS_OBJ

#include <stdio.h>
#include <stdbool.h>
#include "../inputs.h"


static int n_lines;
static line *lines;


static void solve() {
    for(int i=0;i<n_lines;++i){
        copy_line_input(&lines[i]); 
        obj_sub(&current_obj,get_obj("line"));
    }
}

void _set_polygon(polygon *input,obj *obj) {
    lines = input->lines;
    n_lines = input->n_lines;

    current_obj=obj;
   solve();
}

