#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLEN 1024

char *lineptr[MAXLINES];
int reverse = 0;

int mygetline(char [], int);
int readlines(char *[], int);
void writelines(char *[], int);
int pstrcmp(const void *, const void *);
int numcmp(const void *, const void *);

int main(int argc, char *argv[]){
    int nlines;
    int numeric = 0;
    int i;

    for (i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            switch (*(argv[i] + 1)) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                default:
                printf("bad argument '%s'\n", argv[i]);
                return 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, nlines, sizeof(*lineptr), numeric ? numcmp : pstrcmp);
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big\n");
        return 1;
    }
}


int mygetline(char s[], int lim){
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int readlines(char *lineptr[], int maxlines){
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
        return -1;
        else {
        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines){
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int pstrcmp(const void *p1, const void *p2){
    char * const *s1 = reverse ? p2 : p1;
    char * const *s2 = reverse ? p1 : p2;
    return strcmp(*s1, *s2);
}

int numcmp(const void *p1, const void *p2){
    char * const *s1 = reverse ? p2 : p1;
    char * const *s2 = reverse ? p1 : p2;
    double v1, v2;

    v1 = atof(*s1);
    v2 = atof(*s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)                                     
        return 1;      
    else
        return 0;
}