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
static GLuint textureVector[100];			//�����������ȫ���������飬�洢λͼת���õ�������
static GLuint color[3];				//���������ɫ

static double Ox = 0;				//���ε�ȫ��λ�ñ���
static double Oy = 0;
static double Oz = 0;

static double direction = 0;			//վ��λ�ü�ǰ������
static double step = 0.4;				//�ƶ��ĵ�λ
static GLfloat spin = 0.0;				//���ڵ�����ת��ȫ�ֱ���

bool light = false;						//�ƹ��־
bool rolate = false;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//***************************************************^^^**********************************************************//
//*********************************************<__����Ч��__>*****************************************************//
//***************************************************  ***********************************************************//
void bgm() {
	MCI_OPEN_PARMS op;
	op.dwCallback = NULL;
	op.lpstrAlias = NULL;
	op.lpstrDeviceType = L"MPEGAudio";			//mp3��ʽ
	op.lpstrElementName = L"res/loveHome.wav";			//�ļ���
	op.wDeviceID = NULL;
	MCI_PLAY_PARMS pp;							//
	pp.dwCallback = NULL;
	pp.dwFrom = 0;								//�ļ���ͷ

	UINT rs;
	rs = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&op);

	if (rs == 0)
	{
		MCI_PLAY_PARMS pp;
		pp.dwCallback = NULL;
		pp.dwFrom = 0;
		//�豸ID ���� 
		mciSendCommand(op.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&pp);
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//***************************************************^^^**********************************************************//
//*********************************************<__װ������ͼ__>***************************************************//
//***************************************************  ***********************************************************//
void loadTexture(const char* filename, GLuint& texture)// ����λͼ�ļ������ƽ��м���

{
	static GLint    ImageWidth;
	static GLint    ImageHeight;
	static GLint    PixelLength;
	static GLubyte* PixelData;
	// ���ļ�
	FILE* pFile = fopen(filename, "rb"); // �ļ�ָ��
	if (pFile == 0)  // ���û��ָ��λͼ�ļ����ƾ��˳�
		exit(0);
	// ��ȡ24λbmpͼ��Ĵ�С��Ϣ
	fseek(pFile, 0x0012, SEEK_SET);//�ļ�ָ��ָ���ļ��Ŀ�ͷͼ��Ŀ�Ⱥ͸߶ȶ���һ��32λ���������ļ��еĵ�ַ�ֱ�Ϊ0x0012��0x0016���������ǿ���ʹ�����´�������ȡͼ��Ĵ�С��Ϣ���ƶ���0x0016λ��
	// ������һ��ִ�к󱾾�Ӧ����0x0016λ��
	fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);//���ļ��ڵĿ�����ݴ�Ÿ�imagewidth
	fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);
	PixelLength = ImageWidth * 3;	// �����������ݳ���
	while (PixelLength % 4 != 0)	//bmpͼ��֤��������ĳ�����4�ı���,����������Ҫ��ÿ�е����ݵĳ��ȱ�����4�ı��������������Ҫ���б�����䣨��0��䣩���������Դﵽ���еĿ��ٴ�ȡ��
		++PixelLength;//�������ȡ���ݹ���
	PixelLength *= ImageHeight;
	// ��ȡ��������
	PixelData = (GLubyte*)malloc(PixelLength);	//��̬���û���
	if (PixelData == 0)	exit(0);
	fseek(pFile, 0, SEEK_SET);
	fread(PixelData, PixelLength, 1, pFile);
	// �ر��ļ�
	fclose(pFile);
	//��������
	glGenTextures(1, &texture);//�����������������   �洢���������ĵ�һ��Ԫ��ָ��

	glBindTexture(GL_TEXTURE_2D, texture);//�󶨣�ָ��������������ɵ���������ư󶨵�ָ����������
	//����Ķ��庯��
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	//
	//����Ŀ��ƺ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);		//������˺���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //������ض�һ������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	//����һ��2D����Texture����bmpͼƬ������˳����BGR������GL_BGR_EXT�������������
}
//���ڹ���
void lightinit(double x, double y)
{
	//���ʷ���������
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //���淴�����
	GLfloat mat_shininess[] = { 50.0 };               //�߹�ָ��
	GLfloat light_position[] = { Ox, Oy, Oz - 10, 1.0 };//��λ��(1,1,1), ���1-����
	GLfloat white_light[] = { 1, 1, 1, 1.0 };
	GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; //���������
	//��������⣬������⣬���淴���
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//��Դλ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //ɢ�������
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //���淴���

	//���ղ���
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //���������

	if (light) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//�����¼�/
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//ֻ������,������GL_MODULATE,GL_DECAL��GL_BLEND
	}
	glEnable(GL_LIGHTING);   //����:ʹ�ù�
	glEnable(GL_LIGHT0);     //��0#��
	glEnable(GL_DEPTH_TEST); //����Ȳ���
}

