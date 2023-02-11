#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <sys/stat.h>
/*
	web������ 
	B/S
	c/c++ socket������
	1 ��������ͷ�����������ϵ
*/

char rootPath[128] = "./web/"; //�ļ���Ŀ¼

//����socket��
void init_socket() {
	//ȷ��socket�汾��Ϣ2.2
	WSADATA wsadata;
	if (WSAEINVAL == WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		printf("WSAStartup failed,%d\n", WSAGetLastError());
		exit(-1);
	}
}
//�ر�socket
void close_socket() {
	WSACleanup();
}
//����������
SOCKET startServer(const char* ip,unsigned short port) {
	//1 �����׽��� TCP UDP
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET) {
		printf("socket create failed:%d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}
	//2 ��ip��ַ�Ͷ˿ں�
	SOCKADDR_IN serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);	//��� С��
	serAddr.sin_addr.S_un.S_addr = inet_addr(ip);	//���ʮ����IP��ַ -> ����IP��ַ
	if (SOCKET_ERROR == bind(fd, (const struct sockaddr*)&serAddr, sizeof(serAddr))) {
		printf("bind create failed:%d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	//3 ��ʼ����
	listen(fd, 5);


	return fd;
}
void sendFile(SOCKET fd, const char* filename) {
	FILE* fp = fopen(filename, "rb");
	if (!fp) {
		perror("file open failed");
		return;
	}
	char buf[BUFSIZ] = { 0 };

	while (!feof(fp)) {
		int len = fread(buf, sizeof(char), BUFSIZ, fp);
		send(fd, buf, len, 0);
	}

	fclose(fp);
}
//����ͻ�������
void requestHanding(SOCKET fd) {
	char buf[BUFSIZ] = { 0 };

	//����һ�¿ͻ��˷�������
	if (0 >= recv(fd, buf, BUFSIZ, 0)) {
		printf("recv falid,%d\n", WSAGetLastError());
		return;
	}
	//puts(buf);
	//������ GET / HTTP / 1.1
	//GET ���󷽷�
	// "/" ������Դ(index.html)
	//HTTP/1.1 ����Э��汾
	//
	char mothed[10] = { 0 };	//���󷽷�
	char url[128] = { 0 };		//������Դ
	char urlbackup[128] = { 0 };
	//����
	int index = 0;
	char* p;
	for (p = buf; *p != ' '; p++) {
		mothed[index++] = *p;
	}
	//puts(mothed);
	p++;			//�����ո�
	for (; *p != ' '; p++) {
		url[index++] = *p;
	}
	strcpy(urlbackup, url);
	//puts(url);

	//���ݲ�ͬ�����󷽷����в�ͬ�Ĵ���
	if (strcmp(mothed, "GET") == 0) {
		printf("you use GET mothed\n");
		//strcpy(url, rootPath);
		//strcat(url, (strcmp(url, "/") == 0 ? "/index.html" : url));
		//sprintf(url, "%s%s", rootPath, (strcmp(urlbackup, "/") == 0 ? "/index.html" : urlbackup));
		strcpy(url,"./web/index.html");
		//printf("urlpath %s\n", url);
		//�ж��ļ��Ƿ����
		//puts(url);
		struct _stat32 stat;
		if (-1 == _stat32(url, &stat)) {
			char file[128] = { 0 };
			//sprintf(file, "%s%s", rootPath, "404.html");
			strcpy(file, "./web/404.html");
			//printf("path %s\n", file);
			sendFile(fd, file);
		}
		else {
			printf("path %s\n", url);
			sendFile(fd, url);
		}
		//printf("%d,\n", ret);
	}
	else if (strcmp(mothed, "POST") == 0) {

	}
}



int main() {
	init_socket();
	SOCKET serfd = startServer("0.0.0.0", 80);
	while (1) {
		SOCKET clifd = accept(serfd, NULL, NULL);
	//	char buf[] = "<h1>hellor world</h1>";
	//	send(clifd, buf, strlen(buf), 0);
		requestHanding(clifd);
	}
	close_socket();
	return 0;
}