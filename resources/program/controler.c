#include "controler.h"
#include "dev_test.h"

#define MODE int
#define MODE_CMD 1
#define MODE_DEV 2

bool running = true;

MODE mode;


int main(int argc, char *argv[]) {
	
	if(argc>1)
		mode=MODE_CMD;
	else
		mode=MODE_DEV;

	out(INFO,0,"mode number: "," %d",mode);

	init_data();
	start_obj = list_objs = new_obj();


	/* //// */
	switch(mode){
		case MODE_CMD:
			init_scene(&scene_);
			if(proc_obj_cmd(argc,argv)){
				set_resolution(scene_.width,scene_.height);
				switch(init_render()) {
					case EXIT_FAILURE:
						out(ERR,0,"initialization render failed","");
						return EXIT_FAILURE;
				}
				if(render(scene_.points))
					out(SUCCESS,0,"creation and render succeeded","");
				else{
					out(ERR,0,"object render failed","");
					return EXIT_FAILURE;
				}
			}else{
				out(ERR,0,"object creation failed","");
				return EXIT_FAILURE;
			}
			break;
		case MODE_DEV:
			init_scene(&scene_);
			set_resolution(scene_.width,scene_.height);
			init_render();
			test_solution();
			while(1){
				switch(resolve_window_events()) {
					case STATE_QUIT:
						return EXIT_SUCCESS;
				}
			}
			break;
	}


	out(INFO,0,"resolving window events...","");
	/* //// */

	double angle_shift=3.14/8;
	while(resolve_window_events()){

	}
		


	while(running){
		switch(resolve_window_events()) {
			case STATE_QUIT:
				running=false;
				break;
			case ACTION_RIGHT:
				if(scene_.space==_3D){
					scene_.alpha+=angle_shift;
					change_O_pos(0,angle_shift);
				}else{
					scene_.shiftX-=20;
					shift(scene_.shiftX,scene_.shiftY);
				}
				re_render(scene_.points,false);
				break;
			case ACTION_LEFT:
				if(scene_.space==_3D){
					scene_.alpha-=angle_shift;
					change_O_pos(0,-angle_shift);
				}else{
					scene_.shiftX+=20;
					shift(scene_.shiftX,scene_.shiftY);
				}
				re_render(scene_.points,false);
				break;
			case ACTION_UP:
				if(scene_.space==_3D){
					scene_.sigma=+10;
					change_O_pos(angle_shift,0);
				}else{
					scene_.shiftY-=20;
					shift(scene_.shiftX,scene_.shiftY);
				}
				re_render(scene_.points,false);
				break;
			case ACTION_DOWN:
				if(scene_.space==_3D){
					scene_.sigma-=10;
					change_O_pos(-angle_shift,0);
				}else{
					scene_.shiftY+=20;
					shift(scene_.shiftX,scene_.shiftY);
				}
				re_render(scene_.points,false);
				break;
			case ACTION_ZOOM_PLUS:
				if(scene_.width-50>200){
					scene_.width-=50;
					scene_.height-=50;

					scene_.shiftX-=25;
					scene_.shiftY-=25;


					shift(scene_.shiftX,scene_.shiftY);
					set_resolution(scene_.width,scene_.height);
					re_render(scene_.points,true);
				}
				break;
			case ACTION_ZOOM_MINUS:
				if(scene_.height<950){
					scene_.width+=50;
					scene_.height+=50;

					scene_.shiftX+=25;
					scene_.shiftY+=25;

					shift(scene_.shiftX,scene_.shiftY);
					set_resolution(scene_.width,scene_.height);
					re_render(scene_.points,true);
				}
				break;
			default:
				break;
		};
	}
	return EXIT_SUCCESS;
}

