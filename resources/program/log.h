#define RED "\x1B[31m"
#define KYEL "\x1B[33m" 
#define GREEN "\x1B[32m"
#define WHITE "\x1B[37m"

#define ERR -1
#define INFO 0
#define SUCCESS 1

char* LOG[1000];
int lvl_msgs[1000];
int n_msg=-1;


void out(int status,int lvl,char* msg,const char* fmt, ...){
	/* !! */
	LOG[++n_msg]=(char*)malloc(strlen(msg));
	strcpy(LOG[n_msg],msg);
	lvl_msgs[n_msg]=lvl;
	/* !! */
	
	int k;
	char *str_format; 

	str_format=" ";
	char str_format_arr[strlen(str_format)+lvl*2+100];
	get_arr(str_format,str_format_arr);

	for(k=0;k<lvl;++k)
		replace_str_by("  ",str_format_arr,strlen(str_format_arr));	

	switch(lvl){
		case 0:
	 		replace_str_by("%s",str_format_arr,strlen(str_format_arr));	
			break;
		default:
	 		replace_str_by("• %s",str_format_arr,strlen(str_format_arr));	
		break;
	}
	switch(status){
		case ERR:
			printf(RED);
			break;
		case SUCCESS:
			printf(GREEN);
			break;
		case INFO:
			printf(KYEL);
			break;
		default:
			break;
	}

	printf((char*)str_format_arr,LOG[n_msg]);
	va_list args;
	va_start(args,fmt);
	vprintf(fmt,args);
	va_end(args);
	printf(WHITE);
	printf("\n");
}

