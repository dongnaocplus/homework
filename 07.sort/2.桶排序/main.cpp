#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <functional>
#include "bucket_sort.hpp"
using namespace std;

class _my_node : public _list_node<int>
{
public:
    _my_node():_list_node(){};
};

int main(int argc,char* argv[])
{
    int nums[] = {-1,-2,-10,3,3,3,3,-1,-20,-4,-14,-7,0,1,3,10,-16,20,33,44,46,18,28};
    int len = sizeof(nums)/sizeof(int);

    bucket_sort(nums,len,division<int>(10),greater<int>()); 

    for(int i = 0; i < len; i++)
    {
        cout << nums[i] << " ";
    }
     cout << endl;

    return 0;
}
