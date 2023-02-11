#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.09.11 18.35 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream>
#include <ctime>
using namespace std;
int b[12];

template<class T>
void Merge(T a[], int low, int mid, int high) {
	int k, i, j;
	for (k = low; k <= high; k++) {
		b[k] = a[k];
	}

	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
		if (b[i] < b[j])
		{
			a[k] = b[i++];
		}
		else {
			a[k] = b[j++];
		}
	}
	//完成后在a中就ok了
	//剩下那边还有富余就直接接上去
	while (i <= mid) {
		a[k++] = b[i++];
	}
	while (j <= high) {
		a[k++] = b[j++];
	}
}
int count = 0;
template<class T>
void myPrintf(T a[])
{
	cout << "第 " << ++::count << " 次排序结果：";
	for (int i = 0; i < 11; i++)
	{
		cout << a[i] << "\t";
	}
	cout << endl;
}

template<class T>
void MergeSort(T a[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(a, low, mid);
		MergeSort(a, mid + 1, high);
		Merge(a, low, mid, high);
		myPrintf(a);
	}
}

void test01()
{
	int a[] = {9,11,3,7,5,2,66,18,270,32,37};
	//cout << sizeof(a) / sizeof(int) << endl;
	MergeSort(a, 0, sizeof(a)/sizeof(int) - 1);
}
int main01()
{
	time_t start, end;
	start = clock();
	test01();
	end = clock();
	cout << "using time:" << (double)(end - start) << "ms" << endl;
	return 0;
}