//������ת
void spinDisplay(void)
{
	std::cout << "spin" << spin << std::endl;
	spin = spin + 0.08;
	if (spin > 360.0)
	{
		spin = spin - 360.0;
	}
	glutPostRedisplay();//glutPostRedisplay ��ǵ�ǰ������Ҫ���»��ơ�ͨ��glutMainLoop��һ��ѭ��ʱ��������ʾ�����ص���������ʾ���ڵ��������
}

//��ʼ��
GLUquadricObj* g_text;//���棬����һ����Χ����Ĵ�����������
void init(void)

{
	srand(unsigned(time(nullptr)));//��������������
	glClearColor(0.0, 0.0, 0.0, 0.0);//�����ɫ��������������ɫ
	glShadeModel(GL_FLAT);//������ɫģʽ GL_FLAT �㶨��ɫ��GL_SMOOTH�⻬��ɫ

	g_text = gluNewQuadric();//���������������������ڻ�ͼ����ʾ֮ǰ�����µĶ����������
	//װ��λͼ
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

//��ͼ����
//������
void mapLeftAndRight(float m, float n, float x, float y1, float y2, float z1, float z2) {

	glBegin(GL_QUADS);//�����Ӧƽ��
	glTexCoord2f(0.0, 0.0); glVertex3f(x, y1, z1);
	glTexCoord2f(0.0, n); glVertex3f(x, y1, z2);
	glTexCoord2f(m, n); glVertex3f(x, y2, z2);
	glTexCoord2f(m, 0.0); glVertex3f(x, y2, z1);
	glEnd();
}
//ǰ����
void mapBeforeAndBack(float m, float n, float x1, float x2, float y, float z1, float z2) {

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(x1, y, z1);
	glTexCoord2f(0.0, n); glVertex3f(x1, y, z2);
	glTexCoord2f(m, n); glVertex3f(x2, y, z2);
	glTexCoord2f(m, 0.0); glVertex3f(x2, y, z1);
	glEnd();
}
//������
void mapUpAndDown(float m, float n, float x1, float x2, float y1, float y2, float z) {

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(x1, y1, z);
	glTexCoord2f(0.0, n); glVertex3f(x1, y2, z);
	glTexCoord2f(m, n); glVertex3f(x2, y2, z);
	glTexCoord2f(m, 0.0); glVertex3f(x2, y1, z);
	glEnd();
}
//--------------------------------------------------------------------------------------------------------------


//---------------------------------------------�˵���Ӧ����-----------------------------------------------------
#define START 1
int flag = 1;
//������˵�ʱ,���ûص����� func��value Ϊ���ݸ��ص���������ֵ,������ѡ��Ĳ˵���Ŀ��Ӧ ������ֵ��������
void processMenuEvents(int option)
{
	//option�����Ǵ��ݹ����� value ��ֵ��
	switch (option) {
	case START:
		bgm();
		break;
	}
}

void createGLUTMenus()
{
	int menu;
	// �����˵������� GLUT��processMenuEvents ����˵��¼���
	menu = glutCreateMenu(processMenuEvents);
	//���˵�������Ŀ
	glutAddMenuEntry("����~", START);
	// �Ѳ˵�������Ҽ�����������
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
		<< "  ///****************************** ����˵�� ********************************////" << std::endl
		<< "  ///**************************** ���� A ���Ĺ���ǿ��  **********************////" << std::endl
		<< "  ///**************************** �ո� space ��ת  **************************////" << std::endl
		<< "  ///**************************** ����Ҽ��������� **************************////" << std::endl
		<< "  ///**************************** ���¼�ǰ�����ˣ����Ҽ�תͷ��WS�����½� ****////" << std::endl
		<< "  ///********* ��Ŀ��ַ: https://github.com/loveMiaoW/loveMiaoW.git *********////" << std::endl
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
		<< "	///       ^ ���汣��       ����崻�       ����BUG ^            ///" << std::endl
		<< "	///  ^ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        ///" << std::endl
		<< "	//////////////////////////////////////////////////////////////////" << std::endl;
}
//-----------------------------------------------------------------------------------------------------------------

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ�����Լ���Ȼ�
	glEnable(GL_TEXTURE_2D);
	//�������������ӳ��,�����������
	gluQuadricTexture(g_text, GLU_TRUE);              //������������ ʹ������ȷ��
	gluQuadricDrawStyle(g_text, GLU_FILL);            //�������  ʵ��
	glPushMatrix();//2
	glRotatef((GLfloat)direction, 0.0, 0.0, 1.0);//�ص������󣬼��̽������Ӱ�������,�ı������ת
	glTranslated(Ox - 18, Oy - 18, Oz);
	glPushMatrix();//4

	glRotatef(spin * 3, 0.0, 0.0, 1.0);//������ת����

	glBindTexture(GL_TEXTURE_2D, textureVector[1]);
	gluSphere(g_text, 60, 3600, 3600);//����
	glBindTexture(GL_TEXTURE_2D, textureVector[2]);
	gluSphere(g_text, 55, 3600, 3600);

	//����ѹջ
	//-------���´���ɾ��----������ǿ
	glPushMatrix();//7
	lightinit(Ox, Oy);
	glPopMatrix();//7

	glPopMatrix();//4

	//
	glBindTexture(GL_TEXTURE_2D, textureVector[0]);
	//�ұ�ǽ
	mapLeftAndRight(3.0, 1.0, -20.0, -20.0, 20.0, 0.0, 10.0);
	//���ǽ
	mapLeftAndRight(3.0, 1.0, 20.0, -20.0, 20.0, 0.0, 10.0);
	//ǰ��ǽ��
	mapBeforeAndBack(3.0, 1.0, -20.0, 20.0, -20.0, 0.0, 10.0);
	//��ǽ��
	mapBeforeAndBack(3.0, 1.0, -20.0, 20.0, 20.0, 0.0, 10.0);
	//�ذ�
	glBindTexture(GL_TEXTURE_2D, textureVector[3]);
	mapUpAndDown(5, 5, -20.0, 20.0, -20.0, 20.0, 0.0);
	//�컨��
	mapUpAndDown(5, 5, -20.0, 20.0, -20.0, 20.0, 10.0);
	//�ڵذ�
	glBindTexture(GL_TEXTURE_2D, textureVector[4]);
	mapUpAndDown(40.0, 40.0, -40.0, 40.0, -40.0, 40.0,-0.5);
	//С���Ӵ���
	glBindTexture(GL_TEXTURE_2D, textureVector[5]);
	mapBeforeAndBack(1.0, 1.0, 0.0, 7.0, 19.99, 3.0, 7.0);
	glBindTexture(GL_TEXTURE_2D, textureVector[8]);
	mapLeftAndRight(1.0, 1.0, 19.6, -6.0, -14.0, 3.0, 7.0);
	//������ͼһ
	glBindTexture(GL_TEXTURE_2D, textureVector[7]);
	mapBeforeAndBack(1.0, 1.0, 7.0, 13.0, -19.99, 2.0, 8.0);//
	//������ͼ��
	glBindTexture(GL_TEXTURE_2D, textureVector[6]);
	mapLeftAndRight(1.0, 1.0, 16.0, 10.0, 5.0, 0.0, 9);
	//��������ͼ
	glBindTexture(GL_TEXTURE_2D, textureVector[9]);
	mapBeforeAndBack(1.0, 1.0, 16.0, 20.0, 5.0, 0.0, 9);
	mapBeforeAndBack(1.0, 1.0, 16.0, 20.0, 10.0, 0.0, 9);
	mapUpAndDown(1.0, 1.0, 16.0, 20.0, 10.0, 5.0, 9);
	//��ͷ��
	glBindTexture(GL_TEXTURE_2D, textureVector[0]);
	mapBeforeAndBack(1.0, 1.0, 13.5, 19.5, 19.99, 2.5, 7.5);
	glBindTexture(GL_TEXTURE_2D, textureVector[10]);
	mapBeforeAndBack(1.0, 1.0, 14.0, 19.0, 19.80, 3.0, 7.0);
	//��
	glBindTexture(GL_TEXTURE_2D, textureVector[11]);
	mapBeforeAndBack(1.0, 1.0, 13.0, 20.0, 19.3, 0.0, 2.5);
	mapLeftAndRight(1.0, 1.0, 13.0, 20.0, 19.3, 0.0, 2.5);
	mapUpAndDown(1.0, 1.0, 13.0, 20.0, 20.0, 19.3, 2.5);
	mapUpAndDown(1.0, 1.0, 13.0, 20.0, 20.0, 11.0, 1.0);
	mapLeftAndRight(1.0, 1.0, 13.0, 20.0, 11.0, 0.0, 1.0);
	mapBeforeAndBack(1.0, 1.0, 13.0, 20.0, 11.0, 0.0, 1.0);
	//����
	glBindTexture(GL_TEXTURE_2D, textureVector[12]);
	mapUpAndDown(1.0, 1.0, 12.99, 20.0, 17.0, 11.0, 1.01);
	mapLeftAndRight(1.0, 1.0, 12.99, 17.0, 11.0, 0.0, 1.01);
	//��ͷ
	glBindTexture(GL_TEXTURE_2D, textureVector[13]);
	mapBeforeAndBack(1.0, 1.0, 17.0, 19.0, 18.0, 0.0, 1.5);
	mapLeftAndRight(1.0, 1.0, 17.0, 20.0, 18.0, 0.0, 1.5);
	mapUpAndDown(1.0, 1.0, 17.0, 19.0, 20.0, 18.0, 1.5);
	mapBeforeAndBack(1.0, 1.0, 14.0, 16.0, 18.0, 0.0, 1.5);
	mapLeftAndRight(1.0, 1.0, 14.0, 20.0, 18.0, 0.0, 1.5);
	mapUpAndDown(1.0, 1.0, 14.0, 16.0, 20.0, 18.0, 1.5);
	//С����ǽ
	glBindTexture(GL_TEXTURE_2D, textureVector[0]);
	mapBeforeAndBack(2.0, 1.0, -3.0, 20.0, 0.0, 0.0, 10.0);
	mapLeftAndRight(2.0, 1.0, -3.0, 20.0, 0.0, 0.0, 10.0);

	//С�����ֽһ
	glBindTexture(GL_TEXTURE_2D, textureVector[14]);
	mapBeforeAndBack(1.0, 1.0, 0.0, 15.0, 0.09, 3.0, 8.0);
	//��ֽ��
	glBindTexture(GL_TEXTURE_2D, textureVector[15]);
	mapLeftAndRight(1.0, 1.0, -2.90, 5.0, 10, 2.0, 9.0);
	glBindTexture(GL_TEXTURE_2D, textureVector[16]);
	mapLeftAndRight(1.0, 1.0, -2.90, 10, 15, 2.0, 9.0);

	glPopMatrix();//2
	glFlush();//����ǿ��ˢ�»���
	glutSwapBuffers();//����˫����//ʵ�ֶ����Ļ���
	glutPostRedisplay();//��־�´�ˢ�£�û�еĻ�������򿪺󲻻�ˢ�½���
}
void threeObservat(int w, int h)
{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//��Ĭ������£��ӿڱ�����Ϊռ�ݴ򿪴��ڵ��������ؾ���
	glMatrixMode(GL_PROJECTION);//ѡ��ͶӰ����
	glLoadIdentity();//���õ�ǰָ���ľ���Ϊ��λ����
	gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 1, 800.0);//�Ƕȣ���߱ȣ�z�������Զ����
	glMatrixMode(GL_MODELVIEW);//ģ���Ӿ�����||GL_TEXTURE,����������ջӦ�����ľ������.
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, -10, 3, 0.0, 0.0, 1.0);
	if (h == 0) { //����߶�Ϊ0   
		h = 1;   //�ø߶�Ϊ1��������ַ�ĸΪ0������        
	}
}
//����
//------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 65: case 97://A�ƿ���
		if (light)
			light = false;//std::cout << "light" << " " << light << std::endl;
		else
			light = true;
		break;
	case 83: case 115://W������
		Oz += 1.0f;
		std::cout << "w/W" <<" "<< Oz << std::endl;
		break;
	case 87: case 119://S���½�
		Oz -= 1.0f;
		std::cout << "s/S" <<" " << Oz << std::endl;
		break;
	case 27:
		exit(0);
		break;
	case 32://�ո���ת
		if (!rolate) {
			glutIdleFunc(spinDisplay);  //�豸����ʱ���õĺ���
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
//���ⰴť
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
//���ÿ���̨
bool setConsole(int width, int height)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ������
	SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; //���ÿ��
	bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // ���ô���ߴ�
	if (!ret) return false;
	COORD coord = { width, height };
	ret = SetConsoleScreenBufferSize(hOutput, coord); // ���û���ߴ�
	return ret;
	SetConsoleTitleA("loveMiaoW"); //�����±���
}

