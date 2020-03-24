#include <stdio.h>

int main(void){

    int c, old;
    old = EOF;

    while ((c = getchar()) != EOF) {
        if (c == ' ') //verific dacă c e spaţiu, dacă şi caracterul precedent tot era spaţiu
            if (old != c)
                putchar(c);

        if (c != ' ')
            putchar(c);

        old = c;
    }
    return 0;
}