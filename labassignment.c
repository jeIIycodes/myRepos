#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void merge(int pData[], int l, int m, int r)
{
    int a, b, c;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (a = 0; a < n1; a++)
        L[a] = pData[l + a];
    for (b = 0; b < n2; b++)
        R[b] = pData[m + 1+ b];

    a = 0;
    b = 0;
    c = l;
    while (a < n1 && b < n2)
    {
        if (L[a] <= R[b])
        {
            pData[c] = L[a];
            a++;
        }
        else
        {
            pData[c] = R[b];
            b++;
        }
        c++;
    }

    while (a < n1)
    {
        pData[c] = L[a];
        a++;
        c++;
    }

    while (b < n2)
    {
        pData[c] = R[b];
        b++;
        c++;
    }
}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if (l < r)
    {
        int a = l+(r-l)/2;
        mergeSort(pData, l, a);
        mergeSort(pData, a+1, r);
        merge(pData, l, a, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    extraMemoryAllocated = 0;
    int a, j;
    for (int i = 1; i < n; i++)
    {
        a = pData[i];
        j = i - 1;

        while (j >= 0 && pData[j] > a)
        {
            pData[j + 1] = pData[j];
            j = j--;
        }
        pData[j + 1] = a;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    extraMemoryAllocated = 0;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (pData[j] > pData[j+1])
            {
                int temp = pData[j];
                pData[j] = pData[j+1];
                pData[j+1] = temp;
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    extraMemoryAllocated = 0;
	int x;

    for (int i = 0; i < n-1; i++)
    {
        x = i;
        for (int j = i+1; j < n; j++)
        {
            if (pData[j] < pData[x])
            {
                x = j;
            }
        }

        int temp = pData[x];
        pData[x] = pData[i];
        pData[i] = temp;
        extraMemoryAllocated += sizeof(int);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		for (int i = 0; i < dataSz; i++) {
            fscanf(inFile, "%d", (*ppData) + i);
        }
        fclose(inFile);

	}

	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");

	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);

		if (dataSz <= 0)
			continue;

		pDataCopy = (int *)malloc(sizeof(int)*dataSz);

		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");

		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		free(pDataCopy);
		free(pDataSrc);
	}

}
