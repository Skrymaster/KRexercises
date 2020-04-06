//pt că face overflow
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);
void itoa(int n, char s[]);

int main (void) {
    char s[128];
    itoa(INT_MIN, s);
    printf("%d => %s\n", INT_MIN, s);
    return 0;
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

void itoa(int n, char s[]) {

    int i, sign;
    unsigned int m; //folosesc unsigned int ca să evit problema, pun semnul separat
    i = 0;

    if ((sign = n) < 0) {
        m = -n;
    }
    else {
        m = n;
    }


    do {
        s[i++] = (m % 10) + '0';
    }
    while ((m /= 10) > 0);

    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';

    reverse(s);
}
