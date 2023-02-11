/**********************************************************************
Copyright(c) 2022.09.30 15.18 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <queue>
using namespace std;

ifstream ifs("1.txt");
/*
0 6 0 0 0 1 0
6 0 4 0 0 0 3
0 4 0 2 0 0 0
0 0 2 0 6 0 5
0 0 0 6 0 8 7
1 0 0 8 0 0 0
0 1 0 5 7 0 0
*/
/*
7 9
1 2 6
1 6 1
2 3 4
2 7 3
3 4 2
4 5 6
4 7 5
5 6 8
5 7 7

*/
const int N = 510;
const int INF = 0x3f3f3f3f;
int n, m;
int g[N][N];
int dist[N];//存的点到集合的最短距离
bool st[N];//存下标的点是否在集合中,1代表在集合中，0代表不在集合中

int prim()
{
    memset(dist, 0x3f, sizeof dist);
    int res = 0;//存最小生成树的边的和
    for (int i = 0; i < n; i++)//遍历所有的点
    {
        int t = -1;//是存当前集合外的到集合距离最短的点,-1是没找到
        for (int j = 1; j <= n; j++)//找i点与后面的点哪个点t有最短路
        {
            if (!st[j] && (t == -1 || dist[t] > dist[j]))//当j不在最小生成树中，且t还没找到最短路的下标 或者 当前i j距离小于i t距离
                t = j;//更新最短路的下标
        }
        if (i && dist[t] == INF)//当i不是第一个点，且最短路是正无穷时，证明图中存在不连通的点，就不可能有最小生成树
            return INF;
        if (i)//当找到最短路时，且不是第一个点
            res += dist[t];
        st[t] = true;//t点进入集合
        for (int j = 1; j <= n; j++)//用新加入集合的点t，用t到其他边的距离来更新其他点到集合的距离
            dist[j] = min(dist[j], g[t][j]);
    }
    return res;
}

int main()
{

    ifs >> n >> m;
    for (int i = 1; i <= n; i++)//刚开始将所有的边都初始化为正无穷
    {
        for (int j = 1; j <= n; j++)
        {
            /*if(i==j)
                g[i][j]=0;
            else*/
            g[i][j] = INF;
            //ifs >> g[i][j];
        }
    }
    while (m--)
    {
        int a, b, c;
        ifs >> a >> b >> c;
        cout << a <<" " << b <<" " << c << endl;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    int t = prim();
    if (t == INF)
        cout << "impossible" << endl;
    else
        cout <<"最短路径:" << t << endl;
    return 0;
}