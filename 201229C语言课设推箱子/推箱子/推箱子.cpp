#include<stdio.h>                        //ͷ�ļ�
#include<conio.h>                        //�ַ�����
#include<stdlib.h>                       //system����
#include<graphics.h>                     //ͼ�ο�
#include <windows.h>
#include<mmsystem.h>                     //��������
#pragma comment(lib,"winmm.lib")         //��ý���̣��õ�winmm.lib��
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
};/*0-· 1-ǽ 3-Ŀ�ĵ� 4-���� 5&8-�� 7-���ӵ���Ŀ�ĵأ�3+4��*/
void drawmap()                          //��ӡ��ͼ
{                           
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 12; j++) {
			int x = 64 * j;           //��ͼ��Ҫ����
			int y = 57 * i;
			switch (map[i][j]) {
			case 0:                   //·
				                      //��ʾͼƬʹ�ú���putimage
				putimage(x, y, &img[0]);
				                      //printf("  ");���ӻ��в�ʹ��printf����
				break;
			case 1:                   //ǽ��
				                      //printf("��");
				putimage(x, y, &img[1]);
				break;
			case 3:                    //Ŀ�ĵ�
				                       //printf("��");
				putimage(x, y, &img[2]);
				break;
			case 4://����
				                        //printf("��");
				putimage(x, y, &img[3]);
					break; 
				case 5:
				case 8:                  //����
					                     //printf("��");
					putimage(x, y, &img[4]);
					break;
				case 7:                   //���ӵ�Ŀ�ĵ�
					                      //printf("��");
					putimage(x, y, &img[5]);
					break;
             }
		}
		printf("\n");
	}
}

void KeyDown() {                                     //�����ﶯ���������ҵ�������ƶ���
	                                                 //��λ���������
	int i, j;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 12; j++) {
			if (map[i][j] == 8 || map[i][j] == 5) {
				break;                               //ֻ��������һ��forѭ��
			}
		}
		if (map[i][j] == 8 || map[i][j] == 5) {      //����һ��
			break;
		}
	}
	
	char userkey = _getch();                           //�ҵ������Ȼ���ƶ������������
	switch (userkey)                                   //���������������
	{
	case 72:                                           //������ƶ�-����
		if (map[i - 1][j] == 0 || map[i - 1][j] == 3) {
			map[i - 1][j] += 5;
			map[i][j] -= 5;
		}
		                                               //��������
		                                               //�ƶ������ƶ���ĳ��λ�õĶ���
		if (map[i - 1][j] == 4 || map[i - 1][j] == 7) {
			if (map[i - 2][j] == 0 || map[i - 2][j] == 3)
			{
				map[i - 2][j] += 4;                    //��������
				map[i - 1][j] -= 4;                    //��������
				map[i - 1][j] += 5;                    //������
				map[i][j] -= 5;                        //������
			}
		}
		break;
	case 80:                                           //�������߼��㷨����
		if (map[i + 1][j] == 0 || map[i + 1][j] == 3) {
			map[i + 1][j] += 5;
			map[i][j] -= 5;
		}
		                                               //��������
		                                                //�ƶ������ƶ���ĳ��λ�õĶ���
		if (map[i + 1][j] == 4 || map[i + 1][j] == 7) {
			if (map[i + 2][j] == 0 || map[i + 2][j] == 3)
			{
				map[i + 2][j] += 4;                      //��������
				map[i + 1][j] -= 4;                       //��������
				map[i + 1][j] += 5;                       //������
				map[i][j] -= 5;                            //������
			}
		}
		break;
	case 75:                                              //��ͬ��
		if (map[i][j - 1] == 0 || map[i][j - 1] == 3) {
			map[i][j - 1] += 5;
			map[i][j] -= 5;
		}
		                                                  //��������
		                                                   //�ƶ������ƶ���ĳ��λ�õĶ���
		if (map[i][j - 1] == 4 || map[i][j - 1] == 7) {
			if (map[i][j - 2] == 0 || map[i][j - 2] == 3)
			{
				map[i][j - 2] += 4;                       //��������
				map[i][j - 1] -= 4;                       //��������
				map[i][j - 1] += 5;                       //������
				map[i][j] -= 5;                           //������
			}
		}
		break;
	case 77://��
		if (map[i][j + 1] == 0 || map[i][j + 1] == 3) {
			map[i][j + 1] += 5;
			map[i][j] -= 5;
		}
		                                                  //��������
		                                                  //�ƶ������ƶ���ĳ��λ�õĶ���
		if (map[i][j + 1] == 4 || map[i][j + 1] == 7) {
			if (map[i][j + 2] == 0 || map[i][j + 2] == 3)
			{
				map[i][j + 2] += 4;                       //��������
				map[i][j + 1] -= 4;                       //��������
				map[i][j + 1] += 5;                       //������
				map[i][j] -= 5;                           //������
			}
			break;
		}
	}
}
void gameover() {
	if (map[2][5]==7 && map[3][4]==7 && map[3][5]==7 && map[4][4] == 7) {
		MessageBox(NULL, "��Ӯ�����������\n����˧��΢��һ��\n����������","YOU WIN",MB_OK);
	}
}
void welcome()                         //��ʼ����̨ҳ��
{
	printf(" \n");
	printf(" \n");
	printf(" \n");
	printf(" \n");
	printf("\t<< ********\t��ӭ������������Ϸ\t******** << \n");
	printf("\t<< ********\tlove����\t\t******** << \n");
	printf("\t<< ********\t����\t\t\t******** <<\n");
	printf("\t<< ********\t����������������\t******** << \n");
	printf("\t<< ********\t��֧�ֳ�����һ��\t******** << \n");
	printf("\t<< ********\t�����ϣ�\t\t******** << \n");
	printf("\t<< ********\t�������������Ϸ\t******** << \n");
	printf("\t<< ********\t3---����˵��\t\t******** << \n");
	
}
/*void show() {
	printf("");
	printf(" \n");
	printf(" \n");
	printf(" \n");
	printf(" \n");
	printf("\t<< ********\t��ϵqq��652455342\t******** << \n");
	

}*/
	
