设计思路请看count_sort_ex.hpp中

1. count_sort函数，不需要使用RANDMAX了；
2. count_sort函数，做了节省内存的优化；
3. count_sort函数，支持升降序；
4. count_sort函数不支持负数排序；
5. 另外设计了count_sort_ex函数，基于count_sort函数，而且支持负数排序。
