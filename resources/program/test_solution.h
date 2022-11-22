const double pi = 22.0 / 7.0;

static void test_solution(){

   /* usecka */
   input_line.ax = 100;
   input_line.ay = 300;
   input_line.bx = 400;
   input_line.by = 850;
   make_obj("line",false);
   render(&last_obj);

   /* 2D rotace */
   input_rot2d.obj = &last_obj;
   input_rot2d.alpha = pi/2;
   input_rot2d.S->x = 250; 
   input_rot2d.S->y = 250; 
   make_obj("rot2d",false);
   render(&last_obj);

   /* stred rotace */
   input_point.x = 250; 
   input_point.y = 250;
   make_obj("point",false);
   render(&last_obj);

   /* kruznice */
   input_ring.r = 50;
   input_ring.S->x = 500;
   input_ring.S->y = 500;
   make_obj("ring",false);
   render(&last_obj);

   /* kruh */
   input_circle.r = 50;
   input_circle.S->x = 500;
   input_circle.S->y = 500;
   make_obj("circle",false);
   render(&last_obj);

	/* zrcladleni kruznice pres primku */
	input_mirror_to_line.line = &input_line;
	input_point.x = input_ring.S->x;
	input_point.y = input_ring.S->y;
	make_obj("point",false);
	input_mirror_to_line.obj = &last_obj;
	make_obj("mirror_to_line",false);
	input_ring.S->x = last_obj.points->x;
	input_ring.S->y = last_obj.points->y;
	make_obj("ring",false);
	render(&last_obj);


}