int main()
{
        HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);//���ؿ���̨���-���δ���Ͳ�Ҫ������Ҳ����ѽ��
        CONSOLE_CURSOR_INFO cinfo;
		cinfo.bVisible = 0;
		cinfo.dwSize = 1;
        if (SetConsoleCursorInfo(a, &cinfo))
             printf("\n");
        else
			printf("\n");                                //����Ϊ�˿���̨���ںÿ���
    system("mode con cols=64 lines=20");                 //����̨��С
	system("color 0A");                                  //����̨������ɫ
	SetConsoleTitle("love---��ʦ123������");             //����̨��������
	welcome();                                           //����̨�˵�
	getch();                                             //������Ϸ
		
	closegraph();                                        //�رմ���
	mciSendString("open ��Ц������ÿ�.mp3 alias A",0,0,0);//��������
	mciSendString("play A repeat", 0, 0, 0);
	loadimage(&img[0], "0.bmp");                           //����ͼƬ;�ָ�ͼƬ�ڴ�
	loadimage(&img[1], "1.bmp");
	loadimage(&img[2], "3.bmp");
	loadimage(&img[3], "4.bmp");
	loadimage(&img[4], "5.bmp");
	loadimage(&img[5], "7.bmp");
	loadimage(&img[6], "9.bmp");
    initgraph(64*12, 57*7);                           //��װeasyx//����һ��ͼ�δ��ڣ���Ϸ����)���ӻ�����
	while (1)                                         //��Ҫ�ظ�����---ѭ��
	{
		drawmap();                                     //��������
		KeyDown();
		gameover();                                    //��Ϸ����
		system("cls");                                 //������ÿ����һ�λ��γ��µ�ҳ�棬��Ҫ����ϴε�ҳ�棩
}
	_getch();                                         //��ȡ�ַ�
	closegraph();                                     //�رտ���̨ҳ��
	return 0;

}