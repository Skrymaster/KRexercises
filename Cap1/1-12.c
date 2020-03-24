#include <stdio.h>

int main(void){

    int c, old;
    // dacă încep cu spaţiu, tab sau newline, va fi un rând liber, pentru că old nu are valoarea lui c la prima buclă în if
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t'){
            if(old != c){
               putchar('\n');
    	    }
        }

        else{
            putchar(c);
        }
        old = c;
    }
    return 0;
}