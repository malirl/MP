#define N_CHARS 100000 

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

char res[N_CHARS], new_pattern[N_CHARS], searched[N_CHARS];
void get_from_str(char* pattern, char string[], char** str_to_set,int* idx,int* len) {

	/* strcpy(); */

	memset(res, 0, N_CHARS);
	memset(new_pattern, 0, N_CHARS);
	memset(searched, 0, N_CHARS);
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

	/* !! */	
	char clone_pattern[strlen(pattern)];
	clone_pattern[0]='\0';
	for(i=0;i<(int)strlen(pattern);++i) 
		append_ch(clone_pattern, *(pattern+i));
	/* !! */

	match_idx = re_matchp(re_compile(pattern),string, &match_length);


	if(match_idx==-1){
		*str_to_set = NULL;
		return;
	}

	*idx=match_idx;
	*len=match_length;

	for(i=0;i<match_length;++i) 
		append_ch(searched, string[match_idx + i]);

	char* result;

	if(closures_defined) {


	/* pattern pro odstraneni prvnich znaku ze zacatku textu: vem si rozmezi 0 az a-1 patternu do charu */
	char to_remove_from_str[strlen(clone_pattern)];

	replace_str_by(clone_pattern,to_remove_from_str,0);
	rm_range(to_remove_from_str,first_closure,strlen(clone_pattern));

	/* matchuj str_input s pattern pro vymaz */
	match_idx = re_matchp(re_compile(to_remove_from_str), searched, &match_length);

	/* vymaz v searched v rozmezi 0 az len */
	rm_range(searched,0,match_length);









	match_idx = re_matchp(re_compile(new_pattern), searched, &match_length);
	if(match_idx==-1){
		*str_to_set = NULL;
		return;
	}



/* pro konec: */
	if(second_closure < (int)strlen(clone_pattern)){
		replace_str_by(clone_pattern,to_remove_from_str,0);
		rm_range(to_remove_from_str,0,second_closure-1);

		rm_range(searched,re_matchp(re_compile(to_remove_from_str), searched, &match_length),strlen(searched));

	}

	/* printf("\n-po vymazani ze searched: %s-\n",searched); */



	for(i=0;i<match_length;++i)
		append_ch(res, searched[match_idx + i]);

	result=(char*)malloc(sizeof(res));
	strcpy(result,res);
	} else {
		result=(char*)malloc(sizeof(searched));
		strcpy(result,searched);
	}

	*str_to_set=result;
}
/* strfcat() is a function that is similar to the strcat() function, but it is safer and it is able to handle the format of the string. */ 
int strfcat(char *dest, const char *format, ...)
{
	va_list args;
	int len;

	va_start(args, format);
	len = vsnprintf(dest + strlen(dest), 0, format, args);
	va_end(args);

	va_start(args, format);
	vsnprintf(dest + strlen(dest), len + 1, format, args);
	va_end(args);

	return len;
}

