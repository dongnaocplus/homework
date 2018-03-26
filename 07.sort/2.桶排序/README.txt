桶排序设计思路请看bucket_sort.hpp
在编写桶排序程序时，特设计了有序链表工具list_util.hpp，可以快速形成有序的链表，没有使用std::list
也许以后在其它地方也可以使用list_util

1. bucket_sort支持比较大小仿函数参数，使用者可以使用greater或less进行升降序；
2. bucket_sort支持装桶计算仿函数参数，使用者可以自己设置投桶算子；


直接执行make,编译生成main执行文件