/***********************************************************************************************************
 *
 * 列表工具集
 *
 ***********************************************************************************************************/

#ifndef __DONGNAOEDU_LIST_UTIL_H_
#define __DONGNAOEDU_LIST_UTIL_H_

#include <iostream>
#include <stddef.h>
#include <stdlib.h> 
#include "list_util.hpp"
using namespace std;

//定义结点，使用本列表工具的结点都必须以_list_node为父类
template <typename _Td>
class _list_node
{
public:
    _list_node():next(NULL){}
    _Td data;
    _list_node<_Td>* next;
};

/**
 * 向列表插入数据，插入数据后列表保持有序
 * @arg head,列表头
 * @arg data,插入的数据
 * @arg comp,定义数据大小的仿函数
 * @return 返回插入的数据结点
 */

template <typename _Tn, typename _Td, typename _Compare>
inline _Tn* list_fill_node(_Tn*& head, _Td data, _Compare comp)
{
    _Tn* node = new _Tn();
    node->data = data;

    //把新的node先插入到列表的首元素中
    if(head == NULL)
    {
        head = node;
        return node;
    }
    else
    {
        node->next = head;
        head = node;
    }

    //从列表中选取node最佳的放置点，调整node位置，使列表变成有序表。
    _list_node<_Td>* prev = (_list_node<_Td>*)head;
    _list_node<_Td>* it = node->next; 
    while(it != NULL)
    {
        if(!comp(data,it->data))
        {
            node->next = it->next;
            it->next = node;
            if(node == head)
            {
                head = (_Tn*)it;
            }
            else
            {              
                prev->next = it;
            }
            prev = it;
        }
        else
        {
            break;
        }
        it = node->next;

    }

    return node;
}

/**
 * 向列表索要数据，如果列表中没有数据则，自动新建数据结点并插入，列表保持有序
 * 如果表中有此数据则返回，不予以添加。
 * @arg head,列表头
 * @arg data,插入的数据
 * @arg comp,定义数据大小的仿函数
 * @return 返回索要的数据结点
 */
template <typename _Tn, typename _Td, typename _Compare>
inline _Tn* list_require_node(_Tn*& head, _Td data, _Compare comp)
{
    _list_node<_Td>* it = (_list_node<_Td>*)head;
    while(it != NULL)
    {
        if(data == it->data)
        {
            return (_Tn*)it;
        }
        it = it->next;
    }

    return list_fill_node(head, data, comp);
}

/**
 * 打印列表
 * @arg head,列表头
 */
template <typename _Td>
void list_print(const _list_node<_Td>* head)
{
    const _list_node<_Td>* it = (const _list_node<_Td>*)head;  
    while(it != NULL)
    {
        cout << it->data << " ";
        it = it->next;
    }
}

/**
 * 清空列表
 * @arg head,列表头
 */
template <typename _Td>
void list_clear(_list_node<_Td>*& head)
{
    _list_node<_Td>* it = (_list_node<_Td>*)head; 
    _list_node<_Td>* _d = NULL; 
    while(it != NULL)
    {
        _d = it;
        it = it->next;
        delete _d;
    }
    head = NULL;
}

#endif
