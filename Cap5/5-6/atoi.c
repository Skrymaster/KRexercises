#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

int atoi(char *);

int main(void){
	char string[BUFSIZE];
	scanf("%s", string);
	printf("string: %s, number: %d\n", string, atoi(string));
	return 0;
}

int atoi(char *s){
	int sign, n = 0;
	while(isspace(*s))
		s++;
	sign = (*s == '-') ? -1 : 1;
	if(*s == '+' || *s == '-')
		s++;
	while(isdigit(*s)){
		n = 10 * n + (*s-'0');
		s++;
	}
	return n*sign;
}