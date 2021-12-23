#include "Header.h"

void printArray(int* arr) {
	for (int i = 0; i < 10; i++) {
		if (i == 9) printf("%d\n", arr[i]);
		else printf("%d ", arr[i]);
	}
}