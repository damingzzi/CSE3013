#include "Header.h"

int cnt, page;

int main() {
	scanf("%d", &cnt);
	while (cnt--) {
		int* arr = (int *)malloc(sizeof(int)* 10);
		for (int i = 0; i < 10; i++) {
			arr[i] = 0;
		}
		scanf("%d", &page);
		countNum(page, arr);
		printArray(arr);
		free(arr);
	}
}