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

	init_scene(&scene_);
	copy_scene_render(scene_);
	
	/* //// */
	switch(mode){
		case MODE_CMD:
			if(proc_obj_cmd(argc,argv)){
				switch(init_render()) {
					case EXIT_FAILURE:
						out(ERR,0,"initialization render failed","");
						return EXIT_FAILURE;
				}
				if(render(&last_obj))
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
			test_solution();
			break;
	}


	out(INFO,0,"resolving window events...","");
	/* //// */


	while(running){
		switch(resolve_window_events()) {
			case STATE_QUIT:
				running=false;
				break;
			case ACTION_RIGHT:
				scene_.shiftX-=20;
				break;
			case ACTION_LEFT:
				scene_.shiftX+=20;
				break;
			case ACTION_UP:
				scene_.shiftY-=20;
				break;
			case ACTION_DOWN:
				scene_.shiftY+=20;
				break;
			case ACTION_ZOOM_PLUS:
				if(scene_.width-50>200){
					scene_.width-=50;
					scene_.height-=50;

					scene_.shiftX-=25;
					scene_.shiftY-=25;
				}
				break;
			case ACTION_ZOOM_MINUS:
				if(scene_.height<950){
					scene_.width+=50;
					scene_.height+=50;

					scene_.shiftX+=25;
					scene_.shiftY+=25;
				}
				break;
			default:
				break;
		};
		copy_scene_render(scene_);
		render(&last_obj);
	}
	stop_render();
	return EXIT_SUCCESS;
}

