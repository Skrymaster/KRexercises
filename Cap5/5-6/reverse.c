#include <stdio.h>

#define BUFSIZE 100

void reverse(char *s);

int main(void){
	char string[BUFSIZE];
	scanf("%s", string);
	printf("string: %s, ", string);
	reverse(string);
	printf("reversed: %s\n", string);
	return 0;
}

void reverse(char *s){
	char *p;
	int temp;
	p = s;
	while(*p)
		p++;
	p--;
	while(s<=p){
		temp = *s;
		*s = *p;
		*p = temp;
		s++;
		p--;
	}
}