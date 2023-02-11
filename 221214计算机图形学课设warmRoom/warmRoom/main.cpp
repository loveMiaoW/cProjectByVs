#define GLUT_DISABLE_ATEXIT_HACK
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include "GLAUX.H"
#include "glut.h"
#include <iostream>
#include <windows.h>
#include <ctime>  
#include "windows.h"
#include "mmsystem.h"

const double PI = acos(-1);
static GLuint textureVector[100];			//存放纹理其他全局纹理数组，存储位图转换得到的纹理
static GLuint color[3];				//存放纹理颜色

static double Ox = 0;				//漫游的全局位置变量
static double Oy = 0;
static double Oz = 0;

static double direction = 0;			//站立位置及前进方向；
static double step = 0.4;				//移动的单位
static GLfloat spin = 0.0;				//用于地球旋转的全局变量

bool light = false;						//灯光标志
bool rolate = false;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//***************************************************^^^**********************************************************//
//*********************************************<__音乐效果__>*****************************************************//
//***************************************************  ***********************************************************//
void bgm() {
	MCI_OPEN_PARMS op;
	op.dwCallback = NULL;
	op.lpstrAlias = NULL;
	op.lpstrDeviceType = L"MPEGAudio";			//mp3格式
	op.lpstrElementName = L"res/loveHome.wav";			//文件名
	op.wDeviceID = NULL;
	MCI_PLAY_PARMS pp;							//
	pp.dwCallback = NULL;
	pp.dwFrom = 0;								//文件开头

	UINT rs;
	rs = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&op);

	if (rs == 0)
	{
		MCI_PLAY_PARMS pp;
		pp.dwCallback = NULL;
		pp.dwFrom = 0;
		//设备ID 播放 
		mciSendCommand(op.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&pp);
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//***************************************************^^^**********************************************************//
//*********************************************<__装载纹理图__>***************************************************//
//***************************************************  ***********************************************************//
void loadTexture(const char* filename, GLuint& texture)// 根据位图文件的名称进行加载

{
	static GLint    ImageWidth;
	static GLint    ImageHeight;
	static GLint    PixelLength;
	static GLubyte* PixelData;
	// 打开文件
	FILE* pFile = fopen(filename, "rb"); // 文件指针
	if (pFile == 0)  // 如果没有指定位图文件名称就退出
		exit(0);
	// 读取24位bmp图象的大小信息
	fseek(pFile, 0x0012, SEEK_SET);//文件指针指向文件的开头图象的宽度和高度都是一个32位整数，在文件中的地址分别为0x0012和0x0016，于是我们可以使用以下代码来读取图象的大小信息：移动到0x0016位置
	// 由于上一句执行后本就应该在0x0016位置
	fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);//把文件内的宽度数据存放给imagewidth
	fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);
	PixelLength = ImageWidth * 3;	// 计算像素数据长度
	while (PixelLength % 4 != 0)	//bmp图像保证数据区域的长度是4的倍数,满足对齐规则要求每行的数据的长度必须是4的倍数，如果不够需要进行比特填充（以0填充），这样可以达到按行的快速存取。
		++PixelLength;//否则则读取数据过慢
	PixelLength *= ImageHeight;
	// 读取像素数据
	PixelData = (GLubyte*)malloc(PixelLength);	//动态配置缓存
	if (PixelData == 0)	exit(0);
	fseek(pFile, 0, SEEK_SET);
	fread(PixelData, PixelLength, 1, pFile);
	// 关闭文件
	fclose(pFile);
	//加载纹理
	glGenTextures(1, &texture);//用来生成纹理的数量   存储纹理索引的第一个元素指针

	glBindTexture(GL_TEXTURE_2D, texture);//绑定（指定）纹理对象将生成的纹理的名称绑定到指定的纹理上
	//纹理的定义函数
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	//
	//纹理的控制函数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);		//纹理过滤函数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //多个像素对一个纹素
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	//生成一个2D纹理（Texture）。bmp图片的像素顺序是BGR所以用GL_BGR_EXT来反向加载数据
}
//室内光照
void lightinit(double x, double y)
{
	//材质反光性设置
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
	GLfloat mat_shininess[] = { 50.0 };               //高光指数
	GLfloat light_position[] = { Ox, Oy, Oz - 10, 1.0 };//灯位置(1,1,1), 最后1-开关
	GLfloat white_light[] = { 1, 1, 1, 1.0 };
	GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; //环境光参数
	//环境反射光，漫反射光，镜面反射光
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//光源位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光

	//光照材质
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

	if (light) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//触发事件/
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//只用纹理,这里用GL_MODULATE,GL_DECAL和GL_BLEND
	}
	glEnable(GL_LIGHTING);   //开关:使用光
	glEnable(GL_LIGHT0);     //打开0#灯
	glEnable(GL_DEPTH_TEST); //打开深度测试
}

