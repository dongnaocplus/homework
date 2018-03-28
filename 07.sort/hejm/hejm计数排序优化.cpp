#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_CNT 10
#define MAX_VALUE     100

// 缺点解决方式：
// 1. 负数问题：计算对应数的桶号时取绝对值，放进绝对值桶，桶分别标识正数的个数以及负数的个数，计算完后做一次遍历即可。
// 2. 空间问题：计算出数组中元素绝对值中的最小值以及最大值，分配空间为 space = 最大值 - 最小值，当放桶时取偏移桶号即可。

struct BUCKET_STATUS {
	int a0;	// 整数标识
	int a1;	// 负数标识
};

int main()
{
	int nRs;
	int nMin = -1;
	int nMax = -1;
	int nBucketCnt = -1;
	int nZNumber = 0;
	int nFNumber = 0;
	int nArray[MAX_ARRAY_CNT];
	BUCKET_STATUS *pArray;
	bool bFirst = false;

	srand(time(NULL));

	printf("随机数生成如下：\n");

	for (int i = 0; i < sizeof(nArray) / sizeof(int); i++) {

		int nSign = (0 == (rand() % 2) ? 1 : -1);

		nArray[i] = nSign * (rand() % MAX_VALUE);
	}

/*
	nArray[0] = 7;	
	nArray[1] = -36;	
	nArray[2] = -97;	
	nArray[3] = -77;	
	nArray[4] = -16;	
	nArray[5] = -31;	
	nArray[6] = 23;	
	nArray[7] = 0;	
	nArray[8] = -75;	
	nArray[9] = 12;	
*/
	for (int i = 0; i < sizeof(nArray) / sizeof(int); i++)
		printf("%d ", nArray[i]);

	printf("\n");

	for (int i = 0; i < sizeof(nArray) / sizeof(int); i++) {

		if (false == bFirst) {
			bFirst = true;
			nMin = nArray[i];
			nMax = nArray[i];
			continue ;
		}

		if (nMin > abs(nArray[i]))
			nMin = abs(nArray[i]);

		if (nMax < abs(nArray[i]))
			nMax = abs(nArray[i]);
	}

	printf("最小值[%d]，最大值[%d]\n", nMin, nMax);
	if (nMax == nMin)
		return 0;

	nBucketCnt = nMax - nMin + 1;
	pArray = (BUCKET_STATUS *)calloc(nBucketCnt * sizeof(BUCKET_STATUS), 1);
	
	nFNumber = 0;
	nZNumber = 0;

	// 绝对值相同的装到同一个桶中去，以不同的标识来区分
	for (int i = 0; i < (sizeof(nArray) / sizeof(int)); i++) {

		if (0 <= nArray[i]) {
			pArray[nArray[i] - nMin].a0++;
		}
		else {
			pArray[abs(nArray[i]) - nMin].a1++;
			nZNumber++;
		}
	}

	nFNumber = nZNumber - 1;
	printf("正数序号[%d]，负数序号[%d]\n", nZNumber, nFNumber);
	printf("排序后数值：\n");
	
	for (int i = 0; i < nBucketCnt; i++) {

		if (0 != pArray[i].a1) {
			for (int j = 0; j < pArray[i].a1; j++)
				nArray[nFNumber--] = -1 * (i + nMin);
		}
		
		if (0 != pArray[i].a0) {
			for (int j = 0; j < pArray[i].a0; j++)
				nArray[nZNumber++] = i + nMin;
		}
	}

	for (int i = 0; i < sizeof(nArray) / sizeof(int); i++) {
		printf("%d ", nArray[i]);
	}
	printf("\n");

	free(pArray);

	return 0;
}
