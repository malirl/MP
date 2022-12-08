#define POINT_IN
/* #define POINT_D */
#define OBJ_IN
#define ROT3D_IN
#define HELPERS

#include <stdio.h>
#include <math.h>
#include "../inputs.h"

/* static point *head; */
/* static double alpha, x1, y1, x2, y2; */
/* static int Sx, Sy, x, y; */ 

/* static point *head; */
static double o1,o2,o3;
static int xa,ya,za;
static double alpha;



/* static point* get_k(point vec){ */
/* } */


static void solve() {
   double x1,x2,x3;
   double k;

   // predpoklada se nenulovy vektor o

   /* prevedeni na vektor velikosti 1 */
   k=sqrt(o1*o1+o2*o2+o3*o3);
   o1/=k;
   o2/=k;
   o3/=k;

   printf("\no1=%f\no2=%f\no3=%f",o1,o2,o3);

   if(o1!=0 && o2!=0){
      x1=-o2;
      x2=o1;
      x3=0;
   } else{
      x2=-o3;
      x3=o2;
      x1=0;
   }


   k=sqrt(x1*x1+x2*x2+x3*x3);
   x1/=k;
   x2/=k;
   x3/=k;


   printf("\nx1=%f\nx2=%f\nx3=%f",x1,x2,x3);

   /* B */
   int 
      y1=o3*x2-o2*x3,z1=o1,
      y2=o1*x3-o3*x1,z2=o2,
      y3=o2*x1-o1*x2,z3=o3;


   /* preved do B pres inverzni/transponovanou matici B*/
  double 
      xb=x1*xa+x2*ya+x3*za,
      yb=y1*xa+y2*ya+y3*za,
      zb=z1*xa+z2*ya+z3*za;

   /* zrotuj do 2d v B */
   double 
      rotX=xb*cos(alpha) + yb*sin(alpha),
      rotY=yb*cos(alpha) - xb*sin(alpha),
      rotZ=zb;

   printf("\n%f\n",yb);
   /* preved zpatky do A */
   double 
      resX=x1*rotX+y1*rotY+z1*rotZ,
      resY=x2*rotX+y2*rotY+z2*rotZ,
      resZ=y3*rotY+z3*rotZ;


   printf("\nresX=%f\nresY=%f\nresZ=%f",resX,resY,resZ);


   /* vysledek je bod resX,resY,resZ */
   point_set(1,1,&current_point);




   /*    while(1) { */
   /*       x = head->x-Sx; */
   /*       y = head->y-Sy; */

   /*       head = (point*)head->next; */
   /*       if(!head) */
   /*          return; */

   /*       point_add(&current_point); */
   /*    } */


}

void _rot3d(rot3d *input, point **tracked_point) {
   xa=input->x;
   ya=input->y;
   za=input->z;

   o1=input->O->x;
   o2=input->O->y;
   o3=input->O->z;

   alpha = input->alpha; 

   /* head = (point*)input->obj->points; */

   current_point = point_new();
   *tracked_point = current_point;
   solve();
}

