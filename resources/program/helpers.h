
#ifdef LINE_INTERSECTION

#define PARALELL_LINES 1
#define SAME_LINES 2
#define INTERSECTED_LINES 3

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    double x, y;
}intersect;


static int is_lines_parallel(line *a, line *b){
    double Ax=a->A.x, Ay=a->A.y, 
           Bx=a->B.y, By=a->B.y,
           Cx=b->A.x, Cy=b->A.y,
           Dx=b->B.x, Dy=b->B.y;

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


static intersect* line_intersection(line *a, line *b,bool edges_counted){
   if(is_lines_parallel(a,b)!=INTERSECTED_LINES)
      return NULL;

   /* predpoklada se, ze Ax + a1*t = Bx, kdyz t=1, tedy a1 je Bx-Ax, atd. u dalsich souradnic vektoru */
    double Ax=a->A.x, Ay=a->A.y, 
           Bx=a->B.y, By=a->B.y,
           Cx=b->A.x, Cy=b->A.y,
           Dx=b->B.x, Dy=b->B.y;

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

#endif

