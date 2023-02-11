#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.09.12 15.38 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class MATRIX {
public:
	MATRIX();															//构造函数 矩阵名字行数列数
	~MATRIX();															//析构函数 释放矩阵占用的空间
	void creatMatrix(MATRIX* M,int matrixNumber);
	void matrixMultiply(MATRIX* M, int** m, int** n, int matrixNumber);	//算法核心--如何添加括号
	void traceBack(MATRIX* M, int** n, int i, int j);					//回溯获得括号
public:
	int row;															//矩阵行数
	int col;															//矩阵列数
	string name;														//矩阵名字
};

// 构造函数
MATRIX::MATRIX()
{

}

//析构函数
MATRIX::~MATRIX()
{

}

//创造矩阵
//输入名字 行数 列数
void MATRIX::creatMatrix(MATRIX* M, int matrixNumber)
{
	cout << "please initialization matrix(matrixName row col:A1 2 3)" << endl;
	for (int i = 0; i < matrixNumber; i++)
	{
		cout << "input " << i + 1<< " matrix info: ";
		cin >> M[i].name >> M[i].row >> M[i].col;
	}
}
/*
	用高级指针修饰低级指针 -> 二级指针修饰一级指针 -> 三级指针修饰二级指针
*/
void MATRIX::matrixMultiply(MATRIX* M, int** m, int** n, int matrixNumber)
{
	for (int r = 2; r <= matrixNumber; ++r) 
	{																		//至少两个矩阵相乘，至多[1,n]
		for (int i = 0; i < matrixNumber - r + 1; ++i) 
		{																	//i从0开始，主要是第一个矩阵信息在0号内存单元中
			int j = i + r - 1;												//j表示末尾的矩阵										
			m[i][j] = m[i + 1][j] + M[i].row * M[i].col * M[j].col;		//初始：k=i分割
			n[i][j] = i;													//记录分割点k
			for (int k = i + 1; k < j; ++k) 
			{																//k从i一直到j-1
				int t = m[i][k] + m[k + 1][j] + M[i].row * M[k].col * M[j].col;
				if (t < m[i][j]) {											//取最小值
					m[i][j] = t;
					n[i][j] = k;
				}
			}
		}
	}
}

//输出分割括号序列
void MATRIX::traceBack(MATRIX* M, int** n, int i, int j)
{
	if (i == j)
	{
		cout << M[i].name;
		return;
	}
	cout << "(";
	traceBack(M, n, i, n[i][j]);
	traceBack(M, n, n[i][j] + 1, j);
	cout << ")";
}

void test01()
{
	//MATRIX类型指针 M 
	//MATRIX* M;
	MATRIX mat;
	int matrixNumber = 0;
	cout << "please input matrix number: ";
	cin >> matrixNumber;
	MATRIX* M = new MATRIX[matrixNumber];
	mat.creatMatrix(M, matrixNumber);

	int** m = new int* [matrixNumber];
	for (int i = 0; i < matrixNumber; i++) 									//动态二维数组
	{
		m[i] = new int[matrixNumber];
	}

	int** n = new int* [matrixNumber];
	for (int i = 0; i < matrixNumber; i++)
	{
		n[i] = new int[matrixNumber];
	}

	for (int i = 0; i < matrixNumber; i++)									//把m、n中元素全部置为 -1
	{	
		for (int j = 0; j < matrixNumber; j++)
		{
			m[i][j] = -1;
			n[i][j] = -1;
		}
		m[i][i] = n[i][i] = 0;												//对角线置为 0 
	}

	mat.matrixMultiply(M, m, n, matrixNumber);


	//输出[i,j]之间的所有最小的乘法次数以及中间的分界线k
	cout << "\n从[i,j],最小的乘法次数表：\n";
	for (int i = 0; i < matrixNumber; i++) {
		for (int j = 0; j < matrixNumber; j++)
			cout << m[i][j] << "\t";
		cout << "\n";
	}
	cout << "\n从[i,j],中间断开k的记录表：\n";
	for (int i = 0; i < matrixNumber; i++) {
		for (int j = 0; j < matrixNumber; j++)
			cout << n[i][j] << "\t";
		cout << "\n";
	}

	//添加括号
	cout << "\n矩阵连乘添加括号：" << endl;
	cout << "最少乘法次数： " << m[0][matrixNumber - 1] << "次；计算顺序： ";
	mat.traceBack(M, n, 0, matrixNumber - 1);

	cout << endl;
	//内存释放
	for (int i = 0; i < matrixNumber; ++i) {
		delete[] n[i];
		delete[] m[i];
	}
	delete[] n;
	delete[] m;
	delete[] M;
}
int main()
{
	//freopen("./input.txt", "r", stdin);
	test01();
	system("pause");
	return 0;
}