#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.09.06 10.34 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream>
#include <ctime>

using namespace std;

int fibonacci(int n)
{
	if (n <= 2)
	{
		return 1;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}

void test01()
{
	int num;
	cin >> num;
	time_t start, end;
	start = clock();
	cout << num << " 的斐波那契数是：" << fibonacci(num) << endl;
	end = clock();
	cout << "   using time is: " << (double)(end - start) << " ms" << endl;
}
int main()
{
	while (1)
	{
		cout << "---------------test01 begin...-----------" << endl;
		cout << endl;
		test01();
		cout << endl;
		cout << "---------------test01 end.-----------------" << endl;
		system("pause");
	}
	
	return 0;
}