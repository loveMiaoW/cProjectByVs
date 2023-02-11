#define _CRT_SECURE_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;
const int maxint = 9999;
ifstream ifs("1.txt");
template <class Type>
void prim(int n, Type** c)
{
	Type lowcost[maxint];
	int closeSet[maxint];
	bool s[maxint];
	s[0] = true;
	for (int i = 0; i < n - 1; i++)
	{
		lowcost[i] = c[0][i];
		closeSet[i] = -1;
		s[i] = false;
	}

	for (int i = 0; i < n - 1; i++)
	{
		Type min = maxint;
		int j = 1;
		for (int k = 0; k < n; k++)
			if ((lowcost[k] < min) && (!s[k])) {min = lowcost[k];j = k;}
		cout << j << " " << closeSet[j] << endl;
		s[j] = true;
		for (int k = 0; k < n; k++)
		{
			if ((c[j][k] < lowcost[k]) && (!s[k]))
			{
				lowcost[k] = c[j][k];
				closeSet[k] = j;
			}
		}
	}
}

int main()
{
	int n;
	ifs >> n;
	int** c = new int* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ifs >> c[i][j];
			cout << c[i][j] << "\t";
		}
		cout << endl;
	}
	prim(n, c);
	return 0;
}