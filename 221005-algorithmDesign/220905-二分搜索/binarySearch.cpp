#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.09.06 14.35 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream>
#include <ctime>

using namespace std;

template<class T>
T binarySearch(T a[], const T& x, int len)
{
	//找到时返回元素所在下标，未找到返回 -1
	T l = 0;
	T r = len - 1;
	while (l <= r)
	{
		T mid = (l + r) / 2;
		if (x == a[mid])
		{
			return mid;
		}
		if (x > a[mid])
		{
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}
	return -1;
}

void test01()
{
	int data[] = { 12,14,18,20,26,29,34,39,46,48,50,56,90,100,150,160,180,190,9000,100000 };
	//sort();
	cout << "please input need find data:" << endl << endl;
	int da;
	cin >> da;
	int index =  binarySearch(data, da, sizeof(data) / sizeof(int));
	if (index == -1)
	{
		cout << "no find...." << endl;
	}
	else
	{
		cout << da << " 所在下标 " << index << endl;
	}

}

int main()
{
	time_t start, end;
	start = clock();
	test01();
	end = clock();
	cout << endl;
	cout << "程序用时:" << (double)(end - start) << "ms"<< endl;
	//cout <<  (17 + 14) / 2 << endl;
	return 0;
}