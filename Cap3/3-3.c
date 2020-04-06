#include <stdio.h>
#include <ctype.h>

int expand(char s1[], char s2[]);
int isrange(char c1, char c2);

int main(void) {

	char s1[] = "-a a- a-a -a-z - -- -i- a-f\nA-Z\n0-9\nf-a\nz-a\n9-0";
	char s2[500];
	int size;

	size = expand(s1, s2);
	printf("Original string: %s\n",s1);
    printf("Expanded string: %s\n",s2);
    printf("Expanded strlen: %d char\n", size);
	return 0;
}

int expand(char s1[], char s2[]) {
	int i, j, order;
	char c, start, end;

	i = j = 0;
	
	while (c = s1[i]) {
		if (c == '-' && i && (start = s1[i-1]) && (end = s1[i+1]) && (order = isrange(start, end)))	{
			if (order == 1)
				for (c = start + 1; c <= end; ++c)
					s2[j++] = c;
			else
				for (c = start - 1; c >= end; --c)
					s2[j++] = c;
			++i;
		}
		else
			s2[j++] = c;
		++i;
	}
	s2[j] = '\0';
	return j;
}

// verific dacă aparţine alfanumeric
int isrange(char c1, char c2) {
	if ((isdigit(c1) && isdigit(c2)) || (islower(c1) && islower(c2)) || (isupper(c1) && isupper(c2)))
		return c1 > c2 ? -1 : 1;

	return 0;
}