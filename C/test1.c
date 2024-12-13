#include <stdio.h>


int main() {
    int val_1 = 10;
    int *p = &val_1;

    (*p)++;
    printf("%d\n",val_1);
    printf("%p\n",p);

    *p++;
    printf("%d\n",val_1);
    printf("%d\n",*p); //打印指向的值
    printf("%p\n",p);

    p++;
    printf("%d\n",val_1);

    return 0;
}