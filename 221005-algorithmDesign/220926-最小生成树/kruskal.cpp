#define _CRT_SECURN_WARNINGS
/**********************************************************************
Copyright(c) 2022.10.01 09.30 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream ifs("1.txt");
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
const int N = 1e5 + 10;
const int M = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int p[N];
struct Edge {//虽然为无向图，但是存一个边就行
    int a, b, w;//a到b权为w的边
    bool operator < (const Edge& W)const//重载运算符<
    {
        return w < W.w;
    }
}edges[M];

int find(int x)//并查集
{
    if (p[x] != x)
        p[x] = find(p[x]);
    return p[x];
}

int Kruskal()
{
    sort(edges, edges + m);//将n个边按照边权从小到大排列
    for (int i = 1; i <= n; i++)
        p[i] = i;
    int res = 0, cnt = 0;//res记录最小生成树中的边权之和,cnt记录最小生成树中的边数
    for (int i = 0; i < m; i++)
    {
        int a = edges[i].a;
        int b = edges[i].b;
        int w = edges[i].w;//记录边权的值
        a = find(a);//记录a集合的顶点
        b = find(b);//记录b集合的顶点
        if (a != b)//如果a,b不在一个集合中
        {
            p[a] = b;//合并a,b两个集合
            res += w;//加上边权
            cnt++;//加上边
        }
    }
    if (cnt < n - 1)//如果边的个数小于n-1，就不是最小生成树
        return INF;
    return res;
}
int main()
{
    ifs >> n >> m;
    for (int i = 0; i < m; i++) {
        ifs >> edges[i].a >> edges[i].b >> edges[i].w;
        cout << edges[i].a<<" " << edges[i].b<< " " << edges[i].w << endl;
    }
    int t = Kruskal();
    if (t == INF)
        cout << "impossible" << endl;
    else
        cout << "最短路径：" << t << endl;
    return 0;
}