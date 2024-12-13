// main.c
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*add_func)(int, int);

int main() {
    void* handle;
    char* error;
    add_func add;

    // 动态加载库
    handle = dlopen("./libmathlib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    // 获取函数指针
    add = (add_func) dlsym(handle, "add");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    // 使用动态加载的函数
    int result = add(3, 5);
    printf("3 + 5 = %d\n", result);

    // 关闭库
    dlclose(handle);
    return 0;
}