//地球旋转
void spinDisplay(void)
{
	std::cout << "spin" << spin << std::endl;
	spin = spin + 0.08;
	if (spin > 360.0)
	{
		spin = spin - 360.0;
	}
	glutPostRedisplay();//glutPostRedisplay 标记当前窗口需要重新绘制。通过glutMainLoop下一次循环时，窗口显示将被回调以重新显示窗口的正常面板
}

//初始化
GLUquadricObj* g_text;//曲面，制作一个包围房间的大球体做背景
void init(void)

{
	srand(unsigned(time(nullptr)));//产生不变的随机数
	glClearColor(0.0, 0.0, 0.0, 0.0);//清除颜色缓冲区，设置颜色
	glShadeModel(GL_FLAT);//设置着色模式 GL_FLAT 恒定着色，GL_SMOOTH光滑着色

	g_text = gluNewQuadric();//做月球地球这句代码需放置在绘图及显示之前定义新的二次曲面对象
	//装载位图
	loadTexture("res/red.bmp", color[0]);
	loadTexture("res/blue.bmp", color[1]);
	loadTexture("res/black.bmp", color[2]);
	loadTexture("res/wall.bmp", textureVector[0]);
	loadTexture("res/earth.bmp", textureVector[1]);
	loadTexture("res/sky.bmp", textureVector[2]);
	loadTexture("res/floor.bmp", textureVector[3]);
	loadTexture("res/bottom.bmp", textureVector[4]);
	loadTexture("res/windows.bmp", textureVector[5]);
	loadTexture("res/theGirlFir.bmp", textureVector[6]);
	loadTexture("res/theGirlSec.bmp", textureVector[7]);
	loadTexture("res/theGirlTir.bmp", textureVector[8]);
	loadTexture("res/richMan.bmp", textureVector[9]);
	loadTexture("res/bedSidePho.bmp", textureVector[10]);
	loadTexture("res/mod.bmp", textureVector[11]);
	loadTexture("res/beizi.bmp", textureVector[12]);
	loadTexture("res/zt.bmp", textureVector[13]);
	loadTexture("res/lak.bmp", textureVector[14]);
	loadTexture("res/roomBiZhiFir.bmp", textureVector[15]);
	loadTexture("res/roomBiZhiSec.bmp", textureVector[16]);

}

//贴图函数
//左右面
void mapLeftAndRight(float m, float n, float x, float y1, float y2, float z1, float z2) {

	glBegin(GL_QUADS);//纹理对应平面
	glTexCoord2f(0.0, 0.0); glVertex3f(x, y1, z1);
	glTexCoord2f(0.0, n); glVertex3f(x, y1, z2);
	glTexCoord2f(m, n); glVertex3f(x, y2, z2);
	glTexCoord2f(m, 0.0); glVertex3f(x, y2, z1);
	glEnd();
}
//前后面
void mapBeforeAndBack(float m, float n, float x1, float x2, float y, float z1, float z2) {

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(x1, y, z1);
	glTexCoord2f(0.0, n); glVertex3f(x1, y, z2);
	glTexCoord2f(m, n); glVertex3f(x2, y, z2);
	glTexCoord2f(m, 0.0); glVertex3f(x2, y, z1);
	glEnd();
}
//上下面
void mapUpAndDown(float m, float n, float x1, float x2, float y1, float y2, float z) {

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(x1, y1, z);
	glTexCoord2f(0.0, n); glVertex3f(x1, y2, z);
	glTexCoord2f(m, n); glVertex3f(x2, y2, z);
	glTexCoord2f(m, 0.0); glVertex3f(x2, y1, z);
	glEnd();
}
//--------------------------------------------------------------------------------------------------------------


