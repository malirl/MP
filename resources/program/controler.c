#include "controler.h"

const double pi = 22.0 / 7.0;

static void example() {
	/* usecka */
	input_line.ax = 100;
	input_line.ay = 300;
	input_line.bx = 400;
	input_line.by = 850;
	make_obj("line");
	render_obj(&last_obj);


	/* 2D rotace */
	input_rot2d.obj = &last_obj;
	input_rot2d.alpha = pi/2;
	input_rot2d.S->x = 250; 
	input_rot2d.S->y = 250; 
	make_obj("rot2d");
	render_obj(&last_obj);

	/* stred rotace */
	input_point.x = 250; 
	input_point.y = 250;
	make_obj("point");
	render_obj(&last_obj);


	/* kruznice */
	input_ring.r = 50;
	input_ring.S->x = 500;
	input_ring.S->y = 500;
	make_obj("ring");
	render_obj(&last_obj);

	/* kruh */
	input_circle.r = 50;
	input_circle.S->x = 500;
	input_circle.S->y = 500;
	make_obj("circle");
	render_obj(&last_obj);



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
	render_obj(&last_obj);



}





void set_arg(char* obj_name,char* arg){

}

bool check_mandatory_args(char* str_input,char* args,char* obj_name){
	/* vyhledej v args, arg, ktery jednotlive pouzijes a odstranujes dokud neni match=-1 */
	/* 	kdyz to pritom nenajdes, dej chybu */
	char *pattern, *in_text, *val;
	char args_arr[strlen(args)+1], str_input_arr[strlen(str_input)+1];
	int idx,len;
	get_arr(args,args_arr);
	args=(char*)args_arr;
	get_arr(str_input,str_input_arr);
	str_input=(char*)str_input_arr;

	char tmp[20]; //20 delka nazvu jednoho argumentu

	while(1){
		get_from_str("\\w+",args,&pattern,&idx,&len);

		if(!pattern)
			return true;

		get_from_str(pattern,str_input,&in_text,&idx,&len);

		if(!in_text){
			out(ERR,1,"missing mandatory param: ","%s",pattern);
			return false;
		}

		memset(tmp,0,strlen(tmp));
		get_arr(pattern,tmp);
		replace_str_by(":(\\d+)",tmp,strlen(pattern));	

		get_from_str(tmp,str_input,&val,&idx,&len);

		if(val) {
			out(INFO,1,"","%s assigned to '%s'",pattern,val);
			/* validace! */
			set_arg(obj_name,val);
		} else
			out(ERR,1,"invalid value for:"," %s: %s",pattern,val);


		rm_range(args_arr,0,strlen(pattern)+1);
	}
}


bool process_args(char *argv[],int argc,char* args,char* main_arg) {
	char str_input[100];
	size_t n_ch = -1;
	for(int arg=2;arg<argc;++arg){
		for(size_t i=0;i<strlen(argv[arg]);++i) {
			str_input[++n_ch] = *(argv[arg]+i);
			str_input[n_ch+1] = '\0';
		}
		str_input[++n_ch] = ' ';
		str_input[n_ch+1] = '\0';
	}


	check_mandatory_args(str_input,args,main_arg);
	/* printf("\nargs successfully set"); */

	return true;
}



int main(int argc, char *argv[]) {

	char* test[][2] = {
		{"line", "ax ay bx by"},
		{"circle", "Sx Sy"},
		{"ring", "Sx Sy"},
		{NULL, ""}
	};

	/* single object set */
	/* checkni existenci hlavniho parametru a over dostupnost (line, circle,..) */
	if(argc > 1) {
		char* selected, *main_arg = argv[1];
		int	i=-1;

		while(1){
			if(!(selected=test[++i][0]))//takovy nazev pro obj se nenaseL
			{
				out(ERR,0,"unknown obj: ","'%s'",main_arg);
				return 0;
			}

			if(compare_strs(selected, main_arg)){
				out(SUCCESS,0,"processing object: ","%s",main_arg);
				if(process_args(argv,argc,test[i][1],main_arg))
					printf("\nargs successfully set");
				break;
			}
		}
	}






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

