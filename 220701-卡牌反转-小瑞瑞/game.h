#pragma once
#include "myHead.h"
class Widget;	/*������ ���ںͿ�Ƭ��*/
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
	//��ά�����ʾmap
	//���ڱ�ʾ
	//4*8��Ƭ
	//״̬�л�
	//ÿ��ֻ�ܴ�����ͼƬ
	//û�㿪һ�ν���ǰ�򿪵Ĵ�ŵ�һ��������
	array<array<int, 8>, 4> map;	//�ȼ���int map[4][8]
	Widget* pWidget;
	vector<card*> pCard;			//card pCard[x];
	vector<int> isOpen;				//int isOpen[x];

};