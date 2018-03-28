#include "priority_queue.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    int a[] = {2,5,3,100,105,88,77,99,95};
    int len = sizeof(a)/sizeof(int);

    //小根堆方式的优先队列
    priority_queue<int,std::less<int>> pq_less(32);
    //大根堆方式的优先队列
    priority_queue<int,std::greater<int>> pq_greater(32);
    
    for(int i = 0; i < len; i++)
    {
        pq_less.enqueue(a[i]);
        pq_greater.enqueue(a[i]);
    }

    std::cout << "smaller root heap:" << std::endl;
    pq_less.print();
    std::cout << "larger root heap:" << std::endl;
    pq_greater.print();

    std::cout << "smaller root dequeue:" << std::endl;
    while(!pq_less.empty())
    {
        int value = 0;
        pq_less.dequeue(value);
        std::cout << "dequeue -> " << value << std::endl;
    }

    std::cout << "larger root dequeue:" << std::endl;
    while(!pq_greater.empty())
    {
        int value = 0;
        pq_greater.dequeue(value);
        std::cout << "dequeue -> " << value << std::endl;
    }

    return 0;
}
