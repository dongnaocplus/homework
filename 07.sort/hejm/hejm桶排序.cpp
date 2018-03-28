#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_CNT 10
#define MAX_BUCKET_CNT 5
#define MAX_VALUE 100

struct BUCKET_INFO {
	int nBeg;
	int nEnd;
	int nCnt;
	int nArray[MAX_ARRAY_CNT];
};

int IntSort(const void *a, const void *b) {
	return (*((const int *)a) - *((const int *)b));
}

int main()
{
	int nMin;
	int nMax;
	int nStep;
	int nArray[MAX_ARRAY_CNT];
	BUCKET_INFO BucketArray[MAX_BUCKET_CNT];

	memset(BucketArray, 0, sizeof(BucketArray));
	
	printf("排序前：\n");
	for (int i = 0; i < MAX_ARRAY_CNT; i++) {

		nArray[i] = rand() % MAX_VALUE;
		printf("%d ", nArray[i]);

		if (0 == i) {
			nMin = nArray[i];
			nMax = nArray[i];
		}
		else {
			if (nMin > nArray[i])
				nMin = nArray[i];
			if (nMax < nArray[i])
				nMax = nArray[i];
		}
	}
	printf("\n");

	// 分配桶的范围
	nStep = (nMax - nMin) / MAX_BUCKET_CNT;
	nStep += (0 == (nMax - nMin) % MAX_BUCKET_CNT ? 0 : 1);
	printf("最小值:%d, 最大值:%d, 步长:%d\n", nMin, nMax, nStep);
	for (int i = 0; i < MAX_BUCKET_CNT; i++) {

		if (MAX_BUCKET_CNT - 1 == i) {

			BucketArray[i].nBeg = nMin + i * nStep;
			BucketArray[i].nEnd = nMax;
		}
		else {

			BucketArray[i].nBeg = nMin + i * nStep;
			BucketArray[i].nEnd = nMin + (i + 1) * nStep - 1; 
		}
		printf("桶%d --> {BEG:%d, END:%d}\n", 
			i, BucketArray[i].nBeg, BucketArray[i].nEnd);
	}

	printf("准备入桶操作 ...\n");
	for (int i = 0; i < MAX_ARRAY_CNT; i++) {

		int nIndex;

		nIndex = (nArray[i] - nMin) / nStep;	

		BucketArray[nIndex].nArray[BucketArray[nIndex].nCnt++] = nArray[i];
	}
	printf("入桶操作完毕 ...\n");

	for (int i = 0; i < MAX_BUCKET_CNT; i++) {

		if (0 == BucketArray[i].nCnt) 
			continue ;

		qsort(BucketArray[i].nArray, BucketArray[i].nCnt, sizeof(int), IntSort);
	}

	printf("排序后：\n");
	for (int i = 0; i < MAX_BUCKET_CNT; i++) {

		if (0 == BucketArray[i].nCnt)
			continue ;

		for (int j = 0; j < BucketArray[i].nCnt; j++)
			printf("%d ", BucketArray[i].nArray[j]);
	}
	printf("\n");

	return 0;
}
