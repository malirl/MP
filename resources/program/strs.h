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

