#pragma once
#include "myHead.h"
class Widget;	/*包含进 窗口和卡片类*/
class card;

class game {
public:
	game();
	void initGame();
	void showGame();
	int clickGame(ExMessage msg);
	void mouseEvent(ExMessage msg);
	void isClear();
	bool gameOver();

protected:
	//二维数组表示map
	//窗口表示
	//4*8卡片
	//状态切换
	//每次只能打开两个图片
	//没点开一次将当前打开的存放到一个容器中
	array<array<int, 8>, 4> map;	//等价于int map[4][8]
	Widget* pWidget;
	vector<card*> pCard;			//card pCard[x];
	vector<int> isOpen;				//int isOpen[x];

};