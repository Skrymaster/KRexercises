#include <stdio.h>
#define BUFSIZE 100

void mystrcat(char *, char *);

int main(void){
    char s[BUFSIZE] = "Test test";
    char t[BUFSIZE] = " testtest Test";

    mystrcat(s, t);
    printf("%s\n", s);
}

void mystrcat(char *s, char *t){
    for (int i = 0; i <= BUFSIZE && *s != '\0'; i++, s++);

    for (int j = 0 ;j <= BUFSIZE && *t != '\0'; j++, t++, s++)
        *s = *t;
}