#include <stdio.h>

#define SWAP(t,x,y) {t z=x;x=y;y=z;}

int main(void){
    // test 1 cu int
    // int x=20,y=30;
    // printf("x=%d    y=%d \n",x,y);
    // SWAP(int,x,y);
    // printf("x=%d    y=%d after swap macro \n",x,y);
    
    
    // test 2 cu float
    float x=20.2,y=13.4;
    printf("x=%f    y=%f \n",x,y);
    SWAP(float,x,y);
    printf("x=%f    y=%f after swap macro \n",x,y);
    return 0;
}