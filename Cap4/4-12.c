#include <stdio.h>
#include <stdlib.h>
#define MAXSTRING 1000

void itoarecursive(int, char[]);

// int main (void){
//     char s[32] = {0};
//     int n = -35612;
//     int m = 51234;
//     itoarecursive(n, s);
//     printf("%d    %s\n", n, s);
//     itoarecursive(m, s);
//     printf("%d    %s\n", m, s);
//     return 0
// }

void itoarecursive(int n, char s[]){
    static int r = 0;
    static int i;

    if (r == 0){//se execută doar prima dată, nu şi recursiv
        if (n < 0)
            r = -1;
        else
            r = 1;
        i = 0;//indice de recursie
    }
    if (n / 10)
        itoarecursive(n / 10, s);
    if (r != 0)//operaţia e din recursie
    {
        if (r < 0)
            s[i++] = '-';
        r = 0;
    }

    s[i++] = abs(n % 10) + '0';
    s[i] = '\0';
}