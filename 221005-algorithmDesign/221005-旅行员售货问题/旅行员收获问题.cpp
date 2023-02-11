#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.10.05 22.24 MRLIU
All rigth reserved
vs2022
***********************************************************************/
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
ifstream ifs("1.txt");
/*
6
0 0 0 0 0 0 0
0 0 5 7 0 36 30
0 5 0 5 0 18 23
0 7 5 0 22 35 0
0 0 20 22 0 3 9
0 36 18 35 3 0 5
0 30 23 0 9 5 0

*/

template<class Type>
class traveling {
	friend Type tsp(int**, int[], int, Type);
public:
	void backTrack(int i);
	int n, * x, * bestx;
	Type** a, cc, bestc, noEdge;
};

template<class Type>
void traveling<Type>::backTrack(int i)
{
	if (i == n)
	{
		if (a[x[n - 1]][x[n]] != noEdge && a[x[n]][1] != noEdge && (cc + a[x[n - 1]][x[n]] + a[x[n]][1] < bestc || bestc == noEdge))
		{
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];
			}
			bestc = cc + a[x[n - 1]][x[n]] + a[x[n]][1];
		}
	}
	else
	{
		for (int j = i; j <= n; j++)
		{
			if (a[x[i - 1]][x[j]] != noEdge && (cc + a[x[i - 1]][x[j]] < bestc || bestc == noEdge))
			{
				swap(x[i], x[j]);
				cc += a[x[i - 1]][x[i]];
				backTrack(i + 1);
				cc -= a[x[i - 1]][x[i]];
				swap(x[i], x[j]);
			}
		}
	}
}

template<class Type>
Type tsp(Type** a, int v[],int n, Type noEdge)
{
	traveling<Type> tra;
	tra.x = new int[n + 1];
	for (int i = 1; i <= n; i++) tra.x[i] = i;
	tra.a = a;
	tra.n = n;
	tra.bestc = noEdge;
	tra.bestx = v;
	tra.cc = 0;
	tra.noEdge = noEdge;
	tra.backTrack(2);
	delete[] tra.x;
	char c ;
	cout << endl << "bestx 数据有: ";
	for (int i = 1; i < n + 1; i++)
	{
		cout << tra.bestx[i] << " ";
	/*	c = tra.bestx[i] + 64;
		cout << c << " ";*/
	}
	cout << endl << "路径为: ";
	for (int i = 1; i < n + 1; i++)
	{
		//cout << tra.bestx[i] << "\t";
		c = tra.bestx[i] + 64;
		cout << c << " ";
	}
	cout << endl;
	cout << "路径最小值: ";
	return tra.bestc;
}

void test()
{
	int n;
	ifs >> n;
	int* a = new int[n + 1];
	int** m = new int* [n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		m[i] = new int[n + 1];
	}
	cout << "图的邻接矩阵为: " << endl;
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			ifs >> m[i][j];
			cout << m[i][j] << "\t";
		}
		cout << endl;
	}
	cout << tsp(m, a,n,0) << endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}