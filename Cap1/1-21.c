#include <stdio.h>
// aici am folosit parametru simbolic
#define TAB 5

int main(void){
    int i = 0;
    int space = 0;
    char array[TAB+2];
    int c;

    while((c=getchar()) != EOF) {
        array[i++] = c;
        if(c == ' ')
            ++space;
        else
            space = 0;
        if(i == TAB || c == '\n') {
            array[i] = '\0';
            if(space > 1) {
                i -= space;
                array[i] = '\t';
                array[i+1] = '\0';
            }
            printf("%s", array);
            i = space = 0;
        }
    }
    if(i > 0) {
        array[i] = '\0';
        printf("%s", array);
    }
    return 0;
}