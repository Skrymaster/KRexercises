#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
//gcc -lm necesar la compilare

#define MAXOP 100
#define NUMBER 0
#define MAXVAL 100
#define BUFSIZE 100
#define IDENTIFIER 1
#define VARIABLE 2
#define MAXLINE 1000

int getop(char *);
void push(double);
double pop(void);
// int getch(void);
// void ungetch(int);
void showTop(void);
void swap(void);
void duplicate(void);
void clearStack(void);
void mathFunctions(char *);

int bufp = 0;
char buf[BUFSIZE];
int sp = 0;
double val[MAXVAL];
char last;
double variableValue[26] = {0};

char line[MAXLINE];
int line_index;

int main(void){
	int type;
	double op2;
	char s[MAXOP];
    line_index = 0;
    while((type = getop(s)) != EOF){

        switch(type){
            case NUMBER:
                push(atof(s));
                break;
            case IDENTIFIER:
                mathFunctions(s);
                break;
            case VARIABLE:
                push(variableValue[last - 97]);
                break;
            case '_': //ultima variabilă
                push(0);
                printf("%c\n", last);
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
            case '?':
                showTop();
                break;
            case '~':
                swap();
                break;
            case '#':
                duplicate();
                break;
            case '!':
                clearStack();
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

// int getch(void){
// 	return (bufp > 0) ? buf[--bufp] : getchar();
// }

// void ungetch(int c){
// 	if(bufp >= BUFSIZE)
// 		printf("ungetch: too many characters\n");
// 	else
// 		buf[bufp++] = c;
// }
int mygetline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

int getop(char *s){
	int i, c, d;
    int identif = 1;
    int length;
	while((s[0] = c = line[line_index++]) == ' ' || c == '\t');
	s[1] = '\0';
	if(!isdigit(c) && c != '.' && c != '-')
		return c;
	if(c == '-'){
		d = line[line_index++];
		if(d == ' ')
			return c;
		else
			line[line_index--];
	}
	i = 0;
	if(isdigit(c) || c == '-')
		while(isdigit(s[++i] = c = line[line_index++]));
	if(c == '.')
		while(isdigit(s[++i] = c = line[line_index++]));
	s[i] = '\0';
	if(c != EOF)
		line[line_index--];

    length = strlen(s);
	if(length == 1 && isalpha(s[0])){
		last = s[0];
		return VARIABLE;
	}	

	for(i = 0; s[i] != '\0'; i++)
		if(!isalpha(s[i]))
		{
			identif = 0;
			break;
		}
	if(identif == 1)
		return IDENTIFIER;
	else
		return NUMBER;
}

void showTop(void){
	sp > 0 ? printf("\t%.8g\n", val[sp-1]) : printf("stack is empty\n");
}

void swap(void){
	double temp;
	if(sp < 1)
		printf("error: can't swap, too few elements\n");
	else{
		temp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = temp; 
	}
}

void duplicate(void){
	if(sp > MAXVAL - 1)
		printf("error: stack full, can't duplicate\n");
	else{
		double temp = pop();
		push(temp);
		push(temp);
		++sp;
	}
}

void clearStack(void){
	sp = 0;
}

void mathFunctions(char *s)
{
	if(strcmp(s, "sin") == 0)
	{
		if(sp < 1)
			printf("error: stack empty, can't use sin\n");
		else
			push(sin(pop()));
	}
	else if(strcmp(s, "cos") == 0)
	{
		if(sp < 1)
			printf("error: stack empty, can't use cos\n");
		else
			push(cos(pop()));		
	}
	else if(strcmp(s, "exp") == 0)
	{
		if(sp < 1)
			printf("error: stack empty, can't use exp\n");
		else
			push(exp(pop()));
	}
	else if(strcmp(s, "pow") == 0)
	{
		if(sp < 2)
			printf("error: less than 2 elements, can't use pow\n");
		else
		{
			double op2;
			op2 = pop();
			push(pow(pop(), op2));
		}
	}
	else
		printf("%s is not a supported function\n", s);
}