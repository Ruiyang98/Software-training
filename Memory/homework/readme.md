# 一、内存池的设计与实现
memory_pool_linear是一个线性的内存池，只能实现统一销毁，不能回收  
链表实现的内存池，可以分配和回收，运行`./memory_pool_linklist`


# 二、内存泄漏检测
  
1、使用valgrind启动模拟内存泄漏的代码并进行检测：`valgrind --leak-check=full --log-file="valgrind.log" ./leak_memory`   
2、查看日志中valgrind的输出。  


# 三、内存优化与调试
  
1、使用valgrind启动模拟内存泄漏的代码并进行检测：`valgrind --leak-check=full --log-file="valgrind.log" ./memory_optimization_test`，发现有内存泄漏和内存碎片问题。  
2、优化代码方法：内存泄漏的部分释放相关未释放的内存，并使用内存池管理，减少内部内存碎片问题，最后使用tcmalloc编译`gcc -o memory_optimization memory_optimization.c -g -ltcmalloc`，减少外部碎片问题。  
3、测试代码：`valgrind --leak-check=full --log-file="valgrind.log" ./memory_optimization`
  
或者  
1、编译时，使用`gcc -o memory_optimization_test memory_optimization_test.c -fsanitize=address -g`  
2、然后启动`./memory_optimization`时，可以看到内存泄露  
3、编译优化后的代码`gcc -o memory_optimization memory_optimization.c memory_pool_linear.c -fsanitize=address -g`，运行后发现没有内存泄漏
