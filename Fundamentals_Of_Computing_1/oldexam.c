#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(void){
   char x[] = "cse";
   printf("1. a.) %d bytes\n"
          "   b.) %d bytes\n"
          "   c.) %d\n", sizeof("cse"), sizeof(x), strlen(x));
    return 0;
}