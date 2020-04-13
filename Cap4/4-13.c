#include <stdio.h>
#include <string.h>

int reverse(char[], int, int);

int main(void){
  char s[] = "Test test 123 testtest Test";
  reverse(s, 0, strlen(s)-1);
  printf("%s    \n", s);
  return 0;
}

int reverse(char y[], int index, int length){
    if(length < 2)//dacă nu se dă string sau e doar o literă, nu face nimic 
        return 1;
    int temp;
    if (length/2 < index)//dacă deja a parcurs jumate, se opreşte
        return 0;
    temp = y[index];
    y[index] = y[length - index];
    y[length - index] = temp;
    reverse(y, ++index, length);
}