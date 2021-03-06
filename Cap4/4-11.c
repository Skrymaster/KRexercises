#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
//gcc -lm necesar la compilare
//modificat pe fişierul 4-3 unde getop era mai aproape de originalul din K&R

#define MAXOP 100
#define NUMBER 0
#define MAXVAL 100
#define BUFSIZE 100

int getop(char *);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void viewstack(void);

int bufp = 0;
char buf[BUFSIZE];
int sp = 0;
double val[MAXVAL];

int main(void){
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF){

		switch(type){
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: division by zero\n");
				break;
			case '%':
				op2 = pop();
				if(op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: division by zero\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

void push(double f){
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void){
	if(sp > 0)
		return val[--sp];
	else{
		printf("error: stack empty\n");
		exit(1);
	}
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int getop(char *s){
	int i, c, d;
    // modificat cu variabilă statică
    static char buf = EOF;
    if (buf == EOF || buf == ' ' || buf == '\t') {
        while((s[0] = c = getch()) == ' ' || c == '\t');
        s[1] = '\0';
    }
    else
        c = buf;
	if(!isdigit(c) && c != '.' && c != '-')
		return c;



	if(c == '-'){
		d = getch();
		if(d == ' ')
			return c;
		else
			buf = d;
	}
	i = 0;
	if(isdigit(c) || c == '-')
		while(isdigit(s[++i] = c = getch()));
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if(c != EOF)
		buf = c;
	return NUMBER;
}

void viewstack(void){
	int i;
	printf("\nstack:\n");
	for(i = sp - 1; i >= 0; i--)
		printf("%lf\n", val[i]);
}