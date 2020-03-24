#include <stdio.h>

#define MAXLENGTH 20

int main(void){

    int c = EOF;
    int i = 0;
    int j = 0;
    int array[MAXLENGTH + 1];
    int stare = 1;
    int count = 0;
    
    for(i = 0; i <= MAXLENGTH; ++i) //iniţializare matrice
        array[i] = 0;

    while((c = getchar()) != EOF){
        ++count;

        if(c == ' ' || c == '\t' || c == '\n'){
            stare = 0; //în momentul în care găsim un separator de cuvânt, nu-l considerăm drept caracter(--count) şi pregătim înregistrarea lui în matrice
            --count;
        }

        if(stare == 0){
            if(count != 0 && count <= MAXLENGTH)
                ++array[count]; //se incrementează contorul pentru cuvintele cu numărul "count" de caractere

            stare = 1;
            count = 0;
        }
    }

    for(i=1; i <= MAXLENGTH; ++i){
        printf("%2d- ", i);
        for(j = 0; j < array[i]; ++j)
        putchar('#');

        putchar('\n');
    }

    return 0;
}