#include <stdio.h>

#define BUFSIZE 100

int strindex(char *, char *);

int main(void){
	char s[BUFSIZE], t[BUFSIZE];
	scanf("%s", s);
	scanf("%s", t);
	printf("strindex(%s, %s): %d\n", s, t, strindex(s, t));
	return 0;
}

int strindex(char *s, char *t){
	int tlen, count;
	char *p, *q, *r;
	q = t;
	while(*q++);
	q--;
	tlen = q-t;
	for(p = s; *p ; p++){
		count = 0;
		r = p;
		for(q = t; *q ; q++, r++){
			if(*r == *q)
				count++;
			else
				break;
		}
		if(count == tlen)
			return (int)(p-s);
	}
	return -1;
}