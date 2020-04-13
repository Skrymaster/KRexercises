#include <ctype.h>
#include <stdio.h>

#define MAX 20

int getch(void);
void ungetch(int);
int getint(int *);

int bufp = 0;
int buf[MAX];


int main(void){

    int i, matrix[MAX];

	for (i = 0; i < MAX && getint(&matrix[i]) != EOF; i++)
		printf("matrix[%d]:%d\n", i, matrix[i]);
	return 0;
}

int getint(int *pn){
    int c, sign;

    while (isspace(c = getch()));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-'){
        c = getch();
		if (!isdigit(c)) {
			ungetch(sign == 1 ? '+' : '-');
			return 0;
		}
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}


int getch(void){
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if (bufp >= 100)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}