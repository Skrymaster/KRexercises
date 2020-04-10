#include <stdio.h>
#include <string.h>
#include <ctype.h>

int buf = EOF;

int getch(void);
void ungetch(int);

int main(void){
	char c;
	while((c = getch()) != EOF){
        if (isdigit(c)) {
            putchar(c);
            while(isdigit(c = getch())) {
                    putchar(c);
            }
            if (c != EOF) {
                ungetch(c);
            }
        }
        else{
            putchar(c);
        }
    }
	return 0;
}

int getch(void){
	int i;
    if (buf != EOF) {
        i = buf;
        buf = EOF;
    }
    else
        i = getchar();
    return i; 
}

void ungetch(int c){
    if(buf != EOF)
        printf("ungetch: too many characters\n");
    else       
        buf = c;
}
