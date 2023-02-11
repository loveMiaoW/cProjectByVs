#include<stdio.h>                        //头文件
#include<conio.h>                        //字符交换
#include<stdlib.h>                       //system函数
#include<graphics.h>                     //图形库
#include <windows.h>
#include<mmsystem.h>                     //播放音乐
#pragma comment(lib,"winmm.lib")         //多媒体编程，用到winmm.lib库
IMAGE img[7];
int map[7][12]
{
{ 9,9,1,1,1,1,1,9,9,9,9,9 },
{ 9,9,1,0,0,0,1,1,1,1,1,1 },
{ 1,1,1,4,1,3,0,0,0,0,0,1 },
{ 1,0,4,0,3,3,3,1,0,4,0,1 },
{ 1,5,0,4,3,1,7,4,0,0,0,1 },
{ 1,1,1,1,0,0,0,0,1,1,1,1 },
{ 9,9,9,1,1,1,1,1,1,9,9,9 },
};/*0-路 1-墙 3-目的地 4-箱子 5&8-人 7-箱子到达目的地（3+4）*/
void drawmap()                          //打印地图
{                           
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 12; j++) {
			int x = 64 * j;           //贴图需要坐标
			int y = 57 * i;
			switch (map[i][j]) {
			case 0:                   //路
				                      //显示图片使用函数putimage
				putimage(x, y, &img[0]);
				                      //printf("  ");可视化中不使用printf函数
				break;
			case 1:                   //墙壁
				                      //printf("■");
				putimage(x, y, &img[1]);
				break;
			case 3:                    //目的地
				                       //printf("☆");
				putimage(x, y, &img[2]);
				break;
			case 4://箱子
				                        //printf("□");
				putimage(x, y, &img[3]);
					break; 
				case 5:
				case 8:                  //人物
					                     //printf("▲");
					putimage(x, y, &img[4]);
					break;
				case 7:                   //箱子到目的地
					                      //printf("▲");
					putimage(x, y, &img[5]);
					break;
             }
		}
		printf("\n");
	}
}

