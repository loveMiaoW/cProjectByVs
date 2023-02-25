#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*
	打开文件

*/
const char* inputFile = "./sortData.txt";
const char* outPutFile = "./sortOkData.txt";

int getFileCount()
{
	FILE* fp = fopen(inputFile, "rb");
	char buf[20];
	int count = 0;
	while (fgets(buf,sizeof(buf),fp) != NULL)
	{
		//printf("%s\n", buf);
		count++;
	}
	fclose(fp);
	fp = NULL;
	return count;
}

void sortData(int* arr, int n)
{
	int i, j;
	int tmp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void saveData(int *arr,int n,FILE* fp)
{
	if (fp == NULL)
	{
		fp = fopen(outPutFile, "w");
	}
	char buf[100];
	for (int i = 0; i < n; i++)
	{
		sprintf(buf, "%d\n", arr[i]);
		fputs(buf, fp);
	}
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}

int main(int agrc, char** argv)
{
	FILE* fRead = fopen(inputFile, "rb");
	FILE* fWrite = fopen(outPutFile, "wb");
	int fileCount = getFileCount();
	//printf("%d\n", fileCount);
	int i = 0;
	char buf[20];
	int* arr = (int*)malloc(fileCount * sizeof(int));
	while (fgets(buf, sizeof(buf), fRead) != NULL)
	{
		sscanf(buf, "%d", &arr[i]);
		i++;
		//printf("%d\n", arr[i]);
		//printf("----\n");
		//printf("%s\n", buf);
	}
	sortData(arr,fileCount);
	saveData(arr,fileCount,fWrite);
	return 0;
}
