#include <stdio.h>

int main(void){

    int x, y, a, b, c;
    
    x = 13 / 4 + 17 / 7 - (12 % 8) + (13 - 3 * 4) + (2 / 4 * 2); 
    y = 10 + 13 / 4 * 2;
    a = 7;    
    b = 6 + a--;    
    c = b++ + --a;
    
    printf("x = %d\n"
       "a = %d\n"
       "b = %d\n"
       "c = %d\n", x, a, b, c);
}