void KeyDown() {                                     //让人物动起来（先找到人物，在移动）
	                                                 //定位人物，遍历找
	int i, j;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 12; j++) {
			if (map[i][j] == 8 || map[i][j] == 5) {
				break;                               //只能跳出第一层for循环
			}
		}
		if (map[i][j] == 8 || map[i][j] == 5) {      //再跳一次
			break;
		}
	}
	
	char userkey = _getch();                           //找到了人物，然后移动人物，按键操作
	switch (userkey)                                   //人物操作按键输入
	{
	case 72:                                           //人物的移动-向上
		if (map[i - 1][j] == 0 || map[i - 1][j] == 3) {
			map[i - 1][j] += 5;
			map[i][j] -= 5;
		}
		                                               //人推箱子
		                                               //推动箱子移动到某个位置的对象
		if (map[i - 1][j] == 4 || map[i - 1][j] == 7) {
			if (map[i - 2][j] == 0 || map[i - 2][j] == 3)
			{
				map[i - 2][j] += 4;                    //箱子来了
				map[i - 1][j] -= 4;                    //箱子走了
				map[i - 1][j] += 5;                    //人来了
				map[i][j] -= 5;                        //人走了
			}
		}
		break;
	case 80:                                           //往下走逻辑算法不变
		if (map[i + 1][j] == 0 || map[i + 1][j] == 3) {
			map[i + 1][j] += 5;
			map[i][j] -= 5;
		}
		                                               //人推箱子
		                                                //推动箱子移动到某个位置的对象
		if (map[i + 1][j] == 4 || map[i + 1][j] == 7) {
			if (map[i + 2][j] == 0 || map[i + 2][j] == 3)
			{
				map[i + 2][j] += 4;                      //箱子来了
				map[i + 1][j] -= 4;                       //箱子走了
				map[i + 1][j] += 5;                       //人来了
				map[i][j] -= 5;                            //人走了
			}
		}
		break;
	case 75:                                              //左同上
		if (map[i][j - 1] == 0 || map[i][j - 1] == 3) {
			map[i][j - 1] += 5;
			map[i][j] -= 5;
		}
		                                                  //人推箱子
		                                                   //推动箱子移动到某个位置的对象
		if (map[i][j - 1] == 4 || map[i][j - 1] == 7) {
			if (map[i][j - 2] == 0 || map[i][j - 2] == 3)
			{
				map[i][j - 2] += 4;                       //箱子来了
				map[i][j - 1] -= 4;                       //箱子走了
				map[i][j - 1] += 5;                       //人来了
				map[i][j] -= 5;                           //人走了
			}
		}
		break;
	case 77://右
		if (map[i][j + 1] == 0 || map[i][j + 1] == 3) {
			map[i][j + 1] += 5;
			map[i][j] -= 5;
		}
		                                                  //人推箱子
		                                                  //推动箱子移动到某个位置的对象
		if (map[i][j + 1] == 4 || map[i][j + 1] == 7) {
			if (map[i][j + 2] == 0 || map[i][j + 2] == 3)
			{
				map[i][j + 2] += 4;                       //箱子来了
				map[i][j + 1] -= 4;                       //箱子走了
				map[i][j + 1] += 5;                       //人来了
				map[i][j] -= 5;                           //人走了
			}
			break;
		}
	}
}
void gameover() {
	if (map[2][5]==7 && map[3][4]==7 && map[3][5]==7 && map[4][4] == 7) {
		MessageBox(NULL, "你赢了真棒！！！\n奖励帅哥微信一个\n哈哈哈啊哈","YOU WIN",MB_OK);
	}
}
void welcome()                         //初始控制台页面
{
	printf(" \n");
	printf(" \n");
	printf(" \n");
	printf(" \n");
	printf("\t<< ********\t欢迎来到推箱子游戏\t******** << \n");
	printf("\t<< ********\tlove制作\t\t******** << \n");
	printf("\t<< ********\t破晓\t\t\t******** <<\n");
	printf("\t<< ********\t键盘输入上下左右\t******** << \n");
	printf("\t<< ********\t不支持撤回上一步\t******** << \n");
	printf("\t<< ********\t加油呦！\t\t******** << \n");
	printf("\t<< ********\t按任意键进入游戏\t******** << \n");
	printf("\t<< ********\t3---开发说明\t\t******** << \n");
	
}
/*void show() {
	printf("");
	printf(" \n");
	printf(" \n");
	printf(" \n");
	printf(" \n");
	printf("\t<< ********\t联系qq：652455342\t******** << \n");
	

}*/
	
int main()
{
        HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);//隐藏控制台光标-本段代码就不要问啦问也不会呀！
        CONSOLE_CURSOR_INFO cinfo;
		cinfo.bVisible = 0;
		cinfo.dwSize = 1;
        if (SetConsoleCursorInfo(a, &cinfo))
             printf("\n");
        else
			printf("\n");                                //单纯为了控制台窗口好看！
    system("mode con cols=64 lines=20");                 //控制台大小
	system("color 0A");                                  //控制台字体颜色
	SetConsoleTitle("love---大师123推箱子");             //控制台窗口名字
	welcome();                                           //控制台菜单
	getch();                                             //进入游戏
		
	closegraph();                                        //关闭窗口
	mciSendString("open 你笑起来真好看.mp3 alias A",0,0,0);//播放音乐
	mciSendString("play A repeat", 0, 0, 0);
	loadimage(&img[0], "0.bmp");                           //加载图片;分给图片内存
	loadimage(&img[1], "1.bmp");
	loadimage(&img[2], "3.bmp");
	loadimage(&img[3], "4.bmp");
	loadimage(&img[4], "5.bmp");
	loadimage(&img[5], "7.bmp");
	loadimage(&img[6], "9.bmp");
    initgraph(64*12, 57*7);                           //安装easyx//创建一个图形窗口（游戏窗口)可视化操作
	while (1)                                         //需要重复调用---循环
	{
		drawmap();                                     //函数调用
		KeyDown();
		gameover();                                    //游戏结束
		system("cls");                                 //清屏（每操作一次会形成新的页面，需要清除上次的页面）
}
	_getch();                                         //获取字符
	closegraph();                                     //关闭控制台页面
	return 0;

}