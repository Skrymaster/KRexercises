#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(void)
{
	char s1[] =	"Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
			"sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
			"Ut enim ad minim veniam"
            "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat";
	char s2[] =	"abcdeABCDE";
	
	printf("%s\nDacă ştergem abcde ->\n", s1);
	squeeze(s1, s2);
	printf("%s\n", s1);
	
	return 0;
}

void squeeze(char s1[], char s2[])
{
	if (!s1[0] || !s2[0])
		return;

	char array[256], c;
	int i;
	int readindex;
	int writeindex;

	for (i = 0; i < 256; i++)
		array[i] = 0;
	
	i = 0;
	while (c = s2[i++])
		array[c] = 1;
	
	readindex = writeindex  = 0;
	while (s1[readindex])
	{
		if (array[s1[readindex++]])
			s1[writeindex] = s1[readindex];
		else
			s1[++writeindex] = s1[readindex];
	}
	
	s1[writeindex] = '\0';
}