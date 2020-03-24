#include <stdio.h>

unsigned char lowerrewrite(char);

int main(void){

    int i;
    char array[] = "AaBbCcDdZzYyXx1234";
    i = 0;
    puts(array);
    while(array[i] != '\0')
        putchar(lowerrewrite(array[i++]));

    putchar('\n');
}

unsigned char lowerrewrite(char x)
{
    if (x >= 'A' && x <= 'Z'){
        x = x - 'A' +'a';
    }
    return x;
}