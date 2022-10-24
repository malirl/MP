#include "controler.h"


static void example() {

	/* usecka */
	obj obj_line;
	line input_line;
	input_line.ax = 100;
	input_line.ay = 300;
	input_line.bx = 400;
	input_line.by = 850;
	set_line(&obj_line, &input_line);
	render_obj(&obj_line);

	
	/* zrcladleni objektu pres primku definovanou dvema body */
	obj mirror;
	mirror.points = (point*)malloc(sizeof(point));
	mirror.points->x = 400;
	mirror.points->y = 550;
	render_obj(&mirror);
	mirror_to_line(&mirror, &input_line);
	render_obj(&mirror);

		
	/* kruznice */
	obj obj_circle;
	circle input_circle;
	input_circle.r = 300;
	input_circle.sx = 500; 
	input_circle.sy = 500;
	set_circle(&obj_circle, &input_circle);
	render_obj(&obj_circle);

	
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
