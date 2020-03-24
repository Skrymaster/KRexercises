#include <stdio.h>

#define MAX_STRING_LENGTH 256

int main(void){
	/* trebuie să înlocuiesc
	for (i = 0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;
	*/

	int i = 0, lim = MAX_STRING_LENGTH, c;
	char s[MAX_STRING_LENGTH];

	while (i < (lim - 1)){
		c = getchar();

		if (c == EOF)
			break;
		else if (c == '\n')
			break;
		s[i++] = c;
	}

	s[i] = '\0'; //sfârşitul "stringului"

	return 0;
}