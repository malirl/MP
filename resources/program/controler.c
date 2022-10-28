#include "controler.h"


static obj* add_obj(char name[]) {
	obj *obj_to_set = (struct obj*)malloc(sizeof(obj));

	if(strcmp(name, "line") == 0)
		set_line(obj_to_set, &input_line);
	else if(strcmp(name, "circle") == 0)
		set_circle(obj_to_set, &input_circle);
	else if(strcmp(name, "mirror_to_line") == 0)
		set_mirror_to_line(obj_to_set, &input_mirror_to_line);
	else if(strcmp(name, "point") == 0)
		set_point(obj_to_set, &input_point);

		/* scene.obj = obj_to_set; */
		/* scene.obj.next = (struct scene*)malloc(sizeof(scene)); */
		/* scene = *scene.obj.next; */

		return obj_to_set;	
}




static void example() {

	/* usecka */
	input_line.ax = 100;
	input_line.ay = 300;
	input_line.bx = 400;
	input_line.by = 850;
	render_obj(add_obj("line"));	

	/* kruznice */
	input_circle.r = 50;
	
	input_circle.sx = 500; 
	input_circle.sy = 500;
	render_obj(add_obj("circle"));


	/* zrcladleni objektu pres primku definovanou dvema body */
	input_point.x = input_circle.sx;
	input_point.y = input_circle.sy;
	input_mirror_to_line.obj = add_obj("point");

	input_mirror_to_line.ax = 100;
	input_mirror_to_line.ay = 300;
	input_mirror_to_line.bx = 400;
	input_mirror_to_line.by = 850;


	/* obj *mirrored = add_obj("mirror_to_line"); */
	/* printf("%d",mirrored->points->y); */
	/* printf("%d",add_obj("mirror_to_line")->points->y); */


	/* input_circle.sx = mirrored->points->x; */
	/* input_circle.sy = mirrored->points->y; */
	/* render_obj(add_obj("circle")); */


}



int main(void) {
	switch(init_render()) {
		case EXIT_FAILURE:
			return EXIT_FAILURE;
	}


	example();


	switch(resolve_window_events()) {
	};

	return EXIT_SUCCESS;
}

