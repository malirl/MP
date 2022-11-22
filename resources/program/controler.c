#include "controler.h"
#include "test_solution.h"

#define MODE int
#define MODE_CMD 1
#define MODE_DEV 2




int main(int argc, char *argv[]) {

	MODE mode = MODE_CMD;

	if(argc>1)
		mode=MODE_CMD;
	
	out(INFO,0,"mode number: "," %d",mode);

	switch(init_render()) {
		case EXIT_FAILURE:
			return EXIT_FAILURE;
	}

	init_data();
	start_obj = list_objs = new_obj();
	/* //// */

	switch(mode){
		case MODE_CMD:
			if(proc_obj_cmd(argc,argv)){
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
	printf("\n");
	/* //// */
	switch(resolve_window_events()) {
	};

	return EXIT_SUCCESS;
}

