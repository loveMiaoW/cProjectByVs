#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.09.21 11.35 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
//***********************************************************************/
#include<iostream>
#include<cstring>
#include <algorithm>
using namespace std;
#define MAXLEN 100

void LCSLength(char* x, char* y, int m, int n, int c[][MAXLEN], int b[][MAXLEN])
{
    int i, j;
    for (i = 0; i <= m; i++)
        c[i][0] = 0;
    for (j = 1; j <= n; j++)
        c[0][j] = 0;
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 0;//为了后面回溯，作为公共子序列的判定
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                b[i][j] = 1;//为了后面向上回溯，向上寻找子序列的判定
            }
            else
            {
                c[i][j] = c[i][j - 1];
                b[i][j] = -1;//为了后面向左回溯，向左寻找子序列的判定
            }
        }
    }
}

void LCS(int b[][MAXLEN], char* x, int i, int j)
{
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == 0)//找到了公共字符
    {
        LCS(b, x, i - 1, j - 1);
        printf("%c ", x[i - 1]);
    }
    else if (b[i][j] == 1)//向上回溯的过程
        LCS(b, x, i - 1, j);
    else//向左回溯的过程
        LCS(b, x, i, j - 1);
}

int main(int argc, char** argv)
{
    char x[MAXLEN] = { "ABCBDABCA" };
    char y[MAXLEN] = { "BDCABABA" };
    int b[MAXLEN][MAXLEN] = { 0 };
    int c[MAXLEN][MAXLEN] = { 0 };
    int m, n;

    m = strlen(x);
    n = strlen(y);
    //for_each(b[0],b[m],myFun);
   
    LCSLength(x, y, m, n, c, b);//填写动态规划表格
    cout <<"b中数据:" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << b[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "c中数据:" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << c[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "最长公共子序列:" << endl;
    LCS(b, x, m, n);//回溯输出最长公共子序列

    return 0;
}
