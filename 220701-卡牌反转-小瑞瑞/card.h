#pragma once
#include "myHead.h"
class card {
public:
	enum class cardStart{close,open,no};//ö�ٳ���Ƭ״̬
	card(int x, int y, string imgURL, string imgyURL);
	void setStart(cardStart state);		//�ӿ�����״̬
	bool mouseInCard(ExMessage msg);
	bool clickCard(ExMessage msg);
	string getURL();
	void show();
	

protected:
	int x;
	int y;
	int width = WIDTH;
	int height = HEIGHT;
	string imgURL;
	string imgyURL;
	IMAGE* img;
	cardStart start;
};

