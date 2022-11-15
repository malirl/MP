#include "controler.h"

char* LOG[1000];
int n_msg=0;

void out(char* msg){
	LOG[n_msg] = msg;
	LOG[++n_msg]= "\0";
	
	/* char msg_to_write[10]; */
			

}

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


void append_ch(char* s, char c) {
	size_t len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
}

void rm_range(char* s,int a,int b){
	int p;
	for(int i=0;i<b;++i)
		for(p=a+1;s[p-1]!='\0';++p)
			s[p-1]=s[p];
}

void rm_ch(char* s, char c) {
	for(size_t i=0;i<strlen(s);++i) {
		if(s[i]==c) {
			for(i+=1;s[i-1]!='\0';++i)
				s[i-1]=s[i];
		}
	}
}

void get_arr(char* str, char* arr) {
	for(size_t i=0;i<strlen(str);++i) {
		arr[i]=*(str+i);
		arr[i+1] = '\0';
	}
}

bool compare_strs(char* str1, char* str2){
	if(strlen(str1)!=strlen(str2))
		return false;
	for(size_t i=0;i<strlen(str1);++i)
		if(*(str1+i)!=*(str2+i))
			return false;
	return true;
}

void replace_str_by(char* in, char out[], int index){
	int len = strlen(in);
	for(int i=index;i<=index+len;){
		out[i]=*(++in-1);
		out[++i]='\0';
	}
}

char res[100], new_pattern[100], searched[100];

void get_from_str(char* pattern, char string[], char** str_to_set,int* idx,int* len) {
	memset(res, 0, 100);
	memset(new_pattern, 0, 100);
	memset(searched, 0, 100);
	*idx = *len = -1;	

	int match_idx, match_length, i, first_closure = (int)(strchr(pattern, '(') - pattern),
			second_closure = (int)(strchr(pattern, ')') - pattern);
	bool closures_defined = false;

	if(first_closure >= 0 && second_closure >= 0)
		closures_defined = true;

	if(closures_defined) {
		/* strcpy(new_pattern,pattern); */
		/* rm_range(new_pattern,0,first_closure); */
		/* rm_range(new_pattern,strlen(pattern)-first_closure+1,second_closure); */

		for(i=first_closure+1;i<second_closure;++i)
			append_ch(new_pattern, *(pattern+i));

		char arr[] = {'\0'};
		get_arr(pattern,arr);
		pattern = arr;

		rm_ch(pattern, '(');	
		rm_ch(pattern, ')');	
	}
	
	match_idx = re_matchp(re_compile(pattern), string, &match_length);

	if(match_idx==-1){
		*str_to_set = NULL;
		return;
	}

	*idx=match_idx;
	*len=match_length;

	for(i=0;i<match_length;++i) 
		append_ch(searched, string[match_idx + i]);

	char* result=malloc(sizeof(char*));

	if(closures_defined) {
		match_idx = re_matchp(re_compile(new_pattern), searched, &match_length);
		if(match_idx==-1){
			*str_to_set = NULL;
			return;
		}

		for(i=0;i<match_length;++i)
			append_ch(res, searched[match_idx + i]);

		strcpy(result,res);
	} else strcpy(result,searched);

	*str_to_set=result;
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
			printf("\nmissing mandatory param %s!",pattern);
			return false;
		}

		memset(tmp,0,strlen(tmp));
		get_arr(pattern,tmp);
		replace_str_by(":(\\d+)",tmp,strlen(pattern));	

		get_from_str(tmp,str_input,&val,&idx,&len);

		if(val) {
			printf("\n'%s' assigned to: %s\n",val,pattern);
			/* validace! */
			set_arg(obj_name,val);
		} else
			printf("\nINVALID VALUE: %s:'%s'\n",pattern,val);


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
			if(!(selected=test[++i][0]))//takovy nazev pro obj se nenasel
				return 0;

			if(compare_strs(selected, main_arg)){
				printf("\nprocessing object: %s",main_arg);
				if(process_args(argv,argc,test[i][1],main_arg))
					printf("\nargs successfully set");
				break;
			}
		}
	}





	return 0;

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

