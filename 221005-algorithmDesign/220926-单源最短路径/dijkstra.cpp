#define _CRT_SECURE_WARNINGS
/**********************************************************************
Copyright(c) 2022.09.29 17.08 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream> 
#include <fstream>  
#include <string> 
using namespace std;

const int N = 7;			//顶点个数，更换其他图，请更新N的大小
const int MAXINT = 9999;	//若有权值大于9999的边请将MAXINT 更新到更大
/*
9999 4	  6		6	9999 9999 9999
9999 9999 1	   9999 7	 9999 9999
9999 9999 9999 9999 6	 4	  9999
9999 9999 2	   9999 9999 5	  9999
9999 9999 9999 9999 9999 9999 4
9999 9999 9999 9999 1	 9999 8
9999 9999 9999 9999 9999 9999 9999
*/
ifstream fin("1.txt");

template<class Type>
void Dijkstra(int n, int v, Type dist[], int prev[], Type c[][N + 1])
{
	bool s[N + 1];
	for (int i = 1; i <= n; i++)
	{
		dist[i] = c[v][i];//dist[i]表示当前从源到顶点i的最短特殊路径长度
		s[i] = false;

		if (dist[i] == MAXINT)
		{
			prev[i] = 0;//记录从源到顶点i的最短路径i的前一个顶点
		}
		else
		{
			prev[i] = v;
		}
		//cout << "dist:" << dist[i] << " ";
	}
	//cout << endl;
	dist[v] = 0;
	s[v] = true;

	for (int i = 1; i < n; i++)
	{
		int temp = MAXINT;
		int u = v;//上一顶点

		//取出V-S中具有最短特殊路径长度的顶点u
		for (int j = 1; j <= n; j++)
		{
			if ((!s[j]) && (dist[j] < temp))
			{
				u = j;
				temp = dist[j];
			}
		}
		s[u] = true;

		//根据作出的贪心选择更新Dist值
		for (int j = 1; j <= n; j++)
		{
			if ((!s[j]) && (c[u][j] < MAXINT))
			{
				Type newdist = dist[u] + c[u][j];
				if (newdist < dist[j])
				{
					dist[j] = newdist;
					prev[j] = u;
				}
			}
		}
		
	}
}
//输出最短路径 v源点，i终点
void Traceback(int v, int i, int prev[])
{
	if (v == i)
	{
		cout << i;
		return;
	}
	Traceback(v, prev[i], prev);
	cout << "->" << i;
}
int main()
{
	
	int v = 1;//源点为1
	int dist[N + 1], prev[N + 1], c[N + 1][N + 1];

	cout << "(maxint = 9999) 有向图权的矩阵为:" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			fin >> c[i][j];
			cout << c[i][j] << "\t";
		}
		cout << endl;
	}

	Dijkstra(N, v, dist, prev, c);

	for (int i = 2; i <= N; i++)
	{
		cout << "源点1到点" << i << "的最短路径长度为:" << dist[i] << "，其路径为";
		Traceback(1, i, prev);
		cout << endl;
	}

	return 0;
}




