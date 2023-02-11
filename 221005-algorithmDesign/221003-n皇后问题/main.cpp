#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.10.03 19.26 MRLIU
All rigth reserved
vs2022
***********************************************************************/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

class Queen {
	friend int nQueen(int);
private:
	bool place(int k);
	void backTrack(int t);
	int n, * x;
	long sum;
};

bool Queen::place(int k)
{
	for (int j = 1; j < k; j++)
	{
		if ((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
		{
			return false;
		}
	}
	return true;
}

void Queen::backTrack(int t)
{
	if (t > n)
	{
		for (int i = 1; i <= n; i++) 
		{
			cout << que.x[i] << " ";
		}
		cout << endl;
		sum++;
		
	}
	else {
		for (int i = 1; i <= n; i++)
		{
			x[t] = i;
			if (place(t)) backTrack(t + 1);
		}
	}
}

int nQueen(int n)
{
	Queen que;
	que.n = n;
	que.sum = 0;
	int* p = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	que.x = p;
	que.backTrack(1);
	delete[] p;
	return que.sum;
}


int main()
{
	while (1)
	{
		int n;
		cout << "input n: ";
		cin >> n;
		cout <<"з: "<< nQueen(n) << endl;
	}
	return 0;
}