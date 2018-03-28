#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_CNT 10
#define MAX_VALUE     100

// ȱ������ʽ��
// 1. �������⣺�����Ӧ����Ͱ��ʱȡ����ֵ���Ž�����ֵͰ��Ͱ�ֱ��ʶ�����ĸ����Լ������ĸ��������������һ�α������ɡ�
// 2. �ռ����⣺�����������Ԫ�ؾ���ֵ�е���Сֵ�Լ����ֵ������ռ�Ϊ space = ���ֵ - ��Сֵ������Ͱʱȡƫ��Ͱ�ż��ɡ�

struct BUCKET_STATUS {
	int a0;	// ������ʶ
	int a1;	// ������ʶ
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

	printf("������������£�\n");

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

	printf("��Сֵ[%d]�����ֵ[%d]\n", nMin, nMax);
	if (nMax == nMin)
		return 0;

	nBucketCnt = nMax - nMin + 1;
	pArray = (BUCKET_STATUS *)calloc(nBucketCnt * sizeof(BUCKET_STATUS), 1);
	
	nFNumber = 0;
	nZNumber = 0;

	// ����ֵ��ͬ��װ��ͬһ��Ͱ��ȥ���Բ�ͬ�ı�ʶ������
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
	printf("�������[%d]���������[%d]\n", nZNumber, nFNumber);
	printf("�������ֵ��\n");
	
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
