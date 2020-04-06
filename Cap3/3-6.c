#include <stdio.h>
#include <limits.h>
#include <string.h>

void itoa(int n, char s[], int width);
void reverse(char s[]);

int main(void) {
    char buffer[20];
    itoa(123456, buffer, 8);
    printf("Buffer:%s\n", buffer);
    
    return 0;
}

void itoa(int n, char s[], int width) {
    int i, sign;
    
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    
    while (i < width )
        s[i++] = ' ';
    
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {

    int length = strlen(s);
    int c, i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}