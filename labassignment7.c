#include <stdio.h>

int main() {
	
    int arr[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int size = sizeof(arr) / sizeof(arr[0]);
    int swap[n];

    for (int i = 0; i < size; i++) {
        swap[i] = 0;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swap[j]++;
            }
        }
    }
	
    return 0;
}
