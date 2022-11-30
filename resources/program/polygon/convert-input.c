#define POINT_IN 
#define LINE_IN
#define POLYGON_IN
#define POLYGON_CONVERTED_IN 

#include <stdio.h>
#include "../inputs.h"



polygon_converted convert_polygon_input(polygon *input) {
    int n_lines=input->n_points;
    polygon_converted res;

    for(int i=0;i+1<n_lines;++i){
        res.lines[i].ax=input->points[i].x;
        res.lines[i].ay=input->points[i].y;

        res.lines[i].bx=input->points[i+1].x;
        res.lines[i].by=input->points[i+1].y;
    }

    res.lines[n_lines-1].ax=input->points[n_lines-1].x;
    res.lines[n_lines-1].ay=input->points[n_lines-1].y;

    res.lines[n_lines-1].bx=input->points[0].x;
    res.lines[n_lines-1].by=input->points[0].y;

    res.n_lines=n_lines;
    return res;
}

