#include <stdio.h>
 
int main() {
    int x = 100;
    int *p = &x;
    int c = 11;
    int *d= &c;
    int *q = 10;

    printf("Pointer size: %lu\n", sizeof(p)); 
    printf("Value: %d\n", *p);  
    printf("chh\n");  
    printf("Value: %d\n", *q);
    printf("ch\n");  
    printf("Value: %d\n", *d);  
    printf("check\n");
    return 0;
}