const double pi = 22.0 / 7.0;

static void test_solution(){

   /* usecka */
   input_line.A.x = 100;
   input_line.A.y = 300;
   input_line.B.x = 400;
   input_line.B.y = 850;
   make_obj("line");
	 add_obj_points_scene(&last_obj,false);

   /* 2D rotace */
   input_rot2d.obj = &last_obj;
   input_rot2d.alpha = pi/2;
   input_rot2d.S->x = 250; 
   input_rot2d.S->y = 250; 
   make_obj("rot2d");
	 add_obj_points_scene(&last_obj,false);

   /* stred rotace */
   input_point.x = 250; 
   input_point.y = 250;
   make_obj("point");
	 add_obj_points_scene(&last_obj,false);

   /* kruznice */
   input_ring.r = 50;
   input_ring.S->x = 500;
   input_ring.S->y = 500;
   make_obj("ring");
	 add_obj_points_scene(&last_obj,false);

   /* kruh */
   input_circle.r = 50;
   input_circle.S->x = 500;
   input_circle.S->y = 500;
   make_obj("circle");
	 add_obj_points_scene(&last_obj,false);


   /* zrcladleni kruznice pres primku */
   input_mirror_to_line.line = &input_line;
   input_point.x = input_ring.S->x;
   input_point.y = input_ring.S->y;
   make_obj("point");
   input_mirror_to_line.obj = &last_obj;
   make_obj("mirror_to_line");
   input_ring.S->x = last_obj.points->x;
   input_ring.S->y = last_obj.points->y;
   make_obj("ring");
	 add_obj_points_scene(&last_obj,false);


   /* 3D rotace */
   /* input_rot3d.obj = &last_obj; */

   input_rot3d.alpha = pi/1.2;

   input_rot3d.O->x = 0; 
   input_rot3d.O->y = 0; 
   input_rot3d.O->z = 1; 
   make_obj("rot3d");
   /* render(&last_obj); */




   render(scene_.points);
}

