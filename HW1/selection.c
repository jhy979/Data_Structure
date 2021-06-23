#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void selection_Sort(int* arr, int size) {
	int min = 0;
	
	for (int i = 0; i < size; i++) {
		min =i;
		for (int j = i; j < size; j++) {
			if (arr[min] > arr[j])
				min = j;
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
	return;
}
int main() {
	FILE* fp = fopen("lab1.data.txt", "r");
	if (fp == NULL) {
		printf("cannot open file\n");
		return;
	}
	int n;
	double duration;
	clock_t start;
	fscanf(fp,"%d", &n);
	int* arr = (int*)malloc(sizeof(int) * n); // ���� ���� �����Ҵ�
	for (int i = 0; i < n; i++) {
		fscanf(fp,"%d", &arr[i]);
	}

	// Input : ---
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			printf("Input: ");
		}
		printf("%d", arr[i]);
		if (i != n - 1) {
			printf(", ");
		}
	}
	printf("\n");

	
	//��������
	long repetitions = 0;
	start = clock();
	do {
		repetitions++;
		selection_Sort(arr, n);
	} while (clock() - start < 1000);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	printf("\n");
	printf("\n");
	//Sorted: ---
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			printf("Sorted: ");
		}
		printf("%d", arr[i]);
		if (i != n - 1) {
			printf(", ");
		}
	}
	printf("\n");
	//����ð� ���
	printf("����ð� : %lf\n", duration/repetitions);
	free(arr);
	return 0;
}