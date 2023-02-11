#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.10.05 12.26 MRLIU
All rigth reserved
vs2022
***********************************************************************/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>
using namespace std;
ifstream ifs("1.txt");
/*
5
0 0 0 0 0 0
0 0 1 1 1 1
0 1 0 1 1 1
0 1 1 0 1 1
0 1 1 1 0 1
0 1 1 1 1 0

*/
class Clique {
	friend int maxClique(int**, int[], int);
private:
	void backTrack(int i);
	int** a, n, * x, * bestx, cn, bestn;
};

void Clique::backTrack(int i)
{
	if (i > n)
	{
		cout << endl << "bestx: ";

		for (int j = 1; j <= n; j++)
		{
			bestx[j] = x[j];
			//cout << bestx[j] << " ";
			if (bestx[j] == 1)
			{
				cout << j << " ";
			}
		}
		cout << endl;
		bestn = cn;

		return;
	}
	int OK = 1;
	for (int j = 1; j < i; j++)
	{
		if (x[j] && a[i][j] == 0)
		{
			OK = 0;
			break;
		}
	}
	if (OK)
	{
		x[i] = 1;
		cn++;
		backTrack(i + 1);
		x[i] = 0;
		cn--;
	}
	if (cn + n - i > bestn)
	{
		x[i] = 0;
		backTrack(i + 1);
	}
}

int maxClique(int** a, int v[], int n)
{
	Clique cQue;
	cQue.x = new int[n + 1];
	cQue.a = a;
	cQue.n = n;
	cQue.cn = 0;
	cQue.bestn = 0;
	cQue.bestx = v;
	cQue.backTrack(1);
	delete[] cQue.x;
	return cQue.bestn;
}

int main()
{
	int n;	//
	ifs >> n;
	cout << n << endl;
	//system("pause");
	int** m = new int* [n + 1];
	for (int i = 0; i <= n; i++)
	{
		m[i] = new int[n + 1];
	}
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			ifs >> m[i][j];
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	int* v = new int[n];
	cout <<"󶥵: " << maxClique(m, v, n);

	return 0;
}
