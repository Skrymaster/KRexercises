#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itob(int n, char s[], int b);

int main(void) {

    char buffer[10];
    int i;
    
    for ( i = 2; i <= 16; ++i ) {
        itob(256, buffer, i);
        printf("base %d : %s\n", i, buffer);
    }
    return 0;
}

void itob(int n, char s[], int b) {
    static char digits[] = "0123456789ABCDEF";
    int i, sign;
    
    if ( b < 2 || b > 16 ) {
        fprintf(stderr, "Unusual base %d\n", b);
        exit(1);
    }
    
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = digits[n % b];
    } while ((n /= b) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}