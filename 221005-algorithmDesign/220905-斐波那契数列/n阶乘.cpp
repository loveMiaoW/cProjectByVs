#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
//#include <string>
#include <vector>
using namespace std;
int n = 0;
int f(int n)
{
	if (n == 1)
	{
		return 1;
	}
	return n * f(n - 1);
}

//斐波那契数列
//1 1 2 3 5 8 13

//int fibonacci(int n)
//{
//	if (n <= 2)
//	{
//		return 1;
//	}
//	return fibonacci(n - 1) + fibonacci(n - 2);
//}

//ackerman
int ackerman(int m,int n)
{
	if (m == 0)
	{
		return n + 1;
	}
	else if (m > 0 && n == 0)
	{
		return ackerman(m - 1, 1);
	}
	else
	{
		return ackerman(m - 1, ackerman(m, n - 1));
	}
}

void fullPermutation(int arr[],int left,int right)
{
	if (left == right)
	{
		for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
		n++;
	}
	else
	{
		for (int i = left; i <= right; i++)
		{
			swap(arr[i], arr[left]);
			fullPermutation(arr, left + 1, right);
			swap(arr[i], arr[left]);
		}
	}
}
void test01()
{
	int num;
	cin >> num;
	cout << f(num) << endl;
}

void test02()
{
	ifstream ifs;
	ifs.open("./input.txt", ios::in);
	if (ifs.is_open() == false)
	{
		cout << "load is failure" << endl;
	}
	
	int num;
	//cin >> num;
	while (ifs >> num)
	{
		//│ ├ │
		int max = 0;
		cout << "读到的数字是:" << num << endl;
		cout << "├-------------------------------|" << endl;
		for (int i = 1; i <= num; i++)
		{
			cout <<"数字:"<< num <<" " << "第" << i << "次执行 " << fibonacci(i) << endl;
		}
		cout << "总共执行" << num << "次" << endl;
		cout << "├-------------------------------| " << endl;
		//cout << "--------------------------" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
	}
}

void test03()
{
	ifstream ifs;
	ifs.open("./input.txt", ios::in);
	if (ifs.is_open() == false)
	{
		cout << "loading is failure." << endl;
	}
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));
		cout << buf << endl;
	}
}

void test04()
{
	int num1, num2;
	cin >> num1 >> num2;
	//cin >> num2;
	cout << ackerman(num1, num2) << endl;
}

void test05()
{
	int array[4] = { 1,2,3 };
	cout << "(1,2,3)的全排列：\n";
	fullPermutation(array, 0, 2);
	cout << "(1,2,3)的全排列数：" << n << endl;
}

int main01()
{
	while (1)
	{
		//test01();
		//test02();
		//test03();
		//test04();
		test05();
		system("pause");
	}
	
	return 0;
}