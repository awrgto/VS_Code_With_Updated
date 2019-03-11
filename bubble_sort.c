#include <stddef.h>
#include <stdio.h>

void bubble_sort(int *, int);
void swap(int *, int *);

int main() {
	int data[] = {12, 1, 7, 45, 25, 1, 23, 5, 9, 0};

    bubble_sort(data, sizeof(data) / sizeof(int));

    for (size_t i = 0; i < sizeof(data) / sizeof(int); i++) {
		printf("%d ", data[i]);
	}
}

void bubble_sort(int *arr, int count) {
	for (size_t outer = 0; outer < count; outer++) {
		int swapped = 0;
		for (size_t inner = 0; inner < count; inner++) {
			if (arr[inner] > arr[inner + 1]) {
				swap(&arr[inner], &arr[inner + 1]);
                swapped = 1;
            }
		}
        //if(swapped == 1)
          //  break;
    }
}

void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}