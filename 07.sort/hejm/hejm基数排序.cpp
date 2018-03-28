#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ARRAY_CNT 10
#define MAX_VALUE 100

int g_nArray[MAX_ARRAY_CNT];
int g_nBuckets[10][MAX_ARRAY_CNT + 1];

int GetBitValue(int nValue, int nBitPos);

int main()
{
	int nRs;
	int nMax;
	int nLoop;

	memset(g_nArray, 0, sizeof(g_nArray));
	memset(g_nBuckets, 0, sizeof(g_nBuckets));

	printf("原始数据：\n");
	for (int i = 0; i < MAX_ARRAY_CNT; i++) {

		g_nArray[i] = rand() % MAX_VALUE;
		printf("%d ", g_nArray[i]);

		if (0 == i)
			nMax = g_nArray[i];
		else
			nMax = (g_nArray[i] > nMax ? g_nArray[i] : nMax);
	}
	printf("\n");

	printf("最大值：%d\n", nMax);
	// 计算loop次数
	for (nLoop = 1; nLoop < 10; nLoop++) {

		int nValue = pow(10, nLoop);
		if (0 == nMax / nValue)
			break ;
	}
	printf("loop次数：%d\n", nLoop);
	printf("\n");

	for (int i = 0; i < nLoop; i++) {

		int nIndex = 0;

		for (int j = 0; j < MAX_ARRAY_CNT; j++)
			g_nBuckets[j][0] = 0;

		for (int j = 0; j < MAX_ARRAY_CNT; j++) {

			int nPow = pow(10, i + 1);
			int nIndex = GetBitValue(g_nArray[j], i + 1);
			int nPos = g_nBuckets[nIndex][0];

			g_nBuckets[nIndex][1 + nPos] = g_nArray[j];

			g_nBuckets[nIndex][0]++;
		}

		for (int j = 0; j < 10; j++) {

			int nCnt = g_nBuckets[j][0];

			for (int k = 0; k < nCnt; k++)
				g_nArray[nIndex++] = g_nBuckets[j][k + 1];
		}

		printf("第%d趟排序后：\n", i + 1);
		for (int j = 0; j < MAX_ARRAY_CNT; j++)
			printf("%d ", g_nArray[j]);
		printf("\n");
		printf("\n");
	}

	return 0;
}

/*
int main()
{
	GetBitValue(321, 3);
	GetBitValue(321, 2);
	GetBitValue(321, 1);

	return 0;
}
*/
int GetBitValue(int nValue, int nBitPos) {

	int nTmp0, nTmp1, nNewValue;

	if (0 == nBitPos)
		return -1;

	nTmp0 = pow(10, nBitPos);
	nTmp1 = pow(10, nBitPos - 1);
	nNewValue = nValue;	

	nNewValue = nNewValue % nTmp0;
	nNewValue = nNewValue / nTmp1;

//	printf("GetBitValue(%d, %d) --> %d\n", nValue, nBitPos, nNewValue);
	return nNewValue;
}
