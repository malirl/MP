#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define POLYGON_IN
#define POLYGON_CONVERTED_IN
#define POINT_NEW
#define POINT_SET
#define HELPERS

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "../inputs.h"


static int n_points;
static polygon *out;

static const double pi = 22.0 / 7.0;

int compare(const void *a, const void *b) {
    return (*(double*)a > *(double*)b) ? 1 : -1;
}

static void solve() {
    out->n_points=n_points;

    double alphas[n_points];
    /* naplnit pole n hodnotami v intervalu <0;2pi>*/
    srand(time(NULL)); 
    for(int i=0;i<n_points;++i){
        alphas[i]=rand()/(RAND_MAX+1.0)*2*pi;
        /* printf("\n%f",alphas[i]); */
    } 

    /*seradit podle uhlu*/
    qsort(alphas,n_points,sizeof(double),compare);

    /*nasobeni jednotkovy kruznice*/   
    double alpha,k;
    for(int i=0;i<n_points;++i){
        alpha=alphas[i];
        /* souradnice * 'k'*/ 
        k=rand()/(RAND_MAX+1.0)*300;
        point_set(k*cos(alpha)+500,k*sin(alpha)+500,&current_point);
        out->points[i]=*current_point;
    }

}

void _set_polygon_rnd(polygon_rnd *input,polygon *output) {
    n_points=input->n_points;
    out=output;
    current_point=point_new();
    solve();
}

