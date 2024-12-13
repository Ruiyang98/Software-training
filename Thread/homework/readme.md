# 一.进程监控系统process_monitor

test_process.sh是一个循环输出running的测试脚本，可以作为被监视的程序。

测试方法：  
1、首先运行监控程序，启动并监控测试脚本：./process_monitor ./test_process.sh，可以看到终端持续输出Running...  
2、启动另一个终端，查看脚本进程的进程号：ps aux | grep test_process.sh  
3、手动终止测试脚本，模拟进程崩溃：kill 脚本进程号  
4、日志文件 process_monitor.log 中查看记录每次重启的时间和次数  

# 二.实时任务调度系统task_scheduler

测试方法： 
1、启动实时任务调度系统，会创建三个不同优先级的任务，然后优先执行高优先级的任务：./task_scheduler  
2、task_scheduler.log日志输出任务的执行情况，包括任务开始和结束时间  
3、可以修改task_scheduler函数中sleep的时间，测试不同时间片对任务运行的影响。  


# 三.资源隔离与安全性机制resource_isolation

测试方法：  
1、启动程序./resource_isolation，程序会创建5个进程读取各自能读取的资源，然后会创建一个接收通信的进程  
2、不同的进程读取到资源后，将结果打印到日志中，然后将读取结果发送到接收通信的进程，该进程收到后记录消息内容。  
3、查看resource_access.log日志中的内容。  