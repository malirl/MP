#include "controler.h"

static void example() {

	/* usecka */
	input_line.ax = 100;
	input_line.ay = 300;
	input_line.bx = 400;
	input_line.by = 850;
	add_obj("line");
	render_obj(&current_obj);

	/* kruznice */
	input_circle.r = 50;
	input_circle.sx = 500; 
	input_circle.sy = 500;
	add_obj("circle");
	render_obj(&current_obj);

	/* zrcladleni objektu pres primku definovanou dvema body */
	input_point.x = input_circle.sx;
	input_point.y = input_circle.sy;
	add_obj("point");
	input_mirror_to_line.obj = &current_obj;
	input_mirror_to_line.ax = 100;
	input_mirror_to_line.ay = 300;
	input_mirror_to_line.bx = 400;
	input_mirror_to_line.by = 850;
	add_obj("mirror_to_line");
	input_circle.sx = current_obj.points->x;
	input_circle.sy = current_obj.points->y;
	add_obj("circle");
	render_obj(&current_obj);


}



int main(void) {
	switch(init_render()) {
		case EXIT_FAILURE:
			return EXIT_FAILURE;
	}

	list_objs = new_obj();
	/* //// */


	example();


	/* //// */
	switch(resolve_window_events()) {
	};

	return EXIT_SUCCESS;
}

