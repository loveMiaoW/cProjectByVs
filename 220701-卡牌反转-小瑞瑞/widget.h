#pragma once
#include "myHead.h"
//抽象事物的共同特性
class Widget {
public :
	Widget(int width,int height,string imgURL="");
	void Show();
	void Refresh();
	~Widget();/*析构函数 类的一个成员函数 由~+类名构成 执行和构造函数相反的操作 释放对象资源 并销毁所有的非static成员*/
				/*无参数且无返回值 不能重载 有一次构造函数调用 就会调用一次析构函数*/
	

	protected:
		int width;		//窗口的宽度
		int height;		//窗口的高度
		IMAGE* img;		//创建窗口是否带图片
		string imgURL;	//图片路径
};