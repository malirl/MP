typedef struct{
   int x, y;
   struct point *next;
}point;

typedef struct{
	point *points;
	char name[10];
	int color;
}obj;

typedef struct{
   int r, sx, sy;
}input;


void circle_bresenham(input *res, point **point);

