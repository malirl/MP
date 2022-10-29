#include "controler.h"

static void example() {
	/* usecka */
	input_line.ax = 100;
	input_line.ay = 300;
	input_line.bx = 400;
	input_line.by = 850;
	make_obj("line");
	render_obj(&last_obj);


	/* kruznice */
	input_circle.r = 50;
	input_circle.S->x = 500;
	input_circle.S->y = 500;
	make_obj("circle");
	render_obj(&last_obj);


	/* zrcladleni kruznice pres primku */
	input_mirror_to_line.line = &input_line;
	input_point.x = input_circle.S->x;
	input_point.y = input_circle.S->y;
	make_obj("point");
	input_mirror_to_line.obj = &last_obj;
	make_obj("mirror_to_line");
	input_circle.S->x = last_obj.points->x;
	input_circle.S->y = last_obj.points->y;
	make_obj("circle");
	render_obj(&last_obj);

}



int main(void) {
	switch(init_render()) {
		case EXIT_FAILURE:
			return EXIT_FAILURE;
	}

	init_data();
	list_objs = new_obj();
	start_obj = list_objs; 
	/* //// */


	example();


	/* //// */
	switch(resolve_window_events()) {
	};

	return EXIT_SUCCESS;
}

