#define POINT_IN
#define LINE_IN 
#define LINE_INTERSECTION
#define LINE_CONVERTED_IN
#define POLYGON_CONVERTED_IN

#include "../inputs.h"
#include "../helpers.h"
#include <stdbool.h>
#include <stdarg.h>

#define ERR -1
#define INFO 0
#define SUCCESS 1


void out(int status,int lvl,char* msg,const char* fmt,...);


static int n_lines;

bool valid_polygon(polygon_converted *input){

    n_lines = input->n_lines;
    intersect *res;

    if(n_lines<3){
        out(ERR,0,"too few points!","");
        return false;
    }

    for(int k=0;k<n_lines;++k){
        for(int c=0;c<k;++c){
            switch(is_lines_parallel(&input->lines[k],&input->lines[c])){
                case SAME_LINES:
                    /* s kolizi */
                    out(ERR,0,"lines overlap","");
                    return false;
                    break;
                case INTERSECTED_LINES:
                    if((res=line_intersection(&input->lines[k],&input->lines[c],false))){
                        /* s kolizi */
                        out(ERR,0,"polygon is self-intersected!","");
                        return false;
                    }else{
                        /* bez kolize */
                    }
                    break;
                case PARALELL_LINES:
                    /* bez kolize */
                    break;
            }
        }
    }
    return true;
}

