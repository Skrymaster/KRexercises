#include <stdio.h>
#define ASCII 127

int main(void){
    int c;
    int chararray[ASCII];
    int frecventa[ASCII];
    int i, j;
        
    for(i = 0; i < ASCII; ++i){
        frecventa[i] = 0;
        chararray[i] = i;
    }
    i = 0;

    while((c = getchar()) != EOF){
        if(c != ' ' && c != '\t' && c != '\n'){
            ++i;
            for(j = 0; j < ASCII; ++j){
                if(chararray[j] == c){
                    ++frecventa[j];
                }
            }
            j = 0;
        }
    }
    j = 0;
    i = 0;
    for(j; j < ASCII; ++j){
        if(frecventa[j] != 0){
        printf("%c: ",chararray[j]);
        for(i = 0; i < frecventa[j]; ++i){
            putchar('#');
        }
        putchar('\n');
        }
    }
}