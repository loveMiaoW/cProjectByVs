#pragma once
#include "myHead.h"
//��������Ĺ�ͬ����
class Widget {
public :
	Widget(int width,int height,string imgURL="");
	void Show();
	void Refresh();
	~Widget();/*�������� ���һ����Ա���� ��~+�������� ִ�к͹��캯���෴�Ĳ��� �ͷŶ�����Դ ���������еķ�static��Ա*/
				/*�޲������޷���ֵ �������� ��һ�ι��캯������ �ͻ����һ����������*/
	

	protected:
		int width;		//���ڵĿ��
		int height;		//���ڵĸ߶�
		IMAGE* img;		//���������Ƿ��ͼƬ
		string imgURL;	//ͼƬ·��
};