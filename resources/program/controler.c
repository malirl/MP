#include "controler.h"
#include "test_solution.h"

#define MODE int
#define MODE_CMD 1
#define MODE_DEV 2

int main(int argc, char *argv[]) {

	MODE mode = MODE_CMD;

	switch(init_render()) {
		case EXIT_FAILURE:
			return EXIT_FAILURE;
	}

	init_data();
	list_objs = new_obj();
	start_obj = list_objs; 
	/* //// */

	switch(mode){
		case MODE_CMD:
			if(!proc_one_obj(argc,argv))
				return EXIT_FAILURE;
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

