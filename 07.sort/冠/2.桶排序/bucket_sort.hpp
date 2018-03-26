
#ifndef __DONGNAOEDU_BUCKET_SORT_H_
#define __DONGNAOEDU_BUCKET_SORT_H_

#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include "list_util.hpp"

using namespace std;

//定义一个除法仿函数，计算数据对应的桶子标识
template<class T>
struct division : public unary_function<T, int>
{
    int div;
    division(int d):div(d){};
    int operator()(const T& x) const
    {
        return (x/div);
    } 
};

//定义桶数据结构
template <typename T>
class _bucket : public _list_node<int>
{
public:
    _bucket():head(NULL){_list_node();}
    _list_node<T>* head;
};

//定义桶列表数据结构
template <typename T>
class _bucket_list
{
public:    
    _bucket_list():head(NULL){}
    _bucket<T>* head;
};

/***********************************************************************************************************
 *
 * 算法描述：桶排序
 *
 * 实现步骤：
 *          1. 把待排序的数据逐一装桶，数据通过deliver仿函数计算桶标识值key，通过标识值进行装桶；
 *             如果不存在桶标识值key则新建一个标识为key的桶。所有桶串起来是一个链表，并且是按key值有序排列
 *          2. 每个数据装桶时，可以在桶中直接进行插入排序，保证桶的数据是有序的；
 *          3. 重复步骤1~2；
 *          4. 当所有数据装好桶时，排序完成，从桶中取数据，放回a[]中。
 *
 ***********************************************************************************************************/
template <typename T, typename Deliver, typename Compare>
void bucket_sort(T a[], size_t size, Deliver deliver, Compare comp)
{
    //建立桶子列表 
    _bucket_list<T> BucketList;

    for(int i = 0; i < size; ++i)
    {
        //找桶
        _bucket<T>* bucket = list_require_node(BucketList.head, deliver(a[i]), comp);
         if(bucket != NULL)
         {
             //装桶
             list_fill_node(bucket->head, a[i], comp);
         }
    }
    
    T* p = a;  
    const _bucket<T>* bucket = BucketList.head;
    while(bucket != NULL)
    {
        //cout << bl->data << " ";
        const _list_node<T>* node = bucket->head;   
        while(node != NULL)
        {
            *(p++) = node->data;
            //cout << node->data << " ";
            node = node->next;
        }
        //cout << endl;
        list_clear((_list_node<T>*&)bucket->head);
        bucket = (_bucket<T>*)bucket->next;
    }

    list_clear((_list_node<T>*&)BucketList.head);

}

#endif
