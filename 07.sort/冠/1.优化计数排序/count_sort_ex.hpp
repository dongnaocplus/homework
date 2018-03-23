
#ifndef __DONGNAOEDU_COUNT_SORT_EX_H_
#define __DONGNAOEDU_COUNT_SORT_EX_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************************************************
 *
 * 算法描述：计数排序(Counting sort)是一种稳定的排序算法。计数排序使用一个额外的数组C，其中第i个元素是待排序
 *           数组A中值等于i的元素的个数。然后根据数组C来将A中的元素排到正确的位置。它只能对整数进行排序。
 *           它是最快的排序算法，但是因为其对所排序的元素必须要是整数，所以限制了其的应用
 *           count_sort不允许出现负数的待排序数，如果需要排序包含负数的数据请使用count_sort_ex
 *
 * 实现步骤：       
 *         1. 找出待排序的数组中最大和最小的元素；(Lee哥在这里偷懒了，直接使用了RANDMAX，表示排序的元素是0~RANDMAX)
 *         2. 统计数组中每个值为i的元素出现的次数，存入数组C的第i项；
 *         3. 对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）；这个累加就是让C[i]计数了有多少个元素
 *            少于或者等于i的元素，方便了反向输出元素时找到元素存放在数组a中的下标。
 *         4. 反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1。
 *
 * 时间复杂度：
 *           线性时间，region = a的最大值 - a的最小值 + 1
 *           最优情况：T(n) = O(n + region)
 *           最差情况：T(n) = O(n + region)
 *           平均情况：T(n) = O(n + region)
 *
 * 缺点： 1. 元素不能是负数；
 *       2. 额外申请了内存，如果元素值很大，怎么办？（已解决，另外不需要使用RANDMAX了）
 *
 ***********************************************************************************************************/

template <typename T>
void count_sort(T a[], size_t size, bool asc = true)
{
	//用于存放已经有序的数列
    T *storteds = (T *) calloc(size, sizeof(T));

    //找出数组中最大与最小的数，通过最大与最小值可以知道区间长度
    int max = a[0];
    int min = a[0];
    int index = 0; 
    for (index = 0; index < size; ++index) 
	{  
        if(a[index] < 0) 
        {
            //count_sort不允许出现负数的待排序数
            return;
        }
        if(a[index] > max)
        {
            max = a[index];
        }
        
        if(a[index] < min)
        {
            min = a[index];
        }
    }  

    int region = max - min + 1;

    //原来申请RANDMAX*sizeof(T)字节内存，现在只要申请region*sizeof(T)字节内存即可。因为region<=RANDMAX，所以还是很有机会可以节省内存
    //T *counts = (T *) calloc(RANDMAX, sizeof(T)); 
    T *counts = (T *) calloc(region, sizeof(T));
    memset(counts,0,region * sizeof(T));
  
    //统计数组a中各个不同数出现的次数，循环结束后counts[i]表示数值i在a中出现的次数 
    for (index = 0; index < size; ++index) 
	{ 
        counts[a[index] - min]++;
    }  
  
    //统计数值比index小的数的个数，升序的情况下，循环结束之后counts[i]表示a中小于等于数值i的元素个数  
    //而在降序的情况下，循环结束之后counts[i]表示a中大于等于数值i的元素个数  
    if(asc)
    {
        for (index = 1; index < region; ++index) 
        {  
            counts[index] += counts[index - 1];  
        }
    }
    else
    {
        for (index = region - 2 ; index >= 0; --index) 
        {  
            counts[index] += counts[index + 1];  
        }
    }

    for (index = size - 1; index >= 0; --index)
	{  
        //因为数组的起始下标为0，所以要减一  
        storteds[counts[a[index] - min] - 1] = a[index];
		
        //这里减一是为了保证当有多个值为a[index]的元素时，后出现的值为a[index]的元素  
        //放在后面，也就是为了保证排序的稳定性  
        --counts[a[index] - min];  
    }
  
    memcpy(a, storteds, size * sizeof(int));  
    free(storteds);  
    free(counts);
}

/***********************************************************************************************************
 *
 * 算法描述：count_sort_ex是count_sort计数排序的优化版，解决元素不能是负数问题，减少内存开销。性能上与count_sort相当。
 *         不需要使用RANDMAX。
 * 
 *
 * 实现步骤：       
 *         1. 正负数据分两组，记录正负数的边界位置，把负数正数化。
 *         2. 两组数据分别排序。
 *         3. 把被正数化的负数，还原回负数。
 *
 * 时间复杂度：
 *           线性时间，region = a的最大值 - a的最小值 + 1
 *           最优情况：T(n) = O(n + region)
 *           最差情况：T(n) = O(n + region)
 *           平均情况：T(n) = O(n + region)
 *
 *
 ***********************************************************************************************************/
template <typename T>
void count_sort_ex(T a[], size_t size, bool asc = true)
{
    //对a进行预处理，需要升序时，把a的全部负数靠左，正数靠右。记录正负数的边界位置minuspos，然后负数取正; 
    //需要降序时，把a的全部正数靠左，负数靠右。记录正负数的边界位置minuspos，然后负数取正; 
    int index = 0, minuspos;
    bool have_minus = false;
    if(asc)
    {
        minuspos = 0;
        for(index = 0 ; index < size; ++index)
        {
            if(a[index] < 0)
            {
                int temp = a[index];
                a[index] = a[minuspos];
                a[minuspos] = -temp;
                minuspos++;
                have_minus = true;
            }
        }
    }
    else
    {
        minuspos = size - 1;
        for(index = size - 1 ; index >=0 ; --index)
        {
            if(a[index] < 0)
            {
                int temp = a[index];
                a[index] = a[minuspos];
                a[minuspos] = -temp;
                minuspos--;
                have_minus = true;
            }
        }
    }

    if(!have_minus)
    {
        //没有负数的情况下直接调用count_sort即可
        count_sort(a,size,asc);
    }
    else
    {
        //有负数的情况
        if(asc)
        {
            //以minuspos为分界，负数部分降序序排列，正数部分升序排列
            count_sort(a,minuspos,false);
            count_sort(a + minuspos,size - minuspos,true);
            //负数还原本来面貌
            for(index = 0 ; index < minuspos; ++index)
            {
                a[index] = -a[index];
            }
        }
        else
        {
            //以minuspos为分，正数部分降序排列,负数部分升序序排列
            count_sort(a,minuspos,false);
            count_sort(a + minuspos + 1,size - minuspos - 1,true);
            //负数还原本来面貌
            for(index = minuspos ; index < size; ++index)
            {
                a[index] = -a[index];
            }
        }
    }

}

#endif