//---------------------------------------------菜单响应制作-----------------------------------------------------
#define START 1
int flag = 1;
//当点击菜单时,调用回调函数 func，value 为传递给回调函数的数值,它由所选择的菜单条目对应 的整数值所决定。
void processMenuEvents(int option)
{
	//option，就是传递过来的 value 的值。
	switch (option) {
	case START:
		bgm();
		break;
	}
}

void createGLUTMenus()
{
	int menu;
	// 创建菜单并告诉 GLUT，processMenuEvents 处理菜单事件。
	menu = glutCreateMenu(processMenuEvents);
	//给菜单增加条目
	glutAddMenuEntry("哎呦~", START);
	// 把菜单和鼠标右键关联起来。
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//-----------------------------------------------------------------------------------------------------------------
void tip() {
	std::cout << std::endl
		<< "         _       __  ______  __     ______  ____    __  ___  ______              " << std::endl
		<< "        | |     / / / ____/ / /    / ____/ / __ \\  /  |/  / / ____/             " << std::endl
		<< "        | | /| / / / __/   / /    / /     / / / / / /|_/ / / __/                 " << std::endl
		<< "        | |/ |/ / / /___  / /___ / /___  / /_/ / / /  / / / /___                 " << std::endl
		<< "        |__/|__/ /_____/ /_____/ \\____/  \\____/ /_/  /_/ /_____/               " << std::endl << std::endl;
	std::cout << "  ///////////////////////////////////////////////////////////////////////////////" << std::endl
		<< "  ///**************************** Welcom to OurRoom! ************************////" << std::endl
		<< "  ///**************************** Copyright by LIU **************************////" << std::endl
		<< "  ///**************************** makeBy:loveMiaoW **************************////" << std::endl
		<< "  ///**************************** email:LIU_RUI@163.com *********************////" << std::endl
		<< "  ///****************************** 操作说明 ********************************////" << std::endl
		<< "  ///**************************** 按键 A 更改光线强度  **********************////" << std::endl
		<< "  ///**************************** 空格 space 旋转  **************************////" << std::endl
		<< "  ///**************************** 鼠标右键播放音乐 **************************////" << std::endl
		<< "  ///**************************** 上下键前进后退，左右键转头，WS上升下降 ****////" << std::endl
		<< "  ///********* 项目地址: https://github.com/loveMiaoW/loveMiaoW.git *********////" << std::endl
		<< "  ///////////////////////////////////////////////////////////////////////////////" << std::endl << std::endl;

	std::cout
		<< "	//////////////////////////////////////////////////////////////////" << std::endl
		<< "	///                    _ooOoo_                                 ///" << std::endl
		<< "	///                   o8888888o                                ///" << std::endl
		<< "	///                    88 . 88                                 ///" << std::endl
		<< "	///                  (| ^ _ ^ | )                              ///" << std::endl
		<< "	///                    O = / O                                 ///" << std::endl
		<< "	///                ____ / `---'____                            ///" << std::endl
		<< "	///               .'  \|     |//  `.|                          ///" << std::endl
		<< "	///               / \|||  :  |||//| |                             " << std::endl
		<< "	///              / _||||| -:-|||||_-                           ///" << std::endl
		<< "	///              |   | \ -  /// |   |                             " << std::endl
		<< "	///             | _ | ''-- - / ''  |   |                       ///" << std::endl
		<< "	///             . - __  `-`  ___ / -. /                        ///" << std::endl
		<< "	///            ___`. .'  /--.--  `. . ___                      ///" << std::endl
		<< "	///          ."" '<  `.____<|>_/___.'  > '" ".                    " << std::endl
		<< "	///        | | :  `- `.; ` _ / `;.`/ - ` : | |                 ///" << std::endl
		<< "	///            `-._ __ / __ _ / . - ` /  /                     ///" << std::endl
		<< "	/// ========`-.____`-.________ / ___. - `____. - '========     ///" << std::endl
		<< "	///                     `=-- -='                               ///" << std::endl
		<< "	///  ^ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        ///" << std::endl
		<< "	///       ^ 佛祖保佑       永不宕机       永无BUG ^            ///" << std::endl
		<< "	///  ^ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        ///" << std::endl
		<< "	//////////////////////////////////////////////////////////////////" << std::endl;
}
//-----------------------------------------------------------------------------------------------------------------

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色缓冲以及深度缓
	glEnable(GL_TEXTURE_2D);
	//二次曲面的纹理映射,制作曲面地球
	gluQuadricTexture(g_text, GLU_TRUE);              //建立纹理坐标 使用纹理确认
	gluQuadricDrawStyle(g_text, GLU_FILL);            //用面填充  实体
	glPushMatrix();//2
	glRotatef((GLfloat)direction, 0.0, 0.0, 1.0);//回调函数后，键盘交互完会影响后两行,改变地球旋转
	glTranslated(Ox - 18, Oy - 18, Oz);
	glPushMatrix();//4

	glRotatef(spin * 3, 0.0, 0.0, 1.0);//让月球转起来

	glBindTexture(GL_TEXTURE_2D, textureVector[1]);
	gluSphere(g_text, 60, 3600, 3600);//地球
	glBindTexture(GL_TEXTURE_2D, textureVector[2]);
	gluSphere(g_text, 55, 3600, 3600);

	//光照压栈
	//-------以下代码删除----光线增强
	glPushMatrix();//7
	lightinit(Ox, Oy);
	glPopMatrix();//7

	glPopMatrix();//4

	//
	glBindTexture(GL_TEXTURE_2D, textureVector[0]);
	//右边墙
	mapLeftAndRight(3.0, 1.0, -20.0, -20.0, 20.0, 0.0, 10.0);
	//左边墙
	mapLeftAndRight(3.0, 1.0, 20.0, -20.0, 20.0, 0.0, 10.0);
	//前方墙壁
	mapBeforeAndBack(3.0, 1.0, -20.0, 20.0, -20.0, 0.0, 10.0);
	//后方墙壁
	mapBeforeAndBack(3.0, 1.0, -20.0, 20.0, 20.0, 0.0, 10.0);
	//地板
	glBindTexture(GL_TEXTURE_2D, textureVector[3]);
	mapUpAndDown(5, 5, -20.0, 20.0, -20.0, 20.0, 0.0);
	//天花板
	mapUpAndDown(5, 5, -20.0, 20.0, -20.0, 20.0, 10.0);
	//黑地板
	glBindTexture(GL_TEXTURE_2D, textureVector[4]);
	mapUpAndDown(40.0, 40.0, -40.0, 40.0, -40.0, 40.0,-0.5);
	//小屋子窗口
	glBindTexture(GL_TEXTURE_2D, textureVector[5]);
	mapBeforeAndBack(1.0, 1.0, 0.0, 7.0, 19.99, 3.0, 7.0);
	glBindTexture(GL_TEXTURE_2D, textureVector[8]);
	mapLeftAndRight(1.0, 1.0, 19.6, -6.0, -14.0, 3.0, 7.0);
	//大厅贴图一
	glBindTexture(GL_TEXTURE_2D, textureVector[7]);
	mapBeforeAndBack(1.0, 1.0, 7.0, 13.0, -19.99, 2.0, 8.0);//
	//大厅贴图二
	glBindTexture(GL_TEXTURE_2D, textureVector[6]);
	mapLeftAndRight(1.0, 1.0, 16.0, 10.0, 5.0, 0.0, 9);
	//正面立体图
	glBindTexture(GL_TEXTURE_2D, textureVector[9]);
	mapBeforeAndBack(1.0, 1.0, 16.0, 20.0, 5.0, 0.0, 9);
	mapBeforeAndBack(1.0, 1.0, 16.0, 20.0, 10.0, 0.0, 9);
	mapUpAndDown(1.0, 1.0, 16.0, 20.0, 10.0, 5.0, 9);
	//床头照
	glBindTexture(GL_TEXTURE_2D, textureVector[0]);
	mapBeforeAndBack(1.0, 1.0, 13.5, 19.5, 19.99, 2.5, 7.5);
	glBindTexture(GL_TEXTURE_2D, textureVector[10]);
	mapBeforeAndBack(1.0, 1.0, 14.0, 19.0, 19.80, 3.0, 7.0);
	//床
	glBindTexture(GL_TEXTURE_2D, textureVector[11]);
	mapBeforeAndBack(1.0, 1.0, 13.0, 20.0, 19.3, 0.0, 2.5);
	mapLeftAndRight(1.0, 1.0, 13.0, 20.0, 19.3, 0.0, 2.5);
	mapUpAndDown(1.0, 1.0, 13.0, 20.0, 20.0, 19.3, 2.5);
	mapUpAndDown(1.0, 1.0, 13.0, 20.0, 20.0, 11.0, 1.0);
	mapLeftAndRight(1.0, 1.0, 13.0, 20.0, 11.0, 0.0, 1.0);
	mapBeforeAndBack(1.0, 1.0, 13.0, 20.0, 11.0, 0.0, 1.0);
	//被子
	glBindTexture(GL_TEXTURE_2D, textureVector[12]);
	mapUpAndDown(1.0, 1.0, 12.99, 20.0, 17.0, 11.0, 1.01);
	mapLeftAndRight(1.0, 1.0, 12.99, 17.0, 11.0, 0.0, 1.01);
	//枕头
	glBindTexture(GL_TEXTURE_2D, textureVector[13]);
	mapBeforeAndBack(1.0, 1.0, 17.0, 19.0, 18.0, 0.0, 1.5);
	mapLeftAndRight(1.0, 1.0, 17.0, 20.0, 18.0, 0.0, 1.5);
	mapUpAndDown(1.0, 1.0, 17.0, 19.0, 20.0, 18.0, 1.5);
	mapBeforeAndBack(1.0, 1.0, 14.0, 16.0, 18.0, 0.0, 1.5);
	mapLeftAndRight(1.0, 1.0, 14.0, 20.0, 18.0, 0.0, 1.5);
	mapUpAndDown(1.0, 1.0, 14.0, 16.0, 20.0, 18.0, 1.5);
	//小房间墙
	glBindTexture(GL_TEXTURE_2D, textureVector[0]);
	mapBeforeAndBack(2.0, 1.0, -3.0, 20.0, 0.0, 0.0, 10.0);
	mapLeftAndRight(2.0, 1.0, -3.0, 20.0, 0.0, 0.0, 10.0);

	//小房间壁纸一
	glBindTexture(GL_TEXTURE_2D, textureVector[14]);
	mapBeforeAndBack(1.0, 1.0, 0.0, 15.0, 0.09, 3.0, 8.0);
	//壁纸二
	glBindTexture(GL_TEXTURE_2D, textureVector[15]);
	mapLeftAndRight(1.0, 1.0, -2.90, 5.0, 10, 2.0, 9.0);
	glBindTexture(GL_TEXTURE_2D, textureVector[16]);
	mapLeftAndRight(1.0, 1.0, -2.90, 10, 15, 2.0, 9.0);

	glPopMatrix();//2
	glFlush();//用于强制刷新缓存
	glutSwapBuffers();//交换双缓存//实现动画的机制
	glutPostRedisplay();//标志下次刷新，没有的话，程序打开后不会刷新界面
}
void threeObservat(int w, int h)
{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//在默认情况下，视口被设置为占据打开窗口的整个像素矩形
	glMatrixMode(GL_PROJECTION);//选择投影矩阵
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵
	gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 1, 800.0);//角度，宽高比，z轴近处，远处。
	glMatrixMode(GL_MODELVIEW);//模型视景矩阵||GL_TEXTURE,对纹理矩阵堆栈应用随后的矩阵操作.
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, -10, 3, 0.0, 0.0, 1.0);
	if (h == 0) { //如果高度为0   
		h = 1;   //让高度为1（避免出现分母为0的现象）        
	}
}
//键盘
//------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 65: case 97://A灯开关
		if (light)
			light = false;//std::cout << "light" << " " << light << std::endl;
		else
			light = true;
		break;
	case 83: case 115://W键上升
		Oz += 1.0f;
		std::cout << "w/W" <<" "<< Oz << std::endl;
		break;
	case 87: case 119://S键下降
		Oz -= 1.0f;
		std::cout << "s/S" <<" " << Oz << std::endl;
		break;
	case 27:
		exit(0);
		break;
	case 32://空格旋转
		if (!rolate) {
			glutIdleFunc(spinDisplay);  //设备空闲时调用的函数
			rolate = true;
		}
		else {
			glutIdleFunc(nullptr);
			rolate = false;
		}
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------------
//特殊按钮
void SpecialKey(GLint key, GLint x, GLint y) {
	switch (key) {
	case GLUT_KEY_UP:
		Ox += step * sin(direction / 180 * PI);
		Oy += step * cos(direction / 180 * PI);
		std::cout << "up" <<" " << Ox << " " << Oy << std::endl;
		break;
	case GLUT_KEY_DOWN:
		Ox -= step * sin(direction / 180 * PI);
		Oy -= step * cos(direction / 180 * PI);
		std::cout << "down" <<" " << Ox << " " << Oy << std::endl;
		break;
	case GLUT_KEY_LEFT:
		direction = direction - 2;
		std::cout << "dirLeft" <<" " << direction << std::endl;
		break;
	case GLUT_KEY_RIGHT:
		direction = direction + 2;
		std::cout << "dirRight" << " " << direction << std::endl;
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------------------------
//设置控制台
bool setConsole(int width, int height)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出句柄
	SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; //设置宽高
	bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // 设置窗体尺寸
	if (!ret) return false;
	COORD coord = { width, height };
	ret = SetConsoleScreenBufferSize(hOutput, coord); // 设置缓冲尺寸
	return ret;
	SetConsoleTitleA("loveMiaoW"); //设置新标题
}

void curInfo()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出句柄
	CONSOLE_CURSOR_INFO cInfo{};
	GetConsoleCursorInfo(hOutput, &cInfo); //获取现有光标信息
	cInfo.bVisible = false; //false为隐藏窗口,true为显示窗口
	SetConsoleCursorInfo(hOutput, &cInfo);  //重新设置光标信息
}
void fibChange()
{
	HWND hWnd = GetConsoleWindow(); //获取窗口句柄
	LONG_PTR sty = GetWindowLongPtrA(hWnd, GWL_STYLE); //获取窗口样式
	sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX; //去除可变化大小,最大,最小化按钮,~是取反,&是与,这是位运算相关的知识了
	SetWindowLongPtrA(hWnd, GWL_STYLE, sty); //设置窗体不可更改大小,不可最大化
}

void mvName()
{
	SetConsoleTitleA("导航操作指南--<loveMiaoW>"); //设置新标题
}

void moveWindows()
{
	HWND hWnd = GetConsoleWindow(); //获取窗口句柄
	MoveWindow(hWnd, 1, 1, 710, 780, false);
}
int main(int argc, char* argv[])
{
	setConsole(100, 50);
	fibChange();
	curInfo();
	mvName();
	moveWindows();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//实现动画的机制
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(450, 300);
	glutCreateWindow("warmRoomFromLoveMiaoW");
	tip();
	init();
	glutDisplayFunc(display);//回调函数
	glutReshapeFunc(threeObservat);
	glutKeyboardFunc(&keyboard);//键盘
	glutSpecialFunc(&SpecialKey);//键盘
	createGLUTMenus();
	glutMainLoop();
	return 0;
}