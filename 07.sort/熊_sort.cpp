// sort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "common.h"

template <typename T> // ����һ�� T �������ͣ� �������� ���÷� ���͵ı仯���仯
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
template <typename T> // ����һ�� T �������ͣ� �������� ���÷� ���͵ı仯���仯
//�����㷨
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
	//����һ�������Ŵ�����a����Сֵ�����ֵ���ε�����һ������
	for (;iIndex < nLen;++iIndex)
	{
		counts[a[iIndex] + iTempMin]++;

	}
	//��counts�����ۼ�
	for (iIndex = 1; iIndex < size;++iIndex)
	{
		counts[iIndex] += counts[iIndex - 1];

	}
	for (iIndex = nLen - 1; iIndex >= 0; --iIndex)
	{  
		//��Ϊ�������ʼ�±�Ϊ0������Ҫ��һ  
		storteds[counts[a[iIndex] + iTempMin] - 1] = a[iIndex];

		//�����һ��Ϊ�˱�֤���ж��ֵΪa[index]��Ԫ��ʱ������ֵ�ֵΪa[index]��Ԫ��  
		//���ں��棬Ҳ����Ϊ�˱�֤������ȶ���  
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
//Ͱ����
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
//����ֻ�ٶ���Щ����Ϊ�����������Ϊ�����ɲο�����ļ����������
template <typename T>
void bucketSort(T a[],size_t nlen,int max)
{
	if (a==NULL || nlen <1 || max<1)
		return ;

	int i = 0;
	int j = 0;
	//����һ����СΪmax��Ͱ
	T* bucket = (T*)calloc(max,sizeof(T));
	memset(bucket, 0, max*sizeof(T));

	//���м�������һ����Ŀ���ǽ�a�����ݷŵ�0-max-1��Ͱ�У����п�����ЩͰ����ж�����ݼ���bucket[a[i]]�п��ܲ�ֹΪ1
	for (i = 0 ; i < nlen;++i)
	{
		bucket[a[i]]++;
	}
	//��������ȡ��
	for (i = 0,j = 0;i < max;++i)
	{
		//��bucket[i]����0��ʱ��Ҳ������ζ��bucket�±�������������Ӧ��ֵ�����ظ���ʱ�򣬾�ȡ����±��ֵ��������ӡ�������Ƕ�Ӧ������ʽ
		while(bucket[i]-- > 0)
		{
			a[j++] = i;
		}
	}
	free(bucket);
}

//��������
//����Ҫ������������λ��������������Ĵ���
template <typename T>
void maxBit(T a[],size_t len,int& maxbit)
{
	if (a == NULL || len < 1)
	{
		return;
	}
	//��һ��ѭ����������Ӧ�����λ��
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
//���������㷨
template <typename T>
void radixsort(T a[],size_t len)
{
	int maxbit = 0;
	maxBit(a,len,maxbit);
	T* counts = (T *)calloc(len,sizeof(T));
	//����һ�����������洢������,count[0],count[1]...�ֱ��ʾ��λ��Ϊ1��2��3�ĸ�������ʮλ���ֱ�Ϊ1��2��3�ĸ�������������
	int count[10] = {0};
	//����maxbitѭ��
	int radix = 1;
	int j = 0;
	int k = 0;
	for (int i = 0 ; i <= maxbit;++i)
	{
		// ÿ��ѭ����Ҫ����Ӧ�ļ����������
		for (j = 0 ; j < 10;++j)
		{
			count[j] = 0;
		}
		//��һ����������10��100��1000��ȡģ����������Ӧ�����ü�������ͳ�Ƹ���,�õ��Ľ������a[0] = 1,a[2] = 3�ȵȣ���ζ�ŵ�һ�ε�ʱ�򣬸�λ��Ϊ0����1������λ��Ϊ2����2��
		for (j = 0;j < len;++j)
		{
			k = (a[j] / radix)%10; 
			count[k]++;
		}
		//�Զ�Ӧ�����ݽ����ۼӣ�Ŀ�ľ��ǻ�ȡ���֮���ֵ�Ǹ�������a[]�е��±�������
		for (j = 1;j < 10;++j)
		{ 
			count[j] += count[j - 1];
		}
		//�����µ�����,
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
	//bucketSort(a,10,imax);//����max+1��Ϊ���ü����������0��ʼ�㹻��  

	radixsort(a,10);
	for (int i = 0; i < 10; ++i)  
	{  
		printf("%d\n",a[i]);  
	}  

	return 0;
}

