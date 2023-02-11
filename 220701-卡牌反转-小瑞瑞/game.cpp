#include "game.h"
#include "widget.h"
#include "card.h"
#include "time.hpp"

game::game():pWidget(new Widget(WIDTH*8+10*2,HEIGHT*4+10*2,"img//background.jpg"))
{
    int start = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j += 2) {
            map[i][j] = start;
            map[i][j + 1] = start;
            start++;
            /*
                0 0 1 1 2 2 3 3
                4 4 5 5 6 6 7 7
                8 8 9 9 10 10 11 11
            */
        }
    }
}

void game::initGame()
{
    //加载图片
    //批量加载
    string imgURL;
    string coverURL ="img//cover.png";
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            //根据数组中的值创建卡片
            int x = WIDTH * j + 10;
            int y = HEIGHT * i + 10;
            imgURL = "img/" + to_string(map[i][j])+".jpg";      //字符串的连接
            pCard.push_back(new card(x,y,imgURL,coverURL));
        }
    }
    pWidget->Show();    //显示窗口
}

void game::showGame()
{
    pWidget->Refresh();
    for (auto v : pCard) {
        v->show();
    }
}

int game::clickGame(ExMessage msg)
{
    for (int i = 0; i < pCard.size(); i++) {
        if (pCard[i]->clickCard(msg) == true) return i;
    }
    return -1;                  //和数组最小下标区分
}

void game::mouseEvent(ExMessage msg)
{
    if (isOpen.size() < 2) {
        int pos = clickGame(msg);
        if (pos != -1) {
            pCard[pos]->setStart(card::cardStart::open);
            isOpen.push_back(pos);
        }
    }
    if (myTime::timer(10, 0));
    {
        isClear();
    }
}

void game::isClear()
{
    if (isOpen.size() == 2) {
        if (isOpen[0] != isOpen[1] && pCard[isOpen[0]]->getURL() == pCard[isOpen[1]]->getURL()) {
            pCard[isOpen[0]]->setStart(card::cardStart::no);
            pCard[isOpen[1]]->setStart(card::cardStart::no);
        }
        else {
            
                pCard[isOpen[0]]->setStart(card::cardStart::close);
                pCard[isOpen[1]]->setStart(card::cardStart::close);
           
        }
        isOpen.clear();
    }

}

bool game::gameOver()
{
    return false;
}
