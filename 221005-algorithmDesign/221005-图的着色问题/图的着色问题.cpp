#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.10.05 15.58 MRLIU
All rigth reserved
vs2022
***********************************************************************/
#include <iostream>
#include <fstream>

using namespace std;
ifstream ifs("1.txt");
/*
5 4
0 0 0 0 0 0
0 0 1 1 1 0
0 1 0 3 4 5
0 1 1 0 1 0
0 1 1 1 0 1
0 0 1 0 1 0
*/

class color {
	friend int mColor(int, int, int**);
private:
	bool ok(int k);
	void backTrack(int t);
	int n, m, ** a, * x;
	long sum;
};

bool color::ok(int k)
{
	for (int j = 1; j <= n; j++)
	{
		if ((a[k][j] == 1) && (x[j] == x[k])) return false;
	}
	return true;
}

void color::backTrack(int t)
{
	if (t > n)
	{
		sum++;
		for (int i = 1; i <= n; i++)
		{
			cout <<"\t" << x[i] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int i = 1; i <= m; i++)
		{
			x[t] = i;
			if (ok(t)) backTrack(t + 1);
			x[t] = 0;
		}
	}
}

int mColor(int n, int m, int** a)
{
	color col;
	col.n = n;
	col.m = m;
	col.a = a;
	col.sum = 0;
	int* p = new  int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	col.x = p;
	col.backTrack(1);
	delete[] p;
	return col.sum;
}

void test()
{
	int n, m;
	ifs >> n >> m;
	int** ptr = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		ptr[i] = new int[n + 1];
	}
	cout << "输入邻接矩阵: " << endl;
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			ifs >> ptr[i][j];
			cout << ptr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << "上色方案：" << endl;
	cout << endl <<"总共有: " << mColor(n, m, ptr)<<" 种上色方案。" << endl;
}

int main()
{
	test();
	system("pause");

	return 0;
}


