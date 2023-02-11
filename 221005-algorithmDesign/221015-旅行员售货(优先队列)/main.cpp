#include<iostream>
#include <fstream>
#include<cstring>
#include<queue>
#define INF 1e7
using namespace std;

ifstream ifs("1.txt");
//按图节点编号 1 - 2 - 3 -4
/*
4
0 20 10 4
20 0 5 6
10 5 0 30
4 6 30 0
*/

int m[100][100];//存储路径，从1开始
int bestx[100];//最优解路径
int bestl;//最优解长度
int n;//城市数目

//排列树的节点定义
struct node
{
    int cl;//当前走过的路径长度
    int id;//处理的第几个城市
    int x[100];//记录当前路径，下标从1开始

    node() {}
    node(int cl_, int id_)
    {
        cl = cl_;
        id = id_;
        memset(x, 0, sizeof(x));
    }
};



//用于构建最小堆
struct cl_cmp {
    //当前路径长度短的优先级高
    bool operator()(node n1, node n2)
    {
        return n1.cl > n2.cl;
    }
};

void bfs()
{
    //选用最小堆
    priority_queue<node, vector<node>, cl_cmp> q;
    //创建一个节点，从该节点开始，因为1是固定位，其实是从1开始探索
    node temp(0, 2);
    //初始化解向量
    for (int i = 1; i <= n; ++i)
        temp.x[i] = i;
    q.push(temp);
    node cur;//当前节点，也就是活节点
    int t;
    while (!q.empty())
    {
        cur = q.top();
        q.pop();
        t = cur.id;
        //处理到倒数第二个城市
        if (t == n)
        {
            //满足约束条件，有路径
            //检测图G是否存在一条从顶点x[n-1]到顶点x[n]的边和一条从顶点x[n]到顶点1的边
            //这里和前面的理论部分不同，因为这里是从1开始，而不是0开始
            if (m[cur.x[t - 1]][cur.x[t]] != INF && m[cur.x[t]][1] != INF)
            {
                if (cur.cl + m[cur.x[t - 1]][cur.x[t]] + m[cur.x[t]][1] < bestl)
                {
                    //更新最优解和最优路径
                    bestl = cur.cl + m[cur.x[t - 1]][cur.x[t]] + m[cur.x[t]][1];
                    for (int i = 1; i <= n; ++i)
                        bestx[i] = cur.x[i];
                }
            }continue;
        }
        //大于等于最优路径，没必要继续探索了，从下一个节点开始
        if (cur.cl >= bestl)
            continue;
        //从当前节点开始探索t-1 -> t,t+1,t+2...
        for (int j = t; j <= n; ++j)
        {
            //满足约束条件和限界条件
            if (m[cur.x[t - 1]][cur.x[j]] != INF && cur.cl + m[cur.x[t - 1]][cur.x[j]] < bestl)
            {
                temp = node(cur.cl + m[cur.x[t - 1]][cur.x[j]], t + 1);
                //如果找到了一个下级节点，那么该节点到现在为止和同级的节点路径相同，除了当前这一级的不同
                for (int k = 1; k <= n; ++k)
                    temp.x[k] = cur.x[k];
                swap(temp.x[t], temp.x[j]);
                q.push(temp);
            }
        }
    }
}
int main()
{
    ifs >> n;
    cout << "节点个数: " << n << endl;
    //先进行初始化
    int i, j;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            m[i][j] = INF;
    memset(bestx, 0, n);
    bestl = INF;
    cout << "图的邻接矩阵: " << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ifs >> m[i][j];
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    //进行探索
    bfs();
    cout << "最优值为：" << bestl << endl;
    cout << "最优解为：";
    for (int i = 1; i <= n; ++i)
        cout << bestx[i] << " ";
    cout << bestx[1] << endl;
    return 0;
}
