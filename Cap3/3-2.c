#include <stdio.h>

void escape(char * s, char * t);
void unescape(char * s, char * t);

int main(void) {
    char text1[100] = "\aTest\t testtest test test\n test\b\"test testtest\"";
    char text2[100];
    
    printf("Input String: %s\n", text1);
    escape(text2, text1);
    printf("Escape: %s\n", text2);
    unescape(text1, text2);
    printf("Unescape: %s\n", text1);
    return 0;
}

void escape(char * s, char * t) {
    int i, j;
    i = j = 0;
    
    while ( t[i] ) {
        switch( t[i] ) {
        case '\a':
            s[j++] = '\\';
            s[j] = 'a';
            break;
        case '\t':
            s[j++] = '\\';
            s[j] = 't';
            break;
        case '\n':
            s[j++] = '\\';
            s[j] = 'n';
            break;
        case '\b':
            s[j++] = '\\';
            s[j] = 'b';
            break;
        case '\\':
            s[j++] = '\\';
            s[j] = '\\';
            break;
        case '\"':
            s[j++] = '\\';
            s[j] = '\"';
            break;
        default:
            s[j] = t[i];
            break;
        }
        ++i;
        ++j;
    }
    s[j] = t[i];
}

void unescape(char * s, char * t) {
    int i, j;
    i = j = 0;
    
    while ( t[i] ) {
        switch ( t[i] ) {
        case '\\':
            switch( t[++i] ) {
            case 'a':
                s[j] = '\a';
                break;
            case 't':
                s[j] = '\t';
                break;
            case 'n':
                s[j] = '\n';
                break;
            case 'b':
                s[j] = '\b';
                break;
            case '\\':
                s[j] = '\\';
                break;
            case '\"':
                s[j] = '\"';
                break;
            default:
                s[j++] = '\\';
                s[j] = t[i];
            }
            break;
        default:
            s[j] = t[i];
        }
        ++i;
        ++j;
    }
    s[j] = t[i];
}