#include <stdio.h>

int main(void){
    printf("getchar() != EOF: %d\n", getchar() != EOF);
    return 0;
}
// notă: când tastez orice dă 1, dacă dau ctrl+d dă 0