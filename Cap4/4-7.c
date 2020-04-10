#include <stdio.h>
#include <string.h>

#define BUFSIZE 30

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
void ungets(char *);

int main(void){
	char s[] = "Test testtest Test, test.\n";
	int c;
	ungets(s);
	while((c = getch()) != EOF)
		putchar(c);
	return 0;
}

int getch(void){
	return bufp > 0 ? buf[--bufp] : getchar();
}
// Am găsit că e mai bine ca fiecare funcţie să-şi facă bounds checking în parte, şi de asemenea funcţia ungets să se bazeze pe funcţia ungetch pentru a fi mai uşor modificată pe viitor.
void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("error: stack is full\n");
	else
		buf[bufp++] = c;
}

void ungets(char *s){
	int i, len;
	len = strlen(s);
	if(BUFSIZE - bufp >= len)
	{
		for(i = strlen(s) - 1; i >= 0; i--)
			ungetch(s[i]);
	}
	else
		printf("error: buffer too small\n");
}