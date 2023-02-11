#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.08.31 12.31 love
All rigth reserved
vs2019
***********************************************************************/

//2 页码规律数字统计
//
#include <iostream>
#include <string>
#include <fstream>				//IO流
using namespace std;
#define inputPath "input.txt"			//当前所在目录 输入文件
#define outputPath "output.txt"			//当前所在目录 输出文件
//1 读取input.txt文件中的数据
//参数说明:常量 输入路径
int readDataFromFile(const string& rootPath)
{
	ifstream ifs;						//读取流对象
	ifs.open(rootPath, ios::in);		//读文件
	if (ifs.is_open() == false)			//读文件异常返回-1
	{
		cout << "READ FILE EXPERSTION" << endl;
		return -1;
	}
	int num;							//将读入数据存入num 返回
	ifs >> num;
	ifs.close();						//关闭读取流对象
	return num;
}
//2 将数组buf写到磁盘文件
//参数说明:常量输出路径 源信息数组 数组长度
void writeDataToFile(const string& rootPath, int buf[], int bufLength)
{
	ofstream ofs;									//写流对象
	ofs.open(rootPath, ios::out | ios::trunc);		//写文件方式打开文件，如果当前目录没有此文件，就创建文件
	if (ofs.is_open() == false)						//打开失败返回
	{
		cout << "OPEN FILE EXPERSION" << endl;
		return;
	}
	for (int i = 0; i < bufLength; i++)				//将程序信息读取到缓存区，然后写到文件中
	{
		ofs << buf[i];
		ofs << endl;
	}
	ofs.close();									//关闭输出流
}
//3 算法思路
//参数说明:总页码数 存储数组
//思路说明:
//n个0 - n个9  他们中0-9出现次数相同  f(n)
//n = 1 <0-9>    <个位上0-9各出现 1 次>				f(1) = 1
//n = 2 <00-99>	 <个位上0-9各出现 10*1 次>
//				 <十位上0-9各出现 10(10^n-1) 次>    f(2) = 20
//n = 3 <000-999><个位和十位上00-99各出现 10*f(2) 次>
//				 <百位上0-9各出现 100(10^n-1) 次>	f(3) = 300
//……			 ……								……
//n     <0…0-9…9><个位到次高位上0…0-9…9各出现 10*f(n - 1) 次>
//				   <最高位上0-9出现 10^(n-1) 次>   f(n) = 10*f(n-1) + 10^(n-1)

//页码数 n 的位数为 c
//页码数 n 的最高位 m
//页码数 n 除去最高位部分 r(0 - n-1)

//0 - n的三部分:
//第一部分: m 组c - 1 个 0-9 的数,这部分 0-9 出现个数相同 均为m*(c-1)10^(c-2) 次
//第二部分: 最高位 0 - m-1 出现10^(c-1) 次 m 出现 r + 1 次
//第三部分为 0（包含前导 0）到 r rr 的数，按照同样的方法进行递归，直到 r 的位数为 1，0 到r 各出现一次

//减去前导 0 

//举例n = 2222
//第一部分:		0000
//				0999				有两组000-999的数:分别是(000-999)和(1000-1999)后边这个不看最高位 一共出现 2 * 3 * 10^2
//
//第二部分:		1000				最高位0/1/2出现的次数
//				1999				0-1 一共出现 10^3次 
//									2 一共出现 222 + 1次	
//第三部分:		2000
//				2222				对222继续重复上述步骤
//
//				000
//				099
// 
//				100
//				199
// 
//				200
//				222
//									对22重复上述步骤
//				00
//				09
// 
//				10
//				19
// 
//				20
//				22
//									对2重复上述
//				00
//				02					程序结束

//求allNum的位数
int getBit(int allNum)
{
	return (int)log10(allNum) + 1;
}

int f(int allNum)
{
	if (allNum == 0)
	{
		return 1;
	}
	else
	{
		return allNum * (int)pow(10.0, allNum - 1);
	}
}
void function(int allNum, int buf[])
{
	//求总页数的位数c,c - 1个0 到 c - 1个9 中0 - 9 出现次数相同
	int c = getBit(allNum);
	if (c == 1)
	{
		for (int i = 0; i <= allNum; i++)
		{
			buf[i]++;
		}
		return;
	}
	//求总页码数的最高位m，共有 m 组 c-1 个 0-9 的数
	int m = allNum / (int)pow(10.0, c - 1);
	int r = allNum % (int)pow(10.0, c - 1);
	//m 组 c- 1 个 0-9 出现次数
	for (int i = 0; i <= 9; i++)
	{
		buf[i] += m * f(c - 1);
	}
	//次高位
	for (int i = 0; i < m; i++)
	{
		buf[i] += (int)pow(10.0, c - 1);
	}
	buf[m] += r + 1;
	//如果r的位数不是c - 1 ,说明allNum 中间有0，需要补0
	int cr = getBit(r);
	if (cr != c - 1)
	{
		buf[0] += (c - cr - 1) * (r + 1);
	}
	//递归处理r 1中 0-9出现的次数
	function(r, buf);
}

void subStract(int allNum, int buf[])
{
	int c = getBit(allNum);
	for (int i = 0; i < c; i++)
	{
		buf[0] -= (int)pow(10.0, i);
	}
}
//输出到屏幕
//输出文件路径
void outDataToCur(const string& rootPath)
{
	ifstream ifs;
	ifs.open(rootPath, ios::in);
	if (ifs.is_open() == false)
	{
		cout << "FILE OPEN ERROR" << endl;
	}
	char buf[1024] = { 0 };
	int count = -1; //计数器
	while (!ifs.eof())		//判断文件是否是末尾
	{

		ifs.getline(buf, sizeof(buf));	//按行读取文件不包含换行符号
		cout << buf << endl;			//打印到屏幕
	}
}

void yeMaGuiLvTest()
{
	int buf[10] = { 0 };
	//int data = readDataFromFile(inputPath);
	function(readDataFromFile(inputPath), buf);
	subStract(readDataFromFile(inputPath), buf);
	writeDataToFile(outputPath, buf, sizeof(buf) / sizeof(int));
	outDataToCur(outputPath);
}
int main()
{
	yeMaGuiLvTest();
	system("pause");		//暂停防止程序意外结束
	return 0;
}


