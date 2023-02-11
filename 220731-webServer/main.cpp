#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <sys/stat.h>
/*
	web服务器 
	B/S
	c/c++ socket网络编程
	1 让浏览器和服务器建立联系
*/

char rootPath[128] = "./web/"; //文件根目录

//开启socket库
void init_socket() {
	//确定socket版本信息2.2
	WSADATA wsadata;
	if (WSAEINVAL == WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		printf("WSAStartup failed,%d\n", WSAGetLastError());
		exit(-1);
	}
}
//关闭socket
void close_socket() {
	WSACleanup();
}
//开启服务器
SOCKET startServer(const char* ip,unsigned short port) {
	//1 创建套接字 TCP UDP
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET) {
		printf("socket create failed:%d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}
	//2 绑定ip地址和端口号
	SOCKADDR_IN serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);	//大端 小端
	serAddr.sin_addr.S_un.S_addr = inet_addr(ip);	//点分十进制IP地址 -> 整数IP地址
	if (SOCKET_ERROR == bind(fd, (const struct sockaddr*)&serAddr, sizeof(serAddr))) {
		printf("bind create failed:%d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	//3 开始监听
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
//处理客户端请求
void requestHanding(SOCKET fd) {
	char buf[BUFSIZ] = { 0 };

	//接受一下客户端发送请求
	if (0 >= recv(fd, buf, BUFSIZ, 0)) {
		printf("recv falid,%d\n", WSAGetLastError());
		return;
	}
	//puts(buf);
	//请求行 GET / HTTP / 1.1
	//GET 请求方法
	// "/" 请求资源(index.html)
	//HTTP/1.1 请求协议版本
	//
	char mothed[10] = { 0 };	//请求方法
	char url[128] = { 0 };		//请求资源
	char urlbackup[128] = { 0 };
	//解析
	int index = 0;
	char* p;
	for (p = buf; *p != ' '; p++) {
		mothed[index++] = *p;
	}
	//puts(mothed);
	p++;			//跳过空格
	for (; *p != ' '; p++) {
		url[index++] = *p;
	}
	strcpy(urlbackup, url);
	//puts(url);

	//根据不同的请求方法进行不同的处理
	if (strcmp(mothed, "GET") == 0) {
		printf("you use GET mothed\n");
		//strcpy(url, rootPath);
		//strcat(url, (strcmp(url, "/") == 0 ? "/index.html" : url));
		//sprintf(url, "%s%s", rootPath, (strcmp(urlbackup, "/") == 0 ? "/index.html" : urlbackup));
		strcpy(url,"./web/index.html");
		//printf("urlpath %s\n", url);
		//判断文件是否存在
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