#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getline(char*, int);
char *alloc(int);
int readlines(char**, int);
void writelines(char**, int);
void quicksort(void**, int, int, int (*)(void*, void*));
int numcmp(char*, char*);
int mystrcmp(char*, char*);

#define MAXLINES 10000
#define MAXLEN 1000

char *lineptr[MAXLINES]; 
int decreasing = 0;     
int numeric = 0;       
int fold = 0;          
int directory = 0;  
	

int main(int argc, char* argv[])
{
	int nlines, i;
	
	while(--argc > 0) {
		++argv;
		if((*argv)[0] == '-')
			for(i = 1; (*argv)[i]; ++i)
				switch((*argv)[i]) {
					case 'n':
						numeric = 1;
						break;
					case 'f':
						fold = 1;
						break;
					case 'r':
						decreasing = 1;
						break;
					case 'd':
						directory = 1;
						break;
					default:
						printf("usage: sort -dfnr\n");
						return 1;
				}
		else {
			printf("usage: sort -dfnr\n");
			return 1;
		}
	}
	if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		if(numeric)
			quicksort((void**) lineptr, 0, nlines - 1,
		              (int (*)(void*, void*))numcmp);
		else
			quicksort((void**) lineptr, 0, nlines - 1,
		              (int (*)(void*, void*))mystrcmp);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("input too big to sort\n");
		return 1;
	}
}

void quicksort(void *v[], int left, int right, int (*comp)(void*, void*))
{
	int i, last;
	void swap(void *v[], int, int);
	
	if(left >= right)   
		return;       
	swap(v, left, (left + right) / 2); 
	last = left;
	for(i = left + 1; i <= right; ++i) {
		if(!decreasing) {               
			if((*comp)(v[i], v[left]) < 0)  
				swap(v, ++last, i);
		}
		else
			if((*comp)(v[i], v[left]) > 0)
				swap(v, ++last, i);
	}
	swap(v, left, last);   
	quicksort(v, left, last - 1, comp);
	quicksort(v, last + 1, right, comp); 
}


int mystrcmp(char *s1, char *s2)
{
	if(directory) {
		while(!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
			++s1;       
		while(!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
			++s2;       
	}
	while(fold ? (tolower(*s1) == tolower(*s2)) : (*s1 == *s2)) {
		if(*s1 == '\0')
			return 0;
		++s1;
		++s2;
		if(directory) {
			while(!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
				++s1;       
			while(!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
				++s2;       
		}
	}
	return fold ? (tolower(*s1) - tolower(*s2)) : (*s1 - *s2);
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;
	
	v1 = atof(s1);
	v2 = atof(s2);
	if(v1 < v2)
		return -1;
	else if(v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp;
	
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines = 0;
	char *p, line[MAXLEN];
	int longline = 0;
	
	while((len = getline(line, MAXLEN)) > 0) {
		if(nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			if(line[len - 1] == '\n') {
				line[len - 1] = '\0'; 
				strcpy(p, line);
				if(!longline)
					lineptr[nlines++] = p;
				else
					longline = 0;
			}
			else {
				strcpy(p, line);
				if(!longline) {
					lineptr[nlines++] = p;
					longline = 1;
				}
			}
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while(nlines-- > 0)
		printf("%s\n", *lineptr++);
	return;
}

int getline(char *s, int max)
{
	int c;
	char *ps = s;
	while(--max && (c=getchar()) != EOF && c != '\n')
		*s++ = c;
	if(c == '\n')
		*s++ = '\n';
	*s = '\0';
	return s - ps;
}

#define ALLOCSIZE 2000000

static char allocbuf[ALLOCSIZE];  
static char *allocp = allocbuf;   

char *alloc(int n)
{
	if(allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n;         
	}
	else           
		return 0;
}