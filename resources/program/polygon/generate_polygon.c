#define POINT_IN
#define OBJ_IN
#define LINE_IN
#define LINE_COPY_IN 
#define POINT_COPY_IN
#define POLYGON_IN
#define POINT_NEW
#define POINT_SET
#define HELPERS_OBJ

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../inputs.h"

static int n_points;
static point *points;


typedef struct{
    double x, y;
}intersect;

#define PARALELL_LINES 1
#define SAME_LINES 2
#define INTERSECTED_LINES 3



intersect* line_intersection(line *a, line *b,bool edges_counted);
int is_lines_parallel(line *a, line *b);



static void solve() {
        
        int n_lines = n_points;
        line lines [n_lines];

        for(int i=0;i+1<n_points;++i){
            input_line.ax=points[i].x;
            input_line.ay=points[i].y;


            input_line.bx=points[i+1].x;
            input_line.by=points[i+1].y;

            lines[i].ax=points[i].x; 
            lines[i].ay=points[i].y; 
            lines[i].bx=points[i+1].x; 
            lines[i].by=points[i+1].y; 

            copy_line_input(&input_line); 
            obj_sub(&current_obj,get_obj("line"));
        }

        lines[n_lines-1].ax=points[n_points-1].x;
        lines[n_lines-1].ay=points[n_points-1].y;

        lines[n_lines-1].bx=points[0].x;
        lines[n_lines-1].by=points[0].y;


        input_line.ax=points[0].x;
        input_line.ay=points[0].y;

        copy_line_input(&input_line); 
        obj_sub(&current_obj,get_obj("line"));


        for(int k=0;k<n_lines;++k){
            printf("\n%d, %d, %d, %d",lines[k].ax,lines[k].ay,lines[k].bx,lines[k].by);
        }
    printf("\n");


        intersect *res;
        for(int k=0;k<n_lines;++k){
            for(int c=0;c<k;++c){

                printf("\n--\na: %d, %d, %d, %d",lines[k].ax,lines[k].ay,lines[k].bx,lines[k].by);
                printf("\nb: %d, %d, %d, %d",lines[c].ax,lines[c].ay,lines[c].bx,lines[c].by);



                double Ax=lines[k].ax, Ay=lines[k].ay, 
                       Bx=lines[k].bx, By=lines[k].by,
                       Cx=lines[c].ax, Cy=lines[c].ay,
                       Dx=lines[c].bx, Dy=lines[c].by;


    double a1=Bx-Ax,a2=By-Ay,
           b1=Dx-Cx,b2=Dy-Cy;


                switch(is_lines_parallel(&lines[k],&lines[c])){
                    case SAME_LINES:
                        printf("\nkolize nastala\n");
                        break;
                    case INTERSECTED_LINES:
                        if((res=line_intersection(&lines[k],&lines[c],false))){

                            input_line.ax=Cx+res->x*b1;
                            input_line.ay=Cy+res->x*b2;

                            input_line.bx=900;
                            input_line.by=900;

                            copy_line_input(&input_line); 
                            obj_sub(&current_obj,get_obj("line"));


                            printf("\nkolize nastala\n");


                        }else{
                            printf("\nkolize nenastala\n");
                        }
                        break;
                    case PARALELL_LINES:
                        printf("\nkolize nenastala\n");
                        break;
                }
            }
        }



        /* point_set(,,&intersect); */
        return;



}




int is_lines_parallel(line *a, line *b){
    double Ax=a->ax, Ay=a->ay, 
           Bx=a->bx, By=a->by,
           Cx=b->ax, Cy=b->ay,
           Dx=b->bx, Dy=b->by;

    double a1=Bx-Ax,a2=By-Ay,
           b1=Dx-Cx,b2=Dy-Cy;

    if(b1*a2-a1*b2==0)
    {
        if(a1*Cy-a1*Ay-a2*(Cx-Ax)==0) /* primky jsou rovnobezne a shodne */
            return SAME_LINES;
        else /* primky jsou rovnobezne a neshodne*/
            return PARALELL_LINES;
    }else
        return INTERSECTED_LINES;
}


intersect* line_intersection(line *a, line *b,bool edges_counted){
    if(is_lines_parallel(a,b)!=INTERSECTED_LINES)
        return NULL;

    /* predpoklada se, ze Ax + a1*t = Bx, kdyz t=1, tedy a1 je Bx-Ax, atd. u dalsich souradnic vektoru */
    double Ax=a->ax, Ay=a->ay, 
           Bx=a->bx, By=a->by,
           Cx=b->ax, Cy=b->ay,
           Dx=b->bx, Dy=b->by;
    double a1=Bx-Ax,a2=By-Ay,
           b1=Dx-Cx,b2=Dy-Cy;
    double t,k;


    t=(a1*(Cy-Ay)-a2*(Cx-Ax))/(a2*b1-a1*b2);
    k=(Cx+t*b1-Ax)/a1;

    /* printf("\n%f\n",t); */
    /* printf("%f\n",k); */

    if(k<0 || k>1 || t<0 || t>1) /* => bod NElezi soucasne na obou useckach */
        return NULL;
    else if(!edges_counted && (k==0 || k==1 || t==0 || t==1))
        return NULL;

    intersect *res=(intersect*)malloc(sizeof(intersect)); 
    res->x=t;
    res->y=k;

    return res;
}



void _set_polygon(polygon *input,obj *obj) {
    points = input->points;
    n_points = input->n_points;

    current_obj=obj;
    solve();
}

