#include <string.h>
#include <stdio.h>

int strend(char *, char *);

int main(void){
    char *s = "Test test testtest testul";
    char *t = "stul";

    if (strend(s, t)){
        printf("test reuşit \n");
    }
    else{
        printf("eşec \n");
    }
    return 0;
}

int strend(char *s, char *t){
    s += (strlen(s) - strlen(t)); //sar la punctul în s în care încep să fie stringurile comparate
    while (*s++ == *t++)
        if (*s == '\0')
            return 1;
    return 0;
}