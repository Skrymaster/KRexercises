#include <stdio.h>
#include <limits.h>
// am găsit pe stack overflow existenţa unei librării limits.h
int main(void){
    printf("char bits: %d\n", CHAR_BIT);
    printf("max char value: %d\n", CHAR_MAX);
    printf("min char value: %d\n", CHAR_MIN);
    printf("max signed char value: %d\n", SCHAR_MAX);
    printf("min signed char value: %d\n", SCHAR_MIN);
    printf("max unsigned char value: %u\n", (unsigned) UCHAR_MAX);
    printf("max short value: %d\n", SHRT_MAX);
    printf("min short value: %d\n", SHRT_MIN);
    printf("max unsigned short value: %u\n", (unsigned) USHRT_MAX);
    printf("max int value: %d\n", INT_MAX);
    printf("min int value: %d\n", INT_MIN);
    printf("max unsigned int value: %u\n", UINT_MAX);
    printf("max long value: %ld\n", LONG_MAX);
    printf("min long value: %ld\n", LONG_MIN);
    printf("max unsigned long value: %lu\n", ULONG_MAX);

    return 0;
}