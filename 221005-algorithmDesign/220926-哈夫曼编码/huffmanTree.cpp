#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Copyright(c) 2022.09.28 0956 MRLIU
All rigth reserved
vs2019
源码:https://gitee.com/loveMiaoW/vs_project.git
***********************************************************************/
#include <iostream>
#include <ctime>
using namespace std;


//class minHeap {
//public:
//	minHeap(int capacty);
//	~minHeap();
//	int getParent(int i);
//	int getLeftChild(int i);
//	int getRightChild(int i);
//	bool isEmpty();
//	int getRoot();
//	void pushBack(int ele);
//	int pop();
//	void swap(int i,int j);
//	int heapify(int k);
//public:
//	int* huffmanPtr;
//	int capacity;
//	int heapSize;
//};
//
//
//minHeap::minHeap(int capacty)
//{
//	this->heapSize = 0;
//	this->capacity = capacity;
//	huffmanPtr = new int[capacity];
//}
//
//int minHeap::getParent(int i)
//{
//	return (i / 2 - 1);
//}
//
//int minHeap::getLeftChild(int i)
//{
//	return (i * 2 + 1);
//}
//
//int minHeap::getRightChild(int i) 
//{
//	return (i * 2 + 2);
//}
//
//bool minHeap::isEmpty()
//{
//	return heapSize > 0;
//}
//
//int minHeap::getRoot()
//{
//	return huffmanPtr[0];
//}
//
//void minHeap::swap(int i,int j)
//{
//	int tmp = huffmanPtr[i];
//	huffmanPtr[i] = huffmanPtr[j];
//	huffmanPtr[j] = tmp;
//}
//void minHeap::pushBack(int ele)
//{
//	if (heapSize == capacity)
//	{
//		cout << "heap is full" << endl;
//		return;
//	}
//	heapSize++;
//	int i = heapSize - 1;
//	huffmanPtr[i] = ele;
//	while (i != 0 && huffmanPtr[getParent(i)] > huffmanPtr[i]) {
//		swap(i, getParent(i));
//		i = getParent(i);
//	}
//
//}
//int minHeap::heapify(int k)
//{
//
//}
//
//int minHeap::pop()
//{
//	if (heapSize <= 0)
//	{
//		return;
//	}
//	if (heapSize == 1)
//	{
//		heapSize--;
//		return huffmanPtr[0];
//	}
//	huffmanPtr[0] = huffmanPtr[heapSize - 1];
//	heapSize--;
//	heapify(0);
//}
//
//int minHeap::heapify(int k)
//{
//	int left = getLeftChild(k);
//	int right = getRightChild(k);
//	int smallest = k;
//	if (left < heapSize && huffmanPtr[left] < huffmanPtr[smallest])
//		smallest = left;
//	if (right < heapSize && huffmanPtr[right] < huffmanPtr[smallest])
//		smallest = right;
//	if (smallest != k) {
//		swap(k, smallest);
//		heapify(smallest);
//	}
//}
//int main()
//{
//	int arr[8] = { 53,17,78,9,45,65,87,23 };
//	minHeap hp(8);
//	for (int i = 0; i < 8; i++)
//	{
//		hp.pushBack(arr[i]);
//	}
//
//	for (int i = 0; i < 8; i++)
//	{
//		cout << hp(i) << " ";
//	}
//
//	return 0;
//}
//
//

class huffmanTree {

};
typedef struct
{
	int data;
	int parent;
	int lchild, rchild;
}HTNode,* HuffmanTree;


void selectEle(HuffmanTree H, int i, int& s1, int& s2)
{
	int n = 1;
	int j = 1;
	int z;
	while (j <= 2)
	{
		n = 1;
		while (H[n].parent != 0)
		{
			n++;
		}
		z = n;
		while (n < i)
		{
			n = n + 1;
			if (H[n].parent == 0)
			{
				if (H[z].data > H[n].data)
				{
					z = n;
				}
			}
		}
		if (j == 1)
		{
			s1 = z;
			H[s1].parent = 1;
			j++;
		}
		else
		{
			s2 = z;
			j++;
		}

	}
}

void createHuffmanTree(HuffmanTree& H, int n)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1; //赫夫曼共有这么多结点
	H = new HTNode[m + 1];
	int i;

	for (i = 1; i <= m; i++)
	{
		H[i].parent = 0;
		H[i].lchild = 0;
		H[i].rchild = 0;
	}
	i = 1;
	while (i <= n)
	{
		cin >> H[i].data;
		i++;
	}
	int j = n;
	int s1, s2;
	for (i = n + 1; i <= m; ++i)
	{
		selectEle(H, i - 1, s1, s2);
		H[s1].parent = i;
		H[s2].parent = i;
		H[i].lchild = s1;
		H[i].rchild = s2;
		H[i].data = H[s1].data + H[s2].data;
	}

}

void HuffmanTreeCode(HuffmanTree H, int n)
{
	char** c = new char*[n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new char[n];
	}
	
	char* ch = new char[n];
	int i = 1;
	int j, f, k = 0;
	int z, m;
	for (i = 1; i <= n; ++i)
	{
		j = i;
		f = H[i].parent;

		k = 0;
		while (f != 0)
		{
			if (H[f].lchild == j)
			{
				ch[k] = '0';
				k++;
			}
			else
			{
				ch[k] = '1';
				k++;
			}
			j = f;
			f = H[f].parent;


		}
		ch[k] = '\0';

		z = strlen(ch);

		int u = 0;
		for (m = z - 1; m >= 0; m--)
		{
			c[i - 1][u] = ch[m];
			u++;

		}
		c[i - 1][u] = '\0';

	}
	i = 0;

	while (i <= 7)
	{
		j = 0;
		cout << "第" << i + 1 << "个字符的编码是  :";
		while (c[i][j] != '\0')
		{

			cout << c[i][j];
			j++;
		}
		i++;
		cout << endl;
	}
}

int main()
{
	HuffmanTree H;
	int n;
	n = 8;
	createHuffmanTree(H, n);
	HuffmanTreeCode(H, n);
	return 0;
}

















