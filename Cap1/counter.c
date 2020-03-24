#include <stdio.h>
int main(void){
    int c;
    int space = 0;
    int tab = 0;
    int line = 0;

    while ( (c = getchar() ) != EOF ){
        if ( c == ' '  )
            ++space;
        if ( c == '\t' )
            ++tab;
        if ( c == '\n' )
            ++line;
    }

    printf("Spaces: %d, Tabs: %d, Lines: %d", space, tab, line);
}
// programul se opreşte în momentul în care apelez ctrl+d (eof)