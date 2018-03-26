// sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "common.h"

template <typename T> // 声明一个 T 数据类型， 此类型随 调用方 类型的变化而变化
void max_minArry(T a[],size_t nlen,int& iMax,int& iMin)
{
	if (a==NULL || nlen<1)
		return ;

	iMax = a[0];
	iMin = a[0];

	for (int i = 1 ; i < nlen;++i)
	{
		if (a[i] > iMax)
		{
			iMax = a[i];
		}
		if (a[i] < iMin)
		{
			iMin = a[i];
		}
	}
}
template <typename T> // 声明一个 T 数据类型， 此类型随 调用方 类型的变化而变化
//计数算法
void countsort(T a[],int nLen)
{
	if (a==NULL || nLen<1)
		return ;
	int iMax = 0;
	int iMin = 0;
	max_minArry(a,nLen,iMax,iMin);
	
	int iTempMin = 0;
	int size = 0;
	if (iMin <= 0)
	{
		iTempMin = abs(iMin);
		size = iMax - iMin + 1;
	}
	else
	{
		size = iMax + 1;
	}

	T* counts = (T *)calloc(size,sizeof(T));
	T *storteds = (T *) calloc(nLen, sizeof(T));

	int iIndex = 0;
	//构建一个数组存放从数组a中最小值到最大值依次递增的一个数组
	for (;iIndex < nLen;++iIndex)
	{
		counts[a[iIndex] + iTempMin]++;

	}
	//对counts进行累加
	for (iIndex = 1; iIndex < size;++iIndex)
	{
		counts[iIndex] += counts[iIndex - 1];

	}
	for (iIndex = nLen - 1; iIndex >= 0; --iIndex)
	{  
		//因为数组的起始下标为0，所以要减一  
		storteds[counts[a[iIndex] + iTempMin] - 1] = a[iIndex];

		//这里减一是为了保证当有多个值为a[index]的元素时，后出现的值为a[index]的元素  
		//放在后面，也就是为了保证排序的稳定性  
		if (iMin > 0)
		{
			--counts[a[iIndex]];
		}	
		else
		{
			--counts[a[iIndex]  + iTempMin];
		}
	}
	memcpy(a, storteds, size * sizeof(int));  
	free(storteds);  
	free(counts);
}
//---------------------------------------------------------------
//桶排序
//---------------------------------------------------------------
template <typename T>
void maxArray(T a[],int &iMax,int nlen)
{
	iMax = a[0];
	for (int i = 1 ; i < nlen;++i)
	{
		if (a[i] > iMax)
		{
			iMax = a[i];
		}
	}
	iMax += 1;
}
//这里只假定这些数据为正整数，如果为负数可参考上面的计数排序进行
template <typename T>
void bucketSort(T a[],size_t nlen,int max)
{
	if (a==NULL || nlen <1 || max<1)
		return ;

	int i = 0;
	int j = 0;
	//创建一个大小为max的桶
	T* bucket = (T*)calloc(max,sizeof(T));
	memset(bucket, 0, max*sizeof(T));

	//进行计数，这一步的目的是将a的数据放到0-max-1的桶中，其中可能有些桶里会有多个数据即，bucket[a[i]]有可能不止为1
	for (i = 0 ; i < nlen;++i)
	{
		bucket[a[i]]++;
	}
	//将数据提取，
	for (i = 0,j = 0;i < max;++i)
	{
		//当bucket[i]大于0的时候，也就是意味着bucket下标就是数组里面对应的值，有重复的时候，就取多次下标的值，这样打印出来就是对应的排序方式
		while(bucket[i]-- > 0)
		{
			a[j++] = i;
		}
	}
	free(bucket);
}

//基数排序
//首先要求数组中最大的位数，来决定排序的次数
template <typename T>
void maxBit(T a[],size_t len,int& maxbit)
{
	if (a == NULL || len < 1)
	{
		return;
	}
	//用一次循环来决定对应的最大位数
	maxbit = 1;
	int tmp = 10;
	for (int i = 0;i < len;++i)
	{
		while(a[i] >= tmp)
		{
			tmp *= 10;
			++maxbit;
		}
	}
}
//基数排序算法
template <typename T>
void radixsort(T a[],size_t len)
{
	int maxbit = 0;
	maxBit(a,len,maxbit);
	T* counts = (T *)calloc(len,sizeof(T));
	//定义一个数组用来存储计数器,count[0],count[1]...分别表示个位数为1，2，3的个数，及十位数分别为1，2，3的个数。。。。。
	int count[10] = {0};
	//进行maxbit循环
	int radix = 1;
	int j = 0;
	int k = 0;
	for (int i = 0 ; i <= maxbit;++i)
	{
		// 每次循环都要将对应的计数器给清空
		for (j = 0 ; j < 10;++j)
		{
			count[j] = 0;
		}
		//这一步就是来对10，100，1000等取模，用来将对应的数用计数器来统计个数,得到的结果就是a[0] = 1,a[2] = 3等等，意味着第一次的时候，个位数为0的有1个，个位数为2的有2个
		for (j = 0;j < len;++j)
		{
			k = (a[j] / radix)%10; 
			count[k]++;
		}
		//对对应的数据进行累加，目的就是获取组合之后的值是该数据在a[]中的下标索引。
		for (j = 1;j < 10;++j)
		{ 
			count[j] += count[j - 1];
		}
		//调整新的数据,
		for (j = len - 1;j >= 0 ;--j)
		{
			k = (a[j] / radix)%10; 
			counts[count[k] - 1] = a[j];
			count[k]--;
		}
		for(j = 0; j < len; j++) 
			a[j] = counts[j]; 
		radix = radix * 10;  
	} 
}

int main(int argc, char* argv[])
{
	int a[10] = {29,25,1,24,5,2,56,59,5,2};  
	
	int imax = 0;
	//maxArray(a,imax,10);
	//bucketSort(a,10,imax);//传入max+1是为了让计数的数组从0开始足够大  

	radixsort(a,10);
	for (int i = 0; i < 10; ++i)  
	{  
		printf("%d\n",a[i]);  
	}  

	return 0;
}

