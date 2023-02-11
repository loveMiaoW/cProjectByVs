#include "widget.h"
Widget::Widget(int width, int height, string imgURL)
{
	this->width = width;
	this->height = height;
	this->imgURL = imgURL;
	if (imgURL.size() != 0) {
		img = new IMAGE;
		loadimage(img, imgURL.c_str(),width,height);
	}
}

void Widget::Show()
{
	initgraph(this->width, this->height);
	if (imgURL.size() != 0) {
		putimage(0, 0, img);
	}
}

void Widget::Refresh()
{
	if (imgURL.size() == 0) {
		cleardevice;
	}
	else {
		putimage(0, 0, img);
	}
}

Widget::~Widget()
{
	delete[] img;
}
