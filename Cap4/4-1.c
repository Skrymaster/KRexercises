#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]);

int main(void) {

    int i;
	char s1[] = "Test test ab test test ccabca bat";
	char s2[] = "ab";
        i = strrindex(s1, s2);
        printf("%d\n",i);
        return 0;
}

int strrindex(char s[], char t[]) {

	int i, j, k, l = -1;
    for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
        ;
		if (k > 0 && t[k] == '\0')
			l = i;
	}

    return l;
}