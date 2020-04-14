#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

char *mystrncpy(char *s, const char *t, int n);
char *mystrncat(char *s, const char *t, int n);
int mystrncmp(const char *s, const char *t, int n);

int main(void)
{
	char s[BUFSIZE] = "tello world";
	char *t = "test";
    int n = 4;
    printf("original string: %s\n", s);

	mystrncpy(s, t, 4);
	printf("after mystrncpy: %s\n", s);

	mystrncat(s, t, 3);
	printf("after mystrncat: %s\n", s);

	printf("mystrncmp test : Strings start with %d letters identical out of %d checked\n", mystrncmp(s, t, n), n);

	return 0;
}

char *mystrncpy(char *s, const char *t, int n){
	int i;
	for (i = 0; i < n; i++)
		*(s + i) = *(t + i);
    if (strlen(s) < strlen(t))
        *(s + i) ='\0';
	return s;
}

char *mystrncat(char *s, const char *t, int n){
	int i;
    s += strlen(s);
	for (i = 0; i < n && *(t + i); i++)
		*(s + i) = *(t + i);
	*(s + i) = '\0';
	return s;
}

int mystrncmp(const char *s, const char *t, int n){
	int i;
	for (i = 0; i < n && *(s + i) == *(t + i) && *(s + i) && *(t + i); i++);
    return i;
}