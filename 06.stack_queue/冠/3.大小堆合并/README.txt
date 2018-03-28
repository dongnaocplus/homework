
小根堆方式的优先队列
定义
priority_queue<int,std::less<int>> pq_less(32);
    

大根堆方式的优先队列
定义  
priority_queue<int,std::greater<int>> pq_greater(32);

enqueue函数支持动态内存扩容