void curInfo()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ������
	CONSOLE_CURSOR_INFO cInfo{};
	GetConsoleCursorInfo(hOutput, &cInfo); //��ȡ���й����Ϣ
	cInfo.bVisible = false; //falseΪ���ش���,trueΪ��ʾ����
	SetConsoleCursorInfo(hOutput, &cInfo);  //�������ù����Ϣ
}
void fibChange()
{
	HWND hWnd = GetConsoleWindow(); //��ȡ���ھ��
	LONG_PTR sty = GetWindowLongPtrA(hWnd, GWL_STYLE); //��ȡ������ʽ
	sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX; //ȥ���ɱ仯��С,���,��С����ť,~��ȡ��,&����,����λ������ص�֪ʶ��
	SetWindowLongPtrA(hWnd, GWL_STYLE, sty); //���ô��岻�ɸ��Ĵ�С,�������
}

void mvName()
{
	SetConsoleTitleA("��������ָ��--<loveMiaoW>"); //�����±���
}

void moveWindows()
{
	HWND hWnd = GetConsoleWindow(); //��ȡ���ھ��
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//ʵ�ֶ����Ļ���
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(450, 300);
	glutCreateWindow("warmRoomFromLoveMiaoW");
	tip();
	init();
	glutDisplayFunc(display);//�ص�����
	glutReshapeFunc(threeObservat);
	glutKeyboardFunc(&keyboard);//����
	glutSpecialFunc(&SpecialKey);//����
	createGLUTMenus();
	glutMainLoop();
	return 0;
}