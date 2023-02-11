#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.08.31 11.31 love
All rigth reserved
vs2019
***********************************************************************/

//1 暴力数字统计
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
	//cout << rootPath << endl;			//调试
	//system("pause");
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
void writeDataToFile(const string& rootPath, int buf[],int bufLength)
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
//3 解决问题函数
//参数说明:总页码数 存储数组
void function(int allNum,int buf[])
{
	//爆破
	for (int i = 0; i <= allNum; i++)
	{
		int tmp = i;
		while (tmp)
		{
			buf[tmp % 10]++;
			tmp /= 10;
		}
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
void baoLiAcTest()
{
	int buf[10] = { 0 };
	//int data = readDataFromFile(inputPath);
	function(readDataFromFile(inputPath), buf);
	writeDataToFile(outputPath, buf, sizeof(buf) / sizeof(int));
	outDataToCur(outputPath);
}
int main()
{
	baoLiAcTest();
	system("pause");		//暂停防止程序意外结束
	return 0;
}


