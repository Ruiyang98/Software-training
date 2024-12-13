#include <stdio.h>
#include "../include/Linklist.h"
//#include "Linklist.h"

int main() {
    // helloworld
    printf("helloworld");

    int value = 1;
    add(&value);
    //float f = 1.1;
    //add(&f);
    int value2 = 2;
    add(&value2);
    printlist();

    return 0;
}