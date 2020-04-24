#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_NUM_LINES      10
#define MAX_LINE_LEN           256

int mygetline(char [], int);
char *strduplicate(const char *);

int main(int argc, char *argv[]){
    int num_lines = DEFAULT_NUM_LINES;
    char **line_ptrs;
    char buffer[MAX_LINE_LEN];
    int i;
    unsigned j, current_line;

    if (argc > 1) {
        num_lines = atoi(argv[1]);
        if (num_lines >= 0) {
            printf("argument should be [-n]\n");
            return 1;                                           
        }
    // aici dacă argumentul era -n, num_lines va fi negativ, inversez semnul
        num_lines = -num_lines;
    } 
    line_ptrs = malloc(sizeof *line_ptrs * num_lines);
    if (!line_ptrs) {
        printf("Cannot allocate line_ptrs\n");
        return 1;
    }
    for (i = 0; i < num_lines; i++)
        line_ptrs[i] = NULL;
    current_line = 0;

    do {
        mygetline(buffer, sizeof buffer);
        //https://www.tutorialspoint.com/c_standard_library/c_function_feof.htm
        // feof returns a non zero value if the End-of-File indicator associated with the stream is set, else zero is returned.
        if (!feof(stdin)) {
            if (line_ptrs[current_line]) {
                free(line_ptrs[current_line]);//era ceva deja aici, eliberez memoria
            }
            line_ptrs[current_line] = strduplicate(buffer);
            if (!line_ptrs[current_line]) {
                printf("Out of memory\n");
                return 1;
            }
            current_line = (current_line + 1) % num_lines;
        }
    } while (!feof(stdin));
    //output
    for (i = 0; i < num_lines; i++) {
        j = (current_line + i) % num_lines;
        if (line_ptrs[j]) {
            printf("%s", line_ptrs[j]);
            free(line_ptrs[j]);
        }
    }
    return 0;
}

int mygetline(char s[], int lim){
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

char *strduplicate(const char *s){
    char *p = malloc(strlen(s) + 1); 
    if (p)
        strcpy(p, s);
    return p;
}