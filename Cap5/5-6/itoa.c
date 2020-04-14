#include <stdio.h>

#define BUFSIZE 100

char *itoa(int n, char *s);
void reverse(char *s);


int main(void){
	int number;
	char string[BUFSIZE];
	scanf("%d", &number);
	printf("number: %d, string: %s\n", number, itoa(number, string));
	return 0;
}

char *itoa(int n, char *s)
{
	int sign;
	char *p = s;
	sign = (n < 0) ? -1 : 1;
	(sign < 0) ? n = -n : 0;
	while(n > 0){
		*p++ = n%10 + '0';
		n = n / 10;
	}
	(sign == -1) ? (*p++ = '-') : 0;
	*p = '\0';
	reverse(s);
	return s;
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