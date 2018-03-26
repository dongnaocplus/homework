#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "count_sort_ex.hpp"

#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))

int main(int argc,char* argv[])
{
    int nums[] = {-1,-2,-10,-20,-4,-14,-7,0,1,3,10,-16};
    count_sort_ex<int>(nums,_countof(nums),false);

    for(unsigned int i = 0; i < _countof(nums); i++)
    {
        cout << nums[i] << " ";
    }

    cout << endl;

    return 0;
}
