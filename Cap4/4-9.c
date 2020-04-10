#include <stdio.h>
#include <string.h>

#define BUFSIZE 30

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int c);

int main(void){
    char c;
    ungetch(EOF);
    while ((c = getch()) != EOF) {
            putchar(c);
    };
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