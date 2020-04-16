#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5
#define MAXLEN   256

int readlinesnoalloc(char [][MAXLEN], int);
int mygetline(char[], int);


int main(void){
    char linestorage[MAXLINES][MAXLEN];
    readlinesnoalloc(linestorage, MAXLINES);
    for (int i=0; i<6; i++){
        printf("line %d: %s\n",i+1,linestorage[i]);
    }
    return 0;
}


int readlinesnoalloc(char lines[][MAXLEN], int maxlines){
  int len, numberlines;
  numberlines = 0;
  while ((len = mygetline(lines[numberlines], MAXLEN)) > 0)
    if (numberlines >= maxlines)                         
      return -1;           
    else
      lines[numberlines++][len - 1] = '\0';
  return numberlines;
}

// din carte
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