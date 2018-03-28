#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_CNT 10
#define MAX_VALUE 100
#define MAX_INCREMENT 8
#define RATE 1.3

int main()
{
	int nInc;
	int nArray[MAX_ARRAY_CNT];

	nInc = MAX_ARRAY_CNT;

	for (int i = 0; i < MAX_ARRAY_CNT; i++) {
		nArray[i] = rand() % MAX_VALUE;
		printf("%d ", nArray[i]);
	}
	printf("\n");

	while (1) {

		nInc = nInc / RATE;	

		for (int i = 0; i < nInc; i++) {

			for (int j = i + nInc; j < MAX_ARRAY_CNT; j += nInc) {

				if (nArray[j] < nArray[j - nInc]) {
			
					int nTmp = nArray[j];
					nArray[j] = nArray[j - nInc];
					nArray[j - nInc] = nTmp;
				}
			}
		}

		if (nInc <= 1)
			break ;
	}

	for (int i = 0; i< MAX_ARRAY_CNT; i++)
		printf("%d ", nArray[i]);
	printf("\n");

	return 0;
}
