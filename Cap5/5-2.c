#include <ctype.h>
#include <stdio.h>
#include <math.h>

#define BUFSIZE 100

// gcc -lm -o test 5-2.c

int getch(void);
void ungetch(int);
int getfloat(float *);

char buf[BUFSIZE];
int bufp = 0;

int main(void){
    int fn;

    do {
        float f;

        fputs("Number:", stdout);
        fflush(stdout);
        fn = getfloat(&f);
        if (fn > 0) {
                printf("Result: %f\n", f);
        }
    } while (fn > 0);

    if (fn == EOF) {
        puts("EOF");
    } else {
        puts("Error, bad imput!");
    }
    
    return 0;
}

int getch(void){
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}


int getfloat(float *fp){
    int ch;
    int sign;
    int fraction;
    int digits;

    while (isspace(ch = getch()));

    if (!isdigit(ch) && ch != EOF && ch != '+' && ch != '-' && ch != '.' && ch != ','){
        ungetch(ch);
        return 0;
    }

    sign = (ch == '-') ? -1 : 1;
    if (ch == '+' || ch == '-') {
        ch = getch();
        if (!isdigit(ch) && ch != '.' && ch != ',') {
            if (ch == EOF)
                return EOF;
            else {
                ungetch(ch);
                return 0;
            }
        }
    }

    *fp = 0;
    fraction = 0;
    digits = 0;
    for ( ; isdigit(ch) || ch == '.' || ch == ',' ; ch = getch()){
        if (ch == '.' || ch ==',') {
            fraction = 1;
        } else {
            if (!fraction) {
                *fp = 10 * *fp + (ch - '0');
            } else {
                *fp = *fp + ((ch - '0') / pow(10, fraction));
                fraction++;
            }
            digits++;
        }
    }
    *fp *= sign;

    if (ch == EOF)
        return EOF;
    else {
        ungetch(ch);
        return (digits) ? ch : 0;
    }
}