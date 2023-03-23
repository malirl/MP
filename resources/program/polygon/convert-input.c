#define POINT_IN 
#define LINE_IN
#define POLYGON_IN
#define POINT_COPY_IN 
#define LINE_COPY_IN 
#define POLYGON_CONVERTED_IN 

#include <stdio.h>
#include "../inputs.h"


polygon_converted convert_polygon_input(polygon *input) {
    int n_lines=input->n_points;
    polygon_converted res = {0};

    /* hnus */
    if(n_lines==0)
        return res;

    for(int i=0;i+1<n_lines;++i){
        input_point.x=input->points[i].x;
        input_point.y=input->points[i].y;
        input_line.A=input_point;

        input_point.x=input->points[i+1].x;
        input_point.y=input->points[i+1].y;
        input_line.B=input_point;

        res.lines[i]=input_line;
    }

    input_point.x=input->points[n_lines-1].x;
    input_point.y=input->points[n_lines-1].y;
    input_line.A=input_point;

    input_point.x=input->points[0].x;
    input_point.y=input->points[0].y;
    input_line.B=input_point;

    res.lines[n_lines-1]=input_line;

    res.n_lines=n_lines;
    return res;
}

