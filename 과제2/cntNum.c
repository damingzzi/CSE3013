#include "Header.h"

void countNum(int num, int* arr) {
	int temp, i, j;
	for (i = 1; i <= num; i++) {
		temp = i;
		while (temp) {
			j = temp % 10;
			arr[j]++;
			temp /= 10;
		}
	}
}

