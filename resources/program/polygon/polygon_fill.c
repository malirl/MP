#define POINT_IN
#define HELPERS
#define OBJ_IN
#define LINE_IN
#define POLYGON_IN
#define POLYGON_CONVERTED_IN
#define POINT_NEW
#define POINT_SET

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../inputs.h"

typedef struct{
    point* point;
    int pos;
}converted_point;

converted_point point_tmp;

static int n_points;
static point *points;


static void remove_int(int *arr,int i,int n){
    for (int j = i; j < n - 1; j++)
        arr[j] = arr[j + 1];
}

static void remove_double(double *arr,double i,int n){
    for (int j = i; j < n - 1; j++)
        arr[j] = arr[j + 1];
}

static double get_dx(int A_idx, int B_idx) {
    point pointA = points[A_idx];
    point pointB = points[B_idx];
    return -(pointB.x-pointA.x)/(pointB.y-pointA.y);
}

static void insert_int(int *arr,int pos,int val,int n) {
    /* shift */
    for (int j=n; j>pos; --j)
        arr[j] = arr[j - 1];
    arr[pos]=val;
}

static void insert_double(double *arr,int pos,double val,int n) {
    /* shift */
    for (int j=n; j>pos; --j)
        arr[j] = arr[j - 1];
    arr[pos]=val;
}

int compare_points(const void* a, const void* b) {
    converted_point* p1 = (converted_point*)a;
    converted_point* p2 = (converted_point*)b;

    if (p1->point->y > p2->point->y) {
        return -1;
    } else if (p1->point->y < p2->point->y) {
        return 1;
    } else {
        if (p1->point->x < p2->point->x) {
            return -1;
        } else if (p1->point->x > p2->point->x) {
            return 1;
        } else {
            return 0;
        }
    }
}

static void solve(){
    point_set(0,0,&current_point);

    int init[n_points],tmp[n_points];
    double arr_a[n_points], lines_points[n_points]; 
    double Ax, Bx;
    bool found;
    int b_val;

    int tmp1;
    double a1,a2,tmp2;

    converted_point converted_points[n_points];
    for(int i=0;i<n_points;++i){
        point_tmp.point=&points[i];
        point_tmp.pos=i;
        converted_points[i]=point_tmp;
    }

    qsort(converted_points, n_points, sizeof(converted_point), compare_points);

    /* naplneni init */
    int glob_max_y,n_init=0;
    int row=glob_max_y=converted_points[0].point->y;

    init[0]=0;
    for(int i=0;i<n_points;++i){
        if(converted_points[i].point->y==glob_max_y)
            init[n_init]++;
        else{
            glob_max_y=converted_points[i].point->y;
            init[++n_init]=1;
        }
    }

    int b_idx=0,b_tmp,next,prev,n_points_in_row,arr_size=0,insert_pos;

    for(int i=0;i<n_init;++i){
        for(n_points_in_row=0;n_points_in_row<init[i];++n_points_in_row){
            b_val=converted_points[b_idx+n_points_in_row].pos;
            next=(b_val+1)%n_points;
            prev=(b_val==0) ? n_points-1 : b_val-1;
            found=false;

            for(b_tmp=0;b_tmp<arr_size;++b_tmp){
                if(b_val==tmp[b_tmp]){
                    if(points[prev].y<points[b_val].y){
                        tmp[b_tmp]=prev;
                        arr_a[b_tmp]=get_dx(b_val,prev);
                    }else if(points[next].y<points[b_val].y){
                        tmp[b_tmp]=next;
                        arr_a[b_tmp]=get_dx(b_val,next);
                    }
                    else if(points[prev].y==points[b_val].y||points[next].y==points[b_val].y){
                        remove_int(tmp,b_tmp,arr_size);
                        remove_double(arr_a,b_tmp,arr_size);
                        remove_double(lines_points,b_tmp,arr_size);
                        --arr_size;
                    }
                    else{
                        remove_int(tmp,b_tmp,arr_size);
                        remove_int(tmp,b_tmp,arr_size-1);
                        remove_double(arr_a,b_tmp,arr_size);
                        remove_double(arr_a,b_tmp,arr_size-1);
                        remove_double(lines_points,b_tmp,arr_size);
                        remove_double(lines_points,b_tmp,arr_size-1);
                        arr_size-=2;
                    }  
                    found=true;
                    break;
                }
            }
            if(!found){
                /* Jsou zde 2 nové (neuvažované) úsečky, každá s tímto bodem */
                /* je nutné vědět, na jakou pozici obě úsečky vložit, b_tmp nemusí vypovídat */
                insert_pos=0;
                while(points[b_val].x>lines_points[insert_pos] && insert_pos<arr_size)++insert_pos;

                a1=get_dx(b_val,prev);
                a2=get_dx(b_val,next);
                tmp1=prev;
                if(a1>a2){
                    /* prohod prev,next: */
                    prev=next;
                    next=tmp1;
                    /* prohod a1,a2: */
                    tmp2=a1;
                    a1=a2;
                    a2=tmp2;
                }
                if(points[prev].y!=points[b_val].y){
                    insert_int(tmp,insert_pos,prev,arr_size);
                    insert_double(arr_a,insert_pos,a1,arr_size);
                    insert_double(lines_points,insert_pos,points[b_val].x,arr_size);
                    ++arr_size;
                    ++insert_pos;
                }
                if(points[next].y!=points[b_val].y){
                    insert_int(tmp,insert_pos,next,arr_size);
                    insert_double(arr_a,insert_pos,a2,arr_size);
                    insert_double(lines_points,insert_pos,points[b_val].x,arr_size);
                    ++arr_size;
                }
            }
        }
        b_idx+=init[i];

        for(;row>converted_points[b_idx].point->y;--row){
            for(int k=0; k<arr_size;k+=2){
                Ax=lines_points[k]+=arr_a[k];
                Bx=lines_points[k+1]+=arr_a[k+1];


                /* dochazi k postupne odchylce od realne hodnoty v zavislosti na presnosti arr_a[k] */
                /* nakonec vzdy bude potreba cislo zaokrouhlit, ale pro neovlivneni vysledku postupnym pricitanim uz tak nepresne hodnoty by stacilo cislo prevest racionalni cislo na podil dvou cisel */  


                if(Ax>Bx){
                    printf("\n!! Ax:%f Bx:%f",Ax,Bx);
                }

                /* nebo zjistit chybovost a tu pouzit v rovnici zde */
                for(double x=Ax;x<=Bx;++x){
                    point_add(&current_point);
                    point_set(x,row,&current_point);
                }
            }
        }
    }
}

void _set_polygon_fill(polygon *input,point **tracked_point) {
    points=input->points;
    n_points=input->n_points;

    current_point=point_new();
    *tracked_point=current_point;
    solve();
}

