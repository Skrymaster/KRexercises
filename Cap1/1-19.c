#include <stdio.h>

#define MAXLEN 256

int getlineandlength(char current_line[], int len_current_line);
void cpreverse(char line[], char reverse_line[], int len_line);

int main(void){
    int len;
    char ln[MAXLEN];
    char ln_reverse[MAXLEN];

    len = 0;
    while ((len = getlineandlength(ln, MAXLEN)) > 0){
        cpreverse(ln, ln_reverse, len);
    }
    printf("%s\n", ln_reverse);
}

int getlineandlength(char _current_line[], int _len_current_line){

    int i, c;

    for (i = 0; i < MAXLEN -1 && (c = getchar()) != EOF && c != '\n'; ++i)
        _current_line[i] = c;

    if (c == '\n')
        _current_line[i] = '\0';
        
    return i;
}

void cpreverse(char _line[], char _reverse_line[], int _len_line){

    int i, j;
    j = 0;

    for (i = _len_line - 1; i >= 0 && i < MAXLEN - 1; --i){
        _reverse_line[j] = _line[i];
        ++j;
    }
}