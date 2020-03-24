#include <stdio.h>

int main(void){
    int c;

    while((c=getchar()) != EOF){

        if(c== '\\' || c=='\t' || c=='\b'){

            putchar('\\');// indiferent de caz, e nevoie de backslashuri
            if(c == '\\')
                putchar('\\');

            if(c=='\t')
                putchar('t');
                
            if(c=='\b')
                putchar('b');
        }
        else
            putchar(c);
        }
    return 0;
}