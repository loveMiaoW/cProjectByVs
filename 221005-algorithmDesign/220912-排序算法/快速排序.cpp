#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.09.14 09.35 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream>
#include <ctime>
using namespace std;
const int number = 13;
int count = 0;	//全局变量，记录次数

void myPrint(int a[])
{
    //cout << "第" << ++::count << "次交换，";
	cout << "数组数据: ";
	
	for (int i = 0; i < number; ++i)
	{
		cout << a[i] << "\t";
	}
    cout << endl << endl;
}
void swap(int* a,int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//快速排序
int partition(int a[], int left, int right)
{
    int i, j, t, temp;
    temp = a[left]; ///temp中存的就是基准数
    i = left;
    j = right;
    while (true)
    {
        while (a[j] >= temp && i < j)///顺序很重要，要先从右边开始找
        {
            j--;
        }
        while (a[i] <= temp && i < j)///再找左边的
        {
            i++;
        }
        if (i >= j)
        {
            break;
        }

        swap(&a[i], &a[j]);
      /* cout << "---------------------------------------" << endl<<"\t";
        myPrint(a);
        cout << "---------------------------------------" << endl;*/
    }
    a[left] = a[i]; ///最终将基准数归位
    a[i] = temp;
    cout << "确定的元素是: " << a[i] <<" 所在位置: "<< i << endl;
    return i;
}
void quickSort(int a[],int left, int right)
{
    if (left < right)
    {
        int q = partition(a,left, right);
        myPrint(a);
        quickSort(a,left, q - 1);///继续处理左边的，这里是一个递归的过程
        quickSort(a,q + 1, right);///继续处理右边的 ，这里是一个递归的过程
    }
}
void test01()
{
	int a[] = { 49,38,65,97,76,13,27,49,10,21,8,9,-3 };
    cout << "数组初始值" << endl;
    myPrint(a);
	quickSort(a, 0, sizeof(a) / sizeof(int) - 1);
}

int main(int argc,char** argv)
{
	time_t start, end;
	start = clock();
	test01();
	end = clock();

	cout << "using time:" << (double)(end - start) << "ms" << endl;
	system("pause");
	return 0;
}